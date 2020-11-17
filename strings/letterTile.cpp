#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <unordered_map>

using namespace std;

int calc(vector<int> fact, string s){
	unordered_map<char,int> mp;
	int n = s.size();
	for(int i = 0;i<n;i++){
		if(mp.find(s[i]) == mp.end()) mp[s[i]] = 1;
		else mp[s[i]]++;
	}
	int ans = fact[n];
	for(auto it = mp.begin(); it != mp.end(); it++){
		ans /= fact[it->second];
	}
	return ans;
}

int numTilePossibilities(string tiles){
	set<string> s;
	int n = tiles.size();
	vector<int> fact(n+1, 1);
	for(int i = 2;i<=n;i++) fact[i] = i*fact[i-1];

	int ans = 0;
	for(int i = 1;i< (1 << tiles.size());i++){
		string str="";
		for(int j = 0;j<tiles.size();j++){
			if(i & (1 << j)){
				str += tiles[j];
			}
		}
		if(s.find(str) != s.end()) continue;
		s.insert(str);
		ans += calc(fact, str);
	}
	return ans;
}

int main(){
	int t;cin >> t;
	while(t--){
		string tiles;cin >> tiles;
		cout << "string = " << tiles << ", number of possible tile strings = " << numTilePossibilities(tiles) << endl;
	}
	return 0;
}