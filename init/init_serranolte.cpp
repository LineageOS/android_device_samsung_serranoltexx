/*
 * Copyright 2016, The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm.h"

/* Serial number */
#define SERIAL_FILE "/efs/FactoryApp/serial_no"
#define SERIAL_PROP "ro.serialno"
#define SERIAL_OFFSET 0x00
#define SERIAL_LENGTH 11

static int read_file(const char *fname, char *data, int max_size)
{
    int fd, rc;

    if (max_size < 1)
        return 0;

    fd = open(fname, O_RDONLY);
    if (fd < 0) {
        ERROR("failed to open '%s'\n", fname);
        return 0;
    }

    rc = read(fd, data, max_size -1);
    if ((rc > 0) && (rc < max_size ))
        data[rc] = '\0';
    else
        data[0] = '\0';
    close(fd);

    return 1;
}

static void get_serial()
{
    int ret = 0;
    char const *path = SERIAL_FILE;
    char buf[SERIAL_LENGTH + 1];
    prop_info *pi;

    if(read_file(path, buf, sizeof(buf))) {

        if (strlen(buf) > 0) {
            pi = (prop_info*) __system_property_find(SERIAL_PROP);
            if(pi)
                ret = __system_property_update(pi, buf,
                        strlen(buf));
            else
                ret = __system_property_add(SERIAL_PROP,
                        strlen(SERIAL_PROP),
                        buf, strlen(buf));
        }
    }
}

void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type)
{
    char platform[PROP_VALUE_MAX];
    char bootloader[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    int rc;

    UNUSED(msm_id);
    UNUSED(msm_ver);
    UNUSED(board_type);

    rc = property_get("ro.board.platform", platform);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
        return;

    property_get("ro.bootloader", bootloader);

    if (strstr(bootloader, "I257M")) {
        /* serranoltebmc */
        property_set("ro.build.fingerprint", "samsung/serranoltebmc/serranoltebmc:4.4.2/KOT49H/I257MVLUBNE6:user/release-keys");
        property_set("ro.build.description", "serranoltebmc-user 4.4.2 KOT49H I257MVLUBNE6 release-keys");
        property_set("ro.product.model", "SGH-I257M");
        property_set("ro.product.device", "serranoltebmc");
    } else if (strstr(bootloader, "I9195")) {
        /* serranoltexx */
        property_set("ro.build.fingerprint", "samsung/serranoltexx/serranolte:4.4.2/KOT49H/I9195XXUCNE6:user/release-keys");
        property_set("ro.build.description", "serranoltexx-user 4.4.2 KOT49H I9195XXUCNE6 release-keys");
        property_set("ro.product.model", "GT-I9195");
        property_set("ro.product.device", "serranoltexx");
    } else if (strstr(bootloader, "E370K")) {
        /* serranoltektt */
        property_set("ro.build.fingerprint", "samsung/serranoltektt/serranoltektt:4.4.4/KTU84P/E370KKTU2BNK5:user/release-keys");
        property_set("ro.build.description", "serranoltektt-user 4.4.4 KTU84P E370KKTU2BNK5 release-keys");
        property_set("ro.product.model", "SHV-E370K");
        property_set("ro.product.device", "serranoltektt");
    }

    get_serial();
    property_get("ro.product.device", device);
    strlcpy(devicename, device, sizeof(devicename));
    INFO("Found bootloader id %s setting build properties for %s device\n", bootloader, devicename);
}
