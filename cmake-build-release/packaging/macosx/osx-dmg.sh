#!/bin/bash
#
# The script creates a disk image using the dmgbuild utility and signs it.

set -e

# Defaults
dmgbuild=""
version="3.4.5"
settings_file="/root/CLionProjects/tshark_shanghai/cmake-build-release/packaging/macosx/dmgbuild-settings.py"
architecture="Intel 64"

# Help message
#----------------------------------------------------------
help()
{
echo -e "
Create a custom dmg file to distribute Wireshark

USAGE
	$0

OPTIONS
	-h,--help
		Display this help message.

Icons are positioned and the background image is set in
dmgbuild-settings.py.in.
"
}

if [ ! -x "$dmgbuild" ] ; then
	echo "Error: \"$dmgbuild\" not found."
	exit 1
fi

# Parse command line arguments
while [ "$1" != "" ]
do
	case $1 in
		-h|--help)
			help
			exit 0 ;;
		*)
			echo "Invalid command line option"
			exit 2 ;;
	esac
	shift 1
done

vol_name="Wireshark ${version}"
img_name="$vol_name $architecture.dmg"

echo -e "\\nCREATE WIRESHARK DISK IMAGE\\n"

"$dmgbuild" \
	--no-hidpi \
	-s "$settings_file" \
	"$vol_name" \
	"$img_name" || exit 1

echo -e "\\nSIGN WIRESHARK DISK IMAGE\\n"

# TN2206, "Signing Disk Images"
if [ -n "$CODE_SIGN_IDENTITY" ] ; then
	echo -e "Signing $img_name"
	codesign \
		--sign "Developer ID Application: $CODE_SIGN_IDENTITY" \
		--timestamp \
		--verbose \
		"$img_name"
	spctl --assess --type open --context context:primary-signature --verbose=2 "$img_name" || exit 1
fi

exit 0