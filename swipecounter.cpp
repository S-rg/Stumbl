#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>

class Swipe {
private:
    std::unordered_map<std::string, int> swipeCount;

public:
    void recordSwipe(const std::string& code) {
        if (swipeCount.find(code) != swipeCount.end()) {
            swipeCount[code]++;
        } else {
            swipeCount[code] = 1;
        }
    }

    int getSwipeCount(const std::string& code) {
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

    std::cout << "Swipe count for A123: " << swipeTracker.getSwipeCount("A123") << std::endl;
    std::cout << "Swipe count for B456: " << swipeTracker.getSwipeCount("B456") << std::endl;

    return 0;
}
