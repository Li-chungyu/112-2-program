#include <iostream>

using namespace std;

class Gate {
public:
    Gate *input[2];
    virtual bool output() = 0;
    void setValue(Gate *, int);
    void setValue(bool, int);
};

class TRUE : public Gate {
public:
    virtual bool output() { return 1; }
    void setValue(Gate *, int) {}
    void setValue(bool, int) {}
};

class FALSE : public Gate {
public:
    virtual bool output() { return 0; }
    void setValue(Gate *, int) {}
    void setValue(bool, int) {}
};

TRUE t;
FALSE f;

void Gate::setValue(bool val, int pin) {
    if (val) this->input[pin] = &t;
    else this->input[pin] = &f;
}

void Gate::setValue(Gate *gate, int pin) { this->input[pin] = gate; }

class NOT : public Gate {
public:
    virtual bool output() { return !(this->input[0]->output()); }
    void setValue(bool val, int pin = 0) {
        if (val) this->input[0] = &t;
        else this->input[0] = &f;
    }
    void setValue(Gate* gate, int pin = 0) { this->input[0] = gate; }
};

class NAND : public Gate {
public:
    virtual bool output() { return !(this->input[0]->output()) || !(this->input[1]->output()); }
};

class NOR : public Gate {
public:
    virtual bool output() { return !(this->input[0]->output()) && !(this->input[1]->output()); }
};

class AND : public Gate {
public:
    AND() : Gate() {
        component[0] = new NOT;
        component[1] = new NAND;
    }
    virtual bool output() {
        component[1]->input[0] = this->input[0];
        component[1]->input[1] = this->input[1];
        component[0]->input[0] = component[1];
        return component[0]->output();
    }
private:
    Gate *component[2];
};

class OR : public Gate {
public:
    OR() : Gate() {
        component[0] = new NOT;
        component[1] = new NOR;
    }
    virtual bool output() {
        component[1]->input[0] = this->input[0];
        component[1]->input[1] = this->input[1];
        component[0]->input[0] = component[1];
        return component[0]->output();
    }
private:
    Gate *component[2];
};

class XOR : public Gate {
public:
    XOR() : Gate() {
        component[0] = new AND;
        component[1] = new AND;
        component[2] = new NOT;
        component[3] = new NOT;
        component[4] = new OR;
    }
    virtual bool output() {
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
private:
    Gate *component[5];
};

class Decoder {
public:
    virtual void setValue(bool, int) = 0;
    virtual void setValue(Gate *, int) = 0;
    virtual void setEnable(bool) = 0;
    virtual void setEnable(Gate *) = 0;
    virtual int output() = 0;
    virtual Gate *operator[](int) = 0;
protected:
    Gate *enable;
};

class Decoder2_4 : public Decoder {
public:
    Decoder2_4() : Decoder2_4(0) {}
    Decoder2_4(bool val) {
        if (val) this->enable = &t;
        else this->enable = &f;
        for (int i = 0; i < 2; i++)
            component[i] = new NOT; // A, B
        for (int i = 2; i < 6; i++)
            component[i] = new AND;
        for (int i = 0; i < 4; i++)
            enables[i] = new AND;
    }
    virtual void setEnable(bool val) {
        if (val) this->enable = &t;
        else this->enable = &f;
    }
    virtual void setEnable(Gate *gate) { this->enable = gate; }
    virtual void setValue(Gate *gate, int i) { component[i % 2]->input[0] = gate; }
    virtual void setValue(bool val, int i) {
        if (val) component[i % 2]->input[0] = &t;
        else component[i % 2]->input[0] = &f;
    }
    virtual Gate *operator[](int n) {
        _out();
        switch (n) {
            case 0: return enables[0];
            case 1: return enables[1];
            case 2: return enables[2];
            case 3: return enables[3];
            default: return nullptr;
        }
    }
    friend ostream &operator<<(ostream &out, Decoder2_4 &dec) {
        for (int i = 0; i <= 3; i++)
            out << dec[i]->output() << " ";
        return out;
    }
    virtual int output() {
        _out();
        for (int i = 0; i < 4; i++)
            if (enables[i]->output()) return i;
        return -1; // No valid output
    }
private:
    Gate *component[6];
    Gate *enables[4];

    void _out() {
        component[2]->input[0] = component[0];
        component[2]->input[1] = component[1]; // NOT(A) AND NOT(B)

        component[3]->input[0] = component[0]->input[0];
        component[3]->input[1] = component[1]; // A AND NOT(B)

        component[4]->input[0] = component[0];
        component[4]->input[1] = component[1]->input[0]; // NOT(A) AND B

        component[5]->input[0] = component[0]->input[0];
        component[5]->input[1] = component[1]->input[0]; // A AND B

        for (int i = 0; i < 4; i++) {
            enables[i]->input[0] = this->enable;
            enables[i]->input[1] = component[i + 2];
        }
    }
};

class Decoder4_16 : public Decoder {
public:
    Decoder4_16() {
        for (int i = 0; i < 5; i++) {
            dec2_4[i] = new Decoder2_4;
        }
    }
    Decoder4_16(bool val) {
        for (int i = 0; i < 5; i++) {
            dec2_4[i] = new Decoder2_4;
        }
        dec2_4[0]->setEnable(val);
    }
    virtual void setEnable(bool val) {
        dec2_4[0]->setEnable(val);
    }
    virtual void setEnable(Gate *gate) {
        dec2_4[0]->setEnable(gate);
    }
    virtual void setValue(bool val, int pin) {
        if (pin < 2) {
            dec2_4[0]->setValue(val, pin);
        } else {
            for (int i = 1; i < 5; i++) {
                dec2_4[i]->setValue(val, pin);
            }
        }
    }
    virtual void setValue(Gate *gate, int pin) {
        if (pin < 2) {
            dec2_4[0]->setValue(gate, pin);
        } else {
            for (int i = 1; i < 5; i++) {
                dec2_4[i]->setValue(gate, pin);
            }
        }
    }
    virtual Gate *operator[](int n) {
        int enableIndex = dec2_4[0]->output();
        return (*dec2_4[enableIndex + 1])[n % 4];
    }
    friend ostream &operator<<(ostream &out, Decoder4_16 &dec) {
        dec.out_();
        for (int i = 15; i >= 0; i--) {
            out << (*dec[i]).output() << " ";
        }
        return out;
    }
    virtual int output() {
        out_();
        for (int i = 0; i < 4; i++) {
            int base = i * 4;
            int localOutput = dec2_4[i + 1]->output();
            if (localOutput >= 0) {
                return base + localOutput;
            }
        }
        return -1; // No valid output
    }
private:
    Decoder *dec2_4[5];
    void out_() {
        int enableIndex = dec2_4[0]->output();
        for (int i = 1; i < 5; i++) {
            dec2_4[i]->setEnable(enableIndex == (i - 1));
        }
    }
};

int main() {
    Decoder4_16 d;
    d.setEnable(true);
    d.setValue(false, 0);
    d.setValue(false, 1);
    d.setValue(true, 2);
    d.setValue(true, 3);
    cout << d << endl;
    return 0;
}