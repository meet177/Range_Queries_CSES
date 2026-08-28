/**
 *    author:  Meet
 *    created: 19.08.2026 22:41:11
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
    ll lazy_add, lazy_set;
    ll sum;
    node() {
        lazy_add = lazy_set = 0;
        sum = 0;
    }
};

//we always push the values when we go to any node so while coming back the lazy of the node will be always zero so we do not have to worry about change in lazy during merge 
node merge(const node& a, const node& b) {
    node ans;
    ans.sum = a.sum + b.sum;
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
            //leaf node
            seg[id].lazy_add = seg[id].lazy_set = 0;
            seg[id].sum = arr[l];
            return;
        }

        ll mid = (l + r)/2;
        build(2*id, l, mid, arr);
        build(2*id + 1, mid + 1, r, arr);
        seg[id] = merge(seg[2*id], seg[2*id + 1]);
    }

    void push_down(ll node_id, ll child_id) {
        //here the logic of pushing down (how we push the node's lazy to the child's lazy)
        //for many lazy's we make a table and see what are the results

        if(seg[node_id].lazy_set != 0) {
            seg[child_id].lazy_set = seg[node_id].lazy_set;
            seg[child_id].lazy_add = 0;
        }else {
            if(seg[child_id].lazy_set != 0) {
                seg[child_id].lazy_set += seg[node_id].lazy_add;
            }else {
                seg[child_id].lazy_add += seg[node_id].lazy_add;
            }
        }
    }

    void push(ll id, ll l, ll r) {
        //apply to this node and push it to children (make the node up to date(lazy = 0))
        if(seg[id].lazy_add == 0 && seg[id].lazy_set == 0) return;

        //means it is not a leaf node then only we need to propogate
        if(l != r) {    
            push_down(id, 2*id);
            push_down(id, 2*id + 1);
        }

        //apply to this node 
        //either of add or set will be non zero at a time both will never be (we have to make a table to see the relations between the operations)
        if(seg[id].lazy_add != 0) {
            seg[id].sum += (r - l + 1) * seg[id].lazy_add;
        }else {
            seg[id].sum = (r - l + 1) * seg[id].lazy_set;
        }

        //the node of id is now up to date and it's lazy are propogated to the children so now the lazy of the id should be zero
        seg[id].lazy_add = seg[id].lazy_set = 0;
    }

    //now the update is also on some range not only on some point so we will write the same logic of the query
    void update(ll id, ll l, ll r, ll lq, ll rq, ll val, ll tp) {
        //whenever we come to some node we consider that we will need that value so we just push it    
        //just the only difference in function definitions are that we just have to add the push into both the update and query (what it means is basically when we come to any node we just make that node up to date as value of it can be needed now)
        push(id, l, r);     
        if(l > rq || r < lq) {
            return;
        }
        if(l >= lq && r <= rq) {
            //increment
            if(tp == 1) seg[id].lazy_add += val;
            else seg[id].lazy_set = val;

            //you are at some node just make it up to date because it will be needed for the merge while backtracking
            push(id, l, r);
            return;
        }

        ll mid = (l + r)/2;
        update(2*id, l, mid, lq, rq, val, tp);
        update(2*id + 1, mid + 1, r, lq, rq, val, tp);
        seg[id] = merge(seg[2*id], seg[2*id + 1]);
    }

    node query(ll id, ll l, ll r, ll lq, ll rq) {
        push(id, l, r); //you are at some node just make it up to date

        if(l > rq || r < lq) {
            return node();
        }

        if(l >= lq && r <= rq) {
            return seg[id];
        }

        ll mid = (l + r)/2;
        return merge(query(2*id, l, mid, lq, rq), query(2*id + 1, mid + 1, r, lq, rq));
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
        ll tp;
        cin >> tp;
        if(tp == 1 || tp == 2) {
            ll a,b,x;
            cin >> a >> b >> x;
            --a,--b;
            st.update(1, 0, n-1, a, b, x, tp);
        }else {
            ll a,b;
            cin >> a >> b;
            --a, --b;
            node ans = st.query(1, 0, n-1, a, b);
            cout << ans.sum << "\n";
        }
    }
    return 0;
}