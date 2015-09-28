#include <stdio.h>
#include <stdlib.h>

// A struct conjunto possui um vetor que armazena os elementos, e um inteiro que armazena a quantidade
typedef struct conjunto{
    int *vet;
    int n_element;
}CONJUNTO;


//Essa funcao inicializa um conjunto de n elementos
CONJUNTO *inicializar_conj (int n_elementos){

    //Aloco a memoria necessaria para a struct, e em seguida para o vetor
    CONJUNTO *conj = (CONJUNTO*) malloc (sizeof(CONJUNTO));

    conj->n_element = n_elementos;

    if (n_elementos!=0)
        conj->vet = malloc (sizeof(int) * n_elementos);
    else
        conj->vet = NULL;

    return conj;
}

//Essa funcao libera toda a memoria alocada em um conjunto
void liberar_conj (CONJUNTO *conj){
    free (conj->vet);
    free (conj);
}

// Funcao que le via stdin varios elementos, e os insere ordenados em um conjunto
CONJUNTO *receber_conjunto (void){
    int i, k, aux;

    printf ("Entre com o tamanho do conjunto: ");
    scanf ("%d", &aux);

    CONJUNTO *conj = inicializar_conj(aux);

    printf ("\nEntre com os %d elementos do conjunto:\n", aux);

    // O valor de 'i' vai de 0 ate o numero total de elementos do conjunto naquele instante
    for (i=0; i<conj->n_element; i++){
        scanf ("%d", &aux); //Recebe mais um elemento

        //Le os elementos que ja pertencem ao conjunto a partir do ultimo, ate encontrar um que seja menor que "aux"
        for (k=i; k>=0; k--){
            //Caso seja o primeiro, simplesmente atribuo o seu valor a primeira posicao do conjunto
            if (k==0){
                conj->vet[k] = aux;
                break;
            }

            // Enquanto aux for menor que o elemento "k-1", movo 'k-1' para 'k', deslocando-o uma posicao
            if (aux < conj->vet[k-1]){
                conj->vet[k] = conj->vet[k-1];
                continue; //Volto para o inicio do loop for
            }
            //Assim que aux passar a ser >= que o elemento k-1, atribuo 'aux' a posicao 'k'
            conj->vet[k] = aux;
            break; //Finalizo o loop, e volto para receber mais um elemento (A nao ser que ja tenha recebido todos)
        }
    }

    return conj;
}

// Funcao que encontra os pares mais proximos do conjunto
CONJUNTO *pares_proximos (CONJUNTO *conj){

    if (conj->n_element < 2) return NULL; //Para existir um par, e necessario que existam pelo menos 2 elementos

    int i, diff;
    //A variavel "mais_proximo" guarda a diferenca do par mais proximo
    int mais_proximo = conj->vet[conj->n_element-1] - conj->vet[0];
    //O seu valor inicial e o elemento de maior valor do conjunto (o ultimo) menos o valor do menor elemento(o primeiro)

    CONJUNTO *conj_prox = inicializar_conj (2);

    //
    for (i=0; i<conj->n_element-1; i++){
        diff = conj->vet[i+1] - conj->vet[i];

        // Sempre que a diferenca entre o elemento 'i' e o seu proximo for menor que a menor diferenca ja registrada:
        if (diff < mais_proximo){
            mais_proximo = diff; //Essa passa a ser a menor diferenca

            conj_prox->n_element = 2; //Qualquer outro par que ja foi checado e ignorado
            conj_prox->vet = (int*) realloc (conj_prox->vet, sizeof(int) * 2);
            conj_prox->vet[0] = conj->vet[i];
            conj_prox->vet[1] = conj->vet[i+1];

        } else if (diff == mais_proximo){ //Caso a diferenca seja igual, adiciono esse par ao conj_prox
            conj_prox->n_element += 2;
            conj_prox->vet = (int*) realloc (conj_prox->vet, sizeof(int) * conj_prox->n_element);

            conj_prox->vet[conj_prox->n_element-2] = conj->vet[i];
            conj_prox->vet[conj_prox->n_element-1] = conj->vet[i+1];
        }
    }
    return conj_prox;
}

//Funcao que exibe os elementos do conjunto via stdout
void exibir_conjunto (CONJUNTO *conj){
    int i;
    for (i=0; i < conj->n_element; i++){
        printf ("%d ", conj->vet[i]);
    }
    printf ("\n");
}

int main(int argc, char *argv[]){

    CONJUNTO *conj = NULL, *conj_prox;

    if (conj == NULL)
        conj = receber_conjunto();

    conj_prox = pares_proximos(conj);
    printf ("Pares mais proximos: \n");
    exibir_conjunto (conj_prox);
    liberar_conj(conj_prox);


    return 0;
}
