
class Solution {
public:
    vector<int> answer;
    vector<vector<int>> originalTree, newTree;
    vector<int> last;

    void findParents(int u, vector<int>& parent, string& s) {
        int c = s[u] - 'a';

        int previous = last[c];

        if (previous != -1) {
            parent[u] = previous;
        }

        last[c] = u;

        for (int v : originalTree[u]) {
            findParents(v, parent, s);
        }

        last[c] = previous;
    }

    int dfs(int u) {
        int size = 1;

        for (int v : newTree[u]) {
            size += dfs(v);
        }

        answer[u] = size;
        return size;
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        answer.resize(n);
        originalTree.resize(n);
        newTree.resize(n);

        last.assign(26, -1);

        for (int i = 1; i < n; i++) {
            originalTree[parent[i]].push_back(i);
        }

        findParents(0, parent, s);

        for (int i = 1; i < n; i++) {
            newTree[parent[i]].push_back(i);
        }

        dfs(0);

        return answer;
    }
};
