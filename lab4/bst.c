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
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

link z, head;               // Sentinel and root
Item NULLitem = -9999999;   // Sentinel data
static int recycledNodes = 0;  // Count of recycled nodes

// Create a new node
link NEW(Item item, link l, link r, int N) {
    link x = malloc(sizeof *x);
    x->item = item;
    x->l = l;
    x->r = r;
    x->N = N;
    x->tombstone = 0;
    return x;
}

// Initialize tree with sentinel
void STinit() {
    head = (z = NEW(NULLitem, NULL, NULL, 0));
}

// Fix subtree size
void fixN(link h) {
    if (h != z) {
        h->N = h->l->N + h->r->N + (h->tombstone == 0 ? 1 : 0);
    }
}

// Recursive insertion
link STinsertR(link h, Item item) {
    if (h == z) return NEW(item, z, z, 1);

    if (eq(item, h->item)) {
        if (h->tombstone) {
            h->tombstone = 0;  // Revive the node
            recycledNodes--;
        }
    } else if (less(item, h->item)) {
        h->l = STinsertR(h->l, item);
    } else {
        h->r = STinsertR(h->r, item);
    }
    fixN(h);
    return h;
}

// Public insertion function
void STinsert(Item item) {
    head = STinsertR(head, item);
}

// Recursive deletion
void STdelete(Key v) {
    link h = head;
    while (h != z) {
        if (eq(v, h->item)) {
            if (!h->tombstone) {
                h->tombstone = 1;  // Mark as dead
                recycledNodes++;
                fixN(head);        // Update subtree sizes
            }
            return;
        }
        h = less(v, h->item) ? h->l : h->r;
    }
}

// Recursive search
Item searchR(link h, Key v) {
    if (h == z) return NULLitem;
    if (eq(v, h->item)) return h->tombstone ? NULLitem : h->item;
    return searchR(less(v, h->item) ? h->l : h->r, v);
}

// Public search function
Item STsearch(Key v) {
    return searchR(head, v);
}

// Recursive rank calculation
int invSelectR(link h, Key v) {
    if (h == z) return -1;

    if (eq(v, h->item)) return h->tombstone ? -1 : h->l->N + 1;
    if (less(v, h->item)) return invSelectR(h->l, v);

    int rank = invSelectR(h->r, v);
    if (rank == -1) return -1;
    return rank + h->l->N + (h->tombstone ? 0 : 1);
}

// Public rank function
int STinvSelect(Key v) {
    return invSelectR(head, v);
}

// Recursive select function
Item selectR(link h, int k) {
    if (h == z) return NULLitem;

    int t = h->l->N + (h->tombstone ? 0 : 1);
    if (k == t) return h->item;
    if (k < t) return selectR(h->l, k);
    return selectR(h->r, k - t);
}

// Public select function
Item STselect(int k) {
    if (k < 1 || k > getLive()) return NULLitem;
    return selectR(head, k);
}

// Print tree recursively
void printTree(link h, int depth) {
    if (h == z) return;

    printTree(h->r, depth + 1);
    int i;
    for (i = 0; i < depth; i++) printf("     ");
    printf("%s%d %d\n", h->tombstone ? "(" : "", h->item, h->N);
    printTree(h->l, depth + 1);
}

// Public print function
void STprintTree() {
    printTree(head, 0);
}

// Verify BST properties (audit)
int checkInorder(link h, Key *last) {
    if (h == z) return 1;

    if (!checkInorder(h->l, last)) return 0;
    if (less(h->item, *last) && !h->tombstone) {
        printf("Inorder error at key %d\n", h->item);
        return 0;
    }
    if (!h->tombstone) *last = h->item;
    return checkInorder(h->r, last);
}

int verifyBSTproperties() {
    Key last = -9999999; // Minimum possible key
    return checkInorder(head, &last);
}

// Rebuild tree and collect live nodes
void collectLiveNodes(link h, link *liveList, int *index) {
    if (h == z) return;

    collectLiveNodes(h->l, liveList, index);
    if (!h->tombstone) liveList[(*index)++] = h;
    collectLiveNodes(h->r, liveList, index);
}

link rebuildTree(link *liveList, int start, int end) {
    if (start > end) return z;

    int mid = (start + end) / 2;
    link root = liveList[mid];
    root->l = rebuildTree(liveList, start, mid - 1);
    root->r = rebuildTree(liveList, mid + 1, end);
    fixN(root);
    return root;
}

void removeDead() {
    int liveCount = getLive();
    link *liveList = malloc(liveCount * sizeof(link));
    int index = 0;

    collectLiveNodes(head, liveList, &index);
    head = rebuildTree(liveList, 0, liveCount - 1);

    free(liveList);
}

// Get live nodes count
int getLive() {
    return head->N;
}

// Get dead nodes count
int getDead() {
    return recycledNodes;
}

// Compute tree height
int computeHeight(link h) {
    if (h == z) return 0;
    int left = computeHeight(h->l);
    int right = computeHeight(h->r);
    return 1 + (left > right ? left : right);
}

int getHeight() {
    return computeHeight(head);
}

// Get recycled node count
int getRecycled() {
    return recycledNodes;
}
