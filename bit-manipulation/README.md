# Table of Contents
1. [Maximum XOR After Operations](#max_xor_after_operations)

# Maximum XOR After Operations<a name="#max_xor_after_operations"></a>
1. > You are given a 0-indexed integer array nums. In one operation, select any non-negative integer x and an index i, then update nums[i] to be equal to nums[i] AND (nums[i] XOR x). \
    Note that AND is the bitwise AND operation and XOR is the bitwise XOR operation. \
    Return the maximum possible bitwise XOR of all elements of nums after applying the operation any number of times.
2. `x` can be any goddamn whole number in the world.
3. Read explanation [here](https://leetcode.com/problems/maximum-xor-after-operations/discuss/2373604/C%2B%2B-Beginner-Friendly-Explanation), the reason this guy tells that even if the i'th bit of atleast one number is set, it doesn't matter if i'th bit of other numbers is set because:
    > if there are odd number of numbers in arr with i'th bit set, then no worries, if there are even, then exactly one number can be changed by unsetting that bit, since the resultant number will be less than original and that is permissible by the operations(Notice that after carrying out the operation, the resultant number will always be atmost the original number).
    > {1,4,6,2,3,10}: \
        0001 0001  0001 `0000` \
        0100 0100  0100  0100 \
        0110 `0010` 0010  0010 \
        0010 0010  `0000` 0000 \
        0011 0011  0011  0011 \
        1010 1010  1010  1010
