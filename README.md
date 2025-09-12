Super Trunfo — Desafio de Logica em C

Um joguinho de terminal, simples e didático, para comparar duas cartas super trunfo 


Como jogar:

O programa mostra um resumo das duas cartas.

Você escolhe 2 atributos no menu.


Ele mostra:

Quem venceu em cada atributo 

A soma dos dois atributos de cada carta

A vencedora da rodada 



Regras e atributos

Geral: maior valor vence.

Densidade (hab/km²): menor vence.

Atributos disponíveis:
População, Área, PIB, Pontos Turísticos, Densidade, PIB per Capita.

Os derivados são calculados automaticamente:

densidade = populacao / areaKm2 (se área > 0)

pibPerCapita = (pibBilhoes * 1e9) / populacao (se população > 0)

Depois das duas comparações individuais, o jogo soma os dois valores escolhidos para cada carta e decide a rodada pela maior soma.


Pronto. Divirta-se testando combinações e vendo quem leva a rodada! 🎮
