#include <bits/stdc++.h>
using namespace std;

int main() {  
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--) {
        long long n, w;
        cin >> n >> w;
        long long keep = n / w;
        long long remove = n - keep;
        cout << remove << '\n';
    }

    return 0;
}