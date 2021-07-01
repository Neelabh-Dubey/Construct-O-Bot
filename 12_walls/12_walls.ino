/* 
 * Author list: Neelabh Dubey
 * Filename:12_walls
 * Theme:Construct-o-bot
 * Fuctions: forward(),follow_walls(),follow_black_line(int),smooth_forward(),soft_left(int),soft_right(int),
 * Global variables:left_counter,right_counter
 */
 
  /* Function name:smooth_forward
* input:Void
* Output:void
* Logic:This function is used to direct the bot to move in forward direction between the walls without any deviation
* Example call:smooth_forward();
*/
void smooth_forward(){
  if(left_counter-right_counter > 50) while(left_counter != right_counter) soft_left(255);  //if the bot deviates towards the right
  else if(right_counter-left_counter > 50) while(left_counter != right_counter) soft_right(255);  //If the bot deviates towards the left
  else forward(255);
}


/*
  * Function: follow_walls
  * Input:void
  * Output:void
  * Logic: function to follow walls
  * example call: follow_walls();
*/
void follow_walls(){
  left_counter = 0;
  while(left_counter < 1000) follow_black_line(255); // change values

  left_counter = right_counter = 0;
  while(left_counter < 1000) smooth_forward(); // change values
  
  left_counter = 0;
  while(left_counter < 1000) follow_black_line(255); // change values  
}
