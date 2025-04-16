#include "dataParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

//cleaning the lyrics by: lowercasing everything, removing punctuation, splitting into words(tokens)
vector<string> cleanAndTokenize(const string& lyrics) {
    string clean;
    for (char ch : lyrics) {
        if (isalpha(ch) || ch == ' ') {
            clean += tolower(ch);
        }
    }

    stringstream ss(clean);
    string word;
    vector<string> words;

    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}
//opens the CSV file, reads line by line, extracts genre + lyrics, cleans the lyrics, returns a vector of Song objects
vector<Song> parseDataset(const string& dataset) {
    cout << "Attempting to read file: " << dataset << endl; // Debug line

    ifstream file(dataset);
    vector<Song> songs;

    if (!file.is_open()) {
        cout << "Error: Could not open file " << dataset << endl;
        return songs;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string genre, lyrics;

        getline(ss, genre, ',');

        for (int i = 0; i < 5; ++i) {
            string temp;
            getline(ss, temp, ',');
        }

        getline(ss, lyrics);

        vector<string> words = cleanAndTokenize(lyrics);
        songs.push_back({genre, words});

        //debug print
        cout << "Genre: " << genre << ", First few words: ";
        for (int i = 0; i < min(5, (int)words.size()); ++i) {
            cout << words[i] << " ";
        }
        cout << endl; 
    }

    file.close();
    return songs;
}