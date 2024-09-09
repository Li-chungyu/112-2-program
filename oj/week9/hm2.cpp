#include <iostream>

class Gate
{
    public :
        Gate *input[2];
        virtual bool output() = 0;
        void setValue(Gate *, int);
        void setValue(bool, int);
};

class TRUE : public Gate
{
    public :
        virtual bool output() { return 1; }
        void setValue(Gate *, int) {}
        void setValue(bool, int) {}
};

class FALSE : public Gate
{
    public :
        virtual bool output() { return 0; }
        void setValue(Gate *, int) {}
        void setValue(bool, int) {}
};

TRUE t;
FALSE f;

void Gate::setValue(bool val, int pin)
{
    if(val) this->input[pin] = &t;
    else this->input[pin] = &f;
}

void Gate::setValue(Gate *gate, int pin) { this->input[pin] = gate; }

class NOT : public Gate
{
    public :
        virtual bool output() { return !(this->input[0]->output()); }
        void setValue(bool val, int pin = 0)
        {
            if(val) this->input[0] = &t;
            else this->input[0] = &f;
        }
        void setValue(Gate* gate, int pin = 0) { this->input[0] = gate; }
};

class NAND : public Gate
{
    public :
        virtual bool output() { return !(this->input[0]->output() && this->input[1]->output()); }
};

class NOR : public Gate
{
    public :
        virtual bool output() { return !(this->input[0]->output() || this->input[1]->output()); }
};

class AND : public Gate
{
    public :
        AND() : Gate()
        {
            component[0] = new NOT;
            component[1] = new NAND;
        }
        virtual bool output()
        {
            component[1]->input[0] = this->input[0];
            component[1]->input[1] = this->input[1];
            component[0]->input[0] = component[1];
            return component[0]->output();
        }
    private :
        Gate *component[2];
};

class OR : public Gate
{
    public :
        OR() : Gate()
        {
            component[0] = new NOT;
            component[1] = new NOR;
        }
        virtual bool output()
        {
            component[1]->input[0] = this->input[0];
            component[1]->input[1] = this->input[1];
            component[0]->input[0] = component[1];
            return component[0]->output();
        }
    private :
        Gate *component[2];
};

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

class Adder
{
    public :
        virtual void setValue(bool, int) = 0;
        virtual void setValue(Gate *, int) = 0;
        virtual Gate *sum() = 0;
        virtual Gate *carryOut() = 0;
};

class OneBitHalfAdder : public Adder
{
    public :
        OneBitHalfAdder()
        {
            component[0] = new XOR;
            component[1] = new AND;
        }

        virtual void setValue(bool val, int pin)
        {
            component[0]->setValue(val, pin);
            component[1]->setValue(val, pin);
        }

        virtual void setValue(Gate *gate, int pin)
        {
            component[0]->setValue(gate, pin);
            component[1]->setValue(gate, pin);
        }

        virtual Gate *sum()
        {
            return component[0];
        }

        virtual Gate *carryOut()
        {
            return component[1];
        }

    private :
        Gate *component[2]; // component[0] for XOR, component[1] for AND
};

class OneBitFullAdder : public Adder
{
    public :
        OneBitFullAdder()
        {
            a[0] = new OneBitHalfAdder;
            a[1] = new OneBitHalfAdder;
            carry = new OR;
        }

        virtual void setValue(bool val, int pin)
        {
            if (pin < 2)
            {
                a[0]->setValue(val, pin);
            }
            else
            {
                a[1]->setValue(val, 1);
            }
        }

        virtual void setValue(Gate *gate, int pin)
        {
            if (pin < 2)
            {
                a[0]->setValue(gate, pin);
            }
            else
            {
                a[1]->setValue(gate, 1);
            }
        }

        virtual Gate *sum()
        {
            a[1]->setValue(a[0]->sum(), 0);
            return a[1]->sum();
        }

        virtual Gate *carryOut()
        {
            a[1]->setValue(a[0]->sum(), 0);
            carry->input[0] = a[0]->carryOut();
            carry->input[1] = a[1]->carryOut();
            return carry;
        }

    private :
        Adder *a[2]; // Two OneBitHalfAdders
        Gate *carry; // One OR gate
};

int main()
{
    TRUE t;
    FALSE f;

    OneBitHalfAdder halfAdder;
    OneBitFullAdder fullAdder;

    // Test OneBitHalfAdder
    halfAdder.setValue(true, 0);
    halfAdder.setValue(false, 1);
    std::cout << "OneBitHalfAdder Sum (1, 0): " << halfAdder.sum()->output() << std::endl; // Should output 1
    std::cout << "OneBitHalfAdder CarryOut (1, 0): " << halfAdder.carryOut()->output() << std::endl; // Should output 0

    // Test OneBitFullAdder
    fullAdder.setValue(true, 0);
    fullAdder.setValue(true, 1);
    fullAdder.setValue(false, 2);
    std::cout << "OneBitFullAdder Sum (1, 1, 0): " << fullAdder.sum()->output() << std::endl; // Should output 0
    std::cout << "OneBitFullAdder CarryOut (1, 1, 0): " << fullAdder.carryOut()->output() << std::endl; // Should output 1

    fullAdder.setValue(true, 0);
    fullAdder.setValue(true, 1);
    fullAdder.setValue(true, 2);
    std::cout << "OneBitFullAdder Sum (1, 1, 1): " << fullAdder.sum()->output() << std::endl; // Should output 1
    std::cout << "OneBitFullAdder CarryOut (1, 1, 1): " << fullAdder.carryOut()->output() << std::endl; // Should output 1

    return 0;
}