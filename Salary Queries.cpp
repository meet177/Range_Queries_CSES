/**
 *    author:  Meet
 *    created: 14.08.2026 11:16:40
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

    void add(ll i, ll val) {
        for(; i<=n; i += (i & (-i))) {
            bit[i] += val;
        }
    }

    ll query(ll i) {
        ll ans = 0;
        for(; i>0; i -= (i & (-i))) {
            ans += bit[i];
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,q;
    cin >> n >> q;

    //so the thing to remember is that coordinate compression works while changes only we just have to have all the values which will be there in any time so what we do is we store each of the value of the array and each of the value of the query in the array and then apply compression on whole of them rather than just the array itself this way we will always have some index which corresponds to each value

    vector<ll> temp;

    vector<ll> arr(n);
    for(ll i=0; i<n; ++i) {
        cin >> arr[i];
        temp.push_back(arr[i]);
    }

    vector<tuple<char,ll,ll>> queries(q);
    for(ll i=0; i<q; ++i) {
        char tp;
        cin >> tp;
        if(tp == '!') {
            ll k,x;
            cin >> k >> x;
            --k;
            temp.push_back(x);
            queries[i] = {tp, k, x};
        }else {
            ll a,b;
            cin >> a >> b;
            queries[i] = {tp, a, b};
        }
    }

    sort(whole(temp));
    temp.erase(unique(whole(temp)), temp.end());

    ll sz = temp.size();
    Fenwick ft(sz);

    for(ll i=0; i<n; ++i) { 
        ll ind = lower_bound(whole(temp), arr[i]) - temp.begin() + 1;
        ft.add(ind, 1);
    }   

    for(ll i=0; i<q; ++i) {
        char tp = get<0>(queries[i]);
        if(tp == '!') {
            ll k = get<1>(queries[i]);
            ll x = get<2>(queries[i]);

            //we have arr[k] currently which we are changing so remove its contribution and then add the new contribution and also update the value in the array itself for future changes
            ll currInd = lower_bound(whole(temp), arr[k]) - temp.begin() + 1;
            ft.add(currInd, -1);
            ll newInd = lower_bound(whole(temp), x) - temp.begin() + 1;
            ft.add(newInd, 1);
            arr[k] = x;
        }else {
            ll a = get<1>(queries[i]);
            ll b = get<2>(queries[i]);

            ll l = lower_bound(whole(temp), a) - temp.begin() + 1;
            ll r = upper_bound(whole(temp), b) - temp.begin() + 1;
            --r;
            //[l...r] is the region we are trying to find
            ll ans = ft.query(r) - ft.query(l - 1);
            cout << ans << "\n";
        }
    }
    return 0;
}