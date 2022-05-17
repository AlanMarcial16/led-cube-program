#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

const char* ssid="BUAP_Estudiantes";
const char* password="f85ac21de4";

const char* mqtt_server = "bca1dd0c.us-east-1.emqx.cloud";
const int mqtt_port = 15963;
const char* mqtt_user = "davefork";
const char* mqtt_pass = "123";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0; //Indice para hacer orden al leer
char msg[50]; //Para capturar el mensaje
int value = 0; //control sobre los mensajes

int columnas[] = {27,14,12,13,23,22,0,21,19,18,5,17,16,4,2,15}; //Salidas de las columnas
int niveles[] = {32,33,25,26}; //Salidas de los pisos
const int pisos = 4;
const int lineas = 16;

void encenderPisos(int x) { //En esta funciĂłn se establecen los valores para las pisos
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
    case 6: {
      int valN[] = {1,1,1,1};
      for(int i=0;i<pisos;i++)
        digitalWrite(niveles[i],valN[i]);
      break; //Todas las filas apagadas
    }

    case 7:{
      int valN[] = {0,0,0,0};
      for(int i=0;i<pisos;i++)
        digitalWrite(niveles[i],valN[i]);
      break; //Todas las filas apagadas
    }
  }
}

void apagar_cubo() {
  encenderPisos(6);
  for (int x = 0; x < lineas; x ++) {
    digitalWrite(columnas[x], LOW);
  }
}

void encenderColumnas(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11, int p12, int p13, int p14, int p15, int p16) {
  int valColumna[] = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16};
  for (int i = 0; i < lineas; i++) {
    digitalWrite(columnas[i], valColumna[i]);
  }
}

void patron_caracol(){
  int tiempo = 100;
  for(int i=0;i<pisos;i++){
    encenderPisos(i);
    encenderColumnas(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0); delay(tiempo);
    encenderColumnas(0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0); delay(tiempo);
    encenderColumnas(0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0); delay(tiempo);
    encenderColumnas(0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0); delay(tiempo);

    encenderColumnas(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0); delay(tiempo);
    encenderColumnas(0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0); delay(tiempo);
    encenderColumnas(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1); delay(tiempo);
    
    encenderColumnas(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0); delay(tiempo);
    encenderColumnas(0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0); delay(tiempo);
    encenderColumnas(0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0); delay(tiempo);

    encenderColumnas(0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0); delay(tiempo);
    encenderColumnas(0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0); delay(tiempo);
   
    encenderColumnas(0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0); delay(tiempo);
    encenderColumnas(0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0); delay(tiempo);

    encenderColumnas(0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0); delay(tiempo);
    encenderColumnas(0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0); delay(tiempo);

  }
}

void patron_caras_e() {
  int a, b;
  int encenderColumnass[] = {0, 1, 2, 3, 7, 11, 15, 14, 13, 12, 8, 4, 0};

  for (int j = 0; j < 6 ; j++) {
    encenderPisos(j);
    for (int i = 0; i < 12 ; i++) {
      a = encenderColumnass[i];
      digitalWrite (columnas[a], 1); delay(50);
      b = encenderColumnass[i + 1];
      digitalWrite (columnas[b], 1); delay(50);
      digitalWrite (columnas[a], 0); delay(50);
    }
  }
}

void patron_cubos() {
  int a, b, c, d;
  int encenderColumnas1[] = {0, 10, 2, 8};
  int encenderColumnas2[] = {1, 11, 3, 9};
  int encenderColumnas3[] = {4, 14, 6, 12};
  int encenderColumnas4[] = {5, 15, 7, 13};

  for (int i = 4; i < 6; i++)
  {
    encenderPisos(i);
    for (int i = 0; i < 4 ; i++) {
      a = encenderColumnas1[i];
      b = encenderColumnas2[i];
      c = encenderColumnas3[i];
      d = encenderColumnas4[i];
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
    encenderPisos(j);
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
    encenderPisos(i);
    encenderColumnas (1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1); delay(t);
    encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1); delay(t);
    encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1); delay(t);

    encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1); delay(t);
    encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1); delay(t);
    encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1); delay(t);
    encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
    encenderColumnas (1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
  }
}

void ser() {
	int t = 100;
	int a = 10;
	int b = 6.5;
	int y;
	for (int x = 0; x < b ; x++) {
	y = 0; encenderPisos(y);
	encenderColumnas (1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 1; encenderPisos(y);
	encenderColumnas (1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < b ; x++) {
	y = 0; encenderPisos(y);
	encenderColumnas (1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 1; encenderPisos(y);
	encenderColumnas (1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	}
	y = 0; encenderPisos(y);
	encenderColumnas (1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1); delay(t);
	for (int x = 0; x < a ; x++) {
	y = 0; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1); delay(5);
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 0; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1); delay(5);
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1); delay(5);
	}
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1); delay(t);
	encenderColumnas (0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0); delay(t);
	for (int x = 0; x < a ; x++) {
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0); delay(5);
	}
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0); delay(t);
	for (int x = 0; x < a ; x++) {
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0); delay(5);
	}
	for (int x = 0; x < b ; x++) {
	y = 0; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0); delay(5);
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 0; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0); delay(5);
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 0; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0); delay(5);
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < b ; x++) {
	y = 0; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0); delay(5);
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < b ; x++) {
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0); delay(5);
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0); delay(5);
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0); delay(5);
	}
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0); delay(t);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1); delay(t);
	for (int x = 0; x < a ; x++) {
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1); delay(5);
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1); delay(5);
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1); delay(5);
	}
	for (int x = 0; x < b ; x++) {
	y = 0; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0); delay(5);
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 0; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0); delay(5);
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0); delay(5);
	}
	y = 0; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0); delay(t);
	encenderColumnas (0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0); delay(t);
	for (int x = 0; x < a ; x++) {
	y = 0; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 0; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < b ; x++) {
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0); delay(5);
	}
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0); delay(t);
	for (int x = 0; x < a ; x++) {
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0); delay(5);
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < b ; x++) {
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0); delay(5);
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0); delay(5);
	}
	y = 1; encenderPisos(y);
	encenderColumnas (0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	for (int x = 0; x < a ; x++) {
	y = 1; encenderPisos(y);
	encenderColumnas (0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 1; encenderPisos(y);
	encenderColumnas (0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	}
	y = 2; encenderPisos(y);
	encenderColumnas (0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	for (int x = 0; x < a ; x++) {
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	}
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	for (int x = 0; x < a ; x++) {
	y = 2; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 3; encenderPisos(y);
	encenderColumnas (1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 2; encenderPisos(y);
	encenderColumnas (1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 3; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	}
	for (int x = 0; x < a ; x++) {
	y = 1; encenderPisos(y);
	encenderColumnas (1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	y = 2; encenderPisos(y);
	encenderColumnas (1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(5);
	}
}

void abajo_arriba(){
  Serial.print("Entre abajo-arriba");
  for(int i=0;i<4;i++){
    Serial.print(i);
    encenderPisos(i);
    encenderColumnas(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);  
  }
}

void patron_random(){
  long ran1;
  int t=75;
  for (int i = 0; i < 30; i++)
  {
    if(i%2==0){
      encenderPisos(5);
    }
    else{
      encenderPisos(4);
    }
    ran1=random(16);
    digitalWrite(columnas[(int)ran1], 1);
    delay(t);
    digitalWrite(columnas[(int)ran1], 0);
    delay(t);
  }
}

void cubote() {
 //Prende una fila a la vez para formar un cubo sin centro
	int t = 500;
	int a = 50;
	int y;
	y = 6; encenderPisos(y);
	encenderColumnas (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); delay(t);
	encenderColumnas (1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1); delay(t);
	encenderColumnas (1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1); delay(t);
	encenderColumnas (1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1); delay(t);
	for (int x = 0; x < a; x++) {
	y = 3; encenderPisos(y);
	encenderColumnas (1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1); delay(5);
	y = 7; encenderPisos(y);
	encenderColumnas (1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1); delay(5);
	}
	for (int x = 0; x < a; x++) {
	y = 4; encenderPisos(y);
	encenderColumnas (1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1); delay(5);
	y = 5; encenderPisos(y);
	encenderColumnas (1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1); delay(5);
	}
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido bajo el tópico ->");
  Serial.print(topic);
  Serial.print("\n");
  
  char opcion = (char)payload[0]; 
  switch (opcion)
  {
    case '1':
      {
        for(int x=0;x<2;x++)
          patron_caracol();
        apagar_cubo();
        break;
      }
    case '2':
      {
        for(int x=0;x<2;x++)
          ser();
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
    case '7':
    {
      for(int x=0;x<2;x++)
        abajo_arriba();
      apagar_cubo();
      break;
    }
    case '8':
    {
      for(int x=0;x<2;x++)
        cubote();
      apagar_cubo();
      break;
    }
  }
}


void reconnect(){
  
  while (!client.connected()) {
    Serial.println("Intentando Conexión MQTT");

    String clientId = "iot_1_";
    clientId = clientId + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.println("Conexión a MQTT exitosa");
      client.publish("salida","primer mensaje");
      client.subscribe("entrada");  
    }else{
      Serial.println("Falló la conexión");
      Serial.print(client.state());
      Serial.print("Se intentará de nuevo en 5 segundos");
      delay(5000);
    }
  }
} 

void setup_wifi(){

  Serial.println("Conectando a ->");
  Serial.println(ssid);

  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }

  Serial.println("");
  Serial.println("Conexion exitosa");
  Serial.println("Mi IP es -> ");
  Serial.println(WiFi.localIP());
}

void setup() {

  for (int i = 0; i < lineas; i ++) { //Declarar los pines de las columnas como salidas
    pinMode(columnas[i], OUTPUT);
  }
  for (int i = 0; i < pisos; i ++) { //Declarar los pines de las encenderPisos como salidas
    pinMode(niveles[i], OUTPUT);
  }
  Serial.begin(115200);
  setup_wifi();
  //establecemos en nuestro cliente las credenciales del servidor MQTT
  client.setServer(mqtt_server, mqtt_port);

  // //funcion que se llama cada que el servidor envĂ­e un mensaje
  client.setCallback(callback);
}


void loop() {
  // put your main code here, to run repeatedly:
  if(client.connected()==false){
    reconnect();
  }

  client.loop();
  
}