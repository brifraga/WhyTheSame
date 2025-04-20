//
// Created by tomas on 4/16/2025.
//

#include "HashMap.h"

#include <bits/locale_facets_nonio.h>


bool HashMap::validWord(string word) {
    try {
        map.at(word);
    } catch (...) {
        return false;
    }
    return true;
}

vector<string> HashMap::validGenres() {
    return genres;
}

void HashMap::insertHashMap(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while(getline(file, line)) {
            string key;
            vector<vector<string>> data;
            istringstream iss(line);
            if(getline(iss, key, ',')) {
                bool status = true;
                while(status) {
                    vector<string> values;
                    for(int i = 0; i < 2; i++) {
                        string value;
                        if(getline(iss, value, ',')) {
                            values.push_back(value);
                        } else {
                            status = false;
                            break;
                        }
                    }
                    if(status) {
                        insertWord(key, values);
                    }

                    //data.push_back(values);
                }
                //map[key] = data;
            }
        }
        file.close();
    }
}

void HashMap::insertWord(string word, vector<string> value) {
    vector<vector<string>> values = getStats(word);
    bool found = true;
    for(int i = 0; i < values.size(); i++) {
        if(values[i] == value) {
            return;
        } else if (values[i][0] == value[0]) {
            values[i] = value;
            found = false;
            break;
        }
    }
    if (found) {
        values.push_back(value);
    }
    map[word] = values;
    if(!genres.empty()) {
        for(int i = 0; i < genres.size(); i++) {
            if(genres[i] == value[0]) {
                return;
            }
        }
    }
    genres.push_back(value[0]);
}

void HashMap::insertWordOccurrence(string word, string genre) {
    vector<vector<string>> values = getStats(word);
    bool found = false;
    for(int i = 0; i < values.size(); i++) {
        if(values[i][0] == genre) {
            values[i][1] = to_string(stoi(values[i][1]) + 1);
            found = true;
            break;
        }
    }
    if(!found) {
        vector<string> newVal;
        newVal = {genre, "1"};
        values.push_back(newVal);
    }
    map[word] = values;
    if(!genres.empty()) {
        for(int i = 0; i < genres.size(); i++) {
            if(genres[i] == genre) {
                return;
            }
        }
    }
    genres.push_back(genre);
}


vector<vector<string>> HashMap::getStats(string word) {
    if(validWord(word)) {
        vector<vector<string>> stats = map.at(word);
        return stats;
    }
    return vector<vector<string>>();
}

vector<string> HashMap::getStatsFromGenre(string word, string genre) {
    if(validWord(word)) {
        vector<vector<string>> stats = map.at(word);
        for (int i = 0; i < stats.size(); i++) {
            if(stats[i][0] == genre) {
                return stats[i];
            }
        }
    }
    return vector<string>();
}

bool HashMap::saveHashMap(string filename) {
    ofstream file(filename);

    if (file.is_open()) {
        // Write key-value pairs
        for (const auto& pair : map) {
            file << pair.first;
            for (int i = 0; i < pair.second.size(); i++) {
                if (pair.second[i].size() == 2) {
                    file << "," << pair.second[i][0] << "," << pair.second[i][1];
                } else {
                    //return false;
                }
            }
            file << endl;

        }
        file.close();
        return true;
    } else {
        return false;
    }
}

int HashMap::getWordGenreCount(string word, string genre) {
    vector<string> stats = getStatsFromGenre(word, genre);
    if (stats.size() >= 2) {
        try {
            return stoi(stats[1]);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

