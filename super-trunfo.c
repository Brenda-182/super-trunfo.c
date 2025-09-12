#include <stdio.h>
#include <string.h>

int main(void) {
    // =========================
    // Cartas já cadastradas
    // =========================

    // *** Carta 1 ***
    char estado1 = 'A';
    char codigo1[4] = "A01";
    char nomeCidade1[20] = "Sao Paulo"; // evitar acentos no fonte puro C
    unsigned long int populacao1 = 12325000UL;
    float area1 = 1521.11f;                 // km²
    float pib1  = 699.28f;                  // bilhões
    int pontosTuristicos1 = 50;
    float densidade1 = (float)populacao1 / area1;                 // hab/km²

    // *** Carta 2 ***
    char estado2 = 'B';
    char codigo2[4] = "B02";
    char nomeCidade2[20] = "Rio de Janeiro";
    unsigned long int populacao2 = 6748000UL;
    float area2 = 1200.25f;                 // km²
    float pib2  = 300.50f;                  // bilhões
    int pontosTuristicos2 = 30;
    float densidade2 = (float)populacao2 / area2;                 // hab/km²

    // (Opcional) PIB per capita e super poder (não usados na comparação deste nível)
    float perCapita1 = (pib1 * 1000000000.0f) / (float)populacao1;
    float perCapita2 = (pib2 * 1000000000.0f) / (float)populacao2;
    float superPoder1 = (float)populacao1 + area1 + pib1 + (float)pontosTuristicos1 + perCapita1 - densidade1;
    float superPoder2 = (float)populacao2 + area2 + pib2 + (float)pontosTuristicos2 + perCapita2 - densidade2;

    // =========================
    // Exibição das cartas
    // =========================
    printf("=== CARTAS CADASTRADAS ===\n\n");

    printf("Carta 1:\n");
    printf("  Estado: %c | Codigo: %s | Cidade: %s\n", estado1, codigo1, nomeCidade1);
    printf("  Populacao: %lu\n", populacao1);
    printf("  Area: %.2f km^2\n", area1);
    printf("  PIB: %.2f bilhoes R$\n", pib1);
    printf("  Pontos Turisticos: %d\n", pontosTuristicos1);
    printf("  Densidade: %.2f hab/km^2\n", densidade1);
    printf("  (PIB per capita: %.2f | Super Poder: %.2f)\n\n", perCapita1, superPoder1);

    printf("Carta 2:\n");
    printf("  Estado: %c | Codigo: %s | Cidade: %s\n", estado2, codigo2, nomeCidade2);
    printf("  Populacao: %lu\n", populacao2);
    printf("  Area: %.2f km^2\n", area2);
    printf("  PIB: %.2f bilhoes R$\n", pib2);
    printf("  Pontos Turisticos: %d\n", pontosTuristicos2);
    printf("  Densidade: %.2f hab/km^2\n", densidade2);
    printf("  (PIB per capita: %.2f | Super Poder: %.2f)\n\n", perCapita2, superPoder2);

    // =========================
    // Menu interativo
    // =========================
    int opcao;
    do {
        printf("\n=== MENU DE COMPARACAO ===\n");
        printf("Escolha o atributo para comparar Carta 1 (%s) vs Carta 2 (%s):\n", nomeCidade1, nomeCidade2);
        printf("  1) Populacao (maior vence)\n");
        printf("  2) Area (maior vence)\n");
        printf("  3) PIB (maior vence)\n");
        printf("  4) Pontos Turisticos (maior vence)\n");
        printf("  5) Densidade Demografica (MENOR vence)\n");
        printf("  6) Mostrar nomes apenas (sem comparacao)\n");
        printf("  0) Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            // limpeza de entrada inválida
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { /* descarta */ }
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        printf("\n");

        switch (opcao) {
            case 1: { // População (maior vence)
                printf("=== Comparacao por POPULACAO ===\n");
                printf("%s: %lu | %s: %lu\n", nomeCidade1, populacao1, nomeCidade2, populacao2);

                if (populacao1 > populacao2) {
                    printf("Vencedora: Carta 1 (%s)\n", nomeCidade1);
                } else if (populacao2 > populacao1) {
                    printf("Vencedora: Carta 2 (%s)\n", nomeCidade2);
                } else {
                    printf("Empate!\n");
                }
                break;
            }

            case 2: { // Área (maior vence)
                printf("=== Comparacao por AREA ===\n");
                printf("%s: %.2f km^2 | %s: %.2f km^2\n", nomeCidade1, area1, nomeCidade2, area2);

                if (area1 > area2) {
                    printf("Vencedora: Carta 1 (%s)\n", nomeCidade1);
                } else if (area2 > area1) {
                    printf("Vencedora: Carta 2 (%s)\n", nomeCidade2);
                } else {
                    printf("Empate!\n");
                }
                break;
            }

            case 3: { // PIB (maior vence)
                printf("=== Comparacao por PIB ===\n");
                printf("%s: %.2f bilhoes | %s: %.2f bilhoes\n", nomeCidade1, pib1, nomeCidade2, pib2);

                if (pib1 > pib2) {
                    printf("Vencedora: Carta 1 (%s)\n", nomeCidade1);
                } else if (pib2 > pib1) {
                    printf("Vencedora: Carta 2 (%s)\n", nomeCidade2);
                } else {
                    printf("Empate!\n");
                }
                break;
            }

            case 4: { // Pontos turísticos (maior vence)
                printf("=== Comparacao por PONTOS TURISTICOS ===\n");
                printf("%s: %d | %s: %d\n", nomeCidade1, pontosTuristicos1, nomeCidade2, pontosTuristicos2);

                if (pontosTuristicos1 > pontosTuristicos2) {
                    printf("Vencedora: Carta 1 (%s)\n", nomeCidade1);
                } else if (pontosTuristicos2 > pontosTuristicos1) {
                    printf("Vencedora: Carta 2 (%s)\n", nomeCidade2);
                } else {
                    printf("Empate!\n");
                }
                break;
            }

            case 5: { // Densidade demográfica (MENOR vence)
                printf("=== Comparacao por DENSIDADE DEMOGRAFICA (menor vence) ===\n");
                printf("%s: %.2f hab/km^2 | %s: %.2f hab/km^2\n", nomeCidade1, densidade1, nomeCidade2, densidade2);

                if (densidade1 < densidade2) {
                    printf("Vencedora: Carta 1 (%s)\n", nomeCidade1);
                } else if (densidade2 < densidade1) {
                    printf("Vencedora: Carta 2 (%s)\n", nomeCidade2);
                } else {
                    printf("Empate!\n");
                }
                break;
            }

            case 6: { // Nome do país/cidade (exibir somente)
                printf("=== Informacoes ===\n");
                printf("Carta 1: %s (Estado %c, Codigo %s)\n", nomeCidade1, estado1, codigo1);
                printf("Carta 2: %s (Estado %c, Codigo %s)\n", nomeCidade2, estado2, codigo2);
                printf("Obs.: Nome e usado apenas para exibicao, nao ha comparacao direta.\n");
                break;
            }

            case 0:
                printf("Saindo...\n");
                break;

            default:
                // Segurança/usabilidade: opção inválida
                printf("Opcao inexistente. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}