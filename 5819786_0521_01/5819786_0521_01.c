#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
} element;

typedef struct listnode {
    element data;
    struct listnode* link;
} ListNode;

ListNode* insert_first(ListNode* head, element fruit) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = fruit;
    p->link = head;
    return p;
}

ListNode* insert_last(ListNode* head, element fruit) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = fruit;
    p->link = NULL;

    if (head == NULL) {
        return p;
    }
    else {
        ListNode* tail = head;
        while (tail->link != NULL) {
            tail = tail->link;
        }
        tail->link = p;
        return head;
    }
}

ListNode* delete_node(ListNode* h, element x) {
    ListNode* current = h;
    ListNode* pre = NULL;

    while (current != NULL && strcmp(current->data.name, x.name) != 0) {
        pre = current;
        current = current->link;
    }

    if (current == NULL) {
        printf("해당 과일이 없습니다.\n");
        return h;
    }

    if (pre == NULL) {
        h = current->link;
    }
    else {
        pre->link = current->link;
    }

    free(current);
    return h;
}

void print_list(ListNode* h) {
    while (h != NULL) {
        printf("[%s] ", h->data.name);
        h = h->link;
    }
    printf("\n");
}

ListNode* search_list(ListNode* h, element x) {
    ListNode* p = h;

    while (p != NULL) {
        if (strcmp(p->data.name, x.name) == 0) return p;
        p = p->link;
    }
    return NULL;
}

int main() {
    ListNode* head = NULL;
    ListNode* deleted_fruit = NULL;
    element n;
    int choice;

    char* initial_fruits[] = { "Mango","Orange","Apple","Grape","Cherry","Plum","Guava","Raspberry","Banana","Peach" };
    for (int i = 0; i < 10; i++) {
        strcpy(n.name, initial_fruits[i]);
        head = insert_last(head, n);
    }

    while (1) {
        printf("1. 맨 마지막에 과일 추가\n");
        printf("2. 과일 삭제\n");
        printf("3. 삭제된 과일 목록 출력\n");
        printf("4. 종료\n");
        printf("선택하시오 : ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("추가할 과일 이름: ");
            scanf("%s", n.name);
            if (search_list(head, n)) {
                printf("과일 %s가 이미 존재함.\n", n.name);
            }
            else {
                head = insert_last(head, n);
                printf("과일이 추가되었습니다.\n");
            }
            break;
        case 2:
            printf("삭제할 과일 이름: ");
            scanf("%s", n.name);
            ListNode* found = search_list(head, n);
            if (found) {
                head = delete_node(head, n);
                found->link = deleted_fruit;
                deleted_fruit = insert_first(deleted_fruit, n);
            }
            else {
                printf("해당 과일이 없습니다.\n");
            }
            break;
        case 3:
            printf("삭제된 과일 목록: ");
            print_list(deleted_fruit);
            printf("\n");
            break;
        case 4:
            printf("프로그램을 종료합니다.\n");
            exit(0);
        default:
            printf("유효하지 않은 선택입니다!\n");
            break;
        }
    }

    return 0;
}