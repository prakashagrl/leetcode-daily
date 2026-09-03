class Solution
{
public:
       bool uniformArray(vector<int> &nums1)
       {
              int minOdd = INT_MAX;
              int minEven = INT_MAX;

              for (int x : nums1)
              {
                     if (x % 2)
                            minOdd = min(minOdd, x);
                     else
                            minEven = min(minEven, x);
              }

              // Make everything even
              bool makeEven = true;

              // Every odd element needs a smaller odd element
              for (int x : nums1)
              {
                     if (x % 2 && minOdd >= x)
                     {
                            makeEven = false;
                            break;
                     }
              }

              // Make everything odd
              bool makeOdd = true;

              // Every even element needs a smaller odd element
              if (minOdd == INT_MAX)
              {
                     makeOdd = false;
              }
              else
              {
                     for (int x : nums1)
                     {
                            if (x % 2 == 0 && minOdd >= x)
                            {
                                   makeOdd = false;
                                   break;
                            }
                     }
              }

              return makeEven || makeOdd;
       }
};