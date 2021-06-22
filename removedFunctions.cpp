#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "Algorithm.h"
#include "AlgorithmInfAb.h"
#include "Naive.h"
#include "ReadFile.h"
#include <chrono>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
using namespace std::chrono;

void testAlgorithmNumMatches(const string& textName, const string& patternName, int size_ab, const string& analysisFileName);

void testManyTextsNumMatches(const string& textNameStart, const string& analysisFileName) {
    for (int size_ab = 10; size_ab<=320; size_ab*=2) {
        string textName = textNameStart + to_string(size_ab) + ".txt";
        string patternName = "pattern" + to_string(size_ab) + ".txt";
        testAlgorithmNumMatches(textName, patternName, size_ab, analysisFileName);
    }
}


void testAlgorithmNumMatches(const string& textName, const string& patternName, int size_ab, const string& analysisFileName) {
    vector<size_t> text = readNumberFile("files/"+ textName);
    vector<size_t> pattern = readNumberFile("files/"+patternName);

    //for every text file test length of pattern in different sizes
    for (int k = 4; k <= pattern.size(); k*=2) {
        //naive algorithm
        auto start = high_resolution_clock::now(); // Get starting timepoint
        size_t numMatches1 = naiveNumMatches(text.data(), text.size(), pattern.data(), k, size_ab);
        auto stop = high_resolution_clock::now(); // Get ending timepoint
        auto durationNaive = duration_cast<microseconds>(stop - start);

        //algorithm
        start = high_resolution_clock::now(); // Get starting timepoint
        Algorithm *algorithm1 = new Algorithm(text.data(), text.size(), pattern.data(), k, size_ab);
        size_t numMatches = algorithm1->runAlgorithmNumMatches();
        stop = high_resolution_clock::now(); // Get ending timepoint
        auto durationAlgorithm = duration_cast<microseconds>(stop - start);

        //time of each algorithm
        auto naiveTime = durationNaive.count();
        auto algoTime = durationAlgorithm.count();

        fstream fout;
        //add info to the file
        fout.open(analysisFileName, ios::out | ios::app);
        //columns:Name of text file, Name of pattern file, Length of text, Length of pattern, Size of alphabet,
        //      Time taken by naive, Time taken by algorithm, How much faster is the algorithm, Number of matches
        fout<<textName+","<<patternName+","<<text.size()<<","<<k<<","<<size_ab<<","<<naiveTime<<","
            <<algoTime<<","<<(static_cast<float>(naiveTime) / algoTime)<<","<<numMatches<<"\n";
        fout.close();

        //test and make sure both algorithms gave the same result
        string flag = "good";
        if (numMatches != numMatches1) {
            flag == "bad";
        }
        if (flag == "bad") {
            cout<<"bad. text: "<<textName<<", pattern: "<<patternName<<",pattern length: "<<endl;
            cout << "--------------------------------" << endl;
        }

    }
}


