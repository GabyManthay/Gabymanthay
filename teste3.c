#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX 100

// Declaração das struct Lanche e Pedido.
struct Lanche {
    char nomeLanche[MAX];
    float preco; 
    char ingredientes[MAX];
};
typedef struct Lanche Lanche;

struct Pedido{
    int numeroPedido;
    char nomeCliente[MAX];
    int qtdeLanche;
    struct Lanche lanche;
};
typedef struct Pedido Pedido;

// Função printf.
void imprimirPedido(struct Pedido pedido) {
    printf("Número do pedido: %d\n", pedido.numeroPedido);
    printf("Nome do cliente: %s\n", pedido.nomeCliente);
    printf("Quantidade do lanche: %d\n", pedido.qtdeLanche);
    printf("Nome do lanche: %s\n", pedido.lanche.nomeLanche);
    printf("Preço do lanche: %.2f\n", pedido.lanche.preco);
    printf("Ingredientes do lanche: %s\n", pedido.lanche.ingredientes);
}

// Função para pesquisar por número do pedido.
void pesqNumero(struct Pedido pedidos[], int tamanho, int numeroPedido){
    for (int i = 0; i < tamanho; i++) {
        if (pedidos[i].numeroPedido == numeroPedido) {
            imprimirPedido(pedidos[i]);
            return;
        }
    }
    printf("Pedido não encontrado.\n");
}

// Função para inserir pedido.
void inserirPedido(Pedido pedidos[], int *tamanho, int numeroPedido){
    pesqNumero(pedidos, *tamanho, numeroPedido);

    if (pedidos[*tamanho - 1].numeroPedido == numeroPedido) {
        printf("Número de pedido já existe. O pedido não será inserido.\n");
    } else {
        Pedido novoPedido;
        novoPedido.numeroPedido = numeroPedido;

        printf("\n\t-----DADOS DO CLIENTE-----\n");
        printf("Digite o nome do cliente: ");
        scanf(" %99[^\n]s", novoPedido.nomeCliente);
        printf("Digite a quantidade do pedido: ");
        scanf("%d", &novoPedido.qtdeLanche);
        printf("\n---------------------------------------------------\n");
        printf("\n\t-----DADOS DO LANCHE------\n");
        printf("Digite o nome do lanche: ");
        scanf(" %99[^\n]s", novoPedido.lanche.nomeLanche);
        printf("Digite o preço do lanche: ");
        scanf("%f", &novoPedido.lanche.preco); 
        printf("Digite os ingredientes do lanche: ");
        scanf(" %99[^\n]s", novoPedido.lanche.ingredientes);

        pedidos[*tamanho] = novoPedido;
        (*tamanho)++;
        printf("Pedido inserido com sucesso!\n");
    }
}

// Função para pesquisar por nome.
void pesqNome(struct Pedido pedidos[], int tamanho, const char *nomeCliente){
    int encontrado = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(pedidos[i].nomeCliente, nomeCliente) == 0) {
            imprimirPedido(pedidos[i]);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("Pedidos não encontrados para o cliente %s.\n", nomeCliente);
    }
}

// Função para atualizar quantidade.
void atualizarQtde(struct Pedido pedidos[], int tamanho, int numeroPedido, int novaQuantidade) {
    pesqNumero(pedidos, tamanho, numeroPedido);

    int encontrado = 0;
    for (int i = 0; i < tamanho; i++) {
        if (pedidos[i].numeroPedido == numeroPedido) {
            pedidos[i].qtdeLanche = novaQuantidade;
            printf("Quantidade atualizada com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Pedido não encontrado.\n");
    }
}

// Função para pesquisar qual é o pedido com o maior valor. 
void maiorValor(struct Pedido pedidos[], int tamanho) {
    float maxValor = 0;
    int idxMaxValor = -1;

    for (int i = 0; i < tamanho; i++) {
        float valorPedido = pedidos[i].lanche.preco * pedidos[i].qtdeLanche;
        if (valorPedido > maxValor) {
            maxValor = valorPedido;
            idxMaxValor = i;
        }
    }

    if (idxMaxValor != -1) {
        printf("Pedido com o maior valor:\n");
        printf("Número do pedido: %d\n", pedidos[idxMaxValor].numeroPedido);
        printf("Nome do cliente: %s\n", pedidos[idxMaxValor].nomeCliente);
        printf("Quantidade do lanche: %d\n", pedidos[idxMaxValor].qtdeLanche);
        printf("Nome do lanche: %s\n", pedidos[idxMaxValor].lanche.nomeLanche);
        printf("Preço do lanche: %.2f\n", pedidos[idxMaxValor].lanche.preco);
        printf("Ingredientes do lanche: %s\n", pedidos[idxMaxValor].lanche.ingredientes);
    } else {
        printf("Nenhum pedido encontrado.\n");
    }
}

// Função para pedir o número do pedido e excluir do vetor.
void excluirPedido(struct Pedido pedidos[], int *tamanho, int numeroPedido) {
    pesqNumero(pedidos, *tamanho, numeroPedido);

    int encontrado = 0;
    for (int i = 0; i < *tamanho; i++) {
        if (pedidos[i].numeroPedido == numeroPedido) {
            for (int j = i; j < (*tamanho - 1); j++) {
                pedidos[j] = pedidos[j + 1];
            }
            (*tamanho)--;
            printf("Pedido excluído com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Pedido não encontrado.\n");
    }
}

// Função para mostrar todos os pedidos e seu valor total.
void listar(struct Pedido pedidos[], int tamanho){
    float valorTotal = 0;

    printf("Lista de pedidos:\n");
    for (int i = 0; i < tamanho; i++) {
        imprimirPedido(pedidos[i]);

        float valorPedido = pedidos[i].lanche.preco * pedidos[i].qtdeLanche;
        printf("Valor total do pedido: %.2f\n", valorPedido);
        valorTotal = valorTotal + valorPedido;
        printf("\n");
    }
    printf("Valor total de todos os pedidos: %.2f\n", valorTotal);
}

int menu() {
	int op;
	// system("@cls||clear");  // LIMPA A TELA
	printf("\n\nSISTEMA DE LANCHONETE\n\n");
	printf("1 - Inserir\n");
	printf("2 - Pesquisar por número\n");
	printf("3 - Pesquisar por nome\n");
	printf("4 - Atualizar\n");
	printf("5 - Maior\n");
	printf("6 - Excluir\n");
	printf("7 - Listar\n");
	printf("0 - Sair\n");
	do {
		printf("Escolha sua opção: ");
		scanf(" %d", &op);
	} while(op < 0 || op > 7);
	return op;
}

int main() {
    SetConsoleOutputCP(65001);
    char nomeCliente[100];
    struct Pedido pedidos[100];
    int tamanhoPedidos = 0;
    int numeroPedido, novaQuantidade;
    int op;
    do {
		op = menu();
        switch (op) {
            case 1: {
                printf("Número do pedido: ");
                scanf("%d", &numeroPedido);
                inserirPedido(pedidos, &tamanhoPedidos, numeroPedido);
                break;
            }
            case 2: {
                printf("Número do pedido: ");
                scanf("%d", &numeroPedido);
                pesqNumero(pedidos, tamanhoPedidos, numeroPedido);
                break;
            }
            case 3: {
                printf("Nome do cliente: ");
                scanf(" %[^\n]", nomeCliente);
                pesqNome(pedidos, tamanhoPedidos, nomeCliente);
                break;
            }
            case 4: {
                printf("Número do pedido: ");
                scanf("%d", &numeroPedido);
                printf("Nova quantidade do lanche: ");
                scanf("%d", &novaQuantidade);
                atualizarQtde(pedidos, tamanhoPedidos, numeroPedido, novaQuantidade);
                break;
            }
            case 5:
                maiorValor(pedidos, tamanhoPedidos);
                break;
            case 6: {
                printf("Número do pedido a ser excluído: ");
                scanf("%d", &numeroPedido);
                excluirPedido(pedidos, &tamanhoPedidos, numeroPedido);
                break;
            }
            case 7:
                listar(pedidos, tamanhoPedidos);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);

    return 0;
}