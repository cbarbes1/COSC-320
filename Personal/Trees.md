## Binary Tree Function's
- Searching
- Insertion
- Deletion (deletion by copy and deletion by merge)
- Balancing a tree
- Node Count and Longest Path length
### Node Count and Longest Path Length

### Searching 
`Two types: Iterative and Recursive`

#### 3 types of searching 
- pre-order
- in-order
- post-order
### Insertion 

### Deletion
Two Types: Deletion by copy and deletion by merge

### Balancing a Tree
`Self balancing trees and the algorithms that can be used on binary trees`
#### First We Must define rotation
`This is the fundamental procedure for balancing a tree`
#### Rotation
##### Left Rotation

```
save the right node as R
save the rights left
set the rights left to the nodeptr
set nodeptr right to the rights left
```
```c++
template<class T> void 
```
##### Right Rotation
```c

```

## Self Balancing trees
### AVL Tree
#### 3 criterion for a binary tree to be an AVL tree
- balance factors of either -1, 0, 1
- 
### Red Black Trees
`A red-black Tree that satisfies the following red-black properties`
- `Every Node is either red or black`
- `The root is black`
- `Every leaf (Nil) is black`
- `If a node is red, Then both its children are black`
- `For each node, all simple paths from the node to descendant leaves contain same number of black nodes`
#### Properties
- Insertion
- Deletion
- Color



Data Structures And Algorithms