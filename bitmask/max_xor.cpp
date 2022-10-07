#include<iostream>
#include<set>
#include<vector>

using namespace std;

void printMaxXor(vector<int> &nums){
    int mask = 0, mx=0, newMax=0;
    set<int> curr_set;
    for(int bit=31;bit >= 0;bit--){
        mask |= (1 << bit);
        for(auto num: nums) curr_set.insert(mask & num);
        newMax = mx | (1 << bit);
        for(auto num_in_set: curr_set){
            if(curr_set.count(num_in_set ^ newMax)){
                mx = newMax;
                break;
            }
        }
        curr_set.clear();
    }
    cout << "Max XOR is: " << mx << endl;
}

int main(){
    vector<int> testArr;
    testArr.push_back(3);
    testArr.push_back(10);
    testArr.push_back(5);
    testArr.push_back(25);
    testArr.push_back(2);
    testArr.push_back(8);

    printMaxXor(testArr);
    return 0;
}