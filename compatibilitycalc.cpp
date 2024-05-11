#include <iostream>   
#include <bitset>     
#include <sstream>    
#include <string>     
#include <unordered_map>    

using namespace std;

//bitset time of day
unordered_map<string, int> timeToBitMap = {
    {"00:00-01:00", 0}, {"01:00-02:00", 1}, {"02:00-03:00", 2}, {"03:00-04:00", 3}, {"04:00-05:00", 4}, {"05:00-06:00", 5},
    {"06:00-07:00", 6}, {"07:00-08:00", 7}, {"08:00-09:00", 8}, {"09:00-10:00", 9}, {"10:00-11:00", 10}, {"11:00-12:00", 11},
    {"12:00-13:00", 12}, {"13:00-14:00", 13}, {"14:00-15:00", 14}, {"15:00-16:00", 15}, {"16:00-17:00", 16}, {"17:00-18:00", 17},
    {"18:00-19:00", 18}, {"19:00-20:00", 19}, {"20:00-21:00", 20}, {"21:00-22:00", 21}, {"22:00-23:00", 22}, {"23:00-24:00", 23}
};



// Convert a time to a bit position
int timeToBit(const string& time) {
    if (timeToBitMap.find(time) != timeToBitMap.end()) {
        return timeToBitMap[time];
    } else {
        throw invalid_argument("time bad");
    }
}

// Convert a comma-separated list of times into a 24-bit bitset
bitset<24> timesToBitset(const string& timesList) {
    bitset<24> result;
    istringstream stream(timesList);
    string time;

    // Extract times from the stream, trimming spaces
    while (getline(stream, time, ',')) {
        time.erase(time.find_last_not_of(" \t\n\r\f\v") + 1); // Trim whitespace
        result.set(timeToBit(time)); // Set the bit for the corresponding time
    }

    return result;
}


//bitset for days of week
// Mapping days of the week to bit positions
unordered_map<string, int> dayToBitMap = {
    {"Monday", 6},
    {"Tuesday", 5},
    {"Wednesday", 4},
    {"Thursday", 3},
    {"Friday", 2},
    {"Saturday", 1},
    {"Sunday", 0}
};

// Converts inputted day to bit
int dayToBit(const string& day) {
    if (dayToBitMap.find(day) != dayToBitMap.end()) {
        return dayToBitMap[day];
    } else {
        throw invalid_argument("day no exis");
    }
}

// Convert that into big fat bitset
bitset<7> daysToBitset(const string& daysList) {
    bitset<7> result;
    istringstream stream(daysList);
    string day;

    // Taking text from the stream, removes commas, and puts in day
    while (getline(stream, day, ',')) {
        day.erase(day.find_last_not_of(" \t\n\r\f\v") + 1); // Trims whitespace
        result.set(dayToBit(day)); // Set the correct bit position
    }

    return result; 
}

class Preferences {

private:
    int ageWeight;
    int genderWeight;
    int uniWeight;
    int majorWeight;
    int studytimeWeight;
    int modeWeight;
    int daysOfWeekWeight;
    
public:
    Preferences(): 
        ageWeight(6), genderWeight(3), uniWeight(5), majorWeight(7), 
        studytimeWeight(8), modeWeight(8), daysOfWeekWeight(8) {}

    // Functions for calculating weights
    /* Preferences; assigning weights out of 10; completely eyeballing. 
    Technically, they aren't out of 10 for considering total score, y'know. 
    It's just to give us perspective. */

    // Age weight with a margin of +- 2
    int findAgeWeight(int myAge, int otherAge) {
        int ageDifference = abs(myAge - otherAge);

        if (ageDifference <= 2) {
            return ageWeight; 
        } 
        return 0; 
    }

    // Gender weight: 3 choices
    int findGenderWeight(const int& myGender, const int& otherGender) {
        return (myGender == otherGender) ? genderWeight : 0;
    }

    // Mode weight: Only 2 options; IRL or VC. Matches directly
    int findModeWeight(const int& myMode, const int& otherMode) {
        return (myMode == otherMode) ? modeWeight : 0;
    }

    // Uni weight
    int findUniWeight(const int& myUni, const int& otherUni) {
        return (myUni == otherUni) ? uniWeight : 0;
    }

    // Major weight
    int findMajorWeight(const int& myMajor, const int& otherMajor) {
        return (myMajor == otherMajor) ? majorWeight : 0;
    }

    // Day weight: Choose as many days as they want, then compare.
    int findDaysOfWeekWeight(const string& myDaysList, const string& otherDaysList) {
        bitset<7> myBitset = daysToBitset(myDaysList);
        bitset<7> otherBitset = daysToBitset(otherDaysList);

        bitset<7> commonDays = myBitset & otherBitset; 

        for (int i = 0; i < 7; ++i) {
            if (commonDays.test(i)) { 
                return daysOfWeekWeight; 
            }
        }
        return 0; 
    }

    // Study time weight
    int findStudyTimeWeight(const string& myTimeList, const string& otherTimeList) {
        bitset<24> myTimeBitset = timesToBitset(myTimeList);
        bitset<24> otherTimeBitset = timesToBitset(otherTimeList);

        bitset<24> commonTimes = myTimeBitset & otherTimeBitset;

        for (int i = 0; i < 24; ++i) {
            if (commonTimes.test(i)) {
                return studytimeWeight;
            }
        }
        return 0;
    }

    // Calculates the compatibility score
    int calculateCompatibilityScore(int myAge, int otherAge, int myGender, int otherGender, int myUni, int otherUni, int myMajor, int otherMajor, int myTime, int otherTime, int myMode, int otherMode, const string& myDaysList, const string& otherDaysList, int fullWeight) {
        int ageScore = findAgeWeight(myAge, otherAge);
        int genderScore = findGenderWeight(myGender, otherGender);
        int uniScore = findUniWeight(myUni, otherUni);
        int majorScore = findMajorWeight(myMajor, otherMajor);
        int studytimeScore = findStudyTimeWeight(myTimeList, otherTimeList);
        int modeScore = findModeWeight(myMode, otherMode);
        int dayScore = findDaysOfWeekWeight(myDaysList, otherDaysList);

        int compatibility = ageScore + genderScore + uniScore + majorScore + studytimeScore + modeScore + dayScore;

        return compatibility;
    }
};

