//
// Created by a833444 on 08/08/2023.
//

#ifndef JADA_STRINGPARSER_H
#define JADA_STRINGPARSER_H

#include <string>
#include <vector>

using namespace std;

class StringParser {

public:

    static vector<string> explode(string input, char val) {

        string tmp;
        vector<string> exploded;

        for (char i : input) {
            if (i == val) {
                if (tmp.length() > 0) exploded.push_back(tmp);
                tmp = "";
            } else {
                tmp.push_back(i);
            }
        }
        if (tmp.length() > 0) exploded.push_back(tmp);

        return exploded;
    }
};

#endif //JADA_STRINGPARSER_H
