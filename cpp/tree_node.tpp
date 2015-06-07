#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "binary_tree.tpp"

template<typename node_type>
class binary_tree;

template<typename node_type>
/**
 * @brief Implementation of tree's node
 */
class tree_node {
private:
    node_type val;
    tree_node<node_type>* left;
    tree_node<node_type>* right;

    bool _is_marked;
    bool _is_leaf;

    friend class binary_tree<node_type>;

public:
    tree_node(const node_type& val) :
        val(val), left(nullptr), right(nullptr), _is_leaf(true) {}

    tree_node(const node_type& val, const bool is_marked) :
        val(val), left(nullptr), right(nullptr), _is_leaf(true), _is_marked(is_marked) {}

    tree_node(const tree_node& left, const tree_node& right, const node_type& val) :
        val(val), left(left), right(right), _is_leaf(true) {}

    bool is_leaf() const {return _is_leaf;}

    void mark() {_is_marked = true;}
    void unmark() {_is_marked = false;}
    bool is_marked() {return _is_marked;}

    tree_node<node_type>*& get_left() {return left;}
    tree_node<node_type>*& get_right() {return right;}
    node_type get_val() const {return this->val;}

    ~tree_node() {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }
};

#endif // TREE_NODE_H

