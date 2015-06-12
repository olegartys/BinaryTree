#ifndef BINARY_TREE
#define BINARY_TREE

#include "tree_node.tpp"
#include <initializer_list>
#include <iostream>
#include <vector>

template<typename key_type, typename value_type>
class tree_node;

template<typename key_type, typename value_type>
/**
 * @brief Implementation of binary tree
 */
class binary_tree {
private:
    typedef tree_node<key_type, value_type> node;
    typedef int (*comparator)(const key_type&, const key_type&); //callback для сравнения двух элементов дерева
    typedef void (*executor)(node&, void* data); //callback, вызывающаяся для каждого элемента дерева


    comparator compar;

    void _symmetric_pass(node* , executor, void*) const;
    void _beatiful_print(node*, int) const;

public:
    node* root;
    binary_tree(comparator);
//    binary_tree(std::initializer_list<value_type>, comparator);
//    binary_tree(const binary_tree<value_type>& copy_tree);

    bool is_empty() const;

    void insert(const key_type&, const value_type&);
    value_type& operator[] (const key_type&);
    value_type& operator= (const value_type&);
//    value_type delete_node(const value_type&);
    value_type& find(const key_type&) const;

    void symmetric_pass(executor, void*) const;

    void beautiful_print() const;

    ~binary_tree();
};

template<typename node_type, typename value_type>
value_type& binary_tree<node_type, value_type>::
operator= (const value_type& rvalue) {

    std::cout << "I am here" << std::endl;

}

template<typename node_type, typename value_type>
/**
 * @brief binary_tree<value_type>::insert inserts element into a tree
 * @param val element to insert
 */
void binary_tree<node_type, value_type>::
insert(const node_type& key, const value_type& val) {
    if (root == nullptr)
        root = new node(key, val);
    else {
        node *n = root, *p;
        int result;
        while (n) {
            p = n;
            result = (*compar)(key, n->key);
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
            p->right = new node(key, val);
        else
            p->left = new node(key, val);
    }
}

template<typename key_type, typename value_type>
/**
 * @brief binary_tree::find find elements in a tree
 * @param val value to search
 * @return element or nullptr
 */
value_type& binary_tree<key_type, value_type>::
find(const key_type& key) const {
    node* node = root;
    int result = (*compar)(key, root->get_key());
    while (node) {
        if (result > 0)
            node = node->right;
        else if (result < 0)
            node = node->left;
        else
            return node->get_val();
        result = (*compar)(key, node->get_key());
    }
    throw std::exception();
}

template <typename key_type, typename value_type>
/**
 * @brief binary_tree<key_type, value_type>::operator []
 */
value_type& binary_tree<key_type, value_type>::
operator[](const key_type& key) {
    try {
        return this->find(key);
    } catch (std::exception& e) {
        std::cerr << "ERROR in []" << std::endl;
    }
}

template<typename key_type, typename value_type>
/**
 * @brief binary_tree<value_type>::binary_tree standard constructor
 * @param cmp function to compare elements
 */
binary_tree<key_type, value_type>::
binary_tree(comparator cmp) {
    compar = cmp;
    root = nullptr;
}

//TODO список инициализации для конструктора
//template<typename key_type, typename value_type>
//binary_tree<value_type>::
///**
// * @brief binary_tree constructor with initialization list
// * @param init_list list to init the tree
// * @param cmp function to compare elements
// */
//binary_tree(std::initializer_list<value_type> init_list, comparator cmp) {
//    compar = cmp;
//    root = nullptr;

//    for (const value_type it: init_list)
//        this->insert(it);

//}

//TODO конструктор копии (разобраться с ключами)
//template<typename value_type>
//binary_tree<value_type>::
///**
// * @brief binary_tree copy constructor
// * @param copy_tree tree to copy
// */
//binary_tree(const binary_tree<value_type>& copy_tree) {

//    // Init root
//    root = nullptr;

//    // Function to compare elements
//    compar = copy_tree.compar;

//    // Vector with elemennts of old tree
//    std::vector<value_type>* values_to_copy = new std::vector<value_type>();

//    // Init this vector
//    copy_tree.symmetric_pass(
//        [](const value_type& val, void* values_to_copy) {((std::vector<value_type>*)values_to_copy)->push_back(val);},
//        (void*)values_to_copy);

//    // Insert elements from vector into tree
//    for (auto it: *values_to_copy)
//        this->insert(it);

//    delete values_to_copy;
//}

template<typename key_type, typename value_type>
/**
 * @brief binary_tree::is_empty check whether tree is empty
 * @return true if is empty
 */
bool binary_tree<key_type, value_type>::
is_empty() const {
    return (root == nullptr);
}

//TODO симметричный обход дерева (по ключу)
//template<typename value_type>
///**
// * @brief binary_tree<value_type>::_symmetric_pass symmetric pass of the tree
// * @param node element, from which pass starts
// * @param exec function that executes for every node
// * @param data data that will be passed into executor
// */
//void binary_tree<value_type>::
//_symmetric_pass(node *node, executor exec, void* data) const {

//    if (node) {
//        _symmetric_pass(node->left, exec, data);

//        (*exec)(*node, data);

//        _symmetric_pass(node->right, exec, data);
//    }
//}

template<typename key_type, typename value_type>
/**
 * @brief binary_tree<value_type>::symmetric_pass interface for _symmetric_pass
 * @param exec executor function
 * @param data data that will be passed into executor
 */
void binary_tree<key_type, value_type>::
symmetric_pass(executor exec, void* data) const {
    _symmetric_pass(root, exec, data);
}

template<typename key_type, typename value_type>
/**
 * @brief binary_tree::~binary_tree
 */
binary_tree<key_type, value_type>::
~binary_tree() {
    if (root != nullptr)
        delete root;
}

template<typename key_type, typename value_type>
void binary_tree<key_type, value_type>::
_beatiful_print(node* node, int level) const {
    if (node) {
        _beatiful_print(node->right, level+1);
        for (int i = 0; i < level; i++)
            std::cout << "     ";
        std::cout << node->get_val() << ":" << node->get_key() << std::endl;
        _beatiful_print(node->left, level+1);
    }
}

template<typename key_type, typename value_type>
void binary_tree<key_type, value_type>::
beautiful_print() const {
    _beatiful_print(root, 0);
}

#endif // BINARY_TREE

