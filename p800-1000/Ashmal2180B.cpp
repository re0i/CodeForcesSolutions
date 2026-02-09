#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;
        vector<string> a(n);

        for (int i = 0; i < n; i++) cin >> a[i];
        string s = "";
        
        for (int i = 0; i < n; i++) {
            string x = a[i];

            if (x + s < s + x) s = x + s;
            else s = s + x;
        }
        cout << s << '\n';
    }
    return 0;
}