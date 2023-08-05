#include <stdio.h>
#include <stdlib.h>

struct GRAFO{
struct VERTICE *head;
};

struct VERTICE{
struct VERTICE *next;
struct ARESTA *aresta;
int chave;
};

struct ARESTA{
struct ARESTA *next;
struct ARESTA *tail;
struct VERTICE *adj;
};

struct NODE{	
int conteudo;
struct NODE *next; 
};

struct PILHA{
struct NODE *head;
};

typedef struct ARESTA ARESTA;
typedef struct VERTICE VERTICE;
typedef struct GRAFO GRAFO;
typedef struct NODE NODE;
typedef struct PILHA PILHA;


GRAFO *cria_grafo();
VERTICE *busca_vertice(GRAFO *g, int chave);
void cria_vertice(GRAFO *g, int chave);
void cria_aresta(GRAFO *g, int chave1, int chave2);
void imprimi_grafo(GRAFO *g);
void imprimi_estruturas_dfs(int v, int *d, int *f, int *p, char *c);

PILHA *cria_pilha();
void push(PILHA *p, int num);
void pop(PILHA *p);
void imprimi_pilha(PILHA *p);

void DFS(GRAFO *g, PILHA *pi, int vertice_inicio, int v, int *d, int *f, int *p, char *c);

int cont_especial = 0;

int main(){

	GRAFO *g = cria_grafo();

	int vertice, aresta, vertice_inicio, a, b;
	scanf("%d %d %d", &vertice, &aresta, &vertice_inicio);


	for(int i = 0; i < vertice+1; ++i)
		cria_vertice(g, i);

	while(scanf("%d %d", &a, &b) != EOF)
		cria_aresta(g, a, b);

	char cor[vertice+1];
	int pred[vertice+1];
	int descobrimento[vertice+1];
	int fechamento[vertice+1];

	for(int i = 0; i < vertice+1; ++i){
		cor[i] = 'w';
		pred[i] = -1;
		descobrimento[i] = -1;
		fechamento[i] = -1;
	}
	
	PILHA *p = cria_pilha();
	DFS(g, p, vertice_inicio, vertice, descobrimento, fechamento, pred, cor);

	return 0;
	
}

GRAFO *cria_grafo(){
	GRAFO *new_graph = (GRAFO*) malloc(sizeof(GRAFO));
	new_graph->head = NULL;

	return new_graph;
}

VERTICE *busca_vertice(GRAFO *g, int chave){
	VERTICE *aux = g->head;
	
	while(aux != NULL && aux->chave != chave)
		aux = aux->next;
	
	return aux;
}

void cria_vertice(GRAFO *g, int chave){
	if(g == NULL)
		return;

	VERTICE *new_vertice = (VERTICE*) malloc(sizeof(VERTICE));
	new_vertice->chave = chave;
	new_vertice->next = g->head;

	g->head = new_vertice;

	return;
}

void cria_aresta(GRAFO *g, int chave1, int chave2){
	if(g == NULL)
		return;

	VERTICE *v1 = busca_vertice(g, chave1);
	if(v1 == NULL)
		return;

	VERTICE *v2 = busca_vertice(g, chave2);
	if(v2 == NULL)
		return;

	ARESTA *new_aresta1  = (ARESTA*) malloc(sizeof(ARESTA));
	ARESTA *new_aresta2  = (ARESTA*) malloc(sizeof(ARESTA));

	new_aresta1->adj = v2;
	new_aresta1->next = NULL;

	new_aresta2->adj = v1;
	new_aresta2->next = NULL;

	if(v1->aresta == NULL){
		v1->aresta = new_aresta1;
		v1->aresta->tail = new_aresta1;		
	} else {
		v1->aresta->tail->next = new_aresta1;
		v1->aresta->tail = new_aresta1;
	}

	if(v2->aresta == NULL){
		v2->aresta = new_aresta2;
		v2->aresta->tail = new_aresta2;
	} else {
		v2->aresta->tail->next = new_aresta2;
		v2->aresta->tail = new_aresta2;
	}

	return;

}

void imprimi_grafo(GRAFO *g){
    if (g == NULL)
    	return;
    
    VERTICE *v_aux = g->head;

    while(v_aux != NULL){
        printf("%d ->", v_aux->chave);

        ARESTA *a_aux = v_aux->aresta;
        
        while(a_aux != NULL){
            printf(" %d", a_aux->adj->chave);
            a_aux = a_aux->next;
        }
        puts("");
 		
 		v_aux = v_aux->next;

    	free(a_aux);
    }
    free(v_aux);
    return;
}

PILHA *cria_pilha(){
	PILHA *new_pilha = (PILHA*) malloc(sizeof(PILHA));
	new_pilha->head = NULL;
	
	return new_pilha;
}

void push(PILHA *p, int num){
	NODE *new_node = (NODE*) malloc(sizeof(NODE));
	new_node->conteudo = num;
	new_node->next =p->head;

	p->head = new_node;
	return;
}

void pop(PILHA *p){
	if(p->head == NULL)
		return;

	NODE *aux = p->head;
	p->head = aux->next;

	free(aux);
	return;
}

void imprimi_pilha(PILHA*p){
	printf("PILHA: ");
	NODE *aux = p->head;
	while (aux != NULL){
		printf("%d -> ", aux->conteudo);
		aux = aux->next;
	}
	printf("NULL\n\n");
	free(aux);
	return;
} 

void imprimi_estruturas_dfs(int v, int *d, int *f, int *p, char *c){
	printf(" v   d  f  p  c\n");
	for(int i = 0; i < v+1; ++i){
		printf("%2d: %2d %2d %2d %2c\n", i, d[i], f[i], p[i], c[i]);
	}
}      
    
void DFS(GRAFO *g, PILHA *pi, int vertice_inicio, int v, int *d, int *f, int *p, char *c){

	if(cont_especial == 0){
		push(pi, vertice_inicio);
		c[vertice_inicio] = 'g';
		p[vertice_inicio] = 0;
		d[vertice_inicio] = cont_especial;
	}

	printf("ITERAÇÃO %d:\n", cont_especial);
	imprimi_estruturas_dfs(v, d, f, p, c);
	printf("\n");

	++cont_especial;

	VERTICE *v_aux = busca_vertice(g, vertice_inicio);
	ARESTA *a_aux = v_aux->aresta;

	while(a_aux != NULL){
    	if(c[a_aux->adj->chave] == 'w'){
	    	push(pi, a_aux->adj->chave);
	        c[a_aux->adj->chave] = 'g';
	        d[a_aux->adj->chave] = cont_especial;
	    	p[a_aux->adj->chave] = vertice_inicio;
	    	DFS(g, pi, a_aux->adj->chave, v, d, f, p, c);
    	}

    	if(a_aux->next == NULL){
    		c[vertice_inicio] = 'b';
    		f[vertice_inicio] = cont_especial;
    		pop(pi);
    	}


	    a_aux = a_aux->next;
    }

    printf("ITERAÇÃO %d:\n", cont_especial);
	imprimi_estruturas_dfs(v, d, f, p, c);
	printf("\n");
    ++cont_especial;
}