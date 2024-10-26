#include <Python.h>
#include <stdio.h>

#define MISSINGVALUEDTYPE_MODULE
#define PY_ARRAY_UNIQUE_SYMBOL missingvaluedtype_ARRAY_API
#define PY_UFUNC_UNIQUE_SYMBOL missingvaluedtype_UFUNC_API
#define NPY_NO_DEPRECATED_API NPY_2_0_API_VERSION
#define NPY_TARGET_VERSION NPY_2_0_API_VERSION
#include "numpy/ndarraytypes.h"
#include "numpy/arrayobject.h"
#include "numpy/ufuncobject.h"
#include "numpy/dtype_api.h"

#include "dtype.h"

static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        .m_name = "missingvaluedtype_main",
        .m_size = -1,
};

/* Module initialization function */
PyMODINIT_FUNC
PyInit__main(void)
{
    import_array();
    import_umath();

    PyObject *m = PyModule_Create(&moduledef);
    if (m == NULL) {
        return NULL;
    }

    PyObject *mod = PyImport_ImportModule("missingvaluedtype");
    if (mod == NULL) {
        goto error;
    }

    if (PyModule_AddObject(m, "IntNAScalar", (PyObject *)&IntNAScalar_Type) < 0)
        goto error;

    if (IntNAScalar_Type == NULL) {
        goto error;
    }

    Py_DECREF(mod);

    if (init_intna_dtype() < 0) {
        goto error;
    }

    Py_INCREF((PyObject *)&IntNADType);
    if (PyModule_AddObject(m, "IntNADType", (PyObject *)&IntNADType) < 0) {
        Py_DECREF((PyObject *)&IntNADType);
        printf("error: %d", 1);
        goto error;
    }

    // if (init_ufuncs() == -1) {
    //     goto error;
    // }

    return m;

error:
    printf("error");
    Py_DECREF(m);
    return NULL;
}
