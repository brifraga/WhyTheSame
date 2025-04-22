#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class MaxHeapStruct {
    private:
        vector<pair<int, string>> heap;
        //Maintains heap during insertion
        void heapifyUp(int i) {
            int parent = (i - 1) / 2;
            if(i > 0 && heap[i].first > heap[parent].first) {
                swap(heap[i], heap[parent]);
                heapifyUp(parent);
            }
        }
        //Maintains heap during deletion
        void heapifyDown(int i) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;
            if(left < heap.size() && heap[left].first > heap[largest].first) {
                largest = left;
            }
            if (right < heap.size() && heap[right].first > heap[largest].first) {
                largest = right;
            }
            if(largest != i) {
                swap(heap[i], heap[largest]);
                heapifyDown(largest);
            }
        }

    public:
        //Adds element to heap
        void push(pair<int, string> p);
        //Removes element from top of the heap
        pair<int, string> pop();
        //Get Maximum Element
        pair<int, string> top();
        //Check if empty
        bool empty();
        //Get Size
        int size();

};

class MaxHeap {
private:
    //Parallel stirng vector that lists the genre for the heap index
    vector<string> heapGenre;
    // A vector that contains MaxHeaps with pair is <word, frequency>
    vector<MaxHeapStruct> heap;

public:
    //Function to load max heap from file (uses the same file as hashmap load)
    void loadFromFile(string filename);
    //Simple insert debugging and helper function, takes in word genre and count.
    void insert(string word, string genre, int count);
    //Gets word with highest frequency within genre. Optional string vector with words to filter.
    pair<int, string> getMax(string genre, vector<string> filter = {});
    //Gets all wordd sorted by frequency within a genre, has optional string vector with words to filter
    vector<pair<int, string>> getAll(string genre, vector<string> filter = {}); // Get all words sorted by frequency
    //void clear(); // Clears heap and map
    vector<pair<string, int>> getTopWordsByGenre(string genre, int topN, vector<string> filter = {});


};

#endif // MAXHEAP_H

