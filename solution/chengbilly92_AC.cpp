#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef long long ll;

typedef struct ListNode {
  ll val;
  struct ListNode *next;
  struct ListNode *below;
} listnode;

typedef struct SkipList {
  int layer;
  listnode *head[64];
} skiplist;

skiplist s;

void init() {
  s.layer = -1;
  for(int i = 0; i < 64; i++) {
    s.head[i] = NULL;
  }
}

int get_layer(ll n) {
  int layer = 0;
  while((n >> layer) & 1) {
    layer++;
  }
  return layer;
}

void SlowGet(ll k) {
  listnode *node = s.head[0];
  bool flag = false;
  while(node != NULL && k <= node -> val) {
    printf("%lld ", node->val);
    node = node -> next;
    flag = true;
  }
  if(!flag) {
    printf("-1");
  }
  printf("\n");
}

void FastGet(ll k) {
  listnode *node = NULL;
  bool flag = false;
  for(int i = s.layer; i >= 0; i--) {
    if(s.head[i] -> val < k) continue;
    if(node == NULL) {
      node = s.head[i];
    }
    flag = true;
    printf("%lld ", node -> val);
    while(node -> next != NULL && k <= node -> next -> val) {
      node = node -> next;
      printf("%lld ", node -> val);
    }
    if(i > 0) node = node -> below;
  }
  if(!flag) {
    printf("-1");
  }
  printf("\n");
}

void Insert(ll k) {
  int layer = get_layer(k);
  if(s.layer < layer) {
    s.layer = layer;
  }
  listnode *above_node = NULL, *cur_node = NULL;
  for(int i = s.layer; i >= 0; i--) {
    if(s.head[i] == NULL || s.head[i] -> val < k) {
      if(i > layer) continue;
      listnode *node = (listnode*) malloc(sizeof(listnode));
      node -> val = k;
      node -> next = s.head[i];
      node -> below = NULL;
      s.head[i] = node;
      if(above_node != NULL) above_node -> below = node;
      above_node = node;
      continue;
    }
    if(cur_node == NULL) {
      cur_node = s.head[i];
    }
    while(cur_node -> next != NULL && k < cur_node -> next -> val) {
      cur_node = cur_node -> next;
    }
    if(i > layer) {
      cur_node = cur_node -> below;
      continue;
    }
    listnode *node = (listnode*) malloc(sizeof(listnode));
    node -> val = k;
    node -> next = cur_node -> next;
    node -> below = NULL;
    if(above_node != NULL) {
      above_node -> below = node;
    }
    above_node = node;
    cur_node -> next = node;
    if(i > 0) cur_node = cur_node -> below;
  }
}

void Remove(ll k) {
  listnode *node = NULL;
  for(int i = s.layer; i >= 0; i--) {
    if(s.head[i] == NULL || s.head[i] -> val < k) continue;
    if(node == NULL) {
      node = s.head[i];
    }
    while(node -> next != NULL && k < node -> next -> val) {
      node = node -> next;
    }
    if(node == s.head[i] && node -> val == k) {
      s.head[i] = node -> next;
      if(s.head[i] == NULL) s.layer = i - 1;
      node = NULL;
      continue;
    }
    else if(node -> next != NULL && node -> next -> val == k) {
      node -> next = node -> next -> next;
    }
    if(i > 0) node = node -> below;
  }
}

int main() {

  int m;
  scanf("%d", &m);
  init();

  for(int i = 0; i < m; i++) {
    int op;
    ll k;
    scanf("%d%lld", &op, &k);
    if(op == 1) {
      SlowGet(k);
    }
    else if(op == 2) {
      FastGet(k);
    }
    else if(op == 3) {
      Insert(k);
    }
    else {
      Remove(k);
    }
  }
  return 0;
}
