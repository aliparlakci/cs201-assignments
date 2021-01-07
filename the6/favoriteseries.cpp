#include "favoriteseries.h"

FavoriteSeries::FavoriteSeries(string uName, string uSurname)
{
    vector<series> favSeries;

    userName = uName, userSurname = uSurname;
}

string FavoriteSeries::getFullName() const
{
    return userName + " " + userSurname;
}

void FavoriteSeries::addSeries(const series &givenSeries)
{
    favSeries.push_back(givenSeries);
}

bool FavoriteSeries::ifExists(int seriesCode)
{
    bool doesExist = false;

    for (int i = 0; i < favSeries.size() & !doesExist; i++)
    {
        if (favSeries[i].seriesCode == seriesCode)
        {
            doesExist = true;
        }
    }

    return doesExist;
}

bool FavoriteSeries::isListEmpty() const
{
    return favSeries.size() == 0;
}

void FavoriteSeries::dropSeriesSorted(int code)
{
    bool isFound = false;
    for (int i = 0; i < favSeries.size() && !isFound; i++)
    {
        if (favSeries[i].seriesCode == code)
        {
            isFound = true;
            favSeries.erase(favSeries.begin() + i);
        }
    }
}

void FavoriteSeries::displayFavoriteList() const
{
    cout << "CODE,SERIES,EPISODE,DATE,SLOT" << endl;

    vector<episode> allEpisodes;

    for (int i = 0; i < favSeries.size(); i++)
    {
        for (int j = 0; j < favSeries[i].episodes.size(); j++)
        {
            allEpisodes.push_back(favSeries[i].episodes[j]);
        }
    }

    episode last;
    last.date = Date(0);

    episode smallest;
    Date forever(12, 30, 2100);

    for (int _ = 0; _ < allEpisodes.size(); _++)
    {
        smallest.date = forever;
        for (int i = 0; i < allEpisodes.size(); i++)
        {
            episode current = allEpisodes[i];

            int compareLast = isEarlier(last, current);
            int compareSmallest = isEarlier(current, smallest);

            if (compareLast == 1 && compareSmallest == 1)
            {
                smallest = current;
            }
            else
            {
                smallest = smallest;
            }
        }
        last = smallest;
        series matchedSeries;

        for (int i = 0; i < favSeries.size(); i++)
        {
            if (favSeries[i].seriesCode == last.seriesCode)
            {
                matchedSeries = favSeries[i];
            }
        }

        cout << matchedSeries.seriesCode << "," << matchedSeries.seriesName << ","
             << last.episodeName << "," << last.date.ToString() << ","
             << last.slot << endl;
    }
}

int FavoriteSeries::isEarlier(episode &a, episode &b) const
{
    string SLOTS[4] = {"MORNING", "AFTERNOON", "EVENING", "NIGHT"};

    if (a.date < b.date)
    {
        return 1;
    }
    else if (a.date == b.date)
    {
        int aIndex = -1, bIndex = -1;

        for (int index = 0; index < 4; index++)
        {
            aIndex = SLOTS[index] == a.slot ? index : aIndex;
            bIndex = SLOTS[index] == b.slot ? index : bIndex;
        }

        if (aIndex < bIndex)
        {
            return 1;
        }
        else if (aIndex == bIndex)
        {
            if (a.seriesCode < b.seriesCode)
            {
                return 1;
            }
            else if (a.seriesCode == b.seriesCode)
            {
                return -1;
            }
            else if (a.seriesCode > b.seriesCode)
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    return -1;
}

void FavoriteSeries::displayFavoriteActors() const
{
    vector<actor> favActors;

    for (int i = 0; i < favSeries.size(); i++)
    {
        for (int j = 0; j < favSeries[i].actorNames.size(); j++)
        {
            bool doesExist = false;
            for (int k = 0; k < favActors.size() && !doesExist; k++)
            {
                if (favActors[k].name == favSeries[i].actorNames[j])
                {
                    doesExist = true;
                    favActors[k].times += 1;
                }
            }

            if (!doesExist)
            {
                actor newActor;
                newActor.name = favSeries[i].actorNames[j];
                newActor.times = 1;
                favActors.push_back(newActor);
            }
        }
    }

    for (int i = 0; i < favActors.size(); i++)
    {
        int smallestIndex = i;
        actor smallestActor = favActors[i];
        for (int j = i + 1; j < favActors.size(); j++)
        {
            if (favActors[j].times > smallestActor.times)
            {
                smallestIndex = j;
                smallestActor = favActors[j];
            }
            else if (favActors[j].times == smallestActor.times)
            {
                if (favActors[j].name <= smallestActor.name)
                {
                    smallestIndex = j;
                    smallestActor = favActors[j];
                }
            }
        }
        actor tempActor = favActors[i];
        favActors[i] = favActors[smallestIndex];
        favActors[smallestIndex] = tempActor;
    }

    for (int i = 0; i < favActors.size(); i++)
    {
        cout << favActors[i].name << ": " << favActors[i].times << endl;
    }
}

bool FavoriteSeries::isConflict(const series &inSeries) const
{
    bool result = false;

    for (int i = 0; i < favSeries.size() && !result; i++)
    {
        for (int j = 0; j < favSeries[i].episodes.size() && !result; j++)
        {
            for (int k = 0; k < inSeries.episodes.size() && !result; k++)
            {
                episode favEpisode = favSeries[i].episodes[j];
                episode inEpisode = inSeries.episodes[k];

                if (inEpisode.date == favEpisode.date &&
                    inEpisode.slot == favEpisode.slot)
                {
                    result = true;
                }
            }
        }
    }

    return result;
}