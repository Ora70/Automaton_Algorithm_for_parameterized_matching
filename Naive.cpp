//
// Created by User on 19/05/2021.
//

#include "Naive.h"

list <long unsigned int> naiveInfAB(unsigned int *text, long unsigned int len_t, unsigned int *pattern, long unsigned int len_p) {
    list <long unsigned int> matches; //list where there where matches
    long unsigned int i, j;
    //create maps to match letters in text and pattern. need 2 to make sure different letters do not get the same match
    unordered_map<unsigned int, long unsigned int> p_match;
    unordered_map<unsigned int, bool> t_match;
    //for every position in the text find p-match
    for (i = 0; i <= len_t-len_p; i++) {
        //empty maps for re-use
        p_match.clear();
        t_match.clear();
        bool match = true;
        //check for each letter if is matched
        for (j = 0; j < len_p; j++) {
            if (naiveCompareInfAB(p_match, t_match, pattern[j], text[i + j]) == false) {
                match = false;
                break;
            }
        }
        if (match) { //add position to list of matches
            matches.push_back(i);
        }
    }
    return matches;
}

bool naiveCompareInfAB(unordered_map<unsigned int, long unsigned int> &p_match, unordered_map<unsigned int, bool> &t_match, unsigned int p, unsigned int t) {
    auto p_key = p_match.find(p); //check if letter p in map
    auto t_key = t_match.find(t); //check if letter t in map
    if (p_key == p_match.end() && t_key == t_match.end()) { //both letters did not appear before
        p_match[p] = t;
        t_match[t] = true;
        return true;
    } else if (p_key!=p_match.end() && p_key->second == t) { //p is mapped to the letter t
        return true;
    } else {
        return false;
    }
}

list <long unsigned int> naive(unsigned int *text, long unsigned int len_t, unsigned int *pattern, long unsigned int len_p, int size_ab) {
    list <long unsigned int> matches; //list where there where matches
    long unsigned int i, j;
    //create arrays to match letters in text and pattern. need 2 to make sure different letters do not get the same match
    std::vector<unsigned int> p_match(size_ab), t_match(size_ab);

    //for every position in the text find p-match
    for (i = 0; i <= len_t-len_p; i++) {
        //create arrays to match letters in text and pattern. need 2 to make sure different letters do not get the same match
        t_match.assign(size_ab, size_ab+1);
        p_match.assign(size_ab, size_ab+1);

        bool match = true;
        //check for each letter if is matched
        for (j = 0; j < len_p; j++) {
            if (naiveCompare(p_match.data(), t_match.data(), pattern[j], text[i + j], size_ab) == false) {
                match = false;
                break;
            }
        }
        if (match) { //add position to list of matches
            matches.push_back(i);
        }
    }
    return matches;
}

bool naiveCompare(unsigned int *p_match, unsigned int *t_match, unsigned int p, unsigned int t, int size_ab) {
    if (p_match[p] == size_ab+1 && t_match[t] == size_ab+1) {
        p_match[p] = t;
        t_match[t] = p;
        return true;
    } else if (p_match[p] == t) {
        return true;
    } return false;
}