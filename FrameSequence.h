#ifndef FRAMESEQUENCE_H
#define FRAMESEQUENCE_H
#include <string>
#include <vector>
typedef bool boolean;
namespace FrameSequence{ // in namespace
    class FrameSequence {
        public: 
            // instance variables
            
            unsigned char ** fullframe;
            unsigned char * binarydataoneD;
            std::vector<unsigned char**> imageSequence;
           std::vector<std::string> coordinates;
           std::vector<std::string> masterycords;
           FrameSequence(void); // constructor
           void readFullFile(std::string);
           void polyline();
           void addFrame(unsigned char** frame);
           void reversetrajectory(int startx,int starty , int endx, int endy);
           void normaltrajectory(int startx,int starty , int endx, int endy);
           int starty, startx, stopx ,stopy, rowNum, colNum, frow, fcol,horizontal,vertical;
           void takeframe(int startx, int starty);
           void writeToFile(std::string filename);
           void invert();
            void addSequence();
            

    
            ~FrameSequence();
}; 
} // end namespace
#endif