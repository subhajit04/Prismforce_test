#include <bits/stdc++.h>
using namespace std;

int main() {
    int testCases;
    cin >> testCases;  // Read the number of test cases
    while (testCases--) {
        int totalCircles = 11, a, b, p;
        cin >> p >> a >> b;  // Read initial power (p), number of skips (a), and number of recharges (b)

        vector<int> enemies(totalCircles, 0);  // Vector to store the power of enemies at each circle
        for (int i = 0; i < totalCircles; i++) {
            cin >> enemies[i];  // Read the power of enemies
        }

        // Define the dimensions for the DP table
        // dp[ind][currPower][skipsLeft][rechargesLeft]
        // dp[ind][currPower][skipsLeft][rechargesLeft] represents whether Abhimanyu can reach the end of the Chakravyuh
        // starting from circle `ind` with `currPower` power, `skipsLeft` skips, and `rechargesLeft` recharges.
        vector<vector<vector<vector<bool>>>> dp(totalCircles + 1, 
            vector<vector<vector<bool>>>(p + 1, 
            vector<vector<bool>>(a + 1, 
            vector<bool>(b + 1, false))));

        // Base case: If we are at the end of the Chakravyuh, we win as long as we have non-negative power.
        for (int power = 0; power <= p; ++power) {
            dp[totalCircles][power][0][0] = (power >= 0);
        }

        // Fill the DP table in reverse order (from the last circle to the first circle)
        for (int ind = totalCircles - 1; ind >= 0; --ind) {
            for (int currPower = 0; currPower <= p; ++currPower) {
                for (int skipsLeft = 0; skipsLeft <= a; ++skipsLeft) {
                    for (int rechargesLeft = 0; rechargesLeft <= b; ++rechargesLeft) {
                        bool canReach = false;

                        // If Abhimanyu has enough power to defeat the enemy at the current circle
                        if (currPower >= enemies[ind]) {
                            canReach = canReach || dp[ind + 1][currPower - enemies[ind]][skipsLeft][rechargesLeft];
                        }

                        // If the current index is 2 or 6, the enemy at the next circle regenerates
                        if (ind == 2 || ind == 6) {
                            if (ind + 1 < totalCircles) {
                                enemies[ind + 1] = enemies[ind + 1] + enemies[ind] / 2;
                            }
                        }

                        // Option to skip the current circle if skips are available
                        if (skipsLeft > 0) {
                            canReach = canReach || dp[ind + 1][currPower][skipsLeft - 1][rechargesLeft];
                        }

                        // Option to recharge the power if recharges are available
                        if (rechargesLeft > 0) {
                            canReach = canReach || dp[ind + 1][p][skipsLeft][rechargesLeft - 1];
                        }

                        // Update the DP table
                        dp[ind][currPower][skipsLeft][rechargesLeft] = canReach;
                    }
                }
            }
        }

        // Output the result based on the DP table
        if (dp[0][p][a][b]) {
            cout << "Abhimanyu will WIN and can cross the Chakravyuh" << endl;
        } else {
            cout << "Abhimanyu will LOSE and cannot cross the Chakravyuh" << endl;
        }
    }
    return 0;
}


