# Table of contents

1. [Minimum swaps](#min-swaps)
2. [Generate Queue](#generate-queue)





# Minimum swaps to balance parenthesis<a name="min-swaps"></a>

1. store positions of each  starting bracket '[' , initialise pos-pointer p=0.
2. iterate through the string, maintaining a count
   1. increment if '[' is encountered, decrement if ']' is encountered
   2. if count < 0, find the smallest p with pos[p] > i, i : index at which count < 0 was observed
   3. `ans += pos[p]-i`, since this `']'` and `'['` will be exchanged
   4. swap these characters
   5. reinitialize `count = 0` and carry out the remaining part of the string
3. [min-swaps.cpp](min-swaps.cpp)





# Generate Queue<a name="generate-queue"></a>

1. **Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers `(h, k)`, where `h` is the height of the person and `k` is the number of people in front of this person who have a height greater than or equal to `h`. Write an algorithm to reconstruct the queue.**

2. **Example:**

   ```
   Input:
   [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
   
   Output:
   [[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
   ```

3. sort the elements with an increasing order of height, and for elements of same height, sort them in the same fashion.

4. the initialised answer 2D vector is then filled by iterating through this array.

5. the `priority_queue` used basically yields the person with the least height, and we fill up the queue-vector in this manner

6. for the current value popped out from the `priority_queue` it is certain that all values that have been already filled in the answer-2D-vector had heights either less than or equal to this entity's height

   1. if its less than, we don't really care(`if(out[i][0] != -1 && out[i][0] != temp.first)`)
   2. if its equal to, the value of the candidate position is forcefully decremented , that is given by the variable `count` .
   3. its the basic assumption that each person will have an index idx &ge; k , the number of people in front of this person and having height &ge; this person.

7. the value of count is also decremented if we iterate through an empty slot, i.e. `out[i][0] == out[i][1] == -1` , since this may be a candidate position for a person of height that is &ge; the current person's height, hence will be counted towards summing up to k.

8. cpp-file : [queue_recon.cpp](queue_recon.cpp) sample-test-case = [queue_recon.txt](queue_recon.txt)