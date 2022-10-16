#include<bitset>
#include<iostream>

using namespace std;
int main(){
    int a = 6;
    bitset<3>b(a);
    cout << b << endl;
    cout << b[0] << " " << b[1] << endl;
    cout << "Testing bitset bit ops with numbers:\n";
    bitset<32> bs;
    bs[0] = true;
    bs = bs | (bs << 2);
    cout << bs << endl;
    cout << bs[0] << endl;
    return 0;
}
/*

maxW = 10, W = 5
00000000001

x=2
00000000101(same as 00000000001 | (00000000001 << 2 = 00000000100))

x=3
3,3+2 would be set
00000101101(same as 00000000101 | (00000000101 << 3 = 00000101000))
                    00000101000
*/
