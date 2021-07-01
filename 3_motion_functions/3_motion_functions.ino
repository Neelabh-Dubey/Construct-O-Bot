/* 
 * Author list: Neelabh Dubey
 * Filename:3_motion_functions
 * Theme:Construct-o-bot
 * Functions:  motion_init(), forward(int), backward(int), right(int ),left(int)
 *            soft_right(int ),soft_left(int ),soft_right_back(int),soft_left_back(int) 
 *            node_left(),node_right(), node_forward(),turn_180(),  move_forward() , move_backward(), 
 *            follow_black_line(int),readline(),_stop(),_search(int,int),deb(int)
 * Global variables:    m_lf,  m_lb,  m_rf,  m_rb , velocity, left_counter, right_counter
 */
/*
* Function name:motion_init
* Input:void
* Output:void
* Logic:Used for initializing the motor pins
* example call: motion_init();
*/
void motion_init(){
  m_rb = 6;//h3
  m_rf = 7;//h4
  m_lf = 8;//h5
  m_lb = 9;//h6

  pinMode(m_lf, OUTPUT);
  pinMode(m_lb, OUTPUT);
  pinMode(m_rf, OUTPUT);
  pinMode(m_rb, OUTPUT);

}

/*
 * function name: forward
 * input: velocity
 * output: void 
 * logic:It instructs the bot to move in forward direction at given velocity
 * example call: forward(225);
*/
void forward(int velocity){
  analogWrite(m_lf, velocity);
  analogWrite(m_lb, 0);
  analogWrite(m_rf, velocity);
  analogWrite(m_rb, 0);
}
/*
 * function name: backward
 * input: velocity
 * output: void 
 * logic:It instructs the bot to move in backward direction at given velocity
 * example call: backward(180);
*/
void backward(int velocity){
  analogWrite(m_lf, 0);
  analogWrite(m_lb, velocity);
  analogWrite(m_rf, 0);
  analogWrite(m_rb, velocity);
}
/*
 * function: soft_right
 * input: velocity
 * output: void 
 * logic:It instructs the bot to move slowly in forward right direction
 *        by moving forward the left wheel only 
 * example call: soft_right(180);
*/
void soft_right(int velocity){
  velocity = velocity > 255 ? 255 : velocity;
  analogWrite(m_lf, velocity);
  digitalWrite(m_lb, LOW);
  digitalWrite(m_rf, LOW);
  digitalWrite(m_rb, LOW);
}
/*
  * function name: soft_left
  * input: velocity
  * output: void 
  * logic:It instructs the bot to move slowly in forward left direction
  *        by moving forward the right wheel only
  *example call: soft_left(180);        
     
*/
void soft_left(int velocity){
  velocity = velocity > 255 ? 255 : velocity;
  digitalWrite(m_lf, LOW);
  digitalWrite(m_lb, LOW);
  analogWrite(m_rf, velocity);
  digitalWrite(m_rb, LOW);
}
/*
 * function name: soft_right_back
 * input: velocity
 * output: void 
 * logic: It instructs the bot to move slowly in reverse left direction
  *        by moving backward the right wheel only
  * example call: soft_right_back(180);  
*/
void soft_right_back(int velocity){
  velocity = velocity > 255 ? 255 : velocity;
  digitalWrite(m_lf, LOW);
  digitalWrite(m_lb, LOW);
  digitalWrite(m_rf, LOW);
  analogWrite(m_rb, velocity);
}
/*
  * function name: soft_left_back
  * input: velocity
  * output: void 
  * logic:It instructs the bot to move slowly in reverse left direction
  *        by moving backward the right wheel only 
  * example call: soft_right_back(180);        
*/
void soft_left_back(int velocity){
  velocity = velocity > 255 ? 255 : velocity;  
  digitalWrite(m_lf, LOW);
  analogWrite(m_lb, velocity);
  digitalWrite(m_rf, LOW);
  digitalWrite(m_rb, LOW);
}
/*
 * function: right
 * input: velocity
 * output: void 
 * logic: It instructs the bot to move in right direction at given velocity
 *         by moving left wheel forward and right wheel backward
 * example call: right(160);
*/
void right(int velocity){
  analogWrite(m_lf, velocity);
  analogWrite(m_lb, 0);
  analogWrite(m_rf, 0);
  analogWrite(m_rb, velocity);
}
/*
 * function name: left
 * input: velocity
 * output: void 
 * logic: It instructs the bot to move in left direction at given velocity
 *          by moving right wheel forward and left wheel backward
 * example call: left(180);
*/
void left(int velocity){
  analogWrite(m_lf, 0);
  analogWrite(m_lb, velocity);
  analogWrite(m_rf, velocity);
  analogWrite(m_rb, 0);
}
/*
 * function name: _stop
 * input: void
 * output: void 
 * logic:It instructs the bot to stop
 * example call: stop();
*/
void _stop(){
  digitalWrite(m_lf, LOW);
  digitalWrite(m_lb, LOW);
  digitalWrite(m_rf, LOW);
  digitalWrite(m_rb, LOW);
}
/*
 * function: node_left
 * input: void
 * output: void 
 * logic: it moves the bot left to one node and then takes the bot back on line
 * example call: node_left();
*/
void node_left(){
  left_counter = 0;
  right_counter = 0;
  
  while(left_counter < 195 && right_counter < 195) forward(255);
  while(left_counter < 195) soft_right(255);
  while(right_counter < 195) soft_left(255);
  _stop();
  delay(50);
  
  left_counter = 305;
  right_counter = 0;
  while(left_counter > 0 && right_counter < 305) left(255);
  while(left_counter > 0) soft_left_back(255);
  while(right_counter < 305) soft_left(255);
  read_line();
  if(line == "WWW") search(20, 0);
  _stop();
}

/*
 * function: node_right
 * input: void
 * output: void 
 * logic: it moves the bot right to one node and then takes the bot back on line
 * example call: node_right();
*/
void node_right(){
  left_counter = 0;
  right_counter = 0;
  
  while(left_counter < 195 && right_counter < 195) forward(255);
  while(left_counter < 195) soft_right(255);
  while(right_counter < 195) soft_left(255);
  _stop();
  delay(50);
  
  left_counter = 0;
  right_counter = 300;
  while(left_counter < 300 && right_counter > 0) right(255);
  while(left_counter < 300) soft_right(255);
  while(right_counter > 0) soft_right_back(255);
  read_line();
  if(line == "WWW") search(20, 1);
  _stop();
}
/*
 * function name: turn_180
 * input: void
 * output: void 
 * logic:It instructs the bot to turn by 180 degrees
 * example call: turn_180();
*/
void turn_180(){
  right_counter = 0;
  left_counter = 730;
  while(right_counter < 730 && left_counter > 0) left(255);
  while(right_counter < 730) soft_left(255);
  while(left_counter > 0) soft_left_back(255);
  _stop();
  read_line();
  if(line == "WWW") search(20, 0);
  _stop();
} 

/*
  * function name: node_forward
  * input: void
  * output: void 
  * logic: it helps the bot to cross the node
  * example call: node_forward();
*/
void node_forward(){
  left_counter = 0;
  right_counter = 0;
  
  while(left_counter < 80 && right_counter < 80) forward(255);
  while(left_counter < 80) soft_right(255);
  while(right_counter < 80) soft_left(255);
  read_line();
  if(line == "WWW") search(20, 1);
}
/*
  * function: follow_black_line
  * input: void
  * output: void 
  * logic:This function helps the bot to follow the black line without deviation
  * example call: follow_black_line(255);
*/
void follow_black_line(int velocity){
  if((line == "BWW")) soft_left(velocity);
  else if((line == "BBW")) {
    left(velocity);
    delay(17);
    _stop();
  }
  else if((line == "WWB")) soft_right(velocity);
  else if(line == "WBB"){
    right(velocity);
    delay(17);
    _stop();
  }
  else forward(velocity);
}
/*
  * function:move_forward
  * input:encoder value
  * output: void 
  * logic:This function helps the bot to move in forward direction without deviation
  * example call:move_forward(300);
*/
void move_forward(int enc){
  left_counter = right_counter = 0;
  
  while(left_counter < enc && right_counter < enc) forward(255);
  while(left_counter < enc) soft_right(255);
  while(right_counter < enc) soft_left(255);
  _stop();
}
/*
  * function:move_backward
  * input:encoder value
  * output: void 
  * logic:This function helps the bot to move in backward direction without deviation
  * example call:move_backward(500);
*/
void move_backward(int enc){
  left_counter = right_counter = enc;  
  while(left_counter > 0 && right_counter > 0) backward(255);
  while(left_counter > 0) soft_left_back(255);
  while(right_counter > 0) soft_right_back(255);
  _stop();
}

     
/*
 * Function: deb
 * input : time in miliseconds
 * output: void 
 * logic: this function holds the bot in hold condition for given duration, mainly used for debugging purpose
 * Example call:deb(1500);
*/
void deb(long int duration){
  _stop();
  delay(duration);
}
