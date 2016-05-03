#ifndef apImageRegister_H
#define apImageRegister_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
namespace ap
{
  class ImageRegister {
    
    /* TODO
     * > Verify what methods are public.
     */
      
  public:
    ImageRegister(string fixed_path,string moving_path);
    ~ImageRegister();
    int getImages(string fixed_path, string moving_path);
    Mat calHistogram(Mat image);
    Mat calJointHistogram(Mat image_1, Mat image_2);
    Mat calEntropy(Mat image);
    Mat calJointEntropy(Mat image_1, Mat image_2);
    Mat calMutualInformation(Mat image_1, Mat image_2);
    double calMaxMutualInformationValue(Mat image_1, Mat image_2);
      
    /* Testing*/    
            
  public:
    static const int OK=0;
    static const int FAILURE=-1;
    
  private:
    Mat fixed, moving;
    int histSize;
    
  public:
    int getHistSize() const { return histSize; }
    Mat getFixedImage() const { return fixed; }
    Mat getMovingImage() const { return moving; }

    /* Testing*/
      
  };
}

#endif // apImageRegister_H
