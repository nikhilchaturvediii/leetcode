class Solution {
public:
    long long gcd(long long a, long long b) {
        while (b) {
            long long t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    long long countValid(long long x, vector<int>& coins) {
        int n = coins.size();
        long long ans = 0;

        // Inclusion-exclusion over all subsets
        for (int mask = 1; mask < (1 << n); mask++) {
            long long lcm = 1;
            bool valid = true;
            int bits = 0;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bits++;

                    long long g = gcd(lcm, (long long)coins[i]);

                    // Prevent overflow and ignore LCM > x
                    lcm = lcm / g * coins[i];

                    if (lcm > x) {
                        valid = false;
                        break;
                    }
                }
            }

            if (!valid)
                continue;

            if (bits % 2 == 1)
                ans += x / lcm;
            else
                ans -= x / lcm;
        }

        return ans;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        long long low = 1;
        long long high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (countValid(mid, coins) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};