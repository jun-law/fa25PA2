#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <string>
#include <stack> // for traversal only
#include <fstream> // file reading
using namespace std;

struct MinHeap {
    int data[64]; // array of size 64
    int size;

    MinHeap() { // constructor
        size = 0;
    }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        // how to check for NEXT available element??
        // size i
        weightArr[size] = idx; // index is the value
        // restore
        size++;
        upheap(size-1, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index

    }

    // **** check if the parent < child too, min heap condition
    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent

        int parent = weightArr[(pos - 1) / 2];
        int child = weightArr[pos];

        // while the parent exists
        while (pos > 0) { // pos is updated to the latest parent index
            // update all values at beginning so parent and child will keep moving up
            int parentIndex = (pos - 1) / 2;
            parent = weightArr[(pos - 1) / 2];
            child = weightArr[pos];

            // before performing
            // if child is greater than parent

            if (child < parent) { // fixed condition
                // they are references, so the value saves
                swap(weightArr[pos], weightArr[(pos - 1) / 2]);
                // update child index
                pos = parentIndex;
                if ((pos * 2) + 2 >= size) {
                    continue; // disregards everything below it and continues with while loop
                }
                int leftChild = weightArr[(pos * 2) + 1];
                int rightChild = weightArr[(pos * 2) + 2];
                if (leftChild >= rightChild) {
                    swap( weightArr[(pos * 2) + 1], weightArr[(pos * 2) + 2]);
                }

            }
            else {
                break;

            }
        }
    }

    int findMinChildIndex (int pos, int weightArr[]) {

        int leftChildIndex = (pos * 2) + 1;
        int rightChildIndex = (pos * 1) + 2;

        int leftChild = weightArr[leftChildIndex];
        int rightChild = weightArr[rightChildIndex];
        int parent = weightArr[pos];

        int length = sizeof(weightArr) / 4;

        if (leftChildIndex <= length && rightChildIndex <= length) {
            if (leftChild <= rightChild) {
                return leftChildIndex;
            }
            else {
                return rightChildIndex;
            }
        }
        return -1;
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        // pos is the parent index
        cout << "start: pos is " << pos << endl;

        // loop until end of array
        while (pos <= (sizeof(weightArr) / 4)) {
            int index = findMinChildIndex(pos, weightArr);
            if (index != -1) {
                swap(weightArr[index], weightArr[pos]);
                pos = index;
            }
            else {
                break;
            }
        }
    }
};

#endif