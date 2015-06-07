__author__ = 'olegartys'

from binary_node import *

class binary_search_tree:
    """
    Binary search tree implementation
    """

    def __init__(self):
        self._root = None
        self._size = 0

    def __len__(self):
        return self._size

    def __iter__(self):
        return self._root.__iter__()

    def insert(self, key, value):
        """
        :param key: Key for the new element
        :param value: Value of the new element
        :return:
        """
        if self._root == None:
            self._root = binary_node(key, value)
        else:
            if not self.__contains__(key):
                self._insert(key, value, self._root)
            else:
                raise KeyError("Key is already in the tree!")
        self._size += 1


    def _insert(self, key, value, cur_node):
        """
        Component function for function insert
        :param key: Key of the node
        :param value: Value of the node
        :param cur_node: Current node of the recursive pass
        :return:
        """
        if key < cur_node.get_key():

            # Dive into the left tree
            if cur_node.left != None:
                self._insert(key, value, cur_node.left)

            # Create node on a left tree
            else:
                cur_node.left = binary_node(key, value, parent=cur_node)

        else:
             # Dive into the right tree
             if cur_node.right != None:
                self._insert(key, value, cur_node.right)

             # Create node on a right tree
             else:
                cur_node.right = binary_node(key, value, parent=cur_node)


    def __setitem__(self, key, value):
        """
        Function to override operator[] setter
        :param key: Ket for a new element
        :param value: Value of the new element
        :return:
        """
        self.insert(key, value)


    def get(self, key):
        """
        Get element by key
        :param key: key to search
        :return: element by this key
        """
        if self._root:
            res = self._get(key, self._root)
            if res:
                return res.get_val()
            else:
                return None
        else:
            return None


    def _get(self, key, cur_node):
        """
        Component function to function get
        :param key:
        :param cur_node:
        :return:
        """
        if not cur_node:
            return None
        elif cur_node.get_key() == key:
            return cur_node
        elif key < cur_node.get_key():
            return self._get(key, cur_node.left)
        elif key > cur_node.get_key():
            return self._get(key, cur_node.right)


    def __getitem__(self, key):
        """
        Function to override operator[] getter
        :param key:
        :return:
        """
        return self.get(key)


    def beatiful_print(self):
        """
        Beatiful print of the tree
        :return:
        """
        self._beatiful_print(self._root, 0)


    def _beatiful_print(self, cur_node, level):
        """
        Component function for beatiful print
        :param cur_node:
        :param level:
        :return:
        """
        if cur_node:
            self._beatiful_print(cur_node.right, level+1)
            for i in range(level):
                print("    ", end="")
            print(cur_node.get_val())
            self._beatiful_print(cur_node.left, level+1)


    def __contains__(self, key):
        """
        Check whether tree contains element
        :param key: Key to search
        :return:
        """
        if self._get(key, self._root):
            return True
        else:
            return False

