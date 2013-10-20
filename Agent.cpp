//
//  Agent.cpp
//  CS440-HW4
//
//  Created by Wenzhao Xu on 12/9/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#include "Agent.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <cmath>

using namespace std;

agent::agent(float p1,float p2)
{
    P_forward=p1;
    P_left=p2/2;
    P_right=p2/2;
    U=0;
    discount=0.99;
    R_plus=2;
    Ne=10;
}


node * agent::going(int direction)
{
    int randomnum=0;
    node * nextnode;
//    srand((int)time(0));
//    srand((unsigned)time(NULL));
    randomnum=rand()%10;
    
    
    if (randomnum<8) 
        nextnode=currentstate->child[direction];        //going forward
    else if(randomnum==8)
        nextnode=currentstate->child[direction+1];      //going right
    else if(randomnum==9)
        nextnode=currentstate->child[direction-1];      //going left
    
    return nextnode;
}

void agent::TDQ(float err)
{
    int a,a_next;
    float alpha=1;
    float temp=0;
    float maxQ=-9999;
    float Diff;
    int action;
    iternum=0;
    node * temppointer=NULL;

    
    Diff=999;
    float RMSE_temp=0;
    
    while (iternum<20000)
    {
        
        iternum+=1;
        
        currentstate=mapp->root;        //initialize the starting state
        
//        alpha=60.0/(59+iternum);
        
        /* For debug and test
        for (int i=0;i<4; i++)
            for (int j=0; j<6; j++)
                for (int k=0; k<4; k++) {
       //             mapp->wholestate[i][j]->NAction[k]=0;
                }
       //         currentstate->visittime=0;
         */
                
        a=selectaction(currentstate);           //choose a from the initial state

        while(currentstate->xi!=-1)             //if currentstate->xi=-1 then it is the terminal state
        {
            
            /*for debug*/
            cout<<"current: "<<currentstate->xi<<","<<currentstate->yj<<":"<<a<<":        :"<<currentstate->Q[a-1]<<endl;

 
            
            currentstate_next=going(a);         //take action a and get the next state s'
            currentstate->visittime+=1;
            currentstate->NAction[a-1]+=1;
            
            //get the action a' of next state s'

            alpha=60.0/(59+currentstate->NAction[a-1]);
            
//            alpha=60.0/(59+currentstate->visittime);
            
            
            if (currentstate->xi==3 && currentstate->yj==4 && a==4)
            {
                cout<<"";
                
            }
            
            
            a_next=selectaction(currentstate_next); 

            
            temp=0;
            maxQ=-999;
            
            for (int k=0; k<4; k++) {
                temp=currentstate_next->Q[k];
                if (temp>maxQ) {
                    maxQ=temp;
                }
            }
            
//          maxQ=currentstate_next->Q[a_next-1];
            
            cout<<"next:    "<<currentstate_next->xi<<",,"<<currentstate_next->yj<<":"<<a_next<<"  "<<maxQ<<"   "<<alpha<<endl;
            cout<<endl;
            
            //update
            
            currentstate->Q[a-1]=currentstate->Q[a-1]+alpha*(currentstate->R+discount*maxQ-currentstate->Q[a-1]);
            
            currentstate=currentstate_next;
            a=a_next;
            
 //         }
        }
        //calculate the RMS
    
        RMSE_temp=0;
        action=0;
        
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<6; j++)
            {
                temp=0;
                maxQ=-9999;
                
                temppointer=mapp->wholestate[i][j];
                for (int k=0; k<4; k++)
                {
                    temp=temppointer->Q[k];
                    
                    if (temp>maxQ)
                    {
                        maxQ=temp;
                        action=k+1;
                    }
                }
                
                temppointer->Qfinal=maxQ;
                temppointer->optimalpolicy_Q=action;
                
                if (mapp->map_feature[i][j]!='w'&&mapp->map_feature[i][j]!='T') {
                    RMSE_temp+=(temppointer->expect_U-maxQ)*(temppointer->expect_U-maxQ)/18;
                }
            }
        }
        
        //        Diff=abs(RMSE_temp-RMS.back());
        
        RMS.push_back(sqrt(RMSE_temp));
    }
}

int agent::selectaction(node * state)
{
    float maxQ=-999;
    float temp=0;
    int action=-1;
    int N;
    float ratio;
   /*
    for (int i=1; i<5; i++)
    {
        if (currentstate->child[i]!=currentstate)           //add this condition to avoid the agent choosing hitting the wall constantly
        {
            if (currentstate->Actioned[i-1]==0)
            {
                if (currentstate->NAction[i-1]<Ne)
                    temp=R_plus;
                else
                    temp=currentstate->Q[i-1];
                
                if (temp>maxQ)
                {
                    maxQ=temp;
                    action=i;
                }

            }
           
        }
    }
    */
//    srand((unsigned)time(NULL));
    for (int i=1; i<5; i++)
    {
        ratio=rand()/(double(RAND_MAX));
        N=state->NAction[i-1];
        
        if (N<Ne)
        {
            temp=R_plus *(1+ratio);     //randomly choose an action if more than one N(a) is less than Ne
            /*(2-float(N%4)/100.0);
            return (rand()%4)+1;*/
        }
        
        else
            temp=state->Q[i-1];
                
        if (temp>maxQ)
        {
            maxQ=temp;
            action=i;
        }
    }

    

    return action;
}