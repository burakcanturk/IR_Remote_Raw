#include <IR_Remote.h>

#define ir_recv_pin 2

IRRecv irrecv(ir_recv_pin);

void setup() {
  Serial.begin(115200);
  irrecv.begin();
}

void loop() {

  uint16_t vals[256];

  Serial.println("IR receiver is waiting for a signal...");
  int len = irrecv.recvRaw(vals, 30000);
  while (len < 32 and  len != -1) len = irrecv.recvRaw(vals, 30000);

  Serial.println("Copy these commands to the sending_ir_raw.ino file.\n");

  Serial.print("ir_send_vals_len = ");
  Serial.print(len);
  Serial.println(";");
  Serial.print("ir_send_vals[256] = {");
  for (int i = 0; i < len - 1; i++) {
    Serial.print(vals[i]);
    Serial.print(", ");
  }
  Serial.print(vals[len - 1]);
  Serial.println("};");

  Serial.println();
}
