#ifndef PROJECT_NAIVE_H
#define PROJECT_NAIVE_H

#include <list>
#include <vector>
#include <unordered_map>
using namespace std;

list <long unsigned int> naive(unsigned int *text, long unsigned int len_t, unsigned int *pattern, long unsigned int len_p, int size_ab);
bool naiveCompare(unsigned int *p_match, unsigned int *t_match, unsigned int p, unsigned int t, int size_ab);

list <long unsigned int> naiveInfAB(unsigned int *text, long unsigned int len_t, unsigned int *pattern, long unsigned int len_p);
bool naiveCompareInfAB(unordered_map<unsigned int, long unsigned int> &p_match, unordered_map<unsigned int, bool> &t_match, unsigned int p, unsigned int t);


#endif //PROJECT_NAIVE_H
