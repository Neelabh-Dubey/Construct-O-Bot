/* 
 * Author list: Neelabh Dubey
 * Filename: 7_task_handler
 * Theme: Construct-o-Bot
 * Functions:  bonus_init(), where_required(int ),task_list_init(), task_config(), node_num_mapping()
 *             get_op_sequence(int , long , int , int , int)
 * Global variables: floor_array[int],bonus[int] ,house_node_num[int], total_tasks[int][int],task_list[int][int],total_tasks, house_total_requirement[int]
 *                     total_operation,which_material[int],whouse_node_num[int],house_node_num ,floor_array[int][int],
 *                      house_total_requirement[int], total_operation,operation_seq[int][int],op_seq [int][int]
 */
 
  /*
  *  function name: bonus_init
  *  input: void
  *  output: void 
  *  logic:generate list of points awarded at the node of operation
  *  example call: bonus_init();
*/
void bonus_init(){
    for(int i = 0; i < 5; i++){
        if(floor_array[i] == 1) bonus[house_node_num[i+1]] += 100; // for high house
        else bonus[house_node_num[i+1]] += 80; // for low house
    }
    bonus[house_node_num[5]] += 100; // for house number 5
}



/*
   * function name: where_required
   * input: node number
   * output: node number 
   * logic: it will return node number corresponding to input node where we have to place the object  
   * example call: where_required(9);
*/
int where_required(int from){ 
    for(int i = 0; i < total_tasks; i++) if(task_list[i][0] == from) return task_list[i][1]; return 0;
}





/*
  *  function: task_list_init
  *  input: void
  *  output: void 
  *  logic:It will make a n*2 list in which task_list[x][0] will contain the node from where the CM has to be picked
  *  and task_list[x][1] will contain the node where the CM has to be placed
  *  example call: task_list_init();
  */
void task_l
void task_list_init(){
  
  total_tasks = 0;
  for(int i = 0; i < 4; i++) {
      total_tasks += house_total_requirement[i];
  }
  
  total_operation = total_tasks*2;
  int temp = 0;
  for(int i = 0; i < 8; i++){
    if(which_material[i]){
      int a = which_material[i];
      task_list[temp][0] = whouse_node_num[which_material[i]]; // from
      task_list[temp++][1] = house_node_num[i/2 + 1]; // to
    }
  }
}

/*
   * function name:task_config
   * input:void
   * output:void
   * logic:This function is used for initialization of helper variables according to the instructions in rulebook(appendix 1) and
   * driver functions
   * example call:task_config();
*/
int count[9] = {0};
void task_config(){
  //initialising the high and low risr houses
  floor_array[0] = 0;
  floor_array[1] = 1;
  floor_array[2] = 1;
  floor_array[3] = 0;
  floor_array[4] = 0;
  
  //initialising the house requirements
  house_total_requirement[0] = 2; 
  house_total_requirement[1] = 2; 
  house_total_requirement[2] = 2; 
  house_total_requirement[3] = 2; 
  house_total_requirement[4] = 2;

  /*
   * Materials:
   * Brick(B): w1, w2(brown)
   * Gravel(G): w3, w4(red)
   * Cements(C): w5, w6(green)
   * Sand(S): w7, w8(black)
   * Electrical fetting(E): w9, w10(blue)
   * Paint(P): w11, w12(pink)
  */

  //house 1
  which_material[0] = 9; 
  which_material[1] = 11; 

  //house 2
  which_material[2] = 6; 
  which_material[3] = 3; 

  //house 3
  which_material[4] = 12; 
  which_material[5] = 7; 

  //house 4
  which_material[6] = 1; 
  which_material[7] = 4; 

  //house 5
  which_material[8] = 2; 
  which_material[9] = 8; 

  bonus_init();
  node_num_mapping();

  task_list_init();
  
  int op_seq[10][2] = {0};
  int visited[10] = {0};    
  reward = -100000;
  int cnode;
  if(house_total_requirement[4]) cnode = 30;
  else cnode = 33;
  
  get_op_sequence(total_tasks, 0, op_seq, visited, cnode);
}

/*
  *  function name: node_num_mapping
  * input: void
  *  output: void
  *  logic: to store node number of houses and warehouses and map the house and warehouse number to the node number 
  *  example call: node_num_mapping();
*/
void node_num_mapping(){

    house_node_num[1] = 28;//for mapping of house number(given in rulebook) to node number(our terminology) 
    node_house_num[28] = 1;//for mapping of node number(given in rulebook) to house number(our terminology)

    house_node_num[2] = 32;
    node_house_num[32] = 2;
    
    house_node_num[3] = 29;
    node_house_num[29] = 3;
    
    house_node_num[4] = 31;
    node_house_num[31] = 4;
    
    house_node_num[5] = 30;
    node_house_num[30] = 5;

    
    whouse_node_num[1] = 16;
    whouse_node_num[2] = 17;
    whouse_node_num[3] = 26;
    whouse_node_num[4] = 27;
    whouse_node_num[5] = 18;
    whouse_node_num[6] = 19;
    whouse_node_num[7] = 24;
    whouse_node_num[8] = 25;
    whouse_node_num[9] = 20;
    whouse_node_num[10] = 21;
    whouse_node_num[11] = 22;
    whouse_node_num[12] = 23;

}



void get_op_sequence(int task_rem, long rew, int op_seq[][2], int visited[], int cnode){
  count[task_rem]++;
  if(task_rem <= 0){
    if(rew > reward){
      for(int i = 0; i < total_operation; i++){
        operation_seq[i][0] = op_seq[i][0];
        operation_seq[i][1] = op_seq[i][1];
      }
      reward = rew;
    }
    return;
  }
  else{
    int new_visited[10];
    int new_rew;
    int new_op_seq[20][2] = {0};
    for(int i = 0; i < total_tasks; i++){
      if(!visited[i]){
        for(int j = 0; j < total_operation; j++){
          new_op_seq[j][0] = op_seq[j][0];
          new_op_seq[j][1] = op_seq[j][1];
        }
        
        new_op_seq[2*(total_tasks-task_rem)][0]   = task_list[i][0]; 
        new_op_seq[2*(total_tasks-task_rem)][1]   = 1;
        new_op_seq[2*(total_tasks-task_rem)+1][0] = task_list[i][1];
        new_op_seq[2*(total_tasks-task_rem)+1][1] = 0;        
        new_rew = rew - cost[cnode][task_list[i][0]] + bonus[task_list[i][1]];
        
        for(int j = 0; j < 10; j++) new_visited[j] = visited[j];
        
        new_visited[i] = 1;
        get_op_sequence(task_rem-1, new_rew, new_op_seq, new_visited, task_list[i][1]);     
      }
    }    
  }
}
