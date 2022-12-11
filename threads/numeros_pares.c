#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>

// #define N_THREADS 7

enum {EVEN, ODD, ALL};

int type = ALL;

typedef struct block
{
    int n;
    int* numbers;
} Block;

// b   -> Block contendo todos os blocks
// n   -> Quantidade de blocks
void deleteBlock(Block* b, int n){
    int i;
    for(i = 0; i < n; i++)
        free(b[i].numbers);
    free(b);
}

// arr -> array base
// n   -> numero de elementos do array
// m   -> quantidade de subdivisões
Block* subdivideArray(int* arr, int n, int m){
    Block* blocks;
    int i = 0, l = 0, j = 0, _j = 0;
    // quantos elementos são possiveis de ter em
    // cada subarray para que tenhamos m subdivisões.
    int k = (int)(n / m);
    int p = n % m;
    
    printf("são possiveis %d elementos em cada array, e sobra %d\n", k, p);

    for(i = 0; i < m; i++){

        int* t = (int*)malloc(k*sizeof(int));
        if(i == 0){ // cria o primeiro block
            blocks = (Block*)malloc(sizeof(Block));
        }else{      // realoco i+1 na heap
            blocks = (Block*)realloc(blocks, (i+1)*sizeof(Block));
        }

        blocks[i].n = k;
        l = 0;
        for(j = _j; j < _j+k; j++)
            t[l++] = arr[j];
        _j = j;
        blocks[i].numbers = t;
        
    }   
    
    // Os valores que sobrarem resultante da subdivisão
    // que sairam da margem do calculo, serão colocados
    // nos blocks existentes a partir do primeiro
    while(_j < n){
        for(i = 0; i < m; i++){    
            if(_j > n-1) break;        
            Block* _t = &blocks[i];
            _t->n++;
            _t->numbers = (int*)realloc(_t->numbers, _t->n*sizeof(int));
            _t->numbers[_t->n-1] = arr[_j++];
        }
    }
    
    return (blocks);

}

void description(int n){
    if((n % 2) == 0 && (type == ALL || type == EVEN))
        printf("%d[P]\t", n);
    if((n % 2) != 0 && (type == ALL || type == ODD))
        printf("%d[I]\t", n);
}

void* isEven(void* blocks){
    int i;
    Block* b = (Block*)blocks;
    for(i = 0; i < b->n; i++){
        int n = b->numbers[i];
        description(n);
    }
    printf("\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    int i, j, k, error, N_THREADS, SIZE;
    int* arr = NULL;
    // thread configs
    int join = 0;
    k = 0;
    for(i = 0; i < argc; i++){
        k++;
        if(strcmp(argv[i], "-r")==0)
        {
            SIZE = (rand()%90)+10;
            arr = (int*)malloc(SIZE*sizeof(int));
            printf("Aleatoriedade de N[%d] numeros!\n", SIZE);
            for(j = 0; j < SIZE; j++)
                arr[j] = rand()%120;
        } else if(strcmp(argv[i], "-n")==0) {
            SIZE = (argc-k);
            arr = (int*)malloc(SIZE*sizeof(int));
            for(i = k; i < argc; i++)
                arr[i-k] = atoi(argv[i]);
        } else if(strcmp(argv[i], "-j")==0){
            join = 1;
        } else if(strcmp(argv[i], "-even")==0){
            type = EVEN;
        } else if(strcmp(argv[i], "-odd")==0){
            type = ODD;
        } else if(strcmp(argv[i], "-all")==0){
            type = ALL;
        }

    }
    
        
    if(!(N_THREADS=atoi(argv[1]))){
        printf("N_THREADS não pode ser 0, ou não foi possivel converter!\n");
        exit(-1);
    }

    // numero de threads deve ser menor que o numero de elementos
    assert(N_THREADS <= SIZE);
    
    printf("N_THREADS: %d\n", N_THREADS);
    
    pthread_t threads[N_THREADS];

    Block* b = subdivideArray(arr, SIZE, N_THREADS);
    for(i = 0; i < N_THREADS; i++){
        error = pthread_create(&threads[i], NULL, isEven, (void*)(b+i));
        assert(error == 0);
        if(join)pthread_join(threads[i], NULL);
    }
    pthread_exit(NULL);
    return 0;

}