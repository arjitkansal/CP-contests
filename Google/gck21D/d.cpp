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

const int N = (int)5e5+5;
const int M = (int)3e3+5;
const int Q = 301;
const int logN = 19;

class segmentTree {
    int n;
    ll st[N<<1];
    public:
        void init(int n) {
            this->n = n;
            REP(i,1,2*n-1) {
                st[i] = 0;
            }
        }
        void update(int i, ll val) {
            for(i+=(n-1),st[i]=val,i>>=1;i>0;i>>=1) {
                st[i] = st[i<<1] + st[i<<1|1];
            }
        }
        ll sum(int l, int r) {
            ll ret = 0;
            for(l+=(n-1),r+=n;l<r;l>>=1,r>>=1) {
                if(l&1) ret += st[l++];
                if(r&1) ret += st[--r];
            }
            return ret;
        }
} st1, st2, st, st1cnt;

int p;
int v(ll val) {
    if(val == 0) {
        return 0;
    }
    int cnt = 0;
    while(val%p==0) {
        cnt++;
        val/=p;
    }
    return cnt;
}
void setval(int i, ll val) {
    if(val < p || (val%p) == 0) {
        st.update(i,v(val));
        st1.update(i,0);
        st1cnt.update(i,0);
        st2.update(i,0);
        return;
    }
    st.update(i,0);
    st1.update(i, v(val - (val%p)));
    st1cnt.update(i, 1);
    st2.update(i, v(val + (val%p)) - 1);
}

void solve() {
    int n,q;
    cin >> n >> q >> p;
    st.init(n);
    st1.init(n);
    st1cnt.init(n);
    st2.init(n);

    ll val;
    REP(i,1,n) {
        cin >> val;
        setval(i,val);
    }

    int t,pos,s,l,r;
    while(q--) {
        cin >> t;
        if(t == 1) {
            cin >> pos >> val;
            setval(pos,val);
        }
        else {
            cin >> s >> l >> r;
            val = s * st.sum(l,r) + st1.sum(l,r) + st1cnt.sum(l,r) * v(s);
            if(p==2 && (s%2)==0) {
                val += st2.sum(l,r);
            }
            cout << val << " ";
        }
    }
}
int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output1.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    cin>>T;
    REP(TC,1,T) {
        cout<<"Case #"<<TC<<": ";
        solve();
        cout<<"\n";
    }
}
