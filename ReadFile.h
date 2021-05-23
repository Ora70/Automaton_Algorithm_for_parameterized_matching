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
using namespace std;

vector<unsigned int> read_0_9_File(const string& filename);
vector<unsigned int> readDNA(const string& filename);
vector<unsigned int> readNumberFile(const string& filename);

#endif //PROJECT_READFILE_H
