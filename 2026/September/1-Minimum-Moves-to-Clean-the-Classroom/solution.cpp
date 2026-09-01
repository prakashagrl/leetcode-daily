class Solution
{
public:
       int minMoves(vector<string> &classroom, int energy)
       {
              int m = classroom.size();
              int n = classroom[0].size();

              int sr = -1, sc = -1;
              vector<pair<int, int>> litter;

              // Find S and all L
              for (int i = 0; i < m; i++)
              {
                     for (int j = 0; j < n; j++)
                     {
                            if (classroom[i][j] == 'S')
                            {
                                   sr = i;
                                   sc = j;
                            }
                            else if (classroom[i][j] == 'L')
                            {
                                   litter.push_back({i, j});
                            }
                     }
              }

              int k = litter.size();

              // No litter
              if (k == 0)
                     return 0;

              int allMask = (1 << k) - 1;

              // litterMask[i][j] = bit corresponding to litter at (i,j)
              vector<vector<int>> litterMask(m, vector<int>(n, 0));

              for (int i = 0; i < k; i++)
              {
                     litterMask[litter[i].first][litter[i].second] = (1 << i);
              }

              /*
                  visited[r][c][mask][energy]

                  We store the maximum energy with which we have
                  already visited a state.

                  If we reach the same (r,c,mask) with less/equal
                  energy, there is no benefit in processing it again.
              */

              int states = 1 << k;

              vector<vector<vector<int>>> best(
                  m,
                  vector<vector<int>>(n, vector<int>(states, -1)));

              struct State
              {
                     int r, c;
                     int mask;
                     int e;
                     int dist;
              };

              queue<State> q;

              best[sr][sc][0] = energy;
              q.push({sr, sc, 0, energy, 0});

              int dr[] = {1, -1, 0, 0};
              int dc[] = {0, 0, 1, -1};

              while (!q.empty())
              {

                     State cur = q.front();
                     q.pop();

                     int r = cur.r;
                     int c = cur.c;
                     int mask = cur.mask;
                     int e = cur.e;
                     int dist = cur.dist;

                     if (mask == allMask)
                            return dist;

                     for (int d = 0; d < 4; d++)
                     {

                            int nr = r + dr[d];
                            int nc = c + dc[d];

                            if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                                   continue;

                            if (classroom[nr][nc] == 'X')
                                   continue;

                            // Need energy to make the move
                            if (e == 0)
                                   continue;

                            int newEnergy = e - 1;

                            int newMask = mask | litterMask[nr][nc];

                            // Reset energy on R
                            if (classroom[nr][nc] == 'R')
                            {
                                   newEnergy = energy;
                            }

                            /*
                             * If we have already reached this position
                             * with the same collected litter and MORE
                             * energy, this state is unnecessary.
                             */
                            if (best[nr][nc][newMask] >= newEnergy)
                                   continue;

                            best[nr][nc][newMask] = newEnergy;

                            q.push({nr,
                                    nc,
                                    newMask,
                                    newEnergy,
                                    dist + 1});
                     }
              }

              return -1;
       }
};