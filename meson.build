project(
  'missingvaluedtype',
  'c',
)

py_mod = import('python')
py = py_mod.find_installation()

incdir_numpy = run_command(py,
  [
    '-c',
    'import numpy; print(numpy.get_include())'
  ],
  check: true
).stdout().strip()

cc = meson.get_compiler('c')

npymath_path = incdir_numpy / '..' / 'lib'
npymath_lib = cc.find_library('npymath', dirs: npymath_path)
inc_np = include_directories(incdir_numpy)
np_dep = declare_dependency(include_directories: inc_np)

includes = include_directories(
  [
    incdir_numpy,
    'missingvaluedtype/src'
  ]
)

srcs = [
  # 'missingvaluedtype/src/casts.c',
  # 'missingvaluedtype/src/casts.h',
  'missingvaluedtype/src/dtype.c',
  'missingvaluedtype/src/main.c',
  # 'missingvaluedtype/src/umath.c',
  # 'missingvaluedtype/src/umath.h',
]

py.install_sources(
  [
    'missingvaluedtype/__init__.py',
    'missingvaluedtype/scalar.py',
  ],
  subdir: 'missingvaluedtype',
  pure: false
)

py.extension_module(
  '_main',
  srcs,
  install: true,
  subdir: 'missingvaluedtype',
  include_directories: includes,
  dependencies: [np_dep, npymath_lib]
)
