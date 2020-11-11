#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

#define mp make_pair
#define pii pair<int,int>

vector<vector<int> > reconstructQueue(vector<vector<int> >& people) {
    priority_queue <pii,vector<pii>, greater<pii> > pq ;
    int n = people.size() ;
    vector<vector<int> > out(n,vector<int>(2,-1)) ;
    
    for(int i = 0;i<n;i++) pq.push(mp(people[i][0], people[i][1]));
    
    int base =n ;
    int prev = 0 ; 
    while(!pq.empty()){ 
        pii temp = pq.top();
        cout << temp.first << " " << temp.second << endl;
        pq.pop(); 
        int count = temp.second ;
        for(int i=0; i<n ;i++){
            if(out[i][0] != -1 && out[i][0] != temp.first) continue ;
            
            if(count == 0){
                out[i][0] = temp.first ;
                out[i][1]  = temp.second ; 
                break; 
            }
            count --; 
        }
    }
    cout << endl << endl;
    return out ; 
}

int main(){
    int n;cin >> n;
    vector<int> tmp(2, -1);
    vector<vector<int> > v(n, tmp);
    for(int i = 0;i<n;i++) cin >> v[i][0] >> v[i][1];
    vector<vector<int> > ans = reconstructQueue(v);
    for(int i = 0;i<n;i++) cout << ans[i][0] << " " << ans[i][1] << endl;
    return 0;
}