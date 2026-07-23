# ♟️ Jogo de Damas em C (Trabalho Final - FUP)

> Uma implementação em linguagem C do clássico Jogo de Damas para terminal, desenvolvida para o trabalho final da disciplina de **Fundamentos de Programação (FUP)**.

---

## 📌 Sobre o Projeto

O objetivo deste projeto é aplicar os conceitos fundamentais da programação estruturada em **C** para construir uma versão funcional do jogo de damas jogável diretamente pelo terminal.

Entre os conceitos praticados no código estão:

* Manipulação de **matrizes bidimensionais** para representação do tabuleiro $10 \times 10$.
* Estruturação de dados com **`structs`** e manipulação por **ponteiros**.
* Controle de fluxo e **modularização em funções** (validação de movimentos, desenho do tabuleiro, contagem de peças).
* Tratamento de regras e condições de vitória.
* Trabalho em grupo com divisão de responsabilidades.
* Versionamento de código por meio do **Git**

---

## 🎯 Funcionalidades

* [x] **Interface via Terminal:** Renderização do tabuleiro $10 \times 10$ com representação gráfica visual para peões e damas.
* [x] **Movimentação Diagonal:** Validação rigorosa de movimentos simples para frente.
* [x] **Mecânica de Captura:** Suporte à captura de peças adversárias ("comer" peças).
* [x] **Promoção a Dama:** Transformação automática da peça ao atingir a última linha do tabuleiro adversário.
* [x] **Gerenciamento de Turnos:** Alternância automática entre Jogador 1 e Jogador 2.
* [x] **Condição de Fim de Jogo:** Verificação de vitória/derrota com base no total de peças restantes no tabuleiro.

---

## 🧰 Tecnologias Utilizadas

* **Linguagem:** C (compatível com padrões C99 / C ANSI)
* **Compilador:** `gcc` ou `clang`
* **Ambiente de Execução:** Terminal / Console (Linux, Windows via WSL/MinGW, macOS)

---

## 🚀 Como Executar

### Pré-requisitos

Você precisará ter um compilador C instalado (como o **GCC**).

### Passo a Passo

1. **Clone este repositório:**
```bash
git clone https://github.com/daviclira8/trabalho_final_fup_damas.git
cd trabalho_final_fup_damas

```


2. **Compile o projeto:**
* No **Linux/ macOS**:
```bash
make

```
* No **Windows**:
```bash
mingw32-make

```


3. **Execute o programa:**
```bash
./damas

```


---

## 🎮 Como Jogar

1. As posições no tabuleiro são informadas via coordenadas de linha e coluna.
2. As peças normais apenas realizam movimentação diagonal para frente.
3. Ao capturar uma peça inimiga, a peça salta por cima dela ocupando a casa vazia posterior.
4. Peças que alcançarem a extremidade oposta do tabuleiro tornam-se **Damas** e passam a ter raio de movimento estendido.
5. O jogo encerra quando um dos jogadores perder todas as suas peças ou ficar sem movimentos válidos.

---

## 👤 Autor

Desenvolvido por [**@daviclira8**](https://github.com/daviclira8), [**@rogerflevi9**](https://github.com/rogerflevi9) e [**@fgsasaki**](https://github.com/fgsasaki) como projeto final da disciplina de Fundamentos de Programação.

---

## 📄 Licença

Este projeto possui fins estritamente acadêmicos e educacionais. Sinta-se à vontade para utilizar o código como referência de estudo.
