#include <Python.h>
#include <square.h>

static PyObject* square_func(PyObject* self, PyObject* args)
{
    double value;
    double answer;

    if (!PyArg_ParseTuple(args, "d", &value))
    {
        return NULL;
    }

    answer = square(value);

    return Py_BuildValue("d", answer);

}

/*  define functions in module */
static PyMethodDef SquareMethods[] =
{
    {"square_func", square_func, METH_VARARGS, "evaluate the square"},
    {NULL, NULL, 0, NULL}
};

/* module initialization */
PyMODINIT_FUNC

initsquare_module(void)
{
     (void) Py_InitModule("square_module", SquareMethods);
}
