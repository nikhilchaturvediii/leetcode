class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> rows;

        // Store reserved seats as a bitmask for each affected row
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            rows[row] |= (1 << col);
        }

        // Every completely empty row can accommodate 2 families
        long long ans = 2LL * n;

        // Only rows having reserved seats need checking
        for (auto &[row, mask] : rows) {
            
            // Initially assumed this row can fit 2 families.
            // Remove that assumption and calculate properly.
            ans -= 2;

            // Seats 2-5
            bool left = true;
            for (int seat = 2; seat <= 5; seat++) {
                if (mask & (1 << seat)) {
                    left = false;
                    break;
                }
            }

            // Seats 4-7
            bool middle = true;
            for (int seat = 4; seat <= 7; seat++) {
                if (mask & (1 << seat)) {
                    middle = false;
                    break;
                }
            }

            // Seats 6-9
            bool right = true;
            for (int seat = 6; seat <= 9; seat++) {
                if (mask & (1 << seat)) {
                    right = false;
                    break;
                }
            }

            if (left && right) {
                ans += 2;
            } 
            else if (left || middle || right) {
                ans += 1;
            }
        }

        return ans;
    }
};