#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <limits>


using namespace std;

const string userDataFile = "userData.csv";
const string passwordFile = "password.csv";
const string swipingFile = "swiping.csv";

unordered_map<string, int> dayToBitMap = {
    {"Monday", 6},
    {"Tuesday", 5},
    {"Wednesday", 4},
    {"Thursday", 3},
    {"Friday", 2},
    {"Saturday", 1},
    {"Sunday", 0}
};
const string days_list[] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

unordered_map<string,int> uni_map {
    {"Plaksha",0},
    {"Ashoka",1},
    {"UIUC",2},
    {"UCLA",3},
    {"LSR",4},
    {"SRCC",5},
    {"NIFT",6},
    {"Purdue",7}
};

unordered_map<string,int> major_map {
    {"Computer Engineering",0},
    {"RCPS",1},
    {"CSAI",2},
    {"Civil Engineering",4}
};

unordered_map<string, int> timeToBitMap = {
    {"Morning",0}, {"Afternoon",1}, {"Evening",2}, {"Night",3}, {"Late Night",4}
};
const string time_list[] = {"Morning","Afternoon","Evening","Night","Late Night"};

int timeToBit(const string& time) {
    if (timeToBitMap.find(time) != timeToBitMap.end()) {
        return timeToBitMap[time];
    } else {
        throw invalid_argument("time bad");
    }
}

bitset<5> timesToBitset(const string& timesList) {
    bitset<5> result;
    istringstream stream(timesList);
    string time;

    // Extract times from the stream, trimming spaces
    while (getline(stream, time, ',')) {
        time.erase(time.find_last_not_of(" \t\n\r\f\v") + 1); // Trim whitespace
        result.set(timeToBit(time)); // Set the bit for the corresponding time
    }

    return result;
}

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


class User {
    protected:

        //Basic Info
        string name;
        string pronouns;
        string bio;

        //secret secret
        string password;

        //User Profile
        int age;
        int gender;
        int mode; 
        int uniId;
        int majorId;
        bitset<7> studyDays;
        bitset<5> studyTimes;

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
        User(string, string, string, string, int, int, int, int, int, bitset<7>, bitset<5>); //only bio data
        User(string, string, string, string, int, int, int, int, int, bitset<7>, bitset<5>, int, int, int, int, int, int, int); // all weights

        string getName();
        string getPronouns();
        string getBio();
        int getId();

        int getAge() const;
        int getGender() const;
        int getMode() const; 
        int getUniId() const;
        int getMajorId() const;
        bitset<7> getStudyDays() const;
        bitset<5> getStudyTimes() const;

        int getAgeWeight() const;
        int getGenderWeight() const;
        int getModeWeight() const;
        int getUniWeight() const;
        int getMajorWeight() const;
        int getDaysWeight() const;
        int getTimesWeight() const;

        static User loadUser(string, string);
        static User login();
        void logout();
        static User registerUser();
        void writeToCSV();

        void swipeLeft();
        void swipeRight();
        string toString();
        void getUserSwipes();
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
};

class UserHeap{
  public:
    int arr[10];
    int size;
    
    UserHeap() {arr[0]=-1; size=0;}

    void insert(int val) {
        size=size + 1;
        int index = size;
        arr[index] = val;
        
        while(index > 1) {
            int parent = index / 2;
            
            if(arr[parent] < arr[index]) {
                int temp = arr[index];
                arr[index] = arr[parent];
                arr[parent] = temp;
                
                index = parent;
            } else { return; }
        }
    }
    
    void print() {
        for(int i=1;i<= size; i++) {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
    
    void deleteheap() {
        if(size ==0) {
            return;
        }
        
        arr[1] = arr[size];
        size--;
        
        int i=1;
        
        while(i < size) {
            int leftchild= 2 * i;
            int rightchild= ( 2 * i) + 1;
            
            if(leftchild < size && arr[leftchild] > arr[i]) {
                int temp = arr[i];
                arr[i] = arr[leftchild];
                arr[leftchild] = temp;
                
                i = leftchild;
            } else if(rightchild < size && arr[rightchild] > arr[i]) {
                int temp = arr[i];
                arr[i] = arr[rightchild];
                arr[rightchild] = temp;
                
                i = rightchild;
            } else {
                return;
            }
        }
    }

    void heapsort() {
        int s=size;
        while(s>1) {
            int temp=arr[1];
            arr[1]=arr[s];
            arr[s]=temp;
            s--;
            heapify(arr,s,1);
        }
    }

    void heapify(int arr[],int n,int i) {
        int largest = i;
        int leftchild=2*i;
        int rightchild=(2*i)+1;
        
        if(leftchild <= n && arr[leftchild] > arr[largest]) {
            int temp = arr[largest];
            arr[largest] = arr[leftchild];
            arr[leftchild] = temp;
            largest = leftchild;
        } if(rightchild <= n && arr[rightchild] > arr[largest]) {
            int temp = arr[largest];
            arr[largest] = arr[rightchild];
            arr[rightchild] = temp;
            largest = rightchild;
        } if(largest !=i) {
            heapify( arr,n,largest);
        }
    }
};

int User::id_counter = 0;

User::User() {
    name = "Test User " + to_string(id_counter);
    pronouns = "Rather Not Say";
    bio = "";

    age = 0;
    gender = 0;
    mode = 0;
    uniId = 0;
    majorId = 0;

    ageWeight = 0;
    genderWeight = 0;
    modeWeight = 0;
    uniWeight = 0;
    majorWeight = 0;
    daysWeight = 0;
    timesWeight = 0;
}

User::User(string name, string password, string pronouns, string bio, int age, int gender, int mode, int uniId, int majorId, bitset<7> studyDays, bitset<5> studyTimes) {
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

User::User(string name, string password, string pronouns, string bio, int age, int gender, int mode, int uniId, int majorId, bitset<7> studyDays, bitset<5> studyTimes, int ageWeight, int genderWeight, int modeWeight, int uniWeight, int majorWeight, int daysWeight, int timesWeight) {
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

int User::getAge() const {return this->age;}
int User::getGender() const {return this->gender;}
int User::getMode() const {return this->mode;}
int User::getUniId() const {return this->uniId;}
int User::getMajorId() const {return this->majorId;}
bitset<7> User::getStudyDays() const {return this->studyDays;}
bitset<5> User::getStudyTimes() const {return this->studyTimes;}

int User::getAgeWeight() const {return this->ageWeight;}
int User::getGenderWeight() const {return this->genderWeight;}
int User::getModeWeight() const {return this->modeWeight;}
int User::getUniWeight() const {return this->uniWeight;}
int User::getMajorWeight() const {return this->majorWeight;}
int User::getDaysWeight() const {return this->daysWeight;}
int User::getTimesWeight() const {return this->timesWeight;}

User User::registerUser() {
    string name, password, pronouns, bio, inp;
    int age, gender, mode, uniId, majorId;
    bitset<5> studyTimes;
    bitset<7> studyDays;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter name: ";
    getline(cin, name);

    cout << "\nEnter password: ";
    getline(cin,password);

    cout << "\nEnter pronouns: ";
    getline(cin, pronouns);

    cout << "\nEnter bio: ";
    getline(cin, bio);

    age = -1;
    while (age < 0) {
        cout << "\nEnter age: ";
        cin >> age;
        if (age < 0) {
            cout << "Invalid input. Please enter a valid age: ";
        }
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    gender = -1;
    while (gender == -1) {
        cout << "\nEnter gender (M/F/NB): ";
        cin >> inp;
        //tolower(inp);
        if (inp == "m" || inp == "male") { 
            gender = 0; 
        } else if (inp == "f" || inp == "female") {
            gender = 1;
        } else if (inp == "nb" || inp == "non-binary") {
            gender = 2;
        } else {cout << "Invalid input. Please enter M, F, or NB.\n";}
    }

    mode = -1;
    while (mode == -1) {
        cout << "\nEnter mode (Online/Offline): ";
        cin >> inp;
        //tolower(inp);
        if (inp == "online" || inp == "on") {mode = 0; }
        else if (inp == "offline" || inp == "off") {mode = 1;}
        else {cout << "Invalid input. Please enter Online or Offline.\n";}
    }


    cout << "\nEnter University Name: ";
    cin >> inp;
    //Input Sanitation
    uniId = uni_map[inp];

    cout << "\nEnter Major Name: ";
    cin >> inp;
    //Input Sanitation
    majorId = major_map[inp];

    cout << "\nEnter study days per week: ";
    inp = "";
    for (int i = 0; i < 7; i++) {
        char response;

        cout << "Do you study on " << days_list[i] << "? (y/n): ";
        cin >> response;

        if (response == 'y' || response == 'Y') {
            if (!inp.empty()) {
                inp += ",";
            }
            inp += days_list[i];
        }
    }
    studyDays = daysToBitset(inp);
    

    cout << "\nEnter study times per day: ";
    inp = "";
    for (int i = 0; i < 5; i++) {
        char response;

        cout << "Do you study during the " << time_list[i] << "? (y/n): ";
        cin >> response;

        if (response == 'y' || response == 'Y') {
            if (!inp.empty()) {
                inp += ",";
            }
            inp += time_list[i];
        }
    }
    studyTimes = timesToBitset(inp);

    User newUser(name, password, pronouns, bio, age, gender, mode, uniId, majorId, studyDays, studyTimes);
    newUser.writeToCSV();
    return newUser;
}

void User::writeToCSV() {
    ofstream file(userDataFile, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << userDataFile << " for writing." << endl;
        return;
    }
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

    file << ageWeight << ",";
    file << genderWeight << ",";
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
    file3 << name << ",";
    file3 << password << ",";
    file3 << '\n';
    file3.close();
}

string User::toString() {
    string userString = "Name: " + name + "\n";
    userString += "Pronouns: " + pronouns + "\n";
    userString += "Bio: " + bio + "\n";
    userString += "Age: " + to_string(age) + "\n";
    userString += "Gender: " + to_string(gender) + "\n";
    userString += "Mode: " + to_string(mode) + "\n";
    userString += "Uni ID: " + to_string(uniId) + "\n";
    userString += "Major ID: " + to_string(majorId) + "\n";
    userString += "Study Days: " + studyDays.to_string() + "\n";
    userString += "Study Times: " + studyTimes.to_string() + "\n";
    return userString;
}

void User::swipeLeft() {};
void User::swipeRight() {};

User User::loadUser(string username, string password) {
    ifstream file(userDataFile);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string tempUsername,temp;
                getline(ss, tempUsername, ','); 

                if (tempUsername == username) {
                    vector<string> output;
                    string temp;
                    while (getline(ss, temp,',')) {
                        output.push_back(temp);
                    }
                    file.close();
                    return User(tempUsername, password, output[0], output[1], stoi(output[2]), stoi(output[3]), stoi(output[4]), stoi(output[5]), stoi(output[6]), bitset<7>(output[7]), bitset<5>(output[8]), stoi(output[9]), stoi(output[10]), stoi(output[11]), stoi(output[12]), stoi(output[13]),stoi(output[14]),stoi(output[15]));
                }
            }
            cout << "User not found in file." << endl;
        } else {
            cout << "Unable to open user data file." << endl;
        }
        // Return an empty user if not found
        file.close();
        return User();
}

User User::login() {
    string inputUsername, inputPassword;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Username: ";
    getline(cin, inputUsername);

    cout << "\nEnter Password: ";
    getline(cin, inputPassword);

    ifstream file(passwordFile);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string tempUsername, tempPassword, temp;
                getline(ss, tempUsername, ','); 
                getline(ss, tempPassword, ','); 

                // Remove leading and trailing whitespaces from username and password
                tempUsername.erase(0, tempUsername.find_first_not_of(" \t\n\r\f\v"));
                tempUsername.erase(tempUsername.find_last_not_of(" \t\n\r\f\v") + 1);

                if (tempUsername != inputUsername) {continue;}
                tempPassword.erase(0, tempPassword.find_first_not_of(" \t\n\r\f\v"));
                tempPassword.erase(tempPassword.find_last_not_of(" \t\n\r\f\v") + 1);

                if (tempPassword == inputPassword) {
                    // Username and password matched, return the user
                    file.close();
                    User a = loadUser(tempUsername, tempPassword);
                    cout << a.toString();
                    return a;
                }
            }
            cout << "Username or password is incorrect.\n";
        } else {
            cout << "Unable to open the password file.\n";
        }
        // Return an empty user if login fails
        file.close();
        return User();
}

void User::logout() {};

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

int calculateCompactibilityScore(const User &user1, const User &user2) {return 0;};
int calculateCompactibilityScore(const User &user1, const Centroid &centroid) {return 0;};


//K MEANS
// void clusterize(const vector<User>& users, const vector<Centroid> centroids, vector<int>& clusters) {
//     for (int i = 0; i < users.size(); i++) {
//         int minScore = clusters.front();
//         int closestCluster = 0;
//         for (int j = 1; j < centroids.size(); j++) {
//             int score = calculateCompactibilityScore(users[i],centroids[j]);
//             if (score < minScore) {
//                 minScore = score;
//                 closestCluster = j;
//             }
//         }
//         clusters[i] = closestCluster;
//     }
// }

// void updateCentroids(const vector<User>& users, vector<Centroid>& centroids, const vector<int>& clusters) {
//     vector<vector<double>> weightSum(centroids.size(), vector<double>(14, 0));
//     vector<int> count(centroids.size(),0);

//     for (int i = 0; i < users.size(); ++i) {
//         weightSum[clusters[i]][0] += users[i].getAgeWeight();
//         weightSum[clusters[i]][1] += users[i].getGenderWeight();
//         weightSum[clusters[i]][2] += users[i].getModeWeight();
//         weightSum[clusters[i]][3] += users[i].getUniWeight();
//         weightSum[clusters[i]][4] += users[i].getMajorWeight();
//         weightSum[clusters[i]][5] += users[i].getDaysWeight();
//         weightSum[clusters[i]][6] += users[i].getTimesWeight();

//         weightSum[clusters[i]][7] += users[i].getAge();
//         weightSum[clusters[i]][8] += users[i].getGender();
//         weightSum[clusters[i]][9] += users[i].getMode();
//         weightSum[clusters[i]][10] += users[i].getUniId();
//         weightSum[clusters[i]][11] += users[i].getMajorId();
//         weightSum[clusters[i]][12] += users[i].getStudyDays();
//         weightSum[clusters[i]][13] += users[i].getStudyTimes();

//         count[clusters[i]]++;
//     } 
// }

char getUserChoice(bool isLoggedIn) {
    char choice;
    if (isLoggedIn) 
        cout << "Enter 'L' to reject or 'R' to match. Enter 'H' for further help : ";
    else
        cout << "Enter 'L' to login or 'R' to register: ";

    cin >> choice;
    return choice;
}

void printHelp() {
    cout << "Welcome to Stumbl!" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Commands:" << endl;
    cout << "H: Help" << endl;
    cout << "L: Swipe left" << endl;
    cout << "R: Swipe right" << endl;
    cout << "O: Logout" << endl;
    cout << "V: View Profile" << endl;
    cout << "-------------------------------------" << endl;
}


int main() {
    bool isLoggedIn = false;
    User* curr;
    UserHeap userheap;
    unordered_map<int,bool> swipedMap;

    if (isLoggedIn) {
        bool done = false;
        while(true){
            switch (getUserChoice(true)) 
            {
            case 'H':
                printHelp();
                break;
            
            case 'L':
                curr->swipeLeft();
                break;
            
            case 'R':
                curr->swipeRight();
                break;

            case 'O':
                curr->logout();
                isLoggedIn = false;
                done = true;
                break;

            case 'V':
                cout << curr->toString();
                break;

            default:
                cout << "Input Invalid. Type H for Help";
                break;
            }

            if (done){
                break;
            }
        }
    } else {
        bool done = false;
        while (true) {
            switch (getUserChoice(false))
            {
            {case 'L':
                User temp = User::login();
                curr = &temp;
                done = true;
                isLoggedIn = true;
                break;}
            
            {case 'R':
                User temp = User::registerUser();
                curr = &temp;
                done = true;
                isLoggedIn = true;
                break;}

            default:
                cout << "Input Invalid";
                break;
            }

            if (done) {break;}
        }
    }
}