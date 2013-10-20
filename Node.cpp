//
//  Node.cpp
//  CS440-HW4
//
//  Created by Wenzhao Xu on 12/9/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#include "Node.h"

node::node(int i0,int j0)
{
    expect_U=0;
    R=0;
    expect_U_next=0;
    
    xi=i0;
    yj=j0;
    visittime=0;
    Qfinal=0;
    for (int i=0; i<4;i++) {
        NAction[i]=0;

        Q[i]=0;
    } 

}
