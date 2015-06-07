__author__ = 'olegartys'

class binary_node:
    """
    Implementation of binary tree node
    """
    def __init__(self, key, val, left=None, right=None, parent=None):
        self._key = key
        self._val = val
        self.left = left
        self.right = right
        self._parent = parent

    def get_left_child(self):
        return self.left

    def get_right_child(self):
        return self.right

    def get_key(self):
        return self._key

    def get_val(self):
        return self._val