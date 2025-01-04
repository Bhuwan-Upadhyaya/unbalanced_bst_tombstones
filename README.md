# CSE 3318 Lab Assignment 4

## Overview
This project involves implementing and maintaining an **Unbalanced Binary Search Tree (BST)** with support for **tombstones** to handle deletions efficiently. The program processes a series of commands to perform operations on the BST, ensuring subtree sizes remain accurate and supporting operations like rank queries, tree auditing, and rebuilding.

## Goals
1. Gain an understanding of **unbalanced binary search trees**.
2. Learn the concept and implementation of **tombstones** for logical deletions.
3. Efficiently manage subtree sizes and optimize tree operations.

## Requirements
The program supports the following commands:

- **0:** Exit the program.
- **1 x:** Insert a positive integer key `x` into the tree.
- **2 x:** Logically delete key `x` using a tombstone.
- **3 x:** Find the **rank** of key `x`.
- **4 k:** Find the **k-th smallest** key in the tree.
- **5:** Print tree statistics (live nodes, dead nodes, recycling list size, and longest path length).
- **6:** Rebuild the tree using live nodes.
- **7:** Print the tree structure with subtree sizes.
- **8:** Perform an **audit** to verify tree integrity and correctness.

Each command must execute within the specified time complexity bounds.

## Getting Started
### Dependencies
- GCC Compiler
- Standard C Libraries

### Compilation
Use the following command to compile the program on **OMEGA**:
```
gcc -o lab4 main.c bst.c -Wall -std=c11
```

### Execution
Run the program with:
```
./lab4 < input.txt
```
- `input.txt`: File containing the sequence of commands.

### Sample Input
```
1 10
1 5
1 15
2 5
3 10
4 2
5
6
7
8
0
```

### Sample Output
```
Command: 1 10
Command: 1 5
Command: 1 15
Command: 2 5
Command: 3 10 -> Rank: 2
Command: 4 2 -> Key: 10
Command: 5 -> Live Nodes: 2, Dead Nodes: 1, Longest Path: 2
Command: 6 -> Tree rebuilt successfully.
Command: 7 -> Tree Structure Printed
Command: 8 -> Tree is clean.
Command: 0 -> Exiting...
```

## Files Included
- **main.c**: Driver code to handle user commands.
- **bst.c**: Implementation of BST operations.
- **bst.h**: Header file containing BST structure and function prototypes.
- **Makefile**: Build automation for the project.
- **README.md**: Documentation for the project.

## Key Concepts
- **Tombstones:** Logical deletions marked without physically removing nodes.
- **Rank Query:** Finding the number of keys smaller than or equal to a given key.
- **Tree Rebuilding:** Efficient rebalancing without full re-insertion.

## Testing
Provide an input file with valid commands and run the program. Verify outputs manually or use automated scripts.

## Known Issues
- None reported.

## Author
- Bhuwan Upadhyaya
- 1002079187

## License
This project is licensed under the **MIT License**.

## References
- [Lab Resources](https://ranger.uta.edu/~weems/NOTES3318/BST/)
- Course Lecture Notes

---
**Submission Deadline:** November 19, 5:00 PM on Canvas.

Ensure your submission includes all necessary files and adheres to the guidelines provided in the lab assignment documentation.

Happy Coding! 🚀
