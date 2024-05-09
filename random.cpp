#include <bits/stdc++.h>
using namespace std;

struct Profile {
    string name;
    string course;
    string studyTime;
    string preferredDays;
    string genderPreference;
};

void loadProfiles(vector<Profile>& profiles, const string& filename);
void displayProfile(const Profile& profile);
char getUserChoice();
void displayMessage(char choice);

int main() {
    vector<Profile> profiles;
    const string filename = "profiles.csv"; 

    loadProfiles(profiles, filename);

    string email, password;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;

    
    cout << "Enter your name: ";
    string name;
    cin >> name;

    cout << "Enter your course: ";
    string course;
    cin >> course;

    cout << "Enter your preferred study time (Morning/Afternoon/Evening/Night): ";
    string studyTime;
    cin >> studyTime;

    cout << "Enter your preferred study days (Weekdays/Weekends/Any): ";
    string preferredDays;
    cin >> preferredDays;

    cout << "Enter your gender preference (Male/Female/Any): ";
    string genderPreference;
    cin >> genderPreference;

    for (const auto& profile : profiles) {
        displayProfile(profile);
        char choice = getUserChoice();
        displayMessage(choice);
    }

    return 0;
}

void loadProfiles(vector<Profile>& profiles, const string& filename) {
    ifstream file(filename);
    string line, name, course, studyTime, preferredDays, genderPreference;

    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, course, ',');
        getline(ss, studyTime, ',');
        getline(ss, preferredDays, ',');
        getline(ss, genderPreference, ',');
        profiles.push_back({name, course, studyTime, preferredDays, genderPreference});
    }

    file.close();
}

void displayProfile(const Profile& profile) {
    cout << "\nName: " << profile.name
         << "\nCourse: " << profile.course
         << "\nStudy Time: " << profile.studyTime
         << "\nPreferred Days: " << profile.preferredDays
         << "\nGender Preference: " << profile.genderPreference << endl;
}

char getUserChoice() {
    char choice;
    cout << "Enter 'L' to reject or 'R' to match: ";
    cin >> choice;
    return choice;
}

void displayMessage(char choice) {
    if (choice == 'R') {
        cout << "You have matched with this profile!\n";
    } else if (choice == 'L') {
        cout << "You have rejected this profile.\n";
    } else {
        cout << "Invalid choice. Please enter 'L' or 'R'.\n";
    }
}
