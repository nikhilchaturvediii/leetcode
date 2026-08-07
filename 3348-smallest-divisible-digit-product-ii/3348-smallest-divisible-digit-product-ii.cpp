#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string smallestNumber(string num, long long t) {
        int digit_exp[10][4] = {
            {0,0,0,0}, // 0 (unused)
            {0,0,0,0}, // 1
            {1,0,0,0}, // 2
            {0,1,0,0}, // 3
            {2,0,0,0}, // 4
            {0,0,1,0}, // 5
            {1,1,0,0}, // 6
            {0,0,0,1}, // 7
            {3,0,0,0}, // 8
            {0,2,0,0}  // 9
        };

        long long tt = t;
        int A = 0, B = 0, C = 0, D = 0;
        while (tt % 2 == 0) { tt /= 2; A++; }
        while (tt % 3 == 0) { tt /= 3; B++; }
        while (tt % 5 == 0) { tt /= 5; C++; }
        while (tt % 7 == 0) { tt /= 7; D++; }
        if (tt != 1) return "-1";

        int dimB = B + 1, dimC = C + 1, dimD = D + 1;
        long long sizeTotal = (long long)(A + 1) * dimB * dimC * dimD;

        auto idx = [&](int a, int b, int c, int d) -> long long {
            return (((long long)a * dimB + b) * dimC + c) * dimD + d;
        };

        vector<int> minDigits(sizeTotal, 0);
        vector<int> digitsList = {2,3,4,5,6,7,8,9};

        for (int a = 0; a <= A; a++) {
            for (int b = 0; b <= B; b++) {
                for (int c = 0; c <= C; c++) {
                    for (int d = 0; d <= D; d++) {
                        if (a == 0 && b == 0 && c == 0 && d == 0) continue;
                        int best = INT_MAX;
                        for (int dig : digitsList) {
                            int ea = digit_exp[dig][0], eb = digit_exp[dig][1];
                            int ec = digit_exp[dig][2], ed = digit_exp[dig][3];
                            int na = (a - ea > 0) ? a - ea : 0;
                            int nb = (b - eb > 0) ? b - eb : 0;
                            int nc = (c - ec > 0) ? c - ec : 0;
                            int nd = (d - ed > 0) ? d - ed : 0;
                            if (na == a && nb == b && nc == c && nd == d) continue;
                            int val = 1 + minDigits[idx(na, nb, nc, nd)];
                            if (val < best) best = val;
                        }
                        minDigits[idx(a, b, c, d)] = best;
                    }
                }
            }
        }

        auto need = [&](int a, int b, int c, int d) -> int {
            return minDigits[idx(a, b, c, d)];
        };

        int L = (int)num.size();
        vector<int> nums(L);
        for (int i = 0; i < L; i++) nums[i] = num[i] - '0';

        int zeroPos = L;
        for (int i = 0; i < L; i++) {
            if (nums[i] == 0) { zeroPos = i; break; }
        }

        vector<int> PA(zeroPos + 1, 0), PB(zeroPos + 1, 0), PC(zeroPos + 1, 0), PD(zeroPos + 1, 0);
        for (int i = 0; i < zeroPos; i++) {
            int ea = digit_exp[nums[i]][0], eb = digit_exp[nums[i]][1];
            int ec = digit_exp[nums[i]][2], ed = digit_exp[nums[i]][3];
            PA[i+1] = min(A, PA[i] + ea);
            PB[i+1] = min(B, PB[i] + eb);
            PC[i+1] = min(C, PC[i] + ec);
            PD[i+1] = min(D, PD[i] + ed);
        }

        auto build_suffix = [&](int ra, int rb, int rc, int rd, int length) -> string {
            string res;
            res.reserve(length);
            for (int pos = 0; pos < length; pos++) {
                int remAfter = length - pos - 1;
                for (int dig = 1; dig <= 9; dig++) {
                    int ea = digit_exp[dig][0], eb = digit_exp[dig][1];
                    int ec = digit_exp[dig][2], ed = digit_exp[dig][3];
                    int na = (ra - ea > 0) ? ra - ea : 0;
                    int nb = (rb - eb > 0) ? rb - eb : 0;
                    int nc = (rc - ec > 0) ? rc - ec : 0;
                    int nd = (rd - ed > 0) ? rd - ed : 0;
                    if (need(na, nb, nc, nd) <= remAfter) {
                        res.push_back(char('0' + dig));
                        ra = na; rb = nb; rc = nc; rd = nd;
                        break;
                    }
                }
            }
            return res;
        };

        if (zeroPos == L) {
            int ra = max(0, A - PA[L]);
            int rb = max(0, B - PB[L]);
            int rc = max(0, C - PC[L]);
            int rd = max(0, D - PD[L]);
            if (need(ra, rb, rc, rd) == 0) {
                return num;
            }
        }

        int start_i = min(L - 1, zeroPos);
        for (int i = start_i; i >= 0; i--) {
            int pa = PA[i], pb = PB[i], pc = PC[i], pd = PD[i];
            int remLen = L - i - 1;
            int orig = nums[i];
            for (int dcand = orig + 1; dcand <= 9; dcand++) {
                int ea = digit_exp[dcand][0], eb = digit_exp[dcand][1];
                int ec = digit_exp[dcand][2], ed = digit_exp[dcand][3];
                int na = min(A, pa + ea);
                int nb = min(B, pb + eb);
                int nc = min(C, pc + ec);
                int nd = min(D, pd + ed);
                int ra = A - na, rb = B - nb, rc = C - nc, rd = D - nd;
                if (need(ra, rb, rc, rd) <= remLen) {
                    string prefix = num.substr(0, i) + char('0' + dcand);
                    string suffix = build_suffix(ra, rb, rc, rd, remLen);
                    return prefix + suffix;
                }
            }
        }

        int M = need(A, B, C, D);
        int length2 = max(L + 1, M);
        return build_suffix(A, B, C, D, length2);
    }
};