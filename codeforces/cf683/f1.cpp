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
const int Q = 101;
const int logN = 19;

int freq[Q];
int a[N], pref[N];
unordered_map<int,int,custom_hash> first_index_with_prefix_val;
int get_longest_valid_subarray_length(int n, int first_element, int second_element) {
  first_index_with_prefix_val.clear();
  first_index_with_prefix_val[0] = 0;
  int longest_valid_subarray_length = 0;
  REP(i,1,n) {
    pref[i] = pref[i-1];
    if(a[i] == first_element) {
      pref[i]--;
    }
    else if(a[i] == second_element) {
      pref[i]++;
    }
    if(first_index_with_prefix_val.count(pref[i])) {
      longest_valid_subarray_length = max(longest_valid_subarray_length, i-first_index_with_prefix_val[pref[i]]);
    }
    else {
      first_index_with_prefix_val[pref[i]] = i;
    }
  }
  return longest_valid_subarray_length;
}
void solve() {
    int n;
    cin>>n;
    REP(i,1,n) {
      cin >> a[i];
      freq[a[i]]++;
    }
    int most_frequent_element = 0;
    REP(i,1,100) {
      if(freq[i] > freq[most_frequent_element]) {
        most_frequent_element = i;
      }
    }

    int longest_valid_subarray_length = 0;
    REP(j,1,100) {
      if(most_frequent_element != j) {
        int len = get_longest_valid_subarray_length(n,most_frequent_element,j);
        if(longest_valid_subarray_length < len) {
          longest_valid_subarray_length = len;
        }
      }
    }
    cout << longest_valid_subarray_length;
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
