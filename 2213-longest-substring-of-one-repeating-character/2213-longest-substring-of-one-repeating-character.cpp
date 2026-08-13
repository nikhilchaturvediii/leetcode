class Solution {
    struct Node {
        int len;
        int pref, suff, best;
        char leftChar, rightChar;

        Node() {
            len = 0;
            pref = suff = best = 0;
            leftChar = rightChar = '#';
        }

        Node(char c) {
            len = 1;
            pref = suff = best = 1;
            leftChar = rightChar = c;
        }
    };

    vector<Node> seg;

    Node merge(Node &a, Node &b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;

        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        // Prefix
        res.pref = a.pref;
        if (a.pref == a.len && a.rightChar == b.leftChar)
            res.pref = a.len + b.pref;

        // Suffix
        res.suff = b.suff;
        if (b.suff == b.len && a.rightChar == b.leftChar)
            res.suff = b.len + a.suff;

        // Best
        res.best = max(a.best, b.best);

        if (a.rightChar == b.leftChar)
            res.best = max(res.best, a.suff + b.pref);

        return res;
    }

    void build(int idx, int l, int r, string &s) {
        if (l == r) {
            seg[idx] = Node(s[l]);
            return;
        }

        int mid = l + (r - l) / 2;

        build(idx * 2, l, mid, s);
        build(idx * 2 + 1, mid + 1, r, s);

        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    void update(int idx, int l, int r, int pos, char c) {
        if (l == r) {
            seg[idx] = Node(c);
            return;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid)
            update(idx * 2, l, mid, pos, c);
        else
            update(idx * 2 + 1, mid + 1, r, pos, c);

        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {

        int n = s.size();
        int k = queryCharacters.size();

        seg.resize(4 * n);

        build(1, 0, n - 1, s);

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            int pos = queryIndices[i];
            char c = queryCharacters[i];

            update(1, 0, n - 1, pos, c);

            ans.push_back(seg[1].best);
        }

        return ans;
    }
};