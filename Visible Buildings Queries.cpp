/**
 *    author:  Meet
 *    created: 14.08.2026 22:38:37
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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,q;
    cin >> n >> q;

    vector<ll> arr(n);
    for(ll i=0; i<n; ++i) {
        cin >> arr[i];
    }

    vector<ll> nge(n, -1);

    stack<ll> stk;
    for(ll i=0; i<n; ++i) {
        while(!stk.empty() && arr[stk.top()] < arr[i]) {
            nge[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }

    //so basically the thing is we don't have dynamic queries so for sure we wouldn't need any segment tree or fenwick tree, so we should think about prefix sum or sparse table (binary lifting on array) 
    //so here for binary lifting we need the next thing where we can go so now for this problem the next index where we can go from i is just its next greater element which can be found using stack in O(n)
    //now the thing is if we follow whole nge order from a to b it would be O(n) so we need some jumping techniques which can be done using binary lifting
    //so just apply binary lifting and then just try to make the max possible jump which we do in LCA just as same as it is

    vector<vector<ll>> dp(n, vector<ll>(20, -1));
    for(ll i=0; i<n; ++i) dp[i][0] = nge[i];

    for(ll b=1; b<20; ++b) {
        for(ll i=0; i<n; ++i) {
            if(dp[i][b-1] != -1)
                dp[i][b] = dp[dp[i][b-1]][b-1];
        }
    }

    while(q--) {
        ll a,b;
        cin >> a >> b;
        --a,--b;
        ll jumps = 0;
        for(ll i=19; i>=0; --i) {
            if(dp[a][i] != -1 && dp[a][i] <= b) {
                jumps += (1LL << i);
                a = dp[a][i];
            }
        }

        cout << jumps + 1 << "\n";
    }
    return 0;
}