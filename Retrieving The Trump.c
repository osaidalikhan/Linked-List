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

void addNode(Node** head, int data) {
    Node* temp = *head;
    Node* newNode = createNode(data);

        if (!(*head)) {
        *head = newNode;
        return;
    }

       while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void deleteNode(Node** head) {
    if (!(*head)) return;

        if (!(*head)->next) {
        free(*head);
        *head = NULL;
        return;
    }

    Node* prev = NULL;
    Node* temp = *head;
    while (temp->next) {
        prev = temp;
        temp = temp->next;
    }
    free(temp);
    prev->next = NULL;
}

void getTrump(Node* head) {
    if (!head) {
        printf("No customer!\n");
        return;
    }

    Node* slow = head;
    Node* fast = head;
    Node* prevSlow = NULL;

        while (fast && fast->next) {
        prevSlow = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

  
    if (!fast) {
        printf("Lucky Winners: %d and %d\n", prevSlow->data, slow->data);
    } else {
        printf("Lucky Winner: %d\n", slow->data);
    }
}

int main() {
   
    FILE* file = fopen("Test01.txt", "r");
    if (!file) {
        printf("Error opening the file!\n");
        return 1;
    }

    Node* head = NULL;
    char command[10];
    int number;

        while (fscanf(file, "%s", command) != EOF) {
        if (strcmp(command, "ADD") == 0) {
            fscanf(file, "%d", &number);
            addNode(&head, number);
        } else if (strcmp(command, "DELETE") == 0) {
            deleteNode(&head);
        } else if (strcmp(command, "END") == 0) {
            break;
        }
    }

    fclose(file);

    getTrump(head);


    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

