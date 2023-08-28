
#include "objects.hh"

namespace oct::verso::v0::gl
{
    void translate(const numbers::vector<float,3,float>& vec)
    {
        glTranslatef(vec.x(),vec.y(),vec.z());
    }
    void translate(const numbers::vector<double,3,double>& vec)
    {
        glTranslatef(vec.x(),vec.y(),vec.z());
    }



}


