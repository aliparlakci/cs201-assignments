#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct Movie
{
    double rate;
    string name;
    string actor;
    int count;
};

vector<Movie> readRatings(ifstream &ratingsFile);
vector<vector<string>> getActors(ifstream &actorsFile);
void openFile(ifstream &file, string fileType);
bool isAlpha(char chr);
void ToUpper(string &s);
void swap(Movie &a, Movie &b);
int searchMovie(vector<Movie> &movies, Movie query);
void insertMovie(vector<Movie> &sortedMovies, Movie movieToBeAdded);
void onePassSort(vector<Movie> &sortedMovies);
void deleteMovie(vector<Movie> &movies, int index);
void updateMovie(vector<Movie> &movies, string title, string actor);
void updateMoviesWithActors(vector<Movie> &movies, vector<vector<string>> actorAndMovies);
void printSeries(vector<Movie> &movies);
void filterSeries(vector<Movie> &movies, double limit);
void addToFavorites(vector<Movie> &movies, vector<Movie> &favorites, string title);
bool searchMovieByTitle(vector<Movie> &movies, string title, Movie &foundMovie);
void run(vector<Movie> &movies, vector<Movie> &favorites);
void printMenu();
void printSeries(vector<Movie> &movies);
void filterSeries(vector<Movie> &movies, double limit);
void optionOne(vector<Movie> &movies);
void optionTwo(vector<Movie> &movies);
void optionThree(vector<Movie> &movies, vector<Movie> &favorites);
void optionFour(vector<Movie> &favorites);

int main()
{
    cout << "Welcome to Netflix TV Series Ratings Calculator!" << endl;

    ifstream actorsFile, ratingFile;

    openFile(actorsFile, "Series-Actor");
    openFile(ratingFile, "Rating");
    // actorsFile.open("actors_series.txt");
    // ratingFile.open("ratings.txt");

    vector<Movie> favorites;
    vector<Movie> movies = readRatings(ratingFile);
    updateMoviesWithActors(movies, getActors(actorsFile));

    run(movies, favorites);

    return 0;
}

void run(vector<Movie> &movies, vector<Movie> &favorites)
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
            optionOne(movies);
            break;

        case 2:
            cout << "---" << endl;
            optionTwo(movies);
            break;

        case 3:
            cout << "---" << endl;
            optionThree(movies, favorites);
            break;

        case 4:
            cout << "---" << endl;
            optionFour(favorites);
            break;

        case 5:
            cout << "---" << endl;
            isEnded = true;
            break;

        default:
            cout << "---" << endl;
            cout << "This is not a valid option!" << endl;
            break;
        }
    }
}

void printMenu()
{
    cout << "---" << endl
         << "MENU" << endl
         << "1. Print the series" << endl
         << "2. Search the series according to the rating" << endl
         << "3. Add the series to the favorite list" << endl
         << "4. Print the favorite list" << endl
         << "5. Exit" << endl
         << "---" << endl
         << "Enter your choice: ";
}

void optionOne(vector<Movie> &movies)
{
    printSeries(movies);
}

void optionTwo(vector<Movie> &movies)
{
    double rating;

    cout << "Please enter the minimum rating: ";
    cin >> rating;

    if (rating >= 0 && rating <= 10)
    {
        filterSeries(movies, rating);
    }
    else
    {
        cout << "This is not a valid rating!" << endl;
    }
}

void optionThree(vector<Movie> &movies, vector<Movie> &favorites)
{
    string title;

    cout << "Please enter the name of series: ";

    cin.clear();
    cin.ignore();
    getline(cin, title);

    ToUpper(title);

    addToFavorites(movies, favorites, title);
}

void optionFour(vector<Movie> &favorites)
{
    if (favorites.size() > 0)
    {
        printSeries(favorites);
    }
    else
    {
        cout << "Your favorite list is currently empty!" << endl;
    }
}

void printSeries(vector<Movie> &movies)
{
    Movie currentMovie;

    cout << "RANK,NAME,ACTOR,POINTS" << endl;

    for (int i = 0; i < movies.size(); i++)
    {
        currentMovie = movies.at(i);
        cout << i + 1 << "," << currentMovie.name << "," << currentMovie.actor << "," << currentMovie.rate << endl;
    }
}

void filterSeries(vector<Movie> &movies, double limit)
{
    Movie currentMovie;

    cout << "RANK,NAME,ACTOR,POINTS" << endl;

    int i = 0;

    while (i < movies.size() && movies.at(i).rate >= limit)
    {
        currentMovie = movies.at(i);
        cout << i + 1 << "," << currentMovie.name << "," << currentMovie.actor << "," << currentMovie.rate << endl;

        i++;
    }
}

void addToFavorites(vector<Movie> &movies, vector<Movie> &favorites, string title)
{
    Movie movieToBeAdded;

    if (searchMovieByTitle(movies, title, movieToBeAdded))
    {
        if (searchMovie(favorites, movieToBeAdded) > -1)
        {
            cout << "Your favorite list already have " << title << endl;
        }
        else
        {
            insertMovie(favorites, movieToBeAdded);
        }
    }
    else
    {
        cout << "There is no such TV series!" << endl;
    }
}

bool searchMovieByTitle(vector<Movie> &movies, string title, Movie &foundMovie)
{
    bool isFound = false;

    for (int i = 0; i < movies.size() && !isFound; i++)
    {
        if (movies.at(i).name == title)
        {
            isFound = true;
            foundMovie = movies.at(i);
        }
    }

    return isFound;
}

vector<vector<string>> getActors(ifstream &actorsFile)
{
    vector<vector<string>> actorsAndMovies;

    string line = "";

    while (getline(actorsFile, line))
    {
        istringstream lineStream(line);
        string word = "", title = "", actor = "";
        bool found = false;
        vector<string> actorAndMovie;

        while (!found && lineStream >> word)
        {
            ToUpper(word);

            if (word.at(word.length() - 1) == ';')
            {
                found = true;
                word = word.substr(0, word.length() - 1);
                actor += word;
            }
            else
            {
                actor += word;
                actor += " ";
            }
        }

        lineStream >> word;
        bool isSuccesful = !lineStream.fail();

        while (isSuccesful)
        {
            ToUpper(word);

            title += word;

            lineStream >> word;
            isSuccesful = !lineStream.fail();

            title += isSuccesful ? " " : "";
        }

        actorAndMovie.push_back(actor);
        actorAndMovie.push_back(title);
        actorsAndMovies.push_back(actorAndMovie);
    }

    return actorsAndMovies;
}

void updateMoviesWithActors(vector<Movie> &movies, vector<vector<string>> actorAndMovies)
{
    int size = actorAndMovies.size();

    for (int i = 0; i < size; i++)
    {
        updateMovie(movies, actorAndMovies[i][1], actorAndMovies[i][0]);
    }
}

void updateMovie(vector<Movie> &movies, string title, string actor)
{
    bool isFound = false;
    for (int i = 0; i < movies.size() && !isFound; i++)
    {
        Movie currentMovie = movies.at(i);

        if (currentMovie.name == title)
        {
            movies.at(i).actor = actor;
            isFound = true;
        }
    }
}

vector<Movie> readRatings(ifstream &ratingsFile)
{
    vector<Movie> movies;
    string line, title;
    double rate;

    while (getline(ratingsFile, line))
    {
        istringstream lineStream(line);
        Movie currentMovie;
        currentMovie.count = 1;

        lineStream >> currentMovie.rate;

        lineStream >> title;
        bool isSuccess = !lineStream.fail();

        while (isSuccess)
        {
            ToUpper(title);
            currentMovie.name += title;

            lineStream >> title;
            isSuccess = !lineStream.fail();
            currentMovie.name += isSuccess ? " " : "";
        }

        insertMovie(movies, currentMovie);
    }

    return movies;
}

void insertMovie(vector<Movie> &sortedMovies, Movie movieToBeAdded)
{
    int movieLocation = searchMovie(sortedMovies, movieToBeAdded);

    if (movieLocation > -1)
    {
        Movie oldMovie = sortedMovies[movieLocation];

        movieToBeAdded.count = oldMovie.count + 1;
        movieToBeAdded.rate = (oldMovie.count * oldMovie.rate + movieToBeAdded.rate) / (movieToBeAdded.count);

        deleteMovie(sortedMovies, movieLocation);
    }

    sortedMovies.push_back(movieToBeAdded);
    onePassSort(sortedMovies);
}

int searchMovie(vector<Movie> &movies, Movie query)
{
    int location = -1;
    for (int i = 0; i < movies.size() && location == -1; i++)
    {
        location = movies.at(i).name == query.name ? i : -1;
    }
    return location;
}

void deleteMovie(vector<Movie> &movies, int index)
{
    int size = movies.size();

    for (int i = index + 1; i < size; i++)
    {
        movies.at(i - 1) = movies.at(i);
    }

    movies.resize(size - 1);
}

void onePassSort(vector<Movie> &sortedMovies)
{
    Movie currentMovie, previousMovie;
    int size = sortedMovies.size();

    for (int i = size - 1; i > 0; i--)
    {
        currentMovie = sortedMovies.at(i);
        previousMovie = sortedMovies.at(i - 1);

        if (currentMovie.rate > previousMovie.rate)
        {
            swap(sortedMovies.at(i), sortedMovies.at(i - 1));
        }
        else if (currentMovie.rate == previousMovie.rate)
        {
            if (currentMovie.name < previousMovie.name)
            {
                swap(sortedMovies.at(i), sortedMovies.at(i - 1));
            }
        }
    }
}

void openFile(ifstream &file, string fileType)
{
    string filePath;
    do
    {
        if (file.fail())
        {
            cout << "Can not find the specified file." << endl;
            file.clear();
        }

        cout << "Please enter a filename for " << fileType << " file: ";
        cin >> filePath;
        file.open(filePath.c_str());

    } while (file.fail());
}

void ToUpper(string &s)
{
    int len = s.length();
    for (int k = 0; k < len; k++)
    {
        s[k] = toupper(s[k]);
    }
}

bool isAlpha(char chr)
{
    return (chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z');
}

void swap(Movie &a, Movie &b)
{
    Movie temp;
    temp = b;
    b = a;
    a = temp;
}