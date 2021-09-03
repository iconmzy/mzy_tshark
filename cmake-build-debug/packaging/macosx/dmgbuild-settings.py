# -*- coding: utf-8 -*-
from __future__ import unicode_literals

import biplist
import os.path

#
# Example settings file for dmgbuild
#
# Adapted from https://raw.githubusercontent.com/al45tair/dmgbuild/master/examples/settings.py

# Use like this: dmgbuild -s settings.py "Test Volume" test.dmg

# You can actually use this file for your own application (not just TextEdit)
# by doing e.g.
#
#   dmgbuild -s settings.py -D app=/path/to/My.app "My Application" MyApp.dmg

# .. Useful stuff ..............................................................

ws_version = '3.4.5'
ws_volname = 'Wireshark ' + ws_version
ws_srcdir = '/home/ymq/tshark'
ws_bindir = '/home/ymq/tshark/cmake-build-debug'
ws_app = 'Wireshark.app'
ws_readme = 'Read me first.html'
ws_install_chmodbpf = 'Install ChmodBPF.pkg'
ws_uninstall_chmodbpf = 'Uninstall ChmodBPF.pkg'
ws_install_path_helper = 'Add Wireshark to the system path.pkg'
ws_uninstall_path_helper = 'Remove Wireshark from the system path.pkg'

# .. Basics ....................................................................

# Uncomment to override the output filename
# filename = ws_volname + ' Intel 64.dmg'

# Uncomment to override the output volume name
# volume_name = 'Wireshark ' + ws_version

# From the hdiutil man page:
# UDZO - UDIF zlib-compressed image
# UDBZ - UDIF bzip2-compressed image (Mac OS X 10.4+ only)
# ULFO - UDIF lzfse-compressed image (OS X 10.11+ only)
# Volume format (see hdiutil create -help)
format = defines.get('format', 'UDBZ')

# Compression level (if relevant)
compression_level = 9

# Volume size
size = None

# Files to include
files = [
    os.path.join(ws_bindir, 'run', ws_app),
    os.path.join(ws_bindir, 'packaging', 'macosx', ws_readme),
]

# Symlinks to create
symlinks = {
    'Applications': '/Applications',
    ws_install_chmodbpf: os.path.join(ws_app, 'Contents', 'Resources', 'Extras', ws_install_chmodbpf),
    ws_uninstall_chmodbpf: os.path.join(ws_app, 'Contents', 'Resources', 'Extras', ws_uninstall_chmodbpf),
    ws_install_path_helper: os.path.join(ws_app, 'Contents', 'Resources', 'Extras', ws_install_path_helper),
    ws_uninstall_path_helper: os.path.join(ws_app, 'Contents', 'Resources', 'Extras', ws_uninstall_path_helper),
    }

# Volume icon
#
# You can either define icon, in which case that icon file will be copied to the
# image, *or* you can define badge_icon, in which case the icon file you specify
# will be used to badge the system's Removable Disk icon
#
badge_icon = os.path.join(ws_srcdir, 'packaging', 'macosx', 'wsiconvol.icns')
#badge_icon = icon_from_app(application)

# Where to put the icons
icon_locations = {
    ws_app:                     ( 80,  64),
    'Applications':             (240,  64),
    ws_readme:                  (160, 170),
    ws_install_chmodbpf:        ( 80, 276),
    ws_uninstall_chmodbpf:      (250, 276),
    ws_install_path_helper:     ( 80, 382),
    ws_uninstall_path_helper:   (250, 382),
    }

# .. Window configuration ......................................................

# Background
#
# This is a STRING containing any of the following:
#
#    #3344ff          - web-style RGB color
#    #34f             - web-style RGB color, short form (#34f == #3344ff)
#    rgb(1,0,0)       - RGB color, each value is between 0 and 1
#    hsl(120,1,.5)    - HSL (hue saturation lightness) color
#    hwb(300,0,0)     - HWB (hue whiteness blackness) color
#    cmyk(0,1,0,0)    - CMYK color
#    goldenrod        - X11/SVG named color
#    builtin-arrow    - A simple built-in background with a blue arrow
#    /foo/bar/baz.png - The path to an image file
#
# The hue component in hsl() and hwb() may include a unit; it defaults to
# degrees ('deg'), but also supports radians ('rad') and gradians ('grad'
# or 'gon').
#
# Other color components may be expressed either in the range 0 to 1, or
# as percentages (e.g. 60% is equivalent to 0.6).
background = os.path.join(ws_srcdir, 'packaging', 'macosx', 'dmg_background.png')

show_status_bar = False
show_tab_view = False
show_toolbar = False
show_pathbar = False
show_sidebar = False
sidebar_width = 180

# Window position in ((x, y), (w, h)) format
window_rect = ((600, 200), (350, 525))

# Select the default view; must be one of
#
#    'icon-view'
#    'list-view'
#    'column-view'
#    'coverflow'
#
default_view = 'icon-view'

# General view configuration
show_icon_preview = False

# Set these to True to force inclusion of icon/list view settings (otherwise
# we only include settings for the default view)
include_icon_view_settings = 'auto'
include_list_view_settings = 'auto'

# .. Icon view configuration ...................................................

arrange_by = None
grid_offset = (0, 0)
#grid_spacing = 100
scroll_position = (0, 0)
#label_pos = 'bottom' # or 'right'
text_size = 12
icon_size = 72
