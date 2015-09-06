#ifndef BINARY_TREE
#define BINARY_TREE

#include <initializer_list>
#include <iostream>
#include <vector>
#include <functional>


template<typename K,
         typename V >
/**
 * @brief Implementation of binary tree
 */
class binary_tree {

    template<typename, typename>
    /**
     * Implementation of a tree node
     */
    struct tree_node {
        K key;
        V val;

        tree_node<K, V>* left;
        tree_node<K, V>* right;

        // Not necessary fields, but they may be useful.
        bool is_leaf; //becomes true by default when init an object
        bool is_marked; //you can use this flag if you want to mark node (false by default)

        tree_node(const K& key, const V& val,
                  tree_node* left =nullptr,
                  tree_node* right =nullptr,
                  const bool is_leaf =true,
                  const bool is_marked =false) :
                key(key), val(val),
                left(left), right(right),
                is_leaf(is_leaf), is_marked(is_marked) {}

        ~tree_node() {
            if (left != nullptr)
                delete left;
            if (right != nullptr)
                delete right;
        }
    };

public:
    // Defining types for interface usage
    typedef tree_node<K, V> node;
    typedef std::function<void(node&, void* data)> executor; //callback, that is calling when user pass the tree
    typedef std::function<int(const K&, const K&)> comparator;  //callback that is calling to compare two objects

private:
    // Component functions
    V& _find(const K&, bool& flag) const;
    void _preorder_traversal(node*, executor, void*) const;
    void _symmetric_traversal(node*, executor, void*);
    void _beatiful_print(node*, int) const;
    void copy(node*& new_root, node* const& old_root);

protected:

    node* root;
    comparator compar;
    std::size_t size;

public:

    binary_tree() = delete;
    binary_tree(comparator);
    virtual ~binary_tree();

    //    TODO implement this constructor
//    binary_tree(std::initializer_list<K, V>, comparator);

    // Copy semantic
    binary_tree(const binary_tree<K, V>& cptree);
    binary_tree<K, V>& operator= (const binary_tree<K, V>& cptree);

    // Move semantic
    binary_tree(binary_tree<K, V>&& mvtree);
    binary_tree<K, V>& operator= (binary_tree<K, V>&& mvtree);

    // Element insertion
    virtual V& insert(const K&, const V&);
    virtual V& insert(std::pair<const K&, const V&>);

    // Accessing elements
    //    V& find(const K&) const;

    // Element insertion and acsessing (depend on is element exist)
    V& operator[] (const K&);

    // Deleting elements
    //    V delete_node(const V&);

    // Element passing
    virtual void preorder_traversal(executor, void*) const;
    //virtual void postorder_traversal(executor, void*);
    virtual void symmetric_traversal(executor, void *);
    virtual void beautiful_print() const;

    // Container information
    virtual constexpr bool is_empty() const final { return size == 0; };
    virtual constexpr size_t get_size() const final { return size; };
};


// Constructors
/**********************************************************************************************************************/
template<typename key_type, typename value_type>
/**
 * @brief binary_tree<value_type>::binary_tree standard constructor
 * @param cmp function to compare elements
 */
binary_tree<key_type, value_type>::
binary_tree(comparator cmp) {
    compar = cmp;
    size = 0;
    root = nullptr;
}

//TODO список инициализации для конструктора
//template<typename K, typename V>
//binary_tree<V>::
///**
// * @brief binary_tree constructor with initialization list
// * @param init_list list to init the tree
// * @param cmp function to compare elements
// */
//binary_tree(std::initializer_list<V> init_list, comparator cmp) {
//    compar = cmp;
//    root = nullptr;

//    for (const V it: init_list)
//        this->insert(it);

//}

template<typename K, typename V>
/**
 * @brief binary_tree::~binary_tree
 */
binary_tree<K, V>::
~binary_tree() {
    if (root != nullptr)
        delete root;
}

/**********************************************************************************************************************/


// Copy semantic
/**********************************************************************************************************************/
template<typename K, typename V>
binary_tree<K, V>::
/**
 * @brief binary_tree copy constructor
 * @param copy_tree tree to copy
 */
binary_tree(const binary_tree<K, V>& cptree) {

    // Init root an copy other data
    root = nullptr;
    compar = cptree.compar;
    size = cptree.size;

    // Copy all elements
    cptree.preorder_traversal([](node& node, void* _this) {
        binary_tree<K, V>* t = static_cast<binary_tree<K, V>* >(_this);
        (*t)[node.key] = node.val;
    }, static_cast<void*>(this));
}


template<typename K, typename V>
binary_tree<K, V>& binary_tree<K, V>::
/**
 * @brief operator =
 * @param cptree
 */
operator= (const binary_tree<K, V>& cptree) {

    // Init root an copy other data
    root = nullptr;
    compar = cptree.compar;
    size = cptree.size;

    // Copy all elements
    cptree.preorder_traversal([](node& node, void* _this) {
        binary_tree<K, V>* t = static_cast<binary_tree<K, V>* >(_this);
        (*t)[node.key] = node.val;
    }, static_cast<void*>(this));

    return *this;
}

/**********************************************************************************************************************/


// Move semantic
/**********************************************************************************************************************/

template<typename K, typename V>
binary_tree<K, V>::
/**
 * @brief binary_tree move constructor
 * @param copy_tree tree to move
 */
binary_tree(binary_tree<K, V>&& mvtree) {

    root = std::move(mvtree.root);
    compar = std::move(mvtree.compar);
    size = mvtree.size;

    mvtree.root = nullptr;
    mvtree.compar = nullptr;
    mvtree.size = 0;
}

template<typename K, typename V>
binary_tree<K, V>& binary_tree<K, V>::
/**
 * @brief operator =
 * @param cptree
 */
operator= (binary_tree<K, V>&& mvtree) {

    root = std::move(mvtree.root);
    compar = std::move(mvtree.compar);
    size = mvtree.size;

    mvtree.root = nullptr;
    mvtree.compar = nullptr;
    mvtree.size = 0;

    return *this;
}

/**********************************************************************************************************************/


// Element insertion and accessing
/**********************************************************************************************************************/
template<typename K, typename V>
/**
 * @brief binary_tree<V>::insert inserts element into a tree
 * @param val element to insert
 */
V& binary_tree<K, V>::
insert(const K& key, const V& val) {
    if (root == nullptr) {
        root = new node(key, val);
        return root->val;
    }
    else {
        node *n = root, *p;
        int result;
        while (n) {
            p = n;
            result = compar(key, n->key);
            if (result > 0) {
                n = p->right;
            }
            else if (result < 0) {
                n = p->left;
            }
            else {
                return p->val;
            }
        }

        if (result > 0) {
            p->right = new node(key, val);
            return p->right->val;
        }
        else {
            p->left = new node(key, val);
            return p->left->val;
        }

        size++;
    }
}


template <typename K, typename V>
/**
 *
 */
V& binary_tree<K, V>::
insert(std::pair<const K&, const V&> pair) {
    this->insert(pair.first, pair.second);
};

template<typename K, typename V>
/**
 * @brief binary_tree::find find elements in a tree
 * @param key key to search
 * @param is_contains flag that becomes true if element with key already exists
 * @return found element or root
 */
V& binary_tree<K, V>::
_find(const K& key, bool& is_contains) const {

    // If tree is empty, make contains flag false and return zero-value for V
    if (root == nullptr) {
        is_contains = false;
        return *(new V());

        // Else try to find key
    } else {
        node* node = root;
        int result = compar(key, root->key);
        while (node) {
            if (result > 0)
                node = node->right;
            else if (result < 0)
                node = node->left;
            else {
                is_contains = true;
                return node->val;
            }
            if (node)
                result = compar(key, node->key);
        }

        // if element is not in a tree, return zero-value for type V
        //return std::ref(V());
        return *(new V());
    }
}

template <typename K, typename V>
/**
 * @brief binary_tree<K, V>::operator []
 * Tries to find element with the key and return ref to it.
 * If key is not in a tree add a new node with this key and init it with
 * zero meaning.
 * @param key Key to access node
 * @return Reference to a value that contains in a node
 */
V& binary_tree<K, V>::
operator[](const K& key) {
    bool is_contains = false;
    V& x = this->_find(key, is_contains);

    if (is_contains) {
        return x;
    }
    else {
        return this->insert(key, V());
    }
}

/**********************************************************************************************************************/


// Deleting elements
/**********************************************************************************************************************/


/**********************************************************************************************************************/


// Elements passing
/**********************************************************************************************************************/

template<typename K, typename V>
void binary_tree<K, V>::
_beatiful_print(node* node, int level) const {
    if (node) {
        _beatiful_print(node->right, level+1);
        for (int i = 0; i < level; i++)
            std::cout << "     ";
        std::cout << node->key << ":" << node->val << std::endl;
        _beatiful_print(node->left, level+1);
    }
}

template<typename K, typename V>
void binary_tree<K, V>::
beautiful_print() const {
    _beatiful_print(root, 0);
}

template<typename K, typename V>
/**
 * @brief binary_tree<V>::_symmetric_pass symmetric pass of the tree
 * @param node element, from which pass starts
 * @param exec function that executes for every node
 * @param data data that will be passed into executor
 */
void binary_tree<K, V>::
_symmetric_traversal(node *node, executor exec, void *data) {

    if (node) {
        _symmetric_traversal(node->left, exec, data);

        exec(*node, data);

        _symmetric_traversal(node->right, exec, data);
    }
}

template<typename K, typename V>
/**
 * @brief binary_tree<V>::symmetric_pass interface for _symmetric_pass
 * @param exec executor function
 * @param data data that will be passed into executor
 */
void binary_tree<K, V>::
symmetric_traversal(executor exec, void *data) {
    _symmetric_traversal(root, exec, data);
}

template <typename K, typename V>
/**
 *
 */
void binary_tree<K, V>::
_preorder_traversal(node* n, executor exec, void* data) const {

    exec(*n, data);
    if (n->left != nullptr) _preorder_traversal(n->left, exec, data);
    if (n->right != nullptr) _preorder_traversal(n->right, exec, data);

}

template <typename K, typename V>
/**
 *
 */
void binary_tree<K, V>::
preorder_traversal(executor exec, void* data) const {
    _preorder_traversal(root, exec, data);
}

/**********************************************************************************************************************/

// Container information
/**********************************************************************************************************************/


/**********************************************************************************************************************/

#endif // BINARY_TREE

