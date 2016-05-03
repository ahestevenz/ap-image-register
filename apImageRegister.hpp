#ifndef apImageRegister_H
#define apImageRegister_H

#include <iostream>

using namespace std;
namespace ap
{
  class ImageRegister {
      
    public:
      ImageRegister();
      ~ImageRegister();
      void output();
      
    public:
      static const int OK=0;
      static const int FAILURE=-1;

    private: 
      
  };
}

#endif // apImageRegister_H
