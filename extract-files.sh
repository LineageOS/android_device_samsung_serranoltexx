#!/bin/sh

set -e

export DEVICE=serrano-common
export VENDOR=samsung
./../$DEVICE/extract-files.sh $@
