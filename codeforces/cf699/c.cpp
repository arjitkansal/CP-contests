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

const int N = (int)1e5+5;
const int M = (int)3e3+5;
const int Q = 301;
const int logN = 19;

int a[N], b[N], c[N], cnt_equal[N], cnt_diff[N], freq[N];
vector<int> plank_equal[N], plank_diff[N];
void solve() {
  int n,m;
  cin >> n >> m;
  REP(i,1,n) {
    cnt_equal[i] = cnt_diff[i] = freq[i] = 0;
    plank_equal[i].clear();
    plank_diff[i].clear();
  }
  REP(i,1,n) {
    cin >> a[i];
  }
  REP(i,1,n) {
    cin >> b[i];
    if(a[i] == b[i]) {
      cnt_equal[b[i]]++;
      plank_equal[b[i]].pb(i);
    }
    else {
      cnt_diff[b[i]]++;
      plank_diff[b[i]].pb(i);
    }
  }
  REP(i,1,m) {
    cin >> c[i];
    freq[c[i]]++;
  }
  REP(i,1,n) {
    if(a[i] != b[i]) {
      if(!freq[b[i]]) {
        cout << "NO";
        return;
      }
      freq[b[i]]--;
    }
  }
  if(cnt_equal[c[m]] + cnt_diff[c[m]] == 0) {
    cout << "NO";
    return;
  }
  vector<int> ans(m+1);
  REP(i,1,m) {
    if(cnt_diff[c[i]]) {
      cnt_diff[c[i]]--;
      ans[i] = plank_diff[c[i]].back();
      plank_diff[c[i]].ppb();
      cnt_equal[c[i]]++;
      plank_equal[c[i]].pb(ans[i]);
    }
    else if(cnt_equal[c[i]]) {
      // cnt_equal[c[i]]--;
      ans[i] = plank_equal[c[i]].back();
      // plank_equal[c[i]].ppb();
    }
    else {
      int j;
      if(cnt_diff[c[m]]) {
        cnt_diff[c[m]]--;
        j = plank_diff[c[m]].back();
        plank_diff[c[m]].ppb();
        // cnt_equal[c[i]]++;
        // plank_equal[c[i]].pb(ans[i]);
      }
      else {
        cnt_equal[c[m]]--;
        j = plank_equal[c[m]].back();
        plank_equal[c[m]].ppb();
      }
      ans[i] = j;
      cnt_diff[c[m]]++;
      plank_diff[c[m]].pb(j);
    }
  }
  cout << "YES\n";
  REP(i,1,m) {
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
    cin>>T;
    REP(TC,1,T) {
        //cout<<"Case #"<<TC<<": ";
        solve();
        cout<<"\n";
    }
}
