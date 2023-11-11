#include <vector>
#include <iostream>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "FrameSequence.h"
#include <sstream>
typedef bool boolean;
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>



//defualt constructor
namespace FrameSequence {
    FrameSequence::FrameSequence(void){
} 


FrameSequence::~FrameSequence(){
  
    }


//method to in .pgm file and plce in into a 2d array of unsigned char
void FrameSequence::readFullFile(std::string filename){
    boolean rfile=false;
    std::ifstream infile;
    int maxIntensity=0;
    int rows;
    int cols;
    infile.open(filename,std::ios::binary);
    std::string inputLine="";
    std::vector<int> flags;
    int numChars=0;
    if(infile.is_open()){
        while(getline(infile,inputLine)){
            if((inputLine=="P5")&&(flags.size()==0)){
            rfile=true;
            numChars=numChars+inputLine.length();
            flags.push_back(1);
        }
        else if((inputLine[0]!='#')&&(rfile)&&(inputLine!="255") &&(flags.size()==1)){
            std::istringstream iss (inputLine);
            while(!iss.eof()) {

                iss>> cols>>std::ws>>rows;
            }
            numChars=numChars+inputLine.length();
            flags.push_back(1);
        }
        else if(inputLine=="255" &&rfile&&flags.size()==2){

            maxIntensity =atoi(inputLine.c_str()); //
            numChars=numChars+inputLine.length();
            flags.push_back(1);
        }
        else if(inputLine[0]=='#'){
            numChars=numChars+inputLine.length();
        }
        else if(flags.size()==3){
            int numPixels = cols*rows;

            binarydataoneD=new unsigned char[numPixels];
            infile.seekg(numChars+3,std::ios::beg);
            int size=infile.tellg();
            infile.read(reinterpret_cast<char *> (binarydataoneD), (numPixels)*sizeof(unsigned char));

            if(infile){
                std::cout<<"File has been read and image is now beinf processed.."<<std::endl;
            }
            else{std::cout<<"Error at "<<infile.gcount()<<std::endl;}


            
            break;
        }


        }





    }
    fullframe= new unsigned char*[rows];
    //fullframe is the 2d unishged char variable that has 
    rowNum=rows; 
    std::cout<<rows<<" "<<cols<<std::endl;
    colNum=cols;
    for(int i=0;i<rows;i++){
        fullframe[i]=new unsigned char[cols];
        //loop to assing values in 2D array unsighned far array , binarydataoneD is a 1 D array and thus cant be added to image sequnce
        for(int j=0;j<cols;j++){
            
            fullframe[i][j]=binarydataoneD[i*cols+j];
        }

    }
    
  



}
  
  void FrameSequence::addFrame( unsigned char** frame){
      imageSequence.push_back(frame);
  }


//takes a frame and adds it to image sequence
void FrameSequence::takeframe(int startx, int starty){
  
  unsigned char** imseqvalues=new unsigned char*[frow];
  //buffer 2d array that alloccates space for the frame

int limitx=fcol+startx;
int limity=frow+starty;
  for(int i=0;i<frow;i++){
      imseqvalues[i]= new unsigned char[fcol];
      for(int j=0;j<fcol;j++){
          if((horizontal==1)||(vertical==1)){
              
imseqvalues[i][j]= fullframe[i+starty][j+startx];
          }else{        

                  imseqvalues[i][j]= fullframe[i+startx][j+starty];}
          

      }
}
  

//frame is taken for FULLFRAME abd added to the image sequcne
imageSequence.push_back(imseqvalues);




}

//this method caculates the coordicates ina given frame sequce and adds then all to a vector
void FrameSequence::normaltrajectory(int startx,int starty , int endx, int endy){
    FrameSequence::startx=startx;
    FrameSequence::starty=starty;
    int m=0;
    int c=0;
    int changy= endy-starty;
    int changx=endx-startx;
    if(changy==0){
        horizontal=1;
    }
    if(changx==0){
        vertical=1;
    }        
    
boolean vert=false;
    if(changx==0){
        if(changy!=0){
            for(int f=starty;f<endy;f++){
            std::string coord = std::to_string(startx)+"&&&"+std::to_string(f);
        coordinates.push_back(coord);}
            
        }
   
    
    }else if(changy==0){
        if(changx!=0){
            for(int f=startx;f<endx;f++){
            std::string coord = std::to_string(f)+"&&&"+std::to_string(starty);
        coordinates.push_back(coord);}
            
        }
   
    }

    else{
    m=(changy/changx);

    
    c=starty-(m*startx);
    
   if((endx>startx)&&(endy>starty)){
    for(int i=startx;i<endx+1;i++){
        int y = (m*i)+c;
        //this is the creation of a coordinate, using three &'s to sepeate X and Y
        std::string coord = std::to_string(i)+"&&&"+std::to_string(y);

        coordinates.push_back(coord);




    }}else if((endx<startx)&&(endy<starty)){
        for(int i=startx;i>endx;i--){
            int y = (m*i)+c;
std::string coord = std::to_string(i)+"&&&"+std::to_string(y);
        coordinates.push_back(coord);
        }
    }
    else if((endx==startx)&&(endy==starty)){
       std::string coord = std::to_string(startx)+"&&&"+std::to_string(starty);
       coordinates.push_back(coord);
    }
    }
    //The coordiates are created for the different cases, eg horizontal or vertical or normal;

}

//thiss method creates ac oordinates list whihc is for the reveserse case. It basically adds the coordinates from last to first
void FrameSequence::reversetrajectory(int startx, int starty, int endx, int endy){
     FrameSequence::startx=startx;
    FrameSequence::starty=starty;
   int m=0;
    int c=0;
    int changy= endy-starty;
    int changx=endx-startx;
    m=(changy/changx)+(changy%changx);
    c=starty-(m*startx);
    for(int i=endx;i>startx-1;i--){
        int y=(m*i)+c;
        std::string coord = std::to_string(i)+"&&&"+std::to_string(y);
        coordinates.push_back(coord);



}}
//polyline is the method for the MASTERY SECTION it takes in a specialized coordinates list and loops though and takes frames and adds themm to the seqqunce list
void FrameSequence::polyline(){
    
    for(int i=0;i<masterycords.size();i++){
        
        std::string x =masterycords.at(i).substr(0, masterycords.at(i).find("&&&"));
        std::cout<<"good"<<std::endl;
        std::string y =masterycords.at(i).substr(masterycords.at(i).find("&&&")+3, masterycords.at(i).length());
        
        int limx=std::stoi(x)+fcol;
        int limy =std::stoi(x)+frow;
        
        if((limx>colNum)||(limy>rowNum)){
            std::cout<<"reached end of frame"<<std::endl;
            continue;
        }else{
        
            
         //frame is takesn and added to the image list
        takeframe(std::stoi(x),std::stoi(y));}



    }
}
///this method is where the frame Sequnce loops though the cordiantes list and takes frames 
void FrameSequence::addSequence(){
    for(int i=0;i<coordinates.size();i++){
      // std::cout<<coordinates.at(i)<<std::endl;
        std::string x =coordinates.at(i).substr(0, coordinates.at(i).find("&&&"));
        std::string y =coordinates.at(i).substr(coordinates.at(i).find("&&&")+3, coordinates.at(i).length());
        int limx=std::stoi(x)+fcol;
        int limy =std::stoi(x)+frow;
        if((limx>colNum)||(limy>rowNum)){
            std::cout<<"reached end of frame"<<std::endl;
            continue;
        }else{
        
            
         
        takeframe(std::stoi(x),std::stoi(y));}
    }




}
//invert , mthod to invert the unsigned chars in order to invert the image and add it to the frame sequnce
void FrameSequence::invert(){

    std::vector<unsigned char**> invertSequence;
    int size=imageSequence.size();
    for(int x=0;x<size;x++){
        unsigned char ** ans = new unsigned char*[frow];
        for(int i=0;i<frow;i++){
      ans[i]= new unsigned char[fcol];
      for(int j=0;j<fcol;j++){
          
          ans[i][j]= 255-imageSequence[x][i][j];
        

      }
}
invertSequence.push_back(ans);
    }
imageSequence =invertSequence;


}
//method to write all the images in the image sequnece to the cuurent directory and .pgm files
void FrameSequence::writeToFile(std::string filename){

int size=imageSequence.size();
int n=fcol*frow;
//std::cout<<"prows"<<rowNum<<" pcols"<<colNum<<" framerows"<<frow<<" frameCOLS"<<fcol<<std::endl;
for(int x=0;x<size;x++){
    unsigned char * buffer = new unsigned char[n];


    for(int i=0;i<frow;i++){
        for(int j=0;j<fcol;j++){
            
           
            buffer[i*fcol+j] =imageSequence[x][i][j];
            
        }
    }
    
    std::ofstream infile(filename+std::to_string(x)+".pgm",std::ios::binary);
    infile<<"P5\n";
    infile<<fcol<<" "<<frow<<"\n";
    infile<<255<<"\n"<<"\n";

    infile.write( reinterpret_cast<char *>(buffer),(n)*sizeof(unsigned char));
    if(infile){

    }
    else{
        std::cout<<"error writing file: "<<x<<std::endl;
    }
    infile.close();
    


}


}





}





  



