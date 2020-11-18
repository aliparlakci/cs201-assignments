#include <iostream>
#include <string>
#include "strutils.h"

using namespace std;

string scanMultipleWords();
int startsWith(string s, string prefix);
int endsWith(string s, string suffix);
int hasInMiddle(string s, string search);
int contains(string s, string search);
bool isProperlyFormatted(string s);
string getNextWord(string sentence, int index);
void search(string source, string search);
void printFound(int index, string word);

int main()
{
    string sourceString;
    string searchString;

    do
    {
        cout << "Enter source string: ";
        sourceString = scanMultipleWords();

    } while (!isProperlyFormatted(sourceString));

    do
    {
        cout << "Enter search string: ";
        cin >> searchString;

        search(sourceString, searchString);

    } while (UpperString(searchString) != "QUIT");

    return 0;
}

void search(string source, string search)
{
    bool starts = endsWith(search, "+") >= 0;
    bool ends = endsWith(search, ".") >= 0;
    bool any = endsWith(search, "**") >= 0;
    bool middle = endsWith(search, "*") >= 0 && !any;

    if (starts || ends || middle)
    {
        search = search.substr(0, search.length() - 1);
    }
    else if (any)
    {
        search = search.substr(0, search.length() - 2);
    }

    string word;
    string partialWord;
    bool isNewWord = true;
    int index = 0;
    int position = -1;

    if (starts || ends || middle || any)
    {
        while (index < source.length())
        {
            partialWord = getNextWord(source, index);
            if (isNewWord)
            {
                word = partialWord;
            }

            if (starts && isNewWord)
            {
                position = startsWith(partialWord, search);
            }
            else if (ends)
            {
                position = endsWith(partialWord, search);
            }
            else if (any)
            {
                position = contains(partialWord, search);
            }
            else if (middle)
            {
                position = hasInMiddle(partialWord, search);
                if (!isNewWord)
                {
                    int positionStart = startsWith(partialWord, search);
                    position = positionStart >= 0 ? positionStart : position;
                }
            }

            if (position >= 0)
            {
                printFound(index + position, word);
                index += position + 1;
                isNewWord = false;
                position = -1;
            }
            else
            {
                index += partialWord.length() + 1;
                isNewWord = true;
            }
        }
    }
}

bool isProperlyFormatted(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9') || s[i] == ' ')
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

int endsWith(string s, string suffix)
{

    if ((int)(s.length() - suffix.length()) < 0)
    {
        return -1;
    }
    else if (s.substr(s.length() - suffix.length()) == suffix)
    {
        return s.length() - suffix.length();
    }
    else
    {
        return -1;
    }
}

int startsWith(string s, string prefix)
{
    if ((int)(s.length() - prefix.length()) < 0)
    {
        return -1;
    }
    else if (s.substr(0, prefix.length()) == prefix)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int hasInMiddle(string s, string search)
{
    if (startsWith(s, search) >= 0 || endsWith(s, search) >= 0)
    {
        return -1;
    }
    return contains(s, search);
}

int contains(string s, string search)
{
    int position = s.find(search);
    if (position != string::npos)
    {
        return position;
    }
    return -1;
}

void printFound(int index, string word)
{
    cout << "index: " << index << " word: " << word << endl;
}

string getNextWord(string sentence, int index)
{
    string word;
    for (int i = index; i < sentence.length(); i++)
    {
        if (sentence.at(i) == ' ')
        {
            return sentence.substr(index, i - index);
        }
    }
    return sentence.substr(index, sentence.length() - index);
}