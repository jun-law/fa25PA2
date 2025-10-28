#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64]; // array of size 64
    int size;

    MinHeap() { // constructor
        size = 0;
    }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        weightArr[size] = idx; // index is the key, counts frequency
        // restore
        size++;
        upheap(size-1, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        if (size == 0) {
            cout << "Nothing to pop" << endl;
            return -1;
        }
        else {
            // size - 1 is the last spot
            int pop = weightArr[size - 1];
            cout << "Selected element to pop is: " << pop << endl;
            weightArr[0] = pop;
            downheap(size-1, weightArr);
            size--; // last element gets cut off
            cout << "Popped " << pop << endl;
            downheap(size-1, weightArr);
            return pop;
        }
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
                } // do NOT sort by weight, but rather the data[]
                // compare both at the same indexes


            }
            else {
                break;

            } // size works with upheap
        }
    }

    int findMinChildIndex (int pos, int weightArr[]) {

        int leftChildIndex = (pos * 2) + 1;
        int rightChildIndex = (pos * 1) + 2;

        int leftChild = weightArr[leftChildIndex];
        int rightChild = weightArr[rightChildIndex];
        int parent = weightArr[pos];

        // int length = sizeof(weightArr) / 4;
        if (leftChildIndex < size && rightChildIndex < size) {

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
        // cout << "start: pos is " << pos << endl;

        // loop until end of array
        while (pos <= size) {
            int index = findMinChildIndex(pos, weightArr);
            cout << "index is: " << index << endl;
            cout << "min child is: " << weightArr[index] << endl;
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