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
libusbbluetooth_target = library('usbbluetooth',
  sources : libusbbluetooth_src,
  include_directories: libusbbluetooth_inc,
  vs_module_defs : 'usbbluetooth.def',
  dependencies : libusb_dep)

# Library dependency
libusbbluetooth_dep = declare_dependency(
  include_directories: libusbbluetooth_inc,
  link_with : libusbbluetooth_target,
  dependencies : libusb_dep
)
