#include "MaxHeap.h"

void MaxHeap::insert(string word) {
    wordCount[word]++;
    heap.push({wordCount[word], word});
}

pair<int, string> MaxHeap::getMax() {
    while (!heap.empty()) {
        string word = heap.top().second;
        int freq = heap.top().first;

        if (wordCount[word] == freq) {
            return {freq, word};
        }
        heap.pop(); // stale value, skip
    }
    return {0, ""};
}

vector<pair<int, string>> MaxHeap::getAll() {
    priority_queue<pair<int, string>> copy = heap;
    vector<pair<int, string>> result;

    while (!copy.empty()) {
        string word = copy.top().second;
        int freq = copy.top().first;

        if (wordCount[word] == freq) {
            result.push_back({freq, word});
        }

        copy.pop();
    }

    return result;
}

void MaxHeap::clear() {
    while (!heap.empty()) heap.pop();
    wordCount.clear();
}
