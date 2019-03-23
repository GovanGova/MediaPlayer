//
// Created by G on 5/22/2018.
//

#ifndef SIGNAGE_CONSTANT_H
#define SIGNAGE_CONSTANT_H

#endif //SIGNAGE_CONSTANT_H

const unsigned int DF_NONE = 0x0;
const unsigned int DF_XY = 0xFF & 0x1;
const unsigned int DF_WH = 0xFF & 0x2;
const unsigned int DF_ALL = 0xFF;

class Dirty
{
    unsigned int dirtyflag;

  public:
    Dirty()
    {
        dirtyflag = DF_ALL;
    }
    void setDirty(unsigned int value)
    {
        dirtyflag |= value;
    }

    void clearDirty()
    {
        dirtyflag = DF_NONE;
    }
    unsigned int getDirtyFlag()
    {
        return dirtyflag;
    }
    ~Dirty()
    {
    }
};
