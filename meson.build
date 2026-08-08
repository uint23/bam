project(
	'bam',
	'c',
	default_options: [
		'c_std=c89',
		'warning_level=3',
	],
)

maus_subproject = subproject('maus', default_options: ['default_library=static'])
maus_dependency = maus_subproject.get_variable('maus_dep')

cc = meson.get_compiler('c')

vendor_sources = [
]
sources = [
	'source/bam.c',
        vendor_sources
]

vendor_include_dirs = [
]
include_dirs = [
	include_directories('include'),
        vendor_include_dirs
]

executable(
	'bam',
	sources,
	include_directories: include_dirs,
	dependencies: maus_dependency,
)

