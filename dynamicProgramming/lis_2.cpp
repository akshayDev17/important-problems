#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lis(int n, vector<int> &a){
	vector<int> dp(n, 1);
	for(int i =0 ;i<n;i++){
		for(int j = 0;j<i;j++){
			if(a[i] > a[j] && dp[i] < dp[j]+1) dp[i] =  dp[j]+1;
		}
	}
	return *max_element(dp.begin(), dp.end());
}

int main(){
	int n;cin >> n;
	vector<int> arr(n, 0);
	for(int i = 0;i<n;i++) cin >> arr[i];
	cout << "LIS =  : " << lis(n, arr) << endl;
	return 0;
}