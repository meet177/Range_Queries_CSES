/**
 *    author:  Meet
 *    created: 18.08.2026 16:14:40
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

struct node {
    ll pref, suff;
    ll sum;
    ll mx;
    node() {
        pref = suff = 0;
        sum = 0;
        mx = 0;
    }
};

node merge(const node& a, const node& b) {
    node ans;
    ans.sum = a.sum + b.sum;
    ans.mx = max({a.mx, b.mx, a.suff + b.pref});
    ans.pref = max(a.pref, a.sum + b.pref);
    ans.suff = max(b.suff, b.sum + a.suff);
    return ans;
}

class SegTree {
    vector<node> seg;
    public :
    SegTree(vector<ll>& arr) {
        ll n = arr.size();
        seg.assign(4*n, node());
        build(1, 0, n-1, arr);
    }

    void build(ll id, ll l, ll r, vector<ll>& arr) {
        if(l == r) {
            seg[id].sum = arr[l];
            seg[id].pref = seg[id].suff = seg[id].mx = max(0LL, arr[l]);
            return;
        }
        ll mid = (l + r)/2;
        build(2*id, l, mid, arr);
        build(2*id + 1, mid + 1, r, arr);
        seg[id] = merge(seg[2*id], seg[2*id + 1]);
    }

    void update(ll id, ll l, ll r, ll pos, ll val) {
        if(pos > r || pos < l) {
            return;
        }
        if(l == r) {
            seg[id].sum = val;
            seg[id].pref = seg[id].suff = seg[id].mx = max(0LL, val);
            return;
        }
        ll mid = (l + r)/2;
        update(2*id, l, mid, pos, val);
        update(2*id + 1, mid + 1, r, pos, val);
        seg[id] = merge(seg[2*id], seg[2*id + 1]);
    }

    ll query() {
        return seg[1].mx;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,q;
    cin >> n >> q;

    vector<ll> arr(n);
    for(ll i=0; i<n; ++i) cin >> arr[i];

    SegTree st(arr);

    while(q--) {
        ll k,v;
        cin >> k >> v;
        --k;
        st.update(1, 0, n-1, k, v);
        
        cout << st.query() << "\n";
    }
    return 0;
}