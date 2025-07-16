#include <stdio.h>
int main(){

    //Carta 1 variáveis
    char estado = 'A';
    char codigo[4] = "A01";
    char nomeCidade[20] = "São Paulo";
    int populacao = 12325000
    float area = 1521.11
    float pib = 699,28
    int pontosTuristicos = 50

    //Acrescentando strings
    printf("Estdo: %c\n", estado);
    printf("Código: %c\n", codigo);
    printf("Nome da Cidade: %s\n", nomeCidade);
    printf("População: %d\n", populacao);
    printf("Área: %f.2 Km²\n", area);
    printf("Pib: %f.2 bilhões de reais\n", pib);
    printf("Pontos Túristicos: %d\n", pontosTuristicos);
    return 0;
}