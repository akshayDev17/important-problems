Table of contents

1. [Minimum swaps](#min-swaps)





# Minimum swaps to balance parenthesis<a name="min-swaps"></a>

1. store positions of each  starting bracket '[' , initialise pos-pointer p=0.
2. iterate through the string, maintaining a count
   1. increment if '[' is encountered, decrement if ']' is encountered
   2. if count < 0, find the smallest p with pos[p] > i, i : index at which count < 0 was observed
   3. `ans += pos[p]-i`, since this `']'` and `'['` will be exchanged
   4. swap these characters
   5. reinitialize `count = 0` and carry out the remaining part of the string



