# Table of contents

1. [Fractional Knapsack](#fkp)
2. [Minimum swaps](#min-swaps)
3. [Generate Queue](#generate-queue)





# Fractional Knapsack<a name="fkp"></a>

1. Given weights and values of `n` items, we need to put these items in a knapsack of capacity `W` to get the maximum total value in the knapsack.

2. We can break items for maximizing the total value of knapsack, thus the name *fractional* knapsack.

3. ```bash
   Input: 	
   values[] = {60, 100, 120}
   weights[] = {10, 20, 30}
   W = 50
   
   Output :
   Maximum possible value = 240
   By taking full items of 10 kg, 20 kg and 
   2/3rd of last item of 30 kg
   ```

4. calculate the ratio value/weight for each item and sort the item on basis of this ratio(descending order of this ratio).

5. Add the item with the highest ratio, until it cannot be added any further(find the maximum weight of this item, in a fractional sense, that can be added into the knapsack, till either the knapsack is full, or we don't have any quantity of the item left)

   1. in the above example, `ratio = [6, 5, 4]`
   2. now `i = 0`(since this example is already sorted in a descending order, w.r.t. ratio values), check `if(wt[i] <= W)` , if yes, put all of item-i into the knapsack, `value += wt[i]*ratio[i], i++`, updating W as `W -= wt[i]` if no, put as much as can be, i.e. `W` and we will have `value += W*ratio[i]`, updating W as `W = 0`
   3. repeat step 2 till `W == 0`, return `value`.

6. Time complexity = O(NlogN), space complexity = O(N).

7. [CODE](fkp.cpp), [TEST](fkpTest.txt)

8. [0-1 knapsack problem](../dynamicProgramming/README.md/#0-1kp)







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