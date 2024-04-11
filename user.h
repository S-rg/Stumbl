class User {
    private:
        //Basic Info
        string name;
        string pronouns;
        string bio;

        //User Profile
        int age;
        int gender;
        int mode; 
        int uniId;
        int majorId;
        int studyDays;
        int studyTimes;

        //User Preferences
        int ageWeight;
        int genderWeight;
        int modeWeight;
        int uniWeight;
        int majorWeight;
        int daysWeight;
        int timesWeight;

    public:
        User() {};
        User(string, string, string, int, int, int, int, int, int, int) {};

        int getAgeWeight() {};
        int getGenderWeight() {};
        int getModeWeight() {};
        int getUniWeight() {};
        int getMajorWeight() {};
        int getDaysWeight() {};
        int getTimesWeight() {};

        int calculateCompactibilityScore(User &) {};
};