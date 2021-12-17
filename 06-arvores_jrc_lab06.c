#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int chave;
    struct No *esquerda, *direita, *pai;
}No;

typedef No * pont_no;

//funcao para liberar os nos da arvore
void free_tr(pont_no raiz){
    if(raiz){
        free_tr(raiz->esquerda);
        free_tr(raiz->direita);
        free(raiz);
    }
}


pont_no criar_arvore(pont_no raiz){
    if(raiz == NULL)
        return NULL;
    else{
        free_tr(raiz);
        return NULL;
    }
}

//funcao para buscar um elemento com uma determinada chave na arvore
pont_no buscar(pont_no raiz, int chave){
    if(raiz == NULL || raiz->chave == chave)
        return raiz;
    if(chave < raiz->chave)
        return buscar(raiz->esquerda, chave);
    else
        return buscar(raiz->direita, chave);
}

//funcao para inserir um novo no na arvore
void inserir(pont_no *raiz, int num){
    pont_no aux = *raiz;
    pont_no pai = NULL;
    while(aux){
        if(num < aux->chave)
            raiz = &aux->esquerda;
        else
            raiz = &aux->direita;
        pai = aux;
        aux = *raiz;
    }
    aux = malloc(sizeof(No));
    aux->pai = pai;
    aux->chave = num;
    aux->esquerda = NULL;
    aux->direita = NULL;
    *raiz = aux;
}

//funcao que retorna um ponteiro para o elemento de menor chave da arvore
pont_no minimo(pont_no raiz){
    if(raiz == NULL)
        return NULL;
    while(raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz;
}

//funcao que retorna um ponteiro para o elemento de maior chave da arvore
pont_no maximo(pont_no raiz){
    if(raiz == NULL)
        return NULL;
    while(raiz->direita != NULL)
        raiz = raiz->direita;
    return raiz;
}

//funcao para encontrar o sucessor de um elemento, quando a subarvore na sua
//direita eh nula
pont_no ancestral_raiz_dir(pont_no x){
    if(x == NULL)
        return NULL;
    if(x->pai == NULL || x->pai->esquerda == x)
        return x->pai;
    else
        return ancestral_raiz_dir(x->pai);
}

//funcao para encontrar o sucessor de um no x da arvore
pont_no sucessor(pont_no x){
    if(x->direita != NULL)
        return minimo(x->direita);
    else
        return ancestral_raiz_dir(x);
}

//funcao para encontrar o predecessor de um elemento, quando a subarvore na sua
//esquerda eh nula
pont_no ancestral_raiz_esq(pont_no x){
    if(x == NULL)
        return NULL;
    if(x->pai == NULL || x->pai->direita == x)
        return x->pai;
    else
        return ancestral_raiz_esq(x->pai);
}

//funcao para encontrar o predecessor de um no x da arvore
pont_no predecessor(pont_no x){
    if(x->esquerda != NULL)
        return maximo(x->esquerda);
    else
        return ancestral_raiz_esq(x);
}

//funcao para remover um no da arvore que contenha 2 filhos
//nesse caso, o substituimos pelo seu sucessor
void remover2_sucessor(pont_no raiz){
    pont_no t = raiz->direita;
    pont_no pai = raiz;
    while(t->esquerda != NULL){
        pai = t;
        t = t->esquerda;
    }
    if (pai->esquerda == t)
        pai->esquerda = t->direita;
    else
        pai->direita = t->direita;
    raiz->chave = t->chave;
}

//funcao para remover um no da arvore
pont_no remover_elem(pont_no raiz, int chave){
    if(raiz == NULL)
        return NULL;
    if(chave < raiz->chave)
        raiz->esquerda = remover_elem(raiz->esquerda, chave);
    else if (chave > raiz->chave)
        raiz->direita = remover_elem(raiz->direita, chave);
    else if (raiz->esquerda == NULL)
        return raiz->direita;
    else if (raiz->direita == NULL)
        return raiz->esquerda;
    else
        remover2_sucessor(raiz);
    return raiz;
}

//funcao para contar a quantidade de nos na arvore
int qtd_nos(pont_no raiz){
    if(raiz == NULL)
        return 0;
    else
        return 1 + qtd_nos(raiz->direita) + qtd_nos(raiz->esquerda);
}

//funcao para calcular a qtde de folhas
int qtd_folhas(pont_no raiz){
    if(raiz == NULL)
        return 0;
    else if(raiz->esquerda == NULL && raiz->direita == NULL)
        return 1;
    else
        return qtd_folhas(raiz->esquerda) + qtd_folhas(raiz->direita);
}

//funcao para calcular a altura da arvore
int qtd_alt(pont_no raiz){
    int esquerda;
    int direita;

    if(raiz == NULL)
        return -1;
    else{
        esquerda = qtd_alt(raiz->esquerda);
        direita = qtd_alt(raiz->direita);
        if(esquerda > direita)
            return esquerda + 1;
        else
            return direita + 1;
    }
}

//funcao para imprimir elementos da arvore em pre-ordem
void pre_ordem(pont_no raiz){
    if(raiz){
        printf("%d ", raiz->chave);
        pre_ordem(raiz->esquerda);
        pre_ordem(raiz->direita);
    }
}

//funcao para imprimir elementos da arvore em ordem
void em_ordem(pont_no raiz){
    if(raiz){
        em_ordem(raiz->esquerda);
        printf("%d ", raiz->chave);
        em_ordem(raiz->direita);
    }
}

//funcao para imprimir elementos da arvore em pos-ordem
void pos_ordem(pont_no raiz){
    if(raiz){
        pos_ordem(raiz->esquerda);
        pos_ordem(raiz->direita);
        //printf(" ");
        printf("%d ", raiz->chave);
    }    
}

int main(){
    //inicializando a arvore
    pont_no raiz = NULL;

    char comando [20];

    //ponteiros para no (auxiliares)
    pont_no busc, max, suc, pre;

    //laco principal do programa
    while(scanf("%s", comando)){

        if(strcmp(comando, "criar") == 0){
            raiz = criar_arvore(raiz);
        }

        if(strcmp(comando, "buscar") == 0){
            int bu;
            scanf("%d", &bu);
            busc = buscar(raiz, bu);
            if(busc)
                printf("%d esta na arvore\n", bu);
            else
                printf("%d nao esta na arvore\n", bu);
        }

        if(strcmp(comando, "inserir") == 0){
            pont_no ctz;
            int insere;
            scanf("%d", &insere);
            ctz = buscar(raiz, insere);
            if(ctz == NULL)
                inserir(&raiz, insere);
        }

        if(strcmp(comando, "remover") == 0){
            int remov;
            scanf("%d", &remov);
            raiz = remover_elem(raiz, remov);
        }

        if(strcmp(comando, "info") == 0){
            if(raiz)
            printf("nos: %d, folhas: %d, altura: %d\n", qtd_nos(raiz), qtd_folhas(raiz), qtd_alt(raiz));
            else
            printf("nos: 0, folhas: 0, altura: 0\n");
        }

        if(strcmp(comando, "sucessor") == 0){
            pont_no suc2;
            int su;
            scanf("%d", &su);
            suc = buscar(raiz, su);
            if(suc){
                suc2 = sucessor(suc);
                    if(suc2)
                        printf("sucessor de %d: %d\n", su, suc2->chave);
                    else
                        printf("nao ha sucessor de %d\n", su);
            }   
            else
                printf("nao ha sucessor de %d\n", su);
        }

        if(strcmp(comando, "predecessor") == 0){
            pont_no pre2;
            int pr;
            scanf("%d", &pr);
            pre = buscar(raiz, pr);
            if(pre){
                pre2 = predecessor(pre);
                    if(pre2)
                        printf("predecessor de %d: %d\n", pr, pre2->chave);
                    else
                        printf("nao ha predecessor de %d\n", pr);
            }
            else
                printf("nao ha predecessor de %d\n", pr);
        }

        if(strcmp(comando, "maximo") == 0){
            if(raiz == NULL)
                printf("arvore vazia\n");
            else{
            max = maximo(raiz);
            printf("maximo: %d\n", max->chave);
            }
        }

        if(strcmp(comando, "minimo") == 0){
            if(raiz == NULL)
                printf("arvore vazia\n");
            else{
            pont_no min = minimo(raiz);
            printf("minimo: %d\n", min->chave);
            }
        }

        if(strcmp(comando, "em-ordem") == 0){
            if(raiz == NULL)
                printf("arvore vazia\n");
            else{
            printf("em-ordem: ");
            em_ordem(raiz);
            printf("\n");
            }
        }

        if(strcmp(comando, "pre-ordem") == 0){
            if(raiz == NULL)
                printf("arvore vazia\n");
            else{
            printf("pre-ordem: ");
            pre_ordem(raiz);
            printf("\n");
            }
        }

        if(strcmp(comando, "pos-ordem") == 0){
            if(raiz == NULL)
                printf("arvore vazia\n");
            else{
            printf("pos-ordem: ");
            pos_ordem(raiz);
            printf("\n");
            }
        }

        if(strcmp(comando, "terminar") == 0){
            free_tr(raiz);
            break;
        }
        
    }
    return 0;
}