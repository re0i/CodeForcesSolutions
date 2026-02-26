#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;

static bool feasible(unsigned long long s, unsigned long long m, unsigned long long n) {
    i128 L = 0, H = 0;

    for (int i = 0; i < 130; i++) {
        int sb = (i < 64 ? ((s >> i) & 1ULL) : 0);
        bool allowed = (i < 64 ? ((m >> i) & 1ULL) : false);

        i128 low = L;
        i128 high = H + (allowed ? (i128)n : 0);

        if (high < sb) return false;
        if (low < sb) low = sb;

        if ((low & 1) != sb) low++;
        if ((high & 1) != sb) high--;
        if (low > high) return false;

        L = (low - sb) / 2;
        H = (high - sb) / 2;
    }

    return L == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        unsigned long long s, m;
        cin >> s >> m;

        if (!feasible(s, m, s)) {
            cout << -1 << '\n';
            continue;
        }

        unsigned long long lo = 1, hi = s, ans = s;
        while (lo <= hi) {
            unsigned long long mid = lo + (hi - lo) / 2;
            if (feasible(s, m, mid)) {
                ans = mid;
                if (mid == 0) break;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        cout << ans << '\n';
    }
    return 0;
}
