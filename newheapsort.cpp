#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Preferences {
public:
    int calculateCompatibilityScore(int myAge, int otherAge, int myGender, int otherGender, int myUni, int otherUni, int myMajor, int otherMajor, int myTime, int otherTime, int myMode, int otherMode, const string& myDaysList, const string& otherDaysList, int fullWeight) const {
        // Your compatibility score calculation logic here
        // For demonstration purposes, returning a dummy value
        return myAge + otherAge + myGender + otherGender + myUni + otherUni + myMajor + otherMajor + myTime + otherTime + myMode + otherMode + fullWeight;
    }
};

class heap {
public:
    pair<int, string> arr[100]; // Pair of compatibility score and name
    int size;

    heap() {
        size = 0;
    }

    void insert(const string& name, const Preferences& prefs, int myAge, int otherAge, int myGender, int otherGender, int myUni, int otherUni, int myMajor, int otherMajor, int myTime, int otherTime, int myMode, int otherMode, const string& myDaysList, const string& otherDaysList, int fullWeight) {
        int compatibilityScore = prefs.calculateCompatibilityScore(myAge, otherAge, myGender, otherGender, myUni, otherUni, myMajor, otherMajor, myTime, otherTime, myMode, otherMode, myDaysList, otherDaysList, fullWeight);
        size = size + 1;
        int index = size;
        arr[index] = make_pair(compatibilityScore, name);

        while(index > 1) {
            int parent = index / 2;
            if(arr[parent].first < arr[index].first) {
                swap(arr[parent], arr[index]);
                index = parent;
            } else {
                return;
            }
        }
    }

    void print() {
        for(int i = 1; i <= size; i++) {
            cout << arr[i].second << ": " << arr[i].first << " ";
            cout << endl;
        }
    }

    void deleteheap() {
        if(size == 0) {
            return;
        }
        arr[1] = arr[size];
        size--;
        int i = 1;
        while(i < size) {
            int leftchild = 2 * i;
            int rightchild = (2 * i) + 1;
            if(leftchild < size && arr[leftchild].first > arr[i].first) {
                swap(arr[i], arr[leftchild]);
                i = leftchild;
            } else if(rightchild < size && arr[rightchild].first > arr[i].first) {
                swap(arr[i], arr[rightchild]);
                i = rightchild;
            } else {
                return;
            }
        }
    }

    void heapsort() {
        int s = size;
        while(s > 1) {
            swap(arr[1], arr[s]);
            s--;
            heapify(arr, s, 1);
        }
    }

    void heapify(pair<int, string> arr[], int n, int i) {
        int largest = i;
        int leftchild = 2 * i;
        int rightchild = (2 * i) + 1;
        if(leftchild <= n && arr[leftchild].first > arr[largest].first) {
            largest = leftchild;
        }
        if(rightchild <= n && arr[rightchild].first > arr[largest].first) {
            largest = rightchild;
        }
        if(largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
};

int main() {
    heap h;
    Preferences prefs;
    // Dummy data
    int myAge = 30, otherAge = 25, myGender = 1, otherGender = 0, myUni = 1, otherUni = 1, myMajor = 2, otherMajor = 2, myTime = 10, otherTime = 8, myMode = 1, otherMode = 1, fullWeight = 100;
    string myDaysList = "Monday,Tuesday,Wednesday", otherDaysList = "Monday,Wednesday,Thursday";
    
    h.insert("User1", prefs, myAge, otherAge, myGender, otherGender, myUni, otherUni, myMajor, otherMajor, myTime, otherTime, myMode, otherMode, myDaysList, otherDaysList, fullWeight);
    // You can add more users with their compatibility scores here
    
    h.print();
    h.heapsort();
    cout << "After sorting..." << endl;
    h.print();
    
    return 0;
}
