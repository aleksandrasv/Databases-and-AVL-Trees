/*util.h*/

//
// Utility functions for myDB project
//
// <<YOUR NAME>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #04
//

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "avl.h"

using namespace std;

void EchoData(string tablename, int recordSize, int numColumns);

vector<string> GetRecord(string tablename, streamoff pos, int numColumns);

vector<streamoff> LinearSearch(string tablename, int recordSize, int numColumns, string matchValue, int matchColumn);

void StoreMetaIndex( string tablename, int & numberOfColumns, int & recordSize, vector <int>& meta_data, vector <string>& colum_name);


avltree<string, streamoff> BuildIndexTrees (string tablename, int numColumns, int recordSize, int index);