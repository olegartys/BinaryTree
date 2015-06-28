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
//inline void printer(tree_node<int>& node, void* data) {cout << node.get_val() << endl;}

bool is_valid(const string &s) noexcept(false);

int main()
{
    binary_tree<int, string> tree(comparator);

    cout << ">Enter decimals: " << endl;

    tree[17] = "Sighka";
    tree[18] = "Masha";

    binary_tree<int, string> tree1(comparator);
    tree1 = move(tree);
    tree1.beautiful_print();


    vector<binary_tree<int, string> > v;
    v.push_back(move(tree));
    tree.beautiful_print();
    tree1.beautiful_print();

//    tree = 17;
//    tree["adds"];

//    tree["Sighka"] = 17;

//    for (int i = 1; i < 10; i++) {
//        tree.insert(i, i);
//        tree.insert(-i, -i);
//    }

//    tree.find(0) = 7;

   // tree.beautiful_print();

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
//    tree.symmetric_pass(printer, nullptr);

//    // Example of using symmetric pass to find sum
//    int sum = 0;
//    tree.symmetric_pass([](tree_node<int>& node, void* sum) {
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

