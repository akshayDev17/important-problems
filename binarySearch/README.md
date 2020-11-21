# Table of Contents

1. [Find minimum in rotated sorted array *with duplicates*](#prob1)
   1. [Solution](#sol1)







# Find minimum in rotated sorted array *with duplicates*<a name="prob1"></a>

1. Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

   (i.e.,  `[0,1,2,4,5,6,7]` might become  `[4,5,6,7,0,1,2]`).

   Find the minimum element.

   **The array may contain duplicates**.

   **Example 1:**

   ```
   Input: [1,3,5]
   Output: 1
   ```

   **Example 2:**

   ```bash
   Input: [2,2,2,0,1]
   Output: 0
   ```





## Solution<a name="sol1"></a>

1. ```cpp
   int findMin(vector<int>& nums) {
       int n = nums.size();
       if(n == 0) return 0;
       if(n == 1) return nums[0];
       if(n == 2) return min(nums[0], nums[1]);
       int lo = 0, hi = n-1;
       while(lo < hi){
           int m = lo + (hi-lo)/2;
           if (nums[m] > nums[hi]) lo = m + 1;
           else if (nums[m] < nums[hi]) hi = m;
           else hi--; // duplicate nums[m] and nums[hi]
           }
       }
       return nums[lo];
   }
   ```

2. remember to compare mid to its upper limit element.

   1. for the first `if` , it can never happen that `nums[m] > nums[hi]` but the minimum element is at the left of this mid element, since 
      1. if the example is `[1 2 3 4 5 6 0 1 2]`, this is satisfied
      2. if the example is `[1 5 20 0 1 2 3 4 5]`,  this doesn't fall in the criteria of `nums[m] > nums[hi]` thus pointing out that minimum surely lies towards the left of the middle element.
      3. the logic behind this is that if `nums[m] > nums[hi]`, the middle element `m` has landed at the first sorted array `nums[lo]...nums[minimum-1]`.
   2. for the next `if`, it means that middle element `m` has landed in the second sorted array, `nums[minimum]....nums[hi]`, or that the first sorted array is much shorter than that of the second sorted one.

3. due to the **presence of duplicates**, this code eventually boils down to a linear search, as seen by the line **`hi--;`**,

   1. particularly `hi--;` is performed, since the array may not be even rotated, i.e. it may just be a sorted array.
   2. in such cases, if instead `lo++;` is performed, we obviously skip the minimum element.
   3. such a case is a trivial example of the middle element falling in the *second sorted array*, here the first sorted array is of size 0.