#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Função para realizar a troca de valores
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Bubble Sort
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Insertion Sort
void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort
int partition(int arr[], int low, int high)
{
    int pivot = arr[high], i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Selection Sort
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

int le_arquivo(int TAM, int *arr)
{ /* faz a abertura do arquivo e leitura de uma quantidade de numeros */
    int i;
    FILE *arq = fopen("numeros_ordenar.txt", "rt");
    if (arq == NULL)
        return (-1); /* falha na abertura do arquivo */
    else
    {
        /* arquivo aberto com sucesso */
        srand(time(NULL));
        for (i = 0; i < TAM; i++)
        {
            /* lendo 5000 valores aleatórios na faixa de 0 a 10000 */
            fscanf(arq, "%d", &arr[i]);
            printf("%d", arr[i]);
            printf("\n");
        }
    }
    fclose(arq);
    return 0;
}

int main()
{
    srand(time(NULL));
    int sizes[] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000};
    int num_tests = 1000;
    FILE *arq_resultados = fopen("tempos_execucao.txt", "w");

    if (arq_resultados == NULL)
    {
        printf("Erro ao abrir o arquivo de saída\n");
        return 1;
    }

    for (int s = 0; s < 10; s++)
    {
        int n = sizes[s];
        double bubble_total = 0, insertion_total = 0, quick_total = 0, selection_total = 0;

        for (int t = 0; t < num_tests; t++)
        {
            int *arr = (int *)malloc(n * sizeof(int));
            int *arr_copy1 = (int *)malloc(n * sizeof(int));
            int *arr_copy2 = (int *)malloc(n * sizeof(int));
            int *arr_copy3 = (int *)malloc(n * sizeof(int));
            le_arquivo(n, arr);
            memcpy(arr_copy1, arr, n * sizeof(int));
            memcpy(arr_copy2, arr, n * sizeof(int));
            memcpy(arr_copy3, arr, n * sizeof(int));

            clock_t start, end;
            // printar array no arquivo
            for (int i = 0; i < n; i++)
            {
                // printf("%d", arr[i]);
                fprintf(arq_resultados, " %d ", arr[i]);
                if (i % 5 == 0)
                {
                    fprintf(arq_resultados, "\n");
                }
            }
            // Bubble Sort
            start = clock();
            bubbleSort(arr, n);
            end = clock();
            bubble_total += ((double)(end - start)) / CLOCKS_PER_SEC;

            // Insertion Sort
            start = clock();
            insertionSort(arr_copy1, n);
            end = clock();
            insertion_total += ((double)(end - start)) / CLOCKS_PER_SEC;

            // Quick Sort
            start = clock();
            quickSort(arr_copy2, 0, n - 1);
            end = clock();
            quick_total += ((double)(end - start)) / CLOCKS_PER_SEC;

            // Selection Sort
            start = clock();
            selectionSort(arr_copy3, n);
            end = clock();
            selection_total += ((double)(end - start)) / CLOCKS_PER_SEC;

            free(arr);
            free(arr_copy1);
            free(arr_copy2);
            free(arr_copy3);
        }
        printf("\n\nVetor ordenado ==> ");

        fprintf(arq_resultados, "N=%d\n", n);
        fprintf(arq_resultados, "Bubble Sort: %.6f segundos\n", bubble_total / num_tests);
        fprintf(arq_resultados, "Insertion Sort: %.6f segundos\n", insertion_total / num_tests);
        fprintf(arq_resultados, "Quick Sort: %.6f segundos\n", quick_total / num_tests);
        fprintf(arq_resultados, "Selection Sort: %.6f segundos\n\n", selection_total / num_tests);

        printf("Finalizado para N=%d\n", n);
    }

    fclose(arq_resultados);
    printf("Resultados salvos em tempos_execucao.txt\n");
    return 0;
}
