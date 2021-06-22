//
// Created by User on 19/05/2021.
//

#ifndef PROJECT_READFILE_H
#define PROJECT_READFILE_H

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/*
 * read file with numbers 0-9 with no spaces between them and create a vector of numbers
 */
vector<unsigned int> read_0_9_File(const string& filename);
/*
 * read DNA file and create a vector of numbers
 */
vector<unsigned int> readDNA(const string& filename);
/*
 * read a file with unsigned numbers with a space separation the numbers and create a vector
 */
vector<unsigned int> readNumberFile(const string& filename);
/*
 * read text file and create a vector of ints. For ASCII texts
 */
vector<unsigned int> readTextFile(const string& filename);

#endif //PROJECT_READFILE_H
