#!/usr/bin/env python3

import sys
import os
import configparser

# 512B Block size #
block_size = 512
# 16KB Align size #
align_size = 16 * 1024

# NIDB and TFM address is fixed #
NIDB_offset = 0x80
TFM_offset = 0x180

def update_ini_file(setting_file):
    directory = os.path.dirname(setting_file)
    default_file = os.path.join(directory, ".ini")
    print("setting ini file: " + setting_file)
    print("default ini file: " + default_file)

    setting_config = configparser.ConfigParser()
    default_config = configparser.ConfigParser()

    # copy default info #
    setting_config.optionxform = str
    default_config.optionxform = str
    setting_config.read(setting_file)
    for section in setting_config.sections():
        default_config.add_section(section)
        for option in setting_config.options(section):
            value = setting_config.get(section, option)
            default_config.set(section, option, value)

    # update default config #
    part_offset = NIDB_offset
    for section in default_config.sections():
        if default_config.has_option(section, "PartOffset") and default_config.has_option(section, "PartSize"):
            part_file = default_config.get(section, "File")
            part_file = os.path.join(*part_file.split(os.sep)[2:])
            if os.path.exists(part_file):
                part_size = ((os.path.getsize(part_file) + align_size - 1) // align_size) * align_size
                part_size = part_size // block_size

                if default_config.get(section, "Name") == "NIDB":
                    part_size = TFM_offset - NIDB_offset

                default_config.set(section, "PartOffset", f"0x{part_offset:X}")
                default_config.set(section, "PartSize", f"0x{part_size:X}")
                part_offset += part_size
            else:
                print(default_config.get(section, "File") + " file don't exist")
                return -1

    with open(default_file, 'w') as default_file:
        default_config.write(default_file, space_around_delimiters=False)

    return 0

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: " + sys.argv[0] + " <setting.ini>")
        sys.exit(1)

    setting_file = sys.argv[1]
    if os.path.exists(setting_file) and setting_file.endswith('.ini'):
        ret = update_ini_file(setting_file)
        if ret == 0:
            print("make .ini success")
            sys.exit(0)
        else:
            print("make .ini fail")
            sys.exit(1)
    else:
        print("can't create .ini file")
        sys.exit(1)