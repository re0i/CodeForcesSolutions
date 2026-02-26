#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        int vmax = n + m;
        vector<char> has(vmax + 1, 0);
        vector<int> divCnt(vmax + 1, 0);
        vector<int> uniqueA;
        uniqueA.reserve(n);

        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (!has[x]) {
                has[x] = 1;
                uniqueA.push_back(x);
            }
        }

        for (int x : uniqueA) {
            for (int y = x; y <= vmax; y += x) {
                divCnt[y]++;
            }
        }

        long long aliceOnly = 0, bobOnly = 0, both = 0;
        int k = (int)uniqueA.size();
        for (int i = 0; i < m; i++) {
            int y;
            cin >> y;
            if (divCnt[y] == 0) {
                bobOnly++;
            } else if (divCnt[y] == k) {
                aliceOnly++;
            } else {
                both++;
            }
        }

        if (aliceOnly > bobOnly) {
            cout << "Alice\n";
        } else if (aliceOnly < bobOnly) {
            cout << "Bob\n";
        } else {
            cout << (both % 2 ? "Alice\n" : "Bob\n");
        }
    }

    return 0;
}
