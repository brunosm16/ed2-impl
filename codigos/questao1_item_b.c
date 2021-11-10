#include <stdio.h>
#include <stdlib.h>

void torre_Hanoi_Recursivo(int discos, char orig, char dest, char temp);
void torre_Hanoi_Iterativo();
void resolve_Torre_Recursivo(int n_discos);
void resolve_Torre_Iterativo(int qtdDiscos);

// Função que realiza a lógica da movimentação de discos
// usando recursão
void torre_Hanoi_Recursivo(int discos, char orig, char dest, char temp)
{
    // Realiza o movimento quando tiver apenas um disco
    if (discos == 1)
    {
        printf("\nMove disco 1 de %c para %c\n", orig, dest);
        return;
    }

    // Move orig(representa A) para dest(representa B)
    // usando um char temporário temp(representa C)
    torre_Hanoi_Recursivo(discos - 1, orig, temp, dest);

    // Move de orig(representa A) para temp(representa C)
    printf("\nMove o disco %d de %c para %c\n", discos, orig, dest);

    // Move de dest(representa B) para temp(representa C)
    // usando orig(representa A) como um char temporário
    torre_Hanoi_Recursivo(discos - 1, temp, dest, orig);
}

void resolve_Torre_Recursivo(int qtdDiscos)
{
    torre_Hanoi_Recursivo(qtdDiscos, 'A', 'C', 'B');
}

void resolve_Torre_Iterativo(int qtdDiscos)
{
    torre_Hanoi_Iterativo();
}

int main()
{
    int qtd_Discos;

    // Obtém o a quantidade de discogs
    printf("Qual a quantidade de discos ? : \n\n");
    scanf("%d", &qtd_Discos);
    printf("---------------------------------\n");

    printf("Siga os passos abaixo para resolver a Torre :\n\n");
    resolve_Torre_Recursivo(qtd_Discos);

    printf("\n-------------------------------------\n");
    printf("\nRESOLVENDO USANDO ITERATIVIDADE\n");

    resolve_Torre_Iterativo(qtd_Discos);

    return 0;
}