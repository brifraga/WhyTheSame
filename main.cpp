#include <iostream>
#include "dataParser.h"
#include "HashMap.h"
#include "maxHeap.h"

using namespace std;

int main() {
    //loads dataset into a vector of songs
    vector<Song> songs = parseDataset("top100knew.csv");

    // debug for first few words
    // for (int i = 0; i < 5 && i < songs.size(); ++i) {
    //     cout << "Genre: " << songs[i].genre << "\nWords:\n";
    //     for (const string& word : songs[i].words) {
    //         cout << word << " ";
    //     }
    //     cout << "\n----------------------\n";
    // }

    //creates hashmap and prints when every 10000 songs are put into the hashmap
    HashMap songhashmap;
    for (int i = 0; i < songs.size(); i++) {
        for (const string& word : songs[i].words) {
            songhashmap.insertWordOccurrence(word, songs[i].genre);
        }
        if (i % 10000 == 0) {
            cout << i << " songs uploaded to hashmap!" << endl;
        }
    }

    //makes hashmap txt file (works with large dataset)
    if (songhashmap.saveHashMap("wordhashmap.csv")) {
        cout << "Hash map saved!" << endl;
    } else {
        cout << "Hash map NOT saved ;(..." << endl;
    }

    //create maxheap from hashmap?? (can comment everything else ^^^above^^^ until top of main if just hashmap is needed to save time)
    //not sure how heap is made...
    MaxHeap songheapmap;
    songheapmap.loadFromFile("wordhashmap.csv");


    int userinput = 0;
    //menu for each option
    while (true) {
        cout << "MENU:" << endl;
        cout << "1. Search Occurrence By Word and Genre" << endl;
        cout << "2. Search Occurrence By Genre" << endl;
        cout << "3. Search Occurrence By Word" << endl;
        cout << "4. Exit\n" << endl;
        cout << "Enter input:";
        cin >> userinput;
        if (userinput == 1){
            //word and genre
            cout << endl;
        }
        else if (userinput == 2){
            //genre
            cout << endl;
        }
        else if (userinput == 3){
            //word
            cout << endl;
        }
        else if (userinput == 4){
            //exit or add more inputs if we want more options for user
            break;
        }
    }
    return 0;
}