#ifndef BOOK_H
#define BOOK_H

typedef struct Book {
    int id;
    char title[100];
    char author[100];
    char category[50];
} Book;

void print_book(Book *book);

#endif

#include <stdio.h>
#include <stdlib.h>
#include "book.h"
#define MAX 100

typedef struct Stack {
    Book *books[MAX];
    int top;
} Stack;

void init_stack(Stack *stack) {
    stack->top = -1;
}

void push(Stack *stack, Book *book) {
    if (stack->top < MAX - 1) {
        stack->books[++stack->top] = book;
    }
}

Book* pop(Stack *stack) {
    if (stack->top >= 0) {
        return stack->books[stack->top--];
    }
    return NULL;
}

void display_stack(Stack *stack) {
    for (int i = stack->top; i >= 0; i--) {
        print_book(stack->books[i]);
    }
}

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE 100

typedef struct Queue {
    Book *queue[MAX_QUEUE];
    int front, rear;
} Queue;

void init_queue(Queue *q) {
    q->front = q->rear = -1;
}

void enqueue(Queue *q, Book *book) {
    if (q->rear < MAX_QUEUE - 1) {
        q->queue[++q->rear] = book;
        if (q->front == -1) q->front = 0;
    }
}

Book* dequeue(Queue *q) {
    if (q->front <= q->rear && q->front != -1) {
        Book *book = q->queue[q->front++];
        if (q->front > q->rear) q->front = q->rear = -1;
        return book;
    }
    return NULL;
}

void display_queue(Queue *q) {
    for (int i = q->front; i <= q->rear; i++) {
        print_book(q->queue[i]);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include "book.h"

typedef struct Node {
    Book book;
    struct Node *next;
} Node;

Node* create_node(Book book) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->book = book;
    new_node->next = NULL;
    return new_node;
}

void append(Node **head, Book book) {
    Node *new_node = create_node(book);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void display_list(Node *head) {
    while (head != NULL) {
        print_book(&head->book);
        head = head->next;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include "book.h"

typedef struct TreeNode {
    char category[50];
    Book books[MAX];
    int book_count;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* create_node(const char *category) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(node->category, category);
    node->book_count = 0;
    node->left = node->right = NULL;
    return node;
}

void add_book(TreeNode *node, Book book) {
    node->books[node->book_count++] = book;
}

void display_books(TreeNode *node) {
    for (int i = 0; i < node->book_count; i++) {
        print_book(&node->books[i]);
    }
}

#include <stdio.h>
#include "book.h"

void print_book(Book *book) {
    printf("%d - %s by %s (%s)\n", book->id, book->title, book->author, book->category);
}
