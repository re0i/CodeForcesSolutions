#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        string s;
        cin >> s;
        
        long long total_sum = 0;
        for (char c : s) {
            total_sum += c - '0';
        }
        
        if (total_sum <= 9) {
            cout << "0\n";
            continue;
        }
        
        long long R = total_sum - 9;
        
        vector<int> reductions;
        int first_digit = s[0] - '0';
        if (first_digit > 1) {
            reductions.push_back(first_digit - 1);
        }
        
        for (int i = 1; i < s.length(); i++) {
            reductions.push_back(s[i] - '0');
        }
        
        sort(reductions.rbegin(), reductions.rend());
        
        long long sum_reduction = 0;
        int moves = 0;
        for (int r : reductions) {
            if (sum_reduction >= R) break;
            sum_reduction += r;
            moves++;
        }
        
        cout << moves << "\n";
    }
    
    return 0;
}