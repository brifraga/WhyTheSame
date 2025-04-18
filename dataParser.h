#ifndef DATASETPARSER_H
#define DATASETPARSER_H

#include <vector>
#include "Song.h"
using namespace std;

vector<Song> parseDataset(const string& dataset);
bool endsWithRealQuote(const string& line);
vector<string> cleanAndTokenize(const string& lyrics);

#endif