#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "favoriteseries.h"
#include "strutils.h"

using namespace std;

void run(vector<series> &seriesList, FavoriteSeries &favorites);
void printMenu();
void printAll(vector<series> &seriesList);
void add(vector<series> &seriesList, FavoriteSeries &favorites);
void remove(vector<series> &seriesList, FavoriteSeries &favorites);
void printFavoriteSeries(FavoriteSeries &favorites);
void printFavoriteActors(FavoriteSeries &favorites);
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

    run(seriesList, favorites);

    return 0;
}

void run(vector<series> &seriesList, FavoriteSeries &favorites)
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
            printAll(seriesList);
            break;

        case 2:
            add(seriesList, favorites);
            break;

        case 3:
            remove(seriesList, favorites);
            break;

        case 4:
            printFavoriteSeries(favorites);
            break;

        case 5:
            printFavoriteActors(favorites);
            break;

        case 6:
            isEnded = true;
            cout << "Goodbye, " << favorites.getFullName() << "!" << endl;
            break;

        default:
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
         << "Please enter your choice: ";
}

void printAll(vector<series> &seriesList)
{
    FavoriteSeries all("", "");

    for (int i = 0; i < seriesList.size(); i++)
    {
        all.addSeries(seriesList[i]);
    }

    all.displayFavoriteList();
}

void add(vector<series> &seriesList, FavoriteSeries &favorites)
{
    int code;
    cout << "Enter code for the TV series you want to add: ";
    cin >> code;

    series correspondingSeries;
    bool isFound = false;

    for (int i = 0; i < seriesList.size() && !isFound; i++)
    {
        if (seriesList[i].seriesCode == code)
        {
            correspondingSeries = seriesList[i];
            isFound = true;
        }
    }

    if (!isFound)
    {
        cout << favorites.getFullName() << ", there is no such TV series in the database!" << endl;
    }
    else if (favorites.ifExists(code))
    {
        cout << favorites.getFullName() << ", you can't add this TV series because you already added it!" << endl;
    }
    else if (favorites.isConflict(correspondingSeries))
    {
        cout << favorites.getFullName() << ", you can't add this TV series because of a date and slot conflict!" << endl;
    }
    else
    {
        favorites.addSeries(correspondingSeries);
        cout << favorites.getFullName() << ", ";
        cout << correspondingSeries.seriesName;
        cout << " added to your schedule." << endl;
    }
}

void remove(vector<series> &seriesList, FavoriteSeries &favorites)
{

    if (favorites.isListEmpty())
    {
        cout << favorites.getFullName() << ", you did not add any TV series yet!" << endl;
        return;
    }

    int code;
    cout << "Enter code for the TV series you want to drop: ";
    cin >> code;

    series correspondingSeries;
    bool isFound = false;

    for (int i = 0; i < seriesList.size() && !isFound; i++)
    {
        if (seriesList[i].seriesCode == code)
        {
            correspondingSeries = seriesList[i];
            isFound = true;
        }
    }

    if (!favorites.ifExists(code))
    {
        cout << favorites.getFullName() << ", there is no such TV series in your favorite list!" << endl;
    }
    else if (!isFound)
    {
        cout << favorites.getFullName() << ", there is no such TV series in the database!" << endl;
    }
    else
    {
        favorites.dropSeriesSorted(code);
        cout << favorites.getFullName() << ", ";
        cout << correspondingSeries.seriesName;
        cout << " has been dropped from your favorite list!" << endl;
    }
}

void printFavoriteSeries(FavoriteSeries &favorites)
{
    if (favorites.isListEmpty())
    {
        cout << favorites.getFullName() << ", you did not add any TV series yet!" << endl;
    }
    else
    {
        cout << favorites.getFullName() << ", here is your favorite TV series:" << endl;
        favorites.displayFavoriteList();
    }
}

void printFavoriteActors(FavoriteSeries &favorites)
{
    if (favorites.isListEmpty())
    {
        cout << favorites.getFullName() << ", you did not add any TV series yet!" << endl;
    }
    else
    {
        cout << favorites.getFullName() << ", here is your favorite actors:" << endl;
        favorites.displayFavoriteActors();
    }
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
                    lineStream >> word;
                    isEnd = lineStream.fail();
                    actor += isEnd ? "" : " ";
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