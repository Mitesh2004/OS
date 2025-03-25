#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct File { char name[20]; int size, blocks[20]; int index; } files[100];
int *disk, total, count;

// Find free block
int find() { 
    for (int i = 0; i < total; i++) 
        if (!disk[i]) return i; 
    return -1; 
}

// Create a file (Sequential style allocation)
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

    if (i < f.size) { // Not enough space
        for (int j = 0; j < i; j++) disk[f.blocks[j]] = 0;
        printf("No Space!\n");
    } else {
        f.index = f.blocks[0]; // For index display
        files[count++] = f;
        printf("File '%s' stored.\n", f.name);
    }
}

// Delete a file
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

// Sequential Allocation Display
void display_sequential() {
    printf("\nSequential Allocation View:\nFile\tStart\tEnd\n");
    for (int i = 0; i < count; i++) {
        int start = files[i].blocks[0];
        int end = files[i].blocks[files[i].size - 1];
        printf("%s\t%d\t%d\n", files[i].name, start, end);
    }
}

// Linked Allocation Display
void display_linked() {
    printf("\nLinked Allocation View:\nFile\tBlock Chain\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t", files[i].name);
        for (int j = 0; j < files[i].size; j++) {
            printf("%d", files[i].blocks[j]);
            if (j != files[i].size - 1) printf(" -> ");
        }
        printf(" -> NULL\n");
    }
}

// Indexed Allocation Display
void display_indexed() {
    printf("\nIndexed Allocation View:\nFile\tIndex Block\tBlocks\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t%d\t\t", files[i].name, files[i].index);
        for (int j = 0; j < files[i].size; j++) 
            printf("%d ", files[i].blocks[j]);
        printf("\n");
    }
}

int main() {
    printf("Total Blocks: ");
    scanf("%d", &total);
    disk = calloc(total, sizeof(int));

    int ch;
    while (1) {
        printf("\n1.Create 2.Delete 3.Sequential View 4.Linked View 5.Indexed View 0.Exit: ");
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

