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

int a[N], b[N];
int max_special_boxes_cnt(vector<int>& initial_positions, vector<int>& special_positions) {
  int n = initial_positions.size(), m = special_positions.size();
  if(!min(n,m)) {
    return 0;
  }
  vector<int> cnt_suffix_already_special(n+1);
  for(int i=n-1,j=m-1;i>=0;i--) {
    while(j>0 && special_positions[j]>initial_positions[i]) {
      j--;
    }
    cnt_suffix_already_special[i] = cnt_suffix_already_special[i+1];
    if(special_positions[j] == initial_positions[i]) {
      ++cnt_suffix_already_special[i];
    }
  }

  int ans = 0;
  for(int i=0,j=0,k=0,r=0;k<m;k++) {
    if(special_positions[k] < initial_positions[0]) {
      continue;
    }
    while(j<n-1 && initial_positions[j+1]<=special_positions[k]+j-i) {
      ++j;
    }
    while(r<m-1 && special_positions[r+1]<=special_positions[k]+j-i) {
      ++r;
    }
    ans = max(ans, r-k+1 + cnt_suffix_already_special[j+1]);
  }
  return ans;
}
void solve() {
  int n,m;
  cin >> n >> m;
  vector<int> pos, neg;
  REP(i,1,n) {
    cin >> a[i];
    if(a[i] > 0) pos.pb(a[i]);
    else neg.pb(-a[i]);
  }

  vector<int> spos, sneg;
  REP(i,1,m) {
    cin >> b[i];
    if(b[i] > 0) spos.pb(b[i]);
    else sneg.pb(-b[i]);
  }
  reverse(all(neg));
  reverse(all(sneg));

  cout << max_special_boxes_cnt(pos,spos) + max_special_boxes_cnt(neg,sneg);
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
