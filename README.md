# cppython
Python methods written in c++

# About cppython
cppython is a set of c++ classes and functions that uses the same grammar with python3.5.  
The objective is to implement python grammar into c++, therefore the performance is not considered.  

# Datatypes
All datatypes are classes in cppython.  
The datatypes are shown below

|c++|python3.5|cppython|
|:---:|:---------:|:--------:|
|int|int|cppyInt|

# Builtin functions
Builtin functions are also implemented.  
Builtin functions are shown below.

|python3.5|cppython|
|:---:|:---:|
|print|print|

# Usage
Unlike python, cppython needs to declare the variables like C/C++.  
The declaration form follows C/C++.  
But if you don't initialize the variable, it becomes a none type variable so be careful.

> cppyInt a; //declare a none type variable
> cppyInt b=1; //declare an integer with value 1