#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

typedef struct Node {
  struct Node *pre, *nxt, *below;
  ll v;
  int level;
} Node;

Node *new_node(ll v, int level) {
  Node *node = (Node *) malloc(sizeof(Node));
  node->v = v;
  node->level = level;
  node->nxt = NULL;
  node->pre = NULL;
  node->below = NULL;
  return node;
}

Node *head;

void modify(ll k, bool insertion) {
  Node *path[64] = {};
  int level[64] = {};
  Node *cur = head;
  for (int i = 1; 1; i++) {
    assert(i<64);
    while (cur->nxt && cur->nxt->v >= k) cur = cur->nxt;
    assert(insertion == 0 || cur->v > k);
    if (cur->v == k) break;
    path[i] = cur;
    level[cur->level] = i;
    if (!cur->level) break;
    else cur = cur->below;
  }
  if (insertion == 1) {
    assert(cur->level == 0);
    int new_level = 0;
    Node *below = new_node(k, new_level);
    below->pre = cur;
    below->nxt = cur->nxt;
    if (below->nxt) below->nxt->pre = below;
    cur->nxt = below;
    while ((k/((ll)1 << (new_level))) & 1) {
      // printf("%lld, %lld\n", k, ((ll)1 << (new_level)));
      // printf("%lld\n", k/((ll)1 << (new_level)));
      // printf("b %d\n", k);
      cur = path[level[++new_level]];
      if (!cur) {
        Node *pre_head = head;
        head = new_node(head->v, head->level+1);
        head->below = pre_head;
        cur = head;
      }
      Node *tmp = new_node(k, new_level);
      tmp->nxt = cur->nxt;
      cur->nxt = tmp;
      tmp->pre = cur;
      if (tmp->nxt) tmp->nxt->pre = tmp;
      assert(cur->level == new_level);
      tmp->below = below;
      below = tmp;
    }
  } else {
    if (cur->v != k) return;
    while (cur) {
      // printf("level: %d\n", cur->level);
      if(cur->pre) cur->pre->nxt = cur->nxt;
      if(cur->nxt) cur->nxt->pre = cur->pre;
      // printf("pre: %lld\n", cur->pre->v);
      cur = cur->below;
    }
  }
}

void slow_get(ll k) {
  Node *cur = head;
  while (cur->level) cur = cur->below;
  cur = cur->nxt;
  if (!cur || cur->v < k) {
    printf("-1\n");
    return;
  }
  while (cur != NULL && k <= cur->v) {
    printf("%lld ", cur->v);
    cur = cur->nxt;
  }
  printf("\n");
}

void fast_get(ll k) {
  Node *cur = head;
  while ((!cur->nxt || cur->nxt->v < k) && cur->below) cur = cur->below;
  cur = cur->nxt;
  if (!cur || cur->v < k) {
    printf("-1\n");
    return;
  }
  printf("%lld", cur->v);
  while(cur) {
    while (cur->nxt && cur->nxt->v >= k) {
      cur = cur->nxt;
      printf(" %lld", cur->v);
    }
    cur = cur->below;
    if(cur) printf(" %lld", cur->v);
  }
  printf("\n");
}

int main() {
  int M;
  scanf("%d", &M);
  head = new_node(LLONG_MAX, 0);
  while (M--) {
    int t;
    ll k;
    scanf("%d%lld", &t, &k);
    if (t == 1) slow_get(k);
    if (t == 2) fast_get(k);
    if (t == 3) modify(k, 1);
    if (t == 4) modify(k, 0);
  }
  return 0;
}
