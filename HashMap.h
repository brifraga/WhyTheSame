#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <list>
#include <utility>

using namespace std;
#ifndef HASHMAP_H
#define HASHMAP_H
class HashStruct {
    private:
        int BucketSize = 10;
        vector<list<pair<string, vector<pair<string, int>>>>> table;
        int numElements = 0;
        int Hash(string key) {
            int hash = 0;
            for (char c : key) {
                hash = (hash*31 + c) % BucketSize;
            }
            return hash;
        }
    public:
        HashStruct() : table(BucketSize) {}
        //inserts into hashtable
        void insert(string key, vector<pair<string, int>> value);
        //Allows access through [] operator
        vector<pair<string, int>> operator[](string key);
        //Checks if word is in hashmap
        vector<pair<string, int>> at(const string& key);
        //Allows for simple iteration through hashmap
        auto begin() {
            return table.begin();
        }
        auto end() {
            return table.end();
        }
        //Used for rehashing table to avoid collisions
        void rehash();
};

class HashMap {
    private:
        HashStruct map;
        vector<string> genres;
        //helper to check if word is valid (tested)
        bool validWord(string word);
    public:
        //returns a string vector with valid hashmaps (tested)
        vector<string> validGenres();
        //creates HashMap from existing txt file (tested)
        void insertHashMap(string filename);
        //Inserts word, and occurence information into hashmap (tested)
        void insertWord(string word, pair<string,int> value);
        //Inserts one occurrence of the word
        void insertWordOccurrence(string word, string genre);
        //Gets the occurrences of that word in every genre (empty vect returned if doesnt exist) (tested)
        vector<pair<string,int>> getStats(string word);
        //Gets the occurences of the word in that specific genre (empty vect returned if doesnt exist) (tested)
        pair<string,int> getStatsFromGenre(string word, string genre);
        //Used to save hashmap state into txt file (tested)
        bool saveHashMap(string filename);


};



#endif //HASHMAP_H
