//
//  Node.h
//  CS440-HW4
//
//  Created by Wenzhao Xu on 12/9/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#ifndef __CS440_HW4__Node__
#define __CS440_HW4__Node__

#include <iostream>
#include  <vector>

using namespace std;

class node
{
public:
    node * child[6];    //children node pointer: 0=1,2,3,4=5

    float expect_U;     //the expected utility of current state
    float R;
    
    float expect_U_next;    //the expect utility of next stage;
    
    int xi,yj;
    node(int i0, int j0);
    
    float Q[4];             //the Q function 0: up  1: right, 2: down; 3: left
    
    float Qfinal;
    
    int NAction[4];         //the Ne function 0
    int visittime;
    int optimalpolicy_Q;      //the optimal policy based on Q value
    int optimalpolicy_U;      //the optimal policy based on U value
    
    vector<float> HistoryU;  //the U value convergence history
    
             
};







#endif /* defined(__CS440_HW4__Node__) */
