class Solution
{
       struct Node
       {
              int prod = 1;
              int cnt[5] = {0, 0, 0, 0, 0};
       };

       int k;
       vector<Node> tree;

       Node mergeNode(const Node &a, const Node &b)
       {
              Node res;

              res.prod = (long long)a.prod * b.prod % k;

              // Prefixes completely inside left part
              for (int r = 0; r < k; r++)
              {
                     res.cnt[r] = a.cnt[r];
              }

              // Prefixes that extend into right part
              for (int r = 0; r < k; r++)
              {
                     int nr = (long long)a.prod * r % k;
                     res.cnt[nr] += b.cnt[r];
              }

              return res;
       }

       void build(vector<int> &nums, int node, int l, int r)
       {
              if (l == r)
              {
                     int rem = nums[l] % k;

                     tree[node].prod = rem;
                     tree[node].cnt[rem] = 1;

                     return;
              }

              int mid = (l + r) / 2;

              build(nums, node * 2, l, mid);
              build(nums, node * 2 + 1, mid + 1, r);

              tree[node] = mergeNode(tree[node * 2],
                                     tree[node * 2 + 1]);
       }

       void update(int node, int l, int r, int pos, int value)
       {
              if (l == r)
              {
                     tree[node] = Node();

                     int rem = value % k;

                     tree[node].prod = rem;
                     tree[node].cnt[rem] = 1;

                     return;
              }

              int mid = (l + r) / 2;

              if (pos <= mid)
                     update(node * 2, l, mid, pos, value);
              else
                     update(node * 2 + 1, mid + 1, r, pos, value);

              tree[node] = mergeNode(tree[node * 2],
                                     tree[node * 2 + 1]);
       }

       Node query(int node, int l, int r, int ql, int qr)
       {
              if (ql <= l && r <= qr)
                     return tree[node];

              int mid = (l + r) / 2;

              if (qr <= mid)
                     return query(node * 2, l, mid, ql, qr);

              if (ql > mid)
                     return query(node * 2 + 1, mid + 1, r, ql, qr);

              Node left = query(node * 2, l, mid, ql, qr);
              Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

              return mergeNode(left, right);
       }

public:
       vector<int> resultArray(vector<int> &nums,
                               int k,
                               vector<vector<int>> &queries)
       {

              this->k = k;

              int n = nums.size();

              tree.resize(4 * n);

              build(nums, 1, 0, n - 1);

              vector<int> result;
              result.reserve(queries.size());

              for (auto &q : queries)
              {
                     int index = q[0];
                     int value = q[1];
                     int start = q[2];
                     int x = q[3];

                     // Persistent update
                     update(1, 0, n - 1, index, value);

                     // Remaining array is nums[start ... n-1]
                     Node res = query(1, 0, n - 1,
                                      start, n - 1);

                     result.push_back(res.cnt[x]);
              }

              return result;
       }
};