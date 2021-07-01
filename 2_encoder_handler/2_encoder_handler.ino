/* 
 * Author list: Neelabh Dubey
 * Filename:2_encoder_handler
 * Theme:Construct-o-bot
 * Functions :encoder_init(), leftEncoder(), rightEncoder()
 * Global variables:left_enB ,right_enB,right_counter,left_counter
 *
  */
  
/*==============================================================================================================================================
                                          Encoder handler: functions for handelling encoder of motors
===============================================================================================================================================*/
/*
 * function name: encoder_init
 * input: void 
 * output: void
 * logic:Under this function pin declaration and interrupt attachment of the encoder is done
 * Example call: encoder_init();
*/
void encoder_init(){

  left_enB = 53;//B0
  right_enB = 52;//B1
  
  pinMode(left_enB, INPUT);
  pinMode(right_enB, INPUT);

  attachInterrupt(0, leftEncoder, RISING);//E4
  attachInterrupt(1, rightEncoder, RISING);//E5

}



/*
 * function name: leftEncoder
 * input : void
 * output: void
 * logic: It increases value of left_counter if left wheel is moving in forward direction 
 *        else decreases value by one
 * example call: leftEncoder();
  
*/


void leftEncoder(){
  if (!digitalRead(left_enB)) left_counter++;
  else left_counter--;
}
/*
  * function name: rightEncoder
  * input :void
  * output: void
  * logic: it increases value of right_counter if right wheel is moving in forward direction 
           else decreases value by one
  * example call: rightEncoder();
*/
void rightEncoder(){
  if (digitalRead(right_enB)) right_counter++;
  else right_counter--;
}
