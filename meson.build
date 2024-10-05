project(
    'usbbluetooth',
    'c',
    version : run_command('git', '-C', meson.project_source_root(), 'describe', '--tags', '--always', '--dirty').stdout().strip(),
    meson_version : '>= 0.60.0'
)

subdir('src')
subdir('test')
