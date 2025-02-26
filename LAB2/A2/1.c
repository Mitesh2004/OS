#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100

struct File { char name[20]; int start, size; };

int *disk, n, fileCount = 0;
struct File files[MAX_FILES];

void initDisk() { for (int i = 0; i < n; i++) disk[i] = 0; }

int findSpace(int size) {
    for (int i = 0; i <= n - size; i++) {
        int found = 1;
        for (int j = 0; j < size; j++) if (disk[i + j]) { found = 0; break; }
        if (found) return i;
    }
    return -1;
}

void createFile() {
    if (fileCount >= MAX_FILES) return;
    struct File f;
    printf("Enter File Name: "); scanf("%s", f.name);
    printf("Enter File Size: "); scanf("%d", &f.size);

    if ((f.start = findSpace(f.size)) == -1) { printf("No space!\n"); return; }

    for (int i = 0; i < f.size; i++) disk[f.start + i] = 1;
    files[fileCount++] = f;
    printf("File '%s' stored at %d - %d\n", f.name, f.start, f.start + f.size - 1);
}

void deleteFile() {
    char name[20];
    printf("Delete: "); scanf("%s", name);
    for (int i = 0; i < fileCount; i++) {
        if (!strcmp(files[i].name, name)) {
            for (int j = 0; j < files[i].size; j++) disk[files[i].start + j] = 0;
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
    for (int i = 0; i < fileCount; i++)
        printf("File: %s, Start: %d, Size: %d blocks\n", files[i].name, files[i].start, files[i].start + files[i].size - 1);
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




/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100

typedef struct { char name[20]; int start, size; } File;

int *disk, n, fileCount = 0;
File files[MAX_FILES];

void initDisk() { for (int i = 0; i < n; i++) disk[i] = 0; }

int findSpace(int size) {
    for (int i = 0; i <= n - size; i++) {
        int found = 1;
        for (int j = 0; j < size; j++) if (disk[i + j]) { found = 0; break; }
        if (found) return i;
    }
    return -1;
}

void createFile() {
    if (fileCount >= MAX_FILES) return;
    File f;
    printf("Enter File Name: "); scanf("%s", f.name);
    printf("Enter File Size: "); scanf("%d", &f.size);

    if ((f.start = findSpace(f.size)) == -1) { printf("No space!\n"); return; }

    for (int i = 0; i < f.size; i++) disk[f.start + i] = 1;
    files[fileCount++] = f;
    printf("File '%s' stored at %d - %d\n", f.name, f.start, f.start + f.size - 1);
}

void deleteFile() {
    char name[20];
    printf("Delete: "); scanf("%s", name);
    for (int i = 0; i < fileCount; i++) {
        if (!strcmp(files[i].name, name)) {
            for (int j = 0; j < files[i].size; j++) disk[files[i].start + j] = 0;
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
    for (int i = 0; i < fileCount; i++)
        printf("File: %s, Start: %d, Size: %d blocks\n", files[i].name, files[i].start, files[i].start + files[i].size - 1);
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
*/


