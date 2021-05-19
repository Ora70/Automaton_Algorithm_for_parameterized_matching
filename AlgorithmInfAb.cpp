
#include <unordered_map>
#include "AlgorithmInfAb.h"

AlgorithmInfAb::AlgorithmInfAb(unsigned int *text, unsigned long len_t, unsigned int *pattern, unsigned long len_p) {
    this->pattern = pattern;
    this->text = text;
    this->len_p = len_p;
    this->len_t = len_t;
    this->createA();
    this->createAutomat();
}

void AlgorithmInfAb::createA() {
    this->a = new long unsigned int[len_p];
    unordered_map<unsigned int, long unsigned int> lastSeen;
    long unsigned int j;
    for (j = 0; j < len_p; j++) {
        unsigned int letter = pattern[j];
        auto key = lastSeen.find(letter); //check if letter in the map
        if (key == lastSeen.end()) { //letter not seen before
            a[j] = j;
        } else {
            a[j] = key ->second;
        }
        lastSeen[letter] = j; //update the last time so far the letter was seen to be j
    }
}

bool AlgorithmInfAb::compareAutomat(unsigned int j, unsigned int i) {
    if (a[i] == i || i - a[i] > j) { //new letter
        if (a[j] == j) { //also a new letter
            return true;
        } else { //for j not a new letter
            return false;
        }
    } else if ((i - a[i] <= j) && pattern[j] == pattern[j-i+a[i]]) { //old letter for both. same distance
        return true;
    }
    else {
        return false;
    }
}

void AlgorithmInfAb::createAutomat() {
    this->automat = new long unsigned int[len_p+1];
    long unsigned int i, j;
    //fail arrow points to 0 in first
    automat[0] = automat[1] = 0;
    for (i = 2; i < len_p+1; i++) {
        j = i - 1;
        while (true) {
            if (compareAutomat(automat[j], i-1)) {
                automat[i] = automat[j] + 1;
                break;
            } else {
                //reached the beginning of automat. fail arrow points to 0
                if (automat[j] == 0) {
                    automat[i] = 0;
                    break;
                } else {
                    j = automat[j];
                }
            }
        }
    }
}


void AlgorithmInfAb::updateLastSeen(unsigned long i) {
    if (i >= len_p) {
        //check if need to remove an old letter
        unsigned int letter = text[i - len_p];
        if (lastSeenT[letter] == i - len_p) { //need to remove
            lastSeenT.erase(letter);
        }
    }
    lastSeenT[text[i]] = i; //add new letter to map
}

bool AlgorithmInfAb::compareAlgorithm(unsigned int j, unsigned int i) { // j in text. i in pattern
    auto seenInText = lastSeenT.find(text[j]);
    //first time the letter was seen in pattern
    if (a[i] == i && (seenInText == lastSeenT.end() || seenInText->second < j - i)) {
        return true;
    }
        //not the first time the letter was seen in the patttern
    else if (a[i] != i && text[j] == text[j-i+a[i]]) {
        return true;
    } else {
        return false;
    }
}

list<unsigned long> AlgorithmInfAb::runAlgorithm() {
    list <long unsigned int> matches; //list where there are matches
    unsigned long int j = 0, i = 0; //j position in automat. i position in text
    while (i <len_t) {
        if (compareAlgorithm(i, j)) {
            updateLastSeen(i);
            j++;
            i++;
            if (j == len_p) { //reached the end of automat - found a match
                j = automat[j];
                matches.push_back(i - len_p);
            }
        } else { //no match. fail arrow in automat
            if (j == 0) { //if j == 0 than always i moves forward
                updateLastSeen(i);
                i++;
            }
            j = automat[j];
        }
    }
    return matches;
}