#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_GFX.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_SSD1306.h> //INCLUSÃO DE BIBLIOTECA


#define SCREEN_I2C_ADDR 0x3D // or 0x3C
#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
#define OLED_RST_PIN -1      // Reset pin (-1 if not available)


Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST_PIN);

//Declaracao do pino conectado ao sensor
const int PINO_SENSOR = A0;

//Declaracao da variavel que armazena as leituras do sensor
int leitura_sensor = 0;

//Declaracao da variavel que armazena a quantidade de amostras que serao coletadas
const int NUMERO_AMOSTRAS = 5; 
//Altere a variavel acima com a quantidade de amostras que deseja coletar para o calculo da media

//Declaracao da variavel que armazena a soma das leituras
long somatoria = 0;

void leitura();
void media();

void setup(){
  Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE); //DEFINE A COR DO TEXTO
  display.setTextSize(0); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
  
  //Configuracao do pino conectado ao sensor como uma entrada
  pinMode(PINO_SENSOR, INPUT);

}
void loop() {
   // ================ TOP BAR ===============
    display.setCursor(0, 0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    display.print("Coletando leituras..."); //ESCREVE O TEXTO NO DISPLAY
    display.display(); //EFETIVA A ESCRITA NO DISPLAY

    leitura_sensor = analogRead(PINO_SENSOR); //Le o sensor
    somatoria = somatoria + leitura_sensor; //Soma a variavel "somatoria" a leitura atual do sensor com seu valor anterior
    float tensao = leitura_sensor*(5.0/1023); //Converte a leitura para tensao para referencia
  


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
  
  
  display.setCursor(0, 20); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print("Coletando medias..."); //ESCREVE O TEXTO NO DISPLAY
  int media = somatoria / NUMERO_AMOSTRAS;
  
  display.setCursor(60, 20); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print("Média: "); //ESCREVE O TEXTO NO DISPLAY
  display.print(media); //ESCREVE O TEXTO NO DISPLAY
  display.display(); //EFETIVA A ESCRITA NO DISPLAY
    
  delay(2000);
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
}
