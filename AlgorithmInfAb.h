
#ifndef PROJECT_ALGORITHMINFAB_H
#define PROJECT_ALGORITHMINFAB_H

#include <list>
#include <iostream>
#include <unordered_map>
using namespace std;


class AlgorithmInfAb {
    unsigned int *text;
    unsigned int *pattern;
    long unsigned int len_t;
    long unsigned int len_p;
    vector<long unsigned int> a;
    vector<long unsigned int> automat;
    unordered_map<unsigned int, long unsigned int> lastSeenT;
    void createA();
    void createAutomat();
    bool compareAutomat(unsigned int j , unsigned int i);
    bool compareAlgorithm(unsigned int j , unsigned int i);
    void updateLastSeen(long unsigned int i);
public:
    AlgorithmInfAb(unsigned int *text, long unsigned int len_t, unsigned int *pattern, long unsigned int len_p);
    list <long unsigned int> runAlgorithm();
};


#endif //PROJECT_ALGORITHMINFAB_H
