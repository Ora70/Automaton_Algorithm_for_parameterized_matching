#include "Algorithm.h"

Algorithm::Algorithm(unsigned int *text, unsigned long len_t, unsigned int *pattern, unsigned long len_p, int size_ab) {
    this->pattern = pattern;
    this->text = text;
    this->len_p = len_p;
    this->len_t = len_t;
    this->createA(size_ab);
    this->createAutomat();
    //initialize array of letters that will hold the last position in the text where each letter was seen during scan
    // of the text. At first len_t+1 because no letter was seen yet.
    this->lastSeenT.resize(size_ab);
    for (int i = 0; i < size_ab; i++) {
        lastSeenT[i] = len_t+1;
    }
}
 /*
  * A in size len_p holds for each position i the biggest K<=i that the letter was in the pattern
  */
void Algorithm::createA(int size_ab) {
    this->a.resize(len_p);
    auto *lastSeen = new long unsigned int[size_ab]; //to remember the last position a letter was in
    for (int i = 0; i < size_ab; i++) { //initialize last time all letters where seen to len_p+1. meaning no letter was seen
        lastSeen[i] = len_p+1;
    }
    for (long unsigned int j = 0; j < len_p; j++) {
        unsigned int letter = pattern[j];
        if (lastSeen[letter] == len_p+1) { //first time the letter is seen
            a[j] = j;
        } else {
            a[j] = lastSeen[letter];
        }
        lastSeen[letter] = j; //update the last time so far the letter was seen to be j
    }
    delete[] lastSeen;

}

void Algorithm::createAutomat() {
    this->automat.resize(len_p+1);
    long unsigned int j;
    //fail arrow points to 0 in first
    automat[0] = automat[1] = 0;
    for (long unsigned int i = 2; i < len_p+1; i++) {
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

bool Algorithm::compareAutomat(unsigned int j, unsigned int i) {
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

bool Algorithm::compareAlgorithm(unsigned int j, unsigned int i) { // j in text. i in pattern
    //first time the letter was seen in pattern
    if (a[i] == i && (lastSeenT[text[j]] == len_t + 1 || lastSeenT[text[j]] < j - i)) {
        return true;
    //not the first time the letter was seen in the pattern
    } else if (a[i] != i && text[j] == text[j-i+a[i]]) {
        return true;
    } else {
        return false;
    }
}


list<unsigned long> Algorithm::runAlgorithm() {
    list <long unsigned int> matches; //list where there are matches
    unsigned long int j = 0, i = 0; //j position in automat. i position in text
    while (i <len_t) {
        if (compareAlgorithm(i, j)) {
            lastSeenT[text[i]] = i; //update the last position that the letter text[i] was seen to be i
            j++;
            i++;
            if (j == len_p) { //reached the end of automat - found a match
                j = automat[j];
                matches.push_back(i - len_p);
            }
        } else { //no match. fail arrow in automat
            if (j == 0) { //if j == 0 than always i moves forward
                lastSeenT[text[i]] = i; //update the last position that the letter text[i] was seen to be i
                i++;
            }
            j = automat[j];
        }

    }
    return matches;
}