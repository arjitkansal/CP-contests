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

const int N = (int)2e6+5;
const int M = (int)3e3+5;
const int Q = 301;
const int logN = 19;

int st[N<<1], upd[N<<1];
class segmentTree {
    private:
        int n;
        void apply(int i, int d) {
            if(i < n) {
                upd[i] += d;
            }
            st[i] += d;
        }
        void push(int i) {
            REPN(h,20,1) {
                int p = i>>h;
                if(upd[p]) {
                    apply(p<<1, upd[p]);
                    apply(p<<1|1, upd[p]);
                    upd[p] = 0;
                }
            }
        }
        void build(int i) {
            for(i>>=1;i;i>>=1) {
                st[i] = min(st[i<<1], st[i<<1|1]) + upd[i];
            }
        }
    public:
        segmentTree(int n) {
            this->n = n;
        }
        void update(int l, int r, int d) {
            l += n-1, r += n;
            int l0 = l, r0 = r;
            for(;l<r;l>>=1,r>>=1) {
                if(l&1) apply(l++,d);
                if(r&1) apply(--r,d);
            }
            build(l0);
            build(r0-1);
        }
        int rangeMin(int l, int r) {
            l += n-1, r += n;
            push(l);
            push(r-1);
            int ret = mod;
            for(;l<r;l>>=1,r>>=1) {
                if(l&1) ret = min(ret, st[l++]);
                if(r&1) ret = min(ret, st[--r]);
            }
            return ret;
        }
};

void solve() {
    int n,m;
    cin >> n >> m;
    vector<pii> segments;

    int l,r,w;
    REP(i,1,n) {
        cin >> l >> r >> w;
        segments.pb({w,{l,r}});
    }
    sort(all(segments));

    segmentTree st(2*m);
    int j = 0, ans = segments[n-1].first - segments[0].first;
    REP(i,0,n-1) {
        while(st.rangeMin(2,2*m)==0 && j<n) {
            st.update(segments[j].second.first * 2, segments[j].second.second * 2, 1);
            j++;
        }
        if(st.rangeMin(2,2*m) == 0) {
            break;
        }
        ans = min(ans, segments[j-1].first - segments[i].first);
        st.update(segments[i].second.first * 2, segments[i].second.second * 2, -1);
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
