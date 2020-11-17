#include <iostream>
#include <string>
#include <vector>

using namespace std;

string lcs(string x, string y){
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
	// for(int i = 0;i<=n;i++){
	// 	for(int j = 0;j<=m;j++){
	// 		cout << dp[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;


	string ans;
	int i = n, j = m;
	while(i > 0 && j > 0){
		if(x[i-1] == y[j-1]) ans = x[i-1] + ans;
		if(dp[i-1][j] > dp[i][j-1]) i--;
		else j--;
	}
	return ans;
}

string scs(string x, string y){
	int n = x.length(), m = y.length();
	vector<int> tmp(m+1, 0);
	vector<vector<int> > dp(n+1, tmp);
	for(int i = 0;i<=n;i++){
		for(int j = 0;j<=m;j++){
			if(i!= 0 && j != 0){
				if(x[i-1] == y[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
				else dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1]);
			}
			else{
				if(i == 0) dp[i][j] = j;
				else dp[i][j] = i;
			}
		}
	}
	string ans;
	int i = n, j = m;
	while(i > 0 && j > 0){
		if(x[i-1] == y[j-1]){
			ans = x[i-1] + ans;
			i--;
			j--;
		}
		else if(dp[i-1][j] > dp[i][j-1]){
			/*
			supersequence obtained from x[0....i], y[0...j-1]
			is shorter than that obtained from x[0...i-1],y[0...j]
			*/
			ans = y[j-1] + ans;
			j--;
		}
		else{
			/*
			supersequence obtained from x[0...i-1],y[0...j]
			is shorter than that obtained from x[0....i], y[0...j-1]
			*/
			ans = x[i-1] + ans;
			i--;
		}
	}
	// copy remaining characters of both strings

	while(i > 0){
		ans = x[i-1] + ans;
		i--;
	}
	while(j > 0){
		ans = y[j-1] + ans;
		j--;
	}
	return ans;
}

int main(){
	int t;cin >> t;
	while(t--){
		string x,y;cin >> x >> y;
		cout << "Shortest common supersequence is " << scs(x, y) << endl;
	}
}