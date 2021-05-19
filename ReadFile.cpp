//
// Created by User on 19/05/2021.
//

#include "ReadFile.h"

vector<unsigned int> readFile(string filename) {
    vector<unsigned int> arr;
    // Create a text string, which is used to output the text file
    string temp;

    // Read from the text file
    ifstream myfile(filename);

    char letter;

    if (myfile.is_open()) {
        while (!myfile.eof()) {
            myfile >> letter;
            arr.push_back((unsigned int)letter - '0');

        }
    }
    arr.pop_back();

    // Close the file
    myfile.close();
    return arr;
}

vector<unsigned int> readDNA(string filename) {
    vector<unsigned int> arr;
    // Create a text string, which is used to output the text file
    string temp;
    // Read from the text file
    ifstream myfile(filename);
    char letter;
    if (myfile.is_open()) {
        while (!myfile.eof()) {
            myfile >> letter;
            switch (letter) {
                case 'A':
                    arr.push_back(1);
                    break;
                case 'C':
                    arr.push_back(2);
                    break;
                case 'G':
                    arr.push_back(3);
                    break;
                case 'T':
                    arr.push_back(4);
                    break;
                default:
                    break;
            }
        }
    }
    arr.pop_back();

    myfile.close();
    return arr;

}
