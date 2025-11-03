//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object. DONE
    // 2. Push all leaf node indices into the heap. DONE
    // 3. While the heap size is greater than 1: DONE
    //    - Pop two smallest nodes DONE
    //    - Create a new parent node with combined weight DONE
    //    - Set left/right pointers DONE
    //    - Push new parent index back into the heap DONE
    // 4. Return the index of the last remaining node (root) DONE

    // push all items onto heap
    MinHeap heap;
    for (int i = 0; i < nextFree; i++) {
        heap.push(i, weightArr);
    }

    while (heap.size > 1) {
        // pop smallest nodes indices (from data)
        int left = heap.pop(weightArr);
        int right = heap.pop(weightArr);

        // add indexes of children to left and right
        leftArr[nextFree] = left;
        rightArr[nextFree] = right;

        // get sum for weightArr
        int leftValue = weightArr[left];
        int rightValue = weightArr[right];
        int sum = leftValue + rightValue;

        // add entry to weightArr
        weightArr[nextFree] = sum;

        // push new index into heap
        heap.push(nextFree, weightArr);
        nextFree++;
    }
    // only 5 elements in array rn
    for (int i = 0; i < 5; i++) {
        cout << weightArr[i] << " ";
    }
    cout << endl;

    // return index of last remaining node
    int lastIndex = nextFree - 1;
    // cout << "return " << lastIndex << endl;
    return lastIndex;
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.

    // push and pop the root
    stack<pair<int, string>> s;
    cout << "pushing root index " << root << ", this is value " << weightArr[root] << " in weightArr" << endl;
    s.push({root, ""});

    // while it is not a leaf node

    while (!s.empty()) {

        // look up root's left and right children
        pair<int,string> top = s.top();
        s.pop();
        int leftChild = leftArr[top.first];
        int rightChild = rightArr[top.first];

        string currentCode = top.second;

        if (rightChild == -1 && leftChild == -1) {
            //cout << "HIT LEAF NODE" << endl;
            // add code to next empty slot in codes array
           // cout << top.second << endl;
            int leafIndex = top.first;
            codes[leafIndex] = top.second;
            continue;
        }

        // push right child
        if (rightChild != -1) {
            s.push({rightChild, currentCode + "1"}); // go right, add 1
        }
        if (leftChild != -1) {
            s.push({leftChild, currentCode + "0"}); // go left, add 0
        }
    }

}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";

    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << charArr[i] << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";
    // freq[i] at codes[i]
    // for every element in codes[], for every frequency, print out the encoding this many times
    for (int i = 0; i <= sizeof(codes) / 4; i++) {
        for (int j = 0; j < sizeof(codes) / 4; j++) {
            cout << codes[i] << " ";
        }
    }
    cout << endl;

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}