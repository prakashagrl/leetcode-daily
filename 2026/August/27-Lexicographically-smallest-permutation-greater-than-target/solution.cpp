class Solution
{
public:
    string lexGreaterPermutation(string s, string target)
    {
        int n = s.size();

        // Try every possible position from right to left
        // where we make the answer greater than target.
        for (int i = n - 1; i >= 0; i--)
        {

            vector<int> freq(26, 0);

            // Characters available after fixing target[0...i-1]
            for (char c : s)
            {
                freq[c - 'a']++;
            }

            // Match target's prefix
            bool possible = true;

            for (int j = 0; j < i; j++)
            {
                int x = target[j] - 'a';

                if (freq[x] == 0)
                {
                    possible = false;
                    break;
                }

                freq[x]--;
            }

            if (!possible)
                continue;

            // Find smallest character greater than target[i]
            for (int c = target[i] - 'a' + 1; c < 26; c++)
            {

                if (freq[c] > 0)
                {
                    string ans = target.substr(0, i);

                    // Make it strictly greater here
                    ans += char('a' + c);
                    freq[c]--;

                    // Remaining characters in sorted order
                    for (int j = 0; j < 26; j++)
                    {
                        ans += string(freq[j], char('a' + j));
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};