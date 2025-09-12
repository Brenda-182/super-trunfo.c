#include <stdio.h>
#include <string.h>

typedef struct {
    char estado;               // ex.: 'A'
    char codigo[4];            // ex.: "A01"
    char nome[50];             // cidade/pais
    unsigned long int populacao;
    float area;                // km^2
    float pib;                 // bilhoes R$
    int pontos;                // pontos turisticos
    float dens;                // hab/km^2 (derivado)
    float percap;              // R$/hab (derivado)
} Carta;

static void calcular_derivados(Carta *c) {
    c->dens   = (c->area > 0.0f) ? (float)c->populacao / c->area : 0.0f;
    c->percap = (c->populacao  > 0UL) ? (c->pib * 1000000000.0f) / (float)c->populacao : 0.0f;
}

enum Atributo {
    ATR_POP = 1,
    ATR_AREA,
    ATR_PIB,
    ATR_PONTOS,
    ATR_DENS,
    ATR_PERCAP
};

static const char* nome_atributo(enum Atributo a) {
    switch (a) {
        case ATR_POP:    return "Populacao";
        case ATR_AREA:   return "Area (km^2)";
        case ATR_PIB:    return "PIB (bilhoes R$)";
        case ATR_PONTOS: return "Pontos Turisticos";
        case ATR_DENS:   return "Densidade (hab/km^2)";
        case ATR_PERCAP: return "PIB per Capita (R$/hab)";
        default:         return "Desconhecido";
    }
}

static double valor_atributo(const Carta *c, enum Atributo a) {
    switch (a) {
        case ATR_POP:    return (double)c->populacao;
        case ATR_AREA:   return (double)c->area;
        case ATR_PIB:    return (double)c->pib;
        case ATR_PONTOS: return (double)c->pontos;
        case ATR_DENS:   return (double)c->dens;
        case ATR_PERCAP: return (double)c->percap;
        default:         return 0.0;
    }
}

static void print_valor(const Carta *c, enum Atributo a) {
    switch (a) {
        case ATR_POP:    printf("%lu", c->populacao); break;
        case ATR_AREA:   printf("%.2f", c->area); break;
        case ATR_PIB:    printf("%.2f", c->pib); break;
        case ATR_PONTOS: printf("%d", c->pontos); break;
        case ATR_DENS:   printf("%.2f", c->dens); break;
        case ATR_PERCAP: printf("%.2f", c->percap); break;
        default:         printf("0");
    }
}

static void mostrar_cartas(const Carta *c1, const Carta *c2) {
    printf("=== CARTAS ===\n");
    printf("Carta 1: %s (%c-%s)\n", c1->nome, c1->estado, c1->codigo);
    printf("  Pop: %lu | Area: %.2f | PIB: %.2f | Pontos: %d | Dens: %.2f | PerCap: %.2f\n",
           c1->populacao, c1->area, c1->pib, c1->pontos, c1->dens, c1->percap);

    printf("Carta 2: %s (%c-%s)\n", c2->nome, c2->estado, c2->codigo);
    printf("  Pop: %lu | Area: %.2f | PIB: %.2f | Pontos: %d | Dens: %.2f | PerCap: %.2f\n\n",
           c2->populacao, c2->area, c2->pib, c2->pontos, c2->dens, c2->percap);
}

static void limpar_entrada(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

static int ler_opcao() {
    int op;
    if (scanf("%d", &op) != 1) { limpar_entrada(); return -1; }
    limpar_entrada();
    return op;
}

static void mostrar_menu1(void) {
    printf("=== ESCOLHA O 1o ATRIBUTO ===\n");
    printf("1) Populacao (maior vence)\n");
    printf("2) Area (maior vence)\n");
    printf("3) PIB (maior vence)\n");
    printf("4) Pontos Turisticos (maior vence)\n");
    printf("5) Densidade (MENOR vence)\n");
    printf("6) PIB per Capita (maior vence)\n");
    printf("Opcao: ");
}

static void mostrar_menu2_excluindo(int escolhido) {
    printf("\n=== ESCOLHA O 2o ATRIBUTO (diferente do 1o) ===\n");
    for (int i = 1; i <= 6; i++) {
        if (i == escolhido) continue;
        switch (i) {
            case ATR_POP:    printf("1) Populacao (maior vence)\n"); break;
            case ATR_AREA:   printf("2) Area (maior vence)\n"); break;
            case ATR_PIB:    printf("3) PIB (maior vence)\n"); break;
            case ATR_PONTOS: printf("4) Pontos Turisticos (maior vence)\n"); break;
            case ATR_DENS:   printf("5) Densidade (MENOR vence)\n"); break;
            case ATR_PERCAP: printf("6) PIB per Capita (maior vence)\n"); break;
        }
    }
    printf("Opcao: ");
}

// retorna 1 se Carta 1 vence, 0 se Carta 2 vence, -1 se empate
static int comparar_por_atributo(const Carta *c1, const Carta *c2, enum Atributo a) {
    double v1 = valor_atributo(c1, a);
    double v2 = valor_atributo(c2, a);
    if (a == ATR_DENS) {                // Densidade: menor vence
        if (v1 < v2) return 1;
        if (v2 < v1) return 0;
        return -1;
    } else {                             // Demais: maior vence
        if (v1 > v2) return 1;
        if (v2 > v1) return 0;
        return -1;
    }
}

int main(void) {
    // Cartas pre-cadastradas
    Carta c1 = {'A', "A01", "Sao Paulo",     12325000UL, 1521.11f, 699.28f, 50, 0, 0};
    Carta c2 = {'B', "B02", "Rio de Janeiro", 6748000UL, 1200.25f, 300.50f, 30, 0, 0};
    calcular_derivados(&c1);
    calcular_derivados(&c2);

    mostrar_cartas(&c1, &c2);

    int jogarNovamente = 1;
    while (jogarNovamente) {
        // ====== Menus dinâmicos para dois atributos ======
        int a1, a2;

        while (1) {
            mostrar_menu1();
            a1 = ler_opcao();
            if (a1 < 1 || a1 > 6) { printf("Opcao invalida.\n\n"); continue; }

            mostrar_menu2_excluindo(a1);
            a2 = ler_opcao();
            if (a2 < 1 || a2 > 6) { printf("Opcao invalida.\n\n"); continue; }
            if (a2 == a1) { printf("Nao pode escolher o mesmo atributo duas vezes.\n\n"); continue; }

            break; // escolhas válidas
        }

        enum Atributo atr1 = (enum Atributo)a1;
        enum Atributo atr2 = (enum Atributo)a2;

        // ====== Comparações individuais ======
        int res1 = comparar_por_atributo(&c1, &c2, atr1);
        int res2 = comparar_por_atributo(&c1, &c2, atr2);

        printf("\n=== COMPARACAO POR DOIS ATRIBUTOS ===\n");
        printf("Cartas: %s (Carta 1) vs %s (Carta 2)\n\n", c1.nome, c2.nome);

        // Atributo 1
        printf("[%s]\n", nome_atributo(atr1));
        printf("  Carta 1 (%s): ", c1.nome); print_valor(&c1, atr1);
        printf(" | Carta 2 (%s): ", c2.nome); print_valor(&c2, atr1); printf("\n");
        printf("  Resultado: %s\n\n",
            res1 == 1 ? "Carta 1 venceu (1)" :
            res1 == 0 ? "Carta 2 venceu (0)" :
                         "Empate!");

        // Atributo 2
        printf("[%s]\n", nome_atributo(atr2));
        printf("  Carta 1 (%s): ", c1.nome); print_valor(&c1, atr2);
        printf(" | Carta 2 (%s): ", c2.nome); print_valor(&c2, atr2); printf("\n");
        printf("  Resultado: %s\n\n",
            res2 == 1 ? "Carta 1 venceu (1)" :
            res2 == 0 ? "Carta 2 venceu (0)" :
                         "Empate!");

        // ====== Soma dos atributos (maior soma vence) ======
        double soma1 = valor_atributo(&c1, atr1) + valor_atributo(&c1, atr2);
        double soma2 = valor_atributo(&c2, atr1) + valor_atributo(&c2, atr2);

        printf("=== SOMA DOS ATRIBUTOS ===\n");
        printf("  %s + %s\n", nome_atributo(atr1), nome_atributo(atr2));
        printf("  Carta 1 (%s): %.4f\n", c1.nome, soma1);
        printf("  Carta 2 (%s): %.4f\n", c2.nome, soma2);

        const char* resultado_final =
            (soma1 > soma2) ? "Vencedora da rodada: Carta 1" :
            (soma2 > soma1) ? "Vencedora da rodada: Carta 2" :
                              "Empate!";
        printf("  %s\n\n", resultado_final);

        // ====== Quer jogar outra rodada? ======
        printf("Comparar novamente? (1 = sim, 0 = nao): ");
        jogarNovamente = ler_opcao();
        if (jogarNovamente != 0 && jogarNovamente != 1) {
            printf("Opcao invalida. Encerrando.\n");
            jogarNovamente = 0;
        }
        printf("\n");
    }

    // Evita fechar a janela imediatamente (especialmente no Windows/Code Runner)
    printf("Pressione ENTER para sair...");
    fflush(stdout);
    limpar_entrada(); // garante que o buffer esteja limpo
    getchar();
    return 0;
}
