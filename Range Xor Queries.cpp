/**
 *    author:  Meet
 *    created: 02.03.2026 14:13:20
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
        
        vector<ll> pf(n+1, 0);
        for(ll i=1; i<=n; ++i) pf[i] = pf[i-1] ^ arr[i-1];

        while(q--) {
            ll a,b;
            cin >> a >> b;

            cout << (pf[b] ^ pf[a-1]) << "\n";
        }
    }
    return 0;
}