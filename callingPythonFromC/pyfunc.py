import numpy as np
import callback_module

def numpysum(x,sumx):
    """
    This function computes the sum of all values in vector x
    and returns that value to sumx[0]. sumx is assumed to be
    an array with size=1.

    We also return a value 123. at the end

    @param x a numpy array of floating point numbers
    @param sumx a numpy array of size 1 to return the sum
    @return the flating point number 123.
    """
    sumx[0] = np.sum(x) # sumx is assumed to be an array of size 1
    return 123. # return some value for testing


# call back
callback_module.callback_func(numpysum)

