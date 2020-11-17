#include <iostream>
#include <string>
#include "strutils.h"

using namespace std;

string scanMultipleWords();
bool endsWith(string s, string suffix);
bool isProperlyFormatted(string s);
string getWord(string &sentence);

int main()
{
    string sourceString;
    string searchString;

    do
    {
        cout << "Enter source string: ";
        sourceString = scanMultipleWords();

        if (UpperString(sourceString) != "QUIT" && isProperlyFormatted(sourceString))
        {
            cout << "Enter search string: ";
            cin >> searchString;
        }

    } while (UpperString(sourceString) != "QUIT");

    return 0;
}

bool isProperlyFormatted(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if ((s[i] >= 'A' && s[i] >= 'Z') || (s[i] >= 'a' && s[i] >= 'z') || (s[i] >= '0' && s[i] >= '9') || s[i] == ' ')
        {
            // character is valid
        }
        else
        {
            return false;
        }
    }
    return true;
}

string scanMultipleWords()
{
    string result = "";
    string input;
    while (cin >> input && LowerString(input) != "end")
    {
        result += input;
        result += " ";
    }
    return result;
}

bool endsWith(string s, string suffix)
{
    return s.substr(s.length() - suffix.length()) == suffix;
}

string getWord(string &sentence)
{
    string word;
    for (int i = 0; i < sentence.length() - 1; i++)
    {
        if (sentence.at(i + 1) == ' ')
        {
            word = sentence.substr(0, i + 1);
            sentence = sentence.substr(i + 1, sentence.length() - 1);
            StripWhite(sentence);
            return word;
        }
    }
    word = "" + sentence;
    sentence = "";
    return word;
}