#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100

struct Block { int index; struct Block *next; };
struct File { char name[20]; int size; struct Block *start; };

int n, fileCount = 0, *disk;
struct File files[MAX_FILES];

void initDisk() { for (int i = 0; i < n; i++) disk[i] = 0; }

struct Block* allocateBlocks(int size) {
    struct Block *head = NULL, *temp = NULL;
    for (int i = 0, count = 0; i < n && count < size; i++) {
        if (!disk[i]) {
            struct Block *newBlock = (struct Block*)malloc(sizeof(struct Block));
            newBlock->index = i;
            newBlock->next = NULL;
            disk[i] = 1;
            if (!head) head = newBlock;
            else temp->next = newBlock;
            temp = newBlock;
            count++;
        }
    }
    return (temp && temp->index - head->index + 1 == size) ? head : NULL;
}

void createFile() {
    if (fileCount >= MAX_FILES) return;
    struct File f;
    printf("Name: "); scanf("%s", f.name);
    printf("Size: "); scanf("%d", &f.size);

    f.start = allocateBlocks(f.size);
    if (!f.start) { printf("No space!\n"); return; }

    files[fileCount++] = f;
    printf("File '%s' allocated.\n", f.name);
}

void deleteFile() {
    char name[20];
    printf("Delete: "); scanf("%s", name);
    for (int i = 0; i < fileCount; i++) {
        if (!strcmp(files[i].name, name)) {
            struct Block *temp = files[i].start;
            while (temp) {
                disk[temp->index] = 0;
                struct Block *del = temp;
                temp = temp->next;
                free(del);
            }
            files[i] = files[--fileCount];
            printf("Deleted '%s'\n", name);
            return;
        }
    }
    printf("Not found!\n");
}

void displayDisk() {
    for (int i = 0; i < n; i++) printf("%d ", disk[i]);
    printf("\nFiles:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%s: ", files[i].name);
        struct Block *temp = files[i].start;
        while (temp) {
            printf("%d -> ", temp->index);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    printf("Blocks: "); scanf("%d", &n);
    disk = (int*)calloc(n, sizeof(int));

    int ch;
    while (1) {
        printf("\n1.Create 2.Delete 3.Display 0.Exit: ");
        scanf("%d", &ch);
        
        switch (ch) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: displayDisk(); break;
            case 0: free(disk); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}

