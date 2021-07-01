
/* 
 * Author list: Neelabh Dubey
 * Filename:9_pick_place_handler
 * Theme:Construct-o-Bot()
 * Fuctions:pick_place_init(),isHigh(int), search_for_mid(int,int,int),set_gripper(int),set_up_down(int),
 *               deb(int),pick(), place(int),readline(),
 *               _stop(),move_backward(int),move_forward(int velocity)             
  * Global variables:  left_counter,right_counter, line, current_node ,readline(),floor_array[int],

 */
 
  /*
 * Function name: pick_place_init
 * Input: void
 * Output: Void
 * Logic: This function is used to initialise pins and power input for various servos used in the arm of the bot 
 * Example call: pick_place_init();
 */
void pick_place_init(){
  gp.attach(11);//B5  
  up_down.attach(10);//B4

  gp.write(gp_pos);
  up_down.write(up_down_pos);
}
/*Function name: isHigh
* Input:node number
* Output:void
* Logic:this function returns true if the house on the node is high
* example call: isHigh(10);
 */

bool isHigh(int node){
  if(node == 4) return floor_array[0];
  if(node == 14) return floor_array[1];
  if(node == 6) return floor_array[2];
  if(node == 12) return floor_array[3];
  if(node == 9) return floor_array[4];
}

/*
* Function:search_for_mid
* Input:number of searches and direction to be moved in
* Output:void
* Logic:This function instructs the bot to how to follow the black line symmetrically without any deviation
* Example call:search_for_mid(40,2,255);
*/
void search_for_mid(int num, int dir, int vel){
  if (dir == 1){
    for(int i = 0; i < num; i++){
      left_counter = 0;
      while(left_counter < 3) right(vel);
      _stop();
      delay(10);
      read_line();
      if(line == "WBW") return;
    }
    search_for_mid(60, 0, vel);
  }
  else{
    for(int i = 0; i < num; i++){
      right_counter = 0;
      while(right_counter < 3) left(vel);
        _stop();
      delay(10);
      read_line();
      if(line == "WBW") return;
    }  
    search_for_mid(60, 1, vel);
  }
}


/*
 * Function:set_gripper
 * Input:position
 * Output:void
 * Logic:This function instructs the bot to how to grip
 * Example call:set_gripper(60);
*/
void set_gripper(int pos){
  for(; gp_pos < pos; gp_pos++){
    gp.write(gp_pos);
    delay(8);    
  }
  for(; gp_pos > pos; gp_pos--){
    gp.write(gp_pos);
    delay(8);    
  }
}

/*
 * Function:set_up_down
 * Input:position
 * Output:void
  Logic:function to set up-down servo at given angle
*/
void set_up_down(int pos){
  for(; up_down_pos < pos; up_down_pos++){
    up_down.write(up_down_pos);
    delay(10);    
  }
  for(; up_down_pos > pos; up_down_pos--){
    up_down.write(up_down_pos);
    delay(10);    
  }
}

/*
  Function:pick
  Input:void
  Output:void
  Logic: function to pick the box and go back to previous node
*/
void pick(){
  deb(200);
  int dis = 500;

  if((current_node == 3 and current_dir == 2) or (current_node == 13 and current_dir == 4)) {
    left_counter = 0;
    right_counter = 20;
    while(left_counter < 20 && right_counter > 0) right(255);
    while(left_counter < 20) soft_right(255);
    while(right_counter > 0) soft_right_back(255);
    _stop();
    set_gripper(90);
  }
  else set_gripper(115);
  
  set_up_down(14);
  delay(500);
  set_gripper(54);
  delay(500);
  set_up_down(110);
  set_gripper(58);
  if((current_node == 3 and current_dir == 2) or (current_node == 13 and current_dir == 4)) {
    left_counter = 20;
    right_counter = 0;
    while(left_counter > 0 && right_counter < 20) left(255);
    while(left_counter > 0) soft_left_back(255);
    while(right_counter < 20) soft_left(255);
    _stop();
  }

  move_backward(dis);
}


/*
  Function:place
  Input:height of the CM(depends on where it is to be kept on,low rise or high rise house)
  Output:void
  Logic: function to place the box
*/
void place(){
  deb(200);
  if(isHigh(current_node)) {
    if(current_node != 9) move_forward(50);
    set_up_down(80);
    delay(500);
  }
  else {
    if(current_node != 9) move_forward(10);
    set_up_down(40);
    delay(500);
  }
  set_gripper(110);
  delay(500);
  set_up_down(95);
  set_gripper(55);
  if(isHigh(current_node)) {
    if(current_node != 9) move_backward(320); 
  }
  else {
    if(current_node != 9) move_backward(270); 
  }

}
