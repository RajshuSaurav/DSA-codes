#include <iostream>
#include <vector>
using namespace std;

int minSwaps(vector<int>& arr) {
    int n = arr.size();

    // Create a vector to store the indices of elements after sorting
    vector<pair<int, int>> indexedArray(n);
    for (int i = 0; i < n; ++i) {
        indexedArray[i] = {arr[i], i};
    }

    // Initialize the visited array
    vector<bool> visited(n, false);

    int swaps = 0;

    for (int i = 0; i < n; ++i) {
        // If the element is at its correct position or already visited
        if (visited[i] || indexedArray[i].second == i) {
            continue;
        }

        int cycleSize = 0;
        int j = i;

        while (!visited[j]) {
            visited[j] = true;
            j = indexedArray[j].second;
            cycleSize++;
        }

        // For each cycle, calculate the number of swaps needed
        swaps += (cycleSize - 1);
    }

    return swaps;
}

int main() {
    // Example usage
    vector<int> arr = {4,5,1,2,3};

    int swaps = minSwaps(arr);

    cout << "Minimum swaps to make array beautiful: " << swaps << endl;

    return 0;
}
