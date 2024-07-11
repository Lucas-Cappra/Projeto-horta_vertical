#include <Adafruit_Sensor.h>                       // Biblioteca DHT Sensor Adafruit 
#include <DHT.h>
#include <DHT_U.h>


#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_GFX.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_SSD1306.h> //INCLUSÃO DE BIBLIOTECA

#define SCREEN_I2C_ADDR 0x3D // or 0x3C
#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
#define OLED_RST_PIN -1      // Reset pin (-1 if not available)


Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST_PIN);

// selecione um sensor, retirando o comentário - duas barras
//#define DHTTYPE    DHT11                           // Sensor DHT11
#define DHTTYPE      DHT22                       // Sensor DHT22 ou AM2302

#define DHTPIN 2                                   // Pino do Arduino conectado no Sensor(Data) 
DHT_Unified dht(DHTPIN, DHTTYPE);                  // configurando o Sensor DHT - pino e tipo
uint32_t delayMS;                                  // variável para atraso no tempo

//Declaracao do pino conectado ao sensor
const int PINO_SENSOR = A0;

//Declaracao da variavel que armazena as leituras do sensor
int leitura_sensor = 0;

//Declaracao da variavel que armazena a quantidade de amostras que serao coletadas
const int NUMERO_AMOSTRAS = 5; 
//Altere a variavel acima com a quantidade de amostras que deseja coletar para o calculo da media

//Declaracao da variavel que armazena a soma das leituras
long somatoria = 0;
int media = 0;

const int AirValue = 520; //you need to replace this value with Value_1
const int WaterValue = 260; //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;
int soilMoistureValue = 0; 

void setup()
{
  Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE); //DEFINE A COR DO TEXTO
  display.setTextSize(0); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
 //Configuracao do pino conectado ao sensor como uma entrada
  pinMode(PINO_SENSOR, INPUT);


  Serial.begin(9600);                             // monitor serial 9600 bps
  dht.begin();                                    // inicializa a função
  sensor_t sensor;
}

void loop()
{
  media = 0;
  somatoria = 0;
// **********************PARTE SOBRE SENSOR TEMPERATURA**************
   // ================ TOP BAR ===============
  display.setCursor(0, 0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print("Infos do sensor:"); //ESCREVE O TEXTO NO DISPLAY
  display.display(); //EFETIVA A ESCRITA NO DISPLAY
  // ================ END TOP BAR ===============
  //display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
 

  delay(delayMS);                               // atraso entre as medições
  sensors_event_t event;                        // inicializa o evento da Temperatura
  dht.temperature().getEvent(&event);           // faz a leitura da Temperatura
  if (isnan(event.temperature))                 // se algum erro na leitura
  {
    display.setCursor(0, 30); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    display.print("Erro na leitura da Temperatura!");
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(5000); //INTERVALO DE 1,5 SEGUNDOS
  }
  else                                          // senão
  {
    display.setCursor(0, 20); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    display.print("Temperatura: ");              // imprime a Temperatura
    display.print(event.temperature);
    display.println(" oC");
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(500); //INTERVALO DE 1,5 SEGUNDOS
  
  }
  dht.humidity().getEvent(&event);              // faz a leitura de umidade
  if (isnan(event.relative_humidity))           // se algum erro na leitura
  {
    display.setCursor(0, 30); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    display.println("Erro na leitura da Umidade!");
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(5000); //INTERVALO DE 1,5 SEGUNDOS
  }
  else                                          // senão
  {
    display.setCursor(0, 30); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    display.print("Umidade: ");                  // imprime a Umidade
    display.print(event.relative_humidity);
    display.println("%");
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(2000); //INTERVALO DE 1,5 SEGUNDOS
  }
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY

// **********************PARTE SOBRE SENSOR UMIDADE**************

  // ================ TOP BAR ===============
    display.setCursor(0, 0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    display.print("Coletando leituras..."); //ESCREVE O TEXTO NO DISPLAY
    display.display(); //EFETIVA A ESCRITA NO DISPLAY

    soilMoistureValue = analogRead(PINO_SENSOR); //Le o sensor
    somatoria = somatoria + soilMoistureValue; //Soma a variavel "somatoria" a leitura atual do sensor com seu valor anterior
    float tensao = soilMoistureValue*(5.0/1023); //Converte a leitura para tensao para referencia
  


//Realiza a leitura do sensor de acordo com a variavel "NUMERO_AMOSTRAS"
  for(int i = 1; i <= NUMERO_AMOSTRAS; i++){
     
    display.setCursor(10,30); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    display.print("Amostra ");
    display.print(i);
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(1000);
    display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
    delay(500);

     // ================ TOP BAR ===============
    display.setCursor(0, 0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    display.print("Coletando leituras..."); //ESCREVE O TEXTO NO DISPLAY
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
  }
   display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY

  
  display.setCursor(0, 0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print("Coletando medidas.."); //ESCREVE O TEXTO NO DISPLAY
  media = somatoria / NUMERO_AMOSTRAS;
  display.display(); //EFETIVA A ESCRITA NO DISPLAY
  
  display.setCursor(10, 20); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print("Media: "); //ESCREVE O TEXTO NO DISPLAY
  display.print(media); //ESCREVE O TEXTO NO DISPLAY
  display.display(); //EFETIVA A ESCRITA NO DISPLAY
  if(media >= 500){
    display.setCursor(10, 35); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    display.print("Esta seco"); //ESCREVE O TEXTO NO DISPLAY
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
      
  } else if(media < 500){
    display.setCursor(10, 35); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    display.print("Esta umido"); //ESCREVE O TEXTO NO DISPLAY
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
  }
  delay(10000);
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY

}
