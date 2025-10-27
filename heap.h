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
        // call upheap()
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        cout << "start: pos is " << pos << endl;
        // while the parent exists
        while (pos >= 0) { // pos is updated to the latest parent index

            // update all values at beginning so parent and child will keep moving up
            int& parent = weightArr[(pos - 1) / 2];
            int parentIndex = (pos - 1) / 2;
            int& child = weightArr[pos];

            // if child is greater than parent
            if (child > parent) {
                // they are references, so the value saves
                swap(weightArr[pos], weightArr[(pos - 1) / 2]);

                // update child index
                pos = parentIndex;
            }
            else {
                cout << "no more parent indexes" << endl;
                break;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child

    }
};

#endif