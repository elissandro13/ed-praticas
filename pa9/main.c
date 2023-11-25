#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define SWAP_DATA(A, pos, ancestor_pos)    \
    do {                                       \
        A[*pos] += A[*ancestor_pos]; \
        A[*ancestor_pos] = A[*pos] - A[*ancestor_pos]; \
        A[*pos] -= A[*ancestor_pos]; \
    } while (0)

// median of 3 integers
int median (int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
}

#define ALGINSERTION 1
#define ALGSELECTION 2
#define ALGQSORT     3
#define ALGQSORT3    4
#define ALGQSORTINS  5
#define ALGQSORT3INS 6
#define ALGHEAPSORT  7
#define ALGRECSEL    8

typedef struct alg {
    int num;
    char *name;
} alg_t;

alg_t algvet[] = {
        {ALGINSERTION, "i"},
        {ALGSELECTION, "s"},
        {ALGQSORT,     "q"},
        {ALGQSORT3,    "q3"},
        {ALGQSORTINS,  "qi"},
        {ALGQSORT3INS, "q3i"},
        {ALGHEAPSORT,  "h"},
        {ALGRECSEL,    "rs"},
        {0,            0}
};

int name2num(char *name) {
    int i = 0;
    while (algvet[i].num) {
        if (!strcmp(algvet[i].name, name)) return algvet[i].num;
        i++;
    }
    return 0;
}

char *num2name(int num) {
    int i = 0;
    while (algvet[i].num) {
        if (algvet[i].num == num) return algvet[i].name;
        i++;
    }
    return 0;
}

typedef struct opt {
    int size;
    int seed;
    int alg;
} opt_t;

typedef struct sortperf {
    long int cmp;
    long int move;
    long int calls;
} sortperf_t;

void resetcounter(sortperf_t *s) {
// Descricao: inicializa estrutura
// Entrada: 
// Saida: s
    s->cmp = 0;
    s->move = 0;
    s->calls = 0;
}

void inccmp(sortperf_t *s, int num) {
// Descricao: incrementa o numero de comparacoes em num 
// Entrada: s, num
// Saida: s
    s->cmp += num;
}

void incmove(sortperf_t *s, int num) {
// Descricao: incrementa o numero de movimentacoes de dados em num 
// Entrada: s, num
// Saida: s
    s->move += num;
}

void inccalls(sortperf_t *s, int num) {
// Descricao: incrementa o numero de chamadas de função em num 
// Entrada: s, num
// Saida: s
    s->calls += num;
}

char *printsortperf(sortperf_t *s, char *str, char *pref) {
// Descricao: gera string com valores de sortperf 
// Entrada: s, pref
// Saida: str

    sprintf(str, "%s cmp %li move %li calls %li", pref, s->cmp, s->move, s->calls);
    return str;
}


void initVector(int *vet, int size) {
// Descricao: inicializa vet com valores aleatorios
// Entrada: vet
// Saida: vet
    int i;
    // inicializa a parte alocada da vetor com valores aleatorios
    for (i = 0; i < size; i++) {
        vet[i] = (int) (drand48() * size);
    }
}

void swap(int *xp, int *yp, sortperf_t *s) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    incmove(s, 3);
}

// heapsort
void heapify(int *A, int l, int r, sortperf_t *s) {
    inccalls(s, 1);

    int i = l, j = l << 1;
    int aux = A[l];
    while (j <= r) {
        if (j < r) {
            inccmp(s, 1);
            if(A[j] < A[j + 1]) j++;
        }
        inccmp(s, 1);

        if (A[j] <= aux) break;
        incmove(s, 1);
        A[i] = A[j];
        i = j;j = i << 1;
    }
    A[i] = aux;
    incmove(s, 2);
}

void buildheap(int *A, int n, sortperf_t *s) {
    inccalls(s, 1);

    for (int left = n / 2 + 1 ; left > 0; --left) 
        heapify(A, left, n, s);
}

void heapSort(int *A, int n, sortperf_t *s) {
    inccalls(s, 1);
    buildheap(A,n,s);
    
    for (int right = n ; right > 0; --right) {
        swap(&A[1], &A[right], s);

        heapify(A, 1, right - 1, s);
    }
}


// recursive selection sort
void recursiveSelectionSort(int arr[], int l, int r, sortperf_t *s) {
    
    int min = l;

    inccalls(s, 1);

    for (int j = l + 1; j <= r; j++) {
        
        inccmp(s, 1);
        if (arr[j] < arr[min]) {
            min = j;    
        }
    }

    
    if (min != l)
        swap(&arr[min], &arr[l], s);

    if (l + 1 < r) {
        recursiveSelectionSort(arr, l + 1, r, s);
    }
}

// selection sort
void selectionSort(int arr[], int l, int r, sortperf_t *s) {
    inccalls(s, 1);
    for (int i = l, min = i; i < r -1; ++i, min = i) {
        for (int j = i + 1; j < r; j++) {
            inccmp(s, 1);
            if (arr[min] > arr[j]) min = j;
        }
        if (min != i) swap(&arr[min], &arr[i], s);
    }
}

//insertion sort
void insertionSort(int v[], int l, int r, sortperf_t *s) {
    inccalls(s, 1);
    for (int i = l + 1, j = i - 1; i < r; i++, j = i - 1) {
        int aux = v[i];
        inccmp(s, 1);
        while (j >= 0 && aux < v[j]) {
            inccmp(s, 1);
            incmove(s, 1);
            v[j + 1] = v[j];
            j--;
        }
        incmove(s, 2);
        v[j + 1] = aux;
    }
}

// quicksort partition using median of 3
void partition3(int *A, int l, int r, int *i, int *j, sortperf_t *s) {
    inccalls(s, 1);
    *i = l; *j = r;
    int pivo = median(A[l], A[(*i + *j) / 2], A[r]);

    do {
        inccmp(s, 1);

        while (A[*i] < pivo) {
            (*i)++;
            inccmp(s, 1);
        }
        inccmp(s, 1);

        while (pivo < A[*j]) {
            (*j)--;
            inccmp(s, 1);
        }
        if (*i <= *j) {
            incmove(s, 3);
            SWAP_DATA(A, i, j);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

// standard quicksort partition
void partition(int *A, int l, int r, int *i, int *j, sortperf_t *s) {
    inccalls(s, 1);
    *i = l; *j = r;
    int pivot = A[(*i + *j) / 2];

    do {
        inccmp(s, 1);

        while (A[*i] < pivot) {
            (*i)++;
            inccmp(s, 1);
        }
        inccmp(s, 1);

        while (pivot < A[*j]) {
            (*j)--;
            inccmp(s, 1);
        }
        if (*i <= *j) {
            incmove(s, 3);
            SWAP_DATA(A, i, j);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

// standard quicksort
void quickSort(int *A, int l, int r, sortperf_t *s) {
    inccalls(s, 1);

    int i = l; 
    int j = r;

    partition(A, l, r, &i, &j, s);

    if (l < j) 
        quickSort(A, l, j, s);
    if (i < r) 
        quickSort(A, i, r, s);
}

// quicksort with median of 3
void quickSort3(int *A, int l, int r, sortperf_t *s) {
    inccalls(s, 1);
    int i , j;
    partition3(A, l, r, &i, &j, s);
    if (l < j) quickSort3(A, l, j, s);
    if (i < r) quickSort3(A, i, r, s);
}

// quicksort with insertion for small partitions
void quickSortIns(int *A, int l, int r, sortperf_t *s) {
    if (r - l <= 50) {
        insertionSort(A, l, r + 1, s);
    } else {
        int i = l;

        int j = r;

        partition(A, l, r, &i, &j, s);

        inccalls(s, 1);

        if (l < j) 
            quickSortIns(A, l, j, s);
        if (i < r) 
            quickSortIns(A, i, r, s);
    }
}

// quicksort with insertion for small partitions and median of 3
void quickSort3Ins(int *A, int l, int r, sortperf_t *s) {
    if (r - l <= 50) {
        insertionSort(A, l, r + 1, s);
    } else {
        int i = l;

        int j = r;

        partition3(A, l, r, &i, &j, s);

        inccalls(s, 1);

        if (l < j) quickSort3Ins(A, l, j, s);
        if (i < r) quickSort3Ins(A, i, r, s);
    }
}

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
    fprintf(stderr, "sortperf\n");
    fprintf(stderr, "\t-z <int>\t(vector size)\n");
    fprintf(stderr, "\t-s <int>\t(initialization seed)\n");
    fprintf(stderr, "\t-a <s|i|q|q3|qi|q3i|h|rs>\t(algorithm)\n");
    fprintf(stderr, "\t    s\tselection\n");
    fprintf(stderr, "\t    i\tinsertion\n");
    fprintf(stderr, "\t    q\tquicksort\n");
    fprintf(stderr, "\t    q3\tquicksort+median3\n");
    fprintf(stderr, "\t    qi\tquicksort+insertion\n");
    fprintf(stderr, "\t    q3i\tquicksort+median3+insertion\n");
    fprintf(stderr, "\t    h\theapsort\n");
    fprintf(stderr, "\t    rs\trecursive selection\n");
}

void parse_args(int argc, char **argv, opt_t *opt)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc, argv, opt
// Saida: opt
{
    // variaveis externas do getopt
    extern char *optarg;
    extern int optind;

    // variavel auxiliar
    int c;

    // inicializacao variaveis globais para opcoes
    opt->seed = 1;
    opt->size = 10;
    opt->alg = 1;

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while ((c = getopt(argc, argv, "z:s:a:h")) != EOF) {
        switch (c) {
            case 'z':
                opt->size = atoi(optarg);
                break;
            case 's':
                opt->seed = atoi(optarg);
                break;
            case 'a':
                opt->alg = name2num(optarg);
                break;
            case 'h':
            default:
                uso();
                exit(1);

        }
    }
    if (!opt->alg) {
        uso();
        exit(1);
    }
}

void clkDiff(struct timespec t1, struct timespec t2,
             struct timespec *res)
// Descricao: calcula a diferenca entre t2 e t1, que e armazenada em res
// Entrada: t1, t2
// Saida: res
{
    if (t2.tv_nsec < t1.tv_nsec) {
        // ajuste necessario, utilizando um segundo de tv_sec
        res->tv_nsec = 1000000000 + t2.tv_nsec - t1.tv_nsec;
        res->tv_sec = t2.tv_sec - t1.tv_sec - 1;
    } else {
        // nao e necessario ajuste
        res->tv_nsec = t2.tv_nsec - t1.tv_nsec;
        res->tv_sec = t2.tv_sec - t1.tv_sec;
    }
}


int main(int argc, char **argv) {
    sortperf_t s;
    int *vet;
    char buf[200];
    char pref[100];
    opt_t opt;
    struct timespec inittp, endtp, restp;

    // parse_args
    parse_args(argc, argv, &opt);

    // malloc with opt.size+1 for heapsort
    vet = (int *) malloc((opt.size + 1) * sizeof(int));

    // initialize
    resetcounter(&s);
    srand48(opt.seed);
    initVector(vet, opt.size);
    vet[opt.size] = vet[0]; // for heapsort
    //if (opt.size < 100) printVector(vet, opt.size);

    clock_gettime(CLOCK_MONOTONIC, &inittp);

    // execute algorithm
    switch (opt.alg) {
        case ALGINSERTION:
            insertionSort(vet, 0, opt.size, &s);
            break;
        case ALGSELECTION:
            selectionSort(vet, 0, opt.size, &s);
            break;
        case ALGQSORT:
            quickSort(vet, 0, opt.size - 1, &s);
            break;
        case ALGQSORT3:
            quickSort3(vet, 0, opt.size - 1, &s);
            break;
        case ALGQSORTINS:
            quickSortIns(vet, 0, opt.size - 1, &s);
            break;
        case ALGQSORT3INS:
            quickSort3Ins(vet, 0, opt.size - 1, &s);
            break;
        case ALGHEAPSORT:
            heapSort(vet, opt.size, &s);
            break;
        case ALGRECSEL:
            recursiveSelectionSort(vet, 0, opt.size - 1, &s);
            break;
    }
    clock_gettime(CLOCK_MONOTONIC, &endtp);
    clkDiff(inittp, endtp, &restp);



    // print stats
    sprintf(pref, "alg %s seed %d size %d time %ld.%.9ld",
            num2name(opt.alg), opt.seed, opt.size, restp.tv_sec, restp.tv_nsec);

    printsortperf(&s, buf, pref);
    printf("%s\n", buf);

    exit(0);
}