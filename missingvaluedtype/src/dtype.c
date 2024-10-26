// clang-format off
#include <Python.h>
#include "structmember.h"
// clang-format on

#define NPY_TARGET_VERSION NPY_2_0_API_VERSION
#define NPY_NO_DEPRECATED_API NPY_2_0_API_VERSION

#include "numpy/arrayobject.h"
#include "numpy/dtype_api.h"

#include "dtype.h"

/*
 * Internal helper to create new instances
 */
PyObject *
new_intnadtype_instance(PyObject *bit_pattern, PyObject *precision)
{
    PyObject *new = PyArrayDescr_Type.tp_new((PyTypeObject *)&IntNADType, NULL, NULL);

    if (new == NULL) {
        return NULL;
    }

    Py_XINCREF(bit_pattern);
    ((IntNADTypeObject *)new)->bit_pattern = bit_pattern;
    int hasnull = bit_pattern != NULL;
    if (hasnull) {
    }

    Py_XINCREF(precision);
    ((IntNADTypeObject *)new)->precision = precision;

    PyArray_Descr *base = (PyArray_Descr *)new;
    base->flags |= NPY_NEEDS_INIT;
    base->flags |= NPY_LIST_PICKLE;
    base->flags |= NPY_ITEM_REFCOUNT;

    return new;
}

static PyType_Slot IntNADType_Slots[] = {
    // {NPY_DT_ensure_canonical, &ensure_canonical},
    // {NPY_DT_common_instance, &common_instance},
    // {NPY_DT_common_dtype, &common_dtype},
    // {NPY_DT_discover_descr_from_pyobject, &mpf_discover_descriptor_from_pyobject},
    // {NPY_DT_setitem, &mpf_setitem},
    // {NPY_DT_getitem, &mpf_getitem},
    {0, NULL}
};


static PyObject *
intnadtype_new(PyTypeObject *NPY_UNUSED(cls), PyObject *args, PyObject *kwds)
{
    static char *kwargs_strs[] = {"precision", "bit_pattern", NULL};

    PyObject *precision;
    PyObject *bit_pattern;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|$pO&:IntNADType",
                                     kwargs_strs, &precision, &bit_pattern)) {
        return NULL;
    }

    return new_intnadtype_instance(precision, bit_pattern);
}


static void
intnadtype_dealloc(IntNADTypeObject *self)
{
    Py_XDECREF(self->bit_pattern);
    Py_XDECREF(self->precision);
    PyArrayDescr_Type.tp_dealloc((PyObject *)self);
}


static PyObject *
intnadtype_repr(IntNADTypeObject *self)
{
    PyObject *ret = PyUnicode_FromString("IntNADType()");

    return ret;
}


/*
 * This is the basic things that you need to create a Python Type/Class in C.
 * However, there is a slight difference here because we create a
 * PyArray_DTypeMeta, which is a larger struct than a typical type.
 * (This should get a bit nicer eventually with Python >3.11.)
 */
PyArray_DTypeMeta IntNADType = {
        {{
                PyVarObject_HEAD_INIT(NULL, 0).tp_name =
                        "missingvaluedtypes.IntNADType",
                .tp_basicsize = sizeof(IntNADTypeObject),
                .tp_new = intnadtype_new,
                .tp_dealloc = (destructor)intnadtype_dealloc,
                .tp_repr = (reprfunc)intnadtype_repr,
                .tp_str = (reprfunc)intnadtype_repr,
        }},
        /* rest, filled in during DTypeMeta initialization */
};


int
init_intna_dtype(void)
{
    // PyArrayMethod_Spec **IntNADType_casts = get_casts();

    PyArrayDTypeMeta_Spec IntNADType_DTypeSpec = {
            .flags = NPY_DT_PARAMETRIC | NPY_DT_NUMERIC,
            .typeobj = IntNAScalar_Type,
            .slots = IntNADType_Slots,
            // .casts = IntNADType_casts,
    };

    /* Loaded dynamically, so may need to be set here: */
    ((PyObject *)&IntNADType)->ob_type = &PyArrayDTypeMeta_Type;
    ((PyTypeObject *)&IntNADType)->tp_base = &PyArrayDescr_Type;
    if (PyType_Ready((PyTypeObject *)&IntNADType) < 0) {
        return -1;
    }

    if (PyArrayInitDTypeMeta_FromSpec((PyArray_DTypeMeta *)&IntNADType,
                                      &IntNADType_DTypeSpec) < 0) {
        return -1;
    }

    PyArray_Descr *singleton =
            PyArray_GetDefaultDescr((PyArray_DTypeMeta *)&IntNADType);

    if (singleton == NULL) {
        return -1;
    }

    IntNADType.singleton = singleton;

    // for (int i = 0; IntNADType_casts[i] != NULL; i++) {
    //     PyMem_Free(IntNADType_casts[i]->dtypes);
    //     PyMem_Free(IntNADType_casts[i]);
    // }

    // PyMem_Free(IntNADType_casts);

    return 0;
}
