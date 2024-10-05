# Check if libusb is present, otherwise build it...
libusb_dep = dependency('libusb-1.0')

# Project library
libusbbluetooth_inc = include_directories('.')
libusbbluetooth_src = files([
  'usbbluetooth_err.c',
  'usbbluetooth_core.c',
  'usbbluetooth_device.c',
  'usbbluetooth_io.c',
  'utils.c',
])
libusbbluetooth_pub_headers = files([
  'usbbluetooth.h',
  'usbbluetooth_err.h',
  'usbbluetooth_api.h',
  'usbbluetooth_core.h',
  'usbbluetooth_device.h',
  'usbbluetooth_io.h'
])
libusbbluetooth_target = library('usbbluetooth',
  sources : libusbbluetooth_src,
  include_directories: libusbbluetooth_inc,
  install: true,
  vs_module_defs : 'usbbluetooth.def',
  dependencies : libusb_dep)

# Header installation
install_headers(libusbbluetooth_pub_headers, subdir : 'usbbluetooth')

# PC file
pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : 'usbbluetooth',
  description : 'LibUSB based Bluetooth device driver',
  libraries : libusbbluetooth_target,
)

# Library dependency
libusbbluetooth_dep = declare_dependency(
  include_directories: libusbbluetooth_inc,
  link_with : libusbbluetooth_target,
  dependencies : libusb_dep
)
