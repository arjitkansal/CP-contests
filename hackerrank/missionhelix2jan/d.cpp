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

const int N = (int)1e4+5;
const int M = (int)3e3+5;
const int Q = 301;
const int logN = 19;

double x[N], y[N], z[N];
double a, b, c;
double vp, vs;

bool whether_thief_can_be_catched(double time_elasped_for_thief, int i) {
  double time_for_thief = sqrt(sq(x[i]-x[i-1]) + sq(y[i]-y[i-1]) + sq(z[i]-z[i-1])) + vs * time_elasped_for_thief;
  double time_for_person = sqrt(sq(x[i]-a) + sq(y[i]-b) + sq(z[i]-c));
  return (time_for_thief * vp + 1e-9 < time_for_person * vs);
}

double x_angle(int i) {
  double den = sqrt(sq(x[i]-x[i-1]) + sq(y[i]-y[i-1]) + sq(z[i]-z[i-1]));
  return (x[i]-x[i-1])/den;
}

double y_angle(int i) {
  double den = sqrt(sq(x[i]-x[i-1]) + sq(y[i]-y[i-1]) + sq(z[i]-z[i-1]));
  return (y[i]-y[i-1])/den;
}

double z_angle(int i) {
  double den = sqrt(sq(x[i]-x[i-1]) + sq(y[i]-y[i-1]) + sq(z[i]-z[i-1]));
  return (z[i]-z[i-1])/den;
}

vector<double> thief_position(int i, double t) {
  double _x = x[i-1] + vs * t * x_angle(i);
  double _y = y[i-1] + vs * t * y_angle(i);
  double _z = z[i-1] + vs * t * z_angle(i);
  return {_x,_y,_z};
}

double time_for_person_to_reach_position(vector<double>& position) {
  double time_for_person = sqrt(sq(position[0]-a) + sq(position[1]-b) + sq(position[2]-c)) / vp;
  return time_for_person;
}

bool whether_thief_can_be_catched_in_between(double time_elasped_for_thief, double allowed_time, int i) {
  vector<double> target_position = thief_position(i, allowed_time - time_elasped_for_thief);
  return (allowed_time + 1e-9 < time_for_person_to_reach_position(target_position));
}

vector<double> calc_min_time_to_catch_thief(double time_elasped_for_thief, int i) {
  double lo = time_elasped_for_thief, hi = 1e9, mi;
  REP(i,0,70) {
    mi = (lo + hi)/2.0;
    if(whether_thief_can_be_catched_in_between(time_elasped_for_thief, mi, i)) {
      hi = mi;
    }
    else {
      lo = mi;
    }
  }
  vector<double> thief_position_catched_at = thief_position(i, lo - time_elasped_for_thief);
  thief_position_catched_at.insert(thief_position_catched_at.begin(), lo);
  return thief_position_catched_at;
}
void solve() {
  int n;
  cin >> n;
  REP(i,0,n) {
    cin >> x[i] >> y[i] >> z[i];
  }
  cin >> vp >> vs;
  cin >> a >> b >> c;
  if(x[0] == a && y[0] == b && z[0] == c) {
    cout << 0;
    return;
  }

  bool ok = false;
  vector<double> ans = {1e18, 1e18, 1e18, 1e18};
  double time_elasped_for_thief = 0.0;
  REP(i,1,n) {
    if(whether_thief_can_be_catched(time_elasped_for_thief, i)) {
      ok = true;
      vector<double> v = calc_min_time_to_catch_thief(time_elasped_for_thief,i);
      if(v[0] + 1e-9 < ans[0]) {
        ans = v;
      }
    }
    time_elasped_for_thief += (sq(x[i]-x[i-1]) + sq(y[i]-y[i-1]) + sq(z[i]-z[i-1])) / vs;
  }
  if(!ok) {
    cout << -1;
    return;
  }

  cout << fixed << setprecision(20);
  for(auto it:ans) {
    cout << it << "\n";
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
