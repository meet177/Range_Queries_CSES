/**
 *    author:  Meet
 *    created: 13.08.2026 15:59:13
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

//three main things
//1) node structure
//2) merge logic of nodes
//3) leaf value

struct node {
    ll mini;
    node() {
        mini = INF;
    }
};

node merge(node a, node b) {
    node ans;
    ans.mini = min(a.mini, b.mini);
    return ans;
}

class SegTree {
    vector<node> seg;
    public : 
    SegTree(ll n) {
        seg.assign(4*n, node());
    }

    //id is the index of the node in the seg array and it is responsible for [l..r]
    void build(ll id, ll l, ll r) {
        if(l == r) {
            //leaf node
            return;
        }

        ll mid = (l + r)/2;
        build(2*id, l, mid);
        build(2*id + 1, mid + 1, r);
        seg[id] = merge(seg[2*id], seg[2*id + 1]);
    }

    void update(ll id, ll l, ll r, ll pos, ll val) {
        //pos is no where in the [l...r] region
        if(l > pos || r < pos) {
            return;
        }
        //now pos is in [l...r] and if l == r means it is itself pos so just update it
        if(l == r) {    
            seg[id].mini = val;
            return;
        }

        ll mid = (l + r)/2;
        update(2*id, l, mid, pos, val);
        update(2*id + 1, mid + 1, r, pos, val);
        seg[id] = merge(seg[2*id], seg[2*id + 1]);
    }

    node query(ll id, ll l, ll r, ll lq, ll rq) {
        if(l > rq || r < lq) {
            return node();
        }

        //means the query range contains whole responsibility of this node so just return it there is no point in going below it
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

    SegTree st(n);

    st.build(1, 0, n-1);

    for(ll i=0; i<n; ++i) {
        st.update(1, 0, n-1, i, arr[i]);
    }

    while(q--) {
        ll tp;
        cin >> tp;
        if(tp == 1) {
            ll k,u;
            cin >> k >> u;
            --k;
            st.update(1, 0, n-1, k, u);
        }else {
            ll a,b;
            cin >> a >> b;
            --a,--b;
            cout << st.query(1, 0, n-1, a, b).mini << "\n";
        }
    }
    return 0;
}