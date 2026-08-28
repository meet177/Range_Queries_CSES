/**
 *    author:  Meet
 *    created: 18.08.2026 12:21:13
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

struct event {
    ll queryId;
    ll val; //<= val 
    ll sign; //+1 or -1
};

class Fenwick {
    vector<ll> bit;
    ll n;
    public :
    Fenwick(ll _n) {
        n = _n;
        bit.assign(n+1, 0);
    }

    void add(ll id, ll val) {
        for(; id<=n; id += (id & (-id))) {
            bit[id] += val;
        }
    }

    ll query(ll id) {
        ll ans = 0;
        for(; id>0; id -= (id & (-id))) {
            ans += bit[id];
        }
        return ans;
    }
};      

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    //see the first approach would be very easy to come which is make a segment tree where each node will contain all the values in sorted order of their responsibility range, then for each query we go to the query range and try to find the cnt using upper bound and lower bound which would cause logn so it would be O(nlogn * logn = n*log^2(n))
    //so that would be good but for cses it is overflowing so we need to go with the offline query processing + fenwick tree
    //see we have two dimensions so we need to work with one dimension because in two dimensions it is 1e10 around elements and we cannot work with it directly
    //so what we do is basically take the index dimension as sweep dimension on which we will iterate from left to right and then make a query for the value dimension
    //so very natural definition would be F(b, d) as the cnt of numbers which have index <= b and value <= d
    //when we visualize the whole problem as a rectangle counting problem in 2d space we see that the answer for any rectangle described by (a,b,c,d) is basically 2d inclusion exclusion which is F(b,d) - F(a-1,d) - F(b,c-1) + F(a-1,c-1)
    //now we iterate from left to right on index so at any b we have only the values which have index <= b and we want to find count of numbers from [1..b] who have value <= d this can be done using fenwick tree easily hence second dimension can be handled using fenwick tree
    //so go through queries and make it offline and store whole event structure with queryId as we will need it to increase the counts and also for printing at the end, then we need val for whom <= val is needed and we need sign of the operation as in the prefix inclusion exclusion there is both + and -
    //now after this we iterate in the indexes left to right and for each i we add it to fenwick tree using compressed index (as values are 1e9 we cannot work with it directly in fenwick tree) and then for that particular i we go through all the events happening at that instance and find the compressed index of the value and then just basic fenwick query will give me the result and we add it to the queryId's cnt
     
    ll n,q;
    cin >> n >> q;

    vector<ll> arr(n+1);
    vector<ll> temp;
    for(ll i=1; i<=n; ++i) {
        cin >> arr[i];
        temp.push_back(arr[i]);
    }

    sort(temp.begin(), temp.end());
    temp.erase(unique(whole(temp)), temp.end());

    vector<vector<event>> events(n + 1);

    for(ll i=0; i<q; ++i) {
        ll a,b,c,d;
        cin >> a >> b >> c >> d;
        events[b].push_back({i, d, 1}); // F(b, d)
        events[a-1].push_back({i, d, -1}); //F(a-1, d)

        events[b].push_back({i, c-1, -1}); //F(b, c-1)
        events[a-1].push_back({i, c-1, 1}); //F(a-1, c-1)
    }   

    vector<ll> cnt(q, 0);

    Fenwick ft(n);
    //take index as sweep dimension
    for(ll i=1; i<=n; ++i) {
        ll id = lower_bound(whole(temp), arr[i]) - temp.begin() + 1;
        ft.add(id, 1);

        for(auto& e : events[i]) {
            ll ind = upper_bound(whole(temp), e.val) - temp.begin() + 1;
            --ind;
            cnt[e.queryId] += (e.sign * ft.query(ind));
        }
    }

    for(ll i=0; i<q; ++i) cout << cnt[i] << "\n";
    return 0;
}