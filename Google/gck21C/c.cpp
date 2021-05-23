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
const int M = (int)3e3+5;
const int Q = 301;
const int logN = 19;

int w,e;
double dp[61][61][61];
void calc(double& er, double& es, double& ep, int i, int r, int p, int s) {
  if(i>1){
    er = ((double)(w*p + e*s))/(i-1);
    es = ((double)(w*r + e*p))/(i-1);
    ep = ((double)(w*s + e*r))/(i-1);
  } else {
    er = es = ep = ((double)(w + e))/3.0;
  }
}
double rec(int i, int r, int p, int s) {
  if(i == 0) {
    return 0.0;
  }
  else if(dp[i][r][p] != -1.0) {
    return dp[i][r][p];
  }
  double er, es, ep;
  calc(er,es,ep,i,r,p,s);
  double v1 = (r>0) ? (er + rec(i-1,r-1,p,s)) : -1.0;
  double v2 = (p>0) ? (ep + rec(i-1,r,p-1,s)) : -1.0;
  double v3 = (s>0) ? (es + rec(i-1,r,p,s-1)) : -1.0;
  dp[i][r][p] = max({v1,v2,v3});
  return dp[i][r][p];
}
void backtrack(string& moves, int i, int r, int p, int s) {
  if(i==0) {
    return;
  }
  double er, es, ep;
  calc(er,es,ep,i,r,p,s);
  double score = dp[i][r][p];
  if(r>0 && score == er + dp[i-1][r-1][p]) {
    backtrack(moves,i-1,r-1,p,s);
    moves += 'R';
  }
  else if(p>0 && score == ep + dp[i-1][r][p-1]) {
    backtrack(moves,i-1,r,p-1,s);
    moves += 'P';
  }
  else {
    assert(s>0);
    backtrack(moves,i-1,r,p,s-1);
    moves += 'S';
  }
}
void solve(int x) {
    cin >> w >> e;
    REP(i,1,60) {
      REP(j,0,60) {
        REP(k,0,60) {
          dp[i][j][k] = -1.0;
        }
      }
    }
    double maxScore = -1.0;
    int optimal_r, optimal_s, optimal_p;
    REP(r,0,60) {
      REP(p,0,60-r) {
        int s = 60-r-p;
        double score = rec(60,r,p,s);
        if(score > maxScore) {
          maxScore = score;
          optimal_s = s;
          optimal_r = r;
          optimal_p = p;
        }
      }
    }
    string moves = "";
    backtrack(moves, 60, optimal_r, optimal_p, optimal_s);
    cout << moves;
}
int main() {
    //freopen("output.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T=1, x;
    cin>>T>>x;
    REP(TC,1,T) {
        cout<<"Case #"<<TC<<": ";
        solve(x);
        cout<<"\n";
    }
}
