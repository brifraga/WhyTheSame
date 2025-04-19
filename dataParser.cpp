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

bool endsWithRealQuote(const string& line) {
    int len = line.size();
    if (len == 0) return false;
    // check if ends in " or """
    if (line[len - 1] == '"') {
        if (len >= 3 && line.substr(len - 3) == "\"\"\"") {
            return true;
        }
        if (len >= 2 && line[len - 2] != '"') {
            return true;
        }
    }
    return false;
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
    int linenumber = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string genre, views, lyrics;

        getline(ss, genre, ',');
        //skips the views unless we want to use them later
        getline(ss, views, ',');

        //removed the skipping of other columns
        getline(ss, lyrics);
        //the lyrics can be on multiple lines, will continue parsing as long as line doesnt end in double quotes or if it ends in single or triple quotes
        while (getline(file, line) && !(endsWithRealQuote(line))) {
            lyrics += " " + line;
        }
        lyrics += " " + line;

        vector<string> words = cleanAndTokenize(lyrics);
        songs.push_back({genre, words});

        //debug print
        linenumber++;
        cout << "Song: " << linenumber << ", Genre: " << genre << ", First few words: ";
        for (int i = 0; i < min(5, (int)words.size()); ++i) {
            cout << words[i] << " ";
        }
        cout << endl;
    }

    file.close();
    return songs;
}