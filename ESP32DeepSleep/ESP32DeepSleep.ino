/* Definição - GPIO do LED */
#define GPIO_LED          5
 
/* Definições - deep sleep */
#define FATOR_US_PARA_S   1000000  /* Fator de conversão de micro-segundos para segundos */
#define TEMPO_DEEP_SLEEP  60       /* Tempo para o ESP32 ficar em deep sleep (segundos) */
 
void setup() 
{
    /* Configura GPIO do LED e o inicializa desligado */
    pinMode(GPIO_LED, OUTPUT);
    digitalWrite(GPIO_LED, LOW); 
}
 
void loop() 
{
    int i;
 
    /* Pisca o LED 10 vezes */
    for (i=0; i<10; i++)
    {
        digitalWrite(GPIO_LED, HIGH);
        delay(250);
        digitalWrite(GPIO_LED, LOW);
        delay(250);
    }
 
    /* Entra em deep sleep */
    esp_sleep_enable_timer_wakeup(TEMPO_DEEP_SLEEP * FATOR_US_PARA_S);
    esp_deep_sleep_start();
}
