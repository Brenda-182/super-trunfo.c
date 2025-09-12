#include <stdio.h>
#include <string.h>

/*
  Super Trunfo — Comparação por 2 atributos (nível avançado)
  - Menus dinâmicos via switch (o 2º menu oculta o atributo já escolhido)
  - Regras:
      * Geral: maior valor vence
      * Densidade Demográfica: menor valor vence
  - Após comparar os dois atributos individualmente, soma os dois valores:
      * Maior soma vence a rodada
  - Trata empates e entradas inválidas
  - Loop para repetir rodadas até o usuário decidir sair
*/

// -----------------------------------------------------------------------------
// Modelo de dados de uma carta
// -----------------------------------------------------------------------------
typedef struct {
    char estado;                    // Ex.: 'A'
    char codigo[4];                 // Ex.: "A01" (3 chars + '\0')
    char nomeCidadeOuPais[50];      // Ex.: "Sao Paulo"
    unsigned long int populacao;    // População total
    float areaKm2;                  // Área em km^2
    float pibBilhoes;               // PIB em bilhões de R$
    int quantidadePontosTuristicos; // Número de pontos turísticos

    // Atributos derivados (calculados a partir dos campos acima)
    float densidadeDemografica;     // hab/km^2 = populacao / areaKm2
    float pibPerCapita;             // R$/hab = (pibBilhoes * 1e9) / populacao
} CartaCidade;

// -----------------------------------------------------------------------------
// Cálculo de métricas derivadas para uma carta
// -----------------------------------------------------------------------------
static void calcular_metricas_derivadas(CartaCidade *carta) {
    // Evita divisão por zero ao calcular a densidade
    carta->densidadeDemografica = (carta->areaKm2 > 0.0f)
        ? (float)carta->populacao / carta->areaKm2
        : 0.0f;

    // Converte PIB de bilhões para reais antes do cálculo do per capita
    carta->pibPerCapita = (carta->populacao > 0UL)
        ? (carta->pibBilhoes * 1000000000.0f) / (float)carta->populacao
        : 0.0f;
}

// -----------------------------------------------------------------------------
// Enum para mapear os atributos escolhíveis no menu
// -----------------------------------------------------------------------------
enum AtributoComparavel {
    ATR_POPULACAO = 1,
    ATR_AREA_KM2,
    ATR_PIB_BILHOES,
    ATR_PONTOS_TURISTICOS,
    ATR_DENSIDADE_DEMOGRAFICA,
    ATR_PIB_PER_CAPITA
};

// Nome amigável para exibir no console
static const char* nome_do_atributo(enum AtributoComparavel atributo) {
    switch (atributo) {
        case ATR_POPULACAO:           return "Populacao";
        case ATR_AREA_KM2:            return "Area (km^2)";
        case ATR_PIB_BILHOES:         return "PIB (bilhoes R$)";
        case ATR_PONTOS_TURISTICOS:   return "Pontos Turisticos";
        case ATR_DENSIDADE_DEMOGRAFICA:return "Densidade (hab/km^2)";
        case ATR_PIB_PER_CAPITA:      return "PIB per Capita (R$/hab)";
        default:                      return "Atributo Desconhecido";
    }
}

// -----------------------------------------------------------------------------
// Extrai um valor numérico (double) do atributo escolhido, para comparar e somar
// -----------------------------------------------------------------------------
static double valor_do_atributo(const CartaCidade *carta, enum AtributoComparavel atributo) {
    switch (atributo) {
        case ATR_POPULACAO:            return (double)carta->populacao;
        case ATR_AREA_KM2:             return (double)carta->areaKm2;
        case ATR_PIB_BILHOES:          return (double)carta->pibBilhoes;
        case ATR_PONTOS_TURISTICOS:    return (double)carta->quantidadePontosTuristicos;
        case ATR_DENSIDADE_DEMOGRAFICA:return (double)carta->densidadeDemografica;
        case ATR_PIB_PER_CAPITA:       return (double)carta->pibPerCapita;
        default:                       return 0.0;
    }
}

// -----------------------------------------------------------------------------
// Imprime um valor com formatação adequada ao tipo do atributo
// (apenas para exibição bonita na tela)
// -----------------------------------------------------------------------------
static void imprimir_valor_formatado(const CartaCidade *carta, enum AtributoComparavel atributo) {
    switch (atributo) {
        case ATR_POPULACAO:            printf("%lu", carta->populacao); break;
        case ATR_AREA_KM2:             printf("%.2f", carta->areaKm2); break;
        case ATR_PIB_BILHOES:          printf("%.2f", carta->pibBilhoes); break;
        case ATR_PONTOS_TURISTICOS:    printf("%d", carta->quantidadePontosTuristicos); break;
        case ATR_DENSIDADE_DEMOGRAFICA:printf("%.2f", carta->densidadeDemografica); break;
        case ATR_PIB_PER_CAPITA:       printf("%.2f", carta->pibPerCapita); break;
        default:                       printf("0");
    }
}

// -----------------------------------------------------------------------------
// Mostra um resumo das cartas no início do jogo
// -----------------------------------------------------------------------------
static void exibir_resumo_cartas(const CartaCidade *c1, const CartaCidade *c2) {
    printf("=== CARTAS ===\n");
    printf("Carta 1: %s (%c-%s)\n", c1->nomeCidadeOuPais, c1->estado, c1->codigo);
    printf("  Pop: %lu | Area: %.2f | PIB: %.2f | Pontos: %d | Dens: %.2f | PerCap: %.2f\n",
           c1->populacao, c1->areaKm2, c1->pibBilhoes, c1->quantidadePontosTuristicos,
           c1->densidadeDemografica, c1->pibPerCapita);

    printf("Carta 2: %s (%c-%s)\n", c2->nomeCidadeOuPais, c2->estado, c2->codigo);
    printf("  Pop: %lu | Area: %.2f | PIB: %.2f | Pontos: %d | Dens: %.2f | PerCap: %.2f\n\n",
           c2->populacao, c2->areaKm2, c2->pibBilhoes, c2->quantidadePontosTuristicos,
           c2->densidadeDemografica, c2->pibPerCapita);
}

// -----------------------------------------------------------------------------
// Utilidades de leitura/entrada
// -----------------------------------------------------------------------------
static void limpar_buffer_ate_quebra_de_linha(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { /* descarta */ }
}

static int ler_inteiro_do_menu(void) {
    int opcao;
    if (scanf("%d", &opcao) != 1) {
        limpar_buffer_ate_quebra_de_linha();
        return -1; // sinaliza erro de leitura
    }
    limpar_buffer_ate_quebra_de_linha();
    return opcao;
}

// Primeiro menu: todas as opções
static void mostrar_menu_primeiro_atributo(void) {
    printf("=== ESCOLHA O 1o ATRIBUTO ===\n");
    printf("1) Populacao (maior vence)\n");
    printf("2) Area (maior vence)\n");
    printf("3) PIB (maior vence)\n");
    printf("4) Pontos Turisticos (maior vence)\n");
    printf("5) Densidade (MENOR vence)\n");
    printf("6) PIB per Capita (maior vence)\n");
    printf("Opcao: ");
}

// Segundo menu: oculta a opção já escolhida
static void mostrar_menu_segundo_atributo_excluindo(int atributoJaEscolhido) {
    printf("\n=== ESCOLHA O 2o ATRIBUTO (diferente do 1o) ===\n");
    for (int i = 1; i <= 6; i++) {
        if (i == atributoJaEscolhido) continue; // dinâmico: não mostra o repetido
        switch (i) {
            case ATR_POPULACAO:            printf("1) Populacao (maior vence)\n"); break;
            case ATR_AREA_KM2:             printf("2) Area (maior vence)\n"); break;
            case ATR_PIB_BILHOES:          printf("3) PIB (maior vence)\n"); break;
            case ATR_PONTOS_TURISTICOS:    printf("4) Pontos Turisticos (maior vence)\n"); break;
            case ATR_DENSIDADE_DEMOGRAFICA:printf("5) Densidade (MENOR vence)\n"); break;
            case ATR_PIB_PER_CAPITA:       printf("6) PIB per Capita (maior vence)\n"); break;
        }
    }
    printf("Opcao: ");
}

/*
  Compara um atributo entre duas cartas.
  Retornos:
    1  -> Carta 1 vence
    0  -> Carta 2 vence
   -1  -> Empate
*/
static int comparar_um_atributo(const CartaCidade *c1, const CartaCidade *c2, enum AtributoComparavel atributo) {
    double valorC1 = valor_do_atributo(c1, atributo);
    double valorC2 = valor_do_atributo(c2, atributo);

    if (atributo == ATR_DENSIDADE_DEMOGRAFICA) {
        // Regra especial: densidade menor vence
        if (valorC1 < valorC2) return 1;
        if (valorC2 < valorC1) return 0;
        return -1;
    } else {
        // Regra geral: maior vence
        if (valorC1 > valorC2) return 1;
        if (valorC2 > valorC1) return 0;
        return -1;
    }
}

int main(void) {
    // -------------------------------------------------------------------------
    // Cartas pré-cadastradas (você pode ajustar os valores à vontade)
    // -------------------------------------------------------------------------
    CartaCidade carta1 = {'A', "A01", "Sao Paulo",     12325000UL, 1521.11f, 699.28f, 50, 0, 0};
    CartaCidade carta2 = {'B', "B02", "Rio de Janeiro", 6748000UL,  1200.25f, 300.50f, 30, 0, 0};

    // Calcula os campos derivados para cada carta
    calcular_metricas_derivadas(&carta1);
    calcular_metricas_derivadas(&carta2);

    // Mostra um resumo no início
    exibir_resumo_cartas(&carta1, &carta2);

    // Loop principal: permite várias rodadas sem fechar o programa
    int desejaCompararNovamente = 1;
    while (desejaCompararNovamente) {
        // ------------------- Escolha dinâmica de 2 atributos -------------------
        int primeiroAtributoEscolhido;
        int segundoAtributoEscolhido;

        while (1) {
            // Primeiro atributo
            mostrar_menu_primeiro_atributo();
            primeiroAtributoEscolhido = ler_inteiro_do_menu();
            if (primeiroAtributoEscolhido < 1 || primeiroAtributoEscolhido > 6) {
                printf("Opcao invalida. Tente novamente.\n\n");
                continue;
            }

            // Segundo atributo (oculta o já escolhido)
            mostrar_menu_segundo_atributo_excluindo(primeiroAtributoEscolhido);
            segundoAtributoEscolhido = ler_inteiro_do_menu();
            if (segundoAtributoEscolhido < 1 || segundoAtributoEscolhido > 6) {
                printf("Opcao invalida. Tente novamente.\n\n");
                continue;
            }
            if (segundoAtributoEscolhido == primeiroAtributoEscolhido) {
                printf("Voce nao pode escolher o MESMO atributo duas vezes. Tente novamente.\n\n");
                continue;
            }
            break; // saímos do while de escolha quando está tudo válido
        }

        enum AtributoComparavel atributo1 = (enum AtributoComparavel)primeiroAtributoEscolhido;
        enum AtributoComparavel atributo2 = (enum AtributoComparavel)segundoAtributoEscolhido;

        // ------------------- Comparações individuais -------------------
        int resultadoComparacaoAtributo1 = comparar_um_atributo(&carta1, &carta2, atributo1);
        int resultadoComparacaoAtributo2 = comparar_um_atributo(&carta1, &carta2, atributo2);

        printf("\n=== COMPARACAO POR DOIS ATRIBUTOS ===\n");
        printf("Cartas: %s (Carta 1) vs %s (Carta 2)\n\n", carta1.nomeCidadeOuPais, carta2.nomeCidadeOuPais);

        // Atributo 1 — mostra valores e quem venceu
        printf("[%s]\n", nome_do_atributo(atributo1));
        printf("  Carta 1 (%s): ", carta1.nomeCidadeOuPais); imprimir_valor_formatado(&carta1, atributo1);
        printf(" | Carta 2 (%s): ", carta2.nomeCidadeOuPais); imprimir_valor_formatado(&carta2, atributo1); printf("\n");
        printf("  Resultado: %s\n\n",
               (resultadoComparacaoAtributo1 == 1) ? "Carta 1 venceu (1)" :
               (resultadoComparacaoAtributo1 == 0) ? "Carta 2 venceu (0)" :
                                                     "Empate!");

        // Atributo 2 — mostra valores e quem venceu
        printf("[%s]\n", nome_do_atributo(atributo2));
        printf("  Carta 1 (%s): ", carta1.nomeCidadeOuPais); imprimir_valor_formatado(&carta1, atributo2);
        printf(" | Carta 2 (%s): ", carta2.nomeCidadeOuPais); imprimir_valor_formatado(&carta2, atributo2); printf("\n");
        printf("  Resultado: %s\n\n",
               (resultadoComparacaoAtributo2 == 1) ? "Carta 1 venceu (1)" :
               (resultadoComparacaoAtributo2 == 0) ? "Carta 2 venceu (0)" :
                                                     "Empate!");

        // ------------------- Soma dos dois atributos -------------------
        // Observação: para a soma, o enunciado diz "maior soma vence" (sem exceção).
        // Portanto, usamos os valores brutos dos atributos selecionados.
        double somaCarta1 = valor_do_atributo(&carta1, atributo1) + valor_do_atributo(&carta1, atributo2);
        double somaCarta2 = valor_do_atributo(&carta2, atributo1) + valor_do_atributo(&carta2, atributo2);

        printf("=== SOMA DOS ATRIBUTOS ===\n");
        printf("  %s + %s\n", nome_do_atributo(atributo1), nome_do_atributo(atributo2));
        printf("  Carta 1 (%s): %.4f\n", carta1.nomeCidadeOuPais, somaCarta1);
        printf("  Carta 2 (%s): %.4f\n", carta2.nomeCidadeOuPais, somaCarta2);

        const char* resultadoFinalDaRodada =
            (somaCarta1 > somaCarta2) ? "Vencedora da rodada: Carta 1" :
            (somaCarta2 > somaCarta1) ? "Vencedora da rodada: Carta 2" :
                                        "Empate!";
        printf("  %s\n\n", resultadoFinalDaRodada);

        // ------------------- Pergunta se quer jogar outra rodada -------------------
        printf("Comparar novamente? (1 = sim, 0 = nao): ");
        desejaCompararNovamente = ler_inteiro_do_menu();
        if (desejaCompararNovamente != 0 && desejaCompararNovamente != 1) {
            printf("Opcao invalida. Encerrando.\n");
            desejaCompararNovamente = 0;
        }
        printf("\n");
    }

    // Pausa final para evitar que a janela feche imediatamente no Windows/Code Runner
    printf("Obrigado por jogar! Pressione ENTER para sair...");
    fflush(stdout);
    limpar_buffer_ate_quebra_de_linha(); // garante buffer limpo
    getchar();
    return 0;
}
