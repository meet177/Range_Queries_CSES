/**
 *    author:  Meet
 *    created: 02.03.2026 13:05:23
**/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
// order_of_key(k) : no. of elements < k
// *find_by_order(i) : value at index i (0-based)

#define ll long long int
const ll INF = 4e18;
const ll MINF = -4e18;
const ll M = 1e9 + 7;
//const ll M = 998244353;
const ll M1 = 111053273;
const ll M2 = 4011052531;
#define PI acos(-1)

#define whole(x) (x).begin(), (x).end()

#define yes cout << "YES\n"
#define no cout << "NO\n"
#define minus cout << -1 << "\n"

class ST {
    ll n,LOG;
    vector<vector<ll>> dp;

    public :
    ST(vector<ll>& arr) {
        n = arr.size();
        LOG = __lg(n) + 1;
        dp.assign(n, vector<ll>(LOG, 0));

        for(ll i=0; i<n; ++i) {
            dp[i][0] = arr[i];
        }

        for(ll i=1; i<LOG; ++i) {
            for(ll j=0; j + (1LL << i) - 1 < n; ++j) {
                dp[j][i] = min(dp[j][i-1], dp[j + (1LL << (i-1))][i-1]);
            }
        }
    }

    ll query(ll l, ll r) {
        ll len = r - l + 1;
        ll j = __lg(len);
        return min(dp[l][j], dp[r - (1LL << j) + 1][j]);
    }
};

vector<ll> arr;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll t = 1;
    // cin >> t;
    while(t--) {
        ll n,q;
        cin >> n >> q;
        arr.assign(n,0);
        for(ll i=0; i<n; ++i) cin >> arr[i];

        ST st(arr);
        
        while(q--) {
            ll l,r;
            cin >> l >> r;
            --l,--r;
            cout << st.query(l,r) << "\n";
        }
    }
    return 0;
}