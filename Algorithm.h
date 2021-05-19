#ifndef PROJECT_ALGORITHM_H
#define PROJECT_ALGORITHM_H

#include <list>
#include <iostream>
using namespace std;


class Algorithm {
    unsigned int *text;
    unsigned int *pattern;
    long unsigned int len_t;
    long unsigned int len_p;
    long unsigned int *a;
    long unsigned int *automat;
    long unsigned int *lastSeenT;
    void createA(int size_ab);
    void createAutomat();
    bool compareAutomat(unsigned int j , unsigned int i);
    bool compareAlgorithm(unsigned int j , unsigned int i);

public:
    Algorithm(unsigned int *text, long unsigned int len_t, unsigned int *pattern, long unsigned int len_p, int size_ab);
    list <long unsigned int> runAlgorithm();

};


#endif //PROJECT_ALGORITHM_H
