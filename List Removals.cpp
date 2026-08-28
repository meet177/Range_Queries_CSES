/**
 *    author:  Meet
 *    created: 13.08.2026 19:57:22
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
    ll sum;
    node() {
        sum = 0;
    }
};

node merge(node a, node b) {
    node ans;
    ans.sum = a.sum + b.sum;
    return ans;
}

class SegTree {
    vector<node> seg;
    public :
    SegTree(ll n) {
        seg.assign(4*n, node());
        build(1, 0, n-1);
    }

    //go on to the id node of the seg which is responsible for [l...r] and build it's subtree
    void build(ll id, ll l, ll r) {
        if(l == r) {
            //leaf node 
            seg[id].sum = 1;
            return;
        }

        ll mid = (l + r)/2;
        build(2*id, l, mid);
        build(2*id + 1, mid + 1, r);
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
            seg[id].sum = val;
            return;
        }
        
        ll mid = (l + r)/2;
        update(2*id, l, mid, pos, val);
        update(2*id + 1, mid + 1, r, pos, val);
        seg[id] = merge(seg[2*id], seg[2*id + 1]);
    }

    //this is traversing the tree itself and finding the best answer which we want
    ll findPos(ll id, ll l, ll r, ll rem) {
        if(l == r) return l;
        ll mid = (l + r)/2;
        //means there exist enough elements on the left half so go there
        if(seg[2*id].sum >= rem) {
            return findPos(2*id, l, mid, rem);
        }else {
            //here left ones are removed because we will need to find (rem - left) only on the right side
            return findPos(2*id + 1, mid + 1, r, rem - seg[2*id].sum);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n;
    cin >> n;

    vector<ll> arr(n);
    for(ll i=0; i<n; ++i) cin >> arr[i];

    SegTree st(n);
    //so what are we storing here is basically if this position is not removed then we store 1 otherwise we store 0 this way when tree is built it will have nodes as number of remaining elements in the original range [l...r] so we just traverse and see on the both sides where we need to go and just find the original position itself and it will give me the answer

    for(ll i=0; i<n; ++i) {
        ll pos;
        cin >> pos;

        ll p = st.findPos(1, 0, n-1, pos);
        cout << arr[p] << " ";
        st.update(1, 0, n-1, p, 0);
    }
    cout << "\n";
    return 0;
}