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

Mat ImageRegister::calLog2(Mat mat_src)
{
  Mat mat_corr,loge_mat;
  max(mat_src, Scalar::all(1e-10), mat_corr);  
  log(mat_corr,loge_mat);
  Mat log2_mat=loge_mat/log(2);
  
  return log2_mat;
}

double ImageRegister::getNormalRandomNumber(double mean, double stddev, int type)
{
  /* TODO
   * > Add different generator modes   
   */
  normal_distribution<double> distribution(mean,stddev);
  double na=distribution(generator);  

  return na;
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

float ImageRegister::calJointEntropy(Mat image_1, Mat image_2)
{
  /* TODO
   * > Verify this calculation
   */
  float je;
  Mat jpdf=calJointHistogram(image_1,image_2);
  jpdf=jpdf/(sum(jpdf).val[0]); // Normalized Joint Histogram       
  Mat logJP=calLog2(jpdf);       
  je = -1*sum(jpdf.mul(logJP)).val[0]; 
  
  return je;
}

float ImageRegister::calMutualInformation(Mat image_1, Mat image_2)
{  
  float mi; 
  float entropy_1=calEntropy(image_1);
  float entropy_2=calEntropy(image_2);
  float joint_entropy=calJointEntropy(image_1,image_2);  
  mi=entropy_1+entropy_2-joint_entropy;
    
  return mi;
}

double ImageRegister::calMaxMutualInformationValue(Mat image_1, Mat image_2, int points, int max_iterations)
{
  /* TODO
   * > Develop image rotation and translation methods
   * > Save matrices and vectors in debug mode
   * > Develop the Simulated Annealing method
   */
  double max_mi; 
  double mi_init=calMutualInformation(image_1,image_2);
  
  /* Initial values */
  double mi_test=mi_init;
  double th_accept=0.0175; // degtorad(1)
  double tx_accept=0;
  double ty_accept=0;
  
  /* Gaussian window parameters */
  double w_radians_a=-(pi/2)*pow(10,-8);
  double w_radians_b=(pi/4);
  double w_pixels_a=-4*pow(10,-8);
  double w_pixels_b=2;
  int i=1;
  int valid_points=1;
  
   while( valid_points < points )
    {
      if (i>max_iterations); break;
      double th=getNormalRandomNumber(th_accept,w_radians_a*i+w_radians_b, STANDARD);
      double tx=getNormalRandomNumber(tx_accept,w_pixels_a*i+w_pixels_b, STANDARD);
      double ty=getNormalRandomNumber(ty_accept,w_pixels_a*i+w_pixels_b, STANDARD);
 
      i++;
    }
  return max_mi;
}

