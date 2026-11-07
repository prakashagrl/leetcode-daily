class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        // Available servers: {weight, index}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > available;

        // Busy servers: {freeTime, weight, index}
        priority_queue<
            tuple<long long, int, int>,
            vector<tuple<long long, int, int>>,
            greater<tuple<long long, int, int>>
        > busy;

        int n = servers.size();
        int m = tasks.size();

        vector<int> ans(m);

        // Initially, all servers are available.
        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        long long time = 0;

        for (int j = 0; j < m; j++) {

            // Task j arrives at second j.
            time = max(time, (long long)j);

            // Release all servers that have become free.
            while (!busy.empty() && get<0>(busy.top()) <= time) {

                auto [freeTime, weight, idx] = busy.top();
                busy.pop();

                available.push({weight, idx});
            }

            // If no server is available, wait.
            if (available.empty()) {

                time = get<0>(busy.top());

                // Release all servers free at this time.
                while (!busy.empty() && get<0>(busy.top()) <= time) {

                    auto [freeTime, weight, idx] = busy.top();
                    busy.pop();

                    available.push({weight, idx});
                }
            }

            // Select the server with minimum weight and index.
            auto [weight, idx] = available.top();
            available.pop();

            ans[j] = idx;

            // Assign the task to this server.
            busy.push({
                time + tasks[j],
                weight,
                idx
            });
        }

        return ans;
    }
};