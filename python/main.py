__author__ = 'olegartys'

from binary_tree import *
import sys

def fill_tree(tree):
    for i in range(1, 10):
        try:
            tree.insert(i, i)
            tree.insert(-i, -i)
        except KeyError as e:
            print(e)


def main():
    tree = binary_search_tree()

    # Enter elements while not eof
    print("key, value: ")
    for line in sys.stdin:
        node = line.split()
        try:
            tree.insert(node[0], node[1])
        except KeyError as e:
            print(e)
        print("key, value: ")

    tree.beatiful_print()

    return 0


if __name__ == '__main__':
    main()