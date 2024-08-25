#include <IR_Remote_Raw.h>

#define ir_send_pin 3

IRSend irsend(ir_send_pin);

#define ir_send_vals_len 256

uint16_t ir_send_vals[ir_send_vals_len] = {8366, 4316,  426, 1714,  424, 616,  452, 616,  452, 616,  454, 1712,  424, 614,  454, 614,  454, 616,  454, 614,  454, 614,  454, 616,  452, 614,  454, 614,  454, 614,  452, 616,  452, 616,  452, 1712,  424, 614,  454, 1712,  424, 616,  452, 614,  452, 1712,  424, 614,  454, 1710,  426, 1712,  424, 1712,  426, 1710,  426, 1710,  426};

void setup() {
  Serial.begin(115200);
  irsend.begin();
}

void loop() {
  Serial.println("Press any key to send the IR data...");
  while (Serial.available() <= 0);
  irsend.sendRaw(ir_send_vals, ir_send_vals_len, 50);
  Serial.println("IR Data Has Been Sent");
}
