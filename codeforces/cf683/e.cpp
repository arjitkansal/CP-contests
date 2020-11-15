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

void remove_from_trieDS(int val) {
  int bit = 0;
  int node_index = root;
  REPN(i,logN,0) {
    bit = (val>>i) & 1;
    trieDS[node_index].cnt--;
    assert(trieDS[node_index].next_node[bit] > 0);
    node_index = trieDS[node_index].next_node[bit];
  }
  trieDS[node_index].cnt--;
}

int get_value_with_min_xor(int val) {
  int ret = 0;
  int bit = 0;
  int node_index = root, index_with_same_bit;
  REPN(i,logN,0) {
    bit = (val>>i) & 1;
    index_with_same_bit = trieDS[node_index].next_node[bit];
    if(trieDS[index_with_same_bit].cnt > 0) {
      node_index = index_with_same_bit;
      if(bit) ret += (1<<i);
    }
    else {
      node_index = trieDS[node_index].next_node[1-bit];
      if(!bit) ret += (1<<i);
    }
  }
  return ret;
}

int double_edges = 0;
map<pi,bool> edges;
void add_edge(int i, int j) {
  assert(i!=j);
  if(i>j) {
    swap(i,j);
  }
  if(edges.count(make_pair(i,j))) {
    double_edges++;
  }
  else {
    edges[make_pair(i,j)] = true;
  }
}

int a[N];
void solve() {
  int n;
  cin >> n;
  REP(i,1,n) {
    cin >> a[i];
    add_to_trieDS(a[i]);
  }
  REP(i,1,n) {
    remove_from_trieDS(a[i]);
    int val = get_value_with_min_xor(a[i]);
    add_edge(val,a[i]);
    add_to_trieDS(a[i]);
  }
  assert(double_edges != 0);
  cout << (double_edges - 1);
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
