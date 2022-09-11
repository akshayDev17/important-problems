#include<iostream>
#include<vector>

using namespace std;

int main(){
    vector<int> arr;
    arr.push_back(1);
    arr.push_back(4);
    arr.push_back(6);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(10);

    int ans = 0, xor_ = 0;
    for(int i=0;i<arr.size();i++){
        ans = ans | arr[i];
        xor_ = xor_ ^ arr[i];
    }
    cout << "xor = " << xor_ << ", max xor after operations = " << ans << endl;
    return 0;
}