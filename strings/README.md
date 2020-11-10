# Table of Contents

1. [Repeating Pattern](#repeated-pattern)
2. [Valid palindrome 2](#vp2)





# Repeating pattern<a name="repeated-pattern"></a>

1. 





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



## Solution<a name="vp2-sol"></a>

1. 2 pointer-approach, low = first index, high = last index
2. locate the first place of mismatch
3. at that place
   1. the strings formed by 0:low and high:last are already equal, hence deletion wouldn't happen there, and a deletion that actually takes place wouldn't affect them either
   2. either the deletion happens at low, or at high, hence do both and check if either of the operations result in a palindrome
   3. if none of them do, then return false, since a deletion will now happen upstream, thus having an assumption that characters at low-stream are already equal, i.e. `s[0:low] == s[high:-1]` which is obviously not true, since we had found a mismatch at `low,high`
4. [vp2.py](vp2.py)