/**
 *    author:  Meet
 *    created: 21.08.2026 00:17:49
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

const ll LOG = 20;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,q;
    cin >> n >> q;

    vector<ll> arr(n);
    for(ll i=0; i<n; ++i) cin >> arr[i];

    //the main thing to notice is that for range [a...b] the minimum value any index i between a to b can have is basically max(arr[a], arr[a+1], ..., arr[i])
    //so problem becomes count the sum of (max(arr[a], arr[a+1], ..., arr[i]) - arr[i]) for all index i from [a...b]
    //now see this observation that maxi changes only when next greater element appear for any index i so what we gonna do is basically find the nge for all using stack then we again use the binary lifting
    //val[i][0] is the extra things we need to add between the i and nge of i is basically nothing but (ele * arr[i]) - sum[i...nge[i-1]] why because all of them must be at least arr[i] and sum we already have so this is the thing we need to add there

    vector<ll> nge(n, -1);
    stack<ll> stk;

    for(ll i=0; i<n; ++i) {
        while(!stk.empty() && arr[stk.top()] < arr[i]) {
            nge[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }

    vector<ll> pf(n + 1, 0);
    for(ll i=1; i<=n; ++i) pf[i] = pf[i-1] + arr[i-1];

    vector<vector<ll>> dp(n, vector<ll>(LOG, -1)), val(n, vector<ll>(LOG, 0));

    for(ll i=0; i<n; ++i) {
        dp[i][0] = nge[i];
        if(nge[i] != -1) {
            ll ele = nge[i] - i;
            ll sum = pf[nge[i]] - pf[i];
            val[i][0] = (arr[i] * ele) - sum;
        }
    }

    for(ll b=1; b<LOG; ++b) {
        for(ll i=0; i<n; ++i) {
            val[i][b] = val[i][b-1];
            if(dp[i][b-1] != -1) {
                dp[i][b] = dp[dp[i][b-1]][b-1];
                val[i][b] += val[dp[i][b-1]][b-1];
            }
        }
    }
    
    while(q--) {
        ll a,b;
        cin >> a >> b;
        --a,--b;

        ll ans = 0;
        for(ll i=LOG-1; i>=0; --i) {
            if(dp[a][i] != -1 && dp[a][i] <= b) {
                ans += val[a][i];
                a = dp[a][i];
            }
        }

        //this is the important thing we will be at somewhere <= b at the end so we still have a...b remaining range which will have maxi as arr[a] so add its contribution
        ll rem = (b - a + 1)*arr[a] - (pf[b + 1] - pf[a]);
        ans += rem;

        cout << ans << "\n";
    }
    return 0;
}