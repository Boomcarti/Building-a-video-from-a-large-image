extractor: FrameSequence.o  extractor.o
	g++ FrameSequence.o extractor.o -o extractor -std=c++2a

extractor.o: extractor.cpp 
	g++ -c extractor.cpp -o extractor.o -std=c++2a

FrameSequence.o: FrameSequence.cpp FrameSequence.h
	g++ -c FrameSequence.cpp -o FrameSequence.o -std=c++2a

clean:
	rm *.o extractor

cleanImagesAndVideo:
	rm *.pgm *.png *.mp4

moveImages:
	mkdir Images
	mv *.pgm Images
	rm 



runTest1: extractor.exe 
	./extractor.exe sloan_image.pgm -t 0 10 50 50 -s 640 480 -w none normal


runTest2: extractor.exe
	./extractor.exe sloan_image.pgm -t 0 10 500 500 -s 640 480 -w invert inverted


