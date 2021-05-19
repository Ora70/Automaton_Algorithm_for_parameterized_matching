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
#include <chrono>

using namespace std;
using namespace std::chrono;


int main() {
    vector<unsigned int> text = readFile("../pi.txt");
    //vector<unsigned int> text = readDNA("../sequence.fasta");

    text.insert(text.end(), text.cbegin(), text.cend());
    text.insert(text.end(), text.cbegin(), text.cend());

    unsigned int pattern2[] = {3,0,1,0,0};//,0,2,3};

    auto start = high_resolution_clock::now(); // Get starting timepoint
    list <long unsigned int> matches1 = naive(text.data(), text.size(), pattern2, (sizeof(pattern2)/sizeof(*pattern2)), 10);
    //list <long unsigned int> matches = naiveInfAB(text.data(), text.size(), pattern2, (sizeof(pattern2)/sizeof(*pattern2)));
    auto stop = high_resolution_clock::now(); // Get ending timepoint
    auto durationNaive = duration_cast<microseconds>(stop - start);

    Algorithm *algorithm1 = new Algorithm(text.data(), text.size(), pattern2, (sizeof(pattern2)/sizeof(*pattern2)), 10);
    //AlgorithmInfAb *algorithm2 = new AlgorithmInfAb(text.data(), text.size(), pattern2, (sizeof(pattern2)/sizeof(*pattern2)));

    start = high_resolution_clock::now(); // Get starting timepoint
    list <long unsigned int> matches = algorithm1->runAlgorithm();
    //list <long unsigned int> matches1 = algorithm2->runAlgorithm();
    stop = high_resolution_clock::now(); // Get ending timepoint
    auto durationAlgorithm = duration_cast<microseconds>(stop - start);

    auto naiveTime = durationNaive.count();
    auto algoTime = durationAlgorithm.count();
    cout << "Time taken by naive: "<< naiveTime << " microseconds" << endl;
    cout << "Time taken by algorithm: "<< algoTime << " microseconds" << endl;
    cout<< "difference: "<<naiveTime - algoTime<< " microseconds, or "<<(naiveTime - algoTime)/1000000.0<<" seconds"<< endl;
    cout << "The algorithm is x" << (static_cast<float>(naiveTime) / algoTime) << " faster" << endl;


    /*string flag = "good";
    auto it1 = matches.begin();
    auto it2 = matches1.begin();
    while ( it1 != matches.end() && it2 != matches1.end()) {
        if (*it1 != *it2) {
            flag = "bad";
            cout<<"bad\n"<<"regular: "<<*it1<<"\ninf: "<<*it2<<"\n";
            break;
        }
        it1++;
        it2++;
    }
    cout<<flag<<"\n\n";*/

    return 0;
}