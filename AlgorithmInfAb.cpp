
#include <unordered_map>
#include "AlgorithmInfAb.h"

AlgorithmInfAb::AlgorithmInfAb(size_t *text, size_t len_t, size_t *pattern, size_t len_p) {
    this->pattern = pattern;
    this->text = text;
    this->len_p = len_p;
    this->len_t = len_t;
    this->createA();
    this->createAutomat();
}

void AlgorithmInfAb::createA() {
    this->a.resize(len_p);
    unordered_map<size_t, size_t> lastSeen;
    for (size_t j = 0; j < len_p; j++) {
        size_t letter = pattern[j];
        auto key = lastSeen.find(letter); //check if letter in the map
        if (key == lastSeen.end()) { //letter not seen before
            a[j] = j;
        } else {
            a[j] = key ->second;
        }
        lastSeen[letter] = j; //update the last time so far the letter was seen to be j
    }
}

bool AlgorithmInfAb::compareAutomat(size_t j, size_t i) {
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
    this->automat.resize(len_p+1);
    //fail arrow points to 0 in first
    automat[0] = automat[1] = 0;
    for (long unsigned int i = 2; i < len_p+1; i++) {
        size_t j = i - 1;
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


void AlgorithmInfAb::updateLastSeen(size_t i) {
    if (i >= len_p) {
        //check if need to remove an old letter
        size_t letter = text[i - len_p];
        if (lastSeenT[letter] == i - len_p) { //need to remove
            lastSeenT.erase(letter);
        }
    }
    lastSeenT[text[i]] = i; //add new letter to map
}

bool AlgorithmInfAb::compareAlgorithm(size_t j, size_t i) { // j in text. i in pattern
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

list<size_t> AlgorithmInfAb::runAlgorithm() {
    list <size_t> matches; //list where there are matches
    size_t j = 0, i = 0; //j position in automat. i position in text
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