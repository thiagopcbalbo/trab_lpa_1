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

//Funcao que retorna o(s) elemento(s) mais frequente(s) do conjunto
CONJUNTO *frequencia (CONJUNTO *conj){
    int i, count, maior_freq = 0;
    CONJUNTO *conj_freq = inicializar_conj(0);

    for (i=0; i < conj->n_element; i++){
        count =1;
        //Count recebe o valor da frequencia de cada elemento
        while (i < conj->n_element-1 && conj->vet[i] == conj->vet[i+1]){
            count++;
            i++;
        }
        //Se o count desse elemento for maior que a maior frequencia ja registrada:
        if (count > maior_freq){
            conj_freq->vet = (int*)realloc (conj_freq->vet, sizeof(int));
            conj_freq->vet[0] = conj->vet[i];
            conj_freq->n_element = 1;

            maior_freq = count;
        } else if (count == maior_freq){ //Se o count desse elemento for maior que a maior frequencia ja registrada:
            conj_freq->n_element ++;
            conj_freq->vet = (int*)realloc (conj_freq->vet, sizeof(int) * conj_freq->n_element);
            conj_freq->vet[conj_freq->n_element-1] = conj->vet[i];
        }
    }

    return conj_freq;
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

    CONJUNTO *conj = NULL, *conj_freq;

    if (conj == NULL)
        conj = receber_conjunto();

    conj_freq = frequencia(conj);
    printf ("Elemento(s) mais frequente(s): \n");
    exibir_conjunto(conj_freq);
    liberar_conj(conj_freq);

    return 0;
}
