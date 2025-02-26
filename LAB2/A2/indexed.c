#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_BLOCKS 100

struct File {
    char name[20];
    int indexBlock;
    int size;
    int *blocks;
};

int *disk, n, fileCount = 0;
struct File files[MAX_FILES];

void initDisk() { for (int i = 0; i < n; i++) disk[i] = 0; }

int findFreeBlock() {
    for (int i = 0; i < n; i++)
        if (disk[i] == 0) return i;
    return -1;
}

void createFile() {
    if (fileCount >= MAX_FILES) return;
    struct File f;
    printf("Name: "); scanf("%s", f.name);
    printf("Size: "); scanf("%d", &f.size);
    
    if ((f.indexBlock = findFreeBlock()) == -1) { printf("No space!\n"); return; }
    
    disk[f.indexBlock] = 1;
    f.blocks = (int*)malloc(f.size * sizeof(int));
    
    for (int i = 0; i < f.size; i++) {
        if ((f.blocks[i] = findFreeBlock()) == -1) {
            printf("Not enough space!\n");
            disk[f.indexBlock] = 0;
            free(f.blocks);
            return;
        }
        disk[f.blocks[i]] = 1;
    }
    
    files[fileCount++] = f;
    printf("File '%s' stored. Index Block: %d\n", f.name, f.indexBlock);
}

void deleteFile() {
    char name[20];
    printf("Delete: "); scanf("%s", name);
    for (int i = 0; i < fileCount; i++) {
        if (!strcmp(files[i].name, name)) {
            disk[files[i].indexBlock] = 0;
            for (int j = 0; j < files[i].size; j++) disk[files[i].blocks[j]] = 0;
            free(files[i].blocks);
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
        printf("%s (Index %d): ", files[i].name, files[i].indexBlock);
        for (int j = 0; j < files[i].size; j++) printf("%d ", files[i].blocks[j]);
        printf("\n");
    }
}

int main() {
    printf("Blocks: "); scanf("%d", &n);
    disk = (int*)calloc(n, sizeof(int));

    int ch;
    while (1) {
        printf("\n1.Create 2.Delete 3.Display 4.Exit: ");
        scanf("%d", &ch);
        
        switch (ch) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: displayDisk(); break;
            case 4: free(disk); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}

