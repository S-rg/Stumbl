#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <cstdlib>

using namespace std;

const string userDataFile = "userData.csv";
const string passwordFile = "password.csv";

const unordered_map<string, int> dayToBitMap = {
    {"Monday", 6},
    {"Tuesday", 5},
    {"Wednesday", 4},
    {"Thursday", 3},
    {"Friday", 2},
    {"Saturday", 1},
    {"Sunday", 0}
};

class User {
    protected:

        //Basic Info
        string name;
        string pronouns;
        string bio;
        int uid;

        //secret secret
        string password;

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
        static int id_counter;  

        User(); // no values given
        User(string, string, string, string, int, int, int, int, int, int, int); //only bio data
        User(string, string, string, string, int, int, int, int, int, int, int, int, int, int, int, int, int, int); // all weights

        string getName();
        string getPronouns();
        string getBio();
        int getId();

        int getAge();
        int getGender();
        int getMode(); 
        int getUniId();
        int getMajorId();
        int getStudyDays();
        int getStudyTimes();

        int getAgeWeight();
        int getGenderWeight();
        int getModeWeight();
        int getUniWeight();
        int getMajorWeight();
        int getDaysWeight();
        int getTimesWeight();

        static User login(string);
        void logout();
        static User registerUser();
        void writeToCSV();

        void swipeLeft(User &);
        void swipeRight(User &);
};

class Centroid : public User {
    public:
        Centroid() : User() {};
};

class Cluster {
    public:
        Centroid c;
        User* users;

        Cluster();
}

int User::id_counter = 0;

User::User() {
    uid = ++id_counter;
    name = "Test User " + to_string(id_counter);
    pronouns = "Rather Not Say";
    bio = "";

    age = 0;
    gender = 0;
    mode = 0;
    uniId = 0;
    majorId = 0;
    studyDays = 0;
    studyTimes = 0;

    ageWeight = 0;
    genderWeight = 0;
    modeWeight = 0;
    uniWeight = 0;
    majorWeight = 0;
    daysWeight = 0;
    timesWeight = 0;
}

User::User(string name, string password, string pronouns, string bio, int age, int gender, int mode, int uniId, int majorId, int studyDays, int studyTimes) {
    this->uid = ++id_counter;
    this->name = name;
    this->pronouns = pronouns;
    this->bio = bio;

    this->password = password;

    this->age = age;
    this->gender = gender;
    this->mode = mode;
    this->uniId = uniId;
    this->majorId = majorId;
    this->studyDays = studyDays;
    this->studyTimes = studyTimes;

    ageWeight = 0;
    genderWeight = 0;
    modeWeight = 0;
    uniWeight = 0;
    majorWeight = 0;
    daysWeight = 0;
    timesWeight = 0;
}

User::User(string name, string password, string pronouns, string bio, int age, int gender, int mode, int uniId, int majorId, int studyDays, int studyTimes, int ageWeight, int genderWeight, int modeWeight, int uniWeight, int majorWeight, int daysWeight, int timesWeight) {
    this->uid = ++id_counter;
    this->name = name;
    this->pronouns = pronouns;
    this->bio = bio;

    this->password = password;

    this->age = age;
    this->gender = gender;
    this->mode = mode;
    this->uniId = uniId;
    this->majorId = majorId;
    this->studyDays = studyDays;
    this->studyTimes = studyTimes;

    this->ageWeight = ageWeight;
    this->genderWeight = genderWeight;
    this->modeWeight = modeWeight;
    this->uniWeight = uniWeight;
    this->majorWeight = majorWeight;
    this->daysWeight = daysWeight;
    this->timesWeight = timesWeight;
};

string User::getName() {return this->name;}
string User::getPronouns() {return this->pronouns;}
string User::getBio() {return this->bio;}
int User::getId() {return this->uid;}

int User::getAge() {return this->age;}
int User::getGender() {return this->gender;}
int User::getMode() {return this->mode;}
int User::getUniId() {return this->uniId;}
int User::getMajorId() {return this->majorId;}
int User::getStudyDays() {return this->studyDays;}
int User::getStudyTimes() {return this->studyTimes;}

int User::getAgeWeight() {return this->ageWeight;}
int User::getGenderWeight() {return this->genderWeight;}
int User::getModeWeight() {return this->modeWeight;}
int User::getUniWeight() {return this->uniWeight;}
int User::getMajorWeight() {return this->majorWeight;}
int User::getDaysWeight() {return this->daysWeight;}
int User::getTimesWeight() {return this->timesWeight;}

User User::registerUser() {
    string name, password, pronouns, bio;
    int age, gender, mode, uniId, majorId, studyDays, studyTimes;

    cout << "Enter name: ";
    cin >> name;

    cout << "\nEnter password: ";
    cin >> password;
    cout << "\nEnter pronouns: ";
    cin >> pronouns;
    cout << "\nEnter bio: ";
    cin >> bio;
    cout << "\nEnter age: ";
    cin >> age;
    cout << "\nEnter gender";
    cin >> gender;
    cout << "\nEnter mode: ";
    cin >> mode;
    cout << "\nEnter university ID: ";
    cin >> uniId;
    cout << "\nEnter major ID: ";
    cin >> majorId;
    cout << "\nEnter study days per week: ";
    cin >> studyDays;
    cout << "\nEnter study times per week: ";
    cin >> studyTimes;

    User newUser(name,password,pronouns,bio,age,gender,mode,uniId,majorId,studyDays,studyTimes);

    return newUser;
}

void User::writeToCSV() {
    ofstream file(userDataFile, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << userDataFile << " for writing." << endl;
        return;
    }
    file << uid << ",";
    file << name << ",";
    file << pronouns << ",";
    file << bio << ",";
    file << age << ",";
    file << gender << ",";
    file << mode << ",";
    file << uniId << ",";
    file << majorId << ",";
    file << studyDays << ",";
    file << studyTimes << ",";

    file << modeWeight << ",";
    file << uniWeight << ",";
    file << majorWeight << ",";
    file << daysWeight << ",";
    file << timesWeight;

    file << endl;
    file.close();


    ofstream file3(passwordFile, ios::app);
    if (!file3.is_open()) {
        cerr << "Error: Could not open file " << passwordFile << " for writing." << endl;
        return;
    }
    file3 << uid << ",";
    file3 << name << ",";
    file3 << password << ",";
    file3 << '\n';
    file3.close();
}

//populate the csv with random data
void populateCsv(int num) {
    string names[] = {"Alice", "Bob", "Charlie", "David", "Eve"};
    string passwords[] = {"password1", "password2", "password3", "password4", "password5"};
    string pronouns[] = {"she/her", "he/him", "they/them"};
    string bios[] = {"I love coding!", "Music is my passion.", "I'm a bookworm.", "I enjoy outdoor activities."};
    int ages[] = {18, 19, 20, 21, 22};
    int genders[] = {0, 1, 2};
    int modes[] = {0, 1};
    int uniIds[] = {1, 2, 3, 4, 5};
    int majorIds[] = {101, 102, 103, 104, 105};
    int studyDays[] = {3, 4, 5};
    int studyTimes[] = {1, 2, 3, 4};

    int randomNameIndex = rand() % 5;
    int randomPasswordIndex = rand() % 5;
    int randomPronounsIndex = rand() % 3;
    int randomBioIndex = rand() % 4;
    int randomAgeIndex = rand() % 5;
    int randomGenderIndex = rand() % 3;
    int randomModeIndex = rand() % 2;
    int randomUniIdIndex = rand() % 5;
    int randomMajorIdIndex = rand() % 5;
    int randomStudyDaysIndex = rand() % 3;
    int randomStudyTimesIndex = rand() % 4;
    int randomAgeWeight = rand() % 10 + 1; 
    int randomGenderWeight = rand() % 10 + 1;
    int randomModeWeight = rand() % 10 + 1;
    int randomUniWeight = rand() % 10 + 1;
    int randomMajorWeight = rand() % 10 + 1;
    int randomDaysWeight = rand() % 10 + 1;
    int randomTimesWeight = rand() % 10 + 1;

    for (int i = 0; i < num; i++) {
        int randomNameIndex = rand() % 5;
        int randomPasswordIndex = rand() % 5;
        int randomPronounsIndex = rand() % 3;
        int randomBioIndex = rand() % 4;
        int randomAgeIndex = rand() % 5;
        int randomGenderIndex = rand() % 3;
        int randomModeIndex = rand() % 2;
        int randomUniIdIndex = rand() % 5;
        int randomMajorIdIndex = rand() % 5;
        int randomStudyDaysIndex = rand() % 3;
        int randomStudyTimesIndex = rand() % 4;
        int randomAgeWeight = rand() % 10 + 1; 
        int randomGenderWeight = rand() % 10 + 1;
        int randomModeWeight = rand() % 10 + 1;
        int randomUniWeight = rand() % 10 + 1;
        int randomMajorWeight = rand() % 10 + 1;
        int randomDaysWeight = rand() % 10 + 1;
        int randomTimesWeight = rand() % 10 + 1;

        User temp(names[randomNameIndex], passwords[randomPasswordIndex], pronouns[randomPronounsIndex], bios[randomBioIndex], ages[randomAgeIndex], genders[randomGenderIndex], modes[randomModeIndex], uniIds[randomUniIdIndex], majorIds[randomMajorIdIndex], studyDays[randomStudyDaysIndex], studyTimes[randomStudyTimesIndex], randomAgeWeight, randomGenderWeight, randomModeWeight, randomUniWeight, randomMajorWeight, randomDaysWeight, randomTimesWeight);
        temp.writeToCSV();
    }
}

//removes all data from the csv
void depopulateCsv() {
    ofstream file1(userDataFile);
    file1.close();
    ofstream file2(passwordFile);
    file2.close();
}

int calculateCompactibilityScore(User &user1, User &user2) {};

//K MEANS
void clusterize(const vector<User>& users, const vector<Centroid> centroids, vector<int>& clusters) {
    for (int i = 0; i < users.size(); i++) {
        int minScore = clusters.front;
        int closestCluster = 0;
        for (int j = 1; j < centroids.size(); j++) {
            int score = calculateCompactibilityScore(users[i],centroids[j]);
            if (score < minScore) {
                minScore = score;
                closestCluster = j;
            }
        }
        clusters[i] = closestCluster;
    }
}

void updateCentroids(const vector<User>& users, vector<Centroid>& centroids, const vector<int>& clusters) {
    vector<vector<double>> weightSum(centroids.size(), vector<double>(14, 0));
    vector<int> count(centroids.size(),0)

    for (int i = 0; i < users.size(); ++i) {
        weightSum[clusters[i]][0] += users[i].getAgeWeight();
        weightSum[clusters[i]][1] += users[i].getGenderWeight();
        weightSum[clusters[i]][2] += users[i].getModeWeight();
        weightSum[clusters[i]][3] += users[i].getUniWeight();
        weightSum[clusters[i]][4] += users[i].getMajorWeight();
        weightSum[clusters[i]][5] += users[i].getDaysWeight();
        weightSum[clusters[i]][6] += users[i].getTimesWeight();

        weightSum[clusters[i]][7] += users[i].getAge();
        weightSum[clusters[i]][8] += users[i].getGender();
        weightSum[clusters[i]][9] += users[i].getMode();
        weightSum[clusters[i]][10] += users[i].getUniId();
        weightSum[clusters[i]][11] += users[i].getMajorId();
        weightSum[clusters[i]][12] += users[i].getStudyDays();
        weightSum[clusters[i]][13] += users[i].getStudyTimes();

        count[clusters[i]]++;
    } 
}

int main() {
    populateCsv(100);
    return 0;
}