#include<iostream>
#include<string>
#include<vector>

using namespace std;

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

	for(i = 0;i<m;i++) cout << lpp[i] << " ";
	cout << endl;


	return 0;
}