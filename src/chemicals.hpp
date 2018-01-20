//
// derived chemicals
//

#include "chemicalbase.hpp"

#ifndef CHEMICALS_H
#define CHEMICALS_H

// chemical a
class ChemicalA : public Chemical {

    //
    public:
        
        ChemicalA(float _amount):amount{_amount}{}
        ~ChemicalA(){}
        virtual void set(float _amount) { amount = _amount; }
        virtual float get() { return amount; }

    //
    private:

        float amount;
        

};

// chemical b
class ChemicalB : public Chemical {

    //
    public:
        
        ChemicalB(float _amount):amount{_amount}{}
        ~ChemicalB(){}
        virtual void set(float _amount) { amount = _amount; }
        virtual float get() { return amount; }


    //
    private:

        float amount;

};

#endif

