#include <iostream>
#include <limits>

#include "dataParser.h"
#include "HashMap.h"
#include "maxHeap.h"

using namespace std;

int main() {

    //loads dataset into a vector of songs
    vector<Song> songs = parseDataset("top100knew.csv");

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
    cout << "\nGenres loaded into heap:\n";
    for (const auto& g : songheapmap.getLoadedGenres()) {
        cout << "- " << g << endl;
    }

    int userinput = 0;
    //menu for each option
    while (true) {
        cout << "MENU:" << endl;
        cout << "1. Search Occurrence By Word and Genre" << endl;
        cout << "2. Search Occurrence By Genre" << endl;
        cout << "3. Search Occurrence By Word" << endl;
        cout << "4. Exit\n" << endl;

        int userinput;
        cout << "Enter input: ";
        cin >> userinput;

        if (cin.fail()) {
            cin.clear(); // clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
            cout << "Invalid input. Please enter a number.\n\n";
            continue; // go back to the start of the loop
        }

        if (userinput == 1) {
            string word, genre;
            cout << "Enter a word to search: ";
            cin >> word;
            cout << "Enter a genre: ";
            cin >> genre;

            int count = songhashmap.getWordGenreCount(word, genre);
            cout << "The word \"" << word << "\" appeared " << count << " times in genre \"" << genre << "\".\n" << endl;
        } else if (userinput == 2) {
            // Search Occurrence By Genre
            string genre;
            cout << "\nEnter a genre:";
            cin >> genre;

            vector<string> fillerWords = {
                "the", "and", "a", "an", "in", "on", "of", "to", "for", "with",
                "by", "at", "from", "it", "is", "that", "this", "i", "you",
                "he", "she", "we", "they", "me", "my", "your", "our", "us",
                "be", "was", "were", "are", "am", "as", "but", "or", "not",
                "so", "do", "did", "does", "have", "has", "had", "if", "then",
                "a", "im", "it", "to", "all", "its", "verse", "chorus", "intro"
            };

            vector<pair<int, string>> allWords = songheapmap.getAll(genre, fillerWords);

            if (allWords.empty()) {
                cout << "\nNo data found for genre \"" << genre << "\" or all top words were filtered out.\n" << endl;
            } else {
                cout << "\nTop 10 words in genre \"" << genre << "\" (excluding filler words):" << endl;
                for (int i = 0; i < 10 && i < allWords.size(); ++i) {
                    cout << allWords[i].second << " - " << allWords[i].first << " occurrences" << endl;
                }
                cout << endl;
            }
        } else if (userinput == 3) {
            cout << "\nEnter a word to search: ";
            string word;
            cin >> word;

            vector<vector<string>> stats = songhashmap.getStats(word);

            if (stats.empty()) {
                cout << "The word \"" << word << "\" was not found in any genre.\n\n";
            } else {
                cout << "\nOccurrences of \"" << word << "\" by genre:\n";
                for (const auto& entry : stats) {
                    if (entry.size() >= 2 && !entry[0].empty()) { // ✅ check for empty genre
                        cout << entry[0] << " - " << entry[1] << " occurrences\n";
                    }
                }
                cout << endl;
            }
        } else if (userinput == 4){
            //exit or add more inputs if we want more options for user
            break;
        }
    }
    return 0;
}