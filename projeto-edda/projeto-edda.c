#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // Para usar a função sleep

// Função para realizar a troca de valores
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Bubble Sort
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Insertion Sort
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Função auxiliar para o Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Selection Sort
void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

// Função auxiliar para o Merge Sort
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    FILE *file;
    file = fopen("arq.txt.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    // Lê o conteúdo do arquivo
    char buffer[100000];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    // Conta a quantidade de números
    char temp_buffer[100000];
    strcpy(temp_buffer, buffer);
    int count = 0;
    for (char *p = strtok(temp_buffer, ","); p != NULL; p = strtok(NULL, ",")) {
        count++;
    }

    // Armazena os números em arrays
    int *arr = malloc(count * sizeof(int));
    int *arr_copy1 = malloc(count * sizeof(int));
    int *arr_copy2 = malloc(count * sizeof(int));
    int *arr_copy3 = malloc(count * sizeof(int));
    int *arr_copy4 = malloc(count * sizeof(int));

    int idx = 0;
    for (char *p = strtok(buffer, ","); p != NULL; p = strtok(NULL, ",")) {
        arr[idx] = atoi(p);
        arr_copy1[idx] = arr[idx];
        arr_copy2[idx] = arr[idx];
        arr_copy3[idx] = arr[idx];
        arr_copy4[idx] = arr[idx];
        idx++;
    }

    // Tamanhos dos subconjuntos
    int sizes[] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    // Abre o arquivo de saída para salvar os tempos
    FILE *output_file = fopen("tempos_execucao.txt", "w");
    if (output_file == NULL) {
        printf("Erro ao criar o arquivo de saída\n");
        return 1;
    }

    for (int i = 0; i < num_sizes; i++) {
        int current_size = sizes[i];
        printf("\n--- Ordenando %d números ---\n", current_size);
        fprintf(output_file, "\n--- Ordenando %d números ---\n", current_size);

        // Bubble Sort
        printf("\nBubble Sort %d processando...\n", current_size);
        double total_bubble_time = 0;
        for (int j = 0; j < 1000; j++) {
            clock_t start = clock();
            bubbleSort(arr, current_size);
            clock_t end = clock();
            total_bubble_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        }
        printf("Tempo médio de execução (1000 iterações): %f segundos\n", total_bubble_time / 1000);
        fprintf(output_file, "Bubble Sort: %f segundos\n", total_bubble_time / 1000);

        // Insertion Sort
        printf("\nInsertion Sort %d processando...\n", current_size);
        double total_insertion_time = 0;
        for (int j = 0; j < 1000; j++) {
            clock_t start = clock();
            insertionSort(arr_copy1, current_size);
            clock_t end = clock();
            total_insertion_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        }
        printf("Tempo médio de execução (1000 iterações): %f segundos\n", total_insertion_time / 1000);
        fprintf(output_file, "Insertion Sort: %f segundos\n", total_insertion_time / 1000);

        // Quick Sort
        printf("\nQuick Sort %d processando...\n", current_size);
        double total_quick_time = 0;
        for (int j = 0; j < 1000; j++) {
            clock_t start = clock();
            quickSort(arr_copy2, 0, current_size - 1);
            clock_t end = clock();
            total_quick_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        }
        printf("Tempo médio de execução (1000 iterações): %f segundos\n", total_quick_time / 1000);
        fprintf(output_file, "Quick Sort: %f segundos\n", total_quick_time / 1000);

        // Selection Sort
        printf("\nSelection Sort %d processando...\n", current_size);
        double total_selection_time = 0;
        for (int j = 0; j < 1000; j++) {
            clock_t start = clock();
            selectionSort(arr_copy3, current_size);
            clock_t end = clock();
            total_selection_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        }
        printf("Tempo médio de execução (1000 iterações): %f segundos\n", total_selection_time / 1000);
        fprintf(output_file, "Selection Sort: %f segundos\n", total_selection_time / 1000);

        // Merge Sort
        printf("\nMerge Sort %d processando...\n", current_size);
        double total_merge_time = 0;
        for (int j = 0; j < 1000; j++) {
            clock_t start = clock();
            mergeSort(arr_copy4, 0, current_size - 1);
            clock_t end = clock();
            total_merge_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        }
        printf("Tempo médio de execução (1000 iterações): %f segundos\n", total_merge_time / 1000);
        fprintf(output_file, "Merge Sort: %f segundos\n", total_merge_time / 1000);
    }

    // Fecha o arquivo de saída
    fclose(output_file);

    // Libera a memória alocada
    free(arr);
    free(arr_copy1);
    free(arr_copy2);
    free(arr_copy3);
    free(arr_copy4);

    return 0;
}
