class Solution
{
public:
       string buildPalindrome(string half, char mid)
       {
              string ans = half;

              if (mid != '#')
                     ans += mid;

              for (int i = half.size() - 1; i >= 0; i--)
              {
                     ans += half[i];
              }

              return ans;
       }

       string lexPalindromicPermutation(string s, string target)
       {
              int n = s.size();
              int m = n / 2;

              vector<int> freq(26, 0);

              for (char c : s)
              {
                     freq[c - 'a']++;
              }

              // Check whether a palindrome can be formed
              int odd = 0;
              char mid = '#';

              for (int i = 0; i < 26; i++)
              {
                     if (freq[i] % 2)
                     {
                            odd++;
                            mid = char('a' + i);
                     }
              }

              if (odd > 1)
                     return "";

              // Frequency of characters in the first half
              vector<int> cnt(26);

              for (int i = 0; i < 26; i++)
              {
                     cnt[i] = freq[i] / 2;
              }

              /*
               * First, try to make the first half exactly equal
               * to target's first half.
               */
              string prefix = "";
              int matched = 0;

              while (matched < m)
              {
                     int x = target[matched] - 'a';

                     if (cnt[x] == 0)
                            break;

                     cnt[x]--;
                     prefix += target[matched];
                     matched++;
              }

              // If the complete first half can match target,
              // check the resulting palindrome.
              if (matched == m)
              {
                     string candidate = buildPalindrome(prefix, mid);

                     if (candidate > target)
                            return candidate;
              }

              /*
               * Now find the smallest first half that is
               * strictly greater than target's first half.
               *
               * We change the RIGHTMOST possible position.
               */

              // cnt currently contains characters after `matched`
              // characters of the target prefix have been used.

              int start = min(m - 1, matched);

              for (int i = start; i >= 0; i--)
              {

                     /*
                      * If i < matched, restore target[i].
                      *
                      * This makes cnt represent characters available
                      * after keeping target[0 ... i-1].
                      */
                     if (i < matched)
                     {
                            cnt[target[i] - 'a']++;
                     }

                     int cur = target[i] - 'a';

                     // Try the smallest character greater than target[i]
                     for (int c = cur + 1; c < 26; c++)
                     {

                            if (cnt[c] == 0)
                                   continue;

                            string half = target.substr(0, i);

                            half += char('a' + c);

                            cnt[c]--;

                            // Put remaining characters in sorted order
                            for (int j = 0; j < 26; j++)
                            {
                                   half += string(cnt[j], char('a' + j));
                            }

                            return buildPalindrome(half, mid);
                     }
              }

              return "";
       }
};