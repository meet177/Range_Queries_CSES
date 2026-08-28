/**
 *    author:  Meet
 *    created: 13.08.2026 17:58:34
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
    ll maxi;
    node() {
        maxi = -INF;
    }  
};

node merge(node a, node b) {
    node ans;
    ans.maxi = max(a.maxi, b.maxi);
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
            seg[id].maxi = arr[l];
            return;
        }
        ll mid = (l + r)/2;
        build(2*id, l, mid, arr);
        build(2*id + 1,  mid + 1, r, arr);
        seg[id] = merge(seg[2*id], seg[2*id + 1]);
    }

    void update(ll id, ll l, ll r, ll pos, ll val) {
        if(l > pos || r < pos) {
            return;
        }
        if(l == r) {
            seg[id].maxi = val;
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
        if(l >= lq && r <= rq) {
            return seg[id];
        }
        ll mid = (l + r)/2;
        node left = query(2*id, l, mid, lq, rq);
        node right = query(2*id + 1, mid + 1, r, lq, rq);
        return merge(left, right);
    }

    ll findMinPos(ll id, ll l, ll r, ll rooms) {
        if(seg[id].maxi < rooms) return 0;

        if(l == r) return l + 1;
        ll mid = (l + r)/2;
        if(seg[2*id].maxi >= rooms) {
            return findMinPos(2*id, l, mid, rooms);
        }else {
            return findMinPos(2*id + 1, mid + 1, r, rooms);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,m;
    cin >> n >> m;

    vector<ll> arr(n);
    for(ll i=0; i<n; ++i) cin >> arr[i];

    SegTree st(arr);

    for(ll i=0; i<m; ++i) {
        ll r;
        cin >> r;

        // ll lo = 0, hi = n-1;
        // ll mx = st.query(1, 0, n-1, lo, hi).maxi;
        // //means no hotel is there which have >= r rooms available so just print 0
        // if(mx < r) {
        //     cout << 0 << " ";
        //     continue;
        // }

        // while(lo < hi) {
        //     ll mid = (lo + hi)/2;
        //     //do we have possibility in the left half which is [lo...mid]
        //     ll mxL = st.query(1, 0, n-1, lo, mid).maxi;
        //     //means there exist someone where i can afford r rooms so for smallest index i should go to the left part 
        //     if(mxL >= r) {
        //         hi = mid;
        //     }else {
        //         lo = mid + 1;
        //     }
        // }
        // cout << lo + 1 << " ";
        // //decrease the rooms of the hotel and then update the same into the segtree
        // arr[lo] -= r;
        // st.update(1, 0, n-1, lo, arr[lo]);

        //instead of doing binary search we can have more efficient solution where we just traverse the segment tree and if the value at left is >= r means there exist someone on left who has >= r rooms remaining so just go onto left and find that index and if not then just go on the right and find it
        ll pos = st.findMinPos(1, 0, n-1, r);
        if(pos != 0) {
            arr[pos - 1] -= r;
            st.update(1, 0, n-1, pos - 1, arr[pos - 1]);
        }
        cout << pos << " ";
    }

    cout << "\n";
    return 0;
}