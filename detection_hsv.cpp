#include <stdio.h>
#include <stdlib.h>
#include "highgui.h"
#include "cv.h"

using namespace cv;

int main(int argc, char** argv)
{	
    //Detection d'un cylindre jaune

	int h = 42, s = 180, v = 0, tolerance = 20;
	 
	// Touche clavier
    char key;
    Mat hsv;
	Mat frame;
    Mat mask;


    VideoCapture capture(CV_CAP_ANY);
    

    if( !capture.isOpened() )
        throw "Error when reading steam_avi";

    namedWindow("w", 1);
    // Boucle tant que l'utilisateur n'appuie pas sur la touche q (ou Q)
    while(key != 'q' && key != 'Q') 
    {	
    	//flux de données transitant de capture jusqu'à frame
        capture >> frame;
      
		cvtColor(frame, hsv, CV_BGR2HSV);
        //On seuil l'image binaire
        inRange(hsv,Scalar(h-tolerance-1,s-tolerance,0),Scalar(h+tolerance-1,s+tolerance,255),mask);


		Mat kernel;
      
        //Eliminer le bruit
      	kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        morphologyEx(mask, mask, MORPH_OPEN, kernel); 

        //morphologyEx(mask, mask, MORPH_CLOSE, kernel); 
        //if(!frame)
        //    break;
        imshow("original",frame);
        imshow("w", hsv);
        imshow("bin",mask);
        key=waitKey(20); // waits to display frame
    }
    waitKey(0);
}
