#include <string>
#include <fstream>
#include <iostream>

 

#include <iostream>


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include "FrameSequence.h"

#include <sstream>
typedef bool boolean;



int main(int argc, char *argv[])
{

//inputing string filename
std::string filename=argv[1];
std::vector<std::string> operators;
std::vector<std::string> writeOperations;
FrameSequence::FrameSequence tfs;

operators.push_back(argv[2]);
std::string opera= argv[2];

//if read operation is a polyline(mastery)
if(opera=="-p"){
    tfs.readFullFile(filename);
    tfs.imageSequence.clear();

    std::string numcords = argv[3];
    std::vector<std::string> cords;
    int indexcords=stoi(numcords);//4
    
    int termindex=4+(2*indexcords);//12
    
    for(int u=4;u<termindex-1;u=u+2){
        std::string x=argv[u];
        std::string y=argv[u+1];
        std::string cod=x+"&&&"+y;
        std::cout<<cod<<std::endl;
        tfs.masterycords.push_back(cod);
    }
    tfs.fcol=std::stoi(argv[termindex+1]);
    tfs.frow=std::stoi(argv[termindex+2]);
     std::string opone = argv[termindex+4];
        std::string optwo = +argv[termindex+5];
        std::string writeop=opone+"$$$"+optwo;
        writeOperations.push_back(writeop);
    }else{
tfs.startx= std::stoi(argv[3]);
if(tfs.startx<0){
    tfs.startx=0;
}

tfs.starty= std::stoi(argv[4]);
if(tfs.starty<0){
    tfs.starty=0;
}
//storing of important variables

tfs.stopx= std::stoi(argv[5]);

tfs.stopy= std::stoi(argv[6]);

operators.push_back(argv[7]);
tfs.frow=std::stoi(argv[9]);
tfs.fcol=std::stoi(argv[8]);
    }

//accounting for multi test where there an many write commands 
if((argc==13)&&(opera!="-p")){
        std::string opone = argv[11];
        std::string optwo = +argv[12];
        std::string writeop=opone+"$$$"+optwo;
        writeOperations.push_back(writeop);
        
    }
    else if((argc==16)&&(opera!="-p")){
        
        std::string opone = argv[11];
        std::string optwo = +argv[12];
        std::string writeop=opone+"$$$"+optwo;
        writeOperations.push_back(writeop);
        std::string oponet = argv[14];
        std::string optwot = +argv[15];
        std::string writeopt=oponet+"$$$"+optwot;
        writeOperations.push_back(writeopt);
    }else if((argc==19)&&(opera!="-p")){
        
        std::string opone = argv[11];
        std::string optwo = +argv[12];
        std::string writeop=opone+"$$$"+optwo;
        writeOperations.push_back(writeop);
        std::string oponet = argv[14];
        std::string optwot = +argv[15];
        std::string writeopt=oponet+"$$$"+optwot;
        writeOperations.push_back(writeopt);
        std::string oponett = argv[16];
        std::string optwott = +argv[17];
        std::string writeoptt=oponett+"$$$"+optwott;
        writeOperations.push_back(writeoptt);
    }else if((argc==22)&&(opera!="-p")){
        
        std::string opone = argv[11];
        std::string optwo = +argv[12];
        std::string writeop=opone+"$$$"+optwo;
        writeOperations.push_back(writeop);
        std::string oponet = argv[14];
        std::string optwot = +argv[15];
        std::string writeopt=oponet+"$$$"+optwot;
        writeOperations.push_back(writeopt);
        std::string oponett = argv[17];
        std::string optwott = +argv[18];
        std::string writeoptt=oponett+"$$$"+optwott;
        writeOperations.push_back(writeoptt);
         std::string oponettt = argv[20];
        std::string optwottt = +argv[21];
        std::string writeopttt=oponettt+"$$$"+optwottt;
        writeOperations.push_back(writeopttt);
    }



for(int i=0;i<writeOperations.size();i++){
    std::cout<<writeOperations[i]<<std::endl<<" write operations"<<std::endl;
}

try {
       tfs.readFullFile(filename);
    } catch(const std::bad_array_new_length &e) {
        std::cout<<"The file you have entered in not in the assingment file or the spelling might be different"<<std::endl;
        
    }


tfs.imageSequence.clear();



for(int i=0;i<writeOperations.size();i++){
    std::string command=writeOperations.at(i).substr(0,writeOperations.at(i).find("$$$"));
    std::string fname=writeOperations.at(i).substr(writeOperations.at(i).find("$$$")+3,writeOperations.at(i).length());
    //checking if write commands and calling subsequent methods
    if(command=="none"){

       if(opera=="-p"){
           tfs.polyline();
           tfs.writeToFile(fname);

           
       }else{
        tfs.normaltrajectory(tfs.startx,tfs.starty,tfs.stopx,tfs.stopy);
        tfs.addSequence();
        tfs.writeToFile(fname);    }
    }
    else if(command=="invert"){
 tfs.normaltrajectory(tfs.startx,tfs.starty,tfs.stopx,tfs.stopy);
 tfs.addSequence();
 tfs.invert();
tfs.writeToFile(fname);    
    }
    else if(command=="reverse"){
        tfs.reversetrajectory(tfs.startx,tfs.starty,tfs.stopx,tfs.stopy);
 tfs.addSequence();
tfs.writeToFile(fname);    
    }
    else if(command=="revinvert"){
        tfs.reversetrajectory(tfs.startx,tfs.starty,tfs.stopx,tfs.stopy);
 tfs.addSequence();
 tfs.invert();
tfs.writeToFile(fname);
    }




}


return 0;


}
