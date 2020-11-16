#include<iostream>
#include<string>
#include<vector>

using namespace std;
#define pb push_back
int main(){

	string s, p;
	cin >> s >> p;
	int m = p.length();
	vector<int> lpp(m, -1);

	// construct lpp
	int i = 0, j = 0;
	while(j < m){
		if(p[i] == p[j]){
			if(i == j) lpp[i] = 0;
			else{
				lpp[j] = lpp[j-1]+1;
				i++;
			}
		}
		else{
			if(i == 0) lpp[j] = 0;
			else{
				while(i > 0 && p[j] != p[i]) i = lpp[i-1];
				if(p[i] == p[j]) lpp[j] = lpp[i]+1;
				else lpp[j] = 0;
			}
		}
		j++;
	}
	cout << "The LPS/LPP array is: ";
	for(i = 0;i<m;i++) cout << lpp[i] << " ";
	cout << endl;

	vector<int> ans;

	// search
	i = 0, j = 0;
	int n = s.length();
	while(i < n && j < m){
		while(i < n && j< m && s[i] == p[j]){i++;j++;}
		if(j == m){ans.pb(i-j);j=lpp[j-1];}
		else{
			if(j > 0) j = lpp[j-1];
			if(j == 0 && p[j] != s[i])i++; // backtracked j upto the start, 
										   // now if characters mismatch, 
										   // we need to move on to next 
										   // character of the main string s
		}
	}
	cout << endl << "pattern was found at: ";
	for(auto it = ans.begin(); it != ans.end();it++) cout << *it+1 << " ";
	cout << endl;


	return 0;
}