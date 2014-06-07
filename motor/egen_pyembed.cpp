//
//  main.cpp
//  PWM
//
//  Created by Toni Axelsson on 2014-06-06.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#include <iostream>
#include <Python.h>
#include <string>

int main(int argc, char * argv[])
{
    PyObject *pName, *pModule, *pDict, *pFunc, *pValue;
    
    Py_Initialize();
    PyRun_SimpleString ("import sys; sys.path.insert(0, 'Enter path to the .py files here')");
    
    pName = PyString_FromString("hello");
    pModule = PyImport_Import(pName);
    pDict = PyModule_GetDict(pModule);
    
    pFunc = PyDict_GetItemString(pDict, "hello");
    PyObject_CallObject(pFunc, NULL);
    
    Py_DECREF(pModule);
    Py_DECREF(pName);
    
    Py_Finalize();
    return 0;
}

