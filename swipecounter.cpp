#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User {
public:
    void swipeLeft() {
        recordSwipe("swipe_left.csv");
    }

    void swipeRight() {
        recordSwipe("swipe_right.csv");
    }

private:
    void recordSwipe(const string& filename) {
        //Open the CSV file in append mode
        ofstream file(filename, ios::app);
        
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << filename << endl;
            return;
        }
        
        //Write the user's ID and timestamp to the file
        file << getId() << "," << getCurrentTimestamp() << endl;
        
        file.close();
    }

    int getId() {
       
        return 123; 
    }

    string getCurrentTimestamp() {

        return "2024-05-12 10:30:00"; 
    }
};
