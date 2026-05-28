Alunos: Lucas William Albertti & Vinicius H. Mai

RELATÓRIO — COMPARAÇÃO ENTRE ÁRVORE AVL E RUBRO-NEGRA
Introdução
Este trabalho tem como objetivo comparar o desempenho das árvores AVL e
Rubro-Negra em um sistema de ranking em tempo real. Nesse contexto, jogadores
são inseridos e consultados constantemente, exigindo operações eficientes de
inserção e busca.

Metodologia
Foi realizado um experimento com 10.000 inserções de valores aleatórios, seguido
de 10.000 buscas. Para ambas as estruturas, foram medidos:
• Tempo de execução (utilizando clock());
• Número de rotações realizadas durante as inserções.
Os testes foram executados com os mesmos dados para garantir uma
comparação justa.

Resultados
Árvore Rubro-Negra:
• Tempo de inserção: 0.003 segundos
• Tempo de busca: 0.003 segundos
• Rotações: 5038
Árvore AVL:
• Tempo de inserção: 0.012 segundos
• Tempo de busca: 0.001 segundos
• Rotações: 10683

Análise
A árvore Rubro-Negra apresentou menor número de rotações, pois possui um
balanceamento menos rígido. Já a árvore AVL, por manter um controle mais estrito
da altura, tende a realizar mais rotações para se manter balanceada.
Embora a AVL possa oferecer buscas ligeiramente mais rápidas, seu custo de
inserção é maior, o que pode impactar sistemas com atualizações frequentes.

Conclusão
Para um sistema de ranking em tempo real, a árvore Rubro-Negra é a mais
adequada, pois apresenta melhor desempenho em inserções e menor custo de
manutenção estrutural. Isso a torna mais eficiente em cenários dinâmicos, onde
há constantes atualizações de dados.
