project('libwarc', 'cpp', version: '0.9.0', default_options : ['cpp_std=c++14'])

sources = ['src/warc.cc', 'src/constants.hh', 'src/constants.cc']
include = include_directories('include')

libwarc = shared_library('warc', sources,
	include_directories: include,
	install: true)

# pkgconfig

pkg = import('pkgconfig')
pkg.generate(
	name : 'warc',
	description : 'A C++ 14 library to parse WARC files',
	version : meson.project_version(),
	libraries : libwarc,
)

# tests

libwarc_dep = declare_dependency(
	include_directories: include,
	link_with: libwarc,
	sources: sources)

tests_sources = ['tests/main.cc', 'tests/helper.cc', 'tests/helper.hh']
tests_dependencies = [dependency('gtest'), libwarc_dep]

tests = executable('tests',
	tests_sources,
	dependencies: tests_dependencies)

test('warcrecord', tests, args: ['--gtest_filter=WARCRecord.*'])
test('cppconcepts', tests, args: ['--gtest_filter=WARCRecord.warcrecord_cpp_concepts:WARCField.warcfield_cpp_concepts'])
test('input_iterator', tests, args: ['--gtest_filter=WARCRecord.warc_record_input_iterator'])
