#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <iostream>

using namespace std;

class MaxHeap {
private:
    // Each pair is <word, frequency>
    priority_queue<pair<int, string>> heap;

    // Map to track word frequencies
    unordered_map<string, int> wordCount;

public:
    void insert(string word);
    pair<int, string> getMax(); // Get word with highest frequency
    vector<pair<int, string>> getAll(); // Get all words sorted by frequency
    void clear(); // Clears heap and map
};

#endif // MAXHEAP_H
