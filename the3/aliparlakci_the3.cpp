#include <iostream>
#include <string>
#include "strutils.h"

using namespace std;

string scanMultipleWords();
bool startsWith(string s, string prefix);
bool endsWith(string s, string suffix);
bool hasInMiddle(string s, string search);
bool isProperlyFormatted(string s);
string getNextWord(string sentence, int &index);

int main()
{
    string sourceString;
    string searchString;

    string test = "alidir benim adım";
    int i = 0;
    while (i < test.length())
    {
        cout << getNextWord(test, i) << endl;
    }
    // do
    // {
    //     cout << "Enter source string: ";
    //     sourceString = scanMultipleWords();

    //     if (UpperString(sourceString) != "QUIT" && isProperlyFormatted(sourceString))
    //     {
    //         cout << "Enter search string: ";
    //         cin >> searchString;
    //     }

    // } while (UpperString(sourceString) != "QUIT");

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

bool startsWith(string s, string prefix)
{
    return s.substr(0, prefix.length()) == prefix;
}

bool hasInMiddle(string s, string search)
{
    if (s.find(search) == string::npos)
    {
        return false;
    }
    else
    {
        return !startsWith(s, search) && !endsWith(s, search);
    }
}

string getNextWord(string sentence, int &index)
{
    string word;
    for (int i = index; i < sentence.length(); i++)
    {
        if (sentence.at(i) == ' ')
        {
            word = sentence.substr(index, i - index);
            index = i + 1;
            return word;
        }
    }
    word = sentence.substr(index, sentence.length() - index);
    index = sentence.length();
    return word;
}