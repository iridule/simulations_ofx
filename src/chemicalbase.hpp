//
//  chemical header
//

//
#include "ofMain.h"

//
#ifndef CHEMICAL_H
#define CHEMICAL_H

//
class Chemical{

    //
    public: 
    
        Chemical(){}
        ~Chemical(){}
        virtual void set(float _amount) = 0;
        virtual float get() = 0;

    //
    private:    

        float amount;

};

#endif
