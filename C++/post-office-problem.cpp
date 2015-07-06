// Time:  O(k * n^2)
// Space: O(k * n)

class Solution {
public:
    /**
     * @param A an integer array
     * @param k an integer
     * @return an integer
     */
    int postOffice(vector<int>& A, int k) {
        const int n = A.size();
        if (A.empty() || k >= n) {
            return 0;
        }

        sort(A.begin(), A.end());

        // Precompute cost.
        vector<vector<int>> cost(A.size() + 1, vector<int>(A.size() + 1, 0));
        computeMinCost(A, &cost);

        // DP of sum.
        // sum[i][j] denotes the smallest sum of
        // picking i post offices for the first j houses.
        vector<vector<int>> sum(k + 1, vector<int>(A.size() + 1, INT_MAX));
        sum[0][0] = 0;
        for (int i = 1; i <= k; ++i) {
            for (int j = 0; j <= n; ++j) {
                if (sum[i - 1][j] != INT_MAX) {
                    for (int r = 1; j + r <= n; ++r) {
                       sum[i][j + r] = min(sum[i][j + r],
                                           sum[i - 1][j] + cost[j + 1][j + r]);
                    }
                }
            }
        }
        return sum[k][n];
    }

    void computeMinCost(const vector<int>& A, vector<vector<int>> *cost) {
        // Min cost of building a post office for between (i, j).
        // This post office must be in median position.
        for (int i = 0; i < A.size(); ++i) {
            for (int j = i; j < A.size(); ++j) {
                int mid = (i + j) / 2;
                for (int r = i; r <= mid; ++r) {
                    (*cost)[i + 1][j + 1] += A[mid] - A[r];
                }
                for (int r = mid + 1; r <= j; ++r) {
                    (*cost)[i + 1][j + 1] += A[r] - A[mid];
                }
            }
        }
    }
};
