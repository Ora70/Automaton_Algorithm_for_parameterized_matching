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

void analysisFileColumnNames(const string& fileName);
void testAlgorithm(const string& textPath, const string& patternPath, int size_ab, const string& analysisFileName, const string& matchPosFileName);
void copyPosP_matchToFile(const vector<size_t>& matches, string fileName);
void testManyTexts(const string& textNameStart, const string& analysisFileName, const string& matchPosFileNameStart);



int main(int argc, char** argv) {
    //arguments: 1-path to texts, 2-path to pattern, 3-name of match-Pos file, 4-name of analysis file, 5-size of ab
    //get all the text files in the folder and send them to the algorithm with the pattern
    for (const auto & entry : fs::directory_iterator(argv[1])) {
        if (fs::is_regular_file(entry.path())) { //not a directory. Is a text file
            vector<unsigned int> text = readNumberFile(entry.path().string());
            string textName = entry.path().filename().string();
            string matchPosFilename = argv[3] + textName;
            //send to algorithm
            testAlgorithm(entry.path().string(), argv[2], stoi(argv[5]), argv[4], matchPosFilename);
        }
    }
    return 0;
}

/*
 * input: path to text, path to pattern, size of alphabet and name of file to write the information
 * the function runs the naive algorithm and the algorithm, tests the time of each and writes the information to the
 * analysis file
 */
void testAlgorithm(const string& textPath, const string& patternPath, int size_ab, const string& analysisFileName,
                   const string& matchPosFileName) {
    vector<size_t> text = readNumberFile(textPath);
    vector<size_t> pattern = readNumberFile(patternPath);

    //for every text file test length of pattern in different sizes
    for (int k = 16; k <= pattern.size(); k*=2) {
        //naive algorithm
        vector<size_t> matchesNaive;
        matchesNaive.reserve(text.size());
        auto start = high_resolution_clock::now(); // Get starting timepoint
        naive(matchesNaive, text.data(), text.size(), pattern.data(), k, size_ab);
        auto stop = high_resolution_clock::now(); // Get ending timepoint
        auto durationNaive = duration_cast<microseconds>(stop - start);

        //algorithm
        vector<size_t> matchesAlgorithm;
        matchesAlgorithm.reserve(text.size());
        start = high_resolution_clock::now(); // Get starting timepoint
        Algorithm *algorithm1 = new Algorithm(text.data(), text.size(), pattern.data(), k, size_ab);
        algorithm1->runAlgorithm(matchesAlgorithm);
        stop = high_resolution_clock::now(); // Get ending timepoint
        auto durationAlgorithm = duration_cast<microseconds>(stop - start);

        //time of each algorithm
        auto naiveTime = durationNaive.count();
        auto algoTime = durationAlgorithm.count();

        fs::path pathToText = textPath;
        fs::path pathToPattern = patternPath;
        string textName = pathToText.filename().string();
        string patternName = pathToPattern.filename().string();
        string matchPosFileNameFull = matchPosFileName+ "PatternLen"+ to_string(k) + ".txt";

        fstream fout;
        //add info to the file
        fout.open(analysisFileName, ios::out | ios::app);
        //columns:Name of text file, Name of pattern file, Length of text, Length of pattern, Size of alphabet,
        //      Time taken by naive, Time taken by algorithm, How much faster is the algorithm, Number of matchesAlgorithm,
        //      File with matchesAlgorithm
        fout <<textName+"," <<patternName+"," << text.size() << "," << k << "," << size_ab << "," << naiveTime << ","
             << algoTime << "," << (static_cast<float>(naiveTime) / algoTime) << "," << matchesAlgorithm.size() << "," << matchPosFileNameFull << "\n";
        fout.close();

        //write list of p-matchesAlgorithm to a file
        copyPosP_matchToFile(matchesAlgorithm, matchPosFileNameFull);
    }
}

/*
 * used to run many texts with variation on size of alphabet varying from 10 to 320
 */
void testManyTexts(const string& textNameStart, const string& analysisFileName, const string& matchPosFileNameStart) {
    for (int size_ab = 10; size_ab<=320; size_ab*=2) {
        string textName = "files/" + textNameStart + to_string(size_ab) + ".txt";
        string patternName = "files/pattern" + to_string(size_ab) + ".txt";
        string matchPosFileName = matchPosFileNameStart+ "Ab"+ to_string(size_ab);
        testAlgorithm(textName, patternName, size_ab, analysisFileName, matchPosFileName);
    }
}

/*
 * add the positions of the matches to a file
 */
void copyPosP_matchToFile(const vector<size_t>& matches, string fileName) {
    ofstream myfile;
    fileName = "matchPositions/"+fileName;
    myfile.open(fileName);
    for (auto v : matches) {
        myfile<<v<<" ";
    }
    myfile.close();
}

/*
 * create analysis file with names to the columns
 */
void analysisFileColumnNames(const string& fileName) {
    fstream fout;
    fout.open(fileName, ios::out | ios::app);
    fout<<"Name of text file,"<<"Name of pattern file,"<<"Length of text,"<<"Length of pattern,"<<"Size of alphabet,"
    <<"Time taken by naive,"<<"Time taken by algorithm,"<<"How much faster is the algorithm,"<<"Number of matches,"<<"File with matches\n";
    fout.close();
}
