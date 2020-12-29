#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define mod ((int)1e9+9)
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

const int N = (1<<20)+5;
const int M = (int)3e3+5;
const int Q = 301;
const int logN = 19;

ll c = ((int)1e9+7), inv = power(c,mod-2);
string s;
unordered_map<ll,bool,custom_hash> mp;
void blockNotAllowedSubstrings(string& s, int n, int k) {
  mp.clear();
  ll p = 1, hash = 0;
  REP(i,1,n) {
    hash = (hash + ('1'-s[i-1]) * p * c) % mod;
    if(i<=k) {
      p = (p * c) % mod;
    }
    else {
      hash -= (c * ('1' - s[i-k-1]));
      hash = (hash * inv) % mod;
      if(hash < 0) {
        hash += mod;
      }
    }
    if(i>=k) {
      mp[hash] = true;
    }
  }
}
string getBitString(int i, int k) {
  string bitString = "";
  while(k--) {
    bitString += (char)('0'+(i&1));
    i>>=1;
  }
  reverse(all(bitString));
  return (i ? "-1" : bitString);
}
ll calculateHash(string& bitString) {
  ll p = 1, hash = 0;
  for(auto bit : bitString) {
    p = (p * c) % mod;
    hash = (hash + (bit-'0') * p) % mod;
  }
  return hash;
}
int checkIfUnblocked(int i, int k, int actual_k) {
  string bitString = getBitString(i,k);
  if(bitString == "-1") {
    return -1;
  }
  ll hash = (calculateHash(bitString) * power(c,actual_k-k)) % mod;
  return !mp.count(hash);
}
void solve() {
    int n,k;
    cin >> n >> k >> s;
    blockNotAllowedSubstrings(s,n,k);
    REP(i,0,N-1) {
      int res = checkIfUnblocked(i,min(20,k),k);
      if(res == -1) {
        break;
      }
      else if(res) {
        cout << "YES\n" << getBitString(i,k);
        return;
      }
    }
    cout << "NO";
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
