# Table of Contents

1. [sub-square-matrices with all a's](#sub-square-all-1s)
   1. [Solution](#sol1)
2. [Even-summed K-sized Permutations in a given range](#k-sized-permutations)
   1. [Solution](#sol2)





# sub-square-matrices with all a's<a name="sub-square-all-1s"></a>

1. Given a `m * n` matrix of ones and zeros, return how many **square** submatrices have all ones.

2. ```bash
   Input: matrix =
   [
     [0,1,1,1],
     [1,1,1,1],
     [0,1,1,1]
   ]
   Output: 15
   Explanation: 
   There are 10 squares of side 1.
   There are 4 squares of side 2.
   There is  1 square of side 3.
   Total number of squares = 10 + 4 + 1 = 15.
   ```

3. [sub_squares.py](sub_squares.py)



# Solution<a name="sol1"></a>

1. `memo` = a matrix of same dimensionality, and all elements initialised to 0
2. for a cell `matrix[i,j]` 
   1. if it itself is 1, then it can contribute to the total count , since it itself represents a square matrix of 1x1.
   2. if it is a part of a bigger matrix of all 1's, then that is possible if and only if `memo[i-1,j],memo[i,j-1],memo[i-1,j-1]` are all 1's, then only will `memo[i,j] > 1` .
   3. if any of the 3 elements are 0, then only the contribution of `matrix[i,j] == 1`, i.e. a matrix of 1x1 is to be counted.
   4. this code considers the outcome that cell `i,j` is the bottom-right cell of a matrix of order mxm. and we are basically checking for how many such square-matrices of all 1's can the cell `i,j` be their bottom-right element.
   5. by default the first row and first column of `memo` is equal to that of `matrix`.







# Even-summed K-sized Permutations in a given range<a name="k-sized-permutations"></a>

1. Given a range **[low, high]**, both inclusive, and an integer **K**, the task is to select **K** numbers from the range(a number can be chosen multiple times) such that the sum of those **K** numbers is even. 
   Print the number of all such permutations.

2. **Input:** low = 4, high = 5, k = 3 
   **Output:** 4 
   **Explanation:** 
   There are 4 valid permutation. They are {4, 4, 4}, {4, 5, 5}, {5, 4, 5} and {5, 5, 4} which sum up to an even number.

   **Input:** low = 1, high = 10, k = 2 
   **Output:** 50 
   **Explanation:** 
   There are 50 valid permutations. They are {1, 1}, {1, 3}, .. {1, 9} {2, 2}, {2, 4}, …, {2, 10}, …, {10, 2}, {10, 4}, … {10, 10}. 
   These 50 permutations, each sum up to an even number.





## Solution<a name="sol2"></a>

1. even-summed-permutations - either all numbers are even, or there are even number of odd numbers + some even numbers in this K-sized permutations

   1. odd-summed permutations - 
      1. if k is odd - all numbers odd, remove 2 odd numbers, replace with even, repeat this removal-replacement process
      2. if k is even - k-1odd + 1-even , k-3 odd + 3-even .....

2. firstly, find total number of even and odd numbers in the given range.

3. iterate k times to find number of ways of producing a permutation having even sum **and odd sum**

4. ```cpp
   int countEvenSum(int low, int high, int k)  {  
       int even_count = high / 2 - (low - 1) / 2;  
       int odd_count = (high + 1) / 2 - low / 2;  
       long even_sum = 1;  
       long odd_sum = 0;
       for(int i = 0; i < k; i++) {
           long prev_even = even_sum;  
           long prev_odd = odd_sum;
           even_sum = (prev_even * even_count) +  
                       (prev_odd * odd_count); 
           odd_sum = (prev_even * odd_count) + 
                      (prev_odd * even_count);  
       }
       cout << (even_sum);  
   }
   ```

5. 1st iteration - just checks how many ways of getting a permutation of size = 1 with even and odd sums

   1. basically check number of even numbers and odd numbers

6. 2nd iteration - permutations of size=2

   1. even+even, odd+odd = even summed permutations , which is going to be ![equation](https://latex.codecogs.com/gif.latex?%5Cbinom%7B%5Ctextrm%7Beven%5C_count%7D%7D%7B1%7D%5Ctimes%5Cbinom%7B%5Ctextrm%7Beven%5C_count%7D%7D%7B1%7D%20&plus;%20%5Cbinom%7B%5Ctextrm%7Bodd%5C_count%7D%7D%7B1%7D%5Ctimes%5Cbinom%7B%5Ctextrm%7Bodd%5C_count%7D%7D%7B1%7D)
   2. odd+even, even + odd = odd summed permutations, ![equation](https://latex.codecogs.com/gif.latex?%5Cbinom%7B%5Ctextrm%7Beven%5C_count%7D%7D%7B1%7D%5Ctimes%5Cbinom%7B%5Ctextrm%7Bodd%5C_count%7D%7D%7B1%7D%20&plus;%20%5Cbinom%7B%5Ctextrm%7Bodd%5C_count%7D%7D%7B1%7D%5Ctimes%5Cbinom%7B%5Ctextrm%7Beven%5C_count%7D%7D%7B1%7D)
   3. In case we are worried about **permutation order** , take a simple case of `[low=1,high=10]`,  even-summed permutation - 2,2 , 2,4 , 2,6  , 2,8 , 2,10,  4,2  4,4 ,  4,6  , 4,8 ..... hence we see that the cases for permutations with duplicate elements also gets counted in a correct way(no-double counting of permutations with duplicate element is occurring in our algorithm)

7. this is continued till K iterations , and since we want an even-summed permutation, the `even_sum` variable is returned.





