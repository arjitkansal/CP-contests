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

string s[8];
int mask[8], cnt[1<<8], valid[1<<8][1<<8];
ll dp[8][1<<8][9];
bool validMasks(int curr, int prev, int n) {
    vector<pi> ranges;
    int dp[n+1] = {0};
    int l = -1, r;
    REP(i,0,n-1) {
        dp[i+1] = dp[i];
        if((1<<i)&prev) {
            dp[i+1]++;
        }
        if((1<<i)&curr) {
            if(l == -1) {
                l = i;
            }
        }
        else {
            if(l != -1) {
                ranges.pb({l+1,i});
                l = -1;
            }
        }
    }
    if(l != -1) {
        ranges.pb({l+1,n});
    }
    if(prev == 0) {
        return false;
    }
    for(auto it : ranges) {
        if(dp[it.second] == dp[it.first-1]) {
            return false;
        }
    }
    return true;
}

bool oneStretch(int mask, int n) {
    vector<pi> ranges;
    int l = -1, r;
    REP(i,0,n-1) {
        if((1<<i)&mask) {
            if(l == -1) {
                l = i;
            }
        }
        else {
            if(l != -1) {
                ranges.pb({l+1,i});
                l = -1;
            }
        }
    }
    if(l != -1) {
        ranges.pb({l+1,n});
    }
    return (ranges.size() <= 1);
}

void solve() {
    int n,k;
    cin >> n >> k;
    REP(i,0,(1<<n)-1) {
        REP(j,0,(1<<n)-1) {
            valid[i][j] = validMasks(i,j,n);
        }
    }
    REP(i,0,n-1) {
        cin >> s[i];
        REP(j,0,n-1) {
            if(s[i][j] == '.') {
                mask[i] += (1<<j);
            }
        }
    }
    REP(m,0,(1<<n)-1) {
        REP(j,0,n-1) {
            if(m&(1<<j)) {
                cnt[m]++;
            }
        }
        dp[0][m][cnt[m]] = ((m & mask[0]) == m && oneStretch(m,n));
    }
    REP(i,1,n-1) {
        REP(m,0,(1<<n)-1) {
            if((m & mask[i]) == m) {
                dp[i][m][cnt[m]] = 1;
                REP(j,cnt[m]+1,k) {
                    REP(pm,1,(1<<n)-1) {
                        if(((pm & mask[i-1]) == pm) && valid[m][pm]) {
                            dp[i][m][j] += dp[i-1][pm][j-cnt[m]];
                        }
                    }
                }
            }
        }
    }
    ll ans = 0;
    REP(i,0,n-1) {
        REP(m,0,(1<<n)-1) {
            ans += dp[i][m][k];
        }
    }
    cout << ans;
}
int main() {
    //freopen("output.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    //cin>>T;
    REP(TC,1,T) {
        //cout<<"Case #"<<TC<<": ";
        solve();
        cout<<"\n";
    }
}
