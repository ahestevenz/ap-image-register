#include <QCoreApplication>
#include "apImageRegister.hpp"

using namespace ap;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    ImageRegister imgRegister;
    imgRegister.output();
    return ImageRegister::OK;
}
