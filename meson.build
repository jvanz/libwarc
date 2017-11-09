project('libwarc', 'cpp')

sources = ['src/warc.cc']
include = include_directories('include')

libwarc = shared_library('warc', sources, 
	include_directories: include, 
	install: true)

libwarc_dep = declare_dependency(
	include_directories: include,
	link_with: libwarc,
	sources: sources)

# tests 
tests_sources = ['tests/main.cc']
tests_dependencies = [dependency('gtest'), libwarc_dep]
executable('tests', 
	tests_sources, 
	dependencies: tests_dependencies)

