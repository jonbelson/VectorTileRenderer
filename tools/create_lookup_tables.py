#!/usr/bin/env python3

# Read the following Unicode data tables, merge them into a single table then write as C++ code.
# Note the first two files might need edits be be parseable (F;)
# https://www.unicode.org/Public/UNIDATA/extracted/DerivedBidiClass.txt
# https://www.unicode.org/Public/UNIDATA/extracted/DerivedGeneralCategory.txt
# https://www.unicode.org/Public/UCD/latest/ucd/Scripts.txt
# https://www.unicode.org/Public/12.0.0/ucd/Blocks.txt


bidi_classes = [ "LeftToRight", "RightToLeft", "EuropeanNumber", "EuropeanSeparator", "EuropeanTerminator", "ArabicNumber", "CommonSeparator", "ParagraphSeparator", "SegmentSeparator", "WhiteSpace", "OtherNeutral", "BoundaryNeutral", "NonspacingMark", "ArabicLetter", "LeftToRightOverride", "RightToLeftOverride", "LeftToRightEmbedding", "RightToLeftEmbedding", "PopDirectionalFormat", "LeftToRightIsolate", "RightToLeftIsolate", "FirstStrongIsolate", "PopDirectionalIsolate" ]

bidi_mapping = {
		"L": "LeftToRight",
		"R": "RightToLeft",
		"EN": "EuropeanNumber",
		"ES": "EuropeanSeparator",
		"ET": "EuropeanTerminator",
		"AN": "ArabicNumber",
		"CS": "CommonSeparator",
		"B": "ParagraphSeparator",
		"S": "SegmentSeparator",
		"WS": "WhiteSpace",
		"ON": "OtherNeutral",
		"BN": "BoundaryNeutral",
		"NSM": "NonspacingMark",
		"AL": "ArabicLetter",
		"LRO": "LeftToRightOverride",
		"RLO": "RightToLeftOverride",
		"LRE": "LeftToRightEmbedding",
		"RLE": "RightToLeftEmbedding",
		"PDF": "PopDirectionalFormat",
		"LRI": "LeftToRightIsolate",
		"RLI": "RightToLeftIsolate",
		"FSI": "FirstStrongIsolate",
		"PDI": "PopDirectionalIsolate"
}
 
general_category = [
"UppercaseLetter", "LowercaseLetter", "TitlecaseLetter", "CasedLetter", "ModifierLetter", "OtherLetter", "Letter", "NonspacingMark", "SpacingMark", "EnclosingMark", "Mark", "DecimalNumber", "LetterNumber", "OtherNumber", "Number", "ConnectorPunctuation", "DashPunctuation", "OpenPunctuation", "ClosePunctuation", "InitialPunctuation", "FinalPunctuation", "OtherPunctuation", "Punctuation", "MathSymbol", "CurrencySymbol", "ModifierSymbol", "OtherSymbol", "Symbol", "SpaceSeparator", "LineSeparator", "ParagraphSeparator", "Separator", "Control", "Format", "Surrogate", "PrivateUse", "Unassigned", "Other"
]


category_mapping = {
		"Lu": "UppercaseLetter",	# an uppercase letter
		"Ll": "LowercaseLetter",	# a lowercase letter
		"Lt": "TitlecaseLetter",	# a digraph encoded as a single character, with first part uppercase
		"LC": "CasedLetter",       # Lu | Ll | Lt
		"L&": "CasedLetter",       # Lu | Ll | Lt
		"Lm": "ModifierLetter",	# a modifier letter
		"Lo": "OtherLetter",	# other letters, including syllables and ideographs
		"L": "Letter",	# Lu | Ll | Lt | Lm | Lo
		"Mn": "NonspacingMark",	# a nonspacing combining mark (zero advance width)
		"Mc": "SpacingMark",	# a spacing combining mark (positive advance width)
		"Me": "EnclosingMark",	# an enclosing combining mark
		"M": "Mark",	# Mn | Mc | Me
		"Nd": "DecimalNumber",	# a decimal digit
		"Nl": "LetterNumber",	# a letterlike numeric character
		"No": "OtherNumber",	# a numeric character of other type
		"N": "Number",	# Nd | Nl | No
		"Pc": "ConnectorPunctuation",	# a connecting punctuation mark, like a tie
		"Pd": "DashPunctuation",	# a dash or hyphen punctuation mark
		"Ps": "OpenPunctuation",	# an opening punctuation mark (of a pair)
		"Pe": "ClosePunctuation",	# a closing punctuation mark (of a pair)
		"Pi": "InitialPunctuation",	# an initial quotation mark
		"Pf": "FinalPunctuation",	# a final quotation mark
		"Po": "OtherPunctuation",	# a punctuation mark of other type
		"P": "Punctuation",	# Pc | Pd | Ps | Pe | Pi | Pf | Po
		"Sm": "MathSymbol",	# a symbol of mathematical use
		"Sc": "CurrencySymbol",	# a currency sign
		"Sk": "ModifierSymbol",	# a non-letterlike modifier symbol
		"So": "OtherSymbol",	# a symbol of other type
		"S": "Symbol",	# Sm | Sc | Sk | So
		"Zs": "SpaceSeparator",	# a space character (of various non-zero widths)
		"Zl": "LineSeparator",	# U+2028 LINE SEPARATOR only
		"Zp": "ParagraphSeparator",	# U+2029 PARAGRAPH SEPARATOR only
		"Z": "Separator",	# Zs | Zl | Zp
		"Cc": "Control",	# a C0 or C1 control code
		"Cf": "Format",	# a format control character
		"Cs": "Surrogate",	# a surrogate code point
		"Co": "PrivateUse",	# a private-use character
		"Cn": "Unassigned",	# a reserved unassigned code point or a noncharacter
		"C": "Other",	# Cc | Cf | Cs | Co | Cn
}



try:


	class Entry:
		def __init__(self, start, end, value, comment = ""):
			self.start = start
			self.end = end
			self.value = value
			self.comment = comment

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
	

	# Merge consecutive ranges that have the same value.
	def merge_ranges(array):
		i = 0
		while i < len(array) - 1:
			if array[i].end + 1 == array[i + 1].start and array[i].value == array[i + 1].value:
				array[i].end = array[i + 1].end

				if not array[i].comment:
					array[i].comment = array[i + 1].comment
				elif array[i + 1].comment:
					array[i].comment += " | " + array[i + 1].comment

				del(array[i + 1])
			else:
				i+=1


	# Write out a std::array<> of 'type' with name 'name' using data from 'array'.
	def write_enum(name, type, prefix, array):

		print(f"\tstatic constexpr auto {name} = std::to_array<{type}>(")
		print(f"\t{{")
		for item in array:
			print(f"\t\t{{ 0x{item.start:04X}, 0x{item.end:04X}, {prefix}::{item.value} }},\t// {item.comment}")

		print(f"\t}});")


	#
	# Process DerivedBidiClass.txt
	#


	NUM_FIELDS = 5

	CODE_VALUE = 0
	RANGE = 0
	CLASS =  2
	COMMENT = 5

	bidi_entries = []

	bidi_f = open("DerivedBidiClass.txt", 'r');


	for line in bidi_f:
		fields = line.split()

		if len(fields) > 0 and fields[0] == '#':
			continue

		if len(fields) > NUM_FIELDS:

			cp_range = fields[RANGE]

			(start, end) = get_range(fields[RANGE])

			value = bidi_mapping.get(fields[CLASS], "???")

			comment = ""
			if len(fields) > COMMENT:
				if (fields[COMMENT].startswith("[")):
					comment = " ".join(fields[COMMENT + 1:])
				else:
					comment = " ".join(fields[COMMENT:])


			bidi_entries.append(Entry(start, end, value, comment))


	bidi_entries.sort(key=lambda entry: entry.start)


	merge_ranges(bidi_entries)



	#
	# Process DerivedGeneralCategory.txt
	#

	NUM_DGC_COLS = 4
	DGC_RANGE = 0
	DGC_CAT = 2
	DGC_COMMENT = 4

	category_entries = []

	category_f = open("DerivedGeneralCategory.txt", 'r');


	for line in category_f:

		fields = line.split()

		if len(fields) > 0 and fields[0] == '#':
			continue

		if len(fields) > NUM_DGC_COLS:

			(start, end) = get_range(fields[DGC_RANGE])

			category = category_mapping.get(fields[DGC_CAT], "???")

			comment = ""
			if len(fields) > DGC_COMMENT:
				if (fields[DGC_COMMENT].startswith("[")):
					comment = " ".join(fields[DGC_COMMENT + 1:])
				else:
					comment = " ".join(fields[DGC_COMMENT:])


			category_entries.append(Entry(start, end, category, comment))



	category_entries.sort(key=lambda entry: entry.start)

	merge_ranges(category_entries)



	#
	# Process Scripts.txt
	#

	NUM_SCRIPTS_COLS = 4
	SCRIPTS_RANGE = 0
	SCRIPTS_SCRIPT= 2
	SCRIPTS_COMMENT = 5

	scripts_entries = []

	scripts_f = open("Scripts.txt", 'r');


	for line in scripts_f:

		fields = line.split()

		if len(fields) > 0 and fields[0] == '#':
			continue

		if len(fields) > NUM_SCRIPTS_COLS:

			(start, end) = get_range(fields[SCRIPTS_RANGE])

			script = fields[SCRIPTS_SCRIPT].replace("_", "")

			comment = ""
			if len(fields) > SCRIPTS_COMMENT:
				if (fields[SCRIPTS_COMMENT].startswith("[")):
					comment = " ".join(fields[SCRIPTS_COMMENT + 1:])
				else:
					comment = " ".join(fields[SCRIPTS_COMMENT:])

			scripts_entries.append(Entry(start, end, script, comment))

			#print(f" {{ 0x{start:X}, 0x{end:X}, {bidi_class} }},");


	scripts_entries.sort(key=lambda entry: entry.start)

	merge_ranges(scripts_entries)

	#print(scripts_entries)



	#
	# Process Blocks.txt
	#

	NUM_BLOCKS_COLS = 2
	BLOCKS_RANGE = 0
	BLOCKS_NAME = 1

	blocks_entries = []

	blocks_f = open("Blocks.txt", 'r');

	table = {ord(c): None for c in "_- \n"}

	for line in blocks_f:

		fields = line.split(';')

		if len(fields) > 0 and fields[0].startswith('#'):
			continue;

		if len(fields) >= NUM_BLOCKS_COLS:

			(start, end) = get_range(fields[BLOCKS_RANGE])

			comment = fields[BLOCKS_NAME].strip()
			block_name = fields[BLOCKS_NAME].translate(table)

			blocks_entries.append(Entry(start, end, block_name, comment))


	blocks_entries.sort(key = lambda entry: entry.value)

	merge_ranges(blocks_entries)

	print(blocks_entries)




	# Create scripts enum from scripts that have been found.
	script_names = {}

	for entry in scripts_entries:
		script_names[entry.value] = 1

	print("\tenum class Script")
	print("\t{")

	for key, value in sorted(script_names.items()):
		print("\t\t" + key + ", ")

	print("\t};")

	print()


	# Create blocks enum from blocks that have been found.
	blocks_names = {}

	for entry in blocks_entries:
		blocks_names[entry.value] = 1

	print("\tenum class Name")
	print("\t{")

	for key, value in sorted(blocks_names.items()):
		print("\t\t" + key + ", ")

	print("\t};")

	print()



	print("\tenum class BidiClass {")
	for c in sorted(bidi_classes):
		print("\t\t" + c + ",")
	print("\t};")

	print()

	print("\tenum class GeneralCategory")
	print("\t{")
	for c in sorted(general_category):
		print("\t\t" + c + ",")
	print("\t};")

	print()


	write_enum("BidiRanges", "Entry", "BidiClass", bidi_entries)

	write_enum("CategoryRanges", "Entry", "GeneralCategory", category_entries)

	write_enum("ScriptRanges", "Entry", "Script", scripts_entries)

	write_enum("BlockRanges", "Entry", "Name", blocks_entries)





	# Merge the three sets of data, splitting ranges where required.
	# category_entries
	# bidi_entries
	# scripts_entries 


	def get_bidi_default(cp):

		if 0x0590 >= cp >= 0x05FF:
		   return "RightToLeft"

		if 0x0600 >= cp >= 0x07BF:
			return "ArabicLetter"

		if 0x07C0 >= cp >= 0x085F:
			return "RightToLeft"

		if 0x0860 >= cp >= 0x08FF:
		   return "ArabicLetter"

		if 0x20A0 >= cp >= 0x20CF:
			return "EuropeanTerminator"

		if 0xFB1D >= cp >= 0xFB4F:
			return "RightToLeft"

		if 0xFB50 >= cp >= 0xFDCF:
			return "ArabicLetter"

		if 0xFDF0 >= cp >= 0xFDFF:
			return "ArabicLetter"

		if 0xFE70 >= cp >= 0xFEFF:
		   return "ArabicLetter"

		if 0x10800 >= cp >= 0x10CFF:
			return "RightToLeft";

		if 0x10D00 >= cp >= 0x10D3F:
			return "ArabicLetter";

		if 0x10D40 >= cp >= 0x10EBF:
			return "RightToLeft";

		if 0x10EC0 >= cp >= 0x10EFF:
			return "ArabicLetter";

		if 0x10F00 >= cp >= 0x10F2F:
			return "RightToLeft";

		if 0x10F30 >= cp >= 0x10F6F:
			return "ArabicLetter";

		if 0x10F70 >= cp >= 0x10FFF:
			return "RightToLeft";

		if 0x1E800 >= cp >= 0x1EC6F:
			return "RightToLeft";

		if 0x1EC70 >= cp >= 0x1ECBF:
			return "ArabicLetter";

		if 0x1ECC0 >= cp >= 0x1ECFF:
			return "RightToLeft";

		if 0x1ED00 >= cp >= 0x1ED4F:
			return "ArabicLetter";

		if 0x1ED50 >= cp >= 0x1EDFF:
			return "RightToLeft";

		if 0x1EE00 >= cp >= 0x1EEFF:
			return "ArabicLetter";

		if 0x1EF00 >= cp >= 0x1EFFF:
			return "RightToLeft";

		return "LeftToRight"


	def get_category_default(cp):
		return "Unassigned"


	def get_script_default(cp):
		return "Unknown"





except IOError as e:
	print('file open error:', e)

