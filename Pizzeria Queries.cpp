/**
 *    author:  Meet
 *    created: 14.08.2026 15:39:00
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
    ll mini1, mini2; //1 is for (pa - a) and 2 is for (pa + a)
    node() {
        mini1 = mini2 = INF;
    }
};

node merge(node a, node b) {
    node ans;
    ans.mini1 = min(a.mini1, b.mini1);
    ans.mini2 = min(a.mini2, b.mini2);
    return ans;
}

class SegTree {
    vector<node> seg;
    public :
    SegTree(vector<ll>& arr) { 
        ll n = arr.size() - 1;
        seg.assign(4*n, node());
        build(1, 1, n, arr);
    }

    //go on to the id node of the seg which is responsible for [l...r] and build it's subtree
    void build(ll id, ll l, ll r, vector<ll>& arr) {
        if(l == r) {
            //leaf node 
            seg[id].mini1 = arr[l] - l;
            seg[id].mini2 = arr[l] + l;
            return;
        }

        ll mid = (l + r)/2;
        build(2*id, l, mid, arr);
        build(2*id + 1, mid + 1, r, arr);
        seg[id] = merge(seg[2*id], seg[2*id + 1]);
    }

    //go onto this node id which is responsible for [l...r] and try to update all nodes which have a contribution from pos
    void update(ll id, ll l, ll r, ll pos, ll val) {
        //outer part (will be no change)
        if(l > pos || r < pos) {
            return;
        }
        //now pos is inside [l...r] and if there is one pos only so it is pos itself just update it's value
        if(l == r) {
            seg[id].mini1 = val - l;
            seg[id].mini2 = val + l;
            return;
        }
        
        ll mid = (l + r)/2;
        update(2*id, l, mid, pos, val);
        update(2*id + 1, mid + 1, r, pos, val);
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

    vector<ll> arr(n + 1);
    for(ll i=1; i<=n; ++i) cin >> arr[i];

    SegTree st(arr);

    while(q--) {
        ll tp;
        cin >> tp;
        if(tp == 1) {
            ll k,x;
            cin >> k >> x;
            st.update(1, 1, n, k, x);
        }else {
            ll k;
            cin >> k;
            node poss1 = st.query(1, 1, n, 1, k-1); //a < k (pa - a + k) = (mini1 + k)
            node poss2 = st.query(1, 1, n, k, n); //a >= k (pa + a - k) = (mini2 - k)
            ll ans = min(poss1.mini1 + k, poss2.mini2 - k);
            cout << ans << "\n";
        }
    }
    return 0;
}