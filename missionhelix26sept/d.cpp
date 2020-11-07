#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<pair<ll,ll>> ans;
map<ll,int> mp;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n; int m;
    cin>>n>>m;
    ll l,r;
    while(m--) {
        cin>>l>>r;
        mp[l]++;
        mp[r+1]--;
    }
    int k; cin>>k;
    bool active = false;
    int sum = 0;
    for(auto it:mp) {
        sum += it.second;
        if(sum >= k) {
            if(!active) {
                l = it.first;
                active = true;
            }
        }
        else {
            if(active) {
                r = it.first - 1;
                ans.push_back({l,r});
                active = false;
            }
        }
    }
    cout << ans.size();
    for(auto it: ans) {
        cout << "\n" << it.first << " " << it.second;
    }
    return 0;
}
