#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef long long ll;
ll arr[(int)1e5+5];
int length = 0;

int cmp(const void* a, const void* b) {
  if(*(long long*)a - *(long long*)b < 0) return 1;
  if(*(long long*)a - *(long long*)b == 0) return 0;
  if(*(long long*)a - *(long long*)b > 0) return -1;
  return 48763;
}

int main() {
  int M;
  scanf("%d", &M);
  while (M--) {
    int t;
    ll k;
    scanf("%d%lld", &t, &k);
    assert(t == 1 || t == 3 || t == 4);
    if (t == 3) arr[length++] = k;
    if (t == 4) {
      for (int i = 0; i < length; i++) {
        if (arr[i] == k) {
          length--;
          for (; i < length; i++) arr[i] = arr[i+1];
        }
      }
    }
    if (t == 1) {
      qsort(arr, length, sizeof(long long), cmp);
      if (!length || arr[0] < k) printf("-1");
      for (int i = 0; i < length && arr[i] >= k; i++) printf("%lld ", arr[i]);
      printf("\n");
    }
  }
  return 0;
}
