#include <iostream>
#include <stdlib.h>
#include <math.h>

#define noneType -1
#define intType 0
#define floatType 1

namespace cppython
{
    // print function
    void print(bool tf,char* end="\n")
    {
        if (tf==true)
        {
            std::cout<<"True"<<end;
        }
        else
        {
            std::cout<<"False"<<end;
        }
    }

    void print(int n, char* end="\n")
    {
        std::cout << n << end;
    }

    void print(float n, char* end="\n")
    {
        std::cout << n << end;
    }

    template <class VAR>
    void print(VAR pyobj, char* end="\n")
    {
        void* value = &pyobj.ValuePtr;
        
        switch (pyobj.objtype)
        {
        case intType:{
            std::cout << pyobj.Value << end;
            break;}
        
        case floatType:{
            std::cout << pyobj.Value << end;
            break;
        }
        
        default:
            break;
        }
    }

    template <class ... REST>
    void print(int n, REST ... ARGS)
    {
        std::cout << n << " ";
        print(ARGS...);
    }

    template <class ...REST>
    void print(float n, REST ... ARGS)
    {
        std::cout << n << " ";
        print(ARGS...);
    }

    template <class VAR, class ... REST>
    void print(VAR pyobj, REST ... ARGS)
    {
        void* value = &pyobj.ValuePtr;

        switch (pyobj.objtype)
        {
        case intType:
            {
                std::cout << pyobj.Value << " ";
                print(ARGS...);
            }
            break;

        case floatType:
        {
            std::cout << pyobj.Value << " ";
            print(ARGS...);
        }
            break;
        
        default:
            break;
        }
    }

    //end of print

    //cppyObjects

    class cppyObject
    {
        public:
            void* ValuePtr;
    };

    // cppyInt

    class cppyInt : public cppyObject
    {
        public:
            int Value;
            bool iterable = false;
            short int objtype = intType;

            cppyInt();
            cppyInt(int n);
            void operator=(int n);

            cppyInt& operator+=(int rhs);
            template <class pyobj>
            cppyInt& operator+=(pyobj &rhs);

            cppyInt& operator-=(int rhs);
            template <class pyobj>
            cppyInt& operator-=(pyobj &rhs);

            cppyInt& operator*=(int rhs);
            template <class pyobj>
            cppyInt& operator*=(pyobj &rhs);

            cppyInt& operator/=(int rhs);
            template <class pyobj>
            cppyInt& operator/=(pyobj &rhs);

            cppyInt& operator%=(int rhs);
            template <class pyobj>
            cppyInt& operator%=(pyobj &rhs);

            cppyInt& operator^=(int rhs);
            template <class pyobj>
            cppyInt& operator^=(pyobj &rhs);
            
            cppyInt operator+(int rhs);
            template <class pyobj>
            cppyInt operator+(pyobj &rhs);

            cppyInt operator-(int rhs);
            template <class pyobj>
            cppyInt operator-(pyobj &rhs);

            cppyInt operator*(int rhs);
            template <class pyobj>
            cppyInt operator*(pyobj &rhs);

            cppyInt operator/(int rhs);
            template <class pyobj>
            cppyInt operator/(pyobj &rhs);

            cppyInt operator%(int rhs);
            template <class pyobj>
            cppyInt operator%(pyobj &rhs);

            cppyInt operator^(int rhs);
            template <class pyobj>
            cppyInt operator^(pyobj &rhs);

            bool operator==(int rhs);
            template <class pyobj>
            bool operator==(pyobj &rhs);
    };

    cppyInt::cppyInt() // default initialization set value pointer to 0
    {
        this->ValuePtr=0;
        this->objtype=noneType;
    }

    cppyInt::cppyInt(int n) // initialize by integer
    {
        this->Value = n;
        this->ValuePtr = &this->Value;
    }

    // operator =
    void cppyInt::operator=(int rhs)
    {
        this->Value = rhs;
        this->ValuePtr = &this->Value;
    }

    // operator +=
    cppyInt& cppyInt::operator+=(int rhs)
    {
        this->Value += rhs;
        return *this;
    }

    template <class pyobj>
    cppyInt& cppyInt::operator+=(pyobj &rhs)
    {
        if (rhs.objtype == intType)
        {
            this->Value+=rhs.Value;
            return *this;
        }
        else
        {
            std::cout<<"ValueError: expected datatype int, recieved "<<rhs.objtype << std::endl;
            exit(0);
        }
    }

        // operator -=
    cppyInt& cppyInt::operator-=(int rhs)
    {
        this->Value -= rhs;
        return *this;
    }

    template <class pyobj>
    cppyInt& cppyInt::operator-=(pyobj &rhs)
    {
        if (rhs.objtype == intType)
        {
            this->Value-=rhs.Value;
            return *this;
        }
        else
        {
            std::cout<<"ValueError: expected datatype int, recieved "<<rhs.objtype << std::endl;
            exit(0);
        }
    }

        // operator *=
    cppyInt& cppyInt::operator*=(int rhs)
    {
        this->Value *= rhs;
        return *this;
    }

    template <class pyobj>
    cppyInt& cppyInt::operator*=(pyobj &rhs)
    {
        if (rhs.objtype == intType)
        {
            this->Value*=rhs.Value;
            return *this;
        }
        else
        {
            std::cout<<"ValueError: expected datatype int, recieved "<<rhs.objtype << std::endl;
            exit(0);
        }
    }

    // operator /=
    cppyInt& cppyInt::operator/=(int rhs)
    {
        this->Value /= rhs;
        return *this;
    }

    template <class pyobj>
    cppyInt& cppyInt::operator/=(pyobj &rhs)
    {
        if (rhs.objtype == intType)
        {
            this->Value/=rhs.Value;
            return *this;
        }
        else
        {
            std::cout<<"ValueError: expected datatype int, recieved "<<rhs.objtype << std::endl;
            exit(0);
        }
    }

    // operator %=
    cppyInt& cppyInt::operator%=(int rhs)
    {
        this->Value -= (this->Value/rhs)*rhs;
        return *this;
    }

    template <class pyobj>
    cppyInt& cppyInt::operator%=(pyobj &rhs)
    {
        if (rhs.objtype == intType)
        {
            this->Value -= (this->Value/rhs.Value)*rhs.Value;
            return *this;
        }
        else
        {
            std::cout << "ValueError: expected datatype int recieved " << rhs.objtype << std::endl;
            exit(0);
        }
        
    }

    // operator ^=
    cppyInt& cppyInt::operator^=(int rhs)
    {
        int tmp = this->Value;

        for (int i=0; i<rhs; i++)
        {
            this->Value *= tmp;
        }
        
        return *this;
    }

    template <class pyobj>
    cppyInt& cppyInt::operator^=(pyobj &rhs)
    {
        short int objtype = rhs.objtype;
        if (objtype == intType)
        {
            int tmp = this->Value;

            for (int i=0; i<rhs.Value-1; i++)
            {
                this->Value *= tmp;
            }
        }
        else
        {
            std::cout << "ValueError: expected datatype int recieved " << rhs.objtype << std::endl;
            exit(0);
        }
        
    }

    //operator +
    cppyInt cppyInt::operator+(int rhs)
    {
        cppyInt result = *this;
        result+=rhs;
        return result;
    }

    template <class pyobj>
    cppyInt cppyInt::operator+(pyobj &rhs)
    {
        cppyInt result = *this;
        result+=rhs;
        return result;
    }

    //operator -
    cppyInt cppyInt::operator-(int rhs)
    {
        cppyInt result = *this;
        result-=rhs;
        return result;
    }

    template <class pyobj>
    cppyInt cppyInt::operator-(pyobj &rhs)
    {
        cppyInt result = *this;
        result-=rhs;
        return result;
    }

    //operator *
    cppyInt cppyInt::operator*(int rhs)
    {
        cppyInt result = *this;
        result*=rhs;
        return result;
    }

    template <class pyobj>
    cppyInt cppyInt::operator*(pyobj &rhs)
    {
        cppyInt result = *this;
        result*=rhs;
        return result;
    }

    //operator /
    cppyInt cppyInt::operator/(int rhs)
    {
        cppyInt result = *this;
        result/=rhs;
        return result;
    }

    template <class pyobj>
    cppyInt cppyInt::operator/(pyobj &rhs)
    {
        cppyInt result = *this;
        result/=rhs;
        return result;
    }

    //operator %
    cppyInt cppyInt::operator%(int rhs)
    {
        cppyInt result = *this;
        result%=rhs;
        return result;
    }

    template <class pyobj>
    cppyInt cppyInt::operator%(pyobj &rhs)
    {
        cppyInt result = *this;
        result%=rhs;
        return result;
    }

    //operator ^
    cppyInt cppyInt::operator^(int rhs)
    {
        cppyInt result = *this;
        result^=rhs;
        return result;
    }

    template <class pyobj>
    cppyInt cppyInt::operator^(pyobj &rhs)
    {
        cppyInt result = *this;
        result^=rhs;
        return result;
    }

    //operator ==
    bool cppyInt::operator==(int rhs)
    {
        if (this->Value == rhs)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template <class pyobj>
    bool cppyInt::operator==(pyobj &rhs)
    {
        if (rhs.objtype != intType)
        {
            return false;
        }
        else if (this->Value == rhs.Value)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //cppyFloat
    class cppyFloat : public cppyObject
    {
        public:
            float Value;
            bool iterable = false;
            short int objtype = floatType;

            cppyFloat() // initialize with nonetype
            {
                this->ValuePtr = 0;
                this->Value=0;
                this->objtype = noneType;
            }

            cppyFloat(float n) // initialize with float
            {
                this->Value = n;
            }

            cppyFloat(int n) //initialize with int
            {
                this->Value = n;
            }

            // operator =
            void operator=(float n)
            {
                this->Value = n;
            }
            void operator=(int n)
            {
                this->Value = n;
            }

            //operator+=
            cppyFloat& operator+=(float rhs)
            {
                this->Value += rhs;
                return *this;
            }
            cppyFloat&operator+=(int rhs)
            {
                this->Value += rhs;
                return *this;
            }
            template <class pyobj>
            cppyFloat& operator+=(pyobj &rhs)
            {
                if (rhs.objtype == intType || rhs.objtype==floatType)
                {
                    this->Value += rhs.Value;
                    return *this;
                }
                else
                {
                    std::cout << "TypeError: expected float(or int) type. recieved " << rhs.objtype << std::endl;
                }
            }

            // operator -=
            cppyFloat& operator-=(float rhs)
            {
                this->Value -= rhs;
            }
            cppyFloat& operator-=(int rhs)
            {
                this->Value -= rhs;
            }
            template <class pyobj>
            cppyFloat& operator-=(pyobj &rhs)
            {
                if(rhs.objtype == intType || rhs.objtype == floatType)
                {
                    this->Value -= rhs.Value;
                    return *this;
                }
                else
                {
                    std::cout << "TypeError: expected float(or int) type. recieved " << rhs.objtype << std::endl;
                }
            }
            
            // operatot *=
            cppyFloat& operator*=(float rhs)
            {
                this->Value *= rhs;
            }
            cppyFloat& operator*=(int rhs)
            {
                this->Value *= rhs;
            }
            template <class pyobj>
            cppyFloat& operator*=(pyobj &rhs)
            {
                if(rhs.objtype == intType || rhs.objtype == floatType)
                {
                    this->Value *= rhs.Value;
                }
                else
                {
                    std::cout << "TypeError: expected float(or int) type. recieved " << rhs.objtype << std::endl;
                }
            }

            // operator /=
            cppyFloat& operator/=(float rhs)
            {
                this->Value /= rhs;
            }
            cppyFloat& operator/=(int rhs)
            {
                this->Value /= rhs;
            }
            template <class pyobj>
            cppyFloat& operator/=(pyobj &rhs)
            {
                if(rhs.objtype == intType || rhs.objtype == floatType)
                {
                    this->Value /= rhs.Value;
                }
                else
                {
                    std::cout << "TypeError: expected float(or int) type. recieved " << rhs.objtype << std::endl;
                }
            }

            cppyFloat& operator%=(float rhs)
            {
                this->Value = this->Value - (this->Value/rhs)*rhs;
            }
            cppyFloat& operator%=(int rhs)
            {
                this->Value = this->Value - (this->Value/rhs)*rhs;
            }
            template <class pyobj>
            cppyFloat& operator%=(pyobj &rhs)
            {
                if(rhs.objtype == intType || rhs.objtype == floatType)
                {
                    this->Value = this->Value - (this->Value/rhs)*rhs;
                }
                else
                {
                    std::cout << "TypeError: expected float(or int) type. recieved " << rhs.objtype << std::endl;
                }
            }

            cppyFloat& operator^=(float rhs)
            {
                this->Value = pow(this->Value, rhs);
            }
            cppyFloat& operator^=(int rhs)
            {
                this->Value = pow(this->Value, rhs);
            }
            template <class pyobj>
            cppyFloat& operator^=(pyobj &rhs)
            {
                if(rhs.objtype == intType || rhs.objtype == floatType)
                {
                    this->Value = pow(this->Value, rhs);
                }
                else
                {
                    std::cout << "TypeError: expected float(or int) type. recieved " << rhs.objtype << std::endl;
                }
            }
            
            //operator +
            cppyFloat operator+(float rhs)
            {
                cppyFloat tmp = *this;
                tmp += rhs;
                return tmp;
            }
            cppyFloat operator+(int rhs)
            {
                cppyFloat tmp = *this;
                tmp += rhs;
                return tmp;
            }
            template <class pyobj>
            cppyFloat operator+(pyobj &rhs)
            {
                if(rhs.objtype == intType || rhs.objtype == floatType)
                {
                    cppyFloat tmp = *this;
                    tmp += rhs;
                    return tmp;
                }
                else
                {
                    std::cout << "TypeError: expected float(or int) type. recieved " << rhs.objtype << std::endl;
                }
            }

            //operator -
            cppyFloat operator-(float rhs)
            {
                cppyFloat tmp = *this;
                tmp -= rhs;
                return tmp;
            }
            cppyFloat operator-(int rhs)
            {
                cppyFloat tmp = *this;
                tmp += rhs;
                return tmp;
            }
            template <class pyobj>
            cppyFloat operator-(pyobj &rhs)
            {
                if(rhs.objtype == intType || rhs.objtype == floatType)
                {
                    cppyFloat tmp = *this;
                    tmp -= rhs;
                    return tmp;
                }
                else
                {
                    std::cout << "TypeError: expected float(or int) type. recieved " << rhs.objtype << std::endl;
                }
            }

            // operator *
            cppyFloat operator*(float rhs)
            {
                cppyFloat tmp = *this;
                tmp *= rhs;
                return tmp;
            }
            cppyFloat operator*(int rhs)
            {
                cppyFloat tmp = *this;
                tmp *= rhs;
                return tmp;
            }
            template <class pyobj>
            cppyFloat operator*(pyobj &rhs)
            {
                if(rhs.objtype == intType || rhs.objtype == floatType)
                {
                    cppyFloat tmp = *this;
                    tmp *= rhs;
                    return tmp;
                }
                else
                {
                    std::cout << "TypeError: expected float(or int) type. recieved " << rhs.objtype << std::endl;
                }
            }

            // operator /
            cppyFloat operator/(float rhs)
            {
                cppyFloat tmp = *this;
                tmp /= rhs;
                return tmp;
            }
            cppyFloat operator/(int rhs)
            {
                cppyFloat tmp = *this;
                tmp /= rhs;
                return tmp;
            }
            template <class pyobj>
            cppyFloat operator/(pyobj &rhs)
            {
                if(rhs.objtype == intType || rhs.objtype == floatType)
                {
                    cppyFloat tmp = *this;
                    tmp /= rhs;
                    return tmp;
                }
                else
                {
                    std::cout << "TypeError: expected float(or int) type. recieved " << rhs.objtype << std::endl;
                }
            }

            //operator %
            cppyFloat operator%(float rhs)
            {
                cppyFloat tmp = *this;
                tmp %= rhs;
                return tmp;
            }
            cppyFloat operator%(int rhs)
            {
                cppyFloat tmp = *this;
                tmp %= rhs;
                return tmp;
            }
            template <class pyobj>
            cppyFloat operator%(pyobj &rhs)
            {
                if(rhs.objtype == intType || rhs.objtype == floatType)
                {
                    cppyFloat tmp = *this;
                    tmp %= rhs;
                    return tmp;
                }
                else
                {
                    std::cout << "TypeError: expected float(or int) type. recieved " << rhs.objtype << std::endl;
                }
            }

            //operator ^
            cppyFloat operator^(float rhs)
            {
                cppyFloat tmp = *this;
                tmp ^= rhs;
                return tmp;
            }
            cppyFloat operator^(int rhs)
            {
                cppyFloat tmp = *this;
                tmp ^= rhs;
                return tmp;
            }
            template <class pyobj>
            cppyFloat operator^(pyobj &rhs)
            {
                if(rhs.objtype == intType || rhs.objtype == floatType)
                {
                    cppyFloat tmp = *this;
                    tmp ^= rhs;
                    return tmp;
                }
                else
                {
                    std::cout << "TypeError: expected float(or int) type. recieved " << rhs.objtype << std::endl;
                }
            }

            //operator ==
            bool operator==(float rhs)
            {
                if(this->Value == rhs)
                {
                    return true;
                }
                else
                {
                    return false;
                }
                
            }
            bool operator==(int rhs)
            {
                if(this->Value == rhs)
                {
                    return true;
                }
                else
                {
                    return false;
                }
                
            }
            template <class pyobj>
            bool operator==(pyobj &rhs)
            {
                if(rhs.objtype == intType || rhs.objtype == floatType)
                {
                    if(this->Value == rhs.Value)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                    
                }
                else
                {
                    std::cout << "TypeError: expected float(or int) type. recieved " << rhs.objtype << std::endl;
                }
                
            }
    };
};
