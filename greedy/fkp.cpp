#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

bool compare(const pair<int,int> &a, const pair<int,int> &b){
	return a.first/a.second > b.first/b.second;
}

int fkp(vector<int> &values, vector<int> &weights, int n, int W){
	vector<pair<int,int> > ratio(n, make_pair(0,0));
	for(int i =0;i<n;i++){ratio[i].first = values[i];ratio[i].second = weights[i];}
	sort(ratio.begin(), ratio.end(), compare);
	
	int ans = 0;
	for(int i = 0;i<n;i++){
		if(W == 0) break;
		if(ratio[i].second <= W){
			ans += ratio[i].first;
			W -= ratio[i].second;
		}
		else{ans += (ratio[i].first/ratio[i].second) * W;W = 0;}
	}
	return ans;
}

int main(){
	int n;cin >> n;
	vector<int> values(n, 0), weights(n, 0);
	for(int i = 0;i<n;i++) cin >> values[i];
	for(int i = 0;i<n;i++) cin >> weights[i];
	int W;cin >> W; // capacity of knapsack
	cout << fkp(values, weights, n, W) << endl;
	return 0;
}