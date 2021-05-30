#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include "Algorithm.h"
#include "AlgorithmInfAb.h"
#include "Naive.h"
#include "ReadFile.h"
#include "CreateData.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

void testCode();
void analysisFileColumnNames();
void testAlgorithm();
void copyPosP_matchToFile(list<size_t> matches, string fileName);


int main() {
    /*vector<size_t> pattern{1,2,3,3,2,5,7,6};
    list<vector<size_t>> p_matches = create_p_match(pattern, 20);
    for (auto const& match : p_matches) {
        for (auto const& element : match) {
            cout<<element<<", ";
        }
        cout<<endl;
    }*/
    /*vector<unsigned int> pattern = readNumberFile("../testPattern.txt");
    for (auto& it : pattern) {
        cout << it << ", ";
    }*/

    testAlgorithm();


    return 0;
}

void testCode() {
    //vector<size_t> text = read_0_9_File("../pi.txt");
    vector<size_t> text = read_0_9_File("files/text10.txt");
    //vector<unsigned int> text = readDNA("../SARS_CORONAVIRUS_NC_045512_sequence.fasta");

    /*for (int i = 35; i < 58; i++) {
        cout<<text[i];
    }*/
//    text.insert(text.end(), text.cbegin(), text.cend());
//    text.insert(text.end(), text.cbegin(), text.cend());
//    text.insert(text.end(), text.cbegin(), text.cend());
    cout<<"length of file: "<<text.size()<<endl;
    //unsigned int pattern2[] = {3,0,1,0,0,0,2,3,2,1,1,2,0,3,2,1,0};
    //unsigned int pattern2[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,2,3,2,1,1,2,0,3,2,1,0};
    //unsigned int pattern2[] = {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7};
    unsigned int pattern2[] = {3,0,1,0,0,0,4,5,8,7,7,7,1,3,1,5,9,0,2,3,5,9,1,9,9,5,1,3,3,2,5,4,6,5,5,5,7,6,8,1,2,3,4,3,0,1,0,0,0,4,5,8,7,7,7,1,3,1,5,9,0,2,3,5,9,1,9,9,5,1,3,3,2,5,4,6,5,5,5,7,6,8,1,2,3,4,3,0,1,0,0,0,4,5,8,7,7,7,1,3,1,5,9,0,2,3,5,9,1,9,9,5,1,3,3,2,5,4,6,5,5,5,7,6,8,1,2,3,4};
    for (int k = 120; k <= sizeof(pattern2)/sizeof(pattern2[0]); k++) {
        cout << "Pattern's size " << k << endl;

        auto start = high_resolution_clock::now(); // Get starting timepoint
        list<size_t> matches1 = naive(text.data(), text.size(), pattern2, k, 10);
        //list <size_t> matches1 = naiveInfAB(text.data(), text.size(), pattern2, k);
        auto stop = high_resolution_clock::now(); // Get ending timepoint
        auto durationNaive = duration_cast<microseconds>(stop - start);

        start = high_resolution_clock::now(); // Get starting timepoint
        Algorithm *algorithm1 = new Algorithm(text.data(), text.size(), pattern2, k, 10);
        //AlgorithmInfAb *algorithm1 = new AlgorithmInfAb(text.data(), text.size(), pattern2, k);


        list<size_t> matches = algorithm1->runAlgorithm();
        //list <size_t> matches = algorithm1->runAlgorithm();
        stop = high_resolution_clock::now(); // Get ending timepoint
        auto durationAlgorithm = duration_cast<microseconds>(stop - start);

        auto naiveTime = durationNaive.count();
        auto algoTime = durationAlgorithm.count();
        cout << "Time taken by naive: "<< naiveTime << " microseconds" << endl;
        cout << "Time taken by algorithm: "<< algoTime << " microseconds" << endl;
        cout<< "difference: "<<naiveTime - algoTime<< " microseconds, or "<<(naiveTime - algoTime)/1000000.0<<" seconds"<< endl;
        cout << "The algorithm is x" << (static_cast<float>(naiveTime) / algoTime) << " faster\n" << endl;


        string flag = "good";
        auto it1 = matches.begin();
        auto it2 = matches1.begin();
        while (it1 != matches.end() && it2 != matches1.end()) {
            if (*it1 != *it2) {
                flag = "bad";
                cout << "bad\n" << "algorithm: " << *it1 << "\nnaive: " << *it2 << "\n";
                break;
            }
            it1++;
            it2++;
        }
        cout << flag << "\n\n";
        cout << "--------------------------------" << endl;
    }
}

void testAlgorithm() {
    analysisFileColumnNames();
    for (int size_ab = 10; size_ab<=320; size_ab*=2) {
        string textName = "text"+ to_string(size_ab)+".txt";
        string patternName = "pattern"+ to_string(size_ab)+".txt";

        vector<size_t> text = readNumberFile("files/"+ textName);
        vector<size_t> pattern = readNumberFile("files/"+patternName);

        //for every text file test length of pattern in different sizes
        for (int k = 4; k <= pattern.size(); k*=2) {
            //naive algorithm
            auto start = high_resolution_clock::now(); // Get starting timepoint
            list<size_t> matches1 = naive(text.data(), text.size(), pattern.data(), k, size_ab);
            auto stop = high_resolution_clock::now(); // Get ending timepoint
            auto durationNaive = duration_cast<microseconds>(stop - start);

            //algorithm
            start = high_resolution_clock::now(); // Get starting timepoint
            Algorithm *algorithm1 = new Algorithm(text.data(), text.size(), pattern.data(), k, size_ab);
            list<size_t> matches = algorithm1->runAlgorithm();
            stop = high_resolution_clock::now(); // Get ending timepoint
            auto durationAlgorithm = duration_cast<microseconds>(stop - start);

            //time of each algorithm
            auto naiveTime = durationNaive.count();
            auto algoTime = durationAlgorithm.count();

            string matchPosFileName = "ab"+to_string(size_ab)+"patternLen"+ to_string(k)+".txt";
            fstream fout;
            //add info to the file
            fout.open("analysis.csv", ios::out | ios::app);
            //columns:Name of text file, Name of pattern file, Length of text, Length of pattern, Size of alphabet,
            //      Time taken by naive, Time taken by algorithm, How much faster is the algorithm, Number of matches,
            //      File with matches
            fout<<textName+","<<patternName+","<<text.size()<<","<<k<<","<<size_ab<<","<<naiveTime<<","
                <<algoTime<<","<<(static_cast<float>(naiveTime) / algoTime)<<","<<matches.size()<<","<<matchPosFileName<<"\n";
            fout.close();

            //write list of p-matches to a file
            copyPosP_matchToFile(matches, matchPosFileName);

            //test and make sure both algorithms gave the same result
            string flag = "good";
            auto it1 = matches.begin();
            auto it2 = matches1.begin();
            while (it1 != matches.end() && it2 != matches1.end()) {
                if (*it1 != *it2) {
                    flag = "bad";
                    cout << "bad\n" << "algorithm: " << *it1 << "\nnaive: " << *it2 << "\n";
                    break;
                }
                it1++;
                it2++;
            }
            if (flag == "bad") {
                cout<<"bad. text: "<<textName<<", pattern: "<<patternName<<",pattern length: "<<to_string(k)<<endl;
                cout << "--------------------------------" << endl;
            }

        }
    }
}

void copyPosP_matchToFile(list<size_t> matches, string fileName) {
    ofstream myfile;
    fileName = "matchPositions/"+fileName;
    myfile.open(fileName);
    for (auto v : matches) {
        myfile<<v<<" ";
    }
    myfile.close();
}

void writeToFile() {
    fstream fout;
    fout.open("analysis.csv", ios::out | ios::app);
    fout<<"Name of text file,"<<"Name of pattern file,"<<"Length of text,"<<"Length of pattern,"<<"Size of alphabet,"
    <<"Time taken by naive,"<<"Time taken by algorithm,"<<"How much faster is the algorithm,"<<"Number of matches,"
    <<"File with matches\n";
    fout.close();
}