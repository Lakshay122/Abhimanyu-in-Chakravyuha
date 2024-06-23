#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

bool canAbhimanyuReachEnd(int p, vector<int>& enemies, int a, int b) {
    int n = enemies.size();
    p += p * b; // Calculate the total power with recharges

    // Adjust powers for regenerating enemies
    if (n > 2) {
        enemies[2] += enemies[2] / 2;
    }
    if (n > 6) {
        enemies[6] += enemies[6] / 2;
    }

    // Use a min-heap to find the indices of the 'a' largest enemies
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    for (int i = 0; i < n; ++i) {
        minHeap.push({enemies[i], i});
        if (minHeap.size() > a) {
            minHeap.pop();
        }
    }

    // Collect the indices to be skipped
    unordered_set<int> skipSet;
    while (!minHeap.empty()) {
        skipSet.insert(minHeap.top().second);
        minHeap.pop();
    }

    for (int i = 0; i < n; ++i) {
        if (skipSet.find(i) != skipSet.end()) {
            // Skip this enemy
            continue;
        }

        if (p <= enemies[i]) {
            // Not enough power to defeat this enemy
            return false;
        }

        // Battle the enemy
        p -= enemies[i];
    }

    return true;
}

int main() {
    const int n = 11; // Fixed number of circles

    int p, a, b;
    cout << "Enter the initial power of Abhimanyu: ";
    cin >> p;
    cout << "Enter the number of times Abhimanyu can skip fighting an enemy: ";
    cin >> a;
    cout << "Enter the number of times Abhimanyu can recharge his power: ";
    cin >> b;

    vector<int> enemies(n);
    cout << "Enter the powers of enemies in each circle: ";
    for (int i = 0; i < n; ++i) {
        cin >> enemies[i];
    }

    if (canAbhimanyuReachEnd(p, enemies, a, b)) {
        cout << "Abhimanyu can reach the army of the Pandavas" << endl;
    } else {
        cout << "Abhimanyu cannot reach the army of the Pandavas" << endl;
    }

    return 0;
}

/*
Time Complexity (TC): O(n log a) - This is due to the heap operations for finding the 'a' largest enemies.
Space Complexity (SC): O(n + a) - O(n) for the enemies array and O(a) for the heap and skip set.
*/


//Test Case 1:
// Enter the initial power of Abhimanyu: 50
// Enter the number of times Abhimanyu can skip fighting an enemy: 1
// Enter the number of times Abhimanyu can recharge his power: 0
// Enter the powers of enemies in each circle: 1 2 3 4 5 6 7 8 9 10 1

// Abhimanyu cannot reach the army of the Pandavas


//Test Case 2:
// Enter the initial power of Abhimanyu: 51
// Enter the number of times Abhimanyu can skip fighting an enemy: 1
// Enter the number of times Abhimanyu can recharge his power: 0
// Enter the powers of enemies in each circle: 1 2 3 4 5 6 7 8 9 10 1

// Abhimanyu can reach the army of the Pandavas