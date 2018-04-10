#ifndef RUNPYTHON_H
#define RUNPYTHON_H
// compile with I/usr/include/python3.5m
// Link with -L/usr/lib -lpython3.5m -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions
#include<Python.h>
#include<string>
using std::string;

void setup( char* progName ){
    wchar_t* program = Py_DecodeLocale(progName, NULL );
    
    if( program == NULL ){}

    Py_SetProgramName( program );
    Py_Initialize();
}

void runScript(  string filePath ){

    PyRun_SimpleString("print('This was executed from the python interpreter!')");
    
}

void teardown( char* progName ){
    wchar_t* program = Py_DecodeLocale(progName, NULL );
    
    if( program == NULL ){}
    Py_Finalize();
    PyMem_RawFree(program);
}

#endif