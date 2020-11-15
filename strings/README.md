# Table of Contents

1. [Repeating Pattern](#repeated-pattern)
   1. [Solution](#repeated-pattern-sol)
2. [Valid palindrome 2](#vp2)
   1. [Solution](#vp2-sol)
3. [Knuth-Morris-Pratt Algorithm for substring search](#kmp)
   1. [Solution](#sol3)





# Repeating pattern<a name="repeated-pattern"></a>

1. [Leetcode](https://leetcode.com/problems/repeated-substring-pattern/)





## Solution<a name="repeated-pattern-sol"></a>

1. The maximum length of a "repeated" substring that you could get from a string would be half it's length
   For example, s = "abcdabcd", "abcd" of len = 4, is the repeated substring.
   You cannot have a substring >(len(s)/2), **that can be repeated**.
2. So, when ss = s + s , we will have atleast 4 parts of "repeated substring" in ss.
3. (s+s)[1:-1], With this we are removing 1st char and last char => Out of 4 parts of repeated substring, 2 part will be gone (they will no longer have the same substring).
4. ss.find(s) != -1, But still we have 2 parts out of which we can make s. And that's how ss should have s, if s has repeated substring.
5. [repeatingPattern.py](repeatingPattern.py)





# Valid palindrome-2<a name="vp2"></a>

1. Given a non-empty string `s`, you may delete **at most** one character. Judge whether you can make it a palindrome.

2. ```bash
   Input: "aba"
   Output: True
   
   Input: "abca"
   Output: True
   ```
   
3. [Leetcode](https://leetcode.com/problems/valid-palindrome-ii/)



## Solution<a name="vp2-sol"></a>

1. 2 pointer-approach, low = first index, high = last index
2. locate the first place of mismatch
3. at that place
   1. the strings formed by 0:low and high:last are already equal, hence deletion wouldn't happen there, and a deletion that actually takes place wouldn't affect them either
   2. either the deletion happens at low, or at high, hence do both and check if either of the operations result in a palindrome
   3. if none of them do, then return false, since a deletion will now happen upstream, thus having an assumption that characters at low-stream are already equal, i.e. `s[0:low] == s[high:-1]` which is obviously not true, since we had found a mismatch at `low,high`
4. [vp2.py](vp2.py)





# Knuth-Morris-Pratt Algorithm<a name="kmp"></a>

1. used for pattern matching, or in better words, substring search.

2. find all occurrences of a string `pattern`  in a given string `s`

3. ```bash
   Input: pattern="bcgl", s="abcbcglx"
   output: true
   ```



## Solution<a name="sol3"></a>

1. **Naive solution** would be to iterate from `i=0 to i=len(s)-len(pattern)` and check for all appropriate matches, `O(len(s)*len(pattern))` approach

2. iterate through the string `pattern` and construct an auxiliary array called `lps[]`, that stores the **length of longest proper prefix, which is also a suffix**, of the pattern

   1. at each position `i`  in the pattern, `lps[i]` indicates the **longest proper prefix** for the substring `pattern[0:i+1]`, i.e. indices 0 to i in pattern.

   2. longest proper prefix is defined as the longest prefix of a given string, and **not the entire string**.

   3. Here, we are trying to find the longest proper prefix, which is also a  **suffix** (or else, trivially the longest proper prefix would have been `pattern[0...m-2]`) .

   4. in our case, the array **`lps[]`** actually stores the longest proper prefix of the pattern, which is also a suffix.

      1. thus if `pattern="abcaby"`, then `abcab` is the longest proper prefix of this string.

   5. Reference code(also present as a section in [kmp.cpp](kmp.cpp))

      ```cpp
      // construct lpp
      int i = 0, j = 0;
      while(j < m){
          if(p[i] == p[j]){
              if(i == j) lpp[i] = 0;
              else{
                  lpp[j] = lpp[j-1]+1;
                  i++;
              }
          }
          else{
              if(i == 0) lpp[j] = 0;
              else{
                  while(i > 0 && p[j] != p[i]) i = lpp[i-1];
                  if(p[i] == p[j]) lpp[j] = lpp[i]+1;
                  else lpp[j] = 0;
              }
          }
          j++;
      }
      ```

   6. the `i` and `j` pointers serve as storing the length of the longest proper prefix which is also a suffix

      1. if `p[i] == p[j]` and `i != j` and this is the first time that this is occurring, we know that we have found a prefix, which is also a suffix, for the string `p[i....j]`(both indices included).
      2. hence we perform `i++;j++;` on such a discovery, and also `lpp[j] = lpp[j-1] `, since we have found a string which is a prefix and a suffix of the substring `p[0....j]` since we now want to check whether for the substring `p[i+1....j+1]` is `p[i+1] ==  p[j+1]`, i.e. for the substring `p[0.....j+1]` does `p[i]+[i+1] == p[j]+p[j+1]` (string concatenation), i.e. can we find a prefix which is also a suffix longer than that found in step-1 .
         1. we also perform `lpp[j] = lpp[j-1]` in case `p[i] == p[j] && i != j` because this indicates an existence of an even longer prefix(which is also a suffix) than that indicated by `lpp[j-1]`(remember the definition of **`lpp`**), for the substring `p[0....j]` .
      3. if yes, we further increment i and j in hopes of finding the lpp which is also a suffix, of length 3 and so on and so forth.
      4. if no, i.e. we found that `p[i] != p[j]`(incremented i and j), we  suspect that we might have encountered some other kind of prefix(which is also a suffix) having some common characters (i, i+1.. i' , j, j+1, ....j' such that p[i'] != p[j'], but p[i] == p[j], p[i+1]==p[j+1].... ) and since this may not be the longest prefix found yet, we iterate i back to `lpp[i-1]` which stores the information about the last time(starting index of such a prefix) such a prefix `p[i,i+1...i']` was encountered.

3. 