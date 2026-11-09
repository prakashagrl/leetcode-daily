class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {

        // Available servers
        set<int> available;

        // Busy servers: {finishTime, serverIndex}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > busy;

        // Request count for each server
        vector<int> count(k, 0);

        // Initially, all servers are available
        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        for (int i = 0; i < arrival.size(); i++) {

            // Release servers that have completed their tasks
            while (!busy.empty() && busy.top().first <= arrival[i]) {

                int server = busy.top().second;
                busy.pop();

                available.insert(server);
            }

            // If all servers are busy, drop the request
            if (available.empty()) {
                continue;
            }

            // Preferred server
            int preferred = i % k;

            // Find the next available server
            auto it = available.lower_bound(preferred);

            // Wrap around if necessary
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // Assign the request
            available.erase(it);

            count[server]++;

            // Mark server as busy
            busy.push({arrival[i] + load[i], server});
        }

        // Find maximum number of handled requests
        int mx = *max_element(count.begin(), count.end());

        // Collect all busiest servers
        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == mx) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};