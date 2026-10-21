//
// Created by 13402 on 2026/10/21.
//

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <vector>
#include "CleanupActivity.h"

class RedBlackTree{

private:
    struct Node{
        CleanupActivity activity;
        bool red = true;

        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
    };

    Node* root=nullptr;

    //these three are quite similar as the avl tree
    void balance(Node* node);
    void rotateLeft(Node* node);
    void rotateRight(Node* node);

    //for convenience, i decide to use reverseInorder to get the top n cleanupactivity
    //specifically, reverseInorder will return a vector that sorted the cleanupactivity
    //from largest total count to smallest, so that for the topcount function, we
    //only need to call this reverseInorder and get the vector, then slice that vector
    //it will be easier than the normal way that requires remove the right most node
    //because we don't have to rotate and recolor
    void reverseInorder(Node* node,int n,std::vector<CleanupActivity>& result);

    public:
        void insert(const CleanupActivity& activity);
        std::vector<CleanupActivity> topcount(int n);

};
#endif //REDBLACKTREE_H
