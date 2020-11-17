#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int minDrops(int n, int k) 
{
    vector<int> tmp(k+1, 0);
    vector<vector<int> > dp(n+1, tmp);
    
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=k;j++){
            if(i == 1) dp[i][j] = j;
            else{
                if(j == 1) dp[i][j] = 1;
                else{
                    dp[i][j] = INT_MAX;
                    for(int x = 1;x<=j;x++){
                        dp[i][j] = min(dp[i][j], 1+max(dp[i-1][x-1], dp[i][j-x]));
                    }
                }
            }
        }
    }
    return dp[n][k];
}

int main(){
	int n,k;cin >> n >> k;
	// n = number of eggs
	// k = number of total floors of the building
	cout << minDrops(n, k) << endl;
	return 0;
}