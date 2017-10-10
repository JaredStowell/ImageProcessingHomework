#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <time.h>

using namespace cv;
using namespace std;

//PROTOTYPE FUNCTIONS
void addSaltPepper(Mat &src, int mod);
void nearestNeighbor(Mat &src);
void bilinearInterpolation(Mat &src);
void bicubicInterpolation(Mat &src);
void rotateImage(Mat &src, double angle);


int main( )
{   
  bool finished = false; //finished keeps loop running. True when ending program.
  int response = 0; //response logs the user's response as an int. Used for making a selection

  Mat img; //new matrix image

  while(!finished){ //while not done, give the user their options
    cout << "~~~~~~~~~~~ SELECT AN OPTION FROM THE MENU BELOW ~~~~~~~~~~~~~~" << endl;
    cout << "1 - SHOW THE ORIGINAL IMAGE" << endl;
    cout << "2 - SHOW THE GRAYSCALE IMAGE (via imread)" << endl;
    cout << "3 - SHOW THE GRAYSCALE IMAGE (via cvtColor)" << endl;
    cout << "4 - SHOW THE THE SALT AND PEPPER IMAGE" << endl;
    cout << "5 - SHOW THE RESIZED IMAGES" << endl;
    cout << "6 - SHOW THE ROTATED IMAGE" << endl;
    cout << "7 - END THE PROGRAM" << endl;
    cin >> response; //get the user's option

    if(response == 1){ //if SHOW ORIGINAL IMAGE
      img = imread("tamucc.jpg", CV_LOAD_IMAGE_UNCHANGED); //load the image. that's it
      if (img.empty()) //check whether the image is loaded or not
    {
        cout << "Error : Image cannot be loaded..!!" << endl;
        
        return -1;
    }
  namedWindow("ORIGINAL IMAGE",CV_WINDOW_NORMAL); //make new window
  imshow("ORIGINAL IMAGE", img); //show image in window
  waitKey(0); //wait for press
  destroyWindow("ORIGINAL IMAGE"); //destroy when x'd out or key press
  imwrite("tamucc.jpg",img); //write the image to the file system
    }


    else if(response == 2){ //LOAD IN AS GRAYSCALE
      img = imread("tamucc.jpg", 0); //LOAD AS GREYSCALE FROM START
      if (img.empty()) //check whether the image is loaded or not
    {
        cout << "Error : Image cannot be loaded..!!" << endl;
        
        return -1;
    }
  namedWindow("GRAYSCALE IMAGE 1",CV_WINDOW_NORMAL); //make new window
  imshow("GRAYSCALE IMAGE 1", img); //show image in window
  waitKey(0); //wait for press
  destroyWindow("GRAYSCALE IMAGE 1"); //destroy when x'd out or key press
  imwrite("tamuccGrayScale1.jpg",img); //write the image to the file system
    }


    else if(response == 3){ //CONVERT TO GRAYSCALE WITH CvtColor FUNCTION
      img = imread("tamucc.jpg", CV_LOAD_IMAGE_UNCHANGED); //load the image
      if (img.empty()) //check whether the image is loaded or not
    {
        cout << "Error : Image cannot be loaded..!!" << endl;
        
        return -1;
    }
      cvtColor(img,img,CV_BGR2GRAY); //Convert to grayscale using CvtColor function
      namedWindow("GRAYSCALE IMAGE 2",CV_WINDOW_NORMAL); //make new window
      imshow("GRAYSCALE IMAGE 2", img); //show image in window
      waitKey(0); //wait for press
      destroyWindow("GRAYSCALE IMAGE 2"); //destroy when x'd out or key press
      imwrite("tamuccGrayScale2.jpg",img); //write the image to the file system
    }

  else if(response == 4){ //ADD SALT AND PEPPER
    int modifier = 0; //store a modifier value
    img = imread("tamucc.jpg", CV_LOAD_IMAGE_UNCHANGED); //load the image
      if (img.empty()) //check whether the image is loaded or not
    {
        cout << "Error : Image cannot be loaded!" << endl;
        
        return -1;
    }
    cout << "Enter an integer modifier value (smaller for higher Salt And Papper. Ex. 10): "; //ask user to input modifier value
    cout << endl << "Low numbers may take awhile." << endl; //warning
    cin >> modifier; //get modifier value
    
    
    addSaltPepper(img, modifier); //call Salt and Pepper function, sending img matrix and modifier value -- DOES ALL THE IMPORTANT STUFF
    namedWindow("SALT AND PEPPER IMAGE",CV_WINDOW_NORMAL); //make new window
      imshow("SALT AND PEPPER IMAGE", img); //show image in window
      waitKey(0); //wait for press
      destroyWindow("SALT AND PEPPER IMAGE"); //destroy when x'd out or key press
      imwrite("tamuccSaltAndPepper.jpg",img); //write the image to the file system
  }

  else if(response == 5){ //DO NEAREST NEIGHBOR, BILINEAR, AND BICUBIC INTERPOLATION
    img = imread("tamucc.jpg", CV_LOAD_IMAGE_UNCHANGED); //load the image
    if (img.empty()) //check whether the image is loaded or not
    {
        cout << "Error : Image cannot be loaded..!!" << endl;
        
        return -1;
    }
    nearestNeighbor(img); //calls nearest neighbor function sending Mat img
    bilinearInterpolation(img); //calls bilinear interpolation function sending Mat img
    bicubicInterpolation(img); //calls bicubic interpolation function sending Mat img
    
  }

  else if(response == 6){ //ROTATE THE IMAGE
    img = imread("tamucc.jpg", CV_LOAD_IMAGE_UNCHANGED); //load the image
    if (img.empty()) //check whether the image is loaded or not
    {
        cout << "Error : Image cannot be loaded..!!" << endl;
        
        return -1;
    }
    double angle = 30; //store an angle
    rotateImage(img, angle); //calls rotate image function sending Mat img and double angle
  }

  else if(response == 7){ //END PROGRAM
    finished = true; //SET VALUE TO TRUE TO END
    cout << "ENDING THE PROGRAM. THANKS FOR GRADING." << endl;
  }
  else{ //END PROGRAM
    finished = true; //SET VALUE TO TRUE TO END
    cout << "ENDING THE PROGRAM. THANKS FOR GRADING." << endl;
  }

  }  

    return 0;
}

/*
SALT AND PEPPER FUNCTION TAKES IN AN IMAGE AND AN INTEGER 
MODIFIER VALUE AND GOES ROW BY ROW TO RANDOMLY ADD WHITE AND
BLACK PIXELS OVER THE IMAGE, AS A FUNCTION OF THE NUMBER RANDOMLY
GENERATED BY THE USER-DEFINED MODIFIER VALUE
*/

void addSaltPepper(Mat &src, int mod){
  int count = 0; //counter value for loops
  double random = rand() % mod; //random number generator

//cout << "random num1: " << random << endl;
for(int i = 0; i < src.rows; i++){ //go through rows
//cout << "random num2: " << random << endl;
for(int j = 0; j < src.cols; j+=random){ //go through cols
  Vec3b color = src.at<Vec3b>(Point(j,i)); //get the color at current coordinates
//cout << "color: " << color << endl;
if(count%2){ //if count is even, black pixel
color[0] = 0; //SET RGB TO BLACK
color[1] = 0; //SET RGB TO BLACK
color[2] = 0; //SET RGB TO BLACK
src.at<Vec3b>(Point(j,i)) = color; //SET NEW VALUES
count++; //ADD ONE TO COUNT SO NEXT PIXEL IS WHITE
}
else{ //IF COUNT IS ODD
color[0] = 255; //SET RGB TO WHITE
color[1] = 255; //SET RGB TO WHITE
color[2] = 255; //SET RGB TO WHITE
src.at<Vec3b>(Point(j,i)) = color; //SET NEW VALUES
count++; //ADD ONE TO COUNT SO NEXT PIXEL IS BLACK
}
random = rand() % mod; //NEW RANDOM VALUE FOR COLUMN PARSING
if(random == 0){random = 1;} //IF RANDOM = 0, RANDOM = 1 SO NO LOOPS
}
}

}

/*
NEAREST NEIGHBOR FUNCTION TAKES IN MAT IMG AND RESIZES
THE IMAGE TO BE 3 TIMES THE ORIGINAL USING INTER_NEAREST.
UNCOMMENT COUT LINES TO MAKE SURE (OR CHECK FILE SIZE)
*/

void nearestNeighbor(Mat &src){
  Mat nnresize; //temp Mat
resize(src, nnresize, Size(src.cols*3, src.rows*3), 0 , 0, INTER_NEAREST); //resize with 3x cols and rows with INTER_NEAREST

//cout << src.rows << "  " << src.cols << endl;
//cout << nnresize.rows << "  " << nnresize.cols << endl;

namedWindow("NEAREST NEIGHBOR",CV_WINDOW_NORMAL); //make new window
      imshow("NEAREST NEIGHBOR", nnresize); //open window with image
      waitKey(0); //wait for key
      destroyWindow("NEAREST NEIGHBOR"); //destroy window when x'd out or key pressed
      imwrite("tamuccNearestNeighbor.jpg",nnresize); //write image to file system
}

/*
BICUBIC INTERPOLATION FUNCTION TAKES IN MAT IMG AND RESIZES
THE IMAGE TO BE 3 TIMES THE ORIGINAL USING INTER_CUBIC.
UNCOMMENT COUT LINES TO MAKE SURE (OR CHECK FILE SIZE)
*/
void bicubicInterpolation(Mat &src){
Mat biresize; //temp Mat
resize(src, biresize, Size(src.cols*3, src.rows*3), 0 , 0, INTER_CUBIC); //resize with 3x cols and rows using INTER_CUBIC

//cout << src.rows << "  " << src.cols << endl;
//cout << biresize.rows << "  " << biresize.cols << endl;

namedWindow("BICUBIC INTERPOLATION",CV_WINDOW_NORMAL); //make new window
      imshow("BICUBIC INTERPOLATION", biresize); //open window with image
      waitKey(0); //wait for key
      destroyWindow("BICUBIC INTERPOLATION"); //destroy window when x'd out or key pressed
      imwrite("tamuccBicubicInterpolation.jpg",biresize); //write image to file system
}

/*
BILINEAR INTERPOLATION FUNCTION TAKES IN MAT IMG AND RESIZES
THE IMAGE TO BE 3 TIMES THE ORIGINAL USING INTER_LINEAR.
UNCOMMENT COUT LINES SO MAKE SURE (OR CHECK FILE SIZE)
*/
void bilinearInterpolation(Mat &src){
Mat blresize; //temp Mat
resize(src, blresize, Size(src.cols*3, src.rows*3), 0 , 0, INTER_LINEAR); //resize with 3x cols and rows using INTER_LINEAR

//cout << src.rows << "  " << src.cols << endl;
//cout << blresize.rows << "  " << blresize.cols << endl;

namedWindow("BILINEAR INTERPOLATION",CV_WINDOW_NORMAL); //make new window
      imshow("BILINEAR INTERPOLATION", blresize); //open window with image
      waitKey(0); //wait for key
      destroyWindow("BILINEAR INTERPOLATION"); //destroy window when x'd out or key pressed
      imwrite("tamuccBilinearInterpolation.jpg",blresize); //write image to file sytem
}


/*
ROTATE IMAGE TAKES IN A MAT IMG AND DOUBLE ANGLE AND FINDS
THE POINT2F OF THE IMAGE (CENTER), AND THEN USES THE
getRotationMatrix2D FUNCTION TO ROTATE THE IMAGE
*/

void rotateImage(Mat &src, double angle){
  Point2f pt(src.cols/2.,src.rows/2.); //FIND CENTER
  Mat dst; //temp Mat
  Mat r = getRotationMatrix2D(pt, angle, 1.0); //GET ROTATION MATRIX2D
  warpAffine(src, dst, r, Size(src.cols, src.rows)); //warpAffine FUNCTION TO FIX BUGS

  namedWindow("ROTATE IMAGE",CV_WINDOW_NORMAL); //make new window
      imshow("ROTATE IMAGE", dst); //open window with image
      waitKey(0); //wait for key
      destroyWindow("ROTATE IMAGE"); //destroy window when x'd out or key pressed
      imwrite("tamuccRotateImage.jpg",dst); //write image to file system
}