class Solution
{
public:
       string s;
       int pos = 0;

       set<string> parseExpression()
       {
              set<string> result = parseTerm();

              while (pos < s.size() && s[pos] == ',')
              {
                     pos++;
                     set<string> next = parseTerm();
                     result.insert(next.begin(), next.end());
              }

              return result;
       }

       set<string> parseTerm()
       {
              set<string> result = {""};

              while (pos < s.size() &&
                     s[pos] != '}' &&
                     s[pos] != ',')
              {

                     set<string> cur;

                     if (s[pos] == '{')
                     {
                            pos++; // skip '{'
                            cur = parseExpression();
                            pos++; // skip '}'
                     }
                     else
                     {
                            cur.insert(string(1, s[pos]));
                            pos++;
                     }

                     set<string> combined;

                     for (const string &a : result)
                     {
                            for (const string &b : cur)
                            {
                                   combined.insert(a + b);
                            }
                     }

                     result = move(combined);
              }

              return result;
       }

       vector<string> braceExpansionII(string expression)
       {
              s = expression;
              pos = 0;

              set<string> result = parseExpression();

              return vector<string>(result.begin(), result.end());
       }
};