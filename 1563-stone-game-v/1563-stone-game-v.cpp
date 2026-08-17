class Solution {
public:
    vector<int> pre;
    vector<vector<int>> memo;

    int rangeSum(int l, int r) {
        return pre[r + 1] - pre[l];
    }

    int dfs(int l, int r) {
        if (l == r) return 0;
        if (memo[l][r] != -1) return memo[l][r];

        int ans = 0;

        for (int k = l; k < r; k++) {
            int left = rangeSum(l, k);
            int right = rangeSum(k + 1, r);

            if (left < right) {
                ans = max(ans, left + dfs(l, k));
            } else if (left > right) {
                ans = max(ans, right + dfs(k + 1, r));
            } else {
                ans = max(ans,
                          max(left + dfs(l, k),
                              right + dfs(k + 1, r)));
            }
        }

        return memo[l][r] = ans;
    }

    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        pre.assign(n + 1, 0);
        for (int i = 0; i < n; i++)
            pre[i + 1] = pre[i] + stoneValue[i];

        memo.assign(n, vector<int>(n, -1));

        return dfs(0, n - 1);
    }
};