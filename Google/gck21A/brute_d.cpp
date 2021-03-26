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

int a[4][4], b[4][4], r[4], c[4], cr[4], cc[4], ii[4][4];
int get_req_time(int mask, int n) {
  mms(cr,0);
  mms(cc,0);
  mms(ii,0);
  int tot_time = 0, ind = 0, tot = 0;
  REP(i,0,n-1) {
    REP(j,0,n-1) {
      if(a[i][j] == -1) {
        if(mask&(1<<ind)) {
          ii[i][j] = 1;
          tot_time += b[i][j];
        }
        else {
          tot++;
          cr[i]++;
          cc[j]++;
        }
      }
      ind++;
    }
  }
  set<int> rows, cols;
  REP(i,0,n-1) {
    if(cr[i] == 1) {
      rows.insert(i);
    }
    if(cc[i] == 1) {
      cols.insert(i);
    }
  }
  while(!rows.empty() || !cols.empty()) {
    if(!rows.empty()) {
      int r = *(rows.begin());
      rows.erase(r);
      REP(i,0,n-1) {
        if(!ii[r][i] && a[r][i] == -1) {
          ii[r][i] = 1;
          tot--;
          cc[i]--;
          cr[r]--;
          if(cc[i] != 1 && cols.count(i)) {
            cols.erase(i);
          }
          else if(cc[i] == 1 && !cols.count(i)) {
            cols.insert(i);
          }
          break;
        }
      }
    }
    else {
      int c = *(cols.begin());
      cols.erase(c);
      REP(i,0,n-1) {
        if(!ii[i][c] && a[i][c] == -1) {
          ii[i][c] = 1;
          tot--;
          cc[c]--;
          cr[i]--;
          if(cr[i] != 1 && rows.count(i)) {
            rows.erase(i);
          }
          else if(cr[i] == 1 && !rows.count(i)) {
            rows.insert(i);
          }
          break;
        }
      }
    }
  }
  return (tot) ? INT_MAX : tot_time;
}
void solve() {
  int n;
  cin >> n;
  assert(n<=4);
  REP(i,0,n-1) {
    REP(j,0,n-1){
      cin >> a[i][j];
    }
  }
  REP(i,0,n-1) {
    REP(j,0,n-1){
      cin >> b[i][j];
    }
  }
  // REP(i,0,n-1) {
  //   cin >> r[i];
  // }
  // REP(i,0,n-1) {
  //   cin >> c[i];
  // }
  int ans = INT_MAX, m = (1<<(n*n)), optimalMask;
  REP(mask,0,m-1) {
    int ret = get_req_time(mask,n);
    if(ret < ans) {
      optimalMask = mask;
      ans = ret;
    }
    // ans = min(ans, get_req_time(mask,n));
  }
  cout << optimalMask;
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
        cout<<"Case #"<<TC<<": ";
        solve();
        cout<<"\n";
    }
}
