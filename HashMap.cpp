
#include "HashMap.h"

#include <bits/locale_facets_nonio.h>

//Hash Map Core Functions
void HashStruct::insert(string key, vector<pair<string, int>> value) {
    int hashIndex = Hash(key) % table.size();
    for (auto& valInList : table[hashIndex]) {
        if (valInList.first == key) {
            valInList.second = value;
            //cout << "word: " << key << " genre: " << value[value.size()-1].first << " value: " << value[value.size()-1].second << endl;
            return;
        }
    }

    table[hashIndex].push_back({key, value});
    if (++numElements > table.size() * 0.75) {
        rehash();
    }
}

void HashStruct::rehash() {
    int newSize = table.size() * 2;
    vector<list<pair<string, vector<pair<string, int>>>>> newTable(newSize);
    for (auto valInList : table) {
        for (auto valInList2 : valInList) {
                int hashIndex = Hash(valInList2.first) % newSize;
                newTable[hashIndex].push_back(valInList2);
            }
        }
    table = move(newTable);
    }



vector<pair<string, int>> HashStruct::operator[](string key) {
    int hashIndex = Hash(key);
    for (auto valInList : table[hashIndex]) {
        if (valInList.first == key) {
            return valInList.second;
        }
    }
    return {};
}

vector<pair<string, int> > HashStruct::at(const string &key) {
    int hashIndex = Hash(key);
    for (auto valInList : table[hashIndex]) {
        if (valInList.first == key) {
            //cout << key << endl;
            //cout << valInList.second[valInList.second.size()-1].second << endl;
            return valInList.second;
        }
    }
    throw std::out_of_range("Key not found");
}








//Hash Interaction Functions
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
                        pair<string, int> pair;
                        pair.first = values[0];
                        pair.second = stoi(values[1]);
                        insertWord(key, pair);
                    }

                    //data.push_back(values);
                }
                //map[key] = data;
            }
        }
        file.close();
    }
}

void HashMap::insertWord(string word, pair<string, int> value) {
    vector<pair<string,int>> values = getStats(word);
    bool found = true;
    for(int i = 0; i < values.size(); i++) {
        if(values[i] == value) {
            return;
        } else if (values[i].first == value.first) {
            values[i] = value;
            found = false;
            break;
        }
    }
    if (found) {
        values.push_back(value);
    }

    map.insert(word, values);
    if(!genres.empty()) {
        for(int i = 0; i < genres.size(); i++) {
            if(genres[i] == value.first) {
                return;
            }
        }
    }
    genres.push_back(value.first);
}

void HashMap::insertWordOccurrence(string word, string genre) {
    vector<pair<string,int>> values = getStats(word);
    bool found = false;
    for(int i = 0; i < values.size(); i++) {
        if(values[i].first == genre) {
            values[i].second = values[i].second + 1;
            found = true;
            break;
        }
    }
    if(!found) {
        pair<string,int> newVal;
        newVal = {genre, 1};
        values.push_back(newVal);
    }
    map.insert(word, values);
    if(!genres.empty()) {
        for(int i = 0; i < genres.size(); i++) {
            if(genres[i] == genre) {
                return;
            }
        }
    }
    genres.push_back(genre);
}


vector<pair<string,int>> HashMap::getStats(string word) {
    if(validWord(word)) {
        vector<pair<string,int>> stats = map.at(word);
        return stats;
    }
    return vector<pair<string,int>>();
}

pair<string,int> HashMap::getStatsFromGenre(string word, string genre) {
    if(validWord(word)) {
        vector<pair<string,int>> stats = map.at(word);
        for (int i = 0; i < stats.size(); i++) {
            if(stats[i].first == genre) {
                return stats[i];
            }
        }
    }
    return pair<string,int>();
}

bool HashMap::saveHashMap(string filename) {
    ofstream file(filename);

    if (file.is_open()) {
        // Write key-value pairs
        for (auto list : map) {
            for (auto pair : list) {
                file << pair.first;
                for (int i = 0; i < pair.second.size(); i++) {
                    if (pair.second[i].second != 0) {
                        file << "," << pair.second[i].first << "," << pair.second[i].second;
                    } else {
                        //return false;
                    }
                }
                file << endl;
            }
        }
        file.close();
        return true;
    } else {
        return false;
    }

}

