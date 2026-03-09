#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        string filled = s;
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 1; i < n - 1; i++) {
                if (filled[i] == '0' && filled[i-1] == '1' && filled[i+1] == '1') {
                    filled[i] = '1';
                    changed = true;
                }
            }
        }

        int maxOnes = count(filled.begin(), filled.end(), '1');

        int minOnes = 0;
        int i = 0;
        while (i < n) {
            if (filled[i] == '1') {
                int len = 0;
                while (i < n && filled[i] == '1') { len++; i++; }
                minOnes += len / 2 + 1;
            } else {
                i++;
            }
        }

        cout << minOnes << " " << maxOnes << "\n";
    }

    return 0;
}