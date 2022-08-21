#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Solution{
    public:
    bool cmp(int a, int b){
        cout << "a = " << a << ", b = " << b << endl; 
        return a < b;
    }
    void sorting(vector<int> &vec){
        // sort(vec.begin(), vec.end(), cmp);
    }
};

// class cmp{
//     public:
//     bool operator() (int a, int b){return a < b;}
// };

int main(){
    vector<int> vec = {2, 6, 3, 10, 9, 4};
    Solution solution;
    // solution.sorting(vec);
    // sort(vec.begin(), vec.end(), cmp());

    // declare a pointer to member function
    bool (Solution::* ptfptr) (int,int) = &Solution::cmp;
    cout << (solution.*ptfptr) (vec[3], vec[4]) << endl;

    auto comp = [](int a, int b){return a > b;};

    priority_queue<int,vector<int>,decltype(comp)> pq(comp);
    for(auto it: vec) pq.push(it);
    for(int i=0;i<vec.size();i++){
        vec[i] = pq.top();
        pq.pop();
    }
    for(auto it: vec) cout << it << " ";
    cout << endl;
    return 0;
}