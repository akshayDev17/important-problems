# Table of Contents

1. [Repeating Pattern](#repeated-pattern)
   1. [Solution](#repeated-pattern-sol)
2. [Valid palindrome 2](#vp2)
   1. [Solution](#vp2-sol)
3. [Knuth-Morris-Pratt Algorithm for substring search](#kmp)
   1. [Solution](#sol3)
4. [Letter Tile Possibilities](#ltp)
   1. [Solution](#sol4)
5. [Longest Substring Containing Vowels in Even Counts](#even-vowel-counts)
   1. [Solution](#sol5)





String split in cpp:

```cpp
std::string s = "scott>=tiger>=mushroom";
std::string delimiter = ">=";

size_t pos = 0;
std::string token;
while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    std::cout << token << std::endl;
    s.erase(0, pos + delimiter.length());
}
std::cout << s << std::endl;
```



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
      4. if no, i.e. we found that `p[i] != p[j]`(incremented i and j), we  suspect that we might have encountered some other kind of prefix(which is also a suffix) having some common characters (i, i+1.. i' , j, j+1, ....j' such that p[i'] != p[j'], but p[i] == p[j], p[i+1]==p[j+1].... ) and since this may not be the longest prefix found yet, we iterate `i` back to `lpp[i-1]` which stores the information about the last time(starting index of such a prefix) such a prefix `p[i,i+1...i']` was encountered.
      5. for instance, `pattern = "AAACAAAA"`, the corresponding `lps[] = [0 1 2 0 1 2 3 3]`, notice at points `i=0, j = 4` both i and j continuously increment, till `i=3, j = 7`, at which point the code `j = lps[j-1]` is executed, which basically means that 

3. **searching**

   1. re-initialise `i=0;j=0;` , let `n` be the length of the string to be searched in.
   2. while `p[j]==s[i]` increment both i and j.
      1. if j reaches its limit, i.e. end of string, append the position of i at which the first match was found, in other words, append `i-j` to an answer list.
      2. if doesn't reach its limit, it means not all characters of the pattern matched the current substring `s[i-j...i]`, but the string `s[i-j....i-1]` matched completely with `p[0...j-1]` meaning that we **don't need to check for **, since we know by the definition of **`lps[]`** that `lps[j-1]` is count of characters of `p[0…j-1]` that are both proper prefix and suffix.
      3. `if(j == m){ans.pb(i-j);j=lpp[j-1];}` this line tells us that since the first lpp[0...j-1] characters matched, and that `j = lpp[j-1]` gives us the next character that we need to check for mismatch.







# Letter Tile Possibilities<a name="ltp"></a>

1. You have `n` `tiles`, where each tile has one letter `tiles[i]` printed on it.

   Return *the number of possible non-empty sequences of letters* you can make using the letters printed on those `tiles`.

2. [leetcode](https://leetcode.com/problems/letter-tile-possibilities/)

3. ```bash
   Input: tiles = "AAB"
   Output: 8
   Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
   
   Input: tiles = "AAABBC"
   Output: 188
   
   Input: tiles = "V"
   Output: 1
   ```





## Solution<a name="sol4"></a>

1. [CODE](letterTile.cpp) , [TEST](letterTileTest.txt)
2. for an `N` lengthed string, total possible substrings of all sizes = ![equation](https://latex.codecogs.com/gif.latex?%5Csum%5Climits_%7Bi%3D0%7D%5E%7BN%7D%5Cbinom%7BN%7D%7Bi%7D%20%3D%202%5EN)
3. since the empty substring is not to  be considered, total possible strings are ![equation](https://latex.codecogs.com/gif.latex?2%5EN-1), hence the loop `for(int i = 1;i< (1 << tiles.size());i++)` , where `1 << tiles.size()` means ![equation](https://latex.codecogs.com/gif.latex?2%5EN-1)
   1. we start from i = 1, since `i=0` represents the empty string(don't include any character).
4. each character can be bit-encoded into a substring
   1. for instance, if original string `s = "ABC"`, then substring `str="AB"` can be denoted as `110`, where `1` indicates that that particular character is included in this substring, whereas `0` means its excluded
   2. each of these ![equation](https://latex.codecogs.com/gif.latex?2%5EN-1) can be encoded in this bitwise fashion, and if a character, located at index `j` in the main string is present, then `i & (1 << j)` will be non-zero.
5. the `calc` function is basically a representative of the ![equation](https://latex.codecogs.com/gif.latex?%5Cfrac%7Bx%21%7D%7Br_1%21%20r_2%21...r_N%21%7D) where `x = len(str)`, where `str` (refer code) represents one of the substrings formed from an arrangement of `tiles`. the `r_i` indicate count of each unique character in this substring `str` .
6. we insert this substring into a set, and if this substring is generated again due to the bitwise encoding, we force the loop to `continue` meaning that we now don't include the result of `calc` for this substring again.
7. for example, take the case `tiles = "ABC", i = 5` which basically means the substring `AC`(101, thus `B` should be excluded.) `calc` for this substring is 2.







# Longest Substring Containing Vowels in Even Counts<a name="even-vowel-counts"></a>

1. [Leetcode](https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/)

2. Given the string `s`, return the size of the longest substring containing each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.

3. ```
   Input: s = "eleetminicoworoep"
   Output: 13
   Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.
   
   Input: s = "leetcodeisgreat"
   Output: 5
   Explanation: The longest substring is "leetc" which contains two e's.
   
   Input: s = "bcbcbc"
   Output: 6
   Explanation: In this case, the given string "bcbcbc" is the longest because all vowels: a, e, i, o and u appear zero times.
   ```





## Solution<a name="sol5"></a>

1. ```cpp
   class Solution {
   public:
       int findTheLongestSubstring(string s) {
           int n = s.length();
           if(n == 0) return 0;
           
           unordered_map<char,int> mp={{'a', 16}, {'e', 8}, {'i', 4}, {'o', 2}, {'u', 1}};
           if(n == 1) return mp.find(s[0]) == mp.end() ? 1 : 0;
           unordered_map<int,int> valIdx = {{0, -1}};
           int curr = 0, result = 0;
           for(int i = 0;i<n;i++){
               if(mp.find(s[i])!=mp.end()) curr = (curr ^ mp[s[i]]);
               if(valIdx.find(curr) == valIdx.end()) valIdx[curr] = i;
               result = max(result, i - valIdx[curr]);
           }
           return result;
       }
   };
   ```

2. we encode the occurrence of each vowel in the form of a bit

   1. **aeiou** is the bit-wise representation of the number `curr` ,where a=1 means a occurs odd number of times, and i = 0 means that i occurs even number of times.
   2. thus, whenever `curr` becomes 0, we have found ourselves a candidate solution.
   3. each bit basically represents the value `count(vowel) % 2 `

3. initial value of `{0, -1}` is put into the map, since if we find that `curr` becomes 0 later on in the string, then `i-(-1) = i+1` will obviously give us the candidate solution(0-based indexing used to find size of interval).

4. the reason that every new value of `curr` is being pushed into the map is because we may later find the same value, while iterating through the string, which means that the substring existing in between these 2 occurrences has obviously even counts of all vowels.