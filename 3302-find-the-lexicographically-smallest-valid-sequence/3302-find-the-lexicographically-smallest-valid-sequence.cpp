class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        
        // suf[j] = smallest start index i such that word2[j:] is an exact
        // subsequence of word1[i:]. suf[n2] = n1 (empty suffix always fits).
        vector<int> suf(n2 + 1, -1);
        suf[n2] = n1;
        
        int j = n2;
        for (int i = n1 - 1; i >= 0; i--) {
            if (j > 0 && word1[i] == word2[j - 1]) {
                j--;
                suf[j] = i;
            }
        }
        
        vector<int> result;
        result.reserve(n2);
        int i = 0;
        j = 0;
        bool changed = false;
        
        while (i < n1 && j < n2) {
            if (word1[i] == word2[j]) {
                result.push_back(i);
                i++;
                j++;
            } else if (!changed && suf[j + 1] >= i + 1) {
                result.push_back(i);
                changed = true;
                i++;
                j++;
            } else {
                i++;
            }
        }
        
        if (j == n2) return result;
        return {};
    }
};