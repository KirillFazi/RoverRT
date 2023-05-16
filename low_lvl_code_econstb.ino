#include <math.h>
#include <AccelStepper.h>
#include <CNCShield.h>
#include<SoftwareSerial.h>

#define R_ENCODER_A 3
#define R_ENCODER_B 2
#define L_ENCODER_A 5
#define L_ENCODER_B 4

//переменные для робота, значения установлены для теста кода  
#define WHEEL_RADIUS 10
#define GEAR_RATIO 6.5 //поправочный коэфициент передаточного числа
#define MAX_SPEED 1000
CNCShield cnc_shield;
StepperMotor *motorRight = cnc_shield.get_motor(0);
StepperMotor *motorLeft = cnc_shield.get_motor(1);

//функции forwardstep() и backwardstep() нужны для работы либы AccelStepper. Я их прописал для левого и правого колеса
void forwardstepRight()
{
  motorRight->step(CLOCKWISE);
}
void backwardstepRight()
{  
  motorRight->step(COUNTER);
}
void forwardstepLeft()
{
  motorLeft->step(CLOCKWISE);
}
void backwardstepLeft()
{  
  motorLeft->step(COUNTER);
}

AccelStepper stepperRight(forwardstepRight, backwardstepRight);
AccelStepper stepperLeft(forwardstepLeft, backwardstepLeft);

int Encoder(int A = 0, int B = 0) {     //Функция для считывания сигналов из каналов А и В
  int pulses = 0;
  if ( digitalRead(B) == 0 ) {
    if ( digitalRead(A) == 0 ) {
      // Сигнал А упал, В нулевой
      pulses -= 1; // Движемся назад
    } else {
      // Сигнал А вырос, В нулевой
      pulses += 1; // Движемся вперед
    }
  } else {
    if ( digitalRead(A) == 0 ) {
      //Сигнал А упал, В положительный
      pulses += 1; // Движемся вперед
    } else {
      //Сигнал А вырос, В положительный
      pulses -= 1; // Движемся назад
    }
  }
  return pulses;
}

int speedOfWheels(float linearSpeedFunc, float speedOfRobotRotationFunc, float pathLenghtFunc) {
  float wheelSpeed;
  wheelSpeed = (1 / WHEEL_RADIUS)*(linearSpeedFunc + (speedOfRobotRotationFunc * pathLenghtFunc) / 2); // cкорость колеса в РАД\С
  wheelSpeed = (wheelSpeed * GEAR_RATIO) / 0,005; // перевод РАД/С в ШАГ/С
  wheelSpeed = ceil(wheelSpeed);
  wheelSpeed = int(wheelSpeed);
  return wheelSpeed;
}


void startMoving(int wheelSpeedRightFunc, int wheelSpeedLeftFunc) { //передача скоростей шилду
  stepperRight.setSpeed(wheelSpeedRightFunc);
  stepperLeft.setSpeed(wheelSpeedLeftFunc);
  stepperRight.runSpeed();
  stepperLeft.runSpeed();
}

int main() {

  float speedOfRobotRotation = 0; //скорость поворота робота
  float pathLenght = 0; //длина пути
  int wheelSpeedRight = 0;
  int wheelSpeedLeft = 0;
  float linearSpeed = 0;
  int encoderRight = 0;
  int encoderLeft = 0;

  Serial.begin(9600);
  pinMode(R_ENCODER_A, INPUT);
  pinMode(R_ENCODER_B, INPUT); 
  pinMode(L_ENCODER_A, INPUT);
  pinMode(L_ENCODER_B, INPUT); 
  attachInterrupt(0, Encoder(R_ENCODER_A, R_ENCODER_B), CHANGE);
  attachInterrupt(0, Encoder(L_ENCODER_A, L_ENCODER_B), CHANGE);

  cnc_shield.begin();
  stepperRight.setMaxSpeed(MAX_SPEED); //необходимо указать максимальную скорость в шагах в секунду, 1000 стоит для примера
  stepperRight.setMaxSpeed(MAX_SPEED);

  while(true) {
    wheelSpeedRight = speedOfWheels(linearSpeed, speedOfRobotRotation, pathLenght);
    wheelSpeedLeft = speedOfWheels(linearSpeed, -speedOfRobotRotation, pathLenght);
    startMoving(wheelSpeedRight, wheelSpeedLeft);
    encoderRight = Encoder(R_ENCODER_A, R_ENCODER_B);
    encoderRight = Encoder(L_ENCODER_A, L_ENCODER_B);
  }
}

//СРАВНИВАЕМ ПОКАЗАНИЯ МАГНИТОМЕТРА И ЕСЛИ ОНИ РАВНЫ НУЛЮ, ТО УГЛОВАЯ СКОРОСТЬ РАВНО N-РАДИАН В СЕКУНДУ, ЕСЛИ МАГНИТОМЕТР ПОКАЗЫВАЕТ ЧТО МЫ ИДЕМ ТОЧНО ПО КУРСУ ТО СТАВИМ УГЛОВУЮ СКОРОСТЬ РАВНОЙ НУЛЮ И РОБОТ ЕДЕТ ТОЛЬКО С ЛИНЕЙНОЙ СКОРОСТЬЮ
