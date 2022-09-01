# Description
1. Values stored in sorted order.
2. Elements will be unique.
3. Insertion: `set<element> s; s.insert(elem);` , O(Log N) (Binary search tree insertion complexity)
4. Removal of an element: O(Log N)
5. Cannot be subscripted, but can be iterated using pointer: `for(auto it: set_s)`
    1. items will be accessed in sorted order.
6. Search: Binary Search tree implementation.(`set_s.find(elem)`)
7. 