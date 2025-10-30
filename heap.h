#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64]; // holds values of node indexes
    int size;
    // weightArr[] holds the node weights (which ones are lighter or heavier)
    // use weightArr[data[i]] to grab weight of index

    MinHeap() { // constructor
        size = 0;
    }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        // index is the key, counts frequency
        data[size] = idx;
        // restore order
        upheap(size, weightArr);
        size++;
        // read priorities in weightArr
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // empty list condition
        if (size == 0) {
            cout << "Nothing to pop" << endl;
            return -1;
        }
        else {
            // save last element to pop
            int pop = data[size - 1];
            cout << "Selected element to pop is: " << pop << endl;
            // replace first element
            data[0] = pop;
            size--;
            // restore order, read from weightArr
            downheap(0, weightArr);
            // update size
            cout << "Popped " << pop << endl;
            return pop;
        }
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        // while the parent exists
        while (pos > 0) {
            // update all values
            int parentIndex = (pos - 1) / 2; // ultimately relies on pos
            int parent = weightArr[data[parentIndex]];
            int child = weightArr[data[pos]];

            // if child is greater than parent
            if (child < parent) {
                cout << "comparing " << child << " and " << parent << endl;
                // compare weight values and swap data values if necessary, both at pos
                swap(data[pos], data[parentIndex]);
                cout << "swapping " << data[pos] << " and " << data[parentIndex] << endl;
                // update child index
                pos = parentIndex;
            }
            else {
                break;
            }
        }
    }

    // helper to get the smaller child
    int findMinChildIndex (int pos, int weightArr[]) {

        int leftChildIndex = (pos * 2) + 1; // ultimately relies on pos
        int rightChildIndex = (pos * 1) + 2;

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
        // TODO: swap parent downward while larger than any child
        // pos = parent index
        // loop until end of array
        while (pos < size) {
            // index = index of min weight
            int index = findMinChildIndex(pos, weightArr);
            cout << "index is: " << index << endl;
            // cout << "min child is: " << weightArr[data[index]] << endl;
            // if out of bounds
            if (index != -1) {
                // swap data values instead of weight values
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