/*Implement the C program that accepts an integer array. Main function forks child
process. Parent process sorts an integer array and passes the sorted array to child process
through the command line arguments of execve() system call. The child process uses
execve() system call to load new program that uses this sorted array for performing the
binary search to search the particular item in the array.*/
#include <stdio.h>
#include <stdlib.h>

int binary_search(int a[], int n, int target)
{
    int L = 0, R = n - 1;
    while (L <= R)
    {
        int mid = L + (R - L) / 2;
        if (a[mid] == target)
        {
            return mid;
        }
        if (a[mid] < target)
        {
            L = mid + 1;
        }
        else
        {
            R = mid - 1;
        }
    }
    return -1;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <sorted integers>\n", argv[0]);
        return 1;
    }
    int n = argc - 1;
    int arr[n];
    for (int i = 0; i < n; ++i)
    {
        arr[i] = atoi(argv[i + 1]);
    }
    int target;
    printf("Enter the number to search: ");
    scanf("%d", &target);
    int result = binary_search(arr, n, target);
    if (result != -1)
    {
        printf("Element found at index %d\n", result);
    }
    else
    {
        printf("Element not found\n");
    }
}