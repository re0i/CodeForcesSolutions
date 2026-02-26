#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m, d;
        cin >> n >> m >> d;

        int maxPerTower = d / m + 1; 
        int minTowers = (n + maxPerTower - 1) / maxPerTower;

        cout << minTowers << "\n";
    }
    return 0;
}