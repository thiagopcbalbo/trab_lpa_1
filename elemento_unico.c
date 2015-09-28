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

// Funcao que determina quais elementos ocorrem apenas 1 vez em um dado conjunto
CONJUNTO *elemento_unico (CONJUNTO *conj){
    int i, unico;

    CONJUNTO *conj_unicos = inicializar_conj(0);

    //Percorro todo o vetor de elementos
    for (i=1; i< conj->n_element; i++){
        unico = 1;

        while (conj->vet[i] == conj->vet[i-1]){
            i++;
            //Se entrar nesse loop, os valores checados agora sao iguais, e portanto nao sao unicos
            if (unico==1) unico=0;
        }
        // Se nao tiver entrado no loop, o elemento 'i-1' e unico
        if (unico == 1){

            if (i != conj->n_element-1){ //Se o 'i' nao for o ultimo elemento do conjunto:
                //Nesse caso, a unica certeza sera que 'i-1' e unico. Ja 'i' devera ser testado na proxima iteracao
                conj_unicos->vet = (int*) realloc (conj_unicos->vet, (sizeof(int) * (1 + conj_unicos->n_element) ));
                conj_unicos->vet[conj_unicos->n_element] = conj->vet[i-1];
                conj_unicos->n_element ++;
            } else {
                //Se 'i' for o ultimo elemento do conjunto:
                //Nesse caso, tanto 'i' quanto 'i-1' sao unicos!
                conj_unicos->vet = (int*) realloc (conj_unicos->vet, (sizeof(int) * (2 + conj_unicos->n_element) ));
                conj_unicos->vet[conj_unicos->n_element] = conj->vet[i-1];
                conj_unicos->vet[conj_unicos->n_element+1] = conj->vet[i];
                conj_unicos->n_element +=2;
            }
        }

    }
    return conj_unicos;
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

    CONJUNTO *conj = NULL, *conj_unicos;

    if (conj == NULL)
        conj = receber_conjunto();

    conj_unicos = elemento_unico(conj);
    printf ("Elemento(s) unico(s): \n");
    exibir_conjunto(conj_unicos);
    liberar_conj(conj_unicos);
    return 0;
}
