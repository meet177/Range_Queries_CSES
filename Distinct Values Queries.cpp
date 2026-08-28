/**
 *    author:  Meet
 *    created: 20.08.2026 14:28:13
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

    void update(ll id, ll val) {
        for(; id<=n; id += (id & (-id))) {
            bit[id] += val;
        }
    }

    ll query(ll id) {
        ll ans = 0;
        for(; id>0; id -= (id & (-id))) {
            ans += bit[id];
        }
        return ans;
    }
};  

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,q;
    cin >> n >> q;

    vector<ll> arr(n);
    for(ll i=0; i<n; ++i) cin >> arr[i];

    //so basically idea is to process queries offline with sweeping over l from right to left then we store any value's next occurrence in a map and when we come to the index i we just remove that contribution and add contribution to this index
    vector<vector<pair<ll,ll>>> queries(n);

    for(ll i=0; i<q; ++i) {
        ll a,b;
        cin >> a >> b;
        --a,--b;
        queries[a].push_back({b, i});
    }

    Fenwick ft(n);
    map<ll,ll> index;

    vector<ll> ans(q, 0);

    for(ll i=n-1; i>=0; --i) {
        ll val = arr[i];
        if(index.count(val)) ft.update(index[val] + 1, -1);

        ft.update(i + 1, 1);
        index[val] = i;

        for(auto& [r, ind] : queries[i]) {
            ans[ind] = ft.query(r + 1);
        }
    }

    for(ll i=0; i<q; ++i) cout << ans[i] << "\n";
    return 0;
}