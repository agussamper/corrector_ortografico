#include "test_queue.h"
#include "queue.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../type_operations/int_func.h"

void test_queue_crear() {
  Queue queue = queue_crear();
  assert(queue_vacia(queue));
  assert(queue_size(queue) == 0);
  queue_destruir(queue, int_destruir);
}

void test_queue_vacia() {
  Queue queue = queue_crear();
  assert(queue_vacia(queue));

  int nums[] = {0, 1, 2, 3};
  queue_enqueue(queue, int_cpy, nums);
  assert(queue_vacia(queue) == 0);

  queue_dequeue(queue, int_destruir);
  assert(queue_vacia(queue));

  for(int i = 0; i < 4; i++)
    queue_enqueue(queue, int_cpy, nums + i);
  
  assert(queue_vacia(queue) == 0);

  queue_destruir(queue, int_destruir);
}

void test_queue_front() {
  Queue queue = queue_crear();
  int nums[] = {0, 1, 2, 3};
  for(int i = 0; i < 4; i++)
    queue_enqueue(queue, int_cpy, nums + i);

  for(int i = 0; i < 4; i++) {
    assert(*(int*)queue_front(queue) == nums[i]);
    queue_dequeue(queue, int_destruir);
  }
  queue_destruir(queue, int_destruir);
}

void test_queue_size() {
  Queue queue = queue_crear();
  assert(queue_size(queue) == 0);
  int nums[] = {0, 1, 2, 3};  
  for(int i = 0; i < 4; i++) {
    queue_enqueue(queue, int_cpy, nums + i);
    assert(queue_size(queue) == i + 1);
  }
  for(int i = 3; i < -1; i--) {
    queue_dequeue(queue, int_destruir);
    assert(queue_size(queue) == i);
  }
  queue_destruir(queue, int_destruir);
}

void test_queue_enqueue() {
  Queue queue = queue_crear();
  int nums[] = {0,1,2,3,4,5,6,7,8,9,10};
  for (int i = 0; i < 11; i++) {
    queue_enqueue(queue, int_cpy, nums + i);
    assert(queue_size(queue) == i + 1);
    if(!queue_vacia(queue)) {
      assert(*(int*)queue_rear(queue) == nums[i]);
      assert(*(int*)queue_front(queue) == nums[0]);
    }
  }
  queue_dequeue(queue, int_destruir);
  queue_dequeue(queue, int_destruir);
  queue_enqueue(queue, int_cpy, nums);
  assert(*(int*)queue_rear(queue) == nums[0]);
  assert(queue_size(queue) == 10);

  queue_destruir(queue, int_destruir);
}

void test_queue_dequeue() {
  Queue q = queue_crear();
  int nums[] = {0,1,2,3,4,5,6,7,8,9,10};
  for (int i = 0; i < 11; i++)
    queue_enqueue(q, int_cpy, nums + i);
  //queue_recorrer(q, int_visit);puts("");
  for(int i = 0; i < 11; i++) { 
    queue_dequeue(q, int_destruir);
    assert(queue_size(q) == 10-i);
    if(!queue_vacia(q)) {
      assert(*(int*)queue_rear(q) == nums[10]);
      assert(*(int*)queue_front(q) == nums[i+1]);
    }
  }
  queue_enqueue(q, int_cpy, nums);
  queue_enqueue(q, int_cpy, nums + 1);
  queue_dequeue(q, int_destruir);
  assert(*(int*)queue_rear(q) == 1);
  assert(*(int*)queue_front(q) == 1);
  assert(queue_size(q) == 1);
  
  queue_dequeue(q, int_destruir);    
  assert((int*)queue_rear(q) == NULL);
  assert((int*)queue_front(q) == NULL);
  assert(queue_size(q) == 0);

  queue_destruir(q, int_destruir);
}

void test_queue() {
  test_queue_crear();
  test_queue_vacia();
  test_queue_front();
  test_queue_size();
  test_queue_enqueue();
  test_queue_dequeue();
}

int main() {
  test_queue();
}