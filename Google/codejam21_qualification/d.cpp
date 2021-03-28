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

int n,q,m[51][51][51];
int question_exchange(int i, int j, int k) {
  if(i==j || i==k || j==k) {
    return -1;
  }
  int sum = i+j+k;
  int x = max({i,j,k}), y = min({i,j,k});
  j = sum-x-y, i = x, k = y;
  if(m[i][j][k] != -1) {
    return m[i][j][k];
  }
  assert(q>0); q--;
  cout << i << " " << j << " " << k << endl;
  cin >> m[i][j][k];
  assert(m[i][j][k] != -1);
  return m[i][j][k];
}
void solve() {
  mms(m,-1);
  vector<int> ans = {0,1,2};
  REP(i,3,n) {
    if(question_exchange(ans[1],ans[i-1],i) == ans[1]) {
      ans.insert(ans.begin()+1,i);
    }
    else if(question_exchange(ans[1],ans[i-1],i) == ans[i-1]) {
      ans.pb(i);
    }
    else if(i==3) {
      ans.insert(ans.begin()+2,i);
    }
    else {
      // int lo = 2, hi = i-1, mi1, mi2;
      // while(lo < hi) {
      //   // Ternary search
      //   mi1 = lo + (hi - lo)/3;
      //   mi2 = hi - (hi - lo)/3;
      //   if(question_exchange(ans[1],ans[mi2],i) != i) {
      //     lo = mi2+1;
      //   }
      //   else if(question_exchange(ans[1],ans[mi1],i) == i) {
      //     hi = mi1;
      //   }
      //   else {
      //     lo = mi1+1;
      //     hi = mi2;
      //   }
      // }
      int lo = 2, hi = i-1, mi;
      while(lo < hi) {
        mi = (lo+hi)/2;
        if(question_exchange(ans[1],ans[mi],i) == i) {
          hi = mi;
        }
        else {
          lo = mi+1;
        }
      }
      ans.insert(ans.begin()+lo,i);
    }
  }
  REP(i,1,n) {
    cout << ans[i] << " ";
  }
}
int main() {
    //freopen("output.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    cin>>T>>n>>q;
    REP(TC,1,T) {
        // cout<<"Case #"<<TC<<": ";
        solve();
        cout<<endl;
        int resp;
        cin >> resp;
        // cerr << "\nJudge ka response: " << resp << endl;
        assert(resp == 1);
    }
}
