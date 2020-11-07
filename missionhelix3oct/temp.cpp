#include <bits/stdc++.h>

using namespace std;

int requiredNumberOfOperations(int n) {
    return (n/5) + (n%5)/2 + ((n%5)&1);
}
int equal(vector<int>& arr) {
    int n = arr.size();
    int ans = 1e9;
    for(int t = 0; t < 1000; t++) {
        int sum = 0;
        for(int i=0; i<n; i++) {
            if(arr[i] < t) {
                sum = 1e9;
                break;
            }
            sum += requiredNumberOfOperations(arr[i]-t);
        }
        ans = min(ans, sum);
    }
    return ans;
}

int main()
{
    int t;
    cin>>t;
    while(t--) {
      int n;
      cin>>n;
      vector<int> arr(n);
      for(int i=0;i<n;i++) {
        cin >> arr[i];
      }
      if(!t) {
        cout << n << "\n";
        for(auto it : arr) {
          cout << it << " ";
        }
      }
      // cout << equal(arr) << "\n";
    }

    return 0;
}
