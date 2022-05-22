project('asio',
    'cpp',
    version : '2.11.0'
)

asio_dep_multiple = declare_dependency(
    include_directories: include_directories('.')
)
#install_headers()
#asio_dep = declare_dependency(
#    include_directories: include_directories('header')
#)
asio_dep = asio_dep_multiple

    #install_headers('asio.hpp', subdir: 'asio')
    #
    #pkgc = import('pkgconfig')
    #pkgc.generate(name: 'asio',
    #              description: 'Async IO for c++')
