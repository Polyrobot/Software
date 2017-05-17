#include <stdio.h>
#include <stdlib.h>
#include "highgui.h"
#include "cv.h"

 
int main() {
    
    //Code pas propre pour le moment, en cours de developpement
    //Ce code permet de convertir un flux video rgb , d'y sélectionner un objet colorer, convertir l'image en binaire avec le moins de bruit possiblr 

    //ajustement de la couleur dans l'espace hsv (faire la conversion RGB HSV avec un logiciel)
    //Exemple iCi on détecte le rose fluo
    int h = 170, s = 180, v = 0, tolerance = 20;
    // Touche clavier
    char key;
    // Image
     IplImage *image;
     IplImage *hsv;
     IplImage *mask;
     // Capture vidéo
    CvCapture *capture;

 
    // Ouvrir le flux vidéo
    //capture = cvCreateFileCapture("/path/to/your/video/test.avi"); // chemin pour un fichier
    capture = cvCreateCameraCapture(CV_CAP_ANY);
 
    // Vérifier si l'ouverture du flux est ok
    if (!capture) {
 
       printf("Ouverture du flux vidéo impossible !\n");
       return 1;
 
    }
 
    // Définition de la fenêtre
    cvNamedWindow("image_originale", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("image_hsv",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("image_bin",CV_WINDOW_AUTOSIZE);

   

    
 
    // Boucle tant que l'utilisateur n'appuie pas sur la touche q (ou Q)
    while(key != 'q' && key != 'Q') {
 
       // On récupère une image
       image = cvQueryFrame(capture);
       //Charge le masque a partir de l'image
       mask = cvCreateImage(cvGetSize(image), image->depth, 1);
       

       //operation hsv
       hsv = cvCloneImage(image);
      //cvCvtColor(image, hsv, CV_RGB2GRAY);
      cvCvtColor(image, hsv, CV_BGR2HSV);

      //On seuil l'image binaire
      cvInRangeS(hsv,cvScalar(h-tolerance-1,s-tolerance,0),cvScalar(h+tolerance-1,s+tolerance,255),mask);
      //int seuil = 50;
      //cvThreshold(hsv, mask, seuil, 255, CV_THRESH_BINARY);


      //Ouverture fermeture

      IplConvKernel *kernel;
      
      
      kernel = cvCreateStructuringElementEx(7, 7, 2, 2, CV_SHAPE_ELLIPSE);
      cvMorphologyEx(mask, mask, 0,kernel, CV_MOP_OPEN,1 );

      
      kernel = cvCreateStructuringElementEx(3, 3, 2, 2, CV_SHAPE_ELLIPSE);
      
      
      
      
      cvErode(mask, mask, kernel, 1);
      //cvDilate(mask, mask, kernel, 1);


      cvMorphologyEx(mask, mask, 0,kernel, CV_MOP_CLOSE,1 );

      kernel = cvCreateStructuringElementEx(5, 5, 2, 2, CV_SHAPE_ELLIPSE);
      cvMorphologyEx(mask, mask, 0,kernel, CV_MOP_OPEN,1 );


       // On affiche l'image dans une fenêtre
       cvShowImage( "image_originale", image);
       cvShowImage( "image_hsv", hsv);
       cvShowImage("image_bin",mask);


 
       // On attend 10ms
       key = cvWaitKey(10);
 
    }

    
 
    
    cvDestroyWindow("image_originale");
    cvDestroyWindow("image_hsv");
    cvDestroyWindow("image_bin");

    cvReleaseCapture(&capture);
 
    return 0;
 
}



