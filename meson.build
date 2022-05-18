project('thor', 'cpp', default_options: ['cpp_std=c++11'])

project_sources = ['src/main.cpp']
project_include_dir = include_directories('include')

subdir('test')

cppcheck = find_program('cppcheck', required: false)
if cppcheck.found()
  run_target('cppcheck', command : ['cppcheck', '--project=' + 
    join_paths(meson.build_root(), 'compile_commands.json')]) 
endif

example = executable('thor',
                     project_sources,
                     include_directories: project_include_dir)
