/**
 *    author:  Meet
 *    created: 13.08.2026 12:58:58
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
const ll M = 1e9 + 7;
//const ll M = 998244353;
#define PI acos(-1)

#define whole(x) (x).begin(), (x).end()

#define yes cout << "YES\n"
#define no cout << "NO\n"

class Fenwick {
    vector<ll> bit;
    ll n;
    public :
    Fenwick(ll n) {
        this->n = n;
        bit.assign(n+1, 0);
    }

    void add(ll i, ll v) {
        for(; i<=n; i += (i & (-i))) {
            bit[i] += v;
        }
    }

    ll query(ll i) {
        ll ans = 0;
        for(; i>0; i -= (i & (-i))) {
            ans += bit[i];
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,q;
    cin >> n >> q;

    vector<ll> arr(n+1);
    for(ll i=1; i<=n; ++i) cin >> arr[i];

    Fenwick ft(n);

    //always add values into fenwick tree carefully here we are considering difference array so we have to add arr[i] - arr[i-1] which is what difference array holds at any point of time and then when we take prefix so (arr[i] - arr[i-1] + arr[i-1]) would become the arr[i] that's how we get the value at i after prefixing of difference array
    for(ll i=1; i<=n; ++i) {
        ft.add(i, arr[i] - arr[i-1]);
    }

    while(q--) {
        ll tp;
        cin >> tp;
        if(tp == 1) {
            ll a,b,u;
            cin >> a >> b >> u;
            //update the range [a,b] so we just update the values at end points and then we will take prefix sum using fenwick in O(logn)
            //arr[a] += u
            //arr[b + 1] -= u
            ft.add(a, u);
            if(b < n) ft.add(b+1, -u);
        }else {
            ll k;
            cin >> k;

            //now prefix[k] will give me the value at k
            cout << ft.query(k) << "\n";
        }
    }
    return 0;
}