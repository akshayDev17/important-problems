#include<vector.h>
#include<stdio.h>

using namespace std;

int main(){
    // question : number of islands in a given graph of 1's and 0's , 0 - water cell, 1 - land cell
    vector<vector<int>> graph = {{0,1,1,0},{0,0,0,1}, {0,0,1,1}, {1,1,0,0}};
    vector<int> moves = {0,1,0,-1,0};
    int m = graph.size(), n = graph[0].size(), ans = 0; // ans will store the count of islands
    vector<vector<bool>> vis = vector<vector<bool>>(m, vector<bool>(n, false));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(!vis[i][j] && graph[i][j] == 1){
                ans++;
                stack<pair<int,int>> st;
                st.push(i,j);
                while(!st.empty()){
                    pair<int,int> p = st.top();
                    int r = p.first, c = p.second;
                    vis[r][c] = true;
                    for(int idx=0;idx<4;idx++){
                        int nr = r+moves[idx], nc = c+moves[idx+1];
                        if(nr >= 0 && nc >= 0 && nr < m && nc < n && !vis[nr][nc] && graph[nr][nc] == 1) st.push(make_pair(nr,nc));
                    }
                    st.pop();
                }
            }
        }
    }
    cout << "number of islands = " << ans << endl;
    return 0;
}
/*
0,1,1,0
0,0,0,1
0,0,1,1
1,1,0,0

*/