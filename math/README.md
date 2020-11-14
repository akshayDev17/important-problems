# Table of Contents

1. [Super Ugly Number](#super-ugly-number)
   1. [Solution](#sol1)





# Super Ugly Number<a name="super-ugly-number"></a>

1. [Leetcode](), [GeeksforGeeks]()

2. Super ugly numbers are positive numbers whose all prime factors are in the given prime list `primes` of size `k`.

3. Example:

   Input: n = 12, primes = [2,7,13,19]
   Output: 32 
   Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12 
                super ugly numbers given primes = [2,7,13,19] of size 4.



# Solution<a name="sol1"></a>

1. ```cpp
   class Solution {
   public:
       int nthSuperUglyNumber(int n, vector<int>& primes) {
           if(n == 1) return 1;
           int k = primes.size();
           vector<int> ug{1};
           unordered_set<int> ug_set{1}; // ugly number set
           ug.reserve(n);
           ug_set.reserve(n);
           vector<int> multiple_of(k, 0);        
           int min_val, min_idx;
           while(ug.size() < n){
               min_val = INT_MAX;min_idx = -1;
               // iterate through all candidate multiples
               for(int i = 0;i<k;i++){
                   if(min_val > primes[i]*ug_set[multiple_of[i]])
                       min_val = primes[i]*ug_set[multiple_of[i]];
                   	min_idx = i;
               }
               if(ug_set.find(min_val) == ug_set.end()){
                   ug.push_back(min_val);
                   ug_set.insert(min_val);
               }
   			// update the candidates information for next turn 
               multiple_of[min_idx]++;
           }
           return min_val;
       }
   };
   ```

2. maintain an array `multiple_of` that maintains the position of the largest **ugly** number which when multiplied with `primes[i]` gives the smallest possible multiple of `primes[i]` which is **not yet in the set, hence may be a candidate next-ugly-number**.

3. the product `primes[i]*ugly[multiple_of[i]]` gives us this candidate next-ugly-number value, for each prime number `primes[i]`.

   1. select the smallest out of these candidate next-ugly-numbers, append to the set of ugly numbers
   2. update the position of the prime-number whose next-multiple was selected in this step, as the best candidate for the next-ugly number, `multiple_of[min_idx]++;`.

4. ![equation](https://latex.codecogs.com/gif.latex?%7B%5Ccolor%7BRed%7D%20%5Ctextrm%7B%20note%20that%20we%20are%20taking%20non-duplicate%20ugly%20numbers%20as%20the%20answer.%7D%7D)



