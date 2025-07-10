#include <stdio.h>
#include <stdlib.h>

// Function to check if a number is prime (no library functions used)
int is_prime(int num) {
    if (num < 2) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

// Function to compute the zigzag sum
int compute_zigzag_sum(int **matrix, int n) {
    int sum = 0;

    for (int d = 0; d <= 2 * (n - 1); d++) {
        int row, col;

        if (d % 2 == 0) {
            // Move up-right (↗)
            row = (d < n) ? d : n - 1;
            col = d - row;

            while (row >= 0 && col < n) {
                int val = *(*(matrix + row) + col);
                sum += is_prime(val) ? -val : val;
                row--;
                col++;
            }
        } else {
            // Move down-left (↙)
            col = (d < n) ? d : n - 1;
            row = d - col;

            while (col >= 0 && row < n) {
                int val = *(*(matrix + row) + col);
                sum += is_prime(val) ? -val : val;
                row++;
                col--;
            }
        }
    }

    return sum;
}

// Main function
int main() {
    int n;

    printf("Enter the size of the matrix (n x n): ");
    if (scanf("%d", &n) != 1 || n < 2 || n > 100) {
        printf("Invalid input. Please enter an integer between 2 and 100.\n");
        return 1;
    }

    // Dynamically allocate the matrix
    int **matrix = (int **)malloc(n * sizeof(int *));
    if (matrix == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        *(matrix + i) = (int *)malloc(n * sizeof(int));
        if (*(matrix + i) == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    // Input the matrix
    printf("Enter the matrix elements (%d values):\n", n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", (*(matrix + i) + j)) != 1) {
                printf("Invalid input. Please enter integers only.\n");
                return 1;
            }
        }
    }

    // Compute the result
    int result = compute_zigzag_sum(matrix, n);
    printf("Zigzag sum: %d\n", result);

    // Free memory
    for (int i = 0; i < n; i++) {
        free(*(matrix + i));
    }
    free(matrix);

    return 0;
}
