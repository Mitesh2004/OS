#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct File { char name[20]; int size, blocks[20]; } files[100];
int *disk, total, count;

// Find free block
int find() {
    for (int i = 0; i < total; i++)
        if (!disk[i]) return i;
    return -1;
}

// Create file
void create_file() {
    struct File f;
    printf("File Name and Size: ");
    scanf("%s%d", f.name, &f.size);

    int i;
    for (i = 0; i < f.size; i++) {
        int b = find();
        if (b == -1) break;
        disk[b] = 1;
        f.blocks[i] = b;
    }

    if (i < f.size) {
        for (int j = 0; j < i; j++) disk[f.blocks[j]] = 0;
        printf("No Space!\n");
    } else {
        files[count++] = f;
        printf("File '%s' stored.\n", f.name);
    }
}

// Delete file
void delete_file() {
    char name[20];
    printf("Delete File: ");
    scanf("%s", name);
    int i;
    for (i = 0; i < count; i++)
        if (!strcmp(files[i].name, name)) break;

    if (i == count) printf("File Not Found!\n");
    else {
        for (int j = 0; j < files[i].size; j++)
            disk[files[i].blocks[j]] = 0;
        files[i] = files[--count];
        printf("File '%s' Deleted\n", name);
    }
}

// Sequential File Allocation Display
void display_sequential() {
    printf("\n--- Sequential File Allocation ---\n");
    printf("Bit Vector: ");
    for (int i = 0; i < total; i++) printf("%d", disk[i]);
    printf("\nFile\tStart\tEnd\n");
    for (int i = 0; i < count; i++) {
        int start = files[i].blocks[0];
        int end = files[i].blocks[files[i].size - 1];
        printf("%s\t%d\t%d\n", files[i].name, start, end);
    }
}

// Linked File Allocation Display
void display_linked() {
    printf("\n--- Linked File Allocation ---\n");
    printf("Bit Vector: ");
    for (int i = 0; i < total; i++) printf("%d", disk[i]);
    printf("\nFile\tBlock Chain\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t", files[i].name);
        for (int j = 0; j < files[i].size; j++) {
            printf("%d", files[i].blocks[j]);
            if (j != files[i].size - 1) printf(" -> ");
        }
        printf(" -> NULL\n");
    }
}

// Indexed File Allocation Display
void display_indexed() {
    printf("\n--- Indexed File Allocation ---\n");
    printf("Bit Vector: ");
    for (int i = 0; i < total; i++) printf("%d", disk[i]);
    printf("\nFile\tIndex Block\tBlocks\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t%d\t\t", files[i].name, files[i].blocks[0]);
        for (int j = 1; j < files[i].size; j++) {
            printf("%d ", files[i].blocks[j]);
        }
        printf("\n");
    }
}

int main() {
    printf("Total Blocks: ");
    scanf("%d", &total);
    disk = calloc(total, sizeof(int));

    int ch;
    while (1) {
        printf("\n1. Create File\n2. Delete File\n3. Sequential Display\n4. Linked Display\n5. Indexed Display\n0. Exit\nChoice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: create_file(); break;
            case 2: delete_file(); break;
            case 3: display_sequential(); break;
            case 4: display_linked(); break;
            case 5: display_indexed(); break;
            case 0:
                free(disk);
                return 0;
            default: printf("Invalid Choice!\n");
        }
    }
}
