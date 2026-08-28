/**
 *    author:  Meet
 *    created: 21.08.2026 15:58:32
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
    vector<vector<ll>> bit;
    ll n;
    public :
    Fenwick(ll n) {
        this->n = n;
        bit.assign(n+1, vector<ll>(n+1, 0));
    }

    void update(ll x, ll y, ll val) {
        for(ll i=x; i<=n; i += (i & (-i))) {
            for(ll j=y; j<=n; j += (j & (-j))) {
                bit[i][j] += val;
            }
        }
    }

    ll query(ll x, ll y) {
        ll ans = 0;
        for(ll i=x; i>0; i -= (i & (-i))) {
            for(ll j=y; j>0; j -= (j & (-j))) {
                ans += bit[i][j];
            }
        }
        return ans;
    }
};  

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,q;
    cin >> n >> q;

    //basically the concept is nothing new there exists 2d fenwick tree also with both the dimensions handled individually by fenwick tree (it is basically can be treated as nested fenwick trees) so we just iterate over all indexes of bit in x and also in y and we need to take every combinations of them so we run nested loop

    vector<vector<ll>> grid(n + 1, vector<ll>(n + 1, 0));

    Fenwick ft(n);
    char ch;
    for(ll i=1; i<=n; ++i) {
        for(ll j=1; j<=n; ++j) {
            cin >> ch;
            if(ch == '*') {
                grid[i][j] = 1;
                ft.update(i, j, 1);
            }
        }
    }

    while(q--) {
        ll tp;
        cin >> tp;
        if(tp == 1) {
            ll x,y;
            cin >> x >> y;
            if(grid[x][y] == 0) {
                ft.update(x, y, 1);
                grid[x][y] = 1;
            }else {
                ft.update(x, y, -1);
                grid[x][y] = 0;
            }
        }else {
            ll x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;

            ll ans = ft.query(x2, y2) - ft.query(x2, y1-1) - ft.query(x1-1, y2) + ft.query(x1-1, y1-1);
            cout << ans << "\n";
        }
    }
    return 0;
}