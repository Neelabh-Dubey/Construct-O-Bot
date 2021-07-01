/* 
 * Author list: Neelabh Dubey
 * Filename:10_zic_zac_path
 * Theme:Constuct-o-Bot
 * Functions:void search(int, int ),search(int,int ),follow_black_line(int),read_line(),_stop(),
 * Global variables:int left_counter, int right_counter
 */

/* Function name:search
* input:number of searches(i.e the number of the times and the extend of rotation of the bot towards left and right direction)
      left and right direction)and the direction to be moved in
* Output:void
* Logic:This function is used to find the furthur black path,when there is a break in the black line 
      by searching for a new line towards its left and right 
* Example call:search();
*/
void search(int num, int dir){
  if (dir == 1){
    for(int i = 0; i < num; i++){
      left_counter = 0;
      while(left_counter < 3) right(255);
      _stop();
      delay(10);
      read_line();
      if(line == "WBW") return;
    }
    search(40, 0);
  }
  else{
    for(int i = 0; i < num; i++){
      right_counter = 0;
      while(right_counter < 3) left(255);
      _stop();
      delay(10);
      read_line();
      if(line == "WBW") return;
    }  
    search(40, 1);
  }
}
/*
 * Function name:follow_zic_zac
 * Input: void
 * Output: void
 * Logic :This function instructs the bot to how to follow the zic zac path
 * Example call: follow_zic_zac();
 */
void follow_zic_zac(){
 // set_up_down(25);
  read_line();
  while(line != "BBB"){
      if(line == "WWW") search(20, 1);
      else follow_black_line(255);
      read_line();
  }
 // set_up_down(70);
}
