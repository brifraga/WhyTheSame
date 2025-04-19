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

class MaxHeap {
private:
    //Parallel stirng vector that lists the genre for the heap index
    vector<string> heapGenre;
    // A vector that contains MaxHeaps with pair is <word, frequency>
    vector<priority_queue<pair<int, string>>> heap;

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
};

#endif // MAXHEAP_H
