#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>

using namespace std;

class Swipe {
private:
    unordered_map<string, int> swipeCount;

public:
    void recordSwipe(const string& code) {
        if (swipeCount.find(code) != swipeCount.end()) {
            swipeCount[code]++;
        } else {
            swipeCount[code] = 1;
        }
    }

    int getSwipeCount(const string& code) {
        if (swipeCount.find(code) != swipeCount.end()) {
            return swipeCount[code];
        } else {
            return 0;
        }
    }
};

int main() {
    Swipe swipeTracker;

    swipeTracker.recordSwipe("A123");
    swipeTracker.recordSwipe("B456");
    swipeTracker.recordSwipe("A123");
    swipeTracker.recordSwipe("A123");

    cout << "Swipe count for A123: " << swipeTracker.getSwipeCount("A123") << endl;
    cout << "Swipe count for B456: " << swipeTracker.getSwipeCount("B456") << endl;

    return 0;
}
