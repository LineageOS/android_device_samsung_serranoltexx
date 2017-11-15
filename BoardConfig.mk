# Copyright (C) 2013-2016, The CyanogenMod Project
# Copyright (C) 2017, The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#
# This file sets variables that control the way modules are built
# thorughout the system. It should not be used to conditionally
# disable makefiles (the proper mechanism to control what gets
# included in a build is to use PRODUCT_PACKAGES in a product
# definition file).
#

# Inherit from common serrano
-include device/samsung/serrano-common/BoardConfigCommon.mk

# Inherit from proprietary vendor
-include vendor/samsung/serranoltexx/BoardConfigVendor.mk

# Assert
TARGET_OTA_ASSERT_DEVICE := serranolte,serranoltebmc,serranoltektt,serranoltexx

# Kernel
TARGET_KERNEL_VARIANT_CONFIG := msm8930_serrano_eur_lte_defconfig

# Lights
TARGET_PROVIDES_LIBLIGHT := true

# BLN
BOARD_HAVE_GENERIC_BLN := true

# Charger
BOARD_NO_CHARGER_LED := true

# Vendor Init
TARGET_INIT_VENDOR_LIB := libinit_serranolte
TARGET_RECOVERY_DEVICE_MODULES := libinit_serranolte
