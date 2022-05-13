#include <PubSubClient.h>
#include <WiFi.h>

const char* ssid    = "UbeeF7F8";
const char* password= "6FC964F7F8";

const char* mqtt_server = "driver.cloudmqtt.com";
const int mqtt_port = 18609;
//const int mqtt_port = 38625;
const char* mqtt_user = "kuoikysd";
//const char* mqtt_user = "bmtqnhmu";
const char* mqtt_pass = "nSft8JXHmveG";
//const char* mqtt_pass = "KHw4Itds6hTj";
WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0; //Indice para hacer orden al leer
char msg[50]; //Para capturar el mensaje
int value = 0; //control sobre los mensajes

int columnas[] = {27,14,12,13,23,22,1,21,19,18,5,17,16,4,2,15}; //Salidas de las columnas
int niveles[] = {32,33,25,26}; //Salidas de los pisos
const int pisos = 4;
const int lineas = 16;

void apagar_cubo() {
  for (int x = 0; x < lineas; x ++) {
    digitalWrite(columnas[x], LOW);
  }
}

void powerColumnas2(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11, int p12, int p13, int p14, int p15, int p16) {
  int valColumna[] = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16};
  for (int i = 0; i < lineas; i++) {
    digitalWrite(columnas[i], valColumna[i]);
  }
}

void powerPisos(int x) { //En esta funciĂłn se establecen los valores para las pisos
  switch (x) {
    case 0: {
        int valN[] = {0, 1, 1, 1};
        for (int i = 0; i < pisos; i++) {
          digitalWrite(niveles[i], valN[i]);
        }
        break; //La primera fila encendida
      }
    case 1: {
        int valN[] = {1, 0, 1, 1};
        for (int i = 0; i < pisos; i++) {
          digitalWrite(niveles[i], valN[i]);
        }
        break; //La segunda fila encendida
      }
    case 2: {
        int valN[] = {1, 1, 0, 1};
        for (int i = 0; i < pisos; i++) {
          digitalWrite(niveles[i], valN[i]);
        }
        break; //La tercera fila encendida
      }
    case 3: {
        int valN[] = {1, 1, 1, 0};
        for (int i = 0; i < pisos; i++) {
          digitalWrite(niveles[i], valN[i]);
        }
        break; //La cuarta fila encendida
      }
    case 4: {
        int valN[] = {1, 0, 1, 0};
        for (int i = 0; i < pisos; i++) {
          digitalWrite(niveles[i], valN[i]);
        }
        break; //La segunda y cuarta fila encendida
      }
    case 5: {
        int valN[] = {0, 1, 0, 1};
        for (int i = 0; i < pisos; i++) {
          digitalWrite(niveles[i], valN[i]);
        }
        break; //La primera y tercera fila encendida
      }
  }
}

void patron_rededor() {
  int t = 100; //Tiempo de espera para realizar la siguiente acciĂłn
  for (int i = 0; i < pisos; i++)
  {
    powerPisos(i);
    powerColumnas2(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
    delay(t);
    powerColumnas2(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
    delay(t);
    powerColumnas2(0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
    delay(t);
    powerColumnas2(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
    delay(t);
    powerColumnas2(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
    delay(t);
    powerColumnas2(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
    delay(t);
    powerColumnas2(0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0);
    delay(t);
    powerColumnas2(0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0);
    delay(t);
    powerColumnas2(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
    delay(t);
  }
}

void patron_caras_e() {
  int a, b;
  int leds[] = {0, 1, 2, 3, 7, 11, 15, 14, 13, 12, 8, 4, 0};

  for (int j = 0; j < 6 ; j++) {
    powerPisos(j);
    for (int i = 0; i < 12 ; i++) {
      a = leds[i];
      digitalWrite (columnas[a], 1); delay(50);
      b = leds[i + 1];
      digitalWrite (columnas[b], 1); delay(50);
      digitalWrite (columnas[a], 0); delay(50);
    }
  }
}

void patron_cubos() {
  int a, b, c, d;
  int led1[] = {0, 10, 2, 8};
  int led2[] = {1, 11, 3, 9};
  int led3[] = {4, 14, 6, 12};
  int led4[] = {5, 15, 7, 13};

  for (int i = 4; i < 6; i++)
  {
    powerPisos(i);
    for (int i = 0; i < 4 ; i++) {
      a = led1[i];
      b = led2[i];
      c = led3[i];
      d = led4[i];
      digitalWrite (columnas[a], 1);
      digitalWrite (columnas[b], 1);
      digitalWrite (columnas[c], 1);
      digitalWrite (columnas[d], 1);
      delay(200);
      digitalWrite (columnas[a], 0);
      digitalWrite (columnas[b], 0);
      digitalWrite (columnas[c], 0);
      digitalWrite (columnas[d], 0); 
      delay(200);
    }
    delay(200);
  }
    
}

void patron_1p1() {
  for (int j = 0; j < pisos ; j++) {
    powerPisos(j);
    for (int i = 0; i < lineas ; i++) {
      digitalWrite (columnas[i], 1); delay(10);
      digitalWrite (columnas[i], 0); delay(10);
    }
  }
}

void patron_serie() {
  int t = 50;
  for (int i = 4; i < 6; i++)
  {
    powerPisos(i);
    powerColumnas2 (1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1); delay(t);
    powerColumnas2 (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1); delay(t);
    powerColumnas2 (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1); delay(t);

    powerColumnas2 (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1); delay(t);
    powerColumnas2 (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1); delay(t);
    powerColumnas2 (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1); delay(t);
    powerColumnas2 (0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    powerColumnas2 (1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
  }
}

void patron_random(){
  long ran1;
  int t=75;
  for (int i = 0; i < 30; i++)
  {
    if(i%2==0){
      powerPisos(5);
    }
    else{
      powerPisos(4);
    }
    ran1=random(16);
    digitalWrite(columnas[(int)ran1], 1);
    delay(t);
    digitalWrite(columnas[(int)ran1], 0);
    delay(t);
  }
}


void callback(char* topic, byte* payload, unsigned int length) {

  switch ((char)payload[0])
  {
    case '1':
      {
        for (int x = 0; x < 2; x++) {
          patron_rededor();
        }
        apagar_cubo();
        break;
      }
    case '2':
      {
        patron_caras_e();
        apagar_cubo();
        break;
      }
    case '3':
      {
        for (int x = 0; x < 2; x++) {
          patron_serie();
        }
        apagar_cubo();
        break;
      }
    case '4':
      {
        for (int x = 0; x < 1; x++) {
          patron_random();
        }
        apagar_cubo();
        break;
      }
    case '5':
      {
        for (int x = 0; x < 2; x++) {
          patron_cubos();
        }
        apagar_cubo();
        break;
      }
    case '6':
      {
        patron_1p1();
        apagar_cubo();
        break;
      }
  }
}


void reconnect(){
  while (!client.connected())
  {
    String clientId = "iot_1_";
    clientId = clientId + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass))
    {
      client.publish("salida_N", "primer mensaje");
      //client.subscribe("entrada_N");
      client.subscribe("entrada_proyecto");
    }
    else{
      delay(5000);
    }
  }
}

void setup_wifi(){
  //conectando a la red WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(250);
  }
}

void setup() {

  for (int i = 0; i < lineas; i ++) { //Declarar los pines de las columnas como salidas
    pinMode(columnas[i], OUTPUT);
  }
  for (int i = 0; i < pisos; i ++) { //Declarar los pines de las powerPisos como salidas
    pinMode(niveles[i], OUTPUT);
  }
  setup_wifi();
  //establecemos en nuestro cliente las credenciales del servidor MQTT
  client.setServer(mqtt_server, mqtt_port);

  //funcion que se llama cada que el servidor envĂ­e un mensaje
  client.setCallback(callback);
}


void loop() {
  if (client.connected()==false)
  {
    reconnect();
  }
  client.loop();

  if(millis() - lastMsg > 2000){
    lastMsg = millis();
    value++;
    String mes = "Valor -> " + String(value);
    mes.toCharArray(msg, 50);
    client.publish("salida_N", msg);
  }
}
