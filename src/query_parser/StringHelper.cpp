#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <regex>

using namespace std;

namespace StringHelper {
    void replace(string &inpString, string patternString, string replacementString) {
        regex pattern(patternString);
        string outString;
        outString.reserve(inpString.size());
        regex_replace(back_insert_iterator<string>(outString), inpString.cbegin(), inpString.cend(), pattern, replacementString);
        inpString = outString;
    }

    vector<string> split(string inpString, char delimeter) {
        vector<string> stringVector;
        istringstream stringStream(inpString);
        string token;

        while (getline(stringStream, token, delimeter)) {
            stringVector.push_back(token);
        }

        return stringVector;
    }

    string getFirstWord(string inpString) {
        return inpString.substr(0, inpString.find(" "));
    }

    void removeFirstWord(string &inpString) {
        inpString = inpString.substr(inpString.find(" ") + 1);
    }

    void toUpperCase(string &inpString) {
        transform(inpString.begin(), inpString.end(), inpString.begin(), ::toupper);
    }

    string getUpperString(string inpString) {
        transform(inpString.begin(), inpString.end(), inpString.begin(), ::toupper);
        return inpString;
    }
}