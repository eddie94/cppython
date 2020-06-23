#include <iostream>

#define noneType -1
#define intType 0

namespace cppython
{
    // print function
    void print(int n, char* end="\n")
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
            int objtype = intType;

            cppyInt();
            cppyInt(int n);
            cppyInt& operator=(int n);
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

    cppyInt& cppyInt::operator=(int rhs)
    {
        this->Value = rhs;
        this->ValuePtr = &this->Value;
    }

    //end of cppyInt

    template <class T>
    class list
    {
        private:
            int __len__; // length of list
            T *v; // pointer for value in list

        public:
            list();
            explicit list(int n); // explicit definition. initialize with 0 length list
            list(const T &a, int n); // initialize list with n type a's
            list(const T *a, int n); // initialize list with pointers
            list(const list &rhs); // initialize list with a list
            list & operator=(const list &rhs); // assign a list on right hand side
            list & operator=(const T &a); // assign a datatype on right hand side
            inline T & operator[](const int i);
            inline const T & operator[](const int i) const;
            inline int len() const;
            ~list();
    };

    template <class T>
    list<T>::list() : __len__(0), v(0) {}

    template <class T>
    list<T>::list(int n) : __len__(n), v(new T[n]) {}

    template <class T>
    list<T>::list(const T &a, int n) : __len__(n), v(new T[n])
    {
        for (int i=0; i<n; i++)
        {
            v[i] = a;
        }
    }

    template <class T>
    list<T>::list(const T *a, int n) : __len__(n), v(new T[n])
    {
        for(int i=0; i<n; i++)
        {
            v[i] = *a++;
        }
    }

    template <class T>
    list<T>::list(const list<T> &rhs) : __len__(rhs.__len__), v(new T[__len__])
    {
        for (int i=0; i<__len__; i++)
        {
            v[i] = rhs[i];
        }
    }

    template <class T>
    list<T> & list<T>::operator=(const list<T> &rhs)
    {
        if (this != &rhs) // if 2 objects are different
        {
            if (__len__ != rhs.__len__) // if the length between 2 objects are different
            {
                if (v != 0) // allocate memory as the same size as rhs
                    delete [] (v);
                __len__ = rhs.__len__;
                v = new T[__len__];
            }

            for(int i=0; i<__len__; i++)
            {
                v[i]=rhs[i];
            }
        }
        return *this;
    }

    template <class T>
    list<T> & list<T>::operator=(const T &a)
    {
        for(int i=0; i<__len__; i++)
            v[i] = a;
        return *this;
    }

    template <class T>
    inline T & list<T>::operator[](const int i)
    {
        return v[i];
    }

    template <class T>
    inline const T & list<T>::operator[](const int i) const
    {
        return v[i];
    }

    template <class T>
    inline int list<T>::len() const
    {
        return __len__;
    }

    template <class T>
    list<T>::~list()
    {
        if(v!=0)
            delete[] (v);
    }

};