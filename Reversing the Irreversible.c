#include <stdio.h>
#include <stdlib.h>

typedef struct TransactionNode {
    int id;
    int amount;
    struct TransactionNode *next;
} TransactionNode;

TransactionNode* insertTransaction(TransactionNode *head, int id, int amount) {
    TransactionNode *newNode = (TransactionNode*)malloc(sizeof(TransactionNode));
    newNode->id = id;
    newNode->amount = amount;
    newNode->next = head;
    return newNode;
}

TransactionNode* deleteTransaction(TransactionNode *head, int id) {
    TransactionNode *curr = head, *prev = NULL;
    while(curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }
    
    if(curr == NULL) return head;
    
    if(prev == NULL) {
        head = curr->next;
    } else {
        prev->next = curr->next;
    }
    
    free(curr);
    return head;
}

void printTransactions(TransactionNode *head) {
    while(head) {
        printf("Transaction ID: %d | Amount: %d\n", head->id, head->amount);
        head = head->next;
    }
}

int main() {
    TransactionNode *head = NULL;
    int numberOfTransactions, numberOfFraudulentTransactions;
    int id, amount;
    int i; 
    
    FILE *file = fopen("Test01.txt", "r");
    if(!file) {
        printf("Error opening the file!\n");
        return 1;
    }
    
    fscanf(file, "%d %d", &numberOfTransactions, &numberOfFraudulentTransactions);
    
       for(i = 0; i < numberOfTransactions; i++) {
        fscanf(file, "%d,%d", &id, &amount);
        head = insertTransaction(head, id, amount);
    }
    
     for(i = 0; i < numberOfFraudulentTransactions; i++) {
        fscanf(file, "%d", &id);
        head = deleteTransaction(head, id);
    }
    
    fclose(file);
    
     printTransactions(head);
    
  
    while(head) {
        TransactionNode *temp = head;
        head = head->next;
        free(temp);
    }
    
    return 0;
}

