
#ifndef PROJECT_ALGORITHMINFAB_H
#define PROJECT_ALGORITHMINFAB_H

#include <list>
#include <iostream>
#include <unordered_map>
using namespace std;


class AlgorithmInfAb {
    size_t *text;
    size_t *pattern;
    size_t len_t;
    size_t len_p;
    vector<size_t> a;
    vector<size_t> automat;
    unordered_map<size_t, size_t> lastSeenT;
    void createA();
    void createAutomat();
    bool compareAutomat(size_t j , size_t i);
    bool compareAlgorithm(size_t j , size_t i);
    void updateLastSeen(size_t i);
public:
    AlgorithmInfAb(size_t *text, size_t len_t, size_t *pattern, size_t len_p);
    list <size_t> runAlgorithm();
};


#endif //PROJECT_ALGORITHMINFAB_H
