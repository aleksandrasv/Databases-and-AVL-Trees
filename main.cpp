/*main.cpp*/

//
// myDB project using AVL trees
//
// <<Aleksandra Dmitrieva>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #04
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>


#include "util.h"

using namespace std;


//
// tokenize
//
// Given a string, breaks the string into individual tokens (words) based
// on spaces between the tokens.  Returns the tokens back in a vector.
//
// Example: "select * from students" would be tokenized into a vector
// containing 4 strings:  "select", "*", "from", "students".
//
vector<string> tokenize(string line)
{
  vector<string> tokens;
  stringstream  stream(line);
  string token;

  while (getline(stream, token, ' '))
  {
    tokens.push_back(token);
  }

  return tokens;
}



int main()
{

    int numberOfColumns = 0;
    int recordSize = 0;
    string tablename; // = "students";
    vector <int> meta_data;
    vector <string> colum_name;
    vector<avltree<string, streamoff>> avl_Trees;
	vector<string> student_info;
	vector<streamoff> filePositions;



    // Need function to build avl trees
    // Need function to read trough the meta data file

    avltree<string, streamoff> avl; // basic avl tree to use for building tree with an  index column as a key and offset as value


    cout << "Welcome to myDB, please enter tablename> ";
    getline(cin, tablename);

    cout << "Reading meta-data..." << endl;

    StoreMetaIndex(tablename, numberOfColumns, recordSize, meta_data, colum_name); // Vector with indexes

    cout << "Building index tree(s)..." << endl;
	
	// Build index tree for all indexes in meta file and print out tree info
	for (int i = 0; i < numberOfColumns; i++)
	{
		if (meta_data.at(i) == 1)
		{
			cout << "Index column: " << colum_name[i] << endl;
			avl_Trees.push_back(BuildIndexTrees (tablename, numberOfColumns, recordSize, i));		
		}
	}

	
// 	for (int i = 0; i < numberOfColumns; ++i)
// 	{
// 		meta_data.at(i) == 1
// 	}
    //
    // Main loop to input and execute queries from the user:
    //
    string query;

    cout << endl;
    cout << "Enter query> ";
    getline(cin, query);

    while (query != "exit")
    {
		vector<string> tokens = tokenize(query);
		
		// Check if we got correct query		
		if (tokens[0] != "select")
		{
			cout << "Unknown query, ignored..." << endl;
		}
		else if (tokens.size() != 8)
		{
			cout << "Invalid select query, ignored..." << endl;
		}
		// Check if all key words are in correct palce in query
		else if (tokens[2] != "from" || tokens[4] != "where" || tokens[6] != "=" )
		{
			cout << "Invalid select query, ignored..." << endl;
		}
		else if (tokens[3] != tablename)
		{
			cout << "Invalid table name, ignored..." << endl;
		}
		// Check second value in query must be * or a valid column name
		else if (tokens[1] != "*" && find (colum_name.begin(), colum_name.end(), tokens[1]) == colum_name.end())
		{	
			cout << "Invalid select column, ignored..." << endl;
			
		}
		else if ( find (colum_name.begin(), colum_name.end(), tokens[5]) == colum_name.end())
		{
			cout << "Invalid where column, ignored..." << endl;
		}
		else 
		{
			// Find match column # 
			int matchColumn = -1;
			for (int i = 0; i < colum_name.size(); ++i)
			{
				if (colum_name[i] == tokens[5]){
					matchColumn = i;
				}
			} 
			// Store file position in  vector
			filePositions = LinearSearch(tablename, recordSize, numberOfColumns, tokens[7], matchColumn);
			
			// Check if value was found in file data
			if (filePositions.size() == 0)
			{
				cout << "Not found..." << endl;
			}
			
			// if second value in query * and we need to display whole info
			if (tokens[1] == "*")
			{
				
				for (int i = 0; i < filePositions.size(); ++i)
				{
					// Store student info in vector for all matches
					student_info = GetRecord(tablename, filePositions[i], numberOfColumns);
					// Print out all info from query
					for (int j = 0; j< numberOfColumns; ++j)
					{
						cout << colum_name[j] << ": " << student_info[j] << endl;
					}
				}
			}
			// If we are lookin for speific value in DB
			else 
			{
				for (int i = 0; i < filePositions.size(); ++i)
				{
					// Store student info in vector for all matches
					student_info = GetRecord(tablename, filePositions[i], numberOfColumns);
					for (int j = 0; j< numberOfColumns; ++j)
					{
						// Print out the requered info
						if (colum_name[j] == tokens[1])
							cout << colum_name[j] << ": " << student_info[j] << endl;
					}
				}
			}
			
			
		}

		cout << endl;
		cout << "Enter query> ";
		getline(cin, query);
	}

    //
    // done:
    //
    return 0;
}
