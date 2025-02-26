#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

// 노드 구조체
typedef struct ListNode {
    char data[4];
    struct ListNode* link;
} listNode;

// 원형 연결 리스트 구조체
typedef struct {
    listNode* head;
} linkedList_h;

// 함수 선언
linkedList_h* createLinkedList_h(void);
void printList(linkedList_h* CL);
void insertFirstNode(linkedList_h* CL, char* x);
void insertMiddleNode(linkedList_h* CL, listNode* pre, char* x);
void deleteNode(linkedList_h* CL, listNode* old);
listNode* searchNode(linkedList_h* CL, char* x);
void freeList(linkedList_h* CL);

// 원형 연결 리스트 생성
linkedList_h* createLinkedList_h(void) {
    linkedList_h* CL = (linkedList_h*)malloc(sizeof(linkedList_h));
    if (CL == NULL) { // 🚨 메모리 할당 실패 체크
        printf("메모리 할당 실패!\n");
        exit(1);
    }
    CL->head = NULL;
    return CL;
}

// 원형 연결 리스트 출력
void printList(linkedList_h* CL) {
    if (CL->head == NULL) {
        printf("CL = ()\n");
        return;
    }
    
    listNode* p = CL->head;
    printf("CL = (");
    
    do {
        printf("%s", p->data);
        p = p->link;
        if (p != CL->head) printf(", ");
    } while (p != CL->head);
    
    printf(")\n");
}

// 첫 번째 노드 삽입
void insertFirstNode(linkedList_h* CL, char* x) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    if (newNode == NULL) { // 🚨 메모리 할당 실패 체크
        printf("메모리 할당 실패!\n");
        exit(1);
    }

    strcpy(newNode->data, x);
    if (CL->head == NULL) {
        CL->head = newNode;
        newNode->link = newNode;
    } else {
        listNode* temp = CL->head;
        while (temp->link != CL->head)
            temp = temp->link;
        newNode->link = CL->head;
        temp->link = newNode;
        CL->head = newNode;
    }
}

// 중간 노드 삽입
void insertMiddleNode(linkedList_h* CL, listNode* pre, char* x) {
    if (pre == NULL) { // 🚨 NULL 체크
        printf("삽입할 위치를 찾을 수 없습니다.\n");
        return;
    }

    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    if (newNode == NULL) { // 🚨 메모리 할당 실패 체크
        printf("메모리 할당 실패!\n");
        exit(1);
    }

    strcpy(newNode->data, x);
    newNode->link = pre->link;
    pre->link = newNode;
}

// 노드 삭제
void deleteNode(linkedList_h* CL, listNode* old) {
    if (CL->head == NULL || old == NULL) return; // 🚨 NULL 체크

    if (CL->head->link == CL->head) { // 🚨 노드가 하나만 있는 경우
        free(CL->head);
        CL->head = NULL;
        return;
    }

    listNode* pre = CL->head;
    while (pre->link != old) {
        pre = pre->link;
        if (pre == CL->head) { // 🚨 old가 리스트에 없으면 종료
            printf("삭제할 노드를 찾을 수 없습니다.\n");
            return;
        }
    }

    pre->link = old->link;
    if (old == CL->head) // 🚨 삭제할 노드가 head인 경우 갱신
        CL->head = old->link;

    free(old);
}

// 노드 검색
listNode* searchNode(linkedList_h* CL, char* x) {
    if (CL->head == NULL) return NULL;

    listNode* temp = CL->head;
    do {
        if (strcmp(temp->data, x) == 0)
            return temp;
        temp = temp->link;
    } while (temp != CL->head);

    return NULL;
}

// 원형 연결 리스트 메모리 해제
void freeList(linkedList_h* CL) {
    if (CL->head == NULL) return;

    listNode* temp = CL->head;
    listNode* nextNode;

    do {
        nextNode = temp->link;
        free(temp);
        temp = nextNode;
    } while (temp != CL->head);

    free(CL);
}

// 메인 함수
int main() {
    linkedList_h* CL;
    listNode* p;

    CL = createLinkedList_h();
    printf("(1) 원형 연결 리스트 생성하기! \n");
    printList(CL);
    
    printf("\n(2) 원형 연결 리스트 [월] 삽입하기! \n");
    insertFirstNode(CL, "월");
    printList(CL);
    
    printf("\n(3) 원형 연결 리스트 [월] 노드 뒤에 [수] 삽입하기! \n");
    p = searchNode(CL, "월"); 
    if (p) insertMiddleNode(CL, p, "수"); // 🚨 NULL 체크 추가
    printList(CL);

    printf("\n(4) 원형 연결 리스트 [수] 노드 뒤에 [금] 삽입하기! \n");
    p = searchNode(CL, "수"); 
    if (p) insertMiddleNode(CL, p, "금"); // 🚨 NULL 체크 추가
    printList(CL);

    printf("\n(5) 원형 연결 리스트 [수] 노드 삭제하기! \n");
    p = searchNode(CL, "수"); 
    if (p) deleteNode(CL, p); // 🚨 NULL 체크 추가
    printList(CL);

    // 프로그램 종료 전에 메모리 해제
    freeList(CL);

    getchar();
    return 0;
}
