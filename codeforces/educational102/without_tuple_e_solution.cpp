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
typedef tuple<int,int,int> ti3;
typedef pair<ll,ti3> plt3;

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
const int M = (int)3e3+5;
const int Q = 301;
const int logN = 19;

struct state {
  int i,j,k;
};
bool operator<(const state& a, const state& b) {
  if(a.i != b.i) {
    return a.i < b.i;
  }
  else if(a.j != b.j) {
    return a.j < b.j;
  }
  return a.k < b.k;
}
ll dp[N][2][2];
struct edge {
  int i,j,k,w;
};
vector<edge> v[N][2][2];
void add_edges(int x, int y, int w) {
  REP(i,0,1) {
    REP(j,0,1) {
      REP(a,i,1) {
        REP(b,j,1) {
          if(a-i+b-j==0) {
            v[x][i][j].pb({y,a,b,w});
          }
          else if(a-i+b-j==1) {
            if(a!=i) {
              //Twice-taken edge
              v[x][i][j].pb({y,a,b,2*w});
            }
            else {
              //Free-edge
              v[x][i][j].pb({y,a,b,0});
            }
          }
        }
      }
    }
  }
}
void dijkstra(int n) {
  REP(i,1,n) {
    REP(j,0,1) {
      REP(k,0,1) {
        dp[i][j][k] = lim;
      }
    }
  }
  dp[1][0][0] = 0;
  priority_queue<pair<ll,state>,vector<pair<ll,state>>,greater<pair<ll,state>>> pq;
  pq.push({0,{1,0,0}});
  while(!pq.empty()) {
    auto temp = pq.top();
    pq.pop();
    int i = temp.second.i, j = temp.second.j, k = temp.second.k;
    if(dp[i][j][k] == temp.first) {
      for(auto it : v[i][j][k]) {
        int a = it.i, b = it.j, c = it.k, w = it.w;
        if(dp[a][b][c] > temp.first + w) {
          dp[a][b][c] = temp.first + w;
          pq.push({dp[a][b][c],{a,b,c}});
        }
      }
    }
  }
}
void solve() {
  int n,m;
  cin >> n >> m;
  int x,y,w;
  REP(i,1,m) {
    cin >> x >> y >> w;
    add_edges(x,y,w);
    add_edges(y,x,w);
  }
  dijkstra(n);
  REP(i,2,n) {
    cout << min(dp[i][0][0], dp[i][1][1]) << " ";
  }
}
int main() {
    //freopen("output.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    // cin>>T;
    REP(TC,1,T) {
        //cout<<"Case #"<<TC<<": ";
        solve();
        cout<<"\n";
    }
}
