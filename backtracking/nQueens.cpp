#include <iostream>
#include <vector>

using namespace std;


bool isSafe(vector<vector<int> > &board, int row, int col, int n) 
{ 
    int i, j; 

    /* only the left side is being checked
    since the queens are being placed in a 
    left to right order, hence we know that
    there are no queens placed on the right*/
  
    /* Check this row on left side */
    for (i = 0; i < col; i++) 
        if (board[row][i]) 
            return false; 
  
    /* Check upper diagonal on left side */
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
        if (board[i][j]) 
            return false; 
  
    /* Check lower diagonal on left side */
    for (i = row, j = col; j >= 0 && i < n; i++, j--) 
        if (board[i][j]) 
            return false; 
  
    return true; 
}

int solveNthQueen(vector<vector<int> > &board, int n, int col){

	if(col == n){
		// successfully placed all queens
		return true;
	}
	// we will be now placing a queen on the column = col
	for(int row = 0;row < n;row++){
		if(isSafe(board, row, col, n)){
			board[row][col] = 1;
			if(!solveNthQueen(board, n, col+1)) board[row][col] = 0;
			else return true;
		}
	}
	return false;
}

vector<vector<int> > nQueens(int n){
	vector<int> tmp(n, 0);
	vector<vector<int> > arr(n, tmp);
	vector<vector<int> > ans;
	if(!solveNthQueen(arr, n, 0)) return ans;
	return arr;
}

void print(vector<vector<int> > ans, int N){
	int n = ans.size();
	cout << "For N = " << N << endl;
	if(n == 0){
		cout << "No configuration was found" << endl << endl;
		return;
	}
	int m = ans[0].size();
	for(int i = 0;i<n;i++){
		for(int j = 0;j<m;j++){
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return;
}

int main(){
	int t; // cout << "enter number of test cases" << endl;
	cin >> t;
	while(t--){
		int n; // cout << "Enter N value" << endl;
		cin >> n;
		vector<vector<int> >  ans = nQueens(n);
		print(ans, n);
	}
	return 0;
}