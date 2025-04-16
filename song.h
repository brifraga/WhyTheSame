#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>
using namespace std;

struct Song {
    string genre;
    vector<std::string> words;
};

#endif