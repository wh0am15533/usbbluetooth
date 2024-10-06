if build_machine.system() != 'windows' and build_machine.system() != 'cygwin'
    warning('Windows packaging is disabled due to the host OS not being Windows')
else
    tgt_pkg_windows_install = custom_target('_package_windows_install_usbbluetooth',
        build_always_stale: true,
        build_by_default: false,
        install: false,
        command: ['meson.exe', 'install', '-C', meson.project_build_root(), '--destdir', 'package' / 'windows' ],
        output:  ['bin', 'include', 'lib']
    )
    custom_target('package_windows',
        build_by_default: false,
        install: false,
        depends: tgt_pkg_windows_install,
        command: [python3, '-m', 'zipfile', '-c', 'winx64_usbbluetooth_'+meson.project_version()+'.zip', meson.current_build_dir() / 'bin', meson.current_build_dir() / 'include', meson.current_build_dir() / 'lib'],
        output: 'winx64_usbbluetooth_'+meson.project_version()+'.zip')
endif
