#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
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

const int N = (int)2e5+5;
const int M = (int)1e3+5;
const int Q = 301;
const int logN = 19;

struct node {
  int parent;
  int rank;
} dsu[M*2];

void initialize(int n) {
  REP(i,1,n) {
    dsu[i] = {i,0};
  }
}

int find_parent(int i) {
  if(dsu[i].parent != i) {
    dsu[i].parent = find_parent(dsu[i].parent);
  }
  return dsu[i].parent;
}

void dsu_union(int i, int j) {
  int x = find_parent(i);
  int y = find_parent(j);
  if(x != y) {
    if(dsu[x].rank > dsu[y].rank) {
      dsu[y].parent = x;
    }
    else {
      dsu[x].parent = y;
      if(dsu[x].rank == dsu[y].rank) {
        dsu[y].rank++;
      }
    }
  }
}

int a[M][M], b[M][M], c[M];
vector<int> v[2*M];
void dfs(int i, bool& bipartite, int col) {
  if(c[i] != -1) {
    if(c[i] != col) {
      bipartite = false;
    }
    return;
  }
  c[i] = col;
  for(auto it : v[i]) {
    if(bipartite) {
      dfs(it,bipartite,1-col);
    }
  }
}

string str;
void solve() {
  int n;
  cin >> n;
  REP(i,1,n) {
    cin >> str;
    REP(j,1,n) {
      a[i][j] = str[j-1];
    }
  }
  REP(i,1,n) {
    cin >> str;
    REP(j,1,n) {
      b[i][j] = str[j-1];
    }
  }
  initialize(2*n);
  REP(i,1,n) {
    REP(j,1,n) {
      if(a[i][j]==b[i][j]) {
        dsu_union(i,n+j);
      }
    }
  }
  REP(i,1,n) {
    REP(j,1,n) {
      if(a[i][j]!=b[i][j] && find_parent(i) == find_parent(n+j)) {
        cout << "NO";
        return;
      }
    }
  }
  REP(i,1,2*n) {
    c[i] = -1;
    v[i].clear();
  }
  REP(i,1,n) {
    REP(j,1,n) {
      if(a[i][j]!=b[i][j]) {
        int x = find_parent(i);
        int y = find_parent(n+j);
        v[x].pb(y);
        v[y].pb(x);
      }
    }
  }
  bool bipartite = true;
  REP(i,1,2*n) {
    if(bipartite && c[i] == -1) {
      dfs(i,bipartite,0);
    }
  }
  if(bipartite) {
    cout << "YES";
  }
  else {
    cout << "NO";
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
