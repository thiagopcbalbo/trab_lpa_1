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
    char op;
    CONJUNTO *conj = NULL, *conj_prox, *conj_unicos, *conj_freq;

    if (conj == NULL)
        conj = receber_conjunto();

    printf ("\nComandos:\n");
    printf ("1 - Verificar os pares mais proximos\n");
    printf ("2 - Verificar os elementos que ocorrem apenas uma vez\n");
    printf ("3 - Verificar os elementos com maior frequencia\n");
    printf ("4 - Exibir os elementos do conjunto\n");
    printf ("5 - Entrar com um novo conjunto\n\n");
    printf ("0 - Finaliza o programa\n");

    while (1){ //Le os comandos ate que a entrada seja '0'
        getchar();
        scanf ("%c", &op);

        switch (op){
            case '0': liberar_conj(conj); exit(0);

            case '1':
                conj_prox = pares_proximos(conj);
                printf ("Pares mais proximos: \n");
                exibir_conjunto (conj_prox);
                liberar_conj(conj_prox);
            break;
            case '2':
                conj_unicos = elemento_unico(conj);
                printf ("Elemento(s) unico(s): \n");
                exibir_conjunto(conj_unicos);
                liberar_conj(conj_unicos);
            break;
            case '3':
                conj_freq = frequencia(conj);
                printf ("Elemento(s) mais frequente(s): \n");
                exibir_conjunto(conj_freq);
                liberar_conj(conj_freq);
            break;
            case '4':
                printf ("Conjunto: \n");
                exibir_conjunto(conj);
            break;
            case '5':
                liberar_conj(conj);
                conj = receber_conjunto();
            break;
            case 'h':
                printf ("\nComandos:\n");
                printf ("1 - Verificar os pares mais proximos\n");
                printf ("2 - Verificar os elementos que ocorrem apenas uma vez\n");
                printf ("3 - Verificar os elementos com maior frequencia\n");
                printf ("4 - Exibir os elementos do conjunto\n");
                printf ("5 - Entrar com um novo conjunto\n\n");
                printf ("0 - Finaliza o programa\n");
            break;
        }

        printf ("\nDigite 'h' para ver a lista de comandos\n");
    }

    return 0;
}

