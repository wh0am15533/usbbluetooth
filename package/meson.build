subdir('windows')

# A dummy target that allways gets executed
# Whoami is the only common command available in all platforms
# I could think of...
tgt_pkg_dummy = custom_target('package_dummy',
        build_by_default: false,
        install: false,
        command: ['whoami'],
        output: 'package_dummy'
)

package_targets = [tgt_pkg_dummy]
if build_machine.system() == 'windows' or build_machine.system() == 'cygwin'
    package_targets += tgt_pkg_win
endif

alias_target('package', package_targets)
