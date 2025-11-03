#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64]; // holds values of node indices
    int size;

    MinHeap() {
        size = 0;
    }

    void push(int idx, int weightArr[]) {

        // index is the key, counts frequency
        data[size] = idx;
        // restore order
        upheap(size, weightArr);
        size++;
    }

    int pop(int weightArr[]) {

        // empty list condition
        if (size == 0) {
            cout << "Nothing to pop" << endl;
            return -1;
        }
        else {
            // save index with smallest weight
            int pop = data[0];
            // replace root with last element
            data[0] = data[size - 1];
            size--;
            // restore order of first element (now largest), read from weightArr
            downheap(0, weightArr);
            // update size
            return pop;
        }
    }

    void upheap(int pos, int weightArr[]) {

        // while the parent exists
        while (pos > 0) {
            // update all values
            int parentIndex = (pos - 1) / 2; // ultimately relies on pos
            int parent = weightArr[data[parentIndex]];
            int child = weightArr[data[pos]];

            // if child is greater than parent
            if (child < parent) {
                // compare weight values and swap data values if necessary, both at pos
                swap(data[pos], data[parentIndex]);
                // update child index
                pos = parentIndex;
            }
            else {
                break;
            }
        }
    }

    // helper to find the smaller child
    int findMinChildIndex (int pos, int weightArr[]) {

        int leftChildIndex = (pos * 2) + 1;
        int rightChildIndex = (pos * 2) + 2;

        // check bounds for children
        if (leftChildIndex < size && rightChildIndex < size) {

            int leftChild = weightArr[data[leftChildIndex]];
            int rightChild = weightArr[data[rightChildIndex]];

            // if left child is smaller
            if (leftChild <= rightChild) {
                return leftChildIndex;
            }
            // if right child is smaller
            else {
                return rightChildIndex;
            }
        }

        // if out of bounds
        return -1;
    }

    void downheap(int pos, int weightArr[]) {
        // pos = parent index
        while (pos < size) {
            // index = index of min weight
            int index = findMinChildIndex(pos, weightArr);
            // if children are not out of bounds
            if (index != -1) {
                // swap node index values (not weights)
                swap(data[index], data[pos]);
                pos = index;
            }
            else {
                break;
            }
        }
    }
};

#endif