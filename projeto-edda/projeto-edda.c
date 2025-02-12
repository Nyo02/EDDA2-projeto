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
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
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
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Função auxiliar para o Quick Sort
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
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

// Quick Sort
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
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int sessao_teste;
    int numero_ordenar;
    FILE *file;
    file = fopen("arq.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    // Le o conteúdo do arquivo
    char buffer[100000];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    // Conta a quantidade de numeros
    char temp_buffer[100000];
    strcpy(temp_buffer, buffer);
    int count = 0;
    for (char *p = strtok(temp_buffer, ","); p != NULL; p = strtok(NULL, ","))
    {
        count++;
    }

    // Armazena os numeros em arrays
    int *arr = malloc(count * sizeof(int));
    int *arr_copy1 = malloc(count * sizeof(int));
    int *arr_copy2 = malloc(count * sizeof(int));
    int *arr_copy3 = malloc(count * sizeof(int));

    int idx = 0;
    for (char *p = strtok(buffer, ","); p != NULL; p = strtok(NULL, ","))
    {
        arr[idx] = atoi(p);
        arr_copy1[idx] = arr[idx];
        arr_copy2[idx] = arr[idx];
        arr_copy3[idx] = arr[idx];
        idx++;
    }

    // Medição de tempo
    clock_t start, end;
    double bubble_time, insertion_time, quick_time, selection_time;

    // Bubble Sort
    start = clock();
    bubbleSort(arr, count);
    end = clock();
    bubble_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nBubble Sort:\n");
    printArray(arr, count);

    // Insertion Sort
    start = clock();
    insertionSort(arr_copy1, count);
    end = clock();
    insertion_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nInsertion Sort:\n");
    printArray(arr_copy1, count);

    // Quick Sort
    start = clock();
    quickSort(arr_copy2, 0, count - 1);
    end = clock();
    quick_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nQuick Sort:\n");
    printArray(arr_copy2, count);

    // Selection Sort
    // roda mil vezes selection sort para cada caso de 500 a 5000
    FILE *arq_selection;
    arq_selection = fopen("tempo_selection.txt", "r");
    for (numero_ordenar = 2500; numero_ordenar < 5500; numero_ordenar += 500)
    {
        fprintf(arq_selection, "tempo para %d: ", numero_ordenar);
        for (sessao_teste = 0; sessao_teste < 1000; sessao_teste++)
        {

            start = clock();
            selectionSort(arr_copy3, count);
            end = clock();
            selection_time = ((double)(end - start)) / CLOCKS_PER_SEC;
            fprintf(arq_selection, "%d", selection_time);
            fprintf(arq_selection, "\n\n");
        }
    }
    printf("\nSelection Sort:\n");
    printArray(arr_copy3, count);

    // Imprime todos os tempos de execução juntos no final
    printf("\n--- Tempos de execução ---\n");
    printf("Bubble Sort: %f segundos\n", bubble_time);
    printf("Insertion Sort: %f segundos\n", insertion_time);
    printf("Quick Sort: %f segundos\n", quick_time);
    printf("Selection Sort: %f segundos\n", selection_time);

    // Libera a memória alocada
    free(arr);
    free(arr_copy1);
    free(arr_copy2);
    free(arr_copy3);

    return 0;
}
