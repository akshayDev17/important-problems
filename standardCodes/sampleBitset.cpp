#include<bitset>
#include<iostream>

using namespace std;
int main(){
    int a = 6;
    bitset<3>b(a);
    cout << b << endl;
    cout << b[0] << " " << b[1] << endl;
    return 0;
}