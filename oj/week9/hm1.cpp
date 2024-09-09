#include <iostream>

class Gate
{
    public :
        Gate *input[2] ;
        virtual bool output() = 0 ;
        void setValue(Gate *, int) ;
        void setValue(bool, int) ;
} ;

class TRUE : public Gate
{
    public :
        virtual bool output() { return 1 ; }
        void setValue(Gate *, int) {}
        void setValue(bool, int) {}
} ;

class FALSE : public Gate
{
    public :
        virtual bool output() { return 0 ; }
        void setValue(Gate *, int) {}
        void setValue(bool, int) {}
} ;

TRUE t ;
FALSE f ;

void Gate::setValue(bool val, int pin)
{
    if(val) this -> input[pin] = &t ;
    else this -> input[pin] = &f ;
}

void Gate::setValue(Gate *gate, int pin) { this -> input[pin] = gate ; }

class NOT : public Gate
{
    public :
        virtual bool output() { return !(this -> input[0] -> output()) ; }
        void setValue(bool val, int pin = 0)
        {
            if(val) this -> input[0] = &t ;
            else this -> input[0] = &f ;
        }
        void setValue(Gate* gate, int pin = 0) { this -> input[0] = gate ; }
} ;

class NAND : public Gate
{
    public :
        virtual bool output() { return !(this -> input[0] -> output()) || !(this -> input[1] -> output()) ; }
} ;

class NOR : public Gate
{
    public :
        virtual bool output() { return !(this -> input[0] -> output()) && !(this -> input[1] -> output()) ; }
} ;

class AND : public Gate
{
    public :
        AND() : Gate()
        {
            component[0] = new NOT ;
            component[1] = new NAND ;
        }
        virtual bool output()
        {
            component[1]->input[0] = this->input[0];
            component[1]->input[1] = this->input[1];
            component[0]->input[0] = component[1];
            return component[0]->output();
        }
    private :
        Gate *component[2] ;
} ;

class OR : public Gate
{
    public :
        OR() : Gate()
        {
            component[0] = new NOT ;
            component[1] = new NOR ;
        }
        virtual bool output()
        {
            component[1]->input[0] = this->input[0];
            component[1]->input[1] = this->input[1];
            component[0]->input[0] = component[1];
            return component[0]->output();
        }
    private :
        Gate *component[2] ;
} ;

class XOR : public Gate
{
    public :
        XOR() : Gate()
        {
            component[0] = new AND;
            component[1] = new AND;
            component[2] = new NOT;
            component[3] = new NOT;
            component[4] = new OR;
        }
        virtual bool output()
        {
            // NOT A
            component[2]->input[0] = this->input[0];
            // NOT B
            component[3]->input[0] = this->input[1];

            // A AND NOT B
            component[0]->input[0] = this->input[0];
            component[0]->input[1] = component[3];

            // NOT A AND B
            component[1]->input[0] = component[2];
            component[1]->input[1] = this->input[1];

            // (A AND NOT B) OR (NOT A AND B)
            component[4]->input[0] = component[0];
            component[4]->input[1] = component[1];

            return component[4]->output();
        }
    private :
        Gate *component[5];
};

int main()
{
    // Testing the gates
    TRUE t;
    FALSE f;

    AND andGate;
    OR orGate;
    XOR xorGate;

    // AND gate test
    andGate.setValue(&t, 0);
    andGate.setValue(&f, 1);
    std::cout << "AND Gate Output (1 AND 0): " << andGate.output() << std::endl; // Should output 0

    // OR gate test
    orGate.setValue(&t, 0);
    orGate.setValue(&f, 1);
    std::cout << "OR Gate Output (1 OR 0): " << orGate.output() << std::endl; // Should output 1

    // XOR gate test
    xorGate.setValue(&t, 0);
    xorGate.setValue(&t, 1);
    std::cout << "XOR Gate Output (1 XOR 0): " << xorGate.output() << std::endl; // Should output 1

    return 0;
}