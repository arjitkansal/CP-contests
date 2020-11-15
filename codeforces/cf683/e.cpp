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
const int logN = 30;

struct node {
  int cnt = 0;
  int next_node[2] = {0,0};
} trieDS[N*30];

int root = 1;
int next_free_index = 2;

void add_to_trieDS(int val) {
  int bit = 0;
  int node_index = root;
  REPN(i,logN,0) {
    bit = (val>>i) & 1;
    trieDS[node_index].cnt++;
    if(trieDS[node_index].next_node[bit] == 0) {
      trieDS[node_index].next_node[bit] = next_free_index++;
    }
    node_index = trieDS[node_index].next_node[bit];
  }
  trieDS[node_index].cnt++;
}

int dfs(int i) {
  if(trieDS[i].cnt < 2) {
    return 0;
  }
  else if(trieDS[i].next_node[0] && trieDS[i].next_node[1]) {
    int good_0 = dfs(trieDS[i].next_node[0]);
    int good_1 = dfs(trieDS[i].next_node[1]);
    int req_deletion_0 = (trieDS[trieDS[i].next_node[0]].cnt >= 2) ? (trieDS[trieDS[i].next_node[0]].cnt - 1) : 0;
    int req_deletion_1 = (trieDS[trieDS[i].next_node[1]].cnt >= 2) ? (trieDS[trieDS[i].next_node[1]].cnt - 1) : 0;
    return min(req_deletion_0 + good_1, req_deletion_1 + good_0);
  }
  else if(trieDS[i].next_node[0]) {
    return dfs(trieDS[i].next_node[0]);
  }
  else if(trieDS[i].next_node[1]) {
    return dfs(trieDS[i].next_node[1]);
  }
  else {
    return 0;
  }
  return INT_MAX;
}

int a[N];
void solve() {
  int n;
  cin >> n;
  REP(i,1,n) {
    cin >> a[i];
    add_to_trieDS(a[i]);
  }
  cout << dfs(root);
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
