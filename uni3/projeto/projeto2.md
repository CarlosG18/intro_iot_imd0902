# Projeto 2 - Monitoramento de Armários

> Desenvolvendo um dispositivo iot para monitoramento dos armários da sala 203 do NPIT - UFRN

## 🧩 Contextualização do Projeto

O monitoramento de ambientes e objetos por meio de dispositivos IoT (Internet das Coisas) é uma prática que vem crescendo devido à sua eficiência e capacidade de fornecer dados em tempo real. No caso específico dos armários da sala 203 do NPIT - UFRN, a implementação de um sistema de monitoramento visa garantir a segurança e o controle dos itens armazenados, bem como a manutenção das condições ideais dentro dos armários.

## 🔧 Arquitetura do Projeto

<p align="center">
    <img width=700 src="./imgs/"/>
</p>

## 📋 Requisitos do projeto

### [1/7] 🔍 RF01: Realizar a leitura de sensores para coleta de dados.

Os dados que serão obtidos serão o **estado da porta** e a **luminosidade**. Para tal objetivo, foram utilizados dois sensores:

- **Sensor Fim de Curso**: Um sensor fim de curso é um dispositivo usado para detectar a presença ou ausência de um objeto em uma posição específica. Quando o objeto atinge um ponto predefinido, o sensor aciona um mecanismo que pode ser um interruptor ou um sinal elétrico. Com isso, quando a porta está fechada o interruptor e precionado, e desta forma pode ser capturado o estado do armário (aberto/fechado).

<p align="center">
    <img width=300 src="./imgs/images (9).jpeg"/>
</p>

- **Sensor de luminosidade LDR**: O sensor **LDR (Light Dependent Resistor)** é um tipo de resistor cuja resistência varia conforme a intensidade da luz que incide sobre ele. Quando a luz atinge o LDR, a resistência do componente diminui, permitindo que mais corrente passe através dele. Em contraste, em ambientes com pouca luz, a resistência aumenta e a corrente diminui. Essa variação na resistência pode ser medida e utilizada para determinar a intensidade da luz ambiente, possibilitando aplicações como sistemas de iluminação automática, dispositivos de ajuste de brilho e detecção de presença.

<p align="center">
    <img width=300 src="./imgs/images (10).jpeg"/>
</p>

### [2/7] ⚙️ RF02: Realizar algum processamento dos dados no dispositivo IoT.

**falar sobre a conversao do sinal analogico para o digital**

### [3/7] 📦 RF03: Armazenar dados na memória interna do dispositivo IoT.

Para realizar a gravação na memória interna do ESP foi ultilizado a biblioteca `<EEPROM.h>`. Nessa biblioteca, temos os principais comandos:

- **EEPROM.begin(EEPROM_SIZE)**: inicializa a biblioteca, cujo argumento é o tamanho de endereços de memória que será utilizado (EEPROM_SIZE);

- **EEPROM.read(posicao)**: ler o dado da memória interna que está na posicão passada no argumento.

- **EEPROM.write(posicao,var)**: escreve na posição passada no argumento (posição) o valor da variável (var).

- **EEPROM.commit()**: Confirma as escritas que foram realizadas anteriormente.

A variável que foi escolhida para ser armazenada na **memória interna do ESP** foi a varivável **`contador_open`** que armazena a quantidade de vezes que a porta foi aberta. ela foi escolhida para ser armazenada, pelo fato de não se perder esse valor caso o dispositivo perca a alimentação externa.

### [4/7] 📶 RF04: Verificar conexão com a rede Internet e enviar dados para alguma aplicação

**falar sobre a conexao com a internet e falar sobre a plataforma thingsboard**

### [5/7] 🔒 RF05: Implantar ações de gerenciamento de dispositivos e de segurança usando alguma plataforma IoT.

**falar como foi feito o uso do TOKEN**

### [6/7] 📊 RF06: Gerar dashboards e outras funcionalidades em alguma aplicação/plataforma.

**apresentar a dashboard desenvolvida**
**falar das funcionalidades**

### [7/7] ⚠️ RF07: Emitir alerta de valores de variáveis fora de faixa.

**falar dos alertas**

## 📊 Resultados e Análises