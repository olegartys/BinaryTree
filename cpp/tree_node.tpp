#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "binary_tree.tpp"

template<typename key_type, typename value_type>
class binary_tree;

template<typename key_type, typename value_type>
/**
 * @brief Implementation of tree's node
 */
class tree_node {
private:
    key_type key;
    value_type val;

    tree_node<key_type, value_type>* left;
    tree_node<key_type, value_type>* right;

    bool _is_leaf;
    bool _is_marked;

    friend class binary_tree<key_type, value_type>;

public:
    // Constructors
    tree_node(const key_type& key, const value_type& val,
              tree_node* left = nullptr,
              tree_node* right = nullptr,
              const bool is_leaf = true,
              const bool is_marked = false) :
        key(key), val(val),
        left(left), right(right),
        _is_leaf(is_leaf), _is_marked(is_marked) {}
//    tree_node(const key_type& key, const value_type& val) :
//        key(key), val(val), left(nullptr), right(nullptr), _is_leaf(true) {}

//    tree_node(const key_type& key, const value_type& val, const bool is_marked) :
//        key(key), val(val), left(nullptr), right(nullptr), _is_leaf(true), _is_marked(is_marked) {}

//    tree_node(const tree_node& left, const tree_node& right, const value_type& val) :
//        key(key), val(val), left(left), right(right), _is_leaf(true) {}

    // Copy constructor
    tree_node(const tree_node<key_type, value_type>& cpnode) :
        key(cpnode.key), val(cpnode.val), left(cpnode.left), right(cpnode.right),
        _is_leaf(cpnode._is_leaf), _is_marked(cpnode._is_marked) {}

    // Move constructor
    tree_node(tree_node<key_type, value_type>&& mvnode) {
        key = std::move(mvnode.key);
        val = std::move(mvnode.val);
        left = std::move(mvnode.left);
        right = std::move(mvnode.right);
        _is_leaf = mvnode._is_leaf;
        _is_marked = mvnode._is_marked;

    }

    tree_node<key_type, value_type>& operator= (const tree_node<key_type, value_type>& cpnode) {
        key = cpnode.key;
        val = cpnode.val;

        left = cpnode.left;
        right = cpnode.right;

        _is_leaf = cpnode._is_leaf;
        _is_marked = cpnode._is_marked;
        return *this;
    }

    tree_node<key_type, value_type>& operator= (tree_node<key_type, value_type>&& mvnode) {
        key = std::move(mvnode.key);
        val = std::move(mvnode.val);

        left = std::move(mvnode.left);
        right = std::move(mvnode.right);

        _is_leaf = mvnode._is_leaf;
        _is_marked = mvnode._is_marked;
        return *this;
    }

    // Getters and setters
    bool is_leaf() const {return _is_leaf;}

    void mark() {_is_marked = true;}
    void unmark() {_is_marked = false;}
    bool is_marked() {return _is_marked;}

    tree_node<key_type, value_type>*& get_left() {return left;}
    tree_node<key_type, value_type>*& get_right() {return right;}

    value_type& get_val() {return this->val;}
    key_type get_key() const {return this->key;}

    // Destructor
    ~tree_node() {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }
};

#endif // TREE_NODE_H

