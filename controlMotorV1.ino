onst int M1L = 5;//Motor izquierdo hacia adelante
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
const int canal ARMR = 5;
const int resolucion = 8;


void setup() {
  pinMode(M1L, OUTPUT);
  pinMode(M1R, OUTPUT);
  pinMode(M2L, OUTPUT);
  pinMode(M2R, OUTPUT);
  pinMode(ARML, OUTPUT);
  pinMode(ARMR, OUTPUT);

  // configuración de la funcionalidad pwm

  ledcSetup(canalM1L, frecuencia, resolucion);
  ledcSetup(canalM1R, frecuencia, resolucion);
  ledcSetup(canalM2L, frecuencia, resolucion);
  ledcSetup(canalM2R, frecuencia, resolucion);

  ledcAttachPin(M1L, canalM1L);
  ledcAttachPin(M1R, canalM1R);
  ledcAttachPin(M2L, canalM2L);
  ledcAttachPin(M2R, canalM2R);
  ledcAttachPin(ARML, canal);
  ledcAttachPin(ARMR, canal);
}

void loop() {
  int leftJoyIn = Ps3.data.analog.stick.ly;

  int rightJoyIn = PS3.data.analog.sticky.rx;

  if(leftJoyIn<-10 && rightJoyIn==0){
    //Mover hacia enfrente (ambos motores giran hacia adelante)

    int motorPowerDR = map(leftJoyIn, 0, -128, 0, 255);

    //Todos en 0 excepto los que van a funcionar
    ledcWrite(canalM1R, 0);
    ledcWrite(canalM2R, 0);

    //Estos son los que van a funcionar
    ledcWrite(canalM1L, motorPowerDR);
    ledcWrite(canalM2L, motorPowerDR); 

  }else if(leftJoyIn>10 && rightJoyIn==0){
    //Mover hacia atras (ambos motores giran hacia atras)

    int motorPowerDR = map(leftJoyIn, 0, 128, 0, 255);

    //En 0 los que no van a funcionar
    ledcWrite(canalM1L, 0);
    ledcWrite(canalM2L, 0);

    //Estos son los que van a funcionar
    ledcWrite(canalM1R, motorPowerDR);
    ledcWrite(canalM2R, motorPowerDR);

  }else if(leftJoyIn== 0 && rightJoyIn>10){
    //Girar hacia la derecha(Motor 1 hacia enfrente y motor 2 hacia atras)

    int motorPowerLR = map(rightJoyIn, 0, 128, 0, 255);

    //En 0 los que no van a funcionar
    ledcWrite(canalM1R, 0); //motor 1 hacia atras apagado
    ledcWrite(canalM2L, 0); //motor 2 hacia enfrente apagado

    //Estos son los que van a funcionar
    ledcWrite(canalM1L, motorPowerLR);  //motor 1 hacia enfrente potencia del joystick
    ledcWrite(canalM2R, motorPowerLR);  //motor 2 hacia atras potencia del joystick

  }else if(leftJoyIn==0 && rightJoyIn<-10){
    //Girar hacia la izquierda (motor 1 hacia atras y motor 2 hacia enfrente)

    int motorPowerLR = map(rightJoyIn, 0,-128, 0, 255);

    //En 0 los que no funcionan
    ledcWrite(canalM1L, 0);
    ledcWrite(canalM2R, 0);

    //Estos son los que si funcionan
    ledcWrite(canalM1R, motorPowerLR);
    ledcWrite(canalM2L, motorPowerLR);

  }else if(leftJoyIn<-10 && rightJoyIn<-10){
    //Avanzar + Girar hacia la izquierda (reducir considerablemente la potencia del motor izquierdo)

    int motorPowerDR = map(leftJoyIn, 0, -128, 0, 255);

    //En 0 los que no funcionan
    ledcWrite(canalM1R, 0);
    ledcWrite(canalM2R, 0);

    //Estos son los que si funcionan
    ledcWrite(canalM1L, (motorPowerDR/6));//Se reduce la potencia del motor izquierdo para que gire, pero no se detenga la rueda completamente
    ledcWrite(canalM2L, motorPowerDR);//Esta continua con la potencia del joystic
  }else if(leftJoyIn<-10 && rightJoyIn<-10){
    //Avanzar + Girar hacia la izquierda (reducir considerablemente la potencia del motor izquierdo)

    int motorPowerDR = map(leftJoyIn, 0, -128, 0, 255);

    //En 0 los que no funcionan
    ledcWrite(canalM1R, 0);
    ledcWrite(canalM2R, 0);

    //Estos son los que si funcionan
    ledcWrite(canalM1L, (motorPowerDR/6));//Se reduce la potencia del motor izquierdo para que gire, pero no se detenga la rueda completamente
    ledcWrite(canalM2L, motorPowerDR);//Esta continua con la potencia del joystic

  }else if(leftJoyIn<-10 && rightJoyIn>10){
    //Avanzar + Girar hacia la izquierda (reducir considerablemente la potencia del motor izquierdo)

    int motorPowerDR = map(leftJoyIn, 0, -128, 0, 255);

    //En 0 los que no funcionan
    ledcWrite(canalM1R, 0);
    ledcWrite(canalM2R, 0);

    //Estos son los que si funcionan
    ledcWrite(canalM1L, motorPowerDR);//Se reduce la potencia del motor izquierdo para que gire, pero no se detenga la rueda completamente
    ledcWrite(canalM2L, (motorPowerDR/6));//Esta continua con la potencia del joystic
  }else if(leftJoyIn>10 && rightJoyIn<-10){
    //Avanzar + Girar hacia la izquierda (reducir considerablemente la potencia del motor izquierdo)

    int motorPowerDR = map(leftJoyIn, 0, 128, 0, 255);

    //En 0 los que no funcionan
    ledcWrite(canalM1L, 0);
    ledcWrite(canalM2L, 0);

    //Estos son los que si funcionan
    ledcWrite(canalM1R, (motorPowerDR/6));//Se reduce la potencia del motor izquierdo para que gire, pero no se detenga la rueda completamente
    ledcWrite(canalM2R, motorPowerDR);//Esta continua con la potencia del joystic

  }else if(leftJoyIn>10 && rightJoyIn>10){
    //Avanzar + Girar hacia la izquierda (reducir considerablemente la potencia del motor izquierdo)

    int motorPowerDR = map(leftJoyIn, 0, 128, 0, 255);

    //En 0 los que no funcionan
    ledcWrite(canalM1L, 0);
    ledcWrite(canalM2L, 0);

    //Estos son los que si funcionan
    ledcWrite(canalM1R, motorPowerDR);//Se reduce la potencia del motor izquierdo para que gire, pero no se detenga la rueda completamente
    ledcWrite(canalM2R, (motorPowerDR/6));//Esta continua con la potencia del joystic
  }


  
}
