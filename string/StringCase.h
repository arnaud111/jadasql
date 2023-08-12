//
// Created by a833444 on 08/08/2023.
//

#ifndef JADA_STRINGCASE_H
#define JADA_STRINGCASE_H

#include <string>

using namespace std;

class StringCase {

    static bool equal_insensitive(string s1, string s2) {

        if (s1.length() != s2.length()) return false;

        for (int i = 0; i < s1.length(); i++) {
            if (tolower(s1[i]) != tolower(s2[i])) return false;
        }

        return true;
    }
};

#endif //JADA_STRINGCASE_H
