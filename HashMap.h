#include <unordered_map>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;
#ifndef HASHMAP_H
#define HASHMAP_H



class HashMap {
    private:
        unordered_map<string , vector<vector<string>>> map;
        vector<string> genres = {};
        //helper to check if word is valid
        bool validWord(string word);
    public:
        //returns a string vector with valid hashmaps
        vector<string> validGenres();
        //creates HashMap from existing txt file
        void insertHashMap(string filename);
        //Inserts word, and occurence information into hashmap
        void insertWord(string word, vector<string> value);
        //Gets the occurrences of that word in every genre (empty vect returned if doesnt exist)
        vector<vector<string>> getStats(string word);
        //Gets the occurences of the word in that specific genre (empty vect returned if doesnt exist)
        vector<string> getStatsFromGenre(string word, string genre);
        //Used to save hashmap state into txt file
        bool saveHashMap(string filename);

};



#endif //HASHMAP_H
