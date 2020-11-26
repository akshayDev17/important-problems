#include<vector>
#include<iostream>
#include<set>

using namespace std;

class Linear{
public:
	vector<int> parent;
	Linear(int N){
		parent.clear();
		parent.resize(N);
		for(int i = 0;i<N;i++) parent[i] = i;
	}
	int find(int x){
		if(parent[x] != x) parent[x] = find(parent[x]);
		return parent[x];
	}
	void Union(int x, int y){
		int px = find(x), py = find(y);
		parent[px] = py;
	}
};

int main(){
	int n;cin >> n;
	vector<string> grid(n, "");
	for(int i = 0;i<n;i++) cin >> grid[i];
	Linear *linearDS = new Linear(4*n*n);
	/*
	encoding of 4 portions of a grid cell are:
	north = 0
	east = 1
	south = 2
	west = 3
	*/
	for(int i = 0;i<n;i++){
		for(int j = 0;j<n;j++){
			int idx = (i*n + j)*4;
			if(grid[i][j] == '/'){
				linearDS->Union(idx, idx+3); // north and west in one subset
				linearDS->Union(idx+1, idx+2); // east and south in the other
			}
			else if(grid[i][j] == '\\'){
				// cout << i << " " << j << endl;
				linearDS->Union(idx, idx + 1); // north and east in one subset
				linearDS->Union(idx + 3, idx + 2); // west and south in the other
			}
			else{
				// group all of them together
				linearDS->Union(idx, idx + 1);
				linearDS->Union(idx + 1, idx + 2);
				linearDS->Union(idx + 2, idx + 3);
			}
			// group up east and the (west of the next-right cell)
			if(j < n-1) linearDS->Union(idx+1, idx + 5);

			// group up west and the (east of the just-left cell)
			if(j > 0) linearDS->Union(idx+3, idx - 3);

			// group up north and the (south of the just-above cell)
			if(i > 0) linearDS->Union(idx, idx - 4*n + 2);

			// group up south and the (north of the just-below cell)
			if(i < n-1) linearDS->Union(idx + 2, idx + 4*n);
		}
		cout << endl;
	}
	int answer = 0;
	for(int i = 0;i<n;i++){
		for(int j = 0;j<n;j++){
			int idx = (i*n+j)*4;
			for(int k = 0;k<4;k++) cout << linearDS->parent[idx+k] << " ";
			cout << "\t";
		}
		cout << endl;
	}
	cout << "answer = " << answer << endl;
	return 0;
}