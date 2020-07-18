#include <stdlib.h>
#include <stdio.h>

#include "mymalloc.h"

/* Feel free to change/remove these variables and/or add your own. */

struct node {
  int data_size;
  struct node *next;
};

// Base address of the allocated heap.
static char *heap;
// Size of the complete heap.
static int heapsize;
// Next unallocated location in the heap.
static int top;

static struct node *head;


/* Initialize your memory manager to manage the given heap. */
void mymalloc_init(char *_heap, int _heapsize) {
  heap = _heap;
  heapsize = _heapsize;
  top = 0;

  /* TODO: Any other initialization you want to do */
  head = 0;
  /* NOTE! Each call to mymalloc_init should initialize a brand new heap
     (discarding the old one), as it will be called once per test.
     Therefore, be sure to *initialize all your variables* here! */
}

/* Allocate a block of memory of the given size, or NULL if unable. 

Returns: a pointer aligned to 8 bytes, or NULL if allocation failed. */
void *mymalloc(int size) {
	
	//printf("\nRunning mymalloc\n");
	
  /* This is a dumb implementation of malloc, adapted slightly from the slides. 

  You will augment this solution to make a real malloc. */

  /* Round `size` up to a multiple of 8 bytes */
  /* TODO: Make room for any extra metadata you want to store */
  size = (size + 7) / 8 * 8;
  /* TODO: Implement and walk a free list before allocating off `top` as a last resort */
 
 if (head != 0) {           // See if free list is not empty
	void* output = 0;
	struct node *first = head;    	   // first node holder
	struct node *second = first->next; // second node holder 
	if (first->data_size >= size) {    // check if first node has enough space

		//printf("first\n");
		//printf("first: 0x%x\n", first);
		//printf("second: 0x%x\n", second);
		output = ((void*) first);      // store first node address to output o=1
									   // free list:  h->1->2->...
		first->next = 0;               // unlink first node from rest of free list  h->1  2->...
									   
		head = second;                 // link head to 2nd node.  h->2->...

		return output + 16;            // offset node address to cut out metadata
	}
	else {                             // first node didn't have enough space, checking 2nd node
		//printf("second\n");
		//printf("first: 0x%x\n", first);
		//printf("second: 0x%x\n", second);
		
		while (second != 0) {     	   // make sure 2nd node actually exists, if it is null, then finished checking free list
			//printf("loop start\n");
			if (second->data_size >= size) {  // see if 2nd node has enough space
				
				//printf("loop mid\n");				
				//printf("output: 0x%x,   head: 0x%x\n", output, head);
				//printf("second->next: 0x%x\n", second->next);
				
				output = ((void*) second);    // store 2nd node address to output o=2
				
										      //           2->3->...
											  // h->...->1----^
				first->next = second->next;   // link first node to 3rd node which is just second->next
				
											  //              3->...
											  // h->...->1----^
				second->next = 0;			  // unlink 2nd node
				
				return output + 16;
			}
			else {                          // 2nd node didn't have enough space
				//printf("loop mid\n");
										    // increment pointers by one
				first = first->next;        // move 1st node pointer to next node
				second = first->next;       // move 2nd node pointer to next node
			}
		//printf("loop end\n");
		}
	}
  }

  //printf("\nChecking heap size\n");
  
  if(size < 0 || size > heapsize || heapsize - size < top) {
    /* There is not enough room in the heap - fail */
    return NULL;
  }
  /* Allocate the memory from `top` to `top+size` and return it */

  //printf("\nAllocating from top\n");
  
  
  struct node *metadata = ((struct node*) &heap[top]);

  metadata->data_size = size;
  void *res = &heap[top + 16];
  struct node *next_block = res + size;
  metadata->next = next_block;
  
  top = top + 16 + size;
  //printf("block_start: 0x%x   size:        0x%x\n", &metadata->data_size, metadata->data_size);
  //printf("&next_ptr:   0x%x   next_ptr:    0x%x\n", &metadata->next, next_block);
  //printf("res:         0x%x   block_value: 0x%x\n", res, size);
  
  return res;
}

/* Free the given block of memory. */
void myfree(void *ptr) {
  /* TODO: Our dumb implementation does not allow for any freeing. Implement me! */
  
  struct node *curr = ptr - 16;
  //printf("\nRunning free\n");

  if(head == 0) {
	  curr->next = 0;
  }
  else {
	  curr->next = head;
  }
	head = curr;
	//printf("head: 0x%x should equal curr: 0x%x\n", head, curr);
}
