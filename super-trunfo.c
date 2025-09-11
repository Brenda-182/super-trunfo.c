#include <stdio.h>
#include <string.h>

int main(){

    //Atribuindo valores de variáveis
    //***Carta 1***
    char estado1 = 'A';
    char codigo1[4] = "A01";
    char nomeCidade1[20] = "São Paulo";
    unsigned long int populacao1 = 12325000;
    float area1 = 1521.11;
    float pib1 = 699.28;
    int pontosTuristicos1 = 50;
    float densidade1 = populacao1 / area1;
    float perCapita1 = (pib1 * 1000000000) / populacao1;
    float superPoder1 = populacao1 + area1 + pib1 + pontosTuristicos1 + perCapita1 - densidade1;

    //Atribuindo valores as váriaveis
    //***Carta 2***
    char estado2 = 'B';
    char codigo2[4] = "B02";
    char nomeCidade2[20] = "Rio de Janeiro";
    unsigned long int populacao2 = 6748000;
    float area2 = 1200.25;
    float pib2 = 300.50;
    int pontosTuristicos2 = 30;
    float densidade2 = populacao2 / area2;
    float perCapita2 = (pib2 * 1000000000) / populacao2;
    float superPoder2 = populacao2 + area2 + pib2 + pontosTuristicos2 + perCapita2 - densidade2;


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
    printf("Densidade Populacional: %.2f hab/Km² \n", densidade1);
    printf("PIB Per Capita: %.2f reais \n", perCapita1);
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
    printf("Densidade Populacional: %.2f hab/Km² \n", densidade2);
    printf("PIB Per Capita: %.2f reais \n", perCapita2);
    printf("\n");

//Comparando atributos
printf("### Comparação de Cartas ###\n");
printf("\n");
if(populacao1 > populacao2){
    printf("População: Carta 1 venceu! (1)\n");
}else{
    printf("População: Cartar 2 venceu! (0)\n");
}
if(area1 > area2){
    printf("Área: Carta 1 venceu! (1)\n");
}else{
    printf("Área: Cartar 2 venceu! (0)\n");
}
if(pib1 > pib2){
    printf("PIB: Carta 1 venceu! (1)\n");
}else{
    printf("PIB: Cartar 2 venceu! (0)\n");
}
if(pontosTuristicos1 > pontosTuristicos2){
    printf("Pontos Turísticos: Carta 1 venceu! (1)\n");
}else{
    printf("Pontos Turísticos: Cartar 2 venceu! (0)\n");
}
if(densidade1 < densidade2){
    printf("Densidade Populacional: Carta 1 venceu! (1)\n");
}else{
    printf("Densidade Populacional: Cartar 2 venceu! (0)\n");
}
if(perCapita1 > perCapita2){
    printf("PIB per Capita: Carta 1 venceu! (1)\n");
}else{
    printf("PIB per Capita: Cartar 2 venceu! (0)\n");
}
if(superPoder1 > superPoder2){
    printf("Super poder: Carta 1 venceu! (1)\n");
}else{
    printf("Super Poder: Cartar 2 venceu! (0)\n");
}

    return 0;
}