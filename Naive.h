#ifndef PROJECT_NAIVE_H
#define PROJECT_NAIVE_H

#include <list>
#include <vector>
#include <unordered_map>
using namespace std;

void naive(vector <size_t> &matches, size_t *text, size_t len_t, size_t *pattern, size_t len_p, int size_ab);
/*
 * function was used to check the overhead of remembering the position of each match
 */
size_t naiveNumMatches(size_t *text, size_t len_t, size_t *pattern, size_t len_p, int size_ab);
bool naiveCompare(size_t *p_match, size_t *t_match, size_t p, size_t t, int size_ab);

list <size_t> naiveInfAB(size_t *text, size_t len_t, size_t *pattern, size_t len_p);
bool naiveCompareInfAB(unordered_map<size_t, size_t> &p_match, unordered_map<size_t, bool> &t_match, size_t p, size_t t);


#endif //PROJECT_NAIVE_H
