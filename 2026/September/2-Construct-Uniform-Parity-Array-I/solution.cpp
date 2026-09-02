class Solution
{
public:
       bool uniformArray(vector<int> &nums1)
       {
              int odd = 0;
              int even = 0;

              for (int x : nums1)
              {
                     if (x % 2 == 0)
                            even++;
                     else
                            odd++;
              }

              // All elements already have the same parity
              if (odd == 0 || even == 0)
                     return true;

              // If both parities exist, we can make all elements odd
              // by subtracting an element of opposite parity.
              return true;
       }
};