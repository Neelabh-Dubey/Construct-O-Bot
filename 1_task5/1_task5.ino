/* 
 * Author list: Neelabh Dubey
 * Filename: 1_task5
 * Theme:  Construct-o-bot
 * Functions:void task_init(), do_operation(),encoder_init(),sensors_init(),buzzer_init()
 *                graph_init(), task_config(), pick_place_init(),pick(), place(),go(),_stop(),motion_init()
 * Global variables:volatile long left_counter, int right_counter ,int left_enB,int right_enB,int m_lf, int m_lb, int m_rf,int m_rb,
                    int ir_l, int ir_m,int ir_r ,
                    String line,int cost[35][35], int path[35][35],int coordinates[35][2],int operation_seq[20][2]
                   int buzzer,int arm_status[3],int current_node,int current_dir ,int floor_array[5] ,int house_total_requirement[5],long reward ,
                   int which_material[10],int bonus[35],int house_node_num[8],int total_tasks,int total_operation,int task_list[10][2]
                   int left_sh, right_sh,int up_down_pos,int gp_pos
 */
#include<Servo.h>
/*=======================================================================================================================================
                                                Variable Decleration
=========================================================================================================================================*/
volatile long left_counter = 0, right_counter = 0; // to keep encoder data 
int left_enB, right_enB; // for B pins of encoder
int m_lf, m_lb, m_rf, m_rb; // motor pins
int ir_l, ir_m, ir_r;  // line sensor pins
String line; // string to contain current status of line(e.g. WWW for all white, WBW for left and right channel white and middle black)
int buzzer; // pin for buzzer

int arm_status[3] = {-1, -1, -1}; // we have 3 arms on bot, this array will contain -1 if arm is empty
                                  // otherwise it will contain node number of destination where the object is to be placed

int current_node = 33; // to keep status of the bot  
int current_dir = 3;

// graph decleration
int cost[35][35] = {0}; // cost[x][y] is containig one tenth(aprox) of encode values requrird to travell from node x to node y
int path[35][35] = {0}; // path[x][y] is zero if there is direct path b/w x and y otherwise the node number where we have to go next
int coordinates[35][2] = {
  {-10,-10}, // node zero is not there 
  {4,0},{0,0},{0,2},{0,4}, // node 1 to 4
  {0,6},{0,8},{0,10},{0,12}, // node 5 to 8
  {4,12},{8,12},{8,10},{8,8}, // node 9 to 12
  {8,6},{8,4},{8,2},{-2,2}, // node 13 to 16 
  {2,2},{-2,6},{2,6},{-2,10}, // node 17 to 20
  {2,10},{6,10},{10,10},{6,6}, // node 21 to 24
  {10,6},{6,2},{10,2},{-1,4},// node 25 to 28
  {-1,8},{4,11},{10,8},{10,4}, // node 29 to 32
  {4,1}, // start node node33
    {8,0}
};

// varibles as per instruction in rulebook->Appendix1
int floor_array[5]; 
int house_total_requirement[5];
int which_material[10];

long reward = -10000000;// helper variables for finding optimum sequence of operations
int operation_seq[20][2]; // to keep optimum sequence of operation in order to be performed
                          // here operation_seq[x][0] contains the node number, from where we have to pick/place the object
                          // operation_seq[x][1] = 1 if we have to place
                          // and operation_seq[x][1] = 0 if we have to pick the object


int bonus[35] = {0}; // it contains the points that would be awarded for operation on a particulr node
int house_node_num[6]; // for mapping of house number(given in rulebook) to node number(our terminology) 
int whouse_node_num[13];// same as above 
int node_house_num[34];// reverse mappining-- to find house number from node number



int total_tasks;   // We are considering  one complete pick and place action to be a task
int total_operation;  // a single pick or place is considered as an operation,hence total_operation would be twice of total_tasks
int task_list[10][2]; //task_list[x][0] will contain the node number of the warehouse from where the CM is to be picked 
                      //and task_list[x][1] will contain the node number of the house where the CM is to be placed.

int left_sh, right_sh;// for sharp sensor data

// arm mechanism conntrol variables
Servo gp;
Servo up_down;
int up_down_pos = 80;
int gp_pos = 53;


/*
 * function: setup
 * logic: default function of arduino, to run code one time
*/
void setup() {
  Serial.begin(9600);
  encoder_init(); // declared in "2_encoders_handler.ino"
  motion_init();  // declared in "3_motion_functions.ino"
  sensors_init(); // declared in "4_sensors_handler.ino"
  buzzer_init();  // declared in "5_buzzer.ino"
  graph_init();   // declared in "6_graph.ino"
  task_config();  // declared in "7_tasks_handler.ino"
  pick_place_init(); // declared in "9_pick_place_handler.ino"
}


/*
 * function: loop
 * input and output: void
 * logic: function to perform all pick and place operations one by one and then turns buzzer on for 5 seconds
 * 
*/
void loop(){
  
  // first put CM that is required in house 5
  for(int i = 0; i < house_total_requirement[4]; i++){    
    go(whouse_node_num[which_material[i+8]]); // from
    pick();
    go(30); // to
    place();
  }

  // now supply in remainning houses
  for(int op = 0; op < total_operation; op++){
    go(operation_seq[op][0]); // here we are calling go function with argument- node number where we have to send toe bot
                              // this function is defined in the file "8_travelling_handler.ino"
    if(operation_seq[op][1] == 1){// pick condition
        pick();                   // function to pick object, defined in "9_pick_place_handler.ino"
    }
    else{ // place condition
        place();
    }
  }
  _stop();
  // task done, turn buzzer on
  digitalWrite(buzzer, LOW);
  delay(5000);
  digitalWrite(buzzer, HIGH);
  delay(100000000000000);
}
