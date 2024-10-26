# missing value dtypes

> [!WARNING]
> This is very experimental and not even close to being ready for use.

Bit pattern-based missing value dtypes using the custom `numpy` dtype API defined by the following NEPs:

- [NEP41](https://numpy.org/neps/nep-0041-improved-dtype-support.html)
- [NEP42](https://numpy.org/neps/nep-0042-new-dtypes.html)
- [NEP43](https://numpy.org/neps/nep-0043-extensible-ufuncs.html)

Most the code is copied from [numpy-user-dtypes](https://github.com/numpy/numpy-user-dtypes) and the code of `numpy.dtypes.StringDType` (added in `numpy=2.0`).
