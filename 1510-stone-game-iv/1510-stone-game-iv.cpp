class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1, false); // dp[i]: can the player to move win with i stones?
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                if (!dp[i - j * j]) { // move to a losing state for opponent
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};
