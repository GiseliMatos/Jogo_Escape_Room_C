## Este repositório contém o jogo Ecos do Passado, inspirado em jogos de escape estilo Escape Room 🕹️ ##

Implementado em linguagem C usando grafos, foi desenvolvido como projeto final na disciplina de Estrutura de Dados 2. 

Se trata de um jogo de aventura narrada onde o jogador explora um antigo castelo sombrio, repleto de salas misteriosas e enigmas. O jogador inicia em uma sala inicial (calabouço) e, ao longo do caminho, encontra salas bloqueadas que exigem a resolução correta de enigmas para serem desbloqueadas. 

A cada resposta certa, o jogador acumula pontos e avança para novas salas, escolhendo rotas disponíveis no mapa. Caso erre o enigma, tem direito a um número limitado de tentativas (se falhar três vezes, o jogo é encerrado com Game Over). O objetivo final é chegar até a sala final (salão do trono) com a maior pontuação possível no menor tempo.

Para auxiliar, o jogador possui uma chave mestra para abrir qualquer porta, que pode ser usada apenas uma vez por execução. Ao final da partida, os dados do jogador (nome, pontuação e tempo) são organizados em um ranking, que exibe os três melhores desempenhos.

Utilizando grafo, foi possível representar salas como vértices e passagens como arestas. Essa modelagem permite criar múltiplos caminhos, oferecendo ao jogador liberdade de exploração e tomada de decisão.

- `Vértices` (Salas): Cada vértice do grafo representa uma sala com informações como enigma, opções de resposta, resposta correta e pontuação. 

- `Arestas` (Passagens): As conexões entre salas são modeladas como arestas, contendo informações como a sala de origem, destino e uma descrição que simula a passagem ou corredor entre elas.

- `Inventário`: É implementado como uma estrutura auxiliar que armazena o estado de itens especiais.

- `Ranking`: O ranking utiliza um vetor de jogadores ordenado com qsort, que aplica uma função de comparação para organizar os resultados conforme pontuação e tempo.

Todo o fluxo do jogo, do enigma até a movimentação no mapa, é controlado através da manipulação do grafo. A interação é feita via console, com menus e mensagens impressas em tela, permitindo que o jogador navegue pelas opções usando o teclado.
