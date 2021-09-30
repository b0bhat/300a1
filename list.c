#include "list.h"
#include <stdbool.h>
#include <stdio.h>

static Node node[LIST_MAX_NUM_NODES];
static List list[LIST_MAX_NUM_HEADS];
static int nodes= 0;

List* List_create() {
  List *newlist = NULL;
  for (int i = 0; i < LIST_MAX_NUM_HEADS; i++) {
    if (list[i].used == false) {
    	//printf("\n %i \n", i);
    	list[i].used = true;
      	newlist = &list[i];
    	newlist->cur = NULL;
    	newlist->head = NULL;
    	newlist->end = NULL;
    	newlist->bound = LIST_OOB_START;
    	newlist->num = 0;
      break;
    }
  } return newlist;
}

// Returns the number of items in pList.
int List_count(List* pList) {
  return pList->num;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList) {
  if (pList->head == NULL) {
    pList->cur = NULL;
    return NULL;
  } pList->cur = pList->head;
  return pList->head->data;
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_last(List* pList) {
  if (pList->end == NULL) {
    pList->cur = NULL;
    return NULL;
  } pList->cur = pList->end;
  return pList->end->data;
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer
// is returned and the current item is set to be beyond end of pList.
void* List_next(List* pList) {
  if (pList->head == NULL) return NULL;
  //printf("\ncur: %i end: %i \n",pList->cur->data, pList->end->data);
  if (pList->cur == pList->end) {;
    pList->cur = NULL;
    pList->bound = LIST_OOB_END;
    return NULL;
  } pList->cur = pList->cur->next;
  //pList->bound = 2;
  return pList->cur->data;
}

// Backs up pList's current item by one, and returns a pointer to the new current item.
// If this operation backs up the current item beyond the start of the pList, a NULL pointer
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList){
  if (pList->head == NULL) return NULL;
  if (pList->cur == pList->head) {
    pList->cur = NULL;
    pList->bound = LIST_OOB_START;
    return NULL;
  } pList->cur = pList->cur->prev;
  //pList->bound = 2;
  return pList->cur->data;
}

// Returns a pointer to the current item in pList.
void* List_curr(List* pList) {
  if (pList->cur != NULL) return pList->cur->data;
  return NULL;
}

// Adds the new item to pList directly after the current item, and makes item the current item.
// If the current pointer is before the start of the pList, the item is added at the start. If
// the current pointer is beyond the end of the pList, the item is added at the end.
// Returns 0 on success, -1 on failure.
int List_insert_after(List* pList, void* pItem) {
  if (nodes > LIST_MAX_NUM_NODES-1) return -1;
  Node *temp = NULL;
  for (int i = 0; i < LIST_MAX_NUM_NODES; i++) {
    if (node[i].used == false) {
      node[i].data = pItem;
      
      node[i].used = true;
      node[i].pos = i;
      temp = &node[i];
      nodes++;
      break;
    }
  } if (pList->head == NULL) {
    pList->head = temp;
    pList->end = temp;
    temp->next = NULL;
    temp->prev = NULL;
  } if (pList->bound == LIST_OOB_START) {
    temp->next = pList->head;
    temp->prev = NULL;
    pList->head->prev = temp;
    pList->head = temp;
  } else if ((pList->bound == LIST_OOB_END) || pList->cur == pList->end) {
    temp->prev = pList->end;
    temp->next = NULL;
    pList->end->next = temp;
    pList->end = temp;
  } else {
    temp->next = pList->cur->next;
    temp->prev = pList->cur;
    pList->cur->next->prev = temp;
    pList->cur->next = temp;
  }
  pList->cur = temp;
  //pList->bound = 2;
  pList->num++;
  return 0;
}

// Adds item to pList directly before the current item, and makes the new item the current one.
// If the current pointer is before the start of the pList, the item is added at the start.
// If the current pointer is beyond the end of the pList, the item is added at the end.
// Returns 0 on success, -1 on failure.
int List_insert_before(List* pList, void* pItem) {
  if (nodes >= LIST_MAX_NUM_NODES) return -1;
  //printf("\n NODES: %i\n", nodes);
  Node *temp = NULL;
  for (int i = 0; i < LIST_MAX_NUM_NODES; i++) {
    if (node[i].used == false) {
      node[i].data = pItem;
      //printf("\nDATA: %i \n", pItem);
      node[i].used = true;
      node[i].pos = i;
      temp = &node[i];
      nodes++;
      //printf("success: %i\n", i);
      break;
    }
  } if (pList->head == NULL) {
    pList->head = temp;
    pList->end = temp;
    temp->next = NULL;
    temp->prev = NULL;
  } else if (pList->bound == LIST_OOB_START) {
    temp->next = pList->head;
    temp->prev = NULL;
    pList->head->prev = temp;
    pList->head = temp;
  } else if ((pList->bound == LIST_OOB_END) || pList->cur == pList->end) {
    temp->prev = pList->end;
    temp->next = NULL;
    pList->end->next = temp;
    pList->end = temp;
  } else {
    temp->next = pList->cur;
    temp->prev = pList->cur->prev;
    pList->cur->prev->next = temp;
    pList->cur->prev = temp;
  }
  pList->cur = temp;
  //pList->bound = 2;
  pList->num++;
  return 0;
}

// Adds item to the end of pList, and makes the new item the current one.
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem) {
  if (nodes > LIST_MAX_NUM_NODES-1) return -1;
  Node *temp = NULL;
  for (int i = 0; i < LIST_MAX_NUM_NODES; i++) {
    if (node[i].used == false) {
      node[i].data = pItem;
      node[i].used = true;
      node[i].pos = i;
      temp = &node[i];
      nodes++;
      break;
    }
  } if (pList->head == NULL) {
    pList->head = temp;
    pList->end = temp;
    temp->next = NULL;
    temp->prev = NULL;
  } else {
    temp->prev = pList->end;
    temp->next = NULL;
    pList->end->next = temp;
    pList->end = temp;
  } pList->num++;
  pList->cur = temp;
  //pList->bound = 2;
  return 0;
}

// Adds item to the front of pList, and makes the new item the current one.
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem) {
  if (nodes > LIST_MAX_NUM_NODES-1) return -1;
  Node *temp = NULL;
  for (int i = 0; i < LIST_MAX_NUM_NODES; i++) {
    if (node[i].used == false) {
      node[i].data = pItem;
      node[i].used = true;
      node[i].pos = i;
      temp = &node[i];
      nodes++;
      break;
    }
  } if (pList->head == NULL) {
    pList->head = temp;
    pList->end = temp;
    temp->next = NULL;
    temp->prev = NULL;
  } else {
    temp->next = pList->head;
    temp->prev = NULL;
    pList->head->prev = temp;
    pList->head = temp;
  } pList->num++;
  pList->cur = temp;
  //pList->bound = 2;
  return 0;
}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList) {
  if ((pList->cur == NULL) || (pList->head == NULL)) return NULL;
  Node *new = pList->cur->next;
  void* data = pList->cur->data;
  if (pList->head == pList->end) {
    pList->end = NULL;
    pList->head = NULL;
    pList->bound = LIST_OOB_START;
  } else if (pList->cur == pList->head) {
    pList->cur->next->prev = NULL;
    pList->head = pList->cur->next;
  } else if (pList->cur == pList->end) {
    pList->cur->prev->next = NULL;
    pList->end = pList->cur->prev;
  } else {
    pList->cur->next->prev = pList->cur->prev;
    pList->cur->prev->next = pList->cur->next;
  }
  pList->cur->used = false;
  /*pList->cur->data = NULL; pList->cur->next = NULL; pList->cur->prev = NULL; pList->cur->pos = NULL;*/
  pList->cur = new;
  pList->num--;
  nodes--;
  //printf("num: %i Nodes: %i\n", pList->num, nodes);
  return data;
}

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList) {
  if (pList->head == NULL) return NULL;
  //printf("\nremove: %i \n", pList->end->data);
  void* data = pList->end->data;
  pList->end->used = false;
  if (pList->head == pList->end) {
    pList->head = NULL;
    pList->end = NULL;
    pList->cur = NULL;
    pList->bound = LIST_OOB_END;
  } else {
    pList->end->prev->next = NULL;
    pList->end = pList->end->prev;
    pList->cur = pList->end;
  } pList->num--;
  nodes--;
  //pList->bound = 2;
  return data;
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1.
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2) {
  pList1->num += pList2->num;
  pList1->end->next = pList2->head;
  pList2->head->prev = pList1->end;
  pList1->end = pList2->end;
  pList2->used = false;
  pList2->cur = NULL;
  pList1->bound = 2;
  return;
}

// Delete pList. pItemFreeFn is a pointer to a routine that frees an item.
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are
// available for future operations.
typedef void (*FREE_FN)(void* pItem);
void List_free(List* pList, FREE_FN pItemFreeFn) {
  while (pList->head != NULL) {
    pList->end->used = false;
    pItemFreeFn(List_trim(pList));
  } pList->used = false;
  nodes = 0;
}

// Search pList, starting at the current item, until the end is reached or a match is found.
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match,
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator.
//
// If a match is found, the current pointer is left at the matched item and the pointer to
// that item is returned. If no match is found, the current pointer is left beyond the end of
// the list and a NULL pointer is returned.
//
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg) {
  Node* temp = pList->cur;
  if (pList->bound == LIST_OOB_START) temp = pList->head;
  while (temp != NULL) {
    if (pComparator(temp->data, pComparisonArg) != 0) {
      pList->cur = temp;
      return temp->data;
    } if (temp == pList->end) break;
    temp = temp->next;
  } pList->cur = NULL;
  pList->bound = LIST_OOB_END;
  return NULL;
}
