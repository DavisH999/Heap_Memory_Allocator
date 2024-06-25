#define _GNU_SOURCE
#include "alloc.h"
// IN C, the lifetime of any global variable is entire runtime of the program!

void coalesce(struct header *ptr);
static struct allocinfo allocinf = {0, 0, 0, 0};
static enum algs fitAlg;
static int heapCellingLimit;
static uint64_t currentHeapSize = 0;
static void *initialPB = NULL;
struct header *freeHeaderList = NULL;

void updateFreeSize() {
  // compute the sum of all free chunk size in the free list and
  // update the allocinf object.  WHEN TO CALL THIS???????????
  struct header *currentNode = freeHeaderList;
  allocinf.free_size = 0;
  while (currentNode != NULL) {
    allocinf.free_size += (currentNode->size - sizeof(struct header));
    currentNode = currentNode->next;
  }
}
void updateFreeChunks() {
  struct header *currentNode = freeHeaderList;
  allocinf.free_chunks = 0;
  while (currentNode != NULL) {
    allocinf.free_chunks += 1;
    currentNode = currentNode->next;
  }
}
void updateLargestFreeChunkSize() {
  struct header *currentNode = freeHeaderList;
  if (currentNode == NULL) {
    allocinf.largest_free_chunk_size = 0;
    return; // OK???
  }
  allocinf.largest_free_chunk_size = currentNode->size;
  while (currentNode != NULL) {
    if (currentNode->size > allocinf.largest_free_chunk_size) {
      allocinf.largest_free_chunk_size = currentNode->size;
    }
    currentNode = currentNode->next;
  }
}
void updateSmallestFreeChunkSize() {
  struct header *currentNode = freeHeaderList;
  if (currentNode == NULL) {
    allocinf.smallest_free_chunk_size = 0;
    return; // OK???
  }
  allocinf.smallest_free_chunk_size = currentNode->size;
  while (currentNode != NULL) {
    if (currentNode->size < allocinf.smallest_free_chunk_size) {
      allocinf.smallest_free_chunk_size = currentNode->size;
    }
    currentNode = currentNode->next;
  }
}
void updateAllocinf() {
  updateFreeSize();
  updateFreeChunks();
  updateLargestFreeChunkSize();
  updateSmallestFreeChunkSize();
}
void insertFreeHeaderNodeAtFront(struct header *freeHeaderNode) {
  assert(freeHeaderNode != NULL);
  freeHeaderNode->next = freeHeaderList;
  freeHeaderList = freeHeaderNode;
}
void removeFreeHeaderNodeFromList(struct header *freeHeaderNode) {
  if (freeHeaderNode == NULL || freeHeaderList == NULL) {
    return;
  }
  // check if we remove the first node case
  if (freeHeaderNode == freeHeaderList) {
    freeHeaderList = freeHeaderNode->next;
    return;
  }

  struct header *previousNode = freeHeaderList;
  struct header *currentNode = freeHeaderList->next;
  while (currentNode != NULL) {
    if (freeHeaderNode == currentNode) {
      previousNode->next = currentNode->next;
      break;
    }
    previousNode = currentNode;
    currentNode = currentNode->next;
  }
}

// assert the node have enough space, pls check before use.
// RETURN USEABLE ADDRESS.
void *spiltNode(struct header *node, int byteSize) {
  assert(node != NULL);
  uint64_t requiredByteSize = byteSize + sizeof(struct header);
  uint64_t remainingSizeAfterSpilt = node->size - requiredByteSize;
  if (remainingSizeAfterSpilt > sizeof(struct header)) {
    // dospilt
    // update node FIXME???? must do?
    node->size = requiredByteSize;
    // insert splited newNode into the free list
    void *newHeapPtr = (char *)node + requiredByteSize;
    struct header *newNode = (struct header *)newHeapPtr;
    newNode->size = remainingSizeAfterSpilt; // FIXME: already include header
                                             // like prof said, right here?
    newNode->next = NULL;
    insertFreeHeaderNodeAtFront(newNode);
  }
  // FIXME: if splilt or not, we both need to remove the free node?
  removeFreeHeaderNodeFromList(node);
  // update allocinfo
  updateAllocinf();
  return (void *)(node + 1);
}

void *alloc(int byteSize) {
  // first run alloc
  uint64_t requiredByteSize = byteSize + sizeof(struct header);
  if (currentHeapSize == 0) {
    // check limit
    // create new node with sbrk(), size id incr, next is null.
    // insert node
    if (currentHeapSize + INCREMENT > heapCellingLimit) {
      updateAllocinf();
      return NULL;
    }
    initialPB = sbrk(0);
    void *newHeapPtr = sbrk(INCREMENT);
    if (newHeapPtr == (void *)-1) {
      updateAllocinf();
      return NULL;
    }
    // initialPB = newHeapPtr;
    // update currentHeapSize
    currentHeapSize += INCREMENT;
    // create a header node
    // struct header *newNode = (struct header *)newHeapPtr;
    struct header *newNode = (struct header *)initialPB;
    newNode->size = INCREMENT;
    newNode->next = NULL;
    insertFreeHeaderNodeAtFront(newNode);
  }
  // assume we have a node
  bool hasEnoughSpace = false;
  struct header *currentNodeForChecking = freeHeaderList;
  while (currentNodeForChecking != NULL) {
    if (currentNodeForChecking->size >= requiredByteSize) {
      hasEnoughSpace = true;
      break;
    }
    currentNodeForChecking = currentNodeForChecking->next;
  }
  if (hasEnoughSpace == true) {
    struct header *fittestNode = NULL;
    if (fitAlg == FIRST_FIT) {
      // FIXME:
      struct header *currentNode = freeHeaderList;
      while (currentNode != NULL) {
        if (currentNode->size >= requiredByteSize) {
          // if we found, we can break since no need to keep traversing.
          fittestNode = currentNode;
          break;
        } else {
          currentNode = currentNode->next;
        }
      }
    } else if (fitAlg == BEST_FIT) {
      // Find minDiff Node
      // FIXME:
      struct header *currentNode = freeHeaderList;
      uint64_t minDiff = UINT64_MAX;
      while (currentNode != NULL) {
        if (currentNode->size >= requiredByteSize) {
          // FIXME This diff is ok, right?
          uint64_t diff = currentNode->size - requiredByteSize;
          if (diff < minDiff) {
            minDiff = diff;
            fittestNode = currentNode;
          }
        }
        currentNode = currentNode->next;
      }
    } else if (fitAlg == WORST_FIT) {
      // find maxDiff Node
      // FIXME:
      struct header *currentNode = freeHeaderList;
      uint64_t maxDiff = 0;
      while (currentNode != NULL) {
        if (currentNode->size >= requiredByteSize) {
          uint64_t diff = currentNode->size - requiredByteSize;
          if (diff > maxDiff) {
            maxDiff = diff;
            fittestNode = currentNode;
          }
        }
        currentNode = currentNode->next;
      }
    } else {
      assert(false);
    }
    // check before spilt
    assert(hasEnoughSpace);
    assert(fittestNode != NULL);
    assert(fittestNode->size >= requiredByteSize);
    void *ptrToUserUseableMemory = spiltNode(fittestNode, byteSize);
    updateAllocinf();
    return ptrToUserUseableMemory;
  } else if (hasEnoughSpace == false) {
    // no enough space, use sbrk()
    // TODO: use sbrk again and again if current heap < requried size, if in
    // loop we reached the heaplimit, then we return null, give up.
    void *newHeapPtr = NULL;
    while (true) {
      if (currentHeapSize + INCREMENT > heapCellingLimit) {
        updateAllocinf();
        return NULL;
      }
      newHeapPtr = sbrk(INCREMENT);
      if (newHeapPtr == (void *)-1) {
        updateAllocinf();
        return NULL;
      }
      currentHeapSize += INCREMENT;

      assert(newHeapPtr != NULL);
      struct header *newNode = (struct header *)newHeapPtr;
      newNode->size = INCREMENT;
      newNode->next = NULL;
      insertFreeHeaderNodeAtFront(newNode);
      coalesce(newNode);
      // FIXME: do we need spilt node here?
      if (newNode->size >= requiredByteSize) {
        void *ptrToUserUseableMemory = spiltNode(newNode, byteSize);
        updateAllocinf();
        return ptrToUserUseableMemory;
      }
    }
  } else {
    assert(false);
    return NULL;
  }
}

void coalesce(struct header *freedNode) {
  if (freeHeaderList == NULL) {
    return;
  }
  struct header *currentNode = freeHeaderList->next;

  while (currentNode != NULL) {
    char *ptrAfterCurrentChunkEnd = (char *)currentNode + currentNode->size;
    // struct header *nextChunk = currentNode->next;
    char *ptrFreedNodeStart = (char *)freedNode;
    if (ptrAfterCurrentChunkEnd == ptrFreedNodeStart) {
      currentNode->size = freedNode->size + currentNode->size;
      if (currentNode != freeHeaderList->next) {
        insertFreeHeaderNodeAtFront(currentNode);
      } else {
        currentNode->next = freeHeaderList->next->next;
        freeHeaderList = currentNode;
      }
    } else {
      currentNode = currentNode->next;
    }
  }
}
void dealloc(void *ptr) {
  if (ptr == NULL)
    return;
  struct header *nodeToFree = (struct header *)ptr - 1;
  insertFreeHeaderNodeAtFront(nodeToFree);
  coalesce(nodeToFree);
  updateAllocinf();
}

void allocopt(enum algs alg, int limitSize) {
  // doing initializing here
  fitAlg = alg;
  heapCellingLimit = limitSize;
  allocinf = (struct allocinfo){0, 0, 0, 0};
  currentHeapSize = 0;
  freeHeaderList = NULL;
  brk(initialPB);
};

struct allocinfo allocinfo() {
  updateAllocinf();
  return allocinf;
}
