# Table of Contents

1. [Super Ugly Number](#super-ugly-number)
   1. [Solution](#sol1)
2. [Unique Paths](#unique_paths)





# Super Ugly Number<a name="super-ugly-number"></a>

1. [Leetcode](), [GeeksforGeeks]()

2. Super ugly numbers are positive numbers whose all prime factors are in the given prime list `primes` of size `k`.

3. Example:

   Input: n = 12, primes = [2,7,13,19]
   Output: 32 
   Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12 
                super ugly numbers given primes = [2,7,13,19] of size 4.



## Solution<a name="sol1"></a>

1. ```cpp
   class Solution {
   public:
       int nthSuperUglyNumber(int n, vector<int>& primes) {
           int k = primes.size();
           unordered_map<int,int> mp;
           mp[1] = 0;
           vector<int> ugly = {1};
           vector<int> multiple_of(k, 0);
           int count = n;
           while(count){
               int minNum = INT_MAX, minIdx = -1;
               for(int i =0;i<k;i++){
                   if(minNum > primes[i]*ugly[multiple_of[i]]){
                       minNum = primes[i]*ugly[multiple_of[i]];
                       minIdx = i;
                   }
               }
               multiple_of[minIdx]++;
               if(mp.find(minNum) == mp.end()){
                   // duplication check
                   mp[minNum] = 0;
                   count--;
                   ugly.push_back(minNum);
               }
               
           }
           return ugly[n-1];
           // return 32;
       }
   };
   
2. maintain an array `multiple_of` that maintains the position of the largest **ugly** number which when multiplied with `primes[i]` gives the smallest possible multiple of `primes[i]` which is **not yet in the set, hence may be a candidate next-ugly-number**.

3. the product `primes[i]*ugly[multiple_of[i]]` gives us this candidate next-ugly-number value, for each prime number `primes[i]`.

   1. select the smallest out of these candidate next-ugly-numbers, append to the set of ugly numbers
   2. update the position of the prime-number whose next-multiple was selected in this step, as the best candidate for the next-ugly number, `multiple_of[min_idx]++;`.

4. ![equation](https://latex.codecogs.com/gif.latex?%7B%5Ccolor%7BRed%7D%20%5Ctextrm%7B%20note%20that%20we%20are%20taking%20non-duplicate%20ugly%20numbers%20as%20the%20answer.%7D%7D)


# Unique Paths<a name="unique_paths"></a>

1. [Leetcode](https://leetcode.com/problems/unique-paths/)
2. Given the two integers m and n, grid of size `m x n` filled with only 0's and 1's, return the number of possible unique paths that the robot can take to reach the bottom-right corner.
The test cases are generated so that the answer will be less than or equal to 2 x 10^9.

## Solution
1. Think of a Combinatorial, see pattern of each column.
2. ```cpp
    int uniquePaths(int m, int n) {
        if(m == 1 || n == 1) return 1;
        double ans = 1;
        int r = 1, N = n, R = m-1;
        // compute N C r
        while(r <= R){
            ans = ans*N/r;
            N++;
            r++;
        }
        return (int)ans;
    } 
