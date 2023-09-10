#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* insertEnd(Node* head, int data) {
    if(!head) {
        return createNode(data);
    }
    
    Node* temp = head;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = createNode(data);
    return head;
}

int findThirdLast(Node* head) {
    if(!head || !head->next || !head->next->next) {
        return -1;          
                               // If nodes less than 3 , return -1
    }

    Node* first = head;
    Node* second = head->next;
    Node* third = head->next->next;

    while(third->next) {
        first = first->next;
        second = second->next;
        third = third->next;
    }
     return first->data;
}

int main() {
    Node* head = NULL;
    FILE* file = fopen("Test01.txt", "r");

    if (!file) {
        printf("Unable to open file!\n");
        return -1;
    }
    int data;
    while(fscanf(file, "%d", &data) != EOF) {
        head = insertEnd(head, data);
    }

    fclose(file);
    int thirdLast = findThirdLast(head);
    if(thirdLast != -1) {
        printf("The third last element is: %d\n", thirdLast);
    } else {
        printf("The linked list has less than 3 nodes.\n");
    }

        while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

