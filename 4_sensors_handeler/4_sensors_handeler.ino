/* 
 * Author list: Neelabh Dubey
 * Filename: 4_sensors_handeler
 * Theme:Construct-o-bot
 * Functions: sensors_init(),read_line(),read_boxes()
 * Global variables: int ir_1,int ir_2 , int ir_3,String line, int left_sh,int right_sh
 *
/*
* Function name:sensors_init
* input:void
* output:void
* Logic:function for initiliztion of pins for the sensors and line variable
* Example call:sensors_init();
*/
void sensors_init(){
  line = ""; 
}

/*
 * function: read_line
 * input: void 
 * output: void
 * logic: This function updates the value of the global variable "line" with current values 
 *        read by the white line sensors and conveys the bot whether the line is black or white
 * Example call: read_line();
*/
void read_line(){
  ir_l = analogRead(A0);
  ir_m = analogRead(A1);
  ir_r = analogRead(A2);
//    Serial.print(ir_l);
//    Serial.print(" ");
//    Serial.print(ir_m);
//    Serial.print(" ");
//    Serial.println(ir_r);
  line = "";
  if(ir_l > 50) line += 'B'; else line += 'W';
  if(ir_m > 50) line += 'B'; else line += 'W';
  if(ir_r > 50) line += 'B'; else line += 'W';
}
/*Function:read_boxes
*Input:void
*Outut:void
*Logic:This function is used to read values from the front sharp sensors when it faces a CM
*Example call: read_boxes();
*/
void read_boxes(){
  left_sh = analogRead(A3);//F3
  right_sh = analogRead(A4);//F4
  Serial.print(left_sh);
  Serial.print(" ");
  Serial.println(right_sh);
}
