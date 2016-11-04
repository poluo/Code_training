#ifndef _CALLPYTHON_H
#define _CALLPYTHON_H
#include <Python.h>

#define MAX_LENGTH_PYTHON_SCRIPT_NAME 	20
#define MAX_ARGS_NUM				10

extern int InitPython();
extern int ExitPython();
extern void RunSimpleStringPython(const char *args);
extern void RunPyhtonScript(const char *FileName);
extern void CallFunPythonType1(const char * FileName,const char * Func,PyObject *pArg);
extern void CallFunPythonType3(const char * FileName,const char * Func,int *Result ,PyObject *pArg);

extern PyObject *ConvertPyObject(const char *Format,...);
















#endif
