#include <Ps3Controller.h>

// Pines de los cables de los motores
const int M1L = 5;//Motor izquierdo hacia adelante
const int M1R = 18;//Motor izquierdo hacia atras
const int M2L = 22;//Motor derecho hacia adelante
const int M2R = 23;//Motor derecho Hacia atras
const int ARML = 16;//Arma
const int ARMR = 4;//arma

// Propiedades PWM
const int frecuencia = 5000;
const int canalM1L = 0;
const int canalM1R = 1;
const int canalM2L = 2;
const int canalM2R = 3;
const int canalARML = 4;
const int canalARMR = 5;
const int resolucion = 8;

// Variable para la batería del control
int bateria;

// Mensaje al conectarse el control
void onConnect(){
  Serial.println("Control conectado.");
}

void setup() {

  Serial.begin(115200);

  // Configuración de los pines de los motores como salidas
  pinMode(M1L, OUTPUT);
  pinMode(M1R, OUTPUT);
  pinMode(M2L, OUTPUT);
  pinMode(M2R, OUTPUT);
  pinMode(ARML, OUTPUT);
  pinMode(ARMR, OUTPUT);

  // configuración de la funcionalidad PWM
  ledcSetup(canalM1L, frecuencia, resolucion);
  ledcSetup(canalM1R, frecuencia, resolucion);
  ledcSetup(canalM2L, frecuencia, resolucion);
  ledcSetup(canalM2R, frecuencia, resolucion);
  ledcSetup(canalARML, frecuencia, resolucion);
  ledcSetup(canalARMR, frecuencia, resolucion);

  // Asignación de canales PWM a cada cable de motor
  ledcAttachPin(M1L, canalM1L);
  ledcAttachPin(M1R, canalM1R);
  ledcAttachPin(M2L, canalM2L);
  ledcAttachPin(M2R, canalM2R);
  ledcAttachPin(ARML, canalARML);
  ledcAttachPin(ARMR, canalARMR);

  // Configuración e inicio del control 
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("b8:27:eb:52:7e:31");
  Serial.println("Listo para conectar.");
  
}

void loop() {

  if(!Ps3.isConnected()){
    Serial.println("Control desconectado.");
    return;
  }
  int leftJoyIn = Ps3.data.analog.stick.ly;

  int rightJoyIn = Ps3.data.analog.stick.rx;

  if(leftJoyIn<-10 && rightJoyIn==-1){

    //Mover hacia enfrente (ambos motores giran hacia adelante)

    int motorPowerDR = map((leftJoyIn*(-1)), 0, 128, 0, 255);
    Serial.print("Avanzando");

    //Todos en 0 excepto los que van a funcionar
    ledcWrite(canalM1R, 0);
    ledcWrite(canalM2R, 0);

    //Estos son los que van a funcionar
    ledcWrite(canalM1L, motorPowerDR);
    ledcWrite(canalM2L, motorPowerDR); 

  }else if(leftJoyIn>10 && rightJoyIn==-1){

    //Mover hacia atras (ambos motores giran hacia atras)

    int motorPowerDR = map(leftJoyIn, 0, 128, 0, 255);
    Serial.print("Retrocediendo");

    //En 0 los que no van a funcionar
    ledcWrite(canalM1L, 0);
    ledcWrite(canalM2L, 0);

    //Estos son los que van a funcionar
    ledcWrite(canalM1R, motorPowerDR);
    ledcWrite(canalM2R, motorPowerDR);

  }else if(leftJoyIn==-1 && rightJoyIn>10){


    //Girar hacia la derecha(Motor 1 hacia enfrente y motor 2 hacia atras)

    int motorPowerLR = map(rightJoyIn, 0, 128, 0, 255);
    Serial.print("Girando a la derecha");

    //En 0 los que no van a funcionar
    ledcWrite(canalM1R, 0);//motor 1 hacia atras apagado
    ledcWrite(canalM2L, 0);//motor 2 hacia enfrente apagado

    //Estos son los que van a funcionar
    ledcWrite(canalM1L, motorPowerLR);//motor 1 hacia enfrente potencia del joystick
    ledcWrite(canalM2R, motorPowerLR);//motor 2 hacia atras potencia del joystick

  }else if(leftJoyIn==-1 && rightJoyIn<-10){

    
    //Girar hacia la izquierda (motor 1 hacia atras y motor 2 hacia enfrente)

    int motorPowerLR = map((rightJoyIn*(-1)), 0,128, 0, 255);
    Serial.print("Girando a la izquierda");

    //En 0 los que no funcionan
    ledcWrite(canalM1L, 0);
    ledcWrite(canalM2R, 0);

    //Estos son los que si funcionan
    ledcWrite(canalM1R, motorPowerLR);
    ledcWrite(canalM2L, motorPowerLR);

  }else if(leftJoyIn<-10 && rightJoyIn<-10){


    //Avanzar + Girar hacia la izquierda (reducir considerablemente la potencia del motor izquierdo)

    int motorPowerDR = map((leftJoyIn*(-1)), 0, 128, 0, 255);
    Serial.print("Avanzando y girando hacia la izquierda");

    //En 0 los que no funcionan
    ledcWrite(canalM1R, 0);
    ledcWrite(canalM2R, 0);

    //Estos son los que si funcionan
    ledcWrite(canalM1L, (motorPowerDR/6));//Se reduce la potencia del motor izquierdo para que gire, pero no se detenga la rueda completamente
    ledcWrite(canalM2L, motorPowerDR);//Esta continua con la potencia del joystic

  }else if(leftJoyIn<-10 && rightJoyIn>10){

    
    //Avanzar + Girar hacia la derecha (reducir considerablemente la potencia del motor derecho )

    int motorPowerDR = map((leftJoyIn*(-1)), 0, 128, 0, 255);
    Serial.print("Avanzando y girando hacia la derecha");

    //En 0 los que no funcionan
    ledcWrite(canalM1R, 0);
    ledcWrite(canalM2R, 0);

    //Estos son los que si funcionan
    ledcWrite(canalM1L, motorPowerDR);//Potencia queda igual
    ledcWrite(canalM2L, (motorPowerDR/6));//se Reduce la potencia a una sexta parte

  }else if(leftJoyIn>10 && rightJoyIn<-10){


    //Retroceder + Girar hacia la izquierda (reducir considerablemente la potencia del motor izquierdo)

    int motorPowerDR = map(leftJoyIn, 0, 128, 0, 255);
    Serial.print("Retrocediendo y girando a la izquierda");

    //En 0 los que no funcionan
    ledcWrite(canalM1L, 0);
    ledcWrite(canalM2L, 0);

    //Estos son los que si funcionan
    ledcWrite(canalM1R, (motorPowerDR/6));//Se reduce la potencia del motor izquierdo para que gire, pero no se detenga la rueda completamente
    ledcWrite(canalM2R, motorPowerDR);//Esta continua con la potencia del joystic

  }else if(leftJoyIn>10 && rightJoyIn>10){


    //retoceder + Girar hacia la derecha (reducir considerablemente la potencia del motor derecho)

    int motorPowerDR = map(leftJoyIn, 0, 128, 0, 255);
    Serial.print("Retrocediendo y girando a la derecha");

    //En 0 los que no funcionan
    ledcWrite(canalM1L, 0);
    ledcWrite(canalM2L, 0);

    //Estos son los que si funcionan
    ledcWrite(canalM1R, motorPowerDR);//Continua la misma potencia
    ledcWrite(canalM2R, (motorPowerDR/6));//Se reduce la potencia a /6

  }else if(leftJoyIn == -1 && rightJoyIn == -1){

    Serial.println("Motores en 0");

      // Todos los canales de los motores de movimiento en 0
    ledcWrite(canalM1L, 0);
    ledcWrite(canalM1R, 0);
    ledcWrite(canalM2L, 0);
    ledcWrite(canalM2R, 0);

  }

}