//
//  Agent.h
//  CS440-HW4
//
//  Created by Wenzhao Xu on 12/9/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#ifndef __CS440_HW4__Agent__
#define __CS440_HW4__Agent__

#include <iostream>
#include <vector>
#include "Node.h"
#include "Map.h"


using namespace std;

class map;

class agent
{
public:
    node * currentstate;
    node * currentstate_next;
    node * going(int direction);
    
    int iternum;        //the number of iternation;
    
    float P_forward;    //the probability of going the right direction
    float P_left;       //the probability of going the left direction
    float P_right;      //the probability of going the right direction
    
    float U;            //the total utility so far
    
    vector <float> RMS;          //the root mean squared error
    
    float discount;     //the discount rate;
    
    float R_plus;       //the R+ in f(u,n)
    int Ne;             //Ne
    
    agent(float p1,float p2);
    
    map *mapp;
    
    void TDQ(float err);
    int selectaction(node *state);
    
    int tempaction;
    
};

#endif /* defined(__CS440_HW4__Agent__) */
