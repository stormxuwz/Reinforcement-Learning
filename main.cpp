//
//  main.cpp
//  CS440-HW4
//
//  Created by Wenzhao Xu on 12/9/12.
//  Copyright (c) 2012 Xu Wenzhao. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Agent.h"
#include "Node.h"
#include "Map.h"

using namespace std;

void outputresult(agent &player, map &maze)
{
    ofstream fout1,fout2,fout3;
    fout1.open("/Users/Xuwenzhao/Documents/Developer/C++/CS440-HW4/CS440-HW4/QUvalue.txt",ios::out);
    fout2.open("/Users/Xuwenzhao/Documents/Developer/C++/CS440-HW4/CS440-HW4/QlearningProc.txt",ios::out);
    fout3.open("/Users/Xuwenzhao/Documents/Developer/C++/CS440-HW4/CS440-HW4/IterationProc.txt",ios::out);
    
    fout1<<"Value Iteration result"<<endl;
    for (int i=0; i<4; i++) {
        for (int j=0; j<6; j++) {
            if (maze.map_feature[i][j]=='w') {
                fout1<<setw(10)<<'#';
            }
            else
                fout1<<setprecision(4)<<setw(10)<<maze.wholestate[i][j]->expect_U;
        }
        
        
        fout1<<endl;
    }
    fout1<<endl;
    
    for (int i=0; i<4; i++) {
        for (int j=0; j<6; j++) {
            if (maze.map_feature[i][j]=='w') {
                fout1<<setw(10)<<'#';
            }
            else
                fout1<<setprecision(4)<<setw(10)<<maze.wholestate[i][j]->optimalpolicy_U;
        }
        
        
        fout1<<endl;
    }

    
    
    fout1<<endl<<endl<<endl;
    
    fout1<<"TDQ result"<<endl;
    
    for (int i=0; i<4; i++) {
        for (int j=0; j<6; j++) {
            if (maze.map_feature[i][j]=='w') {
                fout1<<setw(10)<<'#';
            }
            else
                fout1<<setprecision(4)<<setw(10)<<maze.wholestate[i][j]->Qfinal;
        }
        fout1<<endl;
    }
    
    fout1<<endl;
    
    for (int i=0; i<4; i++) {
        for (int j=0; j<6; j++) {
            if (maze.map_feature[i][j]=='w') {
                fout1<<setw(10)<<'#';
            }
            else
                fout1<<setprecision(4)<<setw(10)<<maze.wholestate[i][j]->optimalpolicy_Q;
        }
        fout1<<endl;
    }

    
    
    
    
    
    for (int i=0; i<4; i++) {
        for (int j=0; j<6; j++) {
            if (maze.map_feature[i][j]=='w') {
                fout3<<"#  ";
            }
            else
                fout3<<setprecision(4)<<maze.wholestate[i][j]->xi<<","<<maze.wholestate[i][j]->yj<<"   ";
        }
    }
    
    
    fout3<<endl;

    for (int k=0; k<maze.iternum; k++) {

        for (int i=0; i<4; i++) {
            for (int j=0; j<6; j++) {
                if (maze.map_feature[i][j]=='w') {
                    fout3<<setw(10)<<'#';
                }
                else
                    fout3<<setprecision(4)<<setw(10)<<maze.wholestate[i][j]->HistoryU[k];
            }
        }
        
        fout3<<endl;
    }
        
    
    
    
    for (int k=0; k<player.RMS.size(); k++) {
        fout2<<player.RMS[k]<<endl;;
    }
    
    fout1.close();
    fout2.close();
    fout3.close();
}

int main(int argc, const char * argv[])
{

    srand((unsigned)time(NULL));
    agent player(0.8,0.2);
    map maze;
    
    player.currentstate=maze.root;
    player.mapp=&maze;
    
       
    //Value xxx;
    
    maze.valueIter(0.0001, player);
    
    player.currentstate=maze.root;
    player.TDQ(0.0001);
    
    //display
    
    for (int i=0; i<4; i++) {
        for (int j=0; j<6; j++) {
            cout<<"("<<i<<","<<j<<")"<<"  "<<maze.wholestate[i][j]->expect_U<<"   ";
            for (int k=0; k<4; k++) {
                cout<<maze.wholestate[i][j]->Q[k]<<"   ";
            }
            cout<<endl;
        }
    }
    
    // insert code here...
    std::cout << "Hello, job done\n";
    
    outputresult(player,maze);
    
    return 0;
}

