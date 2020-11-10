# Table of Contents







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