#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for a to-do item
struct TodoItem {
    char description[100];
    char status[20];
};

// Global variables
struct TodoItem todoList[100];
int itemCount = 0;

// Function prototypes
void creadit();
void displayMenu();
void addTodoItem();
void viewTodoList();
void markAsCompleted();
void saveToFile();
void loadFromFile();

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
                creadit();
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    }

    return 0;
}

void creadit(){
    printf("\n***** Creadit *****\n");
    printf("Program Devoloped by \nNafiur Rahman Sabbir\n");
}

void displayMenu() {
    printf("\n===== To-Do List Menu =====\n");
    printf("1. Add a To-Do Item\n");
    printf("2. View To-Do List\n");
    printf("3. Mark Item as Completed\n");
    printf("4. Save To-Do List to File\n");
    printf("5. Exit\n");
}

void addTodoItem() {
    printf("Enter the description of the to-do item: ");
    scanf(" %[^\n]", todoList[itemCount].description);
    strcpy(todoList[itemCount].status, "Pending");
    itemCount++;
    printf("To-Do Item added successfully.\n");
}

void viewTodoList() {
    printf("\n");
    if (itemCount == 0) {
        printf("To-Do List is empty.\n");
        return;
    }

    // printf("\n===== To-Do List =====\n");
    printf("\n     **** To-Do List ****  \n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d. Description: %s\n   Status: %s\n", i + 1, todoList[i].description, todoList[i].status);
    }
}

void markAsCompleted() {
    int index;
    printf("Enter the index of the item to mark as completed: ");
    scanf("%d", &index);

    if (index >= 1 && index <= itemCount) {
        strcpy(todoList[index - 1].status, "Completed");
        printf("Item marked as completed.\n");
    } else {
        printf("Invalid index. Please try again.\n");
    }
}

void saveToFile() {
    FILE *file = fopen("todolist.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        fprintf(file, "%s;%s\n", todoList[i].description, todoList[i].status);
    }

    fclose(file);
    printf("To-Do List saved to file successfully.\n");
}

void loadFromFile() {
    FILE *file = fopen("todolist.txt", "r");
    if (file == NULL) {
        printf("No saved To-Do List found.\n");
        return;
    }

    char line[150];
    while (fgets(line, sizeof(line), file)) {
        char *description = strtok(line, ";");
        char *status = strtok(NULL, "\n");

        strcpy(todoList[itemCount].description, description);
        strcpy(todoList[itemCount].status, status);

        itemCount++;
    }

    fclose(file);
    printf("To-Do List loaded from file.\n");
}