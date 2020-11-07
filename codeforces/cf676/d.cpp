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

int dx[] = {1,0,-1,-1,0,1};
int dy[] = {1,1,0,-1,-1,0};
ll dp[11][11];
bool check(int x) {
  return x>=0 && x<=10;
}
void dijkstra(ll c[]) {
  REP(i,0,10) {
    REP(j,0,10) {
      dp[i][j] = 1e18;
    }
  }
  dp[5][5] = 0;
  priority_queue<pii,vector<pii>,greater<pii>> pq;
  pq.push({0,{5,5}});
  while(!pq.empty()) {
    pii temp = pq.top();
    pq.pop();
    if(temp.first == dp[temp.second.first][temp.second.second]) {
      int dist = temp.first;
      int x = temp.second.first;
      int y = temp.second.second;
      REP(k,0,5) {
        if(check(x+dx[k]) && check(y+dy[k]) && dp[x+dx[k]][y+dy[k]] > dist + c[k]) {
          dp[x+dx[k]][y+dy[k]] = dist + c[k];
          pq.push({dist+c[k], {x+dx[k], y+dy[k]}});
        }
      }
    }
  }
  REP(k,0,5) {
    c[k] = dp[5+dx[k]][5+dy[k]];
  }
}
void solve() {
    int x,y;
    cin>>x>>y;
    ll c[6];
    REP(i,0,5) {
      cin >> c[i];
    }
    if(x==0 && y==0) {
      cout << 0;
      return;
    }
    dijkstra(c);
    ll ans = 0;
    if(x>=0 && y>=0) {
      ans += c[0] * min(x,y);
      int d;
      if(x>y) d = 5;
      else d = 1;
      ans += c[d] * abs(x-y);
    }
    else if(x>=0 && y<=0) {
      ans += c[5] * x;
      ans += c[4] * abs(y);
    }
    else if(x<=0 && y>=0) {
      ans += c[2] * abs(x);
      ans += c[1] * y;
    }
    else if(x<=0 && y<=0) {
      x = abs(x), y = abs(y);
      ans += c[3] * min(x,y);
      int d;
      if(x>y) d = 2;
      else d = 4;
      ans += c[d] * abs(x-y);
    }
    cout << ans;
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
