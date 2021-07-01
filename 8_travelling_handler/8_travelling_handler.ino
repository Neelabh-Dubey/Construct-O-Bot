 /* 
 * Author list: Neelabh Dubey
 * Filename:8_travelling_handler
 * Theme:Construct-o-bot
 * Fuctions: bool is_house(int),bool is_warehouse(int),int get_dir(int), align_bot(int),go(int),go_next_node(int)
 *          node_right(),node_left(),node_forward(),turn_180(), follow_walls(),follow_zic_zac(),
 *          go9_via8(),go9_via10(),return_to_10(),go_to_10(),go_to_8(),return_to_8(),go_next_node(int),go_30(),
 *          go_next_node(int),read_line(),follow_black_line(int),is_house(int),is_warehouse(int),!is_house(int),!is_warehouse(int)
 * Global variables: current_dir, coordinates[int][int],to_dir,to_node,current_node, path[int][int],left_counter,line
 */
 
  /*
 * function name:is_house
 * input : node number
 * output : boolean
 * logic : returns boolean value true if the building present at the node is a house
 * example call : is_house(6);
 */
bool is_house(int nd){
  if (nd >= 28 && nd <= 32) return true;
  return false;  
}
/*
 * function name: is_warehouse
 * input : node number
 * output : boolean
 * logic : returns a boolean value depending on the house is a warehouse or not 
 * example call : is_warehouse(14);
 */
bool is_warehouse(int nd){
  if (nd >= 16 && nd <= 27) return true;
  return false;
}
/*
   * function: get_dir
   * input:Final node number where the bot has to move to
   * output:direction code 
   * logic:Returns direction in which the bot has to move to reach the final input node with respect to the current node 
   * example call:get_dir(9);
*/

int get_dir(int to_node) {

  int to_dir = current_dir;
  int a1 = coordinates[current_node][0];
  int b1 = coordinates[current_node][1];
  int a2 = coordinates[to_node][0];
  int b2 = coordinates[to_node][1];
  
  if      (b2 > b1) to_dir = 1;
  else if (a2 > a1) to_dir = 2;
  else if (b1 > b2) to_dir = 3;
  else if (a1 > a2) to_dir = 4;
  
  return to_dir;
}
/*
   * function: align_bot
   * input:node number
   * output:void 
   * logic:It instructs the bot to turn in an appropriate direction
   * Example call:  align_bot(8);
*/
void align_bot(int to_node) {
  
  int to_dir = get_dir(to_node);
  if ((current_dir == to_dir - 1) || (current_dir == 4 && to_dir == 1)) node_right();  
  else if ((current_dir == to_dir + 1) || (current_dir == 1 && to_dir == 4)) node_left();
  else if (current_dir == to_dir) node_forward();
  else if (abs(current_dir - to_dir) == 2)  turn_180();   
  current_dir = to_dir;
}




/*
   * function: go
   * input: node number
   * output: void 
   * logic:This function instructs the bot to move to the destined input node if there is a direct path between the current
   * node and input node else it instructs it to move to a node from where it can find a direct path to the destined node
   * Example call: go(10);
    
*/
void go(int node){
  if(path[current_node][node] == 0){    
    if(node != 30 and !(current_node == 9 and current_dir == 3)) align_bot(node);
    
    if((current_node == 4 && node == 14) || (current_node == 14 && node == 4)) follow_walls();
    else if((current_node == 6 && node == 12)||(current_node == 12 && node == 6)) follow_zic_zac();
    else if(current_node == 8 && node == 9) go9_via8();
    else if(current_node == 10 && node == 9) go9_via10();
    else if(current_node == 9 && node == 10){
      if(current_dir == 3)return_to_10();
      else go_to_10();
    }
    else if(current_node == 9 && node == 8){
      if(current_dir == 3) return_to_8();
      else go_to_8();
    }
    else if(current_node == 9 && node == 30) go_30();
    else go_next_node(cost[current_node][node]);

    if(!is_house(node) and !is_warehouse(node)) current_node = node;

  }
  else{
    go(path[current_node][node]);
    go(node);
  }
}

/*
   * function:go_next_node
   * input:one tenth of encoder count b/w current node and next node
   * output:void  
   * logic:It instructs the bot to follow the black line unless a node is found or left encoder completes 10*cst distance
   * Example call: go_next_node(26):
*/
void go_next_node(int cst){
  if(is_house(current_node)) deb(100);
  left_counter = 0;
  read_line();
  cst*=10;
  while(line != "BBB" && left_counter < cst){
    follow_black_line(255);
    read_line();
  }
}
