#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "list.h"

void FreeFn(void *data) {
  return;
}

void testCreateFree() {
  printf("testCreateFree START\n");
  List* list = List_create();
  assert(list != NULL);
  printf("testCreateFree PASS\n");
  List_free(list, FreeFn);
  return;
}

void testCreateMany() {
  printf("testCreateMany START\n");
  List* list[LIST_MAX_NUM_HEADS];
  for(int i=0; i<LIST_MAX_NUM_HEADS; i++) {
    list[i] = List_create();
    assert(list[i] != NULL);
  } printf("testCreateMany PASS\n");
  for(int i =0; i<LIST_MAX_NUM_HEADS; i++)List_free(list[i], FreeFn);
  return;
}

void testCreateLimit() {
  printf("testCreateLimit START\n");
  List* list[LIST_MAX_NUM_HEADS];
  for(int i=0; i<LIST_MAX_NUM_HEADS; i++) {
    list[i] = List_create();
    assert(list[i] != NULL);
  } List* list2 = List_create();
  assert(list2 == NULL);
  printf("testCreateLimit PASS\n");
  for(int i =0; i<LIST_MAX_NUM_HEADS; i++)List_free(list[i], FreeFn);
  return;
}

void testInsertAfter() {
  printf("testInsertAfter START\n");
  List* list = List_create();
  for(int i = 0; i < LIST_MAX_NUM_HEADS; i++){
    int num = List_insert_after(list, (void *)&i);
    //printf("\n ^num: %i \n", num);
    assert(num == 0);
  } List_free(list, FreeFn);
  printf("testInsertAfter PASS\n");
  return;
}

void testInsertBefore() {
  printf("testInsertBefore START\n");
  List* list = List_create();
  for(int i = 0; i < LIST_MAX_NUM_HEADS; i++){
    int num = List_insert_before(list, (void *)&i);
    //printf("\n ^num: %i \n", num);
    assert(num == 0);
  } List_free(list, FreeFn);
  printf("testInsertBefore PASS\n");
  return;
}

void testCount() {
  printf("testCount START\n");
  List* list = List_create();
  assert (list != NULL);
  for(int i = 0; i < 12; i++){
    int num = List_prepend(list, (void *)&i);
    assert(num == 0);
    assert(List_count(list) == (i+1));
  } List_free(list, FreeFn);
  printf("testCount PASS\n");
  return;
}

void testAppend() {
  printf("testAppend START\n");
  List* list = List_create();
  assert (list != NULL);
  for(int i = 0; i < LIST_MAX_NUM_HEADS; i++){
    int num = List_append(list, (void *)&i);
    //printf("\n ^num: %i \n", num);
    assert(num == 0);
    assert(List_count(list) == (i+1));
  } List_free(list, FreeFn);
  printf("testAppend PASS\n");
  return;
}

void testPrepend() {
  printf("testPrepend START\n");
  List* list = List_create();
  assert (list != NULL);
  for(int i = 0; i < LIST_MAX_NUM_HEADS; i++){
    int num = List_prepend(list, (void *)&i);
    //printf("\n ^num: %i \n", num);
    assert(num == 0);
    assert(List_count(list) == (i+1));
  } List_free(list, FreeFn);
  printf("testPrepend PASS\n");
  return;
}

void testFirst() {
  printf("testFirst START\n");
  List* list = List_create();
  assert (list != NULL);
  void* p;
  for(int i = 0; i < 15; i++){
    if (i==0)p = i; //saving value of first
  //  printf("pos: %i", i);
    int num = List_append(list, (void*)i);
    assert(num == 0);
    assert(List_count(list) == (i+1));
  } void* cur = List_first(list); //getting first item
  //printf("pos: %i p: %i \n", cur, p);
  assert(cur == p); //comparison of item and saved value
  List_free(list, FreeFn);
  printf("testFirst PASS\n");
  return;
}

void testLast() {
  printf("testLast START\n");
  List* list = List_create();
  assert (list != NULL);
  void* p = NULL;
  for(int i = 0; i < 15; i++){
    if (i==14)p = i; //saving value of last
    //printf("pos: %i", i);
    int num = List_append(list, (void*)i);
    assert(num == 0);
    assert(List_count(list) == (i+1));
  } void* cur = List_last(list); //getting last item
  //printf("pos: %i p: %i \n", cur, p);
  assert(cur == p);//comparison of item and saved value
  List_free(list, FreeFn);
  printf("testLast PASS\n");
  return;
}

void testNext() {
  printf("testNext START\n");
  List* list = List_create();
  assert (list != NULL);
  void* p;
  for(int i = 0; i < 15; i++){
    if (i==13)p = i;
    //printf("pos: %i", i);
    int num = List_prepend(list, (void*)i);
    assert(num == 0);
    assert(List_count(list) == (i+1));
  } void* cur = List_next(list);
  //printf("pos: %i p: %i \n", cur, p);
  assert(cur == p);
  List_free(list, FreeFn);
  printf("testNext PASS\n");
  return;
}

void testPrev() {
  printf("testPrev START\n");
  List* list = List_create();
  assert (list != NULL);
  void* p;
  for(int i = 0; i < 15; i++){
    if (i==13)p = i;
    int num = List_append(list, (void*)i);
    assert(num == 0);
    assert(List_count(list) == (i+1));
  } void* cur = List_prev(list);
  assert(cur == p);
  //printf("pos: %i p: %i \n", cur, p);
  List_free(list, FreeFn);
  printf("testPrev PASS\n");
  return;
}

void testTrim() {
  printf("testTrim START\n");
  List* list = List_create();
  assert (list != NULL);
  void* p;
  for(int i = 0; i < 5; i++){
    if (i==3)p = i;
    int num = List_append(list, (void*)i);
    assert(num == 0);
    assert(List_count(list) == (i+1));
  } List_trim(list);
  assert(List_curr(list) == p);
  //printf("pos: %i p: %i \n", List_curr(list), p);
  List_free(list, FreeFn);
  printf("testTrim PASS\n");
  return;
}

void testRemove() {
  printf("testRemove START\n");
  List* list = List_create();
  assert (list != NULL);
  void* p;
  for(int i = 0; i < 5; i++){
    if (i==4)p = i;
    int num = List_append(list, (void*)i);
    assert(num == 0);
    assert(List_count(list) == (i+1));
  }
  List_prev(list);
  List_remove(list);
  assert(List_curr(list) == p);
  //printf("pos: %i p: %i \n", List_curr(list), p);
  List_free(list, FreeFn);
  printf("testRemove PASS\n");
  return;
}

void testConcat() {
  printf("testConcat START\n");
  List* list1 = List_create();
  List* list2 = List_create();
  assert(list1 != NULL);
  assert(list2 != NULL);
  for(int i = 0; i < 20; i++) {
      List_append(list1, (void *)i);
  } for(int i = 20; i < 30; i++) {
      int num = List_append(list2, (void *)i);
      assert(num == 0);
  } List_concat(list1, list2);
  assert(List_count(list1) == 30);
  int p = List_last(list1);
  //printf("p: %i \n", p);
  assert(p == 29);
  List_free(list1, FreeFn);
  List_free(list2, FreeFn);
  printf("testConcat PASS\n");
  return;
}

bool comparator9000(void* data, void* comp) {
  return (data == comp);
}

void testSearchYes() {
  printf("testSearchYes START\n");
  List* list = List_create();
  assert (list != NULL);
  for(int i = 0; i < 5; i++){
    int num = List_append(list, (void*)i);
    assert(num == 0);
    assert(List_count(list) == (i+1));
  }
  int search = List_search(list, comparator9000, (void*)2);
  //printf("search key: %i, search answer and pos: %i\n",search, 2);
  assert(search == 2);
  List_free(list, FreeFn);
  printf("testSearchYes PASS\n");
  return;
}

void testSearchNo() {
  printf("testSearchNo START\n");
  List* list = List_create();
  assert (list != NULL);
  for(int i = 0; i < 5; i++){
    int num = List_append(list, (void*)i);
    assert(num == 0);
    assert(List_count(list) == (i+1));
  }
  int search = List_search(list, comparator9000, (void*)6);
  //printf("search key: %i, search answer and pos: %i\n",search, NULL);
  assert(search == NULL);
  List_free(list, FreeFn);
  printf("testSearchNo PASS\n");
  return;
}

int main() {
  printf("\n\n -w FOR IGNORING TYPE ERRORS IN TESTING ONLY \n\n");
  testCreateFree();
  testCreateMany();
  testCreateLimit();
  testInsertAfter();
  testInsertBefore();
  testCount();
  testAppend();
  testPrepend();

  testFirst();
  testLast();
  testNext();
  testPrev();

  testTrim();
  testRemove();
  testConcat();
  testSearchYes();
  testSearchNo();
}
