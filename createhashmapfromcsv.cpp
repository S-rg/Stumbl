unordered_map<string, int> loadUserSwipes(const string& currentUserName) {
    unordered_map<string, int> swipes;
    ifstream leftFile("left_swipe.csv"), rightFile("right_swipe.csv");
    string line;

    
    auto processLine = [&](ifstream& file, int swipeValue) {
        while (getline(file, line)) {
            stringstream ss(line);
            string user, swipedUser;
            getline(ss, user, ',');
            if (user == currentUserName) {
                while (getline(ss, swipedUser, ',')) {
                    swipedUser.erase(remove(swipedUser.begin(), swipedUser.end(), ' '), swipedUser.end());  
                    swipes[swipedUser] = swipeValue;  
                }
            }
        }
    };

    processLine(leftFile, 0);  

    processLine(rightFile, 1); 

    leftFile.close();
    rightFile.close();

    return swipes;
}

unordered_map<string, int> userSwipes;
if (curr != nullptr) {  // Ensure there is a logged-in user
    userSwipes = loadUserSwipes(curr->getName());
}
