//
//  Map.h
//  CS440-HW4
//
//  Created by Wenzhao Xu on 12/9/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#ifndef __CS440_HW4__Map__
#define __CS440_HW4__Map__

#include <iostream>
#include "Node.h"
#include "Agent.h"

class agent;

class map
{
public:
    char map_feature[4][6];
    
    node * wholestate[4][6];
    node * root;
    
    node * terminal;
    
    int iternum;

    void valueIter(float err, agent & player);
    
    
    float optimalU(node * state,agent & player);
    map();
    
    
};






#endif /* defined(__CS440_HW4__Map__) */
