#!/data/data/com.termux/files/usr/bin/bash
kernelVersion="$(uname -r)"
kernelMajor="${kernelVersion%%.*}"
kernelMinor="${kernelVersion#$kernelMajor.}"
kernelMinor="${kernelMinor%%.*}"
kernelMinor2="${kernelVersion#*$kernelMinor.}"
kernelMinor2="${kernelMinor2%%-*}"
echo "Kernel version: $kernelMajor.$kernelMinor.$kernelMinor2"
