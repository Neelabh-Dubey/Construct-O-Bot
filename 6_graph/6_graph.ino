
/* 
 * Author list: Neelabh Dubey
 * Filename: 6_graph
 * Theme:Construct-o-Bot
 * Functions:void graph_init()
 * Global variables: path[int][int],cost[int][int]
 */
/*
   * function name : graph_init
  *      we are considering the arena given to us as a graph
   *     where every intersection of line as a node
   *     we have given node number and coordinte to every intersection and by this function
   *     we are trying to find best possible path and using floyed algorithm
   *
   *     cost is a directly propotional to distance b/w nodes 
   *
   *     input: void
   *     output: void
   *     logic: it initialises cost and path of arena graph
   *     example call:graph_init(); 
*/
void graph_init(){
    
    // initialy making all values 1e9
    for(int i = 1; i < 35; i++){
        for(int j = 1; j < 35; j++){
            cost[i][j] = 10000;
            path[i][j] = 10000;
        }
    }
    

    // to give initial values
    //The values are completely experimental
    {
        
      //normal paths
      cost[2][3] = 70;
      cost[3][4] = 70;
      cost[4][5] = 70;
      cost[5][6] = 70;
      cost[6][7] = 70;
      cost[7][8] = 70;
      cost[10][11] = 70;
      cost[11][12] = 70;
      cost[12][13] = 70;
      cost[13][14] = 70;
      cost[14][15] = 70;
      cost[15][34] = 70;
     
      cost[33][1] = 40;//check this
  
      //ware-houses
      cost[3][16] = 16;
      cost[3][17] = 16;
      cost[5][18] = 16;
      cost[5][19] = 16;
      cost[7][20] = 16;
      cost[7][21] = 16;
      cost[11][22] = 16;
      cost[11][23] = 16;
      cost[13][24] = 16;
      cost[13][25] = 16;
      cost[15][26] = 16;
      cost[15][27] = 16;
      
      // houses
      cost[9][30] = 0;//check this
      cost[4][28] = 0;
      cost[6][29] = 0;
      cost[12][31] = 0;
      cost[14][32] = 0;
  
      cost[1][34] = 160;
      cost[1][2] = 160;
      cost[8][9] = 160;
      cost[9][10] = 160;
  
      // zic zac
      cost[6][12] = 750;
  
      // walls
//      cost[4][14] = 200; 
        
        path[2][3] = 0;
        path[3][4] = 0;
        path[4][5] = 0;
        path[5][6] = 0;
        path[6][7] = 0;
        path[7][8] = 0;
        path[10][11] = 0;
        path[11][12] = 0;
        path[12][13] = 0;
        path[13][14] = 0;
        path[14][15] = 0;
        path[15][34] = 0;
        path[9][30] = 0;
        path[33][1] = 0;
        path[3][16] = 0;
        path[3][17] = 0;
        path[4][28] = 0;
        path[5][18] = 0;
        path[5][19] = 0;
        path[6][29] = 0;
        path[7][20] = 0;
        path[7][21] = 0;
        path[11][22] = 0;
        path[11][23] = 0;
        path[12][31] = 0;
        path[13][24] = 0;
        path[13][25] = 0;
        path[14][32] = 0;
        path[15][26] = 0;
        path[15][27] = 0;
        path[1][34] = 0;
        path[1][2] = 0;
        path[8][9] = 0;
        path[9][10] = 0;
        path[6][12] = 0;
//        path[4][14] = 0; 
 
    }


    // to make graph symmetrical
    for(int i = 1; i < 35; i++){
        for(int j = 1; j < 35; j++){
            if(cost[i][j] < cost[j][i]){
                cost[j][i] = cost[i][j];
                path[j][i] = 0;
            } 
        }
    }


    // Floyd Warshall algorithm
    // To find the best possible path between each of the nodes
    for(int k = 1; k < 35; k++){
        for(int i = 1; i < 35; i++){
            for(int j = 1; j < 35; j++){
                if(i == j) continue;
                if(cost[i][j] > cost[i][k]+cost[k][j]){
                    if(cost[i][k]+cost[k][j] == 0){
                    //    cout << "changing value of " << i << " " << j << " due to " << k << endl;
                        break;
                    }
                    cost[i][j] = cost[i][k]+cost[k][j];
                    path[i][j] = k;
                } 
            }
        }
    }

    // giving negative cost for self loop i.e. to increase chance to place 2 objects at same time
    for(int i = 1; i < 35; i++) cost[i][i] = -5, path[i][i] = 0;
}
