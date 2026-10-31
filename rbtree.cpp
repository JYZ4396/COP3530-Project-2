#include "redblacktree.h"
#include <vector>

// switches a node's color
void RedBlackTree::colorSwitch(Node* node) {
    if (node->red) node->red = false;
    else node->red = true;
}

// determines the configuration
void RedBlackTree::configuration(Node*& node, Node*& parent, Node*& grandparent, Node*& uncle, bool& first_right, bool& then_left) {

    // gives appropriate names
    parent = node->parent;
    grandparent = parent->parent;

    // finds where uncle is and whether it's red or black
    // for grandparent being left (less) of parent
    if (parent == grandparent->left){
        first_right = false;
        uncle = grandparent->right;
    } // for grandparent being right (greater) of parent
    else if (parent == grandparent->right){
        first_right = true;
        uncle = grandparent->left;
    }


    // for parent being left of child
    if (node == parent->right) {
        then_left = false;
    }
    // for parent being right of child
    else if (node == parent->left) {
        then_left = true;
    }


}

// rotations (family names don't necessarily match with the other functions because parent gets received as node)
void RedBlackTree::rotateLeft(Node* node) {

    Node* parent = node->parent;
    Node* grandparent = parent->parent;

    node->parent = grandparent;
    parent->parent = node;

    parent->right = node->left;
    if (node->left != nullptr) {
        node->left->parent = parent;
    }
    node->left = parent;

    if (grandparent == nullptr) {
        root = node;
        return;
    }

    parent == grandparent->left ? grandparent->left = node : grandparent->right = node;
}

void RedBlackTree::rotateRight(Node* node) {

    Node *parent = node->parent;
    Node *grandparent = parent->parent;

    node->parent = grandparent;
    parent->parent = node;

    parent->left = node->right;
    if (node->right != nullptr) {
        node->right->parent = parent;
    }
    node->right = parent;

    if (grandparent == nullptr) {
        root = node;
        return;
    }

    parent == grandparent->left ? grandparent->left = node : grandparent->right = node;
}


void RedBlackTree::blackUncle(Node*& node, Node*& parent, Node*& grandparent, Node*& uncle, bool& first_right, bool& then_left) {

    // for right right case
    if (first_right && !then_left) {
        rotateLeft(parent);
        colorSwitch(parent);
    } // for left left case
    else if (!first_right && then_left) {
        rotateRight(parent);
        colorSwitch(parent);
    } // for right left case
    else if (first_right && then_left) {
        rotateRight(node);
        rotateLeft(node);
        colorSwitch(node);
    } // for left right case
    else if (!first_right && !then_left) {
        rotateLeft(node);
        rotateRight(node);
        colorSwitch(node);
    }

    colorSwitch(grandparent);
}

void RedBlackTree::insert(const CleanupActivity& activity){

    // creates node of CleanupActivity
    Node *node = new Node;
    node->activity = activity;

    // inserts node in empty tree
    if (root == nullptr) {
        root = node;
        root->red = false;
        return;
    }

    // inserts node using Binary Search
    Node *traverse = root;
    while (true) {

        // for an insert node value greater than current node's value
        if (node->activity.totalCount > traverse->activity.totalCount) {
            if (traverse->right == nullptr) {
                traverse->right = node;
                node->parent = traverse;
                balance(node);
                return;
            }
            traverse = traverse->right;
        } // for an insert node value less than current node's value
        else if (node->activity.totalCount < traverse->activity.totalCount) {
            if (traverse->left == nullptr) {
                traverse->left = node;
                node->parent = traverse;
                balance(node);
                return;
            }
            traverse = traverse->left;
        } // for a node with cleanup activity toalCount that's already in the tree
        else {
            delete node;
            return;
        }
    }
}



void RedBlackTree::balance(Node* node) {

    // root node must be black
    if (node == root) {
        node->red = false;
        return;
    }

    // checks for consecutive red nodes and ensures grandparent must exist
    if (!node->parent->red) return;

    Node *parent, *grandparent, *uncle;
    bool first_right, then_left;

    configuration(node, parent, grandparent, uncle, first_right, then_left);

    // for black uncle
    if (uncle == nullptr || uncle->red == false) {

        blackUncle(node, parent, grandparent, uncle, first_right, then_left);

    } // for red uncle
    else {
        colorSwitch(parent);
        colorSwitch(grandparent);
        colorSwitch(uncle);

        balance(grandparent);

        return;
    }

    // root node must be black
    root->red = false;
}

void RedBlackTree::reverseInorder(Node* node, const int n) {
    if (this->topcount.size() == n || node == nullptr) return;

    reverseInorder(node->right, n);

    if (this->topcount.size() == n) return;
    this->topcount.push_back(*node);

    reverseInorder(node->left, n);
}