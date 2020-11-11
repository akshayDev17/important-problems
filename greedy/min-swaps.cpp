#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	//code
	int t;cin >> t;
	while(t--){
	    int n;cin >> n;
	    string s;cin >> s;
	    int j=-1;
	    vector<int> pos;
	    for(int i =0 ;i<n;i++){
	        if(s[i] == '[') pos.push_back(i);
	    }
	    int p = 0;
	    int ans = 0;
	    int count = 0;
	    for(int i =0 ;i<n;i++){
	        if(s[i] == '['){count++;p++;}
	        else count--;
	        if(count < 0){
	            ans += pos[p]-i;
	            char temp = s[i];
	            s[i] = s[pos[p]];
	            s[pos[p]] = temp;
	            count = 0;
	            p++;
	        }
	    }
	    cout << ans << endl;
	}
	return 0;
}