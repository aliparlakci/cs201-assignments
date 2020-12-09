#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

void openFile(ifstream &file, string fileType);
int getMaxLength(istream &words);
vector<vector<string>> structureWordPool(istream &wordPool);
void correctFile(istream &file, vector<vector<string>> &wordPool);
vector<string> getCorrectWords(string word, vector<string> &wordPoolOfSameLength);
int getNumberOfSameChars(string s1, string s2);
void printMultipleMatch(vector<string> matches);
void printNoMatch(string word);
void printExactMatch(string word);
void ToLower(string &s);

int main()
{
    ifstream poolFile, inputFile;

    openFile(poolFile, "the word pool");
    openFile(inputFile, "the main text");

    vector<vector<string>> wordPool = structureWordPool(poolFile);
    cout << "You may find the results below:" << endl
         << endl;
    correctFile(inputFile, wordPool);

    poolFile.close();
    inputFile.close();

    return 0;
}

void openFile(ifstream &file, string fileType)
{
    string filePath;
    do
    {
        if (file.fail())
        {
            cout << "Cannot open " << fileType << " file." << endl;
            file.clear();
        }

        cout << "Please enter a filename for " << fileType << ": ";
        cin >> filePath;
        file.open(filePath.c_str());

    } while (file.fail());
}

int getMaxLength(istream &words)
{
    string line, word;
    int maxLength = 0;

    while (getline(words, line))
    {
        istringstream lineStream(line);
        while (lineStream >> word)
        {
            maxLength = word.length() > maxLength ? word.length() : maxLength;
        }
    }
    return maxLength;
}

vector<vector<string>> structureWordPool(istream &wordPool)
{
    int maxLength = getMaxLength(wordPool);
    wordPool.clear();
    wordPool.seekg(0);

    // ith index represents the i characters long string
    vector<vector<string>> structuredWords(maxLength + 1, vector<string>(0, ""));

    string line = "", word = "";

    while (getline(wordPool, line))
    {
        istringstream lineStream(line);
        while (lineStream >> word)
        {
            ToLower(word);
            structuredWords.at(word.length()).push_back(word);
        }
    }

    return structuredWords;
}

void correctFile(istream &file, vector<vector<string>> &wordPool)
{
    vector<string> wordPoolOfSameLength;
    string line, word;

    file.clear();
    file.seekg(0);

    while (getline(file, line))
    {
        istringstream lineStream(line);

        lineStream >> word;
        bool isSuccess = !lineStream.fail();

        while (isSuccess)
        {
            ToLower(word);

            if (wordPool.size() - 1 >= word.length())
            {
                wordPoolOfSameLength = wordPool.at(word.length());
            }
            else
            {
                vector<string> wordPoolOfSameLength(0);
            }

            vector<string> correctWords = getCorrectWords(word, wordPoolOfSameLength);

            if (correctWords.size() == 0)
            {
                printNoMatch(word);
            }
            else if (correctWords.size() == 1)
            {
                printExactMatch(correctWords.at(0));
            }
            else
            {
                printMultipleMatch(correctWords);
            }

            lineStream >> word;
            isSuccess = !lineStream.fail();
            cout << (isSuccess ? " " : "");
        }
        cout << endl;
    }
}

vector<string> getCorrectWords(string word, vector<string> &wordPoolOfSameLength)
{
    vector<string> correctWords;
    int maxSameChars = 0;
    int wordCount = 0;

    for (int i = 0; i < wordPoolOfSameLength.size(); i++)
    {
        int sameChars = getNumberOfSameChars(word, wordPoolOfSameLength.at(i));
        if (sameChars > maxSameChars)
        {
            maxSameChars = sameChars;
            vector<string> emptyCorrectWords;
            correctWords = emptyCorrectWords;
        }
        if (sameChars == maxSameChars)
        {
            correctWords.push_back(wordPoolOfSameLength.at(i));
        }
    }
    return correctWords;
}

int getNumberOfSameChars(string s1, string s2)
{
    ToLower(s1);
    ToLower(s2);
    int numberOfSameChars = 0;
    if (s1.length() == s2.length())
    {
        for (int i = 0; i < s1.length(); i++)
        {
            numberOfSameChars += s1.at(i) == s2.at(i) ? 1 : 0;
        }
        return (double)s1.length() / 2 >= s1.length() - numberOfSameChars ? numberOfSameChars : -1;
    }
    else
    {
        return -1;
    }
}

void printMultipleMatch(vector<string> matches)
{
    cout << "(";
    int i = 0;
    for (; i < matches.size() - 1; i++)
    {
        cout << matches.at(i);
        cout << ",";
    }
    cout << matches.at(i) << ")";
}

void printNoMatch(string word)
{
    cout << "{" << word << "}";
}

void printExactMatch(string word)
{
    cout << word;
}

void ToLower(string &s)
{
    int len = s.length();
    for (int k = 0; k < len; k++)
    {
        s[k] = tolower(s[k]);
    }
}