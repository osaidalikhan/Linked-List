#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;


Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void sortedInsert(Node** head, int data) {
    Node* new_node = newNode(data);
    if (*head == NULL || (*head)->data >= new_node->data) {

        new_node->next = *head;
        *head = new_node;
    } else {

        Node* current = *head;
        while (current->next != NULL && current->next->data < new_node->data) {
            current = current->next;
        }
 
        new_node->next = current->next;
        current->next = new_node;
    }
}

float getMedian(Node* head, int count) {
    if (!head) return 0;

    Node* current = head;
    if (count % 2 != 0) {

        int i = 0;
        while (i < count / 2) {
            current = current->next;
            i++;
        }
        return current->data;
    } else {

        int i = 0;
        while (i < (count / 2) - 1) {
            current = current->next;
            i++;
        }
        return (current->data + current->next->data) / 2.0;
    }
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    FILE* file;
    file = fopen("Test02.txt", "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    Node* head = NULL;
    int num, count = 0;

    while (fscanf(file, "%d", &num) != EOF) {

        sortedInsert(&head, num);
        count++;
       
        printf("%d Median : %0.1f\n", num, getMedian(head, count));
    }

    fclose(file);
    freeList(head);

    return 0;
}

