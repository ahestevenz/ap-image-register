#ifndef apImageRegister_H
#define apImageRegister_H

#include <iostream>
#include <random>
#include <opencv2/opencv.hpp>

# define pi 3.14159265358979323846

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
    Mat calHistogram(Mat image);
    Mat calJointHistogram(Mat image_1, Mat image_2);
    float calEntropy(Mat image);
    float calJointEntropy(Mat image_1, Mat image_2);
    float calMutualInformation(Mat image_1, Mat image_2);
    double calMaxMutualInformationValue(Mat image_1, Mat image_2, int points, int max_iterations=2500);
      
    /* Testing*/      
    
  private:
    int getImages(string fixed_path, string moving_path);
    double getNormalRandomNumber(double mean, double stddev, int type);
    Mat calLog2(Mat image);    
            
  public:
    static const int OK=0;
    static const int FAILURE=-1;
    static const int STANDARD=10;
    
  private:
    Mat fixed, moving;
    int histSize;
    default_random_engine generator;
    
  public:
    int getHistSize() const { return histSize; }
    Mat getFixedImage() const { return fixed; }
    Mat getMovingImage() const { return moving; }

    /* Testing*/
         
  };
}

#endif // apImageRegister_H
