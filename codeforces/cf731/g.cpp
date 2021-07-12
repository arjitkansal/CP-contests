#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define unvisited (-3)
#define inf (-1)
#define mod ((int)1e9+7)
#define lim 1000000000000000007
#define lim1 18446744073709551615  //Unsigned
#define sq(a) ((a)*(a))
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define mms(v,i) memset(v,i,sizeof(v))
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define REP(i,a,b) for (int i = a; i <= b; i++)
#define REPN(i,a,b) for (int i = a; i >= b; i--)
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int,int> pi;
typedef pair<ll,ll> PL;
typedef pair<ll,int> PLI;
typedef pair<int,ll> PIL;
typedef pair<int,pair<int,int> > pii;
typedef pair<double,double> pdd;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
ll power(ll a,ll b) {
   a %= mod;
   ll res=1;
   while(b){
      if(b%2==1) res=(res*a)%mod;
      a=(a*a)%mod;
      b>>=1;
   }
   return res;
}
ll gcdll(ll a,ll b) {
    if (b==0) return a;
    return gcdll(b,a%b);
}
int gcd(int a,int b) {
    if (b==0) return a;
    return gcd(b,a%b);
}

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

const int N = (int)4e5+5;
const int M = (int)3e3+5;
const int Q = 301;
const int logN = 19;

int a[N], comp[N];
int freq[N], indegree[N];
bool selfLoop[N];
vector<int> v[N], rv[N], order;
set<int> kv[N];
bool vis[N];
void dfs(int i) {
    if(vis[i]) {
        return;
    }
    vis[i] = true;
    for(auto it: v[i]) {
        dfs(it);
    }
    order.pb(i);
}
void dfs1(int i, int& c) {
    if(vis[i]) {
        return;
    }
    vis[i] = true;
    comp[i] = c;
    freq[c]++;
    if(selfLoop[i]) {
        freq[c]++;
    }
    for(auto it : rv[i]) {
        dfs1(it,c);
    }
}
int kosaraju(int n) {
    order.clear();
    int t = 0;
    REP(i,1,n) {
        vis[i] = false;
        rv[i].clear();
        kv[i].clear();
    }
    REP(i,1,n) {
        if(!vis[i]) {
            dfs(i);
        }
    }
    REP(i,1,n) {
        for(auto it:v[i]) {
            rv[it].pb(i);
        }
        vis[i] = false;
    }
    reverse(all(order));
    int c = 1;
    for(auto i : order) {
        dfs1(i,c);
        c++;
    }
    REP(i,1,n) {
        for(auto it:v[i]) {
            if(comp[i] != comp[it]) {
                kv[comp[i]].insert(comp[it]);
            }
        }
    }
    return c-1;
}
void solve() {
    int n,m;
    cin >> n >> m;
    REP(i,1,n) {
        v[i].clear();
        comp[i] = -1;
        freq[i] = 0;
        a[i] = unvisited;
        selfLoop[i] = false;
        indegree[i] = 0;
    }
    int x,y;
    REP(i,1,m) {
        cin >> x >> y;
        if(x == y) {
            selfLoop[x] = true;
        }
        else {
            v[x].pb(y);
        }
    }
    int c = kosaraju(n);
    REP(i,1,c) {
        for(auto it : kv[i]) {
            indegree[it]++;
        }
    }
    queue<int> q;
    REP(i,1,c) {
        //cout << indegree[i] << " ";
        if(!indegree[i]) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        x = q.front();
        q.pop();
        if(a[x] == unvisited) {
            if(x == comp[1]) {
                a[x] = (freq[x] > 1) ? inf : 1;
            }
        }
        else {
            if(freq[x] > 1) {
                a[x] = inf;
            }
        }
        for(auto y : kv[x]) {
            indegree[y]--;
            if(!indegree[y]) {
                q.push(y);
            }
            if(a[x] == unvisited || a[y] == inf) {
                continue;
            }
            if(a[x] == inf || a[x] == 2) {
                a[y] = a[x];
            }
            else {
                a[y] = (a[y] == unvisited) ? 1 : 2;
            }
        }
    }
    REP(i,1,n) {
        x = comp[i];
        //cout << x << " ";
        cout << ((a[x] == unvisited) ? 0 : a[x]) << " ";
    }
}
int main() {
    //freopen("output.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    cin>>T;
    REP(TC,1,T) {
        //cout<<"Case #"<<TC<<": ";
        solve();
        cout<<"\n";
    }
}
