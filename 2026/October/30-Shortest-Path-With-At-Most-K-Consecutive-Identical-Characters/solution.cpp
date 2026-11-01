class Solution
{
public:
       int shortestPath(int n, vector<vector<int>> &edges, string labels, int k)
       {

              // Build directed adjacency list
              vector<vector<pair<int, int>>> adj(n);

              for (auto &e : edges)
              {
                     adj[e[0]].push_back({e[1], e[2]});
              }

              // dist[node][count] = minimum cost to reach this state
              const long long INF = LLONG_MAX;

              vector<vector<long long>> dist(n, vector<long long>(k + 1, INF));

              // {cost, node, consecutive count}
              using State = tuple<long long, int, int>;

              priority_queue<State, vector<State>, greater<State>> pq;

              // Starting node's label counts as 1
              dist[0][1] = 0;
              pq.push({0, 0, 1});

              while (!pq.empty())
              {

                     auto [cost, u, count] = pq.top();
                     pq.pop();

                     // Ignore outdated states
                     if (cost != dist[u][count])
                            continue;

                     // Destination reached
                     if (u == n - 1)
                            return (int)cost;

                     for (auto &[v, weight] : adj[u])
                     {

                            int newCount;

                            if (labels[u] == labels[v])
                            {
                                   newCount = count + 1;
                            }
                            else
                            {
                                   newCount = 1;
                            }

                            // Cannot exceed k consecutive identical characters
                            if (newCount > k)
                                   continue;

                            long long newCost = cost + weight;

                            if (newCost < dist[v][newCount])
                            {

                                   dist[v][newCount] = newCost;

                                   pq.push({newCost, v, newCount});
                            }
                     }
              }

              return -1;
       }
};