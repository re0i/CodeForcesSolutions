#include <bits/stdc++.h>
using namespace std;

struct Interval {
    int l, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> headR(n + 1, 0), headL(n + 1, 0);
    vector<int> nextR(n + 1, 0), nextL(n + 1, 0);
    vector<int> uVal(n + 1, 0), vVal(n + 1, 0);
    vector<unsigned char> seenU(n + 1, 0);

    vector<long long> diff(n + 3, 0), disjoint(n + 1, 0), ans(n + 1, 0);

    vector<Interval> st;
    st.reserve(64);
    st.push_back({1, n});

    while (!st.empty()) {
        Interval cur = st.back();
        st.pop_back();
        int l = cur.l, r = cur.r;
        if (l > r) continue;
        int m = (l + r) >> 1;

        int u = r - m;
        int v = m - l;
        uVal[m] = u;
        vVal[m] = v;
        seenU[u] = 1;

        nextR[m] = headR[r];
        headR[r] = m;
        nextL[m] = headL[l];
        headL[l] = m;

        if (u > 0) {
            diff[1] += 1;
            diff[u + 1] -= 1;
        }
        if (v > 0) {
            diff[1] += 1;
            diff[v + 1] -= 1;
        }

        st.push_back({m + 1, r});
        st.push_back({l, m - 1});
    }

    vector<int> uList;
    uList.reserve(64);
    vector<int> mapU(n + 1, -1);
    for (int u = 0; u <= n; u++) {
        if (seenU[u]) {
            mapU[u] = (int)uList.size();
            uList.push_back(u);
        }
    }

    int du = (int)uList.size();
    vector<long long> activeCnt(du, 0);

    for (int l = 1; l <= n; l++) {
        int rBoundary = l - 1;
        for (int id = headR[rBoundary]; id != 0; id = nextR[id]) {
            int uid = mapU[uVal[id]];
            activeCnt[uid]++;
        }

        for (int id = headL[l]; id != 0; id = nextL[id]) {
            int v = vVal[id];
            for (int t = 0; t < du; t++) {
                long long c = activeCnt[t];
                if (c) disjoint[uList[t] + v] += c;
            }
        }
    }

    long long cur = 0;
    for (int d = 1; d <= n - 1; d++) {
        cur += diff[d];
        int k = n - d;
        ans[k] += cur;
    }

    for (int s = 0; s <= n - 2; s++) {
        int k = n - 2 - s;
        ans[k] += disjoint[s];
    }

    for (int k = 0; k <= n; k++) {
        cout << ans[k] << ' ';
    }
    cout << '\n';

    return 0;
}
