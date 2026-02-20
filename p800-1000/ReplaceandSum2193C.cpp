#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<long long> a(n + 2), b(n + 2);

        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
            cin >> b[i];

        vector<long long> best(n + 2, 0);
        for (int i = n; i >= 1; i--) {
            best[i] = max({a[i], b[i], best[i + 1]});
        }

        vector<long long> pref(n + 2, 0);
        for (int i = 1; i <= n; i++) {
            pref[i] = pref[i - 1] + best[i];
        }

        while (q--) {
            int l, r;
            cin >> l >> r;
            long long ans = pref[r] - pref[l - 1];
            cout << ans << " ";
        }
        cout << "\n";
    }
    return 0;
}
