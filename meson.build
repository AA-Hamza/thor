project('thor', 'cpp', default_options: ['cpp_std=c++11'])

subproject('asio', required: true)
asio = dependency('asio', required: true)

project_sources = ['src/main.cpp', './src/http/reply.cpp', './src/http/mime_types.cpp', './src/http/request_parser.cpp', './src/master/master.cpp', './src/worker/worker.cpp', './src/worker/connection.cpp', './src/worker/worker.cpp', './src/worker/request_handler.cpp', './src/worker/connection_manager.cpp']
project_include_dir = include_directories('include')

subdir('test')

cppcheck = find_program('cppcheck', required: false)
if cppcheck.found()
  run_target('cppcheck', command : ['cppcheck', '--project=' + 
    join_paths(meson.build_root(), 'compile_commands.json')]) 
endif

example = executable('thor',
                     project_sources,
                     dependencies: asio,
                     include_directories: project_include_dir)
