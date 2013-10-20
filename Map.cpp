//
//  Map.cpp
//  CS440-HW4
//
//  Created by Wenzhao Xu on 12/9/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "Map.h"

using namespace std;

map::map()
{

    //create the map
    for (int i=0; i<4;i++) {
        for (int j=0; j<6; j++) {
            map_feature[i][j]='*';
            wholestate[i][j]=new node(i,j);    //create node
        }
    }
    
    terminal=new node(-1,-1);        //terminal state
    terminal->expect_U=0;
    terminal->R=0;
    
//    map_feature[0][0]='S';
    map_feature[0][2]='w';
    map_feature[1][1]='w';
    map_feature[2][1]='w';
    map_feature[2][4]='w';
    map_feature[0][5]='T';
    map_feature[1][5]='T';
    
    root=wholestate[0][0];
    

    
    
    
    for (int i=0; i<4;i++) {
        for (int j=0; j<6; j++) {
            
            
            //initially assign the children pointers to point self
            wholestate[i][j]->child[1]=wholestate[i][j];
            wholestate[i][j]->child[2]=wholestate[i][j];
            wholestate[i][j]->child[3]=wholestate[i][j];
            wholestate[i][j]->child[4]=wholestate[i][j];
            
            
            
            if (i>0)
            {
                if (map_feature[i-1][j]=='w') 
                    wholestate[i][j]->child[1]=wholestate[i][j];
                else
                    wholestate[i][j]->child[1]=wholestate[i-1][j];
            }
            
            if (j<5)
            {
                
                if (map_feature[i][j+1]=='w')
                    wholestate[i][j]->child[2]=wholestate[i][j];
                else
                    wholestate[i][j]->child[2]=wholestate[i][j+1];

            }
            
            if(i<3)
            {
                if (map_feature[i+1][j]=='w')
                    wholestate[i][j]->child[3]=wholestate[i][j];
                else
                    wholestate[i][j]->child[3]=wholestate[i+1][j];
            }
            
            if(j>0)
            {
                if (map_feature[i][j-1]=='w')
                    wholestate[i][j]->child[4]=wholestate[i][j];
                else
                    wholestate[i][j]->child[4]=wholestate[i][j-1];
            }
            
            wholestate[i][j]->child[0]=wholestate[i][j]->child[4];
            wholestate[i][j]->child[5]=wholestate[i][j]->child[1];
            
            wholestate[i][j]->R=-0.04;
        }
    }
    
    wholestate[0][5]->R=1;
    wholestate[1][5]->R=-1;
    wholestate[0][5]->expect_U=1;
    wholestate[1][5]->expect_U=-1;
   
    
    for (int k=0; k<4; k++) {
        wholestate[0][5]->Q[k]=1;
        wholestate[1][5]->Q[k]=-1;
    }
    
    
    for (int i=0; i<6; i++) {
        
        /* assign the terminal state's next state is the root state. */
        wholestate[0][5]->child[i]=terminal;
        wholestate[1][5]->child[i]=terminal;
        
        
        // assign the terminal state's next state is the root state. 
//        wholestate[0][5]->child[i]=root;
//        wholestate[1][5]->child[i]=root;
        
    }
    
    //display the map
    
    for (int i=0; i<4; i++) {
        for (int j=0;j<6;j++)
        {
            cout<<map_feature[i][j]<<" ";
        }
        cout<<endl;
    }
}

float map::optimalU(node * state,agent & player)
{
    float maxU=-99999;
    
    float temp_forward=0;
    float temp_right=0;
    float temp_left=0;
    
    float tempU;
    
    int actionnum;
    
    for (int i=1; i<5; i++)
    {
        temp_forward=player.P_forward*state->child[i]->expect_U;
        temp_left=player.P_left*state->child[i-1]->expect_U;
        temp_right=player.P_right*state->child[i+1]->expect_U;
        tempU=temp_forward+temp_left+temp_right;
        
        if (tempU>maxU)
        {
            maxU=tempU;
            actionnum=i;
        }
    }
    
    state->optimalpolicy_U=actionnum;
    return maxU;
}

void map::valueIter(float err, agent & player)
{
    float DiffU;
    int stop=0;
    iternum=0;
    
    while (iternum<50)
    {
        iternum+=1;
        stop=1;
        for (int i=0; i<4;i++)
        {
            for (int j=0; j<6; j++)
            {
                wholestate[i][j]->HistoryU.push_back(wholestate[i][j]->expect_U);
                wholestate[i][j]->expect_U_next=wholestate[i][j]->R+player.discount*optimalU(wholestate[i][j], player);
        
                //cout<<"("<<i<<","<<j<<")"<<"  "<<wholestate[i][j]->expect_U_next<<"   "<<endl; // for debug
        
                DiffU=abs(wholestate[i][j]->expect_U_next-wholestate[i][j]->expect_U);
                if (DiffU>err) {        // if this update is not stable, then stop=0 means we need another iteration
                    stop=0;
                } 
                wholestate[i][j]->expect_U=wholestate[i][j]->expect_U_next;
                
                
            }
        }    
        /* Debugging
        for (int i=0; i<4; i++) {
            for (int j=0; j<6; j++) {
                cout<<"("<<i<<","<<j<<")"<<"  "<<
                wholestate[i][j]->expect_U<<endl;
            }
        }
        */
    }
    
}