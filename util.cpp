/*util.cpp*/

//
// Utility functions for myDB project
//
// <<YOUR NAME>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #04
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "util.h"

using namespace std;




//
// EchoData
//
// Reads the contents of a table's .data file, and outputs the
// values for each record (one record per line).  Pass the table
// name, the record size, and the # of columns per record.
//
// Example: EchoData("students", 82, 5) would output the contents
// of "students.data".
//
void EchoData(string tablename, int recordSize, int numColumns)
{
  string   filename = tablename + ".data";
  ifstream data(filename, ios::in | ios::binary);

  if (!data.good())
  {
    cout << "**Error: couldn't open data file '" << filename << "'." << endl;
    return;
  }

  //
  // read file record by record, and output each record of values:
  //
  data.seekg(0, data.end);  // move to the end to get length of file:
  streamoff length = data.tellg();

  streamoff pos = 0;  // first record at offset 0:
  string    value;

  while (pos < length)
  {
    data.seekg(pos, data.beg);  // move to start of record:

    for (int i = 0; i < numColumns; ++i)  // read values, one per column:
    {
        data >> value;
        cout << value  << " ";
    }

    cout << endl;
    pos = pos + recordSize;  // move offset to start of next record:
  }
}


//
// GetRecord
//
// Reads a record of data values and returns these values in a vector.
// Pass the table name, the file position (a stream offset), and the # 
// of columns per record.
//
// Example: GetRecord(�students�, 0, 5) would read the first student
// record in �students.data�.
// 
vector<string> GetRecord(string tablename, streamoff pos, int numColumns)
{
    vector<string>  values;
	
    // open the file
    string   filename = tablename + ".data";
    ifstream data(filename, ios::in | ios::binary);

    // make sure it opened
    if (!data.good())
    {
        cout << "**Error: couldn't open data file '" << filename << "'." << endl;
        return values;
    }

    string    value;

    //seekg to the given position,
    data.seekg(pos, data.beg);

    // loop and input values using >>, store into vector
    for (int i = 0; i < numColumns; ++i )   // read values, one per column:
    {
        data >> value;
        values.push_back(value);
    }

    //  return vector
    return values;

  return values;
}



//
// LinearSearch
//
// Searches the contents of a .data file record by record; the first 
// three parameters are the tablename, record size, and # of columns.
// The 4th parameter specifies the value to search for: matchValue.
// The 5th parameter is the record column to match against --- pass
// 1 for the first column, 2 for the 2nd column, and so on.  All matches
// are exact matches.
//
// Example: LinearSearch(�students�, 82, 5, "kim", 3) would search the 
// "students.data" file for all records whose 3rd column --- lastname ---
// matches "kim".  There are 2 matches (records 3 and 6), so their file 
// positions of 164 and 410 would be returned in the vector.
// 
vector<streamoff> LinearSearch(string tablename, int recordSize, int numColumns, string matchValue, int matchColumn)
{
	vector<streamoff>  matches;
	
	// open the file
	string   filename = tablename + ".data";
	ifstream data(filename, ios::in | ios::binary);

	//make sure it opened
	if (!data.good())
	{
		cout << "**Error: couldn't open data file '" << filename << "'." << endl;
		return matches;
	}
	
	// read file record by record, and output each record of values:
	// 
	data.seekg(0, data.end);  // move to the end to get length of file:
	streamoff length = data.tellg();

	streamoff pos = 0;  // first record at offset 0:
	string    value;

	
	while (pos < length)
	{
		data.seekg(pos, data.beg);  // move to start of record:

		for (int i = 0; i < numColumns; ++i)  // read values, one per column:
		{
			data >> value;
			if (i == matchColumn )
			{
				if (value == matchValue)
				{
					matches.push_back(pos);
				}
			}
		}
		pos += recordSize;  // move offset to start of next record:
	}

  // loop through record by record looking for matches. 
  // For each match found, add file position to vector.
 
  return matches;
}

// StoreMeta()
// Get Meta data info from file:
void StoreMetaIndex( string tablename, int & numberOfColumns, int & recordSize, vector <int>& meta_data, vector <string>& colum_names)
{
    string   filename = tablename + ".meta";
    ifstream meta(filename);

    if (!meta.good())
    {
        cout << "**Error: couldn't open data file '" << filename << "'." << endl;
        return;
    }

    string    colum_name;
    int index_value;

    meta >> recordSize;  // get first ID, or set EOF flag if file empty:
    meta >> numberOfColumns;

    meta >> colum_name;
    while (!meta.eof()){
		
        colum_names.push_back(colum_name); // store colum_names
        meta >> index_value;
        meta_data.push_back(index_value); // store meta data for index values
        meta >> colum_name;

    }
    return;
}

//BuildIndexTrees ()
//Build one avl tree and return it
avltree<string, streamoff>  BuildIndexTrees (string tablename, int numColumns, int recordSize, int index )
{
    avltree<string, streamoff> avl;
    string   filename = tablename + ".data";
    ifstream data(filename, ios::in | ios::binary);

    if (!data.good())
    {
        cout << "**Error: couldn't open data file '" << filename << "'." << endl;
        return avl;
    }

    //
    // Okay, read file record by record, and output each record of values:
    //
    data.seekg(0, data.end);  // move to the end to get length of file:
    streamoff length = data.tellg();

    streamoff pos = 0;  // first record at offset 0:
    string    value;

    while (pos < length)

    {
        data.seekg(pos, data.beg);  // move to start of record:

        for (int j = 0; j < numColumns; ++j)
        {
            data >> value;
            if (j == index) // check if value is indexed
            {
                avl.insert(value, pos); // add value to avl tree
            } 
        }
        pos += recordSize;  // move offset to start of next record:
    }
	//Print out tree information
	cout <<"  Tree size: " << avl.size() << endl; 
	cout <<"  Tree height: " << avl.height() << endl; 
    return avl;
};
