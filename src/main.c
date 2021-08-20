#include <stdio.h>
#include <stdlib.h> 

#define MAX 1000 

typedef struct item
{
    int number;        
    int weight_aresta;       
    struct item *prox;  
    struct item *base;
} item;                

typedef struct
{
    int quantV;
    item *start;
} DynamicList;  

typedef struct fila
{
    int number;
    struct fila *prox;
} fila;

typedef struct
{
    int quant;
    fila *start; 
    fila *fim;   
} DynamicQueue;

void prision(DynamicList *L); 
void CreateDL(DynamicList *L); 
void Free_All(DynamicList *L);
void printCompleteGraph(DynamicList *L);
item *NewEdge(int value, int weight); 
item *NewVertex(int value); 
int CheckEdge(DynamicList *L, int v1, int v2, int weight);
void InsertOrderedEdge(DynamicList *L, item *C, item *V);
int InsertEdge(DynamicList *L, int n);
void InsertFirstVertex(DynamicList *L, item *c);
void InsertEndVertex(DynamicList *L, item *c);
void InsertEdgeOrdely(DynamicList *L, item *C);
void AdjacencyMatrix(DynamicList *L);
int **AllocateDynamicMatrix(int l, int c);
void ShowMatrix(int l, int c, int **matrix); 
void FreeDynamicMatrix(int l, int **M); 
int SearchLine(int value, int l, int c, int **M);
item *EdgesGivenVertex(DynamicList *L, int Vstart);
int **BFS(DynamicList *L, int Vstart); 
int BFS_Verify(DynamicList *L, int Vstart); 
int InformPosition(DynamicList *L, int Vstart); 
void InsertQueue(DynamicQueue *F, int value);
int RemoveQueue(DynamicQueue *F);

int time = 0; 

int main(void)
{
    int option;  
    int retorno; 

    DynamicList Graph;
    CreateDL(&Graph);      

    prision(&Graph); 

    do 
    {
        printf("\n1. Visualizar Grafo\n");
        printf("2. Converter Grafo para matriz de Adjacencia\n");
        printf("3. Buscar fuga (Busca em Largura)\n4. sair\n\n");
        scanf("%d", &option);

        switch (option)
        {
        case 1: 
        {
            if (Graph.quantV == 0)
            {
                printf("Grafo Vazio !!!\n");
            }   
            else
            {
                printCompleteGraph(&Graph);
            }
            break;
        }

        case 2: 
        {
            if (Graph.quantV == 0)
            {
                printf("Grafo Vazio !!!\n");
            }
            else
            {
                AdjacencyMatrix(&Graph);
            }
            break;
        }

        case 3: 
        {
            int v1;
            printf("Informe a cela de Origem: ");
            scanf("%d", &v1);

            retorno = BFS_Verify(&Graph, v1);

            if (retorno == -1)
            {
                printf("ERRO! Nao existe a cela %d na prisão !!!\n", v1);
            }
            else if (retorno == -2)
            {
                printf("Prisão Vazia !!!\n");
            }
            break;
        }

        case 4: 
        {
            Free_All(&Graph); 
            system("clear");
            exit(0);
            break;            
            
        }

        default: 
        {
            printf("Opção invalida !!!\n");
            break;
        }
        }
    } while (option != 13); 
    return 0;
}

void prision(DynamicList *L) 
{
    InsertEdge(L, 1);
    InsertEdge(L, 2);
    InsertEdge(L, 3);
    InsertEdge(L, 4);
    InsertEdge(L, 5);
    InsertEdge(L, 6);
    InsertEdge(L, 7);
    InsertEdge(L, 8);
    InsertEdge(L, 9);
    InsertEdge(L, 10);

    CheckEdge(L, 1, 6, 1);
    CheckEdge(L, 2, 4, 1);
    CheckEdge(L, 2, 5, 1);
    CheckEdge(L, 2, 6, 1);
    CheckEdge(L, 3, 4, 1);
    CheckEdge(L, 4, 2, 1);
    CheckEdge(L, 4, 5, 1);
    CheckEdge(L, 4, 10, 1);
    CheckEdge(L, 5, 2, 1);
    CheckEdge(L, 5, 4, 1);
    CheckEdge(L, 5, 7, 1);
    CheckEdge(L, 5, 9, 1);
    CheckEdge(L, 5, 10, 1);
    CheckEdge(L, 6, 1, 1);
    CheckEdge(L, 6, 2, 1);
    CheckEdge(L, 6, 7, 1);
    CheckEdge(L, 7, 5, 1);
    CheckEdge(L, 7, 6, 1);
    CheckEdge(L, 7, 8, 1);
    CheckEdge(L, 7, 9, 1);
    CheckEdge(L, 8, 7, 1);
    CheckEdge(L, 9, 5, 1);
    CheckEdge(L, 9, 7, 1);
    CheckEdge(L, 9, 10, 1);
    CheckEdge(L, 10, 4, 1);
    CheckEdge(L, 10, 5, 1);
    CheckEdge(L, 10, 9, 1);
}

void CreateDL(DynamicList *L) 
{
    L->quantV = 0;    
    L->start = NULL; 
}

void Free_All(DynamicList *L) 
{
    item *AuxV, *AuxA, *startA; 
    while (L->start != NULL)    
    {
        AuxV = L->start;       
        startA = AuxV->prox;   
        while (startA != NULL) 
        {
            AuxA = startA;
            startA = AuxA->prox;
            free(AuxA); 
            AuxA = NULL;
        }
        L->start = AuxV->base;
        free(AuxV); 
        AuxV = NULL;
    }

}

void printCompleteGraph(DynamicList *L) 
{
    item *auxV = L->start; 
    item *auxA;
    printf("Vertices      Arestas\n");
    while (auxV != NULL) 
    {
        auxA = auxV;                             
        printf("   %2d  ------>", auxV->number); 
        if (auxA->prox == NULL)                  
        {
            printf("   NULL\n");
        }
        else 
        {
            auxA = auxV->prox;   
            while (auxA != NULL) 
            {
                printf(" %d ->", auxA->number);
                auxA = auxA->prox; 
            }
            printf(" NULL\n");
        }
        auxV = auxV->base; 
    }
}

int CheckEdge(DynamicList *L, int v1, int v2, int weight) 
{
    
    if (L->quantV == 0 || L->quantV == 1)
    {              
        return -4; 
    }

    if (v1 == v2) 
    {
        return -3; 
    }

    item *aux = L->start; 
    int cont = 0;          
    while (aux != NULL)
    {
        if (aux->number == v1 || aux->number == v2)
        {
            cont++; 
        }
        aux = aux->base; 
    }
    if (cont != 2) 
    {
        return -2; 
    }

    aux = L->start;          
    cont = 0;                 
    while (aux->number != v1) 
    {                         
        aux = aux->base;
    }
    while (aux != NULL) 
    {
        if (aux->number == v2) 
        {
            cont++; 
        }           
        aux = aux->prox;
    }
    if (cont != 0)
    {
        return -1; 
    }
    
    aux = L->start;          
    while (aux->number != v1) 
    {
        aux = aux->base;
    }
    item *novo;                  
    novo = NewEdge(v2, weight); 
    InsertOrderedEdge(L, novo, aux);

    
    aux = L->start;
    while (aux->number != v2)
    {
        aux = aux->base;
    }
    novo = NewEdge(v1, weight);
    InsertOrderedEdge(L, novo, aux);
    return 1; 
}

void InsertOrderedEdge(DynamicList *L, item *C, item *V) 
{
    
    if (V->prox == NULL) 
    {
        V->prox = C;
    }

    else if (C->number < V->prox->number) 
    {
        C->prox = V->prox;
        V->prox = C;
    }

    else 
    {
        item *auxa = V->prox; 
    
        while (V->prox != NULL) 
        {
            V = V->prox;
        }

        if (C->number > V->number) 
        {
            V->prox = C; 
        }

        else 
        {
            item *auxd;        
            auxd = auxa->prox; 
            while (auxd->number < C->number)
            {
                auxa = auxa->prox;
                auxd = auxa->prox;
            }
            C->prox = auxa->prox;
            auxa->prox = C;
        }
    }
}

void AdjacencyMatrix(DynamicList *L) 
{
    int MatrixSize = L->quantV + 1;
    
    int **MatrixAdj = AllocateDynamicMatrix(MatrixSize, MatrixSize); 
    

    item *Aux = L->start;
    int i;

    for (i = 1; i < MatrixSize; i++) 
    {                                   
        MatrixAdj[0][i] = Aux->number;  
        MatrixAdj[i][0] = Aux->number;  
        Aux = Aux->base;               
    }

    item *AuxA;      
    Aux = L->start; 
    int line = 1, column;

    while (Aux != NULL) 
    {
        if (Aux->prox != NULL) 
        {
            AuxA = Aux->prox;    
            while (AuxA != NULL) 
            {
                column = SearchLine(AuxA->number, MatrixSize, MatrixSize, MatrixAdj); 
                MatrixAdj[line][column] = AuxA->weight_aresta;                                  
                AuxA = AuxA->prox;
            }
        }
        Aux = Aux->base;
        line++;
        
    }
    printf("\n  matriz de Adjacencia das celas\n\n");
    ShowMatrix(MatrixSize, MatrixSize, MatrixAdj);
    FreeDynamicMatrix(MatrixSize, MatrixAdj); 
}

int **AllocateDynamicMatrix(int l, int c) 
{
    int i, j;
    int **m = (int **)malloc(l * sizeof(int *)); 

    for (i = 0; i < l; i++)
    {
        m[i] = (int *)malloc(c * sizeof(int)); 
        for (j = 0; j < c; j++)
        {
            m[i][j] = 0; 
        }
    }
    return m; 
}

int SearchLine(int value, int l, int c, int **M) 
{
    int i;
    for (i = 1; i < l; i++)
    {
        if (M[i][0] == value)
        {
            return i; 
        }
    }
    return -1; 
}
void ShowMatrix(int l, int c, int **matrix) 
{
    int i, j;
    for (i = 0; i < l; i++)
    {
        printf("  ");
        for (j = 0; j < c; j++)
        {
            printf("%2d ", matrix[i][j]); 
        }
        printf("\n");
    }
}

void FreeDynamicMatrix(int l, int **M) 
{
    int i;
    for (i = 0; i < l; i++)
    {
        free(M[i]); 
    }
    free(M); 
    M = NULL;
}


int BFS_Verify(DynamicList *L, int Vstart) 
{
    if (L->quantV == 0)
    {
        return -2; 
    }

    item *aux = L->start;
    int cont = 0;
    while (aux != NULL)
    {
        if (aux->number == Vstart)
        {
            cont++;
            break; 
        }
        aux = aux->base; 
    }

    if (cont == 0) 
    {
        return -1; 
    }

    int **retorno; 
    retorno = BFS(L, Vstart);

    FreeDynamicMatrix(3, retorno);
    retorno = NULL;
    return 0;
}

int **BFS(DynamicList *L, int Vstart) 
{
    int arrVerify[10] = {0};
    arrVerify[0] = Vstart;
    int tamGraph = L->quantV; 

    int **matrix = AllocateDynamicMatrix(3, tamGraph); 
    int i;
    for (i = 0; i < tamGraph; i++) 
    {
        if(i == 10){
            matrix[2][i] = 1;
            continue;
        }

        matrix[1][i] = -1; 
        matrix[0][i] = -1; 
        matrix[2][i] = 0;                       
    }

    int position = InformPosition(L, Vstart); 

    matrix[1][position] = -1;
    matrix[0][position] = 0;
    matrix[2][position] = 1;

    DynamicQueue Q; 
    Q.quant = 0;
    Q.start = NULL;
    Q.fim = NULL;
    InsertQueue(&Q, Vstart); 

    int u, v;
    int posu, posv; 
    item *aux;
    while (Q.quant != 0) 
    {
        u = RemoveQueue(&Q);
        posu = InformPosition(L, u);
        aux = EdgesGivenVertex(L, u); 
        while (aux != NULL)                    
        {
            v = aux->number;
            posv = InformPosition(L, v);
            if (matrix[2][posv] == 0 || matrix[2][posv] == 3)
            {
                for(int i = 0; i < 10; i ++){
                    if(arrVerify[i] == 0){
                        arrVerify[i] = aux->number;
                        break;
                    }
                }
                matrix[2][posv] = 3;
                matrix[0][posu] + 1;
                matrix[0][posv] = matrix[0][posu] + 1;
                matrix[1][posv] = u;
                InsertQueue(&Q, v);
            }
            matrix[2][posu] = 2;
            aux = aux->prox;
        }
    }

    aux = L->start;
    printf("\n BUSCA EM LARGURA");
    printf("\n  celas    p   acesso\n");
    for (i = 0; i < tamGraph; i++)
    {
        printf("   %2d     %2d   %2d\n", aux->number, matrix[0][i], matrix[1][i]); 
        aux = aux->base;
    }
    int count = 0;
    for(int i = 0; i < 10; i ++){
        if(arrVerify[i] != 0){
            ++count;
        }
    }
    printf("Total de portões quebrados: %d\n", count);

    return matrix;
}

item *EdgesGivenVertex(DynamicList *L, int Vstart) 
{
    item *Aux = L->start;
    while (Aux->number != Vstart) 
    {
        Aux = Aux->base;
    }
    return Aux->prox; 
}

int InformPosition(DynamicList *L, int Vstart) 
{
    item *aux = L->start;
    int cont = 0;
    
    while (aux->number != Vstart)
    { 
        cont++;
        aux = aux->base;
    }
    return cont; 
}

void InsertQueue(DynamicQueue *F, int value)
{
    
    fila *aux;
    aux = malloc(sizeof(fila)); 
    aux->number = value;        
    aux->prox = NULL;           

    if (F->quant == 0) 
    {
        F->start = aux;
        F->fim = aux;
    }
    else 
    {
        F->fim->prox = aux; 
        F->fim = aux;       
    }
    F->quant++;
}
int RemoveQueue(DynamicQueue *F)
{
    int value;         
    if (F->quant != 0) 
    {
        value = F->start->number; 
        fila *aux;
        if (F->quant == 1) 
        {
            aux = F->start;
            free(aux);
            aux = NULL;
            
            F->quant = 0;
            F->start = NULL;
            F->fim = NULL;
        }
        else 
        {
            aux = F->start;       
            F->start = aux->prox; 
            free(aux);
            aux = NULL;
            F->quant--;
        }
    }
    return value; 
}

int InsertEdge(DynamicList *L, int n) 
{                                           
    
    item *aux;          
    if (L->quantV != 0) 
    {                   
        int i;
        aux = L->start;                
        for (i = 0; i < L->quantV; i++) 
        {
            if (aux->number == n) 
            {
                return -1;
            }
            aux = aux->base; 
        }
    }
    
    aux = NewVertex(n);              
    InsertEdgeOrdely(L, aux); 
    return 1;                       
}

void InsertFirstVertex(DynamicList *L, item *c) 
{
    L->quantV++; 
    c->base = L->start;
    L->start = c; 
}

void InsertEndVertex(DynamicList *L, item *c) 
{
    
    int pos = L->quantV; 
    int cont = 0;
    item *aux = L->start;   
    while (cont < (pos - 1)) 
    {
        aux = aux->base;
        cont++;
    }
    c->base = aux->base;
    aux->base = c;
    L->quantV++;
}

void InsertEdgeOrdely(DynamicList *L, item *C) 
{
    item *aux = L->start; 
    if (L->quantV != 0)    
    {
        while (aux->base != NULL) 
        {
            aux = aux->base;
        }
    } 

    if (L->start == NULL) 
    {
        InsertFirstVertex(L, C);
    }

    else if (C->number < L->start->number) 
    {
        InsertFirstVertex(L, C);
    }

    else if (C->number > aux->number) 
    {
        InsertEndVertex(L, C);
    }

    else 
    {
        item *auxa, *auxd; 
        auxa = L->start;
        auxd = auxa->base;
        while (auxd->number < C->number)
        {
            auxa = auxa->base;
            auxd = auxa->base;
        }
        C->base = auxa->base;
        auxa->base = C;
        L->quantV++;
    }
}

item *NewVertex(int value) 
{
    item *aux;
    aux = malloc(sizeof(item)); 
    aux->number = value;        
    aux->weight_aresta = -1;         
    aux->prox = NULL;           
    aux->base = NULL;          
    return aux;
}

item *NewEdge(int value, int weight) 
{
    item *aux;
    aux = malloc(sizeof(item)); 
    aux->number = value;        
    aux->weight_aresta = weight;      
    aux->prox = NULL;           
    aux->base = NULL;          
    return aux;
}