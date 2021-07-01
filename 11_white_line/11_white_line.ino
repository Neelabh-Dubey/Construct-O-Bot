/* 
 *Author list: Neelabh Dubey
 * Filename:11_white_line
 * Theme:Construct-o-bot
 * Functions: follow_white_line(int), follow_black_line(int velocity), forward(int)  ,left(), _stop(), right(), deb(int), node_left()
 *       readline(), soft_left(velocity), soft_right(int),move_forward(int),soft_right_back(int)
 *      _search(int , int ), search_for_mid(int,int,int),
 *      go9_via8(), go9_via10(), go_30(),return_to_8(),  go_to_8(), return_to_10(),
 * Global variables: line, left_counter, right_counter,current_dir
 */
 
  /*
 * 
 * Function name :follow_white_line
 * Input:void
* Output:void
* Logic:This function instructs the bot to follow the white line symmetrically
* example call: follow_white_line(255);
 */
void follow_white_line(int velocity){
  if((line == "WBB")) soft_left(velocity);
  else if((line == "WWB")) {
    left(velocity);
    delay(17);
    _stop();
  }
  else if((line == "BBW")) soft_right(velocity);
  else if(line == "BWW"){
    right(velocity);
    delay(17);
    _stop();
  }
  else forward(velocity);
}


/* Function name:search
* input:number of searches(i.e the number of the times and the extend of rotation of the bot towards left and right direction)
      left and right direction)and the direction to be moved in
* Output:void
* Logic:This function is used to find the furthur black path,when there is a break in the black line 
      by searching for a new line towards its left and right 
* Example call:_search(40,1);
*/
void _search(int num, int dir){
  if (dir == 1){
    for(int i = 0; i < num; i++){
      left_counter = 0;
      while(left_counter < 3) right(255);
      _stop();
      delay(10);
      read_line();
      if(line != "WWW") return;
    }
    _search(40, 0);
  }
  else{
    for(int i = 0; i < num; i++){
      right_counter = 0;
      while(right_counter < 3) left(255);
      _stop();
      delay(10);
      read_line();
      if(line != "WWW") return;
    }  
    _search(40, 1);
  }
}

/*
 * Function name : go9_via8 
 * Input:void
 * Output: void
 * Logic: this function is to instruct the bot to go to node 9 via node 8
 * example call: go9_via8();
 */
void go9_via8(){
  deb(200);
  _search(20, 1);
  move_forward(60);
  read_line();
  left_counter = 0;
  while(left_counter < 1350){
    follow_white_line(255);
    read_line();
  }
//  deb(1500);
}
/*
 * Function name : go9_via10
 * Input:void
 * Output: void
 * Logic: this function is to instruct the bot to go to node 10 via node 9
 * example call: go9_via10();
 */
void go9_via10(){
  search_for_mid(30, 0, 255);
  move_forward(75);
  read_line();
  left_counter = 0;
  while(left_counter < 1350){
    follow_white_line(255);
    read_line();
  }
  _stop();
}
/*
 * Function name : go_30
 * Input:void
 * Output: void
 * Logic: this function instructs the bot how to move from node 2 to node 30
 * example call:  go_30();;
 */
void go_30(){
  
  move_forward(100);
  if(current_dir == 2) node_right();
  else node_left();
  current_dir = 3;
  
}


/*
 * Function name : go_to_8 
 * Input:void
 * Output: void
 * Logic: called when bot has to go to node 8
 * example call: go_to_8();
 */
void go_to_8(){
  move_forward(300);
  read_line();
  while(line != "WBW"){
    follow_white_line(255);
    read_line();
  }
  search_for_mid(30, 1, 255);
  move_forward(250);
  _stop();  
}

/*
 * Function name : go_to_10
 * Input:void
 * Output: void
 * Logic: called when bot has to go to node 10
 * example call: go_to_10();
 */
void go_to_10(){
  move_forward(300);
  while(line != "WBW"){
    follow_white_line(255);
    read_line();
  }
  search_for_mid(30, 1, 255);
  move_forward(250);
  _stop();
}
/*
 * Function name : return_to_8 
 * Input:void
 * Output: void
 * Logic: called when bot has to come back to node 8
 * example call: return_to_8();
 */
void return_to_8(){
  left_counter = 0;
  right_counter = 320;
  while(left_counter < 320 && right_counter > 0) right(255);
  while(left_counter < 320) soft_right(255);
  while(right_counter > 0) soft_right_back(255);
  current_dir = 4;
  read_line();
  while(line != "WBW" and line != "WWW"){
    follow_white_line(255);
    read_line();
  }
  search_for_mid(30, 1, 255);
  move_forward(300);
  _stop();
}

/*
 * Function name : return_to_10 
 * Input:void
 * Output: void
 * Logic: called when bot has to come back to node 10
 * example call: return_to_10();
 * 
  */
void return_to_10(){
  left_counter = 310;
  right_counter = 0;
  while(left_counter > 0 && right_counter < 310) left(255);
  while(left_counter > 0) soft_left_back(255);
  while(right_counter < 310) soft_left(255);
  current_dir = 2;
  read_line();
  while(line != "WBW" and line != "WWW"){
    follow_white_line(255);
    read_line();
  }
  search_for_mid(30, 1, 255);
  move_forward(250);
  _stop();
}
