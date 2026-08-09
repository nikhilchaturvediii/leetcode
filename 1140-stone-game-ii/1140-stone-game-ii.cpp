#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<int> suffixSum(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }
        
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        for (int i = n - 1; i >= 0; i--) {
            for (int m = 1; m <= n; m++) {
                if (i + 2 * m >= n) {
                    dp[i][m] = suffixSum[i];
                } else {
                    int best = 0;
                    for (int X = 1; X <= 2 * m; X++) {
                        int nextM = min(max(m, X), n);
                        best = max(best, suffixSum[i] - dp[i + X][nextM]);
                    }
                    dp[i][m] = best;
                }
            }
        }
        
        return dp[0][1];
    }
};