/* 
 * Author list: Neelabh Dubey
 * Filename:5_buzzer
 * Theme: Construct-o-bot
 * Functions:void buzzer_init(), void beep(),_stop(),
 * Global variables:  buzzer
 */
 
  /*
  * function name: buzzer_init
  * input: void 
  * output: void
  * logic: for initilization of buzzer pins
  * Example call: buzzer_init();
*/
void buzzer_init(){
  buzzer = 51;//B2
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
}
/*
 * function name: beep
 * input: void 
 * output: void
 * logic: it turns on the buzzer for 20 milli seconds and then turns off
 * example call: beep();
*/
void beep(){
  _stop();
  digitalWrite(buzzer, LOW);
  delay(20);
  digitalWrite(buzzer, HIGH);
  delay(20);
}
