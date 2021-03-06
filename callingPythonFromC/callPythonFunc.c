#include <Python.h>
#include <numpy/arrayobject.h>
#include <stdio.h>
#include <string.h>
// Build an Eigen Vector from a pointer to data of a given size

static PyObject * CalBackError;

/*
we expect the user to call this as callback_func(my_func,result_val),
were my_func accepts a numpy vector as argument and returns a single number back
 */

static PyObject* callback_func(PyObject* self, PyObject* args) {

    Py_ssize_t TupleSize = PyTuple_Size(args);

    printf("number of arguments = %ld\n",TupleSize);

    if(TupleSize != 1)
    {
        PyErr_SetString(CalBackError, "Unexpected number of arguments");
        return CalBackError;
    }

    PyObject*   py_like_func  = PyTuple_GetItem(args,0);

    if (!PyCallable_Check(py_like_func))
    {
        PyErr_SetString(PyExc_TypeError, "parameter must be callable");
        return NULL;
    }

    // make vector of 10 elements
    const int vect_size = 10;
    double * vect = (double*) malloc(vect_size*sizeof(double));

    int i=0;
    for(i=0;i<vect_size;++i)
    {
        vect[i] = 1.;
    }

    // first argument
    int nd = 1;
    npy_intp dims[1]={vect_size};
    PyObject* in_vec = PyArray_SimpleNewFromData(nd,dims,NPY_DOUBLE,vect);

    // second argument
    // we need to pass this as a numpy array so that it can get
    // modified inside the python function.
    double result_val=2;
    npy_intp dims_ret[1]={1};
    PyObject* ret_val = PyArray_SimpleNewFromData(nd,dims_ret,NPY_DOUBLE,&result_val);

    Py_ssize_t tuple_size = 2;
    PyObject* args_tuple = PyTuple_Pack(tuple_size,in_vec,ret_val);

    // to collect the output returned
    PyObject* outputs = PyEval_CallObject(py_like_func,args_tuple);
    double call_back_out = PyFloat_AsDouble(outputs);

    // print the returned value
    printf("return of the callback = %f\n",call_back_out);
    // print the modified value
    printf("value modfied in the callback = %f\n",result_val);

    free(vect);

    return Py_None;
}

static PyMethodDef CallBackMethods[] = {

    // Python Name, C Name, Arguments, Description
    {"callback_func", callback_func, METH_VARARGS, "call back python."},
    {NULL,NULL,0,NULL}
};

PyMODINIT_FUNC initcallback_module(void) {

    PyObject *m;
    m = Py_InitModule("callback_module",CallBackMethods);
    if(m==NULL) {return;}
    CalBackError = PyErr_NewException("callback_module.error", NULL, NULL);
    Py_INCREF(CalBackError);
    PyModule_AddObject(m, "error", CalBackError);
    import_array();
}

int main(int argc, char *argv[]) {

    Py_SetProgramName(argv[0]);
    Py_Initialize();
    initcallback_module();
    return 0;
}
