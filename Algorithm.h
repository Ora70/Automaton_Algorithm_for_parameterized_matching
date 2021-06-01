#ifndef PROJECT_ALGORITHM_H
#define PROJECT_ALGORITHM_H

#include <list>
#include <iostream>
#include <vector>
using namespace std;


class Algorithm {
    size_t *text;
    size_t *pattern;
    size_t len_t;
    size_t len_p;
    vector<size_t> a;
    vector<size_t> automat;
    vector<size_t> lastSeenT;
    void createA(int size_ab);
    void createAutomat();
    bool compareAutomat(size_t j , size_t i);
    bool compareAlgorithm(size_t j , size_t i);

public:
    Algorithm(size_t *text, size_t len_t, size_t *pattern, size_t len_p, int size_ab);
    list <size_t> runAlgorithm();
    size_t runAlgorithmNumMatches();

};


#endif //PROJECT_ALGORITHM_H
