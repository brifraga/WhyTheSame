//
// Created by tomas on 4/16/2025.
//

#include "HashMap.h"


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
                    //insertWord(key, values);
                    data.push_back(values);
                }
                map[key] = data;
            }
        }
        file.close();
    }
}

void HashMap::insertWord(string word, vector<string> value) {
    vector<vector<string>> values = getStats(word);
    values.push_back(value);
    map[word] = values;
    for(int i = 0; i < genres.size(); i++) {
        if(genres[i] == value[0]) {
          return;
        }
    }
    genres.push_back(value[0]);
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
            if(stats[i][1] == genre) {
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
            cout << "here" << endl;
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
