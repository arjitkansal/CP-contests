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
const int Q = 501;
const int logN = 19;

vector<pi> edges;
unordered_map<int,int> salary;
int a[Q][Q], nfi = 0, head;
void rec(vector<int>& v, int p) {
  if(v.size() == 1) {
    assert(p != -1);
    edges.pb({v[0],p});
    salary[v[0]] = a[v[0]][v[0]];
    return;
  }
  int max_salary = 0;
  REP(i,1,v.size()-1) {
    max_salary = max(max_salary, a[v[0]][v[i]]);
  }
  int curr_index = nfi++;
  salary[curr_index] = max_salary;
  if(p == -1) {
    head = curr_index;
  }
  else {
    edges.pb({curr_index, p});
  }
  vector<int> subtree_nodes;
  while(!v.empty()) {
    int k = v[0];
    subtree_nodes.pb(k);
    swap(v[0],v[v.size()-1]);
    v.ppb();
    REP(i,0,(int)v.size()-1) {
      if(a[k][v[i]] != max_salary) {
        subtree_nodes.pb(v[i]);
        swap(v[i],v[v.size()-1]);
        v.ppb();
        i--;
      }
    }
    rec(subtree_nodes,curr_index);
    subtree_nodes.clear();
  }
}
void solve() {
  int n;
  cin >> n;
  nfi = n+1;
  REP(i,1,n) {
    REP(j,1,n) {
      cin >> a[i][j];
    }
  }
  vector<int> v;
  REP(i,1,n) {
    v.pb(i);
  }
  rec(v,-1);

  int k = nfi-1;
  assert(edges.size() == k-1);
  cout << k << "\n";
  REP(i,1,k) {
    cout << salary[i] << " ";
  }
  cout << "\n";
  cout << head << "\n";
  for(auto it : edges) {
    cout << it.first << " " << it.second << "\n";
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
        // cout<<"\n";
    }
}
