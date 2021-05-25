#include "Naive.h"

list <size_t> naiveInfAB(size_t *text, size_t len_t, size_t *pattern, size_t len_p) {
    list <size_t> matches; //list where there where matches
    //create maps to match letters in text and pattern. need 2 to make sure different letters do not get the same match
    unordered_map<size_t, size_t> p_match;
    unordered_map<size_t, bool> t_match;
    //for every position in the text find p-match
    for (size_t i = 0; i <= len_t-len_p; i++) {
        //clear maps for new use
        p_match.clear();
        t_match.clear();
        bool match = true;
        //check for each letter if is matched
        for (size_t j = 0; j < len_p; j++) {
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

bool naiveCompareInfAB(unordered_map<size_t, size_t> &p_match, unordered_map<size_t, bool> &t_match, size_t p, size_t t) {
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

list <size_t> naive(size_t *text, size_t len_t, size_t *pattern, size_t len_p, int size_ab) {
    list <size_t> matches; //list where there where matches
    //create arrays to match letters in text and pattern. need 2 to make sure different letters do not get the same match
    std::vector<size_t> p_match(size_ab), t_match(size_ab);

    //for every position in the text find p-match
    for (size_t i = 0; i <= len_t-len_p; i++) {
        //create arrays to match letters in text and pattern. need 2 to make sure different letters do not get the same match
        t_match.assign(size_ab, size_ab+1);
        p_match.assign(size_ab, size_ab+1);

        bool match = true;
        //check for each letter if is matched
        for (size_t j = 0; j < len_p; j++) {
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

bool naiveCompare(size_t *p_match, size_t *t_match, size_t p, size_t t, int size_ab) {
    if (p_match[p] == size_ab+1 && t_match[t] == size_ab+1) {
        p_match[p] = t;
        t_match[t] = p;
        return true;
    } else if (p_match[p] == t) {
        return true;
    } return false;
}