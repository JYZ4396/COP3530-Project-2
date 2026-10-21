//
// Created by 13402 on 2026/10/21.
//

#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include "CleanupActivity.h"

class MaxHeap{

    private:
        std::vector<CleanupActivity> heap;

        //if my understanding is correct
        //after insert we need to call heapifyup
        //after extract we need to call heapifydown
        void heapifyUp(int index);
        void heapifyDown(int index);

    public:


        void insert(const CleanupActivity& activity);

        //My idea is set this extractmax function
        //after calling it, it will return the top node
        //then it will delete the top node, and heapifydown
        CleanupActivity extractMax();
        //this topcount function will call extractMax n times and return
        //a vector of cleanupactivity which have largest total count
        std::vector<CleanupActivity> topcount(int n);
};







#endif //MAXHEAP_H
