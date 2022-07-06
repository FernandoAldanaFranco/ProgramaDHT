#include "DHT.h"
#define DHTPIN 12     // Pin donde está conectado el sensor
#define DHTTYPE DHT11   // Descomentar si se usa el DHT 11
//Componentes del sistema
#define LED1 4
#define LED2 2
#define boton1 14
#define boton2 15
#define boton3 13
//DHT 
DHT dht(DHTPIN, DHTTYPE);
//Banderas de botones
int manual, demanda, sobrecarga;
//Variables de sensor
  float h; //humedad
  float t; //temperatura
  float f; //Temperatura en °F
void setup() {
  //Inicializa entradas y salidas
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);
  pinMode(boton3, INPUT);
  //Inicializa banderas de botones
  manual=0;
  demanda=0;
  sobrecarga=0;
  Serial.begin(9600);
  Serial.println("Iniciando sensor y sistema");
  dht.begin();
  Serial.println("Inicia loop");
}
void loop() {
  leer_botones();
  leer_sensor();
  actuacion();
  //Espera un segundo y repite el proceso
  delay(1000);
}

//Función que se encarga de leer los estados de los botones y cambiar el estado de las banderas
void leer_botones(void){
  delay(10);
  if(digitalRead(boton1)==true)manual=1;
  else manual=1;
  delay(10);
  if(digitalRead(boton2)==true)demanda=1;
  else demanda=1;
  delay(10);
  if(digitalRead(boton3)==true)sobrecarga=1;
  else sobrecarga=1;
}
//Función para leer el sensor
void leer_sensor(void){
  h = dht.readHumidity(); //Leemos la Humedad
  t = dht.readTemperature(); //Leemos la temperatura en grados Celsius
  f = dht.readTemperature(true); //Leemos la temperatura en grados Fahrenheit
}
//Función para cambiar los actuadores
void actuacion(void){
  //Pone ambas salidas a 0
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  //Que se encienda la refrigeracion manual cada que se presione el boton de manual
  if(manual==1){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  }else{
    // La refrigeracion manual tiene prioridad a la refrigeracion automática.
    if((t>28)||(demanda==1)||(sobrecarga==1)){
      //Si la termperatura es alta (mayor a 28, por ejemplo), se activa la refrigeracion automática
      digitalWrite(LED2, HIGH);  
    }
  }
  if((demanda==1)||(sobrecarga==1)){
    // Si tengo alta demanda o sobre carga, se activa la refrigeración automática
    digitalWrite(LED2, HIGH);
    if(t>28){
      //Si tengo alta demanda o sobrecarga de funcionamiento y ademas temperatura alta, se activan ambas refrigeraciones
      digitalWrite(LED1, HIGH);
    }
  }
}
