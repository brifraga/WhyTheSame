#include <iostream>
#include "dataParser.h"
#include "HashMap.h"

using namespace std;

int main() {
    vector<Song> songs = parseDataset("top100knew.csv");

    // for (int i = 0; i < 5 && i < songs.size(); ++i) {
    //     cout << "Genre: " << songs[i].genre << "\nWords:\n";
    //     for (const string& word : songs[i].words) {
    //         cout << word << " ";
    //     }
    //     cout << "\n----------------------\n";
    // }
    HashMap songhashmap;
    // for (const Song :songs){
    //  for (each word : song.words){
    //      add into hashmap;
    //  }
    //}
    return 0;
}