
bool isValid(int i, int j, int m, int n) {return (i>=0 && i < m && j >= 0 && j < n);}

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();

    vector<vector<int>> ans = vector<vector<int>>(m, vector<int>(n, 100000));
    vector<int> moves = {0, 1, 0, -1, 0};
    int count = 0;
    queue<pair<int,int>> q;
    for(int i = 0;i<m;i++){
        for(int j =0;j<n;j++){
            if(mat[i][j] == 0){
                q.push(make_pair(i, j));
                ans[i][j]=0;
            }
        }
    }
    
    while(!q.empty()){
        pair<int,int> top = q.front();q.pop();
        int r = top.first, c = top.second;

        for(int idx=0;idx<4;idx++){
            int nr = r+moves[idx], nc = c+moves[idx+1];
            if(isValid(nr, nc, m, n)){
                if(mat[nr][nc] == 1 && ans[nr][nc] > ans[r][c]+1){
                    // this needs to be updated, and so its children
                    pair<int,int> temp(nr, nc);
                    ans[nr][nc] = ans[r][c]+1;
                    q.push(temp);
                }
            }
        }
    }
    return ans;
}