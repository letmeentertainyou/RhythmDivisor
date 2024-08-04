#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "array.h"


static PyObject* RhythmError;

Array *rhythm_permutations(Array* start, int size) {
    /* 
    Returns an array of all permutations including duplicates of the starting array with a given size.
    start = starting array of unique digits
    size = desired sum of the output permutations
    */
    Array *old = empty_array(1);
    Array *tmp = empty_array(1);
    Array *tail = empty_array(1);
    Array *perm = empty_array(1);
    Array *results = empty_array(1);
    int max_length = size / 2;

    for (int i = 0; i < start->length; i++) {
        old = append_pad(old, start->values[i]);
    }

    for (int length = 0; length < max_length; length++) {
        for (int start_idx = 0; start_idx < start->length; start_idx ++) {
            int digit = start->values[start_idx];

            for (int old_idx = 0; old_idx < old->length; old_idx++) {
                int value = old->values[old_idx];
                
                if (value != 0) {
                    tail = append(tail, value);
                } else {
                    clear_array(perm);
                    perm = append(perm, digit);
                    perm = extend(perm, tail);
                    clear_array(tail);

                    int sum_perm = sum_array(perm);
                    if (sum_perm == size) {
                        results = extend_pad(results, perm);
                        continue;
                    }
                    if (sum_perm == size - 1) {
                        continue;
                    }
                    if (sum_perm < size) {
                        tmp = extend_pad(tmp, perm);
                    }
                }
            }
            clear_array(tail);
        }
        Array* swap = old;
        old = tmp;
        tmp = swap;
        clear_array(tmp);
    }
    free(start);
    free(old);
    free(tmp);
    free(tail);
    free(perm);
    return results;
}

// NOTE: There is SO much error handling for this one function, I want to reduce it or create a method to do a lot of it but I'm not sure how yet.
PyObject *unpack_array(Array* array) {
    /* 
    This function takes a one dimensional array where zeros mark the boundaries 
    between sub arrays and unpacks it into a 2D Python array.
    */
    PyObject *outer_array = PyList_New(0);

    if (!outer_array) {
        return NULL;
    }
    PyObject *inner_array = PyList_New(0);
    if (!inner_array) {
        Py_DECREF(outer_array);
        return NULL;
    }

    for (int i = 0; i < array->length; i++) {
        if (array->values[i] != 0) {
            PyObject *value = PyLong_FromLong(array->values[i]);
            if (!value) {
                Py_DECREF(inner_array);
                Py_DECREF(outer_array);
                return NULL;
            }
            if (PyList_Append(inner_array, value) == -1) {
                Py_DECREF(value);
                Py_DECREF(inner_array);
                Py_DECREF(outer_array);
                return NULL;
            }
            Py_DECREF(value);
        }
        // On zeros the inner array is appended to the outer array.
        else {
            if (PyList_Append(outer_array, inner_array) == -1) {
                Py_DECREF(inner_array);
                Py_DECREF(outer_array);
                return NULL;
            }
            Py_DECREF(inner_array);
            inner_array = PyList_New(0);
            if (!inner_array) {
                Py_DECREF(outer_array);
                return NULL;
            }
        }
    }
    Py_DECREF(inner_array);
    return outer_array;
}

static PyObject* permutations(PyObject* self, PyObject* args) {
    /*
    This function is the C Python wrapper of the above rhythm_permutations function.
    */

    PyObject *START;
    int size;
    if (!PyArg_ParseTuple(args, "Oi", &START, &size)) {
        return NULL;
    }

    int start_length = (int)PyList_Size(START);
    Array *start = empty_array(start_length);
    for (int i = 0; i < start_length; i++) {
        // There is no simpler way to extract an int from a PyObject
        // Note this method called PyList_GetItem doesn't take PyListObjects. 
        append(start, (int) PyFloat_AsDouble(PyList_GetItem(START, (Py_ssize_t)i)));
    }

    Py_DECREF(START);
    Array *packed_results = rhythm_permutations(start, size);
    PyObject *results = unpack_array(packed_results);
    free(packed_results);
    return results;
}

static PyMethodDef RhythmMethods[] = {
    {
        // This is the external name of the method.
        "permutations",
        // This is the internal name of the method, they don't have to match.
        permutations,
        METH_VARARGS,
        "Calculate the rhythmic permutations of a given size and return a one dimensional list.\n",
    },
    {NULL, NULL, 0, NULL},  // This means all the methods have been defined.
};

static PyModuleDef rhythmmodule = {
    PyModuleDef_HEAD_INIT,
    "rhythm",
    "A C Python version of rhythm.py.",
    -1,
    RhythmMethods,
};

PyMODINIT_FUNC PyInit_rhythm() {
    PyObject* module;
    module = PyModule_Create(&rhythmmodule);
    
    if (module == NULL) {
        return NULL;
    }
    
    RhythmError = PyErr_NewException("rhythm.Error", NULL, NULL);
    Py_INCREF(RhythmError);
    PyModule_AddObject(module, "Error", RhythmError);
    return module;
}
