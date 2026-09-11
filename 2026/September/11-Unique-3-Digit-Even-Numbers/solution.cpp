class Solution
{
public:
       int totalNumbers(vector<int> &digits)
       {
              vector<int> freq(10, 0);

              for (int d : digits)
                     freq[d]++;

              int ans = 0;

              for (int num = 100; num <= 998; num += 2)
              {
                     int a = num / 100;
                     int b = (num / 10) % 10;
                     int c = num % 10;

                     vector<int> used(10, 0);
                     used[a]++;
                     used[b]++;
                     used[c]++;

                     bool possible = true;

                     for (int d = 0; d <= 9; d++)
                     {
                            if (used[d] > freq[d])
                            {
                                   possible = false;
                                   break;
                            }
                     }

                     if (possible)
                            ans++;
              }

              return ans;
       }
};