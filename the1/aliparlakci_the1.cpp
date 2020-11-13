#include <iostream>
#include <string>
using namespace std;

bool isValidGrade(string grade);

int main()
{
    string name, course, firstTime, newGrade;
    bool isFirstTime;

    cout << "Welcome to the Fall 2020-2021 Semester grading system. What is your name? ";
    cin >> name;

    cout << "Hello " << name << "! Please enter the name of the course to be processed: ";
    cin >> course;

    cout << "Hello " << name << "! If you take the " << course << " for the first time, enter YES otherwise NO: ";
    cin >> firstTime;

    if (firstTime == "YES")
    {
        isFirstTime = true;
    }
    else if (firstTime == "NO")
    {
        isFirstTime = false;
    }
    else
    {
        return 0;
    }

    if (isFirstTime)
    {
        string shoudlSwitch, grade;

        cout << "What is your grade from (A,B,C,D,F)? ";
        cin >> grade;

        if (isValidGrade(grade))
        {
        }
        else
        {
            cout << "Invalid grade selection. Goodbye..." << endl;
            return 0;
        }

        if (grade == "F")
        {
            newGrade = "U";
        }
        else
        {
            newGrade = "S";
        }

        cout << "Do you want to switch your grade from " << grade << " to " << newGrade << " (YES or NO)? ";
        cin >> shoudlSwitch;

        if (shoudlSwitch == "YES")
        {
        }
        else if (shoudlSwitch == "NO")
        {
            newGrade = grade;
        }
        else
        {
            cout << "Invalid grade selection. Goodbye..." << endl;
            return 0;
        }
    }
    else
    {
        string prevGrade, currGrade, chosenGrade;

        cout << "Please enter your previous grade from (A,B,C,D,F,S,U): ";
        cin >> prevGrade;

        if (isValidGrade(prevGrade) || prevGrade == "S" || prevGrade == "U")
        {
        }
        else
        {
            cout << "Invalid grade selection. Goodbye..." << endl;
            return 0;
        }

        cout << "Please enter your current grade from (A,B,C,D,F): ";
        cin >> currGrade;

        if (isValidGrade(currGrade))
        {
        }
        else
        {
            cout << "Invalid grade selection. Goodbye..." << endl;
            return 0;
        }

        cout << "Please enter the grade you want to choose from (A,B,C,D,F,S,U): ";
        cin >> chosenGrade;

        if (currGrade == "F")
        {
            if (prevGrade == "F" || prevGrade == "S")
            {
                if (chosenGrade != "F")
                {
                    string STUPID_SINGLE_COMMA = "";
                    if (prevGrade == "F")
                    {
                        STUPID_SINGLE_COMMA = ",";
                    }
                    cout << "Invalid grade selection. If you received " << prevGrade << " before" << STUPID_SINGLE_COMMA << " and fail this semester, you get F." << endl;
                    return 0;
                }
            }
            else
            {
                if (chosenGrade == "F" || chosenGrade == "U")
                {
                }
                else
                {
                    cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
                    return 0;
                }
            }
        }
        else
        {
            if (chosenGrade == "S" || chosenGrade == currGrade)
            {
            }
            else if (prevGrade == "U")
            {
                cout << "Invalid grade selection. If you received U before, you may choose S or current letter grade." << endl;
                return 0;
            }
            else
            {
                cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
                return 0;
            }
        }
        newGrade = chosenGrade;
    }

    cout << name << ", your final grade for " << course << " is " << newGrade << ". Goodbye..." << endl;

    return 0;
}

bool isValidGrade(string grade)
{
    return grade == "A" || grade == "B" || grade == "C" || grade == "D" || grade == "F";
}