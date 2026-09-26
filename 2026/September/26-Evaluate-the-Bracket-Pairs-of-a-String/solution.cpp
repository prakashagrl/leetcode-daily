class Solution
{
public:
       string evaluate(string s, vector<vector<string>> &knowledge)
       {
              unordered_map<string, string> mp;

              for (auto &entry : knowledge)
              {
                     mp[entry[0]] = entry[1];
              }

              string ans;

              for (int i = 0; i < s.size();)
              {

                     if (s[i] == '(')
                     {
                            int j = i + 1;

                            while (s[j] != ')')
                                   j++;

                            string key = s.substr(i + 1, j - i - 1);

                            if (mp.count(key))
                                   ans += mp[key];
                            else
                                   ans += "?";

                            i = j + 1;
                     }
                     else
                     {
                            ans += s[i];
                            i++;
                     }
              }

              return ans;
       }
};