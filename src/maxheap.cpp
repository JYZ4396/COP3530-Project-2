//
// Created by micha on 11/3/2026.
//

#include "maxheap.h"
using namespace std;

void MaxHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].totalCount <= heap[parent].totalCount) {
            break;
        }
        swap(heap[index], heap[parent]);
        index = parent;
    }
}

void MaxHeap::heapifyDown(int index) {
    int n = heap.size();
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < n && heap[left].totalCount > heap[largest].totalCount) {
            largest = left;
        }
        if (right < n && heap[right].totalCount > heap[largest].totalCount) {
            largest = right;
        }

        if (largest == index) {
            break;
        }

        swap(heap[index], heap[largest]);
        index = largest;
    }
}

void MaxHeap::insert(const CleanupActivity& activity) {
    heap.push_back(activity);
    heapifyUp(heap.size() - 1);
}

CleanupActivity MaxHeap::extractMax() {


    CleanupActivity top = heap.front();
    heap.front() = heap.back();
    heap.pop_back();

    if (!heap.empty()) {
        heapifyDown(0);
    }

    return top;
}

vector<CleanupActivity> MaxHeap::topcount(int n){
    MaxHeap copy = *this;
    vector<CleanupActivity> result;
    for (int i = 0; i < n && !copy.isEmpty(); ++i) {
        result.push_back(copy.extractMax());
    }
    return result;
}