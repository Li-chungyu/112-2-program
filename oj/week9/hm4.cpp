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
        AND() : Gate() {}
        virtual bool output() {}
    private :
        Gate *component[2] ;
} ;

class OR : public Gate
{
    public :
        OR() : Gate() {}
        virtual bool output() {}
    private :
        Gate *component[2] ;
} ;

class XOR : public Gate
{
    public :
        XOR() : Gate() {}
        virtual bool output() {}
    private :
        Gate *component[5] ;
} ;

class Mux
{
    public :
        virtual void setData(bool, int) = 0 ;
        virtual void setData(Gate *, int) = 0 ;
        virtual void setSelect(bool, int) = 0 ;
        virtual void setSelect(Gate *, int) = 0 ;
        virtual void setEnable(bool) = 0 ;
        virtual void setEnable(Gate *) = 0 ;
        virtual Gate *output() = 0 ;
    protected :
        Gate *enable ;
} ;

class Mux2_1 : public Mux
{
    public :
        Mux2_1() : Mux2_1(0) {}
        Mux2_1(bool val)
        {
            if(val) this -> enable = &t ;
            else this -> enable = &f ;
            component[0] = new AND ;
            component[1] = new AND ;
            component[2] = new NOT ;
            component[3] = new OR ;
            component[4] = new AND ;
        }
        virtual void setData(bool val, int pin)
        {
            switch(pin)
            {
                case 0 : component[0] -> setValue(val, 0) ; break ;
                case 1 : component[1] -> setValue(val, 0) ; break ;
                default : ;
            }
        }
        virtual void setData(Gate *gate, int pin)
        {
            switch(pin)
            {
                case 0 : component[0] -> setValue(gate, 0) ; break ;
                case 1 : component[1] -> setValue(gate, 0) ; break ;
                default : ;
            }
        }
        virtual void setEnable(bool val)
        {
            if(val) this -> enable = &t ;
            else this -> enable = &f ;
        }
        virtual void setEnable(Gate *gate)
        {
            this -> enable = gate ;
        }
        virtual void setSelect(bool val, int pin = 0)
        {
            component[1] -> setValue(val, 1) ;
            component[2] -> setValue(val, 0) ;
            component[0] -> input[1] = component[2] ;
        }
        virtual void setSelect(Gate *gate, int pin = 0)
        {
            component[1] -> setValue(gate, 1) ;
            component[2] -> setValue(gate, 0) ;
            component[0] -> input[1] = component[2] ;
        }
        virtual Gate *output()
        {
            component[3] -> setValue(component[0], 0) ;
            component[3] -> setValue(component[1], 1) ;
            component[4] -> setValue(this -> enable, 0) ;
            component[4] -> setValue(component[3], 1) ;
            return component[4] ;
        }
    private :
        Gate *component[5] ;
} ;

class Mux4_1 : public Mux
{
    public :
        Mux4_1() : Mux4_1(0) {}
        Mux4_1(bool val)
        {
            if(val) this -> enable = &t ;
            else this -> enable = &f ;
            mux2_1[0] = new Mux2_1;
            mux2_1[1] = new Mux2_1;
            component[0] = new AND;
            component[1] = new AND;
            component[2] = new OR;
        }
        virtual void setData(bool val, int pin)
        {
            if (pin < 2) 
                mux2_1[0]->setData(val, pin);
            else 
                mux2_1[1]->setData(val, pin - 2);
        }
        virtual void setData(Gate *gate, int pin)
        {
            if (pin < 2) 
                mux2_1[0]->setData(gate, pin);
            else 
                mux2_1[1]->setData(gate, pin - 2);
        }
        virtual void setSelect(bool val, int pin)
        {
            if(pin == 0 || pin == 1)
            {
                mux2_1[0]->setSelect(val, pin);
                mux2_1[1]->setSelect(val, pin);
            }
        }
        virtual void setSelect(Gate *gate, int pin)
        {
            if(pin == 0 || pin == 1)
            {
                mux2_1[0]->setSelect(gate, pin);
                mux2_1[1]->setSelect(gate, pin);
            }
        }
        virtual void setEnable(bool val)
        {
            if(val) this -> enable = &t ;
            else this -> enable = &f ;
        }
        virtual void setEnable(Gate *gate)
        {
            this -> enable = gate ;
        }
        virtual Gate *output()
        {
            // 使用兩個Mux2_1的輸出作為輸入
            mux2_1[0]->setEnable(this->enable);
            mux2_1[1]->setEnable(this->enable);
            component[0]->setValue(mux2_1[0]->output(), 0);
            component[1]->setValue(mux2_1[1]->output(), 1);

            // 最後一個OR閘
            component[2]->setValue(component[0], 0);
            component[2]->setValue(component[1], 1);

            return component[2];
        }
    private :
        Mux *mux2_1[2] ;
        Gate *component[3] ;
};

