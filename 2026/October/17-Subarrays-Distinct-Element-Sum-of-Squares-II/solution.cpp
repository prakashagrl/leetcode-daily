class Solution {
public:
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum = 0, sqSum = 0, lazy = 0;
    };

    vector<Node> tree;
    int n;

    void apply(int node, int l, int r, long long v) {
        long long len = r - l + 1;

        tree[node].sqSum = (tree[node].sqSum
            + 2 * v % MOD * tree[node].sum % MOD
            + len % MOD * v % MOD * v % MOD) % MOD;

        tree[node].sum = (tree[node].sum + len * v) % MOD;
        tree[node].lazy = (tree[node].lazy + v) % MOD;
    }

    void push(int node, int l, int r) {
        if (tree[node].lazy == 0 || l == r) return;

        int mid = (l + r) / 2;
        apply(node * 2, l, mid, tree[node].lazy);
        apply(node * 2 + 1, mid + 1, r, tree[node].lazy);
        tree[node].lazy = 0;
    }

    void update(int node, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            apply(node, l, r, v);
            return;
        }

        push(node, l, r);
        int mid = (l + r) / 2;

        if (ql <= mid)
            update(node * 2, l, mid, ql, qr, v);
        if (qr > mid)
            update(node * 2 + 1, mid + 1, r, ql, qr, v);

        tree[node].sum =
            (tree[node * 2].sum + tree[node * 2 + 1].sum) % MOD;
        tree[node].sqSum =
            (tree[node * 2].sqSum + tree[node * 2 + 1].sqSum) % MOD;
    }

    long long query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[node].sqSum;

        push(node, l, r);
        int mid = (l + r) / 2;
        long long res = 0;

        if (ql <= mid)
            res += query(node * 2, l, mid, ql, qr);
        if (qr > mid)
            res += query(node * 2 + 1, mid + 1, r, ql, qr);

        return res % MOD;
    }

    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n, Node());

        unordered_map<int, int> last;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int start = last.count(nums[i]) ? last[nums[i]] + 1 : 0;

            update(1, 0, n - 1, start, i, 1);
            ans = (ans + query(1, 0, n - 1, 0, i)) % MOD;

            last[nums[i]] = i;
        }

        return ans;
    }
};