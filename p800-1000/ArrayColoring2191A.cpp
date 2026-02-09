#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int mismatches = 0;
        for (int i = 0; i < n; i++) {
            // Check if parity of the position and the number match
            if ((a[i] % 2) != ((i + 1) % 2)) {
                mismatches++;
            }
        }

        // If all or none are mismatched, coloring is possible
        if (mismatches == 0 || mismatches == n) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
