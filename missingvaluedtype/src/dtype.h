#ifndef _INTNADTYPE_DTYPE_H
#define _INTNADTYPE_DTYPE_H

#include "numpy/dtype_api.h"

typedef enum {
    int8 = 1,
    int16 = 2,
    int32 = 3,
    int64 = 4,
} precision_t;

typedef struct {
    PyObject *value;
} IntNAScalar_Type;

typedef struct {
    PyArray_Descr base;
    PyObject *precision;
    PyObject *bit_pattern;
} IntNADTypeObject;

extern PyArray_DTypeMeta IntNADType;

PyObject *
new_intnadtype_instance(PyObject *bit_pattern, PyObject *precision);

int
init_intna_dtype(void);

#endif /* _INTNADTYPE_DTYPE_H */
