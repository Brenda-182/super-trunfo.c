#include <stdio.h>

int main(){

    //Atribuindo valores de variáveis
    //Carta 1
    char estado1 = 'A';
    char codigo1[4] = "A01";
    char nomeCidade1[20] = "São Paulo";
    int populacao1 = 12325000;
    float area1 = 1521.11;
    float pib1 = 699.28;
    int pontosTuristicos1 = 50;
    float densidadePopulacional1 = populacao1 / area1;
    float pibPerCapita1 = (pib1 * 1000000000) / populacao1;

    //Atribuindo valores as váriaveis
    //Carta 2
    char estado2 = 'B';
    char codigo2[4] = "B02";
    char nomeCidade2[20] = "Rio de Janeiro";
    int populacao2 = 6748000;
    float area2 = 1200.25;
    float pib2 = 300.50;
    int pontosTuristicos2 = 30;
    float densidadePopulacional2 = populacao2 / area2;
    float pibPerCapita2 = (pib2 * 1000000000) / populacao2;

    //Exibindo resultados
    //Acrescentando as strings Carta1
    printf("Carta 1: \n");
    printf("Estado:  %c\n", estado1);
    printf("Código: %s\n", codigo1);
    printf("Nome da Cidade: %s\n", nomeCidade1);
    printf("População: %d\n", populacao1);
    printf("Área: %.2f Km²\n", area1);
    printf("Pib: %.2f bilhões de reais\n", pib1);
    printf("Número de Pontos Túristicos: %d\n", pontosTuristicos1);
    printf("Densidade Populacional: %.2f hab/Km² \n", densidadePopulacional1);
    printf("PIB Per Capita: %.2f reais \n", pibPerCapita1);
    printf("\n");
    
     //Acrescentando as strings Carta2
     printf("Carta 2:\n");
    printf("Estado: %c\n", estado2);
    printf("Código: %s\n", codigo2);
    printf("Nome da Cidade: %s\n", nomeCidade2);
    printf("População: %d\n", populacao2);
    printf("Área: %.2f Km²\n", area2);
    printf("Pib: %.2f bilhões de reais\n", pib2);
    printf("Número de Pontos Túristicos: %d\n", pontosTuristicos2);
printf("Densidade Populacional: %.2f hab/Km² \n", densidadePopulacional2);
        printf("PIB Per Capita: %.2f reais \n", pibPerCapita2);

    return 0;
}