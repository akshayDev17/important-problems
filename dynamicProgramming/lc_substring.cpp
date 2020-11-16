#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int lcs(string x, string y, int n, int m){
	vector<int> tmp(m+1, 0);
	vector<vector<int> > dp(n+1, tmp);
	for(int i = 0;i<=n;i++){
	    for(int j = 0;j<=m;j++){
	        if(i != 0 && j != 0){
	            // considering strings x[0..i-1], y[0..j-1]
	            if(x[i-1] == y[j-1]) dp[i][j] = 1+dp[i-1][j-1];
	            else dp[i][j] = 0;
	        }
	    }
	}
	int ans = -1;
	for(int i = 0;i<=n;i++){
	    for(int j = 0;j<=m;j++){
	        ans = max(ans, dp[i][j]);
	    }
	}
	return ans;
}

int main() {
	// multiple test cases
	int t;cin >> t;
	while(t--){
	    int n,m;cin >> n >> m;
	    string x,y;
	    cin >> x >> y;
	    cout << lcs(x, y, n, m) << endl;
	}
	return 0;
}