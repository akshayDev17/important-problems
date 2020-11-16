#include <iostream>
#include <vector>

using namespace std;

int kp_01(vector<int> &values, vector<int> &weights, int n, int W){
	vector<int> tmp(n, 0);
	vector<vector<int> > dp(W+1, tmp);
	for(int w = 1;w<=W;w++){
		for(int i = 0;i<n;i++){
			if(weights[i] <= w){
				// first option = choose item i
				// second option = reject item i
				dp[w][i] = max(dp[w - weights[i]][i-1]+values[i], dp[w][i-1]);
			}
			else dp[w][i] = dp[w][i-1];
		}
	}
	return dp[W][n-1];
}

int main(){
	int n;cin >> n;
	vector<int> values(n, 0), weights(n, 0);
	for(int i = 0;i<n;i++) cin >> values[i];
	for(int i = 0;i<n;i++) cin >> weights[i];
	int W;cin >> W; // capacity of knapsack
	cout << kp_01(values, weights, n, W) << endl;
	return 0;
}