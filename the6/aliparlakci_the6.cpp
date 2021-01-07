#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "favoriteseries.h"
#include "strutils.h"

using namespace std;

void printMenu();
void mergeEpisodesAndSeries(const vector<episode> &episodesList, vector<series> &seriesList);
vector<series> readSeries(ifstream &seriesFile);
vector<episode> readEpisodes(ifstream &episodesFile);
Date parseDate(const string &givenDate);

int main()
{
    ifstream episodesFile, seriesFile;
    vector<episode> episodesList;
    vector<series> seriesList;

    episodesFile.open("episodes.txt");
    episodesList = readEpisodes(episodesFile);
    episodesFile.close();

    seriesFile.open("series.txt");
    seriesList = readSeries(seriesFile);
    seriesFile.close();

    mergeEpisodesAndSeries(episodesList, seriesList);

    string name, surname;
    cout << "Welcome to my favorite TV series schedule program!" << endl;
    cout << "Please, enter your name and surname: ";
    cin >> name >> surname;

    ToUpper(name);
    ToUpper(surname);

    FavoriteSeries favorites(name, surname);

    for (int i = 0; i < seriesList.size(); i++)
    {
        favorites.addSeries(seriesList[i]);
    }

    favorites.displayFavoriteActors();

    return 0;
}

void run(vector<series> &seriesList)
{
    int choice = 0;

    bool isEnded = false;

    while (!isEnded)
    {
        printMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "---" << endl;
            break;

        case 2:
            cout << "---" << endl;
            break;

        case 3:
            cout << "---" << endl;
            break;

        case 4:
            cout << "---" << endl;
            break;

        case 5:
            cout << "---" << endl;
            break;

        case 6:
            cout << "---" << endl;
            isEnded = true;
            break;

        default:
            cout << "---" << endl;
            cout << "Invalid option!" << endl;
            break;
        }
    }
}

void printMenu()
{
    cout << "---" << endl
         << "MENU" << endl
         << "1. Print all TV series" << endl
         << "2. Add TV series" << endl
         << "3. Drop TV series" << endl
         << "4. Print your favorite series with schedule" << endl
         << "5. Print all your favorite actors" << endl
         << "6. Exit" << endl
         << "---" << endl
         << "Enter your choice: ";
}

void mergeEpisodesAndSeries(const vector<episode> &episodesList, vector<series> &seriesList)
{
    for (int i = 0; i < episodesList.size(); i++)
    {
        for (int j = 0; j < seriesList.size(); j++)
        {
            if (episodesList[i].seriesCode == seriesList[j].seriesCode)
            {
                seriesList[j].episodes.push_back(episodesList[i]);
            }
        }
    }
}

vector<series> readSeries(ifstream &seriesFile)
{
    vector<series> seriesList;
    string word, line;

    while (getline(seriesFile, line))
    {
        istringstream lineStream(line);
        series currentSeries;

        lineStream >> currentSeries.seriesCode;

        lineStream >> word;
        bool isEnd = false;

        while (!isEnd)
        {
            ToUpper(word);

            if (word[word.size() - 1] == ';')
            {
                isEnd = true;
                currentSeries.seriesName += word.substr(0, word.size() - 1);
            }
            else
            {
                currentSeries.seriesName += word;
                currentSeries.seriesName += " ";
                lineStream >> word;
            }
        }

        while (lineStream >> word)
        {
            isEnd = false;

            string actor;

            while (!isEnd)
            {
                ToUpper(word);

                if (word[word.size() - 1] == ',')
                {
                    isEnd = true;
                    actor += word.substr(0, word.size() - 1);
                }
                else
                {
                    actor += word;
                    actor += " ";
                    lineStream >> word;
                    isEnd = lineStream.fail();
                }
            }

            currentSeries.actorNames.push_back(actor);
        }

        seriesList.push_back(currentSeries);
    }

    return seriesList;
}

vector<episode> readEpisodes(ifstream &episodesFile)
{
    vector<episode> episodes;
    string line, word, date, slot;

    while (getline(episodesFile, line))
    {
        istringstream lineStream(line);
        episode currentEpisode;

        lineStream >> currentEpisode.seriesCode;
        lineStream >> date;
        lineStream >> slot;

        ToUpper(slot);

        currentEpisode.episodeName = "";
        currentEpisode.date = parseDate(date);
        currentEpisode.slot = slot;

        lineStream >> word;
        bool isSuccess = !lineStream.fail();

        while (isSuccess)
        {
            ToUpper(word);
            currentEpisode.episodeName += word;

            lineStream >> word;
            isSuccess = !lineStream.fail();
            currentEpisode.episodeName += isSuccess ? " " : "";
        }

        episodes.push_back(currentEpisode);
    }

    return episodes;
}

Date parseDate(const string &givenDate)
{
    int d, m, y;

    int index = 0;
    char currentChar = givenDate[index];

    string month = "";
    while (currentChar != '/')
    {
        month += currentChar;
        index += 1;
        currentChar = givenDate[index];
    }
    m = atoi(month);
    index += 1;
    currentChar = givenDate[index];

    string day = "";
    while (currentChar != '/')
    {
        day += currentChar;
        index += 1;
        currentChar = givenDate[index];
    }
    d = atoi(day);
    index += 1;
    currentChar = givenDate[index];

    string year = "";
    while (index < givenDate.length())
    {
        year += currentChar;
        index += 1;
        currentChar = givenDate[index];
    }
    y = atoi(year);

    return Date(m, d, y);
}