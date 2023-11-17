#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TodoItem {
    char description[100];
    char status[20];
    struct TodoItem* next;
};

// Global variable: head of the linked list
struct TodoItem* head = NULL;

// Function prototypes
void displayMenu();
void addTodoItem();
void viewTodoList();
void markAsCompleted();
void saveToFile();
void loadFromFile();
void freeList();

int main() {
    loadFromFile();

    int choice;
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTodoItem();
                break;
            case 2:
                viewTodoList();
                break;
            case 3:
                markAsCompleted();
                break;
            case 4:
                saveToFile();
                break;
            case 5:
                freeList();
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\n===== To-Do List Menu =====\n");
    printf("1. Add a To-Do Item\n");
    printf("2. View To-Do List\n");
    printf("3. Mark Item as Completed\n");
    printf("4. Save To-Do List to File\n");
    printf("5. Exit\n");
    printf("============================\n");
}

void addTodoItem() {
    struct TodoItem* newItem = (struct TodoItem*)malloc(sizeof(struct TodoItem));
    if (newItem == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter the description of the to-do item: ");
    scanf(" %[^\n]", newItem->description);
    strcpy(newItem->status, "Pending");
    newItem->next = NULL;

    // Insert the new item at the beginning of the linked list
    newItem->next = head;
    head = newItem;

    printf("To-Do Item added successfully.\n");
}

void viewTodoList() {
    if (head == NULL) {
        printf("To-Do List is empty.\n");
        return;
    }

    // printf("\n===== To-Do List =====\n");
    printf("\n     **** To-Do List ****  \n");
    struct TodoItem* current = head;
    int index = 1;

    while (current != NULL) {
        printf("%d. Description: %s\n   Status: %s\n", index, current->description, current->status);
        current = current->next;
        index++;
    }
}

void markAsCompleted() {
    if (head == NULL) {
        printf("To-Do List is empty.\n");
        return;
    }

    int index;
    printf("Enter the index of the item to mark as completed: ");
    scanf("%d", &index);

    struct TodoItem* current = head;
    int currentIndex = 1;

    while (current != NULL && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }

    if (current != NULL) {
        strcpy(current->status, "Completed");
        printf("Item marked as completed.\n");
    } else {
        printf("Invalid index. Please try again.\n");
    }
}

void saveToFile() {
    FILE* file = fopen("todolist.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    struct TodoItem* current = head;

    while (current != NULL) {
        fprintf(file, "%s;%s\n", current->description, current->status);
        current = current->next;
    }

    fclose(file);
    printf("To-Do List saved to file successfully.\n");
}

void loadFromFile() {
    FILE* file = fopen("todolist.txt", "r");
    if (file == NULL) {
        printf("No saved To-Do List found.\n");
        return;
    }

    char line[150];
    while (fgets(line, sizeof(line), file)) {
        struct TodoItem* newItem = (struct TodoItem*)malloc(sizeof(struct TodoItem));
        if (newItem == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }

        char* description = strtok(line, ";");
        char* status = strtok(NULL, "\n");

        strcpy(newItem->description, description);
        strcpy(newItem->status, status);
        newItem->next = head;
        head = newItem;
    }

    fclose(file);
    printf("To-Do List loaded from file.\n");
}

void freeList() {
    struct TodoItem* current = head;

    while (current != NULL) {
        struct TodoItem* temp = current;
        current = current->next;
        free(temp);
    }

    head = NULL;
}




