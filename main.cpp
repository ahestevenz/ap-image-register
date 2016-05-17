#include <iostream>
#include <stdio.h>
#include "apImageRegister.hpp"

using namespace std;
using namespace cv;
using namespace ap;

/**
 * @function main
 */
int main( int argc, char** argv )
{
  /*TODO: 
   * > Bash script: DICOM -> JPG or make a C++ class to manage this.
   * > C++ Library or class to manage graphics.
   * > GUI to explore images to make the program easier to use.
   * > Args parser tool for bash or perl scripts
   */
  ImageRegister imgRegister("ct.jpg","pet.jpg");    
  
  /* Histograms calculation */
  Mat hist_fixed=imgRegister.calHistogram(imgRegister.getFixedImage());
  Mat hist_moving=imgRegister.calHistogram(imgRegister.getMovingImage());
  
  /* Joint Histogram calculation */
  
  Mat joint_hist=imgRegister.calJointHistogram(imgRegister.getFixedImage(),imgRegister.getMovingImage());
  double minVal; 
  double maxVal; 
  Point minLoc; 
  Point maxLoc;
  
  minMaxLoc( joint_hist, &minVal, &maxVal, &minLoc, &maxLoc );
  
  cout << "Joint Histogram minimal value : " << minVal << endl;
  cout << "Joint Histogram maximal value : " << maxVal << endl;
  
  /* Draw histograms */
  int hist_w = 512; int hist_h = 400;
  int bin_w = cvRound((double)hist_w/imgRegister.getHistSize()); 
  
  Mat histImageFixed( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0));
  Mat histImageMoving( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0) );
  
  normalize(hist_fixed, hist_fixed, 0, histImageFixed.rows, NORM_MINMAX, -1, Mat() );
  normalize(hist_moving, hist_moving, 0, histImageMoving.rows, NORM_MINMAX, -1, Mat() );

  for( int i = 1; i < imgRegister.getHistSize(); i++ )
  {
      line( histImageFixed, Point( bin_w*(i-1), hist_h - cvRound(hist_fixed.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(hist_fixed.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
      line( histImageMoving, Point( bin_w*(i-1), hist_h - cvRound(hist_moving.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(hist_moving.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );      
  }
  /* Testing */
  
  cout << "Fixed image entropy : " << imgRegister.calEntropy(imgRegister.getFixedImage()) << endl;
  cout << "Moving image entropy : " << imgRegister.calEntropy(imgRegister.getMovingImage()) << endl;  
  cout << "Joint Entropy : " << imgRegister.calJointEntropy(imgRegister.getFixedImage(),imgRegister.getMovingImage()) << endl;  
  
  /* Display images and histograms */
  
  namedWindow("Histogram: Fixed image", CV_WINDOW_AUTOSIZE );
  imshow("Histogram: Fixed image", histImageFixed );
  namedWindow("Fixed image", CV_WINDOW_AUTOSIZE );
  imshow("Fixed image", imgRegister.getFixedImage() );
  namedWindow("Histogram: Moving image", CV_WINDOW_AUTOSIZE );
  imshow("Histogram: Moving image", histImageMoving );
  namedWindow("Moving image", CV_WINDOW_AUTOSIZE );
  imshow("Moving image", imgRegister.getMovingImage() );
  namedWindow("Joint Histogram", CV_WINDOW_AUTOSIZE );
  imshow("Joint Histogram", joint_hist );
   
  waitKey(0);  
  destroyAllWindows();

  return ImageRegister::OK;    
}
