#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
 
#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
    int size;
} Queue;
 
void initialize(Queue *queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
}      

bool isEmpty(Queue *queue) {
    return queue->size == 0;
}

bool isFull(Queue *queue) {
    return queue->size == MAX_SIZE;
}

int size(Queue *queue) {
    return queue->size;
}

void enqueue(Queue *queue, int item) {
    if (isFull(queue)) {
        printf ("队列已满，无法入队\n");
        return;
    }
    queue->items[queue->rear] = item;
    queue->rear = (queue->rear +1) % MAX_SIZE;
    queue->size++;
}

int dequeue(Queue *queue) {
    if (isEmpty(queue)) {
        printf ("队列为空， 无法出队\n");
        return-1;
    }
    
    int item = queue->items[queue->front];
    queue->front = (queue->front + 1)%MAX_SIZE;
    queue->size--;
    return item;
}

int front(Queue *queue) {
    if(isEmpty(queue)) {
        printf ("队列为空，无法查看对头\n");
        return -1;
    }
    return queue->items[queue->front];
}

int main() {
    Queue queue;
    initialize(&queue);
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    printf("队头元素； %d\n", front(&queue));
    printf("出队的元素：%d\n", dequeue(&queue));
    printf("队列的大小:%d\n" ,size(&queue));
    printf("队列是否为空：%s\n",isEmpty(&queue) ?"yes" : "no");

    return 0;
}