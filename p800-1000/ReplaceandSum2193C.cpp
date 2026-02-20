#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<long long> a(n+1), b(n+1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];

        vector<long long> suf(n+2, 0);
        for (int i = n; i >= 1; i--)
            suf[i] = max(a[i], suf[i+1]);

        vector<long long> pre(n+1, 0);
        for (int i = 1; i <= n; i++)
            pre[i] = pre[i-1] + max(suf[i], b[i]);

        while (q--) {
            int l, r;
            cin >> l >> r;
            cout << pre[r] - pre[l-1] << " \n"[q == 0];
        }
    }
    return 0;
}
