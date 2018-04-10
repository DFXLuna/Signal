#ifndef RUNPYTHON_H
#define RUNPYTHON_H
// compile with I/usr/include/python3.5m
// Link with -L/usr/lib -lpython3.5m -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions
#include<Python.h>
#include<string>
using std::string;
#include<cstdio>
using std::fopen;
#include<iostream>
using std::cerr;
using std::endl;

void setup( char* progName ){
    wchar_t* program = Py_DecodeLocale( progName, NULL );
    
    if( program == NULL ){}

    Py_SetProgramName( program );
    Py_Initialize();
}

void runScript(  string filePath ){
    FILE* script = 0;

    if( (script = fopen( filePath.c_str(), "r" )) != NULL ){
        PyRun_SimpleFile( script, filePath.c_str() ); 
    }
    else{
        cerr << "Failed to open " << filePath << " in runScript." << endl;
    }
}

void teardown( char* progName ){
    wchar_t* program = Py_DecodeLocale( progName, NULL );
    
    if( program == NULL ){}
    Py_Finalize();
    PyMem_RawFree( program );
}

#endif