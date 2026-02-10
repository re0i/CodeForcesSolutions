#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, h, l;
        cin >> n >> h >> l;

        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int rows = 0, cols = 0, both = 0;
        for (int x: a) {
            if (x <= h) rows++;
            if (x <= l) cols++;
            if (x <= min(h, l)) both++;
        }

        int maxPairs = min({rows, cols, (rows + cols - both) / 2});
        cout << maxPairs << '\n';
    }

    return 0;
}