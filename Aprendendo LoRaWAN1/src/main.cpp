//Include geral
#include <mbed.h> // Include do MBED

//Includes específicos
//Driver do transceiver SX1276 necessário para comunicação LoRa
#include "sx1276-mbed-hal.h"
//Mapeamento dos pinos necessários
#include "PinMap.h"

//Defines do projeto
#define FREQ_LORA 915E6                 // Frequência de transmissão [Hz]
#define TX_OUTPUT_POWER 20              // Potência do sinal de transmissão [dBm]
#define FREQ_DEVIATION 0                // Desvio de frequência, utilizado somente em modem FSK, no LoRa é 0 [Hz]
#define LORA_BANDWIDTH 500E3            // Largura de banda da transmissão [Hz]
// Spreading Factor utilizado pelo LoRaWAN, melhor explicado no arquivo README.md nas referências
// Utilize a calculadora de AirTime para se adequar aos regulamentos regionais (BR para LASC e minifoguetes, EUA para SACup)
#define LORA_SPREADING_FACTOR LORA_SF9  // 1775 bit/s
#define LORA_CODINGRATE LORA_ERROR_CODING_RATE_4_5 // Fator de bits de correção de erro
#define LORA_PREAMBLE_LENGTH 8          // Tamanho do preambulo, padrão é 8
#define LORA_FIX_LENGTH_PAYLOAD_ON false
#define LORA_CRC_ENABLED true
#define LORA_FHSS_ENABLED false  
#define LORA_NB_SYMB_HOP 4 
#define LORA_IQ_INVERSION_ON false
#define TX_TIMEOUT 2000
#define LORA_SYMBOL_TIMEOUT 5




int main() {

  //Instanciando a utilização do Radio para transmissão LoRa e os pinos associados
  static RadioEvents_t* RadioEvents;
  SX1276Generic Radio(RadioEvents, MURATA_SX1276,
		    LORA_SPI_MOSI, LORA_SPI_MISO, LORA_SPI_SCLK, LORA_CS, LORA_RESET,
		    LORA_DIO0, LORA_DIO1, LORA_DIO2, LORA_DIO3, LORA_DIO4, LORA_DIO5,
		    LORA_ANT_RX, LORA_ANT_TX, LORA_ANT_BOOST, LORA_TCXO);

  // Configura a frequência utilizada
  Radio.SetChannel(FREQ_LORA);

  Radio.SetTxConfig(MODEM_LORA,TX_OUTPUT_POWER,FREQ_DEVIATION,LORA_BANDWIDTH,LORA_SPREADING_FACTOR,LORA_CODINGRATE,LORA_PREAMBLE_LENGTH,LORA_FIX_LENGTH_PAYLOAD_ON,LORA_CRC_ENABLED, LORA_FHSS_ENABLED, LORA_NB_SYMB_HOP, 
		      LORA_IQ_INVERSION_ON,TX_TIMEOUT);
  char* mensagem = "Burro";
  while(true) {
    Radio.Send(mensagem,sizeof(mensagem));
    wait_us(1e6);
  }
}
