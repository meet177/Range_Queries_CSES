/**
 *    author:  Meet
 *    created: 18.08.2026 16:31:33
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

//four things we need to consider
// 1) node's structure
// 2) merge logic of nodes
// 3) leaf values
// 4) identity element (which we can return for irrelevant segments)
// sum -> 0, prod -> 1, gcd -> 0, maxi -> -INF, mini -> INF

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

node merge(node a, node b) {
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

    //go on to the id node of the seg which is responsible for [l...r] and build it's subtree
    void build(ll id, ll l, ll r, vector<ll>& arr) {
        if(l == r) {
            //leaf node 
            seg[id].sum = arr[l];
            seg[id].pref = seg[id].suff = seg[id].mx = max(0LL, arr[l]);
            return;
        }

        ll mid = (l + r)/2;
        build(2*id, l, mid, arr);
        build(2*id + 1, mid + 1, r, arr);
        seg[id] = merge(seg[2*id], seg[2*id + 1]);
    }

    //go onto this node id which is responsible for [l...r] and try to find the contribution of [lq...rq] from it
    node query(ll id, ll l, ll r, ll lq, ll rq) {
        //fully outer range (will have no contribution)
        if(l > rq || r < lq) {
            return node();
        }
        //fully inner range (means this node contributes fully to the query just take it)
        if(l >= lq && r <= rq) {
            return seg[id];
        }
        ll mid = (l + r)/2;
        node left = query(2*id, l, mid, lq, rq);
        node right = query(2*id + 1, mid + 1, r, lq, rq);
        return merge(left, right);
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
        ll a,b;
        cin >> a >> b;
        --a,--b;

        cout << st.query(1, 0, n-1, a, b).mx << "\n";
    }
    return 0;
}