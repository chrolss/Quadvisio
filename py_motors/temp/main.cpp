//
//  main.cpp
//  PWMxcode
//
//  Created by Toni Axelsson on 2014-06-07.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#include <iostream>
#include <Python.h>

int main(int argc, const char * argv[])
{
    PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue;
    
    double d[4] = {89.3489492023,45.25443,1.23143,45.564};
    
    // Initialize Python interpreter
    Py_Initialize();
    
    // Make sure so that the Python code is found
    PyRun_SimpleString ("import sys; sys.path.insert(0, '/Users/toniaxelsson/Documents/Kod/PWM')");
    
    //Name of the Python script
    pName = PyString_FromString("hello");
    
    // Load the module object
    pModule = PyImport_Import(pName);
    
    // pDict is a borrowed reference
    pDict = PyModule_GetDict(pModule);
    
    // pFunc is also a borrowed reference
    pFunc = PyDict_GetItemString(pDict, "hello");
    
    
    pArgs = PyTuple_New(4);
    
    
    for (int i=0; i<4; i++) {
        pValue = PyFloat_FromDouble(d[i]);
        PyTuple_SetItem(pArgs, i, pValue);
    }
    
    
    // Call the function in the Python script
    PyObject_CallObject(pFunc, pArgs);
    
    Py_DECREF(pModule);
    Py_DECREF(pName);
    
    Py_Finalize();
    return 0;
}

