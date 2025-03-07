# Simulador de CPU 🖥️

Este é um projeto de **Simulador de CPU** desenvolvido em **C** para a disciplina de **Arquitetura de Computadores - 2024.2** da **Universidade Federal do Ceará - Campus Quixadá**. O simulador emula o funcionamento de uma CPU, incluindo a manipulação de registros, execução de instruções e diversas funcionalidades essenciais, como operações lógicas e aritméticas dentro da ULA (Unidade Lógica e Aritmética), gerenciamento da pilha, controle da memória de dados e atualização de flags de status. 🚀

## Funcionalidades ⚙️

- **Operações lógicas e aritméticas**: A ULA realiza operações como soma, subtração, AND, OR, etc. ➕➖
- **Manipulação da pilha**: O simulador gerencia a pilha de execução, com suporte a operações como PUSH e POP. 🏋️‍♂️
- **Memória de Dados e Programa**: O simulador utiliza diferentes tipos de memória, incluindo a memória de dados do programa, para armazenar variáveis e instruções. 💾
- **Atualização das flags**: Durante a execução das operações, as flags da CPU (como zero, carry, overflow, etc.) são atualizadas conforme necessário. 🚩
- **Leitura de Instruções de Arquivos**: As instruções são lidas a partir de arquivos, permitindo que o simulador execute programas e teste diferentes cenários de maneira eficiente. 📂

### Descrição dos Diretórios 🗂️:

- **src/funcoes/**: Contém as implementações das principais funções do simulador, como a Unidade Lógica e Aritmética (ULA), manipulação da pilha, decodificação de instruções, etc. 🔧
- **Main/**: Contém o arquivo principal `main.c`, onde a execução do simulador ocorre. 📜
- **Testes/**: Contém arquivos de teste (como `memoria.txt`) usados para validar as operações e o comportamento do simulador. 🧪

## Desenvolvedores 👨‍💻:
- Clidenor Lopes Martins Filho - 566434
- Cauan Ricardo Ribeiro - 569566
- Victor Emanuel Silva de Queiroz - 567683

## Como Executar 🏃‍♂️

Para rodar o simulador, siga os passos abaixo:

1. Clone o repositório:
    ```bash
    git clone https://github.com/cauanrricardo/Simulador-CPU.git
    ```

2. Navegue até o diretório do projeto:
    ```bash
    cd simulador-cpu
    ```

3. Compile o código:
    ```bash
    gcc -o simulador src/Main/main.c
    ```

4. Crie ou edite um arquivo de instruções (por exemplo, `memoria.txt`) na pasta `Testes/` com as instruções que deseja executar.

5. Execute o simulador, passando o caminho para o arquivo de instruções:
    ```bash
    ./Simulador-C ..\..\Testes\memoria.txt
    ```

    No exemplo acima, o arquivo `memoria.txt` contém as instruções que serão processadas pelo simulador. Substitua o caminho e o nome do arquivo conforme necessário.


## Licença 📄

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes. 🔓