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
        // Open the CSV file in append mode
        ofstream file(filename, ios::app);
        
        // Check if the file is opened successfully
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << filename << endl;
            return;
        }
        
        // Write the user's ID and timestamp to the file
        file << getId() << "," << getCurrentTimestamp() << endl;
        
        // Close the file
        file.close();
    }

    int getId() {
        // Function to get the user's ID
        // You can implement this based on your user ID logic
        // For demonstration, I'll return a dummy ID
        return 123; // Replace with actual user ID logic
    }

    string getCurrentTimestamp() {

        return "2024-05-12 10:30:00"; // Replace with actual timestamp logic
    }
};
