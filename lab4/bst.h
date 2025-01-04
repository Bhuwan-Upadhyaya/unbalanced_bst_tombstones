/* 
Name :Bhuwan Upadhyaya
Netid: bxu9187 /1002079187

I used the following command in omega server
gcc -Wall -o lab4 lab4fall24.c bst.c
./lab4 < lab4fall24.a.dat (or cat lab4fall24.a.dat | ./lab4)


Also i tried using the powershell
gcc -Wall -o lab4 lab4fall24.c bst.c
Get-Content lab4fall24.a.dat | ./lab4

*/ 
#ifndef BST_H
#define BST_H

// Define key and item for generic use
typedef int Key;
typedef Key Item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (key(A) == key(B))

// Node structure
typedef struct STnode *link;

struct STnode {
    Item item;       // Data for this node
    link l, r;       // Left and right child pointers
    char tombstone;  // 0 = live key, 1 = dead key
    int N;           // Subtree size (counts only live nodes)
};

// External variables
extern Item NULLitem;

// Function prototypes
void STinit();          // Initialize tree
Item STsearch(Key v);   // Search for a key
void STinsert(Item item);   // Insert a key
void STdelete(Key v);       // Logically delete a key
int STinvSelect(Key v);     // Find rank of a key
Item STselect(int k);       // Find key with a given rank
void STprintTree();         // Print tree
int verifyBSTproperties();  // Verify correctness
void removeDead();          // Rebuild tree
int getLive();              // Get count of live nodes
int getDead();              // Get count of dead nodes
int getHeight();            // Get tree height
int getRecycled();          // Get recycled nodes count

#endif
