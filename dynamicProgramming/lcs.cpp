#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lcs(string x, string y){
	int n = x.length(), m = y.length();
	vector<int> tmp(m+1, 0);
	vector<vector<int> > dp(n+1, tmp);
	for(int i = 0;i<=n;i++){
		for(int j = 0;j<=m;j++){
			if(i!= 0 && j != 0){
				if(x[i-1] == y[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
				else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			}
		}
	}
	return dp[n][m];
}

int main(){
	string x, y;
	cin >> x >> y;
	cout << "LCS =  : " << lcs(x, y) << endl;
	return 0;
}