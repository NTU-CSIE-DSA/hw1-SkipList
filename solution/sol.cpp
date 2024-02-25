#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct SkipNode {
    long long key;
    struct SkipNode **next;
} SkipNode;

typedef struct SkipList {
    int max_level;
    int level;
    SkipNode *header;
} SkipList;

SkipNode* createNode(long long key, int level) {
    SkipNode *new_node = (SkipNode*)malloc(sizeof(SkipNode));
    new_node->key = key;
    new_node->next = (SkipNode**)malloc(sizeof(SkipNode*) * (level + 1));
    return new_node;
}

SkipList* createSkipList(int max_level) {
    SkipList *list = (SkipList*)malloc(sizeof(SkipList));
    list->max_level = max_level;
    list->level = 0;
    list->header = createNode(LLONG_MAX, max_level);
    for (int i = 0; i <= max_level; i++) {
        list->header->next[i] = NULL;
    }
    return list;
}

int GetLevel(long long key) {
    int level = 0;
    while (key % 2 == 1) {
        level++;
        key = key / 2;
    }
    return level;
}

void insertNode(SkipList *list, long long key) {
    SkipNode *update[list->max_level + 1];
    SkipNode *current = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (current->next[i] != NULL && key < current->next[i]->key) {
            current = current->next[i];
        }
        update[i] = current;
    }
    current = current->next[0];
    if (current == NULL || current->key != key) {
        int new_level = GetLevel(key);
        if (new_level > list->level) {
            for (int i = list->level + 1; i <= new_level; i++) {
                update[i] = list->header;
            }
            list->level = new_level;
        }
        SkipNode *new_node = createNode(key, new_level);
        for (int i = 0; i <= new_level; i++) {
            new_node->next[i] = update[i]->next[i];
            update[i]->next[i] = new_node;
        }
    }
}

void deleteNode(SkipList *list, long long key) {
    SkipNode *update[list->max_level + 1];
    SkipNode *current = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (current->next[i] != NULL && key < current->next[i]->key) {
            current = current->next[i];
        }
        update[i] = current;
    }
    current = current->next[0];
    if (current != NULL && current->key == key) {
        for (int i = 0; i <= list->level; i++) {
            if (update[i]->next[i] != current) {
                break;
            }
            update[i]->next[i] = current->next[i];
        }
        free(current->next);
        free(current);
        while (list->level > 0 && list->header->next[list->level] == NULL) {
            list->level--;
        }
    }
}

void slow_get(SkipList *list, long long k){ // slow get the first element >= k
    SkipNode *current = list->header->next[0];
    int found = 0;
    while (current != NULL && current->key >= k) {
        printf("%lld ", current->key);
        found = 1;
        current = current->next[0];
    }
    if(found == 0) printf("-1");
    printf("\n");
}

void fast_get(SkipList *list, long long k){ // fast get the first element >= k
    SkipNode *current = list->header;
    int found = 0;
    for (int i = list->level; i >= 0; i--){
        if(current->key != LLONG_MAX) printf("%lld ", current->key);
        while (current->next[i] != NULL && k <= current->next[i]->key) {
            current = current->next[i];
            found = 1;
            printf("%lld ", current->key);
        }
    }
    if(found == 0) printf("-1");
    printf("\n");
}

void freeSkipList(SkipList *list) {
    SkipNode *current = list->header->next[0];
    while (current != NULL) {
        SkipNode *temp = current;
        current = current->next[0];
        free(temp->next);
        free(temp);
    }
    free(list->header->next);
    free(list->header);
    free(list);
}

int main() {
    SkipList *list = createSkipList(64); // 最大層數為64
    int M, t;
    long long k;
    scanf("%d", &M);
    for(int i = 0; i < M; i++){
        scanf("%d%lld", &t, &k);
        if(t == 1) slow_get(list, k);
        else if(t == 2) fast_get(list, k);
        else if(t == 3) insertNode(list, k);
        else deleteNode(list, k);
    }
    freeSkipList(list);
    return 0;
}
