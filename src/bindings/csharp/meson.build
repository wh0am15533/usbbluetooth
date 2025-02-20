dotnet = find_program('dotnet', required : false)

if not dotnet.found()
    warning('C# bindings are disabled because dotnet could not be found')
else
    proj_ver = meson.project_version().split('-')[0].strip('v')
    custom_target('usbbluetooth_csharp',
        build_by_default: false,
        install: false,
        command: [dotnet, 'build', meson.current_source_dir()+'/UsbBluetooth', '-o', meson.current_build_dir(), '/p:Version='+proj_ver],
        output: 'UsbBluetooth.'+proj_ver+'.nupkg')
endif
