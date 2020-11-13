#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

bool check_input(string color, double length, double width, double height);
void calculate(string color, double length, double width, double height, double &area, double &volume);
string compare(string colorA, string colorB, string metric, double quantityA, double quantityB);
void display(string color, double area, double volume);
void checkCubeAndDisplay(string color, double length, double width, double height);
string ToLower(string s);
string ToUpper(string s);

int main()
{
    string colorOfCuboidA, colorOfCuboidB;
    double widthA, widthB, heightA, heightB, lengthA, lengthB, areaA, areaB, volumeA, volumeB;

    cout.setf(ios::fixed);
    cout.precision(2);

    cout << "Hello! This program compares two cuboids..." << endl;

    cout << "Please enter colors for the two cuboids: ";
    cin >> colorOfCuboidA >> colorOfCuboidB;

    if (ToLower(colorOfCuboidA) != ToLower(colorOfCuboidB))
    {
        cout << "Please enter length, width and height of the " << colorOfCuboidA << " cuboid: ";
        cin >> lengthA >> widthA >> heightA;

        if (check_input(colorOfCuboidA, lengthA, widthA, heightA))
        {
            cout << "Please enter length, width and height of the " << colorOfCuboidB << " cuboid: ";
            cin >> lengthB >> widthB >> heightB;

            if (check_input(colorOfCuboidB, lengthB, widthB, heightB))
            {
                calculate(colorOfCuboidA, lengthA, widthA, heightA, areaA, volumeA);
                cout << endl;
                calculate(colorOfCuboidB, lengthB, widthB, heightB, areaB, volumeB);
                cout << endl;

                cout << "Comparison of the two cuboids:"
                     << endl
                     << compare(colorOfCuboidA, colorOfCuboidB, "volume", volumeA, volumeB)
                     << endl
                     << compare(colorOfCuboidA, colorOfCuboidB, "area", areaA, areaB)
                     << endl;
            }
        }
    }
    else
    {
        cout << "Color names cannot be the same, good bye..." << endl;
    }

    return 0;
}

bool check_input(string color, double length, double width, double height)
{
    if (length <= 0 || width <= 0 || height <= 0)
    {
        cout << "Invalid entry for " << color << " cuboid. Dimensions should be positive real numbers!" << endl;
        return false;
    }
    return true;
}

void checkCubeAndDisplay(string color, double length, double width, double height)
{
    cout << color << " cuboid is "
         << (length == height && height == width ? "a " : "not a ")
         << "cube." << endl;
}

void display(string color, double area, double volume)
{
    cout << "Results for the " << color << " cuboid:" << endl;
    cout << "Area: " << area << endl;
    cout << "Volume: " << volume << endl;
}

void calculate(string color, double length, double width, double height, double &area, double &volume)
{
    area = 2 * ((length * width) + (width * height) + (height * length));
    volume = length * height * width;

    display(color, area, volume);
    checkCubeAndDisplay(color, length, width, height);
}

string compare(string colorA, string colorB, string metric, double quantityA, double quantityB)
{
    string result = "";
    string winner = "";

    if (quantityA > quantityB)
    {
        winner = colorA;
    }
    else if (quantityA < quantityB)
    {
        winner = colorB;
    }

    if (winner != "")
    {
        result += winner;
        result += " has the largest ";
    }
    else
    {
        result += "Two cuboids have the same ";
    }

    result += metric;
    result += ".";

    return result;
}

string ToLower(string s)
{
    int len = s.length();
    for (int k = 0; k < len; k++)
    {
        s[k] = tolower(s[k]);
    }
    return s;
}

string ToUpper(string s)
{
    int len = s.length();
    for (int k = 0; k < len; k++)
    {
        s[k] = toupper(s[k]);
    }
    return s;
}