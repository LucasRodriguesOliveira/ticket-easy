# Ticket Easy

## Description
Projeto de cadastro de eventos de casas de shows para a disciplina de `Desenvolvimento Desktop`

## Compile

Para compilar o projeto, é necessário realizar compile de cada arquivo `.c` separadamente, para isso, no console, utilize a seguinte instrução:

`gcc <filename>.c -o <filename>.o -c`
essa instrução vai criar um arquivo `<filename>.o` onde `<filename>` é o nome do arquivo alvo da compilação, por exemplo:

Se eu quiser compilar os arquivos `menu.c`, `util.c` e `main.c`, devo fazer o seguinte:

```bash
$ gcc main.c -o main.o -c
$ gcc menu.c -o menu.o -c
$ gcc util.c -o util.o -c
```

Cada comando começa com `$`, mas não digite o símbolo `$`, é apenas para ilustrar a instrução.

Por fim, é preciso linkar os arquivos de objeto `<filename>.o` em um único arquivo executável

Se estiver no windows, o resultado será `<program>.exe`

Se estiver no linux, o resultado será `<program>`

Para criar o executável, considerando o exemplo acima, apenas replique para sua situação:

`gcc -o <program> main.o menu.o util.o`

Dessa forma, o arquivo executável `<program>` será criado com todos os arquivos object `.o` adicionados.

Para executar, basta referenciar o executável na linha de comando como:

```bash
$ ./<program>
```

Substitua `<program>` pelo nome adequado, para esse projeto, recomendo `ticket-easy`

<details>
<summary>Compilar - Linux (atalho - copia e cola)</summary>

```bash
$  gcc area.c -o area.o -c && gcc batch.c -o batch.o -c && gcc event.c -o event.o -c && gcc main.c -o main.o -c && gcc menu.c -o menu.o -c && gcc ticket.c -o ticket.o -c && gcc util.c -o util.o -c && gcc sale.c -o sale.o -c && gcc -o ticket-easy area.o batch.o event.o main.o menu.o util.o ticket.o sale.o
```
</details>
