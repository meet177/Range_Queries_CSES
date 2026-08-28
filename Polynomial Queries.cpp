/**
 *    author:  Meet
 *    created: 20.08.2026 00:56:37
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
    ll a, d; //basically we need to add a AP to this node so we need a and d 
    ll sum;
    node() {
        a = d = 0;
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
            seg[id].a = seg[id].d = 0;
            return;
        }

        ll mid = (l + r)/2;
        build(2*id, l, mid, arr);
        build(2*id + 1, mid + 1, r, arr);
        seg[id] = merge(seg[2*id], seg[2*id + 1]);
    }

    void push(ll id, ll l, ll r) {
        if(seg[id].a == 0 && seg[id].d == 0) return;

        if(l != r) {
            ll mid = (l + r)/2;
            ll la = seg[id].a;
            //(mid - l + 1) terms are there on the left half so right half starts with (mid - l + 2)th term of the ap 
            ll ra = seg[id].a + (mid - l + 1) * seg[id].d;

            //now the main concept is that two AP's can overlap and when overlapped it's a = a1 + a2 and it's d = d1 + d2
            //for example
            //(3, 5) AP -> 3, 8, 13
            //(4, 7) AP -> 4, 11, 18
            //now when both are overlapped term by term
            //7, 19, 31 which has (a = 7 = 3 + 4) and (d = 12 = 5 + 7)
            //this is the concept why we can propogate the a and d easily
            seg[2*id].a += la;
            seg[2*id].d += seg[id].d;

            seg[2*id + 1].a += ra;
            seg[2*id + 1].d += seg[id].d;
        }

        //apply to the node 
        ll n = r - l + 1;
        //n/2(2a + (n-1)d)
        ll ap_sum = n * (2*seg[id].a + (n - 1)*seg[id].d);
        ap_sum >>= 1;

        seg[id].sum += ap_sum;
        seg[id].a = seg[id].d = 0; //reset because now it is up to date
    }
    //go onto this node id which is responsible for [l...r] and try to update all nodes which have a contribution from pos
    void update(ll id, ll l, ll r, ll lq, ll rq) {
        push(id, l, r);
        //outer part (will be no change)
        if(l > rq || r < lq) {
            return;
        }
        //now pos is inside [l...r] and if there is one pos only so it is pos itself just update it's value
        if(l >= lq && r <= rq) {
            //first term for the range is (l - lq + 1)
            seg[id].a += (l - lq + 1);
            seg[id].d += 1;
            push(id, l, r);
            return;
        }
        
        ll mid = (l + r)/2;
        update(2*id, l, mid, lq, rq);
        update(2*id + 1, mid + 1, r, lq, rq);
        seg[id] = merge(seg[2*id], seg[2*id + 1]);
    }

    //go onto this node id which is responsible for [l...r] and try to find the contribution of [lq...rq] from it
    ll query(ll id, ll l, ll r, ll lq, ll rq) {
        push(id, l, r);
        //fully outer range (will have no contribution)
        if(l > rq || r < lq) {
            return 0;
        }
        //fully inner range (means this node contributes fully to the query just take it)
        if(l >= lq && r <= rq) {
            return seg[id].sum;
        }
        ll mid = (l + r)/2;
        ll left = query(2*id, l, mid, lq, rq);
        ll right = query(2*id + 1, mid + 1, r, lq, rq);
        return left + right;
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
        ll tp,a,b;
        cin >> tp >> a >> b;
        --a,--b;

        if(tp == 1) {
            st.update(1, 0, n-1, a, b);    
        }else {
            cout << st.query(1, 0, n-1, a, b) << "\n";
        }
    }
    return 0;
}