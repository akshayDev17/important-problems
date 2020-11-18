# Table of Contents

1. [Introduction](#intro)
2. [Maximum of all subarrays of size k](#max-subarr-k)







# Introduction<a name="intro"></a>

1. double-ended queue - a Queue that allows insertion and deletion  **at both ends**.

   1. note that the spelling is actually **deque**(and not dequeue).

2. Unlike vectors, contiguous storage allocation may **not** be guaranteed.

3. ```cpp
   #include <iostream> 
   #include <deque> 
     
   using namespace std; 
     
   void showdq(deque <int> g) 
   { 
       deque <int> :: iterator it; 
       for (it = g.begin(); it != g.end(); ++it) 
           cout << '\t' << *it; 
       cout << '\n'; 
   } 
     
   int main() 
   { 
       deque <int> gquiz; 
       gquiz.push_back(10);   // insert at back
       gquiz.push_front(20);  // insert at front
       gquiz.push_back(30); 
       gquiz.push_front(15); 
       cout << "The deque gquiz is : "; 
       showdq(gquiz); // no need to empty the queue for iteration, we can iterate in this pointer fashion as well., here its : 15 20 10 30
     
       cout << "\ngquiz.size() : " << gquiz.size(); // in this case, 4
       cout << "\ngquiz.max_size() : " << gquiz.max_size(); // how much total can it accomodate, here 4611686018427387903
     
       cout << "\ngquiz.at(2) : " << gquiz.at(2); // similar to a vector/array indexing, vec[2] means the third element, i.e. 10 .
       cout << "\ngquiz.front() : " << gquiz.front(); // 15
       cout << "\ngquiz.back() : " << gquiz.back();   // 30
     
       cout << "\ngquiz.pop_front() : "; 
       gquiz.pop_front(); // 15 is removed
       showdq(gquiz);     // 20 10 30
     
       cout << "\ngquiz.pop_back() : "; 
       gquiz.pop_back(); // 30 is removed
       showdq(gquiz);    // 20 10
     
       return 0; 
   } 
   ```

4. Other methods:

   ```cpp
   #include <iostream>
   #include <deque>
   using namespace std;
   
   void showdq(deque <int> g) { 
       deque <int> :: iterator it; 
       for (it = g.begin(); it != g.end(); ++it) 
           cout << *it << " "; 
       cout << '\n';} 
   
   int main(){
       deque<int> dq = {1,2,3}; // we can initialize a deque just like a vector/array.
       deque<int>::iterator it = dq.insert(dq.begin(), 19); // insert always requires a pointer argument, followed by the value to be inserted.
       showdq(dq); // 19 1 2 3 
       cout << endl << *dq.rbegin() << endl; /*dq.rbegin() represents a reverse pointer , which points to the last element of the deque, i.e. reverse begin, in this case output = 3. */
       cout << endl << *dq.rend() << endl; // similarly, dq.rend() is a reverse iterator that points to the start of the deque, i.e. reverse-end, in this case output = 0.
       cout << endl << *dq.cbegin() << endl; // constant iterator that points to the start of the deque, AND CANNOT BE MODIFIED.
       cout << endl << *(++dq.cbegin()) << endl;
   
       // assign 5 values of 10 each 
       dq.assign(5, 10);
       showdq(dq); // 10 10 10 10 10
   
       // assign 10 values of 5 each 
       dq.assign(10, 5);
       showdq(dq); // 5 5 5 5 5 5 5 5 5 5
   
       dq.resize(0);
       dq.push_back(1);dq.push_back(2);dq.push_back(3);
       showdq(dq); // 1 2 3
   
       dq.resize(2);
       showdq(dq); // 1 2
   
       dq.resize(4);
       showdq(dq); // 1 2 0 0
   
       dq.at(2) = 69;
       showdq(dq); // 1 2 69 0
   
       deque<int> dq2;
       dq2.assign(dq.begin() + 1, dq.end());
       showdq(dq2); // dq2 = 2 69 0
       
       dq.pop_front(); // remove first element
       showdq(dq); // dq = 2 69 0
       dq.pop_back(); // remove last element
       showdq(dq); // dq = 2 69
       
       cout << dq.front() << " " << dq2.back() << endl;  // 2 0
       dq.clear(); // just made the first deque empty.
       if(dq.empty()) cout << "\nfirst deque became empty\n"; // check if deque is empty
       cout << "\nThe size of copy deque is :  " << dq2.size() << endl;
       
       // erase is used to remove elements at a specific position(or range of positions)
       dq2.push_back(68);dq2.push_front(86);dq2.push_back(100);
       showdq(dq2); // 86 2 69 0 68 100
       dq2.erase(dq2.begin()+2, dq2.end()-1); // elements from index=2 to index=n-2 deleted
       showdq(dq2); // 86 2 100
       
       dq.push_front(1);dq.push_front(2);dq.push_front(3);showdq(dq); // 3 2 1
       dq = dq2; // equal-to operator of deque, similar to assign(.begin(), .end())
       showdq(dq); // 86 2 100
       
       cout << endl << dq[1] << endl; // output = 2, indexing operator, just like an array/vector
       dq.push_front(98);
       showdq(dq); /* 98 86 2 100*/ showdq(dq2); /*86 2 100*/
       dq.swap(dq2); // swaps the 2 deques
       showdq(dq); /* 86 2 100*/ showdq(dq2); /* 98 86 2 100*/
       return 0;}
   ```

   1. `dq.assign(num, val)` : assigns a deque of size `num` with all values being equal to `val`, and if the deque is already initialised, then this function destroys the values of the previous elements and re-assigns the new ones.
      we can also use assign, with pointers, to transfer some(or all) values of one deque to another.
   2. `dq.resize(n)` : resizes the deque to size `n`
      1. if n is smaller than initial size of deque, elements are destroyed from the end.
      2. else elements are added to the end.
   3. for `dq.at(x)`, if the position is not present in the deque, it throws ***out_of_range***.







# Maximum of all subarrays of size k/Sliding Window Maximum<a name="max-subarr-k"></a>

1. Given an array and an integer **K**, find the maximum for each and every contiguous subarray of size k.

2. **Examples :** 

   ```bash
   Input: arr[] = {1, 2, 3, 1, 4, 5, 2, 3, 6}, K = 3 
   Output: 3 3 4 5 5 5 6
   Explanation: 
   Maximum of 1, 2, 3 is 3
   Maximum of 2, 3, 1 is 3
   Maximum of 3, 1, 4 is 4
   Maximum of 1, 4, 5 is 5
   Maximum of 4, 5, 2 is 5 
   Maximum of 5, 2, 3 is 5
   Maximum of 2, 3, 6 is 6
   
   Input: arr[] = {8, 5, 10, 7, 9, 4, 15, 12, 90, 13}, K = 4 
   Output: 10 10 10 15 15 90 90
   Explanation:
   Maximum of first 4 elements is 10, similarly for next 4 
   elements (i.e from index 1 to 4) is 10, So the sequence 
   generated is 10 10 10 15 15 90 90
   ```





# Solution<a name="sol1"></a>

1. [CODE](slidingWindowMaximum.cpp) , [TEST](slidingWindowMaximumTest.txt)

2. construct a deque for the first i=0 to i=k-1 elements, such that it contains indices of those elements that are greater than all the elements in their right, for this particular window.

   1. and the order is such that, of these indices that end up in the deque, the index at the front corresponds to the maximum, next index is the next maximum and so on.

   2. ```cpp
      while(!dq.empty() && arr[dq.back()] <= arr[i]) dq.pop_back();
      dq.push_back(i);
      ```

   3. these 2 lines help in the ordering, since the incoming element is pushed at the back, just because it trivially exceeds all of its right elements in the current window.

   4. since the elements corresponding to the indices at the back of the deque are the least, we eliminate all such indices, till we encounter an index whose corresponding element(in the main array) is greater than the incoming element, thus this makes the incoming element, the least among all the remaining elements in the queue.

   5. thus its index is added at the back.

3. Now, run a loop from k to end of the array.

4. the front element of the deque will always be the maximum index element for this current window(current window ends at element with index i). `ans.push_back(arr[dq.front()]);`

5. Remove those elements from the front of the queue if they are out of the current window. `while(!dq.empty() && dq.front() <= i-k) dq.pop_front();`

6. Insert the next element in the deque. 

   1. Before inserting the element, check if the element at the back of the queue is smaller than the current element , if it is so remove the element from the back of the deque, until all elements left in the deque are greater than the current element.  `while(!dq.empty() && arr[dq.back()] <= arr[i]) dq.pop_back();`
   2. Then insert the current element, at the back of the deque. `dq.push_back(i);`

7. since after adding the last element into the dequeu the loop stops, we need to write a separate line outside of the loop, to get the result of this last window and add it to our ending array. `ans.push_back(arr[dq.front()]);`