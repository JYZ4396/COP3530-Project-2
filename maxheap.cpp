//
// Created by micha on 11/3/2026.
//

#include "maxheap.h"
using namespace std;

void MaxHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].getTotalCount() <= heap[parent].getTotalCount()) {
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

        if (left < n && heap[left].getTotalCount() <= heap[largest].getTotalCount()) {
            largest = left;
        }
        if (right < n && heap[right].getTotalCount() <= heap[largest].getTotalCount()) {
            largest = right;
        }

        if (largest == index) {
            break;
        }

        swap(heap[index], heap[largest]);
        index = largest;
    }
}