#include "apImageRegister.hpp"

using namespace ap;

ImageRegister::ImageRegister(string fixed_path, string moving_path)
  :histSize(255)
{
  getImages(fixed_path,moving_path);
}

ImageRegister::~ImageRegister()
{
  
}

int ImageRegister::getImages(string fixed_path, string moving_path)
{
  
  fixed=imread(fixed_path);
  moving=imread(moving_path);  
  
  if (!fixed.data || !moving.data)
  {
    cerr<<"No image data available!"<<endl;
    return FAILURE;
  }
  
  Size size_fixed=fixed.size();
  Size size_moving=moving.size();  
  
  if ((size_fixed.height*size_fixed.width)>(size_moving.height*size_moving.width)) 
    resize(moving, moving, fixed.size());
  else 
    resize(fixed, fixed, moving.size());   
  
  return OK;
}

Mat ImageRegister::calLog2(Mat image)
{
  Mat loge_mat;
  log(image,loge_mat);
  Mat log2_mat=loge_mat/log(2);
  
  return log2_mat;
}


Mat ImageRegister::calHistogram(Mat image)
{
  Mat hist=Mat::zeros(1,histSize,CV_32FC1);
  
  if (image.channels()==3) cvtColor(image, image, CV_RGB2GRAY);
  
  float range[] = { 0, 255 };
  const float* hist_range = range; 
  
  calcHist( &image, 1, 0, Mat(), hist, 1, &histSize, &hist_range );
    
  return hist;
}

Mat ImageRegister::calJointHistogram(Mat image_1, Mat image_2)
{
  /* TODO
   * > Verify this calculation
   * > Search a better method to do this.
   */
  Mat jpdf;
  Size image_size=image_1.size();  
  jpdf= Mat::zeros(histSize,histSize,CV_32FC1);

  for (int i=0;i<image_size.height; i++)
  {
    for (int j=0;j<image_size.width; j++)
    {
      jpdf.at<float>(image_1.at<uchar>(i,j),image_2.at<uchar>(i,j))=(float)(jpdf.at<float>(image_1.at<uchar>(i,j),image_2.at<uchar>(i,j))+1);     
    }    
  }
  
  return jpdf;  
}

float ImageRegister::calEntropy(Mat image)
{ 
  float entropy; 
  Mat hist=calHistogram(image);
  hist/=image.total();
  Mat logP=calLog2(hist);      
  entropy = -1*sum(hist.mul(logP)).val[0];  
  
  return entropy;
}

Mat ImageRegister::calJointEntropy(Mat image_1, Mat image_2)
{
  /* TODO
   * > Implement this method
   */
  Mat je; 
  
  return je;
}

Mat ImageRegister::calMutualInformation(Mat image_1, Mat image_2)
{
  /* TODO
   * > Implement this method
   */
  Mat mi; 
  
  return mi;
}

double ImageRegister::calMaxMutualInformationValue(Mat image_1, Mat image_2)
{
  /* TODO
   * > Implement this method
   */
  double max_mi; 
  
  return max_mi;
}

