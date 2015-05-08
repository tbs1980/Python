#include <Python.h>
#include <numpy/arrayobject.h>
// Build an Eigen Vector from a pointer to data of a given size

static PyObject * CalBackError;

static PyObject* callback_func(PyObject* self, PyObject* args) {

    Py_ssize_t TupleSize = PyTuple_Size(args);

    printf("number of arguments = %ld\n",TupleSize);

    PyObject*   py_obj_low    = PyTuple_GetItem(args, 0);

    PyObject*   py_arr_low    = PyArray_FROM_OTF(py_obj_low, NPY_DOUBLE, NPY_IN_ARRAY);

    double*     p_low_lims    = (double*) (PyArray_DATA(py_arr_low));

    double evid = 0;
    double err = 0;

    PyObject*  return_evidence = PyFloat_FromDouble(evid);
    PyObject*  return_error    = PyFloat_FromDouble(err);
    Py_ssize_t tuple_size      = 2;
    PyObject*  tuple_outputs   = PyTuple_Pack(tuple_size,return_evidence,return_error);

    return tuple_outputs;
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
}
