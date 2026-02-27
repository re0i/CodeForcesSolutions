#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];

        bool sorted = true;

        for (int i = 0; i + 1 < n; i++) {
            if (a[i] > a[i + 1]) {
                sorted = false;
                break;
            }
        }

        if (sorted) cout << n << "\n";
        else cout << 1 << "\n";
    }

    return 0;
}