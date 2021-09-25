project('source', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

executable('source',
           ['./source/main.cpp', './source/display.cpp', './source/object.cpp'],
           install : true,
           link_args : ['-lraylib', '-lGL', '-lm', '-pthread', '-ldl'])
