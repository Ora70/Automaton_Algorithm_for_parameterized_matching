//
// Created by User on 25/05/2021.
//
#include "CreateData.h"

list<vector<size_t>> create_p_match(vector<size_t> original, unsigned int num_copies) {
    list<vector<size_t>> p_matches;
    srand((unsigned) time(0));
    for (unsigned int i=0; i < num_copies; i++) {
        vector<size_t> match;
        int shift = (rand() % 35);
        for(const auto& value: original) {
            match.push_back(value+shift);
        }
        p_matches.push_back(match);
    }
    return p_matches;
}

