#!/usr/bin/env python3


# Using table from https://www.unicode.org/Public/UCD/latest/ucd/UnicodeData.txt
# See https://www.unicode.org/L2/L1999/UnicodeData.html

NUM_FIELDS = 15

CODE_VALUE = 0
CHARACTER_NAME = 1
UPPERCASE_MAPPING = 12
LOWERCASE_MAPPING = 13
TILECASE_MAPPING = 14

try:

    f = open("UnicodeData.txt", 'r');


    print("using Entry = std::pair<uint32_t, uint32_t>;")
    print()

    num_lines = 0
    for line in f:
        fields = line.split(sep=";")
        if len(fields) == NUM_FIELDS:
            if fields[UPPERCASE_MAPPING] != "": 
                print(f"    {{ 0x{fields[CODE_VALUE]:4}, 0x{fields[UPPERCASE_MAPPING]:4} }},   // {fields[CHARACTER_NAME]}")
                num_lines = num_lines + 1

    print("};")
    print()

    print(f"static constexpr std::array<Entry, {num_lines}> ToUpper = {{")
    print()

    f.seek(0)

    num_lines = 0
    for line in f:
        fields = line.split(sep=";")
        if len(fields) == NUM_FIELDS:
            if fields[LOWERCASE_MAPPING] != "":
                print(f"    {{ 0x{fields[CODE_VALUE]:4}, 0x{fields[LOWERCASE_MAPPING]:4} }},   // {fields[CHARACTER_NAME]}")
                num_lines = num_lines + 1

    print("};")
    print()

    print(f"static constexpr std::array<Entry, {num_lines}> ToLower = {{")


except IOError as e:
    print('file open error:', e)



