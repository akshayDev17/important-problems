# Table of Contents
1. [Max XOR of two elements in array](#max_xor)

# Max XOR of two elements in array<a name="max_xor"></a>
1. Given an array of size n(n <= 2 * 10^5) , return max xor value of two elements. All elements are non-negative.
2. Explanation:
    1. Mask each element.
        1. w.r.t. the test case `[3,10,5,25,2,8]`, till bit > 4, all mask to 0.
        2. at bit=4 , idx=3 masks to 16, all others mask to 0.
        3. at bit-3, idx=3-->24, idx=1,5--->8, idx=0,2,4-->0
        4. at bit=2, idx=3-->24, idx=1,5--->8, idx=2-->4, idx=0,4-->0
    2. insert mask into a set.
    3. the idea here is that if `newMax` is the answer, it should be found by xoring atleast 1 pair in the given array. \
    Say the pair is a,b , where a and b are masks of actual values A,B. \
    if `a^b = newMax`, then `a^newMax = b` , hence we xor off all masks in the set(`a`) with `newMax` to see if `b` is found, if yes, `mx=newMax`, i.e. a new maximum is found. \
    4. `newMax(at bit=i) >= (at bit=i+1)` because `mx` will either remain unchanged(the if condition wasn't met), or if the condition is met, then `mx` goes from `...1000...` --> `...1100...`
2. Solution: [max_xor.cpp](max_xor.cpp)



