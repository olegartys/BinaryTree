#ifndef BINARY_TREE
#define BINARY_TREE

#include "tree_node.tpp"
#include <initializer_list>
#include <iostream>
#include <vector>

template<typename node_type>
class tree_node;

template<typename node_type>
/**
 * @brief Implementation of binary tree
 */
class binary_tree {
private:
    typedef tree_node<node_type> node;
    typedef int (*comparator)(const node_type&, const node_type&); //callback для сравнения двух элементов дерева
    typedef void (*executor)(node&, void* data); //callback, вызывающаяся для каждого элемента дерева

    node* root;
    comparator compar;

    void _symmetric_pass(node* , executor, void*) const;
    void _beatiful_print(node*, int) const;

public:
    binary_tree(comparator);
    binary_tree(std::initializer_list<node_type>, comparator);
    binary_tree(const binary_tree<node_type>& copy_tree);

    bool is_empty() const;

    void insert(const node_type&);
    node_type delete_node(const node_type&);
    node_type find(const node_type&) const;

    void symmetric_pass(executor, void*) const;

    void beautiful_print() const;

    ~binary_tree();
};

template<typename node_type>
/**
 * @brief binary_tree<node_type>::insert inserts element into a tree
 * @param val element to insert
 */
void binary_tree<node_type>::
insert(const node_type& val) {
    if (root == nullptr)
        root = new node(val);
    else {
        node *n = root, *p;
        int result;
        while (n) {
            p = n;
            result = (*compar)(val, n->val);
            if (result > 0) {
                n = p->right;
            }
            else if (result < 0) {
                n = p->left;
            }
            else
                return;
        }
        if (result > 0)
            p->right = new node(val);
        else
            p->left = new node(val);
    }
}

template<typename node_type>
/**
 * @brief binary_tree<node_type>::binary_tree standard constructor
 * @param cmp function to compare elements
 */
binary_tree<node_type>::
binary_tree(comparator cmp) {
    compar = cmp;
    root = nullptr;
}

template<typename node_type>
binary_tree<node_type>::
/**
 * @brief binary_tree constructor with initialization list
 * @param init_list list to init the tree
 * @param cmp function to compare elements
 */
binary_tree(std::initializer_list<node_type> init_list, comparator cmp) {
    compar = cmp;
    root = nullptr;

    for (const node_type it: init_list)
        this->insert(it);

}

template<typename node_type>
binary_tree<node_type>::
/**
 * @brief binary_tree copy constructor
 * @param copy_tree tree to copy
 */
binary_tree(const binary_tree<node_type>& copy_tree) {

    // Init root
    root = nullptr;

    // Function to compare elements
    compar = copy_tree.compar;

    // Vector with elemennts of old tree
    std::vector<node_type>* values_to_copy = new std::vector<node_type>();

    // Init this vector
    copy_tree.symmetric_pass(
        [](const node_type& val, void* values_to_copy) {((std::vector<node_type>*)values_to_copy)->push_back(val);},
        (void*)values_to_copy);

    // Insert elements from vector into tree
    for (auto it: *values_to_copy)
        this->insert(it);

    delete values_to_copy;
}

template<typename node_type>
/**
 * @brief binary_tree::is_empty check whether tree is empty
 * @return true if is empty
 */
bool binary_tree<node_type>::
is_empty() const {
    return (root == nullptr);
}

template<typename node_type>
/**
 * @brief binary_tree::find find elements in a tree
 * @param val value to search
 * @return element or nullptr
 */
node_type binary_tree<node_type>::
find(const node_type& val) const {
    node* node = root;
    int result = (*compar)(val, root);
    while (node) {
        if (result > 0)
            node = node->right;
        else if (result < 0)
            node = node->left;
        else
            return result;
    }
    return nullptr;
}

template<typename node_type>
/**
 * @brief binary_tree<node_type>::_symmetric_pass symmetric pass of the tree
 * @param node element, from which pass starts
 * @param exec function that executes for every node
 * @param data data that will be passed into executor
 */
void binary_tree<node_type>::
_symmetric_pass(node *node, executor exec, void* data) const {

    if (node) {
        _symmetric_pass(node->left, exec, data);

        (*exec)(*node, data);

        _symmetric_pass(node->right, exec, data);
    }
}

template<typename node_type>
/**
 * @brief binary_tree<node_type>::symmetric_pass interface for _symmetric_pass
 * @param exec executor function
 * @param data data that will be passed into executor
 */
void binary_tree<node_type>::
symmetric_pass(executor exec, void* data) const {
    _symmetric_pass(root, exec, data);
}

template<typename node_type>
/**
 * @brief binary_tree::~binary_tree
 */
binary_tree<node_type>::
~binary_tree() {
    if (root != nullptr)
        delete root;
}

template<typename node_type>
void binary_tree<node_type>::
_beatiful_print(node* node, int level) const {
    if (node) {
        _beatiful_print(node->right, level+1);
        for (int i = 0; i < level; i++)
            std::cout << "     ";
        std::cout << node->get_val() << std::endl;
        _beatiful_print(node->left, level+1);
    }
}

template<typename node_type>
void binary_tree<node_type>::
beautiful_print() const {
    _beatiful_print(root, 0);
}

#endif // BINARY_TREE

