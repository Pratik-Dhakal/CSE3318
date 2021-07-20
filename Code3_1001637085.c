//Name - Pratik Dhakal
//Student ID - 1001637085
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void swap(int *SwapA, int *SwapB)
{
    int temp = *SwapA;
    *SwapA = *SwapB;
    *SwapB = temp;
}

int partition(int A[], int low, int high)
{
    int i, j = 0;
    #if QSM
    int middle = (high+low)/2;
    swap(&A[middle], &A[high]);
    #elif QSRND
    int random = (rand() % (high-low+1)) + low;
    swap(&A[random], &A[high]);
    #endif
    int pivot = A[high];

    i  = (low - 1);

    for(j = low; j < high; j++)
    {
        if(A[j] < pivot)
        {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[high]);

    return (i + 1);
}

void QuickSort(int A[], int low, int high)
{
    if(low < high)
    {
        int ndx = partition(A, low, high);

        QuickSort(A, low, ndx - 1);
        QuickSort(A, ndx + 1, high);
    }
}

int * ReadFileIntoLL(int argc,  char *argv[], int * count)
{
    
	if(argc < 2)
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}

	FILE *fp;
    char line[128];
    fp = fopen(argv[1], "r");
    int pos = ftell(fp);

    while(fgets(line, sizeof(line), fp))
    {
        //AddNodeToLL(atoi(line), LLH);
		*count = *count + 1;
    }
    fseek (fp, pos, SEEK_SET);

    int *array = (int*)(malloc)(*(count)*sizeof(int));
    int i = 0;

    while(fgets(line, sizeof(line), fp))
    {
        array[i] = atoi(line);
        i++;	
    }

    fclose(fp);

    return array;
}

void printarray(int *array, int count)
{
    int x;
    for(x = 0; x < count; x++)
    {
        printf("%d \n", array[x]);
    }

    printf("\n");
    
}

int main(int argc, char *argv[])
{
    int runs,run_increment = 0, sum = 0;
    clock_t start,end;
    if(argc < 3)
	{
		printf("Number of runs not specified on command line...defaulting to 10\n\n");
        runs = 10;
	}
    else
    {
        runs = atoi(argv[2]);
    }
    int count = 0;
    int *array;
    int records;


    while(run_increment < runs)
    {
        array = ReadFileIntoLL(argc,argv,&count);

        //int arr[] = {9,6,5,7};
        //int n = sizeof(array)/sizeof(array[0]);
        #ifdef PRINTARRAY
            printarray(array,count);
        #endif
        
        start = clock();
        QuickSort(array,0, count-1);
        end = clock();
        printf("Run %d complete: %ld tics\n", run_increment + 1,end-start);
        sum += (end - start);

        #ifdef PRINTARRAY
            printarray(array,count);
        #endif

        free(array);
        records = count;
        count = 0;
        run_increment++;

        

    }
    
    int average = sum/runs;

    printf("\nThe average runtime for %d runs is %d\n",runs,average);

    printf("There are %d records\n",records);
    
    

    return 0;
}