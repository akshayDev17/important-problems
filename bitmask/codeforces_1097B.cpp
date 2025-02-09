#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n; cin >> n;
    int net_sum = 0;
    vector<int> v(n, 0);
    for(int i=0;i<n;i++){
        cin >> v[i];
        net_sum += v[i];
    }
    string ans = "NO";
    for(int i=1;i<(1 << n);i++){
        int sum1=0, sum2=0;
        int num = i, j=n-1;
        while(num){
            if(num & 1) sum1 += v[j];
            j--;
            num = num >> 1;
        }
        sum2 = net_sum - sum1;
        sum1 = sum1 % 360;
        sum2 = sum2 % 360;
        if(sum1 == sum2){
            ans = "YES";
            // cout << sum1 << " " << sum2 << " " << i << endl;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}