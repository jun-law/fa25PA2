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
/*
 * Construct an encoding tree with each parent having the sum of minimum two weights
 * Uses minheap to choose the minimum weights each time
 * nextFree keeps track of next available index of leftArr[], rightArr[] and weightArr[]
 * returns the last index of the encoding tree
 */
int buildEncodingTree(int nextFree) {
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

    // return index of last remaining node
    int lastIndex = nextFree - 1;
    return lastIndex;
}

// Step 4: Use an STL stack to generate codes
/*
  * Use a stack to traverse the encoding tree, starting with the current node, left child, and right child,
    repeating until leaf node is reached
  * Adds 0 when going left, and 1 when going right to assign codes
  * root - the index of the first node
  * codes[] - holds the encoding for each leaf node
  */
void generateCodes(int root, string codes[]) {

    // push root
    stack<pair<int, string>> s;

    s.push({root, ""});

    // while it is not a leaf node
    while (!s.empty()) {

        // look up root's left and right children
        pair<int,string> top = s.top();
        s.pop();
        int leftChild = leftArr[top.first]; // first is the index
        int rightChild = rightArr[top.first];

        // grab the code
        string currentCode = top.second;

        // if it is a leaf node, assign a valid code
        if (rightChild == -1 && leftChild == -1) {
            codes[charArr[top.first] - 'a'] = top.second;
            continue;
        }

        // push right child
        if (rightChild != -1) {
            s.push({rightChild, currentCode + "1"}); // go right, add 1
        }
        // push left child
        if (leftChild != -1) {
            s.push({leftChild, currentCode + "0"}); // go left, add 0
        }
    }
}

// Step 5: Print table and encoded message
/*
 * Prints each letter with its respective code
 * Reads input file and prints encoded message based on each character in order
 * filename - the name of the input file
 * codes[] - holds the encoding for each leaf node
 */
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";

    // print each letter with correct encoding
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    // read characters from input file
    string input = "";
    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
            input += ch;
    }
    cout << endl;

    file.close();
}