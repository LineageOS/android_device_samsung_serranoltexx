#!/bin/sh

set -e

export DEVICE_COMMON=serrano-common
export DEVICE=serranoltexx
export VENDOR=samsung
./../$DEVICE_COMMON/extract-files.sh $@
