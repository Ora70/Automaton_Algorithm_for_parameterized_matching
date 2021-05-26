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

void testAlgorithm();


int main() {
    vector<size_t> pattern{1,2,3,3,2,5,7,6};
    list<vector<size_t>> p_matches = create_p_match(pattern, 3);
    for (auto const& match : p_matches) {
        for (auto const& element : match) {
            cout<<element<<", ";
        }
        cout<<endl;
    }


    return 0;
}

void testAlgorithm() {
    vector<size_t> text = read_0_9_File("../pi.txt");
    //vector<unsigned int> text = readDNA("../SARS_CORONAVIRUS_NC_045512_sequence.fasta");

    /*for (int i = 35; i < 58; i++) {
        cout<<text[i];
    }*/
//    text.insert(text.end(), text.cbegin(), text.cend());
//    text.insert(text.end(), text.cbegin(), text.cend());
//    text.insert(text.end(), text.cbegin(), text.cend());
    cout<<"length of file: "<<text.size()<<endl;
    unsigned int pattern2[] = {3,0,1,0,0,0,2,3,2,1,1,2,0,3,2,1,0};
    //unsigned int pattern2[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,1,0,0,0,2,3,2,1,1,2,0,3,2,1,0};
    //unsigned int pattern2[] = {3,0,1,0,0,0,4,5,8,7,7,7,1,3,1,5,9,0,2,3,5,9,1,9,9,5,1,3,3,2,5,4,6,5,5,5,7,6,8,1,2,3,4,3,0,1,0,0,0,4,5,8,7,7,7,1,3,1,5,9,0,2,3,5,9,1,9,9,5,1,3,3,2,5,4,6,5,5,5,7,6,8,1,2,3,4,3,0,1,0,0,0,4,5,8,7,7,7,1,3,1,5,9,0,2,3,5,9,1,9,9,5,1,3,3,2,5,4,6,5,5,5,7,6,8,1,2,3,4};
    for (int k = 1; k <= sizeof(pattern2)/sizeof(pattern2[0]); k++) {
        cout << "Pattern's size " << k << endl;

        auto start = high_resolution_clock::now(); // Get starting timepoint
        //list<size_t> matches1 = naive(text.data(), text.size(), pattern2, k, 10);
        list <size_t> matches1 = naiveInfAB(text.data(), text.size(), pattern2, k);
        auto stop = high_resolution_clock::now(); // Get ending timepoint
        auto durationNaive = duration_cast<microseconds>(stop - start);

        start = high_resolution_clock::now(); // Get starting timepoint
        //Algorithm *algorithm1 = new Algorithm(text.data(), text.size(), pattern2, k, 10);
        AlgorithmInfAb *algorithm1 = new AlgorithmInfAb(text.data(), text.size(), pattern2, k);


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