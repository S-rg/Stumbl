#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Constants
const int MAX_USERS = 100; // Maximum number of users

// Structure to store user data
struct UserData {
    string username;
    string password;
    bool online = false;
};

// Function prototypes
void registerUser(UserData users[], int &numUsers);
bool loginUser(UserData users[], int numUsers);

int main() {
    // Load existing user data from file
    UserData users[MAX_USERS];
    int numUsers = 0;

    ifstream file("userdata.csv");
    if (file.is_open()) {
        string username, password;
        while (file >> username >> password && numUsers < MAX_USERS) {
            users[numUsers].username = username;
            users[numUsers].password = password;
            numUsers++;
        }
        file.close();
    } else {
        cout << "Error: Unable to open file userdata.txt" << endl;
        return 1;
    }

    int choice;
    cout << "Welcome to the login system!" << endl;
    do {
        cout << "1. Register\n2. Login\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        int idk=0;

        switch (choice) {
            case 1:
                registerUser(users, numUsers);
                break;
            case 2:
                if (loginUser(users, numUsers)) {
                    cout << "Login successful!" << endl;
                } else {
                    cout << "Login failed. Invalid username or password." << endl;
                }
                for(int i=0;i<numUsers;i++){
                    if(users[i].online==1){
                        idk++;
                    }
                }
                cout<<"The number of online users are: "<<idk<<endl;
                break;
            case 3:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    // Save user data to file before exiting
    ofstream outfile("userdata.csv");
    if (outfile.is_open()) {
        for (int i = 0; i < numUsers; i++) {
            outfile << users[i].username << " " << users[i].password << endl;
        }
        outfile.close();
    } else {
        cout << "Error: Unable to save user data." << endl;
    }

    return 0;
}

void registerUser(UserData users[], int &numUsers) {
    if (numUsers >= MAX_USERS) {
        cout << "Maximum number of users reached. Cannot register more users." << endl;
        return;
    }

    string username, password;
    cout << "Enter username: ";
    cin >> username;

    // Check if username already exists
    for (int i = 0; i < numUsers; i++) {
        if (users[i].username == username) {
            cout << "Username already exists. Please choose a different username." << endl;
            return;
        }
    }

    cout << "Enter password: ";
    cin >> password;

    // Add new user
    users[numUsers].username = username;
    users[numUsers].password = password;
    numUsers++;

    cout << "User registered successfully!" << endl;
}

bool loginUser(UserData users[], int numUsers) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout<<users->password<<endl;
    cout<<users->username<<endl;

    // Check if username exists and password matches
    for (int i = 0; i < numUsers; i++) {
        if (users[i].username == username && users[i].password == password) {
            users[i].online = true;
            return true;
        }
    }
    return false;
}