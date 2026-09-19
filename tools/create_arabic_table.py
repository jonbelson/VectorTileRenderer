
#!/usr/bin/env python3


# Using table from https://www.unicode.org/Public/UCD/latest/ucd/UnicodeData.txt
# See https://www.unicode.org/L2/L1999/UnicodeData.html

import sys

from collections import defaultdict

NUM_FIELDS = 15

CODE_VALUE = 0
CHARACTER_NAME = 1
DECOMPOSITION_MAPPING = 5
UPPERCASE_MAPPING = 12
LOWERCASE_MAPPING = 13
TILECASE_MAPPING = 14

try:

	#
	# Process UnicodeData.txt
	#


	def get_decomposition(decomposition):
		if decomposition in valid_decompositions:
			return decomposition[1:-1].capitalize()
		else:
			return '????'



	presentation_forms = defaultdict(dict)

	lam_alef_forms = defaultdict(dict)

	valid_decompositions = [ '<initial>', '<medial>', '<final>', '<isolated>' ]

	f = open("UnicodeData.txt", 'r')

	#print("using Entry = std::pair<uint32_t, uint32_t>;")
	#print()

	num_lines = 0
	for line in f:
		fields = line.split(sep=";")

		if len(fields) > 0 and fields[0].startswith("#"):
			continue

		if len(fields) == NUM_FIELDS:
			if fields[DECOMPOSITION_MAPPING] != "": 

				cp = int(fields[CODE_VALUE], 16)

				dmf = fields[DECOMPOSITION_MAPPING].split(sep=" ")

				if len(dmf) >= 2:
					dtype = dmf[0]

					dmapping = int(dmf[-1], 16)

					if (dtype in valid_decompositions):

						if len(dmf) == 2:
							presentation_forms[dmapping][get_decomposition(dtype)] = cp
						elif len(dmf) > 2:
							lam_alef_forms[dmapping][get_decomposition(dtype)] = cp

#							print(f"    {{ 0x{fields[CODE_VALUE]:4}, 0x{fields[UPPERCASE_MAPPING]:4} }},   // {fields[CHARACTER_NAME]}")
#							print(f"    {{ 0x{fields[CODE_VALUE]:4}, 0x{fields[UPPERCASE_MAPPING]:4} }},   // {fields[CHARACTER_NAME]}")

		#print("};")
		#print()


	print("export enum struct JoinForm")
	print("{")
	for d in sorted(valid_decompositions):
		print(f"    {get_decomposition(d)},")
	print("};")

	print()

	# for outer_key, inner_map in presentation_forms.items():
	# 	for inner_key, value in inner_map.items():
	# 		print(f" outer_key: {outer_key}, inner_key: {inner_key}, cp: 0x{value:4}")

	# print()

	# for outer_key, inner_map in lam_alef_forms.items():
	# 	for inner_key, value in inner_map.items():
	# 		print(f" outer_key: {outer_key}, inner_key: {inner_key}, cp: 0x{value:4}")


	class Form:
		def __init__(self, cp, decomposition, value):
			self.cp = cp
			self.decomposition = decomposition
			self.value = value

		def __str__(self):
			return f"( 0x{self.cp:04X}, {self.decomposition}, 0x{self.value:04X} )"


	presentation_array = []

	for outer_key, inner_map in presentation_forms.items():
		for inner_key, value in inner_map.items():
			presentation_array.append(Form(outer_key, inner_key, value))

	presentation_array.sort(key = lambda entry: ( entry.cp, entry.decomposition ) )


	lam_alef_array = []

	mandatory_lam_alef = [ 0x0622, 0x0623, 0x0625, 0x0627 ]

	for outer_key, inner_map in lam_alef_forms.items():
		if outer_key not in mandatory_lam_alef:
			continue

		for inner_key, value in inner_map.items():
			lam_alef_array.append(Form(outer_key, inner_key, value))

	lam_alef_array.sort(key = lambda entry: ( entry.cp, entry.decomposition ) )


	def write_array(name, atype, prefix, array):
		print(f"\tstatic constexpr auto {name} = std::to_array<{atype}>(")
		print(f"\t{{")
		for item in array:
			print(f"\t\t{{ 0x{item.cp:04X}, {prefix}::{item.decomposition}, 0x{item.value:04X} }},")

		print(f"\t}});")

	write_array("PresentationForms", "Form", "JoinForm", presentation_array)
	write_array("LamAlefLigatures", "Form", "JoinForm", lam_alef_array)


	#
	# Process DerivedJoiningType.txt
	#

	class Entry:
		def __init__(self, start, end, value):
			self.start = start
			self.end = end
			self.value = value

		def __str__(self):
			return f"( {self.start:04X}, {self.end:04X}, {self.value} )"


	# Split codepoint range of form XXXX..YYYY or XXXX into start and end values.
	def get_range(cp_range):
		start = 0
		end = 0

		r = cp_range.split("..")
		if len(r) >= 0:
			start = int(r[0], 16)
			if len(r) > 1:
				end = int(r[1], 16)
			else:
				end = start
		return start, end


	# Write out a std::array<> of 'type' with name 'name' using data from 'array'.
	def write_enum(name, type, prefix, array):

		print(f"\tconstexpr static auto {name} = std::to_array<{type}>(")
		print(f"\t{{")
		for item in array:
			print(f"\t\t{{ 0x{item.start:04X}, 0x{item.end:04X}, {prefix}::{item.value} }},")

		print(f"\t}});")


	joining_type_mapping = {		
		"R": "RightJoining",
		"L": "LeftJoining",
		"D": "DualJoining",
		"C": "JoinCausing",
		"U": "NonJoining",
		"T": "Transparent"	
	}

	NUM_FIELDS = 2

	RANGE = 0
	JOINING_TYPE = 1

	ARABIC_START = 0x0600
	ARABIC_END = 0x07bf

	joining_type_entries = []

	f = open("DerivedJoiningType.txt", 'r')

	for line in f:
		fields = line.split(sep=";")

		if len(fields) > 0 and fields[0].startswith("#"):
			continue

		if len(fields) >= NUM_FIELDS:

			cp_range = fields[RANGE].strip()

			(start, end) = get_range(cp_range)

			if end < ARABIC_START or start > ARABIC_END:
				continue

			jt = fields[1].strip()
			if len(jt) < 1:
				continue

			if joining_type_mapping.get(jt[0]) is None:
				continue;

			joining_type_entries.append(Entry(start, end, joining_type_mapping[jt[0]]))

			#print(f" cp: {cp}, jt: {jt}")

	print()

	joining_type_entries.sort(key=lambda entry: entry.start)

	print("\texport enum struct JoiningType")
	print("\t{")
	for key, value in sorted(joining_type_mapping.items()):
		print(f"\t\t{value},")
	print("\t};")

	print()


	# print("\tconstexpr static auto JoiningTypes = std::to_array<Entry>(")
	# for entry in joining_type_entries:
	# 	for cp in range(entry.start, entry.end + 1):
	# 		print(f"\t\t{{ {{ 0x{cp:04X}, JoiningType::{entry.value} }} }},")
	# print("};")

	write_enum("JoiningTypes", "Entry", "JoiningType", joining_type_entries)

	# print("\tconstexpr static auto JoiningTypes = std::to_array<Entry>(")
	# print(f"\t{{")
	# for entry in joining_type_entries:
	# 	print(f"\t\t{{ 0x{item.start:04X}, 0x{item.end:04X}, JoiningType::{item.value} }},\t// {item.comment}")
	# print("};")



	print()


	sys.exit(0)




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

