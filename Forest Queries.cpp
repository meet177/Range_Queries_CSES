/**
 *    author:  Meet
 *    created: 02.03.2026 14:17:58
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

vector<string> grid;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll t = 1;
    // cin >> t;
    while(t--) {
        ll n,q;
        cin >> n >> q;
        grid.assign(n,"");
        for(ll i=0; i<n; ++i) cin >> grid[i];
        
        vector<vector<ll>> pf(n+1, vector<ll>(n+1,0));

        for(ll i=1; i<=n; ++i) {
            for(ll j=1; j<=n; ++j) {
                if(grid[i-1][j-1] == '*') {
                    ++pf[i][j];
                }
            }
        }

        for(ll i=1; i<=n; ++i) {
            for(ll j=1; j<=n; ++j) {
                pf[i][j] += pf[i][j-1] + pf[i-1][j] - pf[i-1][j-1];
            }
        }

        while(q--) {
            ll i1, j1, i2, j2;
            cin >> i1 >> j1 >> i2 >> j2;

            cout << (pf[i2][j2] - pf[i1-1][j2] - pf[i2][j1-1] + pf[i1-1][j1-1]) << "\n";
        }
    }
    return 0;
}