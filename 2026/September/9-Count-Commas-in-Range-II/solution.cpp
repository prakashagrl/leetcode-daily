class Solution
{
public:
       long long countCommas(long long n)
       {
              long long ans = 0;

              long long start = 1000;
              long long commaCount = 1;

              while (start <= n)
              {
                     long long end = min(n, start * 1000 - 1);

                     long long numbers = end - start + 1;

                     ans += numbers * commaCount;

                     start *= 1000;
                     commaCount++;
              }

              return ans;
       }
};