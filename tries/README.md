# Table of Contents

1. [Word search 2][#word-search-2]
   1. [Solution](#sol1)







# Word search 2<a name="word-search-2"></a>

1. Given an `m x n` `board` of characters and a list of strings `words`, return *all words on the board*.
   Each word must be constructed from letters of sequentially adjacent cells, where **adjacent cells** are horizontally or vertically neighbouring. The same letter cell may not be used more than once in a word.

   ```bash
   Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
   Output: ["eat","oath"]
   ```

2. <img src="wordsearch2.jpg" />

3. <img src="wordsearch2_2.jpg" />

   ```bash
   Input: board = [["a","b"],["c","d"]], words = ["abcb"]
   Output: []
   ```





## Solution<a name="sol1"></a>

1. create a `Trie` and insert all strings of `words` in it.
2. perform a depth-first search with backtracking, starting on every node of the board
   1. if a node is found in the current root of the `Trie` , 