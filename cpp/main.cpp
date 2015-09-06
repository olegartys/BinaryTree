/*
 * Example of using template tree with decimals
 */

#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <cstring>
#include <vector>

#include "binary_tree.tpp"

using namespace std;

inline int comparator(const int& a, const int& b) {return a - b;}
inline int comparator(const string& a, const string& b) {return strcmp(a.c_str(), b.c_str());}
inline void printer(typename binary_tree<int, int>::node& node, void* data) {cout << node.val << endl;}

bool is_valid(const string &s) noexcept(false);

template <typename K, typename V>
void f(binary_tree<K, V> t) {
    cout << "\n=================\n";
    t.beautiful_print();
    cout << "\n=================\n";
};

int main()
{
    binary_tree<int, int> tree([](const int& a, const int& b) -> int {return a-b;});
    binary_tree<int, int> tree1([](const int& a, const int& b) -> int {return a-b;});

    for (int i = 1; i <= 5; ++i) {
        tree[i] = i;
        tree[-i] = -i;
    }

    int a[] = {1, 2, 3}

    for (int i = 10; i <= 20; ++i) {
        tree1[i] = i;
        tree1[-i] = -i;
    }

    f(std::move(tree));
    tree.beautiful_print();



//    // Input data
//    string line;
//    while (getline(cin, line)) {
//        try {
//            if (is_valid(line))
//                tree.insert(stoi(line));
//        }
//        catch (std::exception& e) {
//            cerr << "Can't transalate input into a decimal!" << endl;
//        }
//    }

//    //Print the tree
//    cout << ">Input tree: " << endl;
//    tree.beautiful_print();

//    cout << endl;

//    // Example of using symmetric pass without data
//    tree.symmetric_traversal(printer, nullptr);

//    // Example of using symmetric pass to find sum
//    int sum = 0;
//    tree.symmetric_traversal([](tree_node<int>& node, void* sum) {
//        *(int*)sum += node.get_val();
//    }, (void*)&sum);

    return 0;
}

/**
 * @brief is_valid decide whether string include only decimal
 * @param s string to check
 * @return true in case of success
 */
bool is_valid(const string& s) noexcept(false) {
    for (char c: s)
        if (!isdigit(c) && c != '-') {
            throw std::exception();
        }
    return true;
}

