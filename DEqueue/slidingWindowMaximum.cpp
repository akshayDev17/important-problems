#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void print(vector<int> arr){
	int n = arr.size();
	for(int i =0;i<n;i++) cout << arr[i] << " ";
	cout << endl;
	return;
}

void showdq(deque<int> dq){
	for(auto it = dq.begin(); it != dq.end();it++) cout << *it << " ";
	cout << endl;return;}

void slidingWindowMax(vector<int> arr, int n, int k){
	deque<int> dq;
	for(int i = 0;i<k;i++){
		while(!dq.empty() && arr[dq.back()] <= arr[i]) dq.pop_back();
		dq.push_back(i);
	}
	// showdq(dq);
	vector<int> ans;
	for(int i = k;i<n;i++){
		ans.push_back(arr[dq.front()]);
		while(!dq.empty() && dq.front() <= i-k) dq.pop_front(); // indices not in the current window need to be removed from the deque
		while(!dq.empty() && arr[dq.back()] <= arr[i]) dq.pop_back(); // for the incoming element, indices of 
																	  // elements less than this and in the queue need to be removed
		dq.push_back(i);
		
	}
	ans.push_back(arr[dq.front()]);
	print(ans);
}

int main(){
	int t;cin >> t;
	while(t--){
		int n; cin >> n;vector<int> v(n, 0);
		for(int i=0;i<n;i++) cin >> v[i];
		int k;cin >> k;
		slidingWindowMax(v, n, k);
	}
	return 0;
}