/**
 *    author:  Meet
 *    created: 21.08.2026 01:11:02
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

    vector<pair<ll,ll>> arr(n);
    vector<ll> start(n);
    ll mx = 0;
    for(ll i=0; i<n; ++i) {
        ll s,e;
        cin >> s >> e;
        start[i] = s;
        arr[i] = {s, e};
        mx = max(mx, e);
    }

    //so the idea is to basically enforce greedy choice of scheduling into queries
    //we always prefer earliest ending time so that we can get more room for the future ones remaining 
    //here what we do is basically define next[t] as the earliest ending time for all the movies who has starting time >= t
    //this thing we can do with sweeping over starting time backwards so at any time t we will be always processed all the > t so we just maintain a minEnd which denotes the minimum end time for all movies who has starting time >= t
    //next[t] = minEnd itself 
    //now all the times will not be covered so we have to loop over times and then for any t (lower_bound(start, t) - start.begin()) will find me the ind which has some movie starting at it and it is already processed and since it is lower_bound there is no movie starting in between t and this ind so we can simply imply next[t] = next[start[ind]] because there is no option for t till start[ind] to watch a movie as there is no one starting in between so we can always go onto the start[ind] directly 

    //now all t has some next[t] if not then -1 but all are there
    //so we now just apply binary lifting and then it is pretty easy

    sort(whole(arr), greater<pair<ll,ll>>());
    sort(whole(start));

    vector<ll> next(mx + 1, -1);

    ll minEnd = INF;
    for(ll i=0; i<n; ++i) {
        ll s = arr[i].first, e = arr[i].second;
        minEnd = min(minEnd, e);

        if(next[s] != -1) next[s] = min(next[s], minEnd);
        else next[s] = minEnd;
    }

    for(ll t=0; t<=mx; ++t) {
        ll ind = lower_bound(whole(start), t) - start.begin();
        if(ind < n) next[t] = next[start[ind]];
    }

    vector<vector<ll>> dp(mx + 1, vector<ll>(LOG, -1));

    for(ll t=0; t<=mx; ++t) dp[t][0] = next[t];

    for(ll b=1; b<LOG; ++b) {
        for(ll t=0; t<=mx; ++t) {
            if(dp[t][b-1] != -1)
                dp[t][b] = dp[dp[t][b-1]][b-1];
        }
    }

    while(q--) {
        ll a,b;
        cin >> a >> b;

        ll ans = 0;
        for(ll i=LOG-1; i>=0; --i) {
            if(dp[a][i] != -1 && dp[a][i] <= b) {
                ans += (1LL << i);
                a = dp[a][i];
            }
        }

        cout << ans << "\n";
    }
    return 0;
}