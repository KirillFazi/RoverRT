#include "log.h"
#include <GParser.h>

#define ASCII_CONVERT '0'
#define MAX_SIZE_BUFF 10
#define MAX_SIZE_INPUT_BUFF 5
#define ENC_STEP_DELAY 10

char buffer_in[MAX_SIZE_INPUT_BUFF];
static int data_move_buff[MAX_SIZE_BUFF];

enum buff_data_number_t {
  SPEED  = 1,
  ANGLE,
  DISTANCE
};

enum error_process_t {
  ENCODER  = 1,
  OPTICAL_SENS,
  MOTO
};

struct Str {
  char start_msg;
  char devide;
  int code_msg;
  int data_msg;
  char end_msg;
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  check_data_recieve();
  if(check_process()){
    send_data(check_process(), NULL);
  }
}

void check_data_recieve() {
  if (read_data()) {
    switch (data_move_buff[0]) {
      case 0:
        movement(data_move_buff[SPEED], data_move_buff[ANGLE], data_move_buff[DISTANCE]);
        break;
      case 1:
        send_data_new();
        break;
      case 2:
        extra_stop();
        break;
      case 3:
        start_working();
        break;
    }
  }
}

int read_data() {
  static bool parseStart = false;
  static byte counter = 0;
  if (Serial.available()) {
    GParser data(buffer_in, ',');
    char in = Serial.read();
    if (in == '\n' || in == '\r') return 0;
    if (in == ';') {
      parseStart = false;
      return counter;
    }
    if (in == '$') {
      parseStart = true;
      //      GParser data(buffer_in, ',');
      counter = 0;
      return 0;
    }
    if (parseStart) {
      data_move_buff[counter] = data.getInt(counter);
      counter++;
    }
  }
  return 0;
}

//int copy_data(byte counter_data) {
//  data_move_buff[counter_data] = data.getInt(counter_data);
//}

void movement(int speed_normally, int angle, int distance) {

}

void send_data_new() {

}

void extra_stop() {

}

void start_working() {

}

int check_process() {
  if (get_flag_enc() == true) {
    static int timer_enc_first;
    static int enc_counter;
    if (millis() - timer_enc_first >= ENC_STEP_DELAY) {
      if (get_flag_enc() != false) {
        enc_counter++;
      }
      if (enc_counter >= 3) {
        return ENCODER;
      }
    }
  }
return 0;
}

int send_data(int code, int data) {
  Str buff;
  buff.start_msg = '#';
  buff.devide = ',';
  buff.code_msg = code;
  buff.devide = ',';
  buff.data_msg = data;
  buff.devide = ',';
  buff.end_msg = ';';
  Serial.write((char*)&buff);
}

bool get_flag_enc() {
  
}
