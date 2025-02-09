#include<iostream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;

int dist(pair<int,int> s, pair<int,int> p){
    // returns squared distance
    int xdiff = s.first-p.first, ydiff = s.second-p.second;
    return xdiff*xdiff + ydiff*ydiff;
}

string string_rep(int pos_idx){
    stringstream ss; ss << pos_idx;
    string s; ss >> s;
    return s;
}

/*
void recursive_dp(vector<pair<int,int> > &coord, int n, int mask, int xs, int ys, int x, int y, int counter, string curr_seq, int ans, string &final_seq, int &currMin){
    // xs, ys: starting positions
    // x, y: current positions

    int returning_dist = 0;
    
    if(mask == 0){
        // all objects picked, return to xs,ys
        returning_dist += dist(make_pair(xs, ys), make_pair(x, y));
        curr_seq += " 0";
        if(currMin >= returning_dist + ans){
            cout << "\nFound new min at " << returning_dist + ans << ", where old min = " << currMin << endl;
            currMin = returning_dist + ans;
            cout << "Sequence -" << final_seq << "- replaced by |" << curr_seq << "|\n";
            final_seq = curr_seq;
        }
        return;
    }

    if(counter == 2){
        // return to xs, ys, already have 2 items in hand
        returning_dist = dist(make_pair(xs, ys), make_pair(x, y));
        curr_seq += " 0";

        x=xs;y=ys;
        counter=0;
    }

    // find next set bit in mask, unset it and see whats the optimal value found
    int copyMask = mask, bitpos=0;
    while(copyMask){
        if(copyMask & 1){
            // set bit found
            int nextMask = mask ^ (1 << bitpos);
            int jump = returning_dist + dist(make_pair(x,y), coord[n-bitpos-1]);
            recursive_dp(coord, n, nextMask, xs, ys, coord[n-bitpos-1].first, coord[n-bitpos-1].second, counter+1, curr_seq + " " + string_rep(n-bitpos), ans+jump, final_seq, currMin);
        }
        copyMask = copyMask >> 1;
        bitpos++;
    }
    // return to start and then see, i.e. don't visit any set bit directly
    // return is only valid if we have atleast 1 object, i.e. counter >= 1
    // counter = 0 is used in the call below since if there is an object in hand, its returned, hence hand's empty
    if(counter == 1)
        recursive_dp(coord, n, mask, xs, ys, xs, ys, 0, curr_seq + " 0", ans+dist(make_pair(x, y), make_pair(xs, ys)), final_seq, currMin);
}
*/

int look_for_order(vector<vector<vector<int> > > &dp, vector<pair<int,int> > &coord, int curr_pos_idx, int counter, int mask){
    // counter = 0 means Lena is at curr_pos_idx with 0 items, before collecting item at curr_pos_idx
    // counter = 1 means Lena is at curr_pos_idx with 1 item, before collecting item at curr_pos_idx(next movement will forcefully be to curr_pos_idx=0)
    if(mask == 0){
        // no items left to pick up
        if(curr_pos_idx == 0){
            // already at origin
            return dp[curr_pos_idx][mask][counter]=0;
        }
        else{
            // at some other place than origin, return to origin
            return dp[curr_pos_idx][mask][counter] = dist(coord[0], coord[curr_pos_idx]);
        }
    }
    // atleast 1 object is left to be put in the bag
    if(dp[curr_pos_idx][mask][counter] != INT_MAX) return dp[curr_pos_idx][mask][counter];
    if(curr_pos_idx == 0){
        // currently at origin, has to go at remaining objects and pick 1
        // find next set bit in mask, unset it and see whats the optimal value found
        int copyMask = mask, bitpos=0;
        while(copyMask){
            if(copyMask & 1){
                // set bit found
                int nextMask = mask ^ (1 << bitpos);
                int jump = returning_dist + dist(coord[curr_pos_idx], coord[n-bitpos]);
                look_for_order(dp, coord, n-bitpos,0,nextMask); // we are currently at origin, hence empty-handed, 
                // and on arriving at n-bitpos point, 
                // will have no item before picking this item(first comment of this function)
                
            }
            copyMask = copyMask >> 1;
            bitpos++;
        }
    }
    int returning_dist = 0;
    if(counter == 2){
        // return to 0'th index, i.e. handbag position
        returning_dist += dist(coord[curr_pos_idx], coord[0]);
        curr_pos_idx = 0;
    }
    if(dp[curr_pos_idx][mask][counter] != INT_MAX) return dp[curr_pos_idx][mask][counter];
    // if curr_pos_idx=0 with counter=0, then you have to unset a set-bit.
    return 0;
}

int main(){
    // similar to person-assignment-to-job problem(reference: https://www.youtube.com/watch?v=685x-rzOIlY)
    /*
    0--->min(dist(1)+cost(1,coverAll()),dist(2)+cost(2,coverAll())...dist(n)+cost(n,coverAll()))

    n-bit number: 
        - ith bit set: yet to collect i'th object, 
        - ith bit unset:  already collected i'th object
    
    for each set bit, unset it , travel to the coordinate,update the current dist, and then call the helper function with the new mask + new cost.

    0,1,2,3 - indices

    0 1...0 - dist(0,1) + cost(1-->0, )
    0 2...0 - dist(0,2)

    */
    int xs, ys;
    cin >> xs >> ys;
    int n;cin >> n;
    vector<pair<int,int> > coordinates(n+1, make_pair(0,0));
    coordinates[0].first=xs;coordinates[0].second=ys;
    for(int i=1;i<=n;i++) cin >> coordinates[i].first >> coordinates[i].second;
    string final_seq="0";
    int currMin = INT_MAX;
    int M = (1 << n);
    // recursive_dp(coordinates, n, (1 << n)-1, xs, ys, xs, ys, 0, "0", 0, final_seq, currMin);
    // cout << currMin << endl << final_seq << endl;
    vector<vector<vector<int> > > dp = vector<vector<vector<int> > >(n+1, vector<vector<int> >(M, vector<int>(2, INT_MAX)));
    look_for_order(dp, coordinates, 0, 0, M-1);
    cout << dp[0][M-1][0] << endl;
    return 0;
}
/*
xs, ys = 0,0
1,1 -1,1

mask=11
2+dp(10,-1,1,1),2+dp(01,1,1,1) (mask,x,y,counter)

dp(10,-1,1,1)=6
dp(01,1,1,1) =6

dp[i][m]: m = 0 to (1 << n)-1
i: 0 to n

ans = dp[0][(1 << n)-1] : start at index=0(starting pos) with mask value = all bits set(nothing picked up)

all dp[][] initialized to INT_MAX
dp[i][m] = min(dp[i][m], dist[i][j]+dp[j][m ^ (1 << j)] for all j which are set)
----------------------------------------------------------------------
lets take the following test-case:
0 0
2
1 1
-1 1
n = 2
M = (1 << n)-1 = 3
dp[0][M] = INT_MAX
dp[i][0] = 0(when no items left to pick, nothing to travel to)

dp[0][M] = min(INT_MAX, 
j=1: dist[0][1]+dp[1][3 ^ (1 << (1-1)) = 2],
j=2: dist[0][2]+dp[2][3 ^ (1 << (2-1)) = 1],

    dp[1][3 ^ 1 = 2] = min(
        INT_MAX,
        j=2: dist[1][0]+dp[0][2 ^ (1 << (2-1)) = 0] = dist[1][0]=
    )
)
----------------------------------------------------------------------
*/