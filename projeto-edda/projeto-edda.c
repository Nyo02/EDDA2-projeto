#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // Para usar a funcao sleep
#include <locale.h>

// Funcao para realizar a troca de valores
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Bubble Sort
void bubbleSort(int array_bubble[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (array_bubble[j] > array_bubble[j + 1])
            {
                swap(&array_bubble[j], &array_bubble[j + 1]);
            }
        }
    }
}

// Insertion Sort
void insertionSort(int array_bubble[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = array_bubble[i];
        j = i - 1;
        while (j >= 0 && array_bubble[j] > key)
        {
            array_bubble[j + 1] = array_bubble[j];
            j = j - 1;
        }
        array_bubble[j + 1] = key;
    }
}

// Funcao auxiliar para o Quick Sort
int partition(int array_bubble[], int low, int high)
{
    int pivot = array_bubble[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (array_bubble[j] < pivot)
        {
            i++;
            swap(&array_bubble[i], &array_bubble[j]);
        }
    }
    swap(&array_bubble[i + 1], &array_bubble[high]);
    return (i + 1);
}

// Quick Sort
void quickSort(int array_bubble[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(array_bubble, low, high);
        quickSort(array_bubble, low, pi - 1);
        quickSort(array_bubble, pi + 1, high);
    }
}

// Selection Sort
void selectionSort(int array_bubble[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (array_bubble[j] < array_bubble[min_idx])
            {
                min_idx = j;
            }
        }
        swap(&array_bubble[min_idx], &array_bubble[i]);
    }
}

// Funcao auxiliar para o Merge Sort
void merge(int array_bubble[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = array_bubble[l + i];
    for (j = 0; j < n2; j++)
        R[j] = array_bubble[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            array_bubble[k] = L[i];
            i++;
        }
        else
        {
            array_bubble[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        array_bubble[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        array_bubble[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort
void mergeSort(int array_bubble[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(array_bubble, l, m);
        mergeSort(array_bubble, m + 1, r);
        merge(array_bubble, l, m, r);
    }
}
void heapify(int array_bubble[], int n, int i)
{

    int largest = i;
    int l = 2 * i + 1;

    int r = 2 * i + 2;
    if (l < n && array_bubble[l] > array_bubble[largest])
    {
        largest = l;
    }

    if (r < n && array_bubble[r] > array_bubble[largest])
    {
        largest = r;
    }

    if (largest != i)
    {
        int temp = array_bubble[i];
        array_bubble[i] = array_bubble[largest];
        array_bubble[largest] = temp;

        heapify(array_bubble, n, largest);
    }
}
// Heap Sort
void heapSort(int array_bubble[], int len)
{
    for (int i = len / 2 - 1; i >= 0; i--)
    {
        heapify(array_bubble, len, i);
    }
    for (int i = len - 1; i > 0; i--)
    {

        // Move current root to end
        int temp = array_bubble[0];
        array_bubble[0] = array_bubble[i];
        array_bubble[i] = temp;

        // Call max heapify on the reduced heap
        heapify(array_bubble, i, 0);
    }
}

void printArrayFile(FILE *output_file, int array_bubble[], int size)
{
    fprintf(output_file, "\n");
    for (int i = 0; i < size; i++)
    {
        fprintf(output_file, "%d ", array_bubble[i]);
    }
    fprintf(output_file, "\n");
}

void printArray(int array_bubble[], int size)
{
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array_bubble[i]);
    }
    printf("\n");
}
int main()
{
    setlocale(LC_ALL, "Portuguese");
    FILE *file;
    file = fopen("arq.txt.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    // Le o conteúdo do arquivo
    char buffer[100000];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    // Conta a quantidade de números
    char temp_buffer[100000];
    strcpy(temp_buffer, buffer);
    int count = 0;
    for (char *p = strtok(temp_buffer, ","); p != NULL; p = strtok(NULL, ","))
    {
        count++;
    }

    // Armazena os números em um array grande
    int *array_original = malloc(count * sizeof(int));
    int idx = 0;
    for (char *p = strtok(buffer, ","); p != NULL; p = strtok(NULL, ","))
    {
        array_original[idx] = atoi(p);
        idx++;
    }

    // Tamanhos dos subconjuntos
    int sizes[] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    // Abre o arquivo de saida para salvar os tempos
    FILE *output_file = fopen("tempos_execucao.txt", "w");
    if (output_file == NULL)
    {
        printf("Erro ao criar o arquivo de saida\n");
        return 1;
    }
    FILE *output_file_com_arrays = fopen("tempos_execucao_c_arrays.txt", "w");
    if (output_file_com_arrays == NULL)
    {
        printf("Erro ao criar o arquivo de saida\n");
        return 1;
    }
    int num_testes=1000;
    for (int i = 0; i < num_sizes; i++)
    {
        int current_size = sizes[i];
        printf("\n--- Ordenando %d numeros ---\n", current_size);
        fprintf(output_file, "\n--- Ordenando %d numeros ---\n", current_size);
        fprintf(output_file_com_arrays, "\n--- Ordenando %d numeros ---\n", current_size);
        //printar para arquivo

        fprintf(output_file_com_arrays, "\n--- Array desordenado ---\n");
        printArrayFile(output_file_com_arrays, array_original, current_size);
        //printar tela
        printf("\n--- Array desordenado ---\n");
        printArray(array_original, current_size);
        // Bubble Sort
        printf("\nBubble Sort %d processando...\n", current_size);
        double total_bubble_time = 0;
        for (int j = 0; j < num_testes; j++)
        {
            int *array_bubble = malloc(current_size * sizeof(int));
            memcpy(array_bubble, array_original, current_size * sizeof(int));

            clock_t start = clock();
            bubbleSort(array_bubble, current_size);
            clock_t end = clock();
            total_bubble_time += ((double)(end - start)) / CLOCKS_PER_SEC;
            if (j == 0)
            {
                fprintf(output_file_com_arrays,"\n--- Array ordenado ---\n");
                printArrayFile(output_file_com_arrays,array_bubble, current_size);
                printf("\n--- Array ordenado ---\n");
                printArray(array_bubble, current_size);
            }
            free(array_bubble);
        }

        printf("Tempo medio de execucao (%d iteracaes): %f segundos\n", num_testes,total_bubble_time / num_testes);
        fprintf(output_file, "Bubble Sort: %f segundos\n", total_bubble_time / num_testes);
        // Insertion Sort
        printf("\nInsertion Sort %d processando...\n", current_size);
        double total_insertion_time = 0;
        for (int j = 0; j < num_testes; j++)
        {
            int *array_insertion = malloc(current_size * sizeof(int));
            memcpy(array_insertion, array_original, current_size * sizeof(int));

            clock_t start = clock();
            insertionSort(array_insertion, current_size);
            clock_t end = clock();
            total_insertion_time += ((double)(end - start)) / CLOCKS_PER_SEC;
            free(array_insertion);
        }
        printf("Tempo medio de execucao (%d iteracaes): %f segundos\n", num_testes,total_insertion_time / num_testes);
        fprintf(output_file, "Insertion Sort: %f segundos\n", total_insertion_time / num_testes);

        // Quick Sort
        printf("\nQuick Sort %d processando...\n", current_size);
        double total_quick_time = 0;
        for (int j = 0; j < num_testes; j++)
        {
            int *array_quick = malloc(current_size * sizeof(int));
            memcpy(array_quick, array_original, current_size * sizeof(int));

            clock_t start = clock();
            quickSort(array_quick, 0, current_size - 1);
            clock_t end = clock();
            total_quick_time += ((double)(end - start)) / CLOCKS_PER_SEC;
            free(array_quick);
        }
        printf("Tempo medio de execucao (%d iteracaes): %f segundos\n", num_testes,total_quick_time / num_testes);
        fprintf(output_file, "Quick Sort: %f segundos\n", total_quick_time / num_testes);
        // Selection Sort
        printf("\nSelection Sort %d processando...\n", current_size);
        double total_selection_time = 0;
        for (int j = 0; j < num_testes; j++)
        {
            int *array_selection = malloc(current_size * sizeof(int));
            memcpy(array_selection, array_original, current_size * sizeof(int));

            clock_t start = clock();
            selectionSort(array_selection, current_size);
            clock_t end = clock();
            total_selection_time += ((double)(end - start)) / CLOCKS_PER_SEC;
            free(array_selection);
        }
        printf("Tempo medio de execucao (%d iteracaes): %f segundos\n", num_testes,total_quick_time / num_testes);
        fprintf(output_file, "Selection Sort: %f segundos\n", total_selection_time / num_testes);

        // Merge Sort
        printf("\nMerge Sort %d processando...\n", current_size);
        double total_merge_time = 0;
        for (int j = 0; j < num_testes; j++)
        {
            int *array_merge = malloc(current_size * sizeof(int));
            memcpy(array_merge, array_original, current_size * sizeof(int));

            clock_t start = clock();
            mergeSort(array_merge, 0, current_size - 1);
            clock_t end = clock();
            total_merge_time += ((double)(end - start)) / CLOCKS_PER_SEC;
            free(array_merge);
        }
        printf("Tempo medio de execucao (%d iteracaes): %f segundos\n", num_testes,total_quick_time / num_testes);
        fprintf(output_file, "Merge Sort: %f segundos\n", total_merge_time / num_testes);


        // Heap sort
        printf("\nHeap Sort %d processando...\n", current_size);
        double total_heap_time = 0;
        for (int j = 0; j < num_testes; j++)
        {
            int *array_heap = malloc(current_size * sizeof(int));
            memcpy(array_heap, array_original, current_size * sizeof(int));

            clock_t start = clock();
            heapSort(array_heap, current_size - 1);
            clock_t end = clock();
            total_heap_time += ((double)(end - start)) / CLOCKS_PER_SEC;
            free(array_heap);
        }
        printf("Tempo medio de execucao (%d iteracaes): %f segundos\n", num_testes,total_heap_time / num_testes);
        fprintf(output_file, "Heap Sort: %f segundos\n", total_heap_time / num_testes);

    }

    // Fecha o arquivo de saida
    fclose(output_file);

    // Libera a memoria alocada do original
    free(array_original);

    return 0;
}
