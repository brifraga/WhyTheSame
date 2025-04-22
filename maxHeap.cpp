#include "MaxHeap.h"


void MaxHeapStruct::push(pair<int, string> p) {
    heap.push_back(p);
    heapifyUp(heap.size() - 1);
}

pair<int, string> MaxHeapStruct::pop() {
    if (heap.empty()) {
        throw out_of_range("Max heap is empty");
    }
    pair<int, string> maxValue = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);

    return maxValue;
}

pair<int, string> MaxHeapStruct::top() {
    if (heap.empty()) {
        throw runtime_error("MaxHeap is empty");
    }
    return heap[0];
}

bool MaxHeapStruct::empty() {
    return heap.empty();
}

int MaxHeapStruct::size() {
    return heap.size();
}


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

                    if(status) {
                        insert(key, values[0], stoi(values[1]));
                    }


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
    MaxHeapStruct pq;
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
    MaxHeapStruct PqCopy = heap[genreIndex];
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
    vector<pair<int, string>> result;
    int genreIndex = -1;
    for (int i = 0; i < heapGenre.size(); ++i) {
        if (heapGenre[i] == genre) {
            genreIndex = i;
            break;
        }
    }
    if (genreIndex == -1) {
        return result;
    }

    MaxHeapStruct pqCopy = heap[genreIndex];

    while (!pqCopy.empty() && result.size() < 10) {
        pair<int, string> top = pqCopy.top();
        pqCopy.pop();

        bool isFiller = false;
        for (const string& word : filter) {
            if (word == top.second) {
                isFiller = true;
                break;
            }
        }

        if (!isFiller) {
            result.push_back(top);
        }
    }

    return result;
}

