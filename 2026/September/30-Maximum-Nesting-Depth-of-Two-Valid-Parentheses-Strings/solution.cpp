class Solution
{
public:
       vector<int> maxDepthAfterSplit(string seq)
       {
              vector<int> ans;
              int depth = 0;

              for (char c : seq)
              {
                     if (c == '(')
                     {
                            depth++;

                            // Alternate between A and B
                            ans.push_back(depth % 2);
                     }
                     else
                     {
                            // Closing parenthesis belongs to the
                            // same group as its matching opening parenthesis
                            ans.push_back(depth % 2);
                            depth--;
                     }
              }

              return ans;
       }
};