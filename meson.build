project('libwarc', 'cpp')

sources = ['src/warc.cc']
include = include_directories('include')

shared_library('warc', sources, include_directories: include)

tests_sources = ['tests/main.cc']
tests_dependencies = [dependency('gtest')]
executable('tests', tests_sources, include_directories: include, dependencies: tests_dependencies)

