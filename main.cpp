#include <iostream>
#include "dataParser.h"


using namespace std;

int main() {
    vector<Song> songs = parseDataset("song_lyrics.csv");

    for (int i = 0; i < 5 && i < songs.size(); ++i) {
        cout << "Genre: " << songs[i].genre << "\nWords:\n";
        for (const string& word : songs[i].words) {
            cout << word << " ";
        }
        cout << "\n----------------------\n";
    }
    return 0;
}