#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353LL;

struct Fenwick {
    int n;
    vector<long long> bit;
    Fenwick() : n(0) {}
    explicit Fenwick(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }

    void add(int idx, long long val) {
        for (int i = idx; i <= n; i += i & -i) bit[i] += val;
    }

    long long sumPrefix(int idx) const {
        long long res = 0;
        for (int i = idx; i > 0; i -= i & -i) res += bit[i];
        return res;
    }

    int kth(long long k) const {
        int idx = 0;
        int pw = 1;
        while ((pw << 1) <= n) pw <<= 1;
        for (int step = pw; step > 0; step >>= 1) {
            int nxt = idx + step;
            if (nxt <= n && bit[nxt] < k) {
                idx = nxt;
                k -= bit[nxt];
            }
        }
        return idx + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;
    vector<long long> a(m);
    for (int i = 0; i < m; i++) cin >> a[i];

    vector<long long> all = a;
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    int sz = (int)all.size();

    vector<int> pos(m);
    for (int i = 0; i < m; i++) {
        pos[i] = (int)(lower_bound(all.begin(), all.end(), a[i]) - all.begin()) + 1;
    }

    vector<long long> inv(m + 1, 1);
    for (int i = 2; i <= m; i++) {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
    }

    Fenwick bitCnt(sz), bitSum(sz);

    auto getL = [&](int rank) -> long long {
        int idx = bitCnt.kth(rank + 1);
        long long x = all[idx - 1];
        long long sumLeft = bitSum.sumPrefix(idx - 1);
        return 1LL * rank * x - sumLeft;
    };

    auto getR = [&](int rank, int nCards, long long totalSum) -> long long {
        int idx = bitCnt.kth(rank + 1);
        long long x = all[idx - 1];
        long long sumUpTo = bitSum.sumPrefix(idx);
        long long sumRight = totalSum - sumUpTo;
        long long cntRight = nCards - 1 - rank;
        return sumRight - cntRight * x;
    };

    auto evalAt = [&](int i, int nCards, long long totalSum) -> long long {
        long long left = (i == 0 ? 0 : getL(i - 1));
        long long right = (i == nCards - 1 ? 0 : getR(i + 1, nCards, totalSum));
        return max(left, right);
    };

    int nCards = 0;
    long long totalSum = 0;

    for (int i = 0; i < m; i++) {
        bitCnt.add(pos[i], 1);
        bitSum.add(pos[i], a[i]);
        nCards++;
        totalSum += a[i];

        if (nCards < 3) continue;

        int lo = 0, hi = nCards - 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            long long A = (mid == 0 ? 0 : getL(mid - 1));
            long long B = (mid == nCards - 1 ? 0 : getR(mid + 1, nCards, totalSum));
            if (A >= B) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        long long best = evalAt(lo, nCards, totalSum);
        if (lo > 0) best = min(best, evalAt(lo - 1, nCards, totalSum));

        long long ansMod = (best % MOD) * inv[nCards - 2] % MOD;
        cout << ansMod << '\n';
    }

    return 0;
}
