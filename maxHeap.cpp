#include "MaxHeap.h"

void MaxHeap::loadFromFile(string filename) {
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
                    // debug for insert?
                    /*
                    if(status) {
                        cout << "here" << endl;
                        insert(key, values[0], stoi(values[1]));
                    }
                    */

                    //data.push_back(values);
                }
                //map[key] = data;
            }
        }
        file.close();
    }
}

void MaxHeap::insert(string word, string genre, int count) {
    pair<int, string> currPair = {count, word};
    int genreIndex;
    bool found = false;
    for(int i = 0; i < heapGenre.size(); i++ ) {
        if(heapGenre[i] == genre) {
            heap[i].push(currPair);
            return;
        }
    }
    priority_queue<pair<int, string>> pq;
    pq.push(currPair);
    heapGenre.push_back(genre);
    heap.push_back(pq);
}

pair<int, string> MaxHeap::getMax(string genre, vector<string> filter) {
    pair<int, string> empty;
    int genreIndex;
    bool found = false;
    for(int i = 0; i < heapGenre.size(); i++ ) {
        if(heapGenre[i] == genre) {
            genreIndex = i;
            found = true;
            break;
        }
    }
    if(!found) {
        return empty;
    }
    if(filter.empty()) {
        return heap[genreIndex].top();
    }
    priority_queue<pair<int, string>> PqCopy = heap[genreIndex];
    while(!PqCopy.empty()) {
        cout<<"here"<<endl;
        for(int i = 0; i < filter.size(); i++) {
            if(filter[i] == PqCopy.top().second) {
                PqCopy.pop();
            }
        }
        return PqCopy.top();
    }
    return empty;
    /*
    while (!heap.empty()) {
        string word = heap.top().second;
        int freq = heap.top().first;

        if (wordCount[word] == freq) {
            return {freq, word};
        }
        heap.pop(); // stale value, skip
    }
    return {0, ""};
    */
}

vector<pair<int, string>> MaxHeap::getAll(string genre, vector<string> filter) {
    vector<pair<int, string>> empty;
    int genreIndex;
    bool found = false;
    for(int i = 0; i < heapGenre.size(); i++ ) {
        if(heapGenre[i] == genre) {
            genreIndex = i;
            found = true;
            break;
        }
    }
    if(!found) {
        return empty;
    }
    priority_queue<pair<int, string>> PqCopy = heap[genreIndex];
    if(!filter.empty()) {
        while(!PqCopy.empty()) {
            for(int i = 0; i < filter.size(); i++) {
                if(filter[i] == PqCopy.top().second) {
                    PqCopy.pop();
                }
            }
            empty.push_back(PqCopy.top());
            PqCopy.pop();
        }
    } else {
        while(!PqCopy.empty()) {
            empty.push_back(PqCopy.top());
            PqCopy.pop();
        }
    }
    return empty;
}


/*
void MaxHeap::clear() {
    while (!heap.empty()) heap.pop();
    wordCount.clear();
}
*/
