#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t; 
    cin >> t;
    while(t--){
        int n; 
        cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; i++)
            cin >> p[i];

        int k = 0;
        while (k < n && p[k] == n - k)
            k++;

        if (k < n){
            int idx = k;
            for (int i = k + 1; i < n; i++){
                if (p[i] > p[idx])
                    idx = i;
            }
            reverse(p.begin() + k, p.begin() + idx + 1);
        }

        for (int x: p) cout << x << " ";
        cout << "\n";
    }

    return 0;
}
