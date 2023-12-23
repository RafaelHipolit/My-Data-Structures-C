#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int partition(int array[], int start, int end);
void quickSort(int array[], int start, int end);

void mergeSort(int vetor[], int inicio, int fim);
void mergeSortRecusao(int vetor[], int inicio, int fim, int esq[], int dir[]);
void merge(int vetor[], int inicio, int meio, int fim, int esq[], int dir[]);

void printVetor(int v[], int tamanho);
void printArrayInteval(int v[], int start, int end);

void insertionSort(int array[], int length)
{
    int n = 0;
    int j = 0;
    int temp = 0;
    int c = 0;
    for (int i = 1; i < length; i++)
    {          
        n = array[i];
        j = i - 1;
        while (array[j] > n)
        {
            temp = array[j];
            array[j] = n;
            array[j + 1] = temp;
            j--;
        }     

    }   
}

void quickSort(int array[], int start, int end)
{
    if (start < end)
    {
        int pivot = partition(array, start, end);

        //printf("pivo=%d; array[%d]=%d\n",pivot,pivot,array[pivot]);
        //printArrayInteval(array, start, pivot - 1);
        //printArrayInteval(array, pivot + 1, end);

        quickSort(array, start, pivot - 1);
        quickSort(array, pivot + 1, end);
    }
}

int partition(int array[], int start, int end)
{
    int posLowerValue = start - 1;
    int pivot = end;
    int temp = 0;

    for (int i = start; i < end; i++)
    {
        if (array[i] <= array[pivot])
        {
            // change position
            posLowerValue++;
            temp = array[i];
            array[i] = array[posLowerValue];
            array[posLowerValue] = temp;
        }
    }
    // change position
    posLowerValue++;
    temp = array[pivot];
    array[pivot] = array[posLowerValue];
    array[posLowerValue] = temp;
    pivot = posLowerValue;

    return pivot;
}



void mergeSort(int vetor[], int inicio, int fim)
{
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;

        int esqSize = meio - inicio + 1 + 1;
        int *esq = (int *)malloc((esqSize) * sizeof(int));

        int dirSize = fim - meio + 1;
        int *dir = (int *)malloc((dirSize) * sizeof(int));

        mergeSortRecusao(vetor, inicio, meio, esq, dir);
        mergeSortRecusao(vetor, meio + 1, fim, esq, dir);

        if (vetor[meio] > vetor[meio + 1])
        {
            merge(vetor, inicio, meio, fim, esq, dir);
        }

        free(esq);
        free(dir);
    }
}

void mergeSortRecusao(int vetor[], int inicio, int fim, int esq[], int dir[])
{
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;
        mergeSortRecusao(vetor, inicio, meio, esq, dir);
        mergeSortRecusao(vetor, meio + 1, fim, esq, dir);

        if (vetor[meio] > vetor[meio + 1])
        {
            merge(vetor, inicio, meio, fim, esq, dir);
        }
    }
}

void merge(int vetor[], int inicio, int meio, int fim, int esq[], int dir[])
{
    int esqSize = meio - inicio + 1 + 1;

    int dirSize = fim - meio + 1;

    for (int i = 0; i < esqSize; i++)
    {
        esq[i] = vetor[inicio + i];
    }
    esq[esqSize - 1] = __INT_MAX__;
    // printf("esq=");
    // printVetor(esq,esqSize);

    for (int i = 0; i < dirSize; i++)
    {
        dir[i] = vetor[meio + 1 + i];
    }
    dir[dirSize - 1] = __INT_MAX__;
    // printf("dir=");
    // printVetor(dir,dirSize);

    int j = 0;
    int k = 0;
    for (int i = 0; i < fim - inicio + 1; i++)
    {
        if (esq[j] <= dir[k])
        {
            vetor[inicio + i] = esq[j];
            j++;
        }
        else
        {
            vetor[inicio + i] = dir[k];
            k++;
        }
    }
    // printVetor(vetor,6);
}

void printVetor(int v[], int tamanho)
{

    for (int i = 0; i < tamanho; i++)
    {
        printf("%i, ", v[i]);
    }
    printf("\n");
}

void printArrayInteval(int v[], int start, int end)
{

    for (int i = start; i <= end; i++)
    {
        printf("%i, ", v[i]);
    }
    printf("\n");
}

int organized(int vetor[], int tamanho)
{

    int organizado = 1;
    for (int i = 1; i < tamanho; i++)
    {
        if (vetor[i - 1] > vetor[i])
        {
            organizado = 0;
            break;
        }
    }

    if (organizado)
    {
        printf("Organizado!\n");
    }
    else
    {
        printf("Nao ordenado :(\n");
    }

    return organizado;
}

int main()
{
    //int size = 10000000;
      int size = 10000;
    int *vetor1 = (int *)malloc((size) * sizeof(int));
    int *vetor2 = (int *)malloc((size) * sizeof(int));
    int *vetor3 = (int *)malloc((size) * sizeof(int));

    printf("gerando\n");
    srand((unsigned int)clock());
    int randomNum = 0;
    for (int i = 0; i < size; i++)
    {
        randomNum = rand();
        vetor1[i] = randomNum;
        vetor2[i] = randomNum; 
        vetor3[i] = randomNum; 
    }
    
    //printVetor(vetor1,size);

    clock_t start, end;
    double intevalo = 0;



    printf("\nMergeSort\n");

    start = clock();
    mergeSort(vetor1, 0, size - 1);
    end = clock();

    intevalo = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("tempo(s)=%f\n", intevalo);

    //printVetor(vetor1,size);
    printf("verificando... ");
    organized(vetor1, size);




    printf("\nQuickSort\n");

    start = clock();
    quickSort(vetor2, 0, size - 1);
    end = clock();

    intevalo = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("tempo(s)=%f\n", intevalo);

    //printVetor(vetor2,size);
    printf("verificando... ");
    organized(vetor2, size);




    printf("\nInsertionSort\n");

    start = clock();
    insertionSort(vetor3, size);
    end = clock();

    intevalo = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("tempo(s)=%f\n", intevalo);

    //printVetor(vetor3,size);
    printf("verificando... ");
    organized(vetor3, size);



    return 0;
}