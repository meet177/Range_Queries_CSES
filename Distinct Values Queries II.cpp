/**
 *    author:  Meet
 *    created: 20.08.2026 16:48:43
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
    ll maxi;
    node() {
        maxi = 0;
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
        ll n = arr.size() - 2;
        seg.assign(4*n, node());
        build(1, 1, n, arr);
    }

    //go on to the id node of the seg which is responsible for [l...r] and build it's subtree
    void build(ll id, ll l, ll r, vector<ll>& arr) {
        if(l == r) {
            //leaf node 
            seg[id].maxi = arr[l];
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
            seg[id].maxi = val;
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

    //so basically for range [a...b] to be fully distinct we need to see that prev[i] < a for all i from a to b, which is max(prev[i]) < a on [a...b] here comes the idea of maintaining prev on a segment tree so that we can find range maxi directly
    //now update is the real critical thing because query is as simple as it is just find maxi and compare it with condition
    //for updation, we need to notice some things
    //firstly the position k has some old value a -> prv ... k ... nxt (set of a)
    //so now after it is changed we will remove it from a's set so we need to update prev and next of k which is nothing but prev[nxt] = prev[k] (changed) and next[prv] = next[k]
    //now the position k will be putted into a new value b -> prv .... k .... nxt (set of b)
    //so we need to find positions prv and nxt which we can find using lower_bound or upper_bound as we are maintaining set for it only
    //it = pos[u].upper_bound(k)
    //now if it is at the end means there is no next of k so ind2 = n+1 else ind2 = *it
    //now if it is at the begin means there is no prev of k so ind1 = 0 else ind1 = *(--it)
    //then we just make prev and next connection it is just linkedlist type thing
    //prev[nxt] = k (changed)
    //next[prv] = k
    //prev[k] = prv (changed)
    //next[k] = nxt

    //now as we are storing prev into segment tree so after this update to make the whole segment tree up to date we need to update all the positions where the prev values changed which as above shown (old next[k] = ind) and (new next[k] = ind2 and k)
    //so we just update them and also don't forget to put the value into set and also update the value at the array

    map<ll, set<ll>> pos;
    vector<ll> prev(n+2, 0), next(n+2, n + 1);

    for(ll i=1; i<=n; ++i) {
        ll val = arr[i];
        if(pos.count(val)) {
            ll ind = *pos[val].rbegin();
            prev[i] = ind;
            next[ind] = i;
        }

        pos[val].insert(i);
    }

    SegTree st(prev);

    while(q--) {
        ll tp;
        cin >> tp;
        if(tp == 1) {
            ll k,u;
            cin >> k >> u;
            ll val = arr[k];
            if(val == u) continue;

            next[prev[k]] = next[k];
            prev[next[k]] = prev[k];
            ll ind = next[k]; //ind is changed
            pos[val].erase(k);

            auto it = pos[u].upper_bound(k);
            ll ind1, ind2;
            if(it == pos[u].end()) {
                ind2 = n + 1;
            }else {
                ind2 = *it;
            }

            if(it == pos[u].begin()) {
                ind1 = 0;
            }else {
                ind1 = *(--it);
            }

            pos[u].insert(k);
            arr[k] = u;
            
            next[ind1] = k;
            prev[k] = ind1; //k is changed
            prev[ind2] = k; //ind2 is changed
            next[k] = ind2;

            st.update(1, 1, n, k, prev[k]);
            if(ind <= n) st.update(1, 1, n, ind, prev[ind]);
            if(ind2 <= n) st.update(1, 1, n, ind2, prev[ind2]);
        }else {
            ll a,b;
            cin >> a >> b;

            node ans = st.query(1, 1, n, a, b);
            if(ans.maxi < a) yes;
            else no;
        }
    }
    return 0;
}