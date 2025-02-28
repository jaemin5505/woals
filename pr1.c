#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define MAX_QUEUE 100

typedef struct Book {
    int id;
    char title[100];
    char author[100];
    char category[50];
} Book;

void print_book(Book *book) {
    printf("%d - %s by %s (%s)\n", book->id, book->title, book->author, book->category);
}

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

typedef struct TreeNode {
    char category[50];
    Book books[MAX];
    int book_count;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* create_tree_node(const char *category) {
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
int main() {
    Book book1 = {1, "C 프로그래밍", "데니스 리치", "IT"};
    Book book2 = {2, "자료구조", "이지영", "IT"};
    Book book3 = {3, "해리포터", "J.K. 롤링", "문학"};

    printf("=== 도서 목록 ===\n");
    print_book(&book1);
    print_book(&book2);
    print_book(&book3);

    Stack stack;
    init_stack(&stack);
    push(&stack, &book1);
    push(&stack, &book2);
    printf("\n=== 대출 기록 ===\n");
    display_stack(&stack);

    Queue queue;
    init_queue(&queue);
    enqueue(&queue, &book3);
    printf("\n=== 예약 대기열 ===\n");
    display_queue(&queue);

    Node *head = NULL;
    append(&head, book1);
    append(&head, book2);
    append(&head, book3);
    printf("\n=== 도서 목록 (연결 리스트) ===\n");
    display_list(head);

    TreeNode *root = create_tree_node("IT");
    add_book(root, book1);
    add_book(root, book2);
    printf("\n=== 카테고리별 도서 (트리) ===\n");
    display_books(root);

    return 0;
}
