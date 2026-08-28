// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cstdint>

module unicode.properties;

import std;

namespace unicode::properties
{
	// https://www.unicode.org/Public/UNIDATA/extracted/DerivedBidiClass.txt

	enum struct BidiClass
	{
		LeftToRight,
		RightToLeft,
		EuropeanNumber,
		EuropeanSeparator,
		EuropeanTerminator,
		ArabicNumber,
		CommonSeparator,
		ParagraphSeparator,
		SegmentSeparator,
		WhiteSpace,
		OtherNeutral,
		BoundaryNeutral,
		NonspacingMark,
		ArabicLetter,
		LeftToRightOverride,
		RightToLeftOverride,
		LeftToRightEmbedding,
		RightToLeftEmbedding,
		PopDirectionalFormat,
		LeftToRightIsolate,
		RightToLeftIsolate,
		FirstStrongIsolate,
		PopDirectionalIsolate,
	};

	enum struct GeneralCategory
	{
		UppercaseLetter,
		LowercaseLetter,
		TitlecaseLetter,
		CasedLetter,
		ModifierLetter,
		OtherLetter,
		Letter,
		NonspacingMark,
		SpacingMark,
		EnclosingMark,
		Mark,
		DecimalNumber,
		LetterNumber,
		OtherNumber,
		Number,
		ConnectorPunctuation,
		DashPunctuation,
		OpenPunctuation,
		ClosePunctuation,
		InitialPunctuation,
		FinalPunctuation,
		OtherPunctuation,
		Punctuation,
		MathSymbol,
		CurrencySymbol,
		ModifierSymbol,
		OtherSymbol,
		Symbol,
		SpaceSeparator,
		LineSeparator,
		ParagraphSeparator,
		Separator,
		Control,
		Format,
		Surrogate,
		PrivateUse,
		Unassigned,
		Other,
	};


	struct BidiRange
	{
		uint32_t		start{};
		uint32_t		end{};
		BidiClass		bidiClass{ BidiClass::LeftToRight };
		GeneralCategory	category{ GeneralCategory::Other };
	};

	static constexpr auto Ranges = std::to_array<BidiRange>(
	{
		{ 0x0000, 0x0008, BidiClass::BoundaryNeutral, GeneralCategory::Control },	// <control-0000>..<control-0008>
		{ 0x0009, 0x0009, BidiClass::SegmentSeparator, GeneralCategory::Control },	// <control-0009>
		{ 0x000A, 0x000A, BidiClass::ParagraphSeparator, GeneralCategory::Control },	// <control-000A>
		{ 0x000B, 0x000B, BidiClass::SegmentSeparator, GeneralCategory::Control },	// <control-000B>
		{ 0x000C, 0x000C, BidiClass::WhiteSpace, GeneralCategory::Control },	// <control-000C>
		{ 0x000D, 0x000D, BidiClass::ParagraphSeparator, GeneralCategory::Control },	// <control-000D>
		{ 0x000E, 0x001B, BidiClass::BoundaryNeutral, GeneralCategory::Control },	// <control-000E>..<control-001B>
		{ 0x001C, 0x001E, BidiClass::ParagraphSeparator, GeneralCategory::Control },	// <control-001C>..<control-001E>
		{ 0x001F, 0x001F, BidiClass::SegmentSeparator, GeneralCategory::Control },	// <control-001F>
		{ 0x0020, 0x0020, BidiClass::WhiteSpace, GeneralCategory::SpaceSeparator },	// SPACE
		{ 0x0021, 0x0022, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// EXCLAMATION MARK..QUOTATION MARK
		{ 0x0023, 0x0023, BidiClass::EuropeanTerminator, GeneralCategory::OtherPunctuation },	// NUMBER SIGN
		{ 0x0024, 0x0024, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// DOLLAR SIGN
		{ 0x0025, 0x0025, BidiClass::EuropeanTerminator, GeneralCategory::OtherPunctuation },	// PERCENT SIGN
		{ 0x0026, 0x0027, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// AMPERSAND..APOSTROPHE
		{ 0x0028, 0x0028, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT PARENTHESIS
		{ 0x0029, 0x0029, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT PARENTHESIS
		{ 0x002A, 0x002A, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// ASTERISK
		{ 0x002B, 0x002B, BidiClass::EuropeanSeparator, GeneralCategory::MathSymbol },	// PLUS SIGN
		{ 0x002C, 0x002C, BidiClass::CommonSeparator, GeneralCategory::OtherPunctuation },	// COMMA
		{ 0x002D, 0x002D, BidiClass::EuropeanSeparator, GeneralCategory::DashPunctuation },	// HYPHEN-MINUS
		{ 0x002E, 0x002F, BidiClass::CommonSeparator, GeneralCategory::OtherPunctuation },	// FULL STOP..SOLIDUS
		{ 0x0030, 0x0039, BidiClass::EuropeanNumber, GeneralCategory::DecimalNumber },	// DIGIT ZERO..DIGIT NINE
		{ 0x003A, 0x003A, BidiClass::CommonSeparator, GeneralCategory::OtherPunctuation },	// COLON
		{ 0x003B, 0x003B, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// SEMICOLON
		{ 0x003C, 0x003E, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// LESS-THAN SIGN..GREATER-THAN SIGN
		{ 0x003F, 0x0040, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// QUESTION MARK..COMMERCIAL AT
		{ 0x0041, 0x005A, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN CAPITAL LETTER A..LATIN CAPITAL LETTER Z
		{ 0x005B, 0x005B, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT SQUARE BRACKET
		{ 0x005C, 0x005C, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// REVERSE SOLIDUS
		{ 0x005D, 0x005D, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT SQUARE BRACKET
		{ 0x005E, 0x005E, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// CIRCUMFLEX ACCENT
		{ 0x005F, 0x005F, BidiClass::OtherNeutral, GeneralCategory::ConnectorPunctuation },	// LOW LINE
		{ 0x0060, 0x0060, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// GRAVE ACCENT
		{ 0x0061, 0x007A, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN SMALL LETTER A..LATIN SMALL LETTER Z
		{ 0x007B, 0x007B, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT CURLY BRACKET
		{ 0x007C, 0x007C, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// VERTICAL LINE
		{ 0x007D, 0x007D, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT CURLY BRACKET
		{ 0x007E, 0x007E, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// TILDE
		{ 0x007F, 0x0084, BidiClass::BoundaryNeutral, GeneralCategory::Control },	// <control-007F>..<control-0084>
		{ 0x0085, 0x0085, BidiClass::ParagraphSeparator, GeneralCategory::Control },	// <control-0085>
		{ 0x0086, 0x009F, BidiClass::BoundaryNeutral, GeneralCategory::Control },	// <control-0086>..<control-009F>
		{ 0x00A0, 0x00A0, BidiClass::CommonSeparator, GeneralCategory::SpaceSeparator },	// NO-BREAK SPACE
		{ 0x00A1, 0x00A1, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// INVERTED EXCLAMATION MARK
		{ 0x00A2, 0x00A5, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// CENT SIGN..YEN SIGN
		{ 0x00A6, 0x00A6, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// BROKEN BAR
		{ 0x00A7, 0x00A7, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// SECTION SIGN
		{ 0x00A8, 0x00A8, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// DIAERESIS
		{ 0x00A9, 0x00A9, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// COPYRIGHT SIGN
		{ 0x00AA, 0x00AA, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// FEMININE ORDINAL INDICATOR
		{ 0x00AB, 0x00AB, BidiClass::OtherNeutral, GeneralCategory::InitialPunctuation },	// LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
		{ 0x00AC, 0x00AC, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// NOT SIGN
		{ 0x00AD, 0x00AD, BidiClass::BoundaryNeutral, GeneralCategory::Format },	// SOFT HYPHEN
		{ 0x00AE, 0x00AE, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// REGISTERED SIGN
		{ 0x00AF, 0x00AF, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// MACRON
		{ 0x00B0, 0x00B0, BidiClass::EuropeanTerminator, GeneralCategory::OtherSymbol },	// DEGREE SIGN
		{ 0x00B1, 0x00B1, BidiClass::EuropeanTerminator, GeneralCategory::MathSymbol },	// PLUS-MINUS SIGN
		{ 0x00B2, 0x00B3, BidiClass::EuropeanNumber, GeneralCategory::OtherNumber },	// SUPERSCRIPT TWO..SUPERSCRIPT THREE
		{ 0x00B4, 0x00B4, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// ACUTE ACCENT
		{ 0x00B5, 0x00B5, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MICRO SIGN
		{ 0x00B6, 0x00B7, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// PILCROW SIGN..MIDDLE DOT
		{ 0x00B8, 0x00B8, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// CEDILLA
		{ 0x00B9, 0x00B9, BidiClass::EuropeanNumber, GeneralCategory::OtherNumber },	// SUPERSCRIPT ONE
		{ 0x00BA, 0x00BA, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MASCULINE ORDINAL INDICATOR
		{ 0x00BB, 0x00BB, BidiClass::OtherNeutral, GeneralCategory::FinalPunctuation },	// RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
		{ 0x00BC, 0x00BE, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// VULGAR FRACTION ONE QUARTER..VULGAR FRACTION THREE QUARTERS
		{ 0x00BF, 0x00BF, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// INVERTED QUESTION MARK
		{ 0x00C0, 0x00D6, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN CAPITAL LETTER A WITH GRAVE..LATIN CAPITAL LETTER O WITH DIAERESIS
		{ 0x00D7, 0x00D7, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// MULTIPLICATION SIGN
		{ 0x00D8, 0x00F6, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN CAPITAL LETTER O WITH STROKE..LATIN SMALL LETTER O WITH DIAERESIS
		{ 0x00F7, 0x00F7, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// DIVISION SIGN
		{ 0x00F8, 0x01BA, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN SMALL LETTER O WITH STROKE..LATIN SMALL LETTER EZH WITH TAIL
		{ 0x01BB, 0x01BB, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LATIN LETTER TWO WITH STROKE
		{ 0x01BC, 0x01BF, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN CAPITAL LETTER TONE FIVE..LATIN LETTER WYNN
		{ 0x01C0, 0x01C3, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LATIN LETTER DENTAL CLICK..LATIN LETTER RETROFLEX CLICK
		{ 0x01C4, 0x0293, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN CAPITAL LETTER DZ WITH CARON..LATIN SMALL LETTER EZH WITH CURL
		{ 0x0294, 0x0295, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LATIN LETTER GLOTTAL STOP..LATIN LETTER PHARYNGEAL VOICED FRICATIVE
		{ 0x0296, 0x02AF, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN LETTER INVERTED GLOTTAL STOP..LATIN SMALL LETTER TURNED H WITH FISHHOOK AND TAIL
		{ 0x02B0, 0x02B8, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER SMALL H..MODIFIER LETTER SMALL Y
		{ 0x02B9, 0x02BA, BidiClass::OtherNeutral, GeneralCategory::ModifierLetter },	// MODIFIER LETTER PRIME..MODIFIER LETTER DOUBLE PRIME
		{ 0x02BB, 0x02C1, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER TURNED COMMA..MODIFIER LETTER REVERSED GLOTTAL STOP
		{ 0x02C2, 0x02C5, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// MODIFIER LETTER LEFT ARROWHEAD..MODIFIER LETTER DOWN ARROWHEAD
		{ 0x02C6, 0x02CF, BidiClass::OtherNeutral, GeneralCategory::ModifierLetter },	// MODIFIER LETTER CIRCUMFLEX ACCENT..MODIFIER LETTER LOW ACUTE ACCENT
		{ 0x02D0, 0x02D1, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER TRIANGULAR COLON..MODIFIER LETTER HALF TRIANGULAR COLON
		{ 0x02D2, 0x02DF, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// MODIFIER LETTER CENTRED RIGHT HALF RING..MODIFIER LETTER CROSS ACCENT
		{ 0x02E0, 0x02E4, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER SMALL GAMMA..MODIFIER LETTER SMALL REVERSED GLOTTAL STOP
		{ 0x02E5, 0x02EB, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// MODIFIER LETTER EXTRA-HIGH TONE BAR..MODIFIER LETTER YANG DEPARTING TONE MARK
		{ 0x02EC, 0x02EC, BidiClass::OtherNeutral, GeneralCategory::ModifierLetter },	// MODIFIER LETTER VOICING
		{ 0x02ED, 0x02ED, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// MODIFIER LETTER UNASPIRATED
		{ 0x02EE, 0x02EE, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER DOUBLE APOSTROPHE
		{ 0x02EF, 0x02FF, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// MODIFIER LETTER LOW DOWN ARROWHEAD..MODIFIER LETTER LOW LEFT ARROW
		{ 0x0300, 0x036F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING GRAVE ACCENT..COMBINING LATIN SMALL LETTER X
		{ 0x0370, 0x0373, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER HETA..GREEK SMALL LETTER ARCHAIC SAMPI
		{ 0x0374, 0x0374, BidiClass::OtherNeutral, GeneralCategory::ModifierLetter },	// GREEK NUMERAL SIGN
		{ 0x0375, 0x0375, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// GREEK LOWER NUMERAL SIGN
		{ 0x0376, 0x0377, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER PAMPHYLIAN DIGAMMA..GREEK SMALL LETTER PAMPHYLIAN DIGAMMA
		{ 0x037A, 0x037A, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// GREEK YPOGEGRAMMENI
		{ 0x037B, 0x037D, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK SMALL REVERSED LUNATE SIGMA SYMBOL..GREEK SMALL REVERSED DOTTED LUNATE SIGMA SYMBOL
		{ 0x037E, 0x037E, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// GREEK QUESTION MARK
		{ 0x037F, 0x037F, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER YOT
		{ 0x0384, 0x0385, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// GREEK TONOS..GREEK DIALYTIKA TONOS
		{ 0x0386, 0x0386, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER ALPHA WITH TONOS
		{ 0x0387, 0x0387, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// GREEK ANO TELEIA
		{ 0x0388, 0x038A, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER EPSILON WITH TONOS..GREEK CAPITAL LETTER IOTA WITH TONOS
		{ 0x038C, 0x038C, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER OMICRON WITH TONOS
		{ 0x038E, 0x03A1, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER UPSILON WITH TONOS..GREEK CAPITAL LETTER RHO
		{ 0x03A3, 0x03F5, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER SIGMA..GREEK LUNATE EPSILON SYMBOL
		{ 0x03F6, 0x03F6, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// GREEK REVERSED LUNATE EPSILON SYMBOL
		{ 0x03F7, 0x0481, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER SHO..CYRILLIC SMALL LETTER KOPPA
		{ 0x0482, 0x0482, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// CYRILLIC THOUSANDS SIGN
		{ 0x0483, 0x0487, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING CYRILLIC TITLO..COMBINING CYRILLIC POKRYTIE
		{ 0x0488, 0x0489, BidiClass::NonspacingMark, GeneralCategory::EnclosingMark },	// COMBINING CYRILLIC HUNDRED THOUSANDS SIGN..COMBINING CYRILLIC MILLIONS SIGN
		{ 0x048A, 0x052F, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// CYRILLIC CAPITAL LETTER SHORT I WITH TAIL..CYRILLIC SMALL LETTER EL WITH DESCENDER
		{ 0x0531, 0x0556, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// ARMENIAN CAPITAL LETTER AYB..ARMENIAN CAPITAL LETTER FEH
		{ 0x0559, 0x0559, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// ARMENIAN MODIFIER LETTER LEFT HALF RING
		{ 0x055A, 0x055F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// ARMENIAN APOSTROPHE..ARMENIAN ABBREVIATION MARK
		{ 0x0560, 0x0588, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// ARMENIAN SMALL LETTER TURNED AYB..ARMENIAN SMALL LETTER YI WITH STROKE
		{ 0x0589, 0x0589, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// ARMENIAN FULL STOP
		{ 0x058A, 0x058A, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// ARMENIAN HYPHEN
		{ 0x058D, 0x058E, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// RIGHT-FACING ARMENIAN ETERNITY SIGN..LEFT-FACING ARMENIAN ETERNITY SIGN
		{ 0x058F, 0x058F, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// ARMENIAN DRAM SIGN
		{ 0x0591, 0x05BD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// HEBREW ACCENT ETNAHTA..HEBREW POINT METEG
		{ 0x05BE, 0x05BE, BidiClass::RightToLeft, GeneralCategory::DashPunctuation },	// HEBREW PUNCTUATION MAQAF
		{ 0x05BF, 0x05BF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// HEBREW POINT RAFE
		{ 0x05C0, 0x05C0, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// HEBREW PUNCTUATION PASEQ
		{ 0x05C1, 0x05C2, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// HEBREW POINT SHIN DOT..HEBREW POINT SIN DOT
		{ 0x05C3, 0x05C3, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// HEBREW PUNCTUATION SOF PASUQ
		{ 0x05C4, 0x05C5, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// HEBREW MARK UPPER DOT..HEBREW MARK LOWER DOT
		{ 0x05C6, 0x05C6, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// HEBREW PUNCTUATION NUN HAFUKHA
		{ 0x05C7, 0x05C7, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// HEBREW POINT QAMATS QATAN
		{ 0x05D0, 0x05EA, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// HEBREW LETTER ALEF..HEBREW LETTER TAV
		{ 0x05EF, 0x05F2, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// HEBREW YOD TRIANGLE..HEBREW LIGATURE YIDDISH DOUBLE YOD
		{ 0x05F3, 0x05F4, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// HEBREW PUNCTUATION GERESH..HEBREW PUNCTUATION GERSHAYIM
		{ 0x0600, 0x0605, BidiClass::ArabicNumber, GeneralCategory::Format },	// ARABIC NUMBER SIGN..ARABIC NUMBER MARK ABOVE
		{ 0x0606, 0x0607, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// ARABIC-INDIC CUBE ROOT..ARABIC-INDIC FOURTH ROOT
		{ 0x0608, 0x0608, BidiClass::ArabicLetter, GeneralCategory::MathSymbol },	// ARABIC RAY
		{ 0x0609, 0x060A, BidiClass::EuropeanTerminator, GeneralCategory::OtherPunctuation },	// ARABIC-INDIC PER MILLE SIGN..ARABIC-INDIC PER TEN THOUSAND SIGN
		{ 0x060B, 0x060B, BidiClass::ArabicLetter, GeneralCategory::CurrencySymbol },	// AFGHANI SIGN
		{ 0x060C, 0x060C, BidiClass::CommonSeparator, GeneralCategory::OtherPunctuation },	// ARABIC COMMA
		{ 0x060D, 0x060D, BidiClass::ArabicLetter, GeneralCategory::OtherPunctuation },	// ARABIC DATE SEPARATOR
		{ 0x060E, 0x060F, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ARABIC POETIC VERSE SIGN..ARABIC SIGN MISRA
		{ 0x0610, 0x061A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ARABIC SIGN SALLALLAHOU ALAYHE WASSALLAM..ARABIC SMALL KASRA
		{ 0x061B, 0x061B, BidiClass::ArabicLetter, GeneralCategory::OtherPunctuation },	// ARABIC SEMICOLON
		{ 0x061C, 0x061C, BidiClass::ArabicLetter, GeneralCategory::Format },	// ARABIC LETTER MARK
		{ 0x061D, 0x061F, BidiClass::ArabicLetter, GeneralCategory::OtherPunctuation },	// ARABIC END OF TEXT MARK..ARABIC QUESTION MARK
		{ 0x0620, 0x063F, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER KASHMIRI YEH..ARABIC LETTER FARSI YEH WITH THREE DOTS ABOVE
		{ 0x0640, 0x0640, BidiClass::ArabicLetter, GeneralCategory::ModifierLetter },	// ARABIC TATWEEL
		{ 0x0641, 0x064A, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER FEH..ARABIC LETTER YEH
		{ 0x064B, 0x065F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ARABIC FATHATAN..ARABIC WAVY HAMZA BELOW
		{ 0x0660, 0x0669, BidiClass::ArabicNumber, GeneralCategory::DecimalNumber },	// ARABIC-INDIC DIGIT ZERO..ARABIC-INDIC DIGIT NINE
		{ 0x066A, 0x066A, BidiClass::EuropeanTerminator, GeneralCategory::OtherPunctuation },	// ARABIC PERCENT SIGN
		{ 0x066B, 0x066C, BidiClass::ArabicNumber, GeneralCategory::OtherPunctuation },	// ARABIC DECIMAL SEPARATOR..ARABIC THOUSANDS SEPARATOR
		{ 0x066D, 0x066D, BidiClass::ArabicLetter, GeneralCategory::OtherPunctuation },	// ARABIC FIVE POINTED STAR
		{ 0x066E, 0x066F, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER DOTLESS BEH..ARABIC LETTER DOTLESS QAF
		{ 0x0670, 0x0670, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ARABIC LETTER SUPERSCRIPT ALEF
		{ 0x0671, 0x06D3, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER ALEF WASLA..ARABIC LETTER YEH BARREE WITH HAMZA ABOVE
		{ 0x06D4, 0x06D4, BidiClass::ArabicLetter, GeneralCategory::OtherPunctuation },	// ARABIC FULL STOP
		{ 0x06D5, 0x06D5, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER AE
		{ 0x06D6, 0x06DC, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ARABIC SMALL HIGH LIGATURE SAD WITH LAM WITH ALEF MAKSURA..ARABIC SMALL HIGH SEEN
		{ 0x06DD, 0x06DD, BidiClass::ArabicNumber, GeneralCategory::Format },	// ARABIC END OF AYAH
		{ 0x06DE, 0x06DE, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ARABIC START OF RUB EL HIZB
		{ 0x06DF, 0x06E4, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ARABIC SMALL HIGH ROUNDED ZERO..ARABIC SMALL HIGH MADDA
		{ 0x06E5, 0x06E6, BidiClass::ArabicLetter, GeneralCategory::ModifierLetter },	// ARABIC SMALL WAW..ARABIC SMALL YEH
		{ 0x06E7, 0x06E8, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ARABIC SMALL HIGH YEH..ARABIC SMALL HIGH NOON
		{ 0x06E9, 0x06E9, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ARABIC PLACE OF SAJDAH
		{ 0x06EA, 0x06ED, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ARABIC EMPTY CENTRE LOW STOP..ARABIC SMALL LOW MEEM
		{ 0x06EE, 0x06EF, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER DAL WITH INVERTED V..ARABIC LETTER REH WITH INVERTED V
		{ 0x06F0, 0x06F9, BidiClass::EuropeanNumber, GeneralCategory::DecimalNumber },	// EXTENDED ARABIC-INDIC DIGIT ZERO..EXTENDED ARABIC-INDIC DIGIT NINE
		{ 0x06FA, 0x06FC, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER SHEEN WITH DOT BELOW..ARABIC LETTER GHAIN WITH DOT BELOW
		{ 0x06FD, 0x06FE, BidiClass::ArabicLetter, GeneralCategory::OtherSymbol },	// ARABIC SIGN SINDHI AMPERSAND..ARABIC SIGN SINDHI POSTPOSITION MEN
		{ 0x06FF, 0x06FF, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER HEH WITH INVERTED V
		{ 0x0700, 0x070D, BidiClass::ArabicLetter, GeneralCategory::OtherPunctuation },	// SYRIAC END OF PARAGRAPH..SYRIAC HARKLEAN ASTERISCUS
		{ 0x070F, 0x070F, BidiClass::ArabicLetter, GeneralCategory::Format },	// SYRIAC ABBREVIATION MARK
		{ 0x0710, 0x0710, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// SYRIAC LETTER ALAPH
		{ 0x0711, 0x0711, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SYRIAC LETTER SUPERSCRIPT ALAPH
		{ 0x0712, 0x072F, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// SYRIAC LETTER BETH..SYRIAC LETTER PERSIAN DHALATH
		{ 0x0730, 0x074A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SYRIAC PTHAHA ABOVE..SYRIAC BARREKH
		{ 0x074D, 0x07A5, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// SYRIAC LETTER SOGDIAN ZHAIN..THAANA LETTER WAAVU
		{ 0x07A6, 0x07B0, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// THAANA ABAFILI..THAANA SUKUN
		{ 0x07B1, 0x07B1, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// THAANA LETTER NAA
		{ 0x07C0, 0x07C9, BidiClass::RightToLeft, GeneralCategory::DecimalNumber },	// NKO DIGIT ZERO..NKO DIGIT NINE
		{ 0x07CA, 0x07EA, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// NKO LETTER A..NKO LETTER JONA RA
		{ 0x07EB, 0x07F3, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// NKO COMBINING SHORT HIGH TONE..NKO COMBINING DOUBLE DOT ABOVE
		{ 0x07F4, 0x07F5, BidiClass::RightToLeft, GeneralCategory::ModifierLetter },	// NKO HIGH TONE APOSTROPHE..NKO LOW TONE APOSTROPHE
		{ 0x07F6, 0x07F6, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// NKO SYMBOL OO DENNEN
		{ 0x07F7, 0x07F9, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// NKO SYMBOL GBAKURUNEN..NKO EXCLAMATION MARK
		{ 0x07FA, 0x07FA, BidiClass::RightToLeft, GeneralCategory::ModifierLetter },	// NKO LAJANYALAN
		{ 0x07FD, 0x07FD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// NKO DANTAYALAN
		{ 0x07FE, 0x07FF, BidiClass::RightToLeft, GeneralCategory::CurrencySymbol },	// NKO DOROME SIGN..NKO TAMAN SIGN
		{ 0x0800, 0x0815, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// SAMARITAN LETTER ALAF..SAMARITAN LETTER TAAF
		{ 0x0816, 0x0819, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SAMARITAN MARK IN..SAMARITAN MARK DAGESH
		{ 0x081A, 0x081A, BidiClass::RightToLeft, GeneralCategory::ModifierLetter },	// SAMARITAN MODIFIER LETTER EPENTHETIC YUT
		{ 0x081B, 0x0823, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SAMARITAN MARK EPENTHETIC YUT..SAMARITAN VOWEL SIGN A
		{ 0x0824, 0x0824, BidiClass::RightToLeft, GeneralCategory::ModifierLetter },	// SAMARITAN MODIFIER LETTER SHORT A
		{ 0x0825, 0x0827, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SAMARITAN VOWEL SIGN SHORT A..SAMARITAN VOWEL SIGN U
		{ 0x0828, 0x0828, BidiClass::RightToLeft, GeneralCategory::ModifierLetter },	// SAMARITAN MODIFIER LETTER I
		{ 0x0829, 0x082D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SAMARITAN VOWEL SIGN LONG I..SAMARITAN MARK NEQUDAA
		{ 0x0830, 0x083E, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// SAMARITAN PUNCTUATION NEQUDAA..SAMARITAN PUNCTUATION ANNAAU
		{ 0x0840, 0x0858, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// MANDAIC LETTER HALQA..MANDAIC LETTER AIN
		{ 0x0859, 0x085B, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MANDAIC AFFRICATION MARK..MANDAIC GEMINATION MARK
		{ 0x085E, 0x085E, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// MANDAIC PUNCTUATION
		{ 0x0860, 0x086A, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// SYRIAC LETTER MALAYALAM NGA..SYRIAC LETTER MALAYALAM SSA
		{ 0x0870, 0x0887, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER ALEF WITH ATTACHED FATHA..ARABIC BASELINE ROUND DOT
		{ 0x0888, 0x0888, BidiClass::ArabicLetter, GeneralCategory::ModifierSymbol },	// ARABIC RAISED ROUND DOT
		{ 0x0889, 0x088F, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER NOON WITH INVERTED SMALL V..ARABIC LETTER NOON WITH RING ABOVE
		{ 0x0890, 0x0891, BidiClass::ArabicNumber, GeneralCategory::Format },	// ARABIC POUND MARK ABOVE..ARABIC PIASTRE MARK ABOVE
		{ 0x0897, 0x089F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ARABIC PEPET..ARABIC HALF MADDA OVER MADDA
		{ 0x08A0, 0x08C8, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER BEH WITH SMALL V BELOW..ARABIC LETTER GRAF
		{ 0x08C9, 0x08C9, BidiClass::ArabicLetter, GeneralCategory::ModifierLetter },	// ARABIC SMALL FARSI YEH
		{ 0x08CA, 0x08E1, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ARABIC SMALL HIGH FARSI YEH..ARABIC SMALL HIGH SIGN SAFHA
		{ 0x08E2, 0x08E2, BidiClass::ArabicNumber, GeneralCategory::Format },	// ARABIC DISPUTED END OF AYAH
		{ 0x08E3, 0x0902, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ARABIC TURNED DAMMA BELOW..DEVANAGARI SIGN ANUSVARA
		{ 0x0903, 0x0903, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// DEVANAGARI SIGN VISARGA
		{ 0x0904, 0x0939, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DEVANAGARI LETTER SHORT A..DEVANAGARI LETTER HA
		{ 0x093A, 0x093A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// DEVANAGARI VOWEL SIGN OE
		{ 0x093B, 0x093B, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// DEVANAGARI VOWEL SIGN OOE
		{ 0x093C, 0x093C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// DEVANAGARI SIGN NUKTA
		{ 0x093D, 0x093D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DEVANAGARI SIGN AVAGRAHA
		{ 0x093E, 0x0940, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// DEVANAGARI VOWEL SIGN AA..DEVANAGARI VOWEL SIGN II
		{ 0x0941, 0x0948, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// DEVANAGARI VOWEL SIGN U..DEVANAGARI VOWEL SIGN AI
		{ 0x0949, 0x094C, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// DEVANAGARI VOWEL SIGN CANDRA O..DEVANAGARI VOWEL SIGN AU
		{ 0x094D, 0x094D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// DEVANAGARI SIGN VIRAMA
		{ 0x094E, 0x094F, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// DEVANAGARI VOWEL SIGN PRISHTHAMATRA E..DEVANAGARI VOWEL SIGN AW
		{ 0x0950, 0x0950, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DEVANAGARI OM
		{ 0x0951, 0x0957, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// DEVANAGARI STRESS SIGN UDATTA..DEVANAGARI VOWEL SIGN UUE
		{ 0x0958, 0x0961, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DEVANAGARI LETTER QA..DEVANAGARI LETTER VOCALIC LL
		{ 0x0962, 0x0963, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// DEVANAGARI VOWEL SIGN VOCALIC L..DEVANAGARI VOWEL SIGN VOCALIC LL
		{ 0x0964, 0x0965, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// DEVANAGARI DANDA..DEVANAGARI DOUBLE DANDA
		{ 0x0966, 0x096F, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// DEVANAGARI DIGIT ZERO..DEVANAGARI DIGIT NINE
		{ 0x0970, 0x0970, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// DEVANAGARI ABBREVIATION SIGN
		{ 0x0971, 0x0971, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// DEVANAGARI SIGN HIGH SPACING DOT
		{ 0x0972, 0x0980, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DEVANAGARI LETTER CANDRA A..BENGALI ANJI
		{ 0x0981, 0x0981, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BENGALI SIGN CANDRABINDU
		{ 0x0982, 0x0983, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BENGALI SIGN ANUSVARA..BENGALI SIGN VISARGA
		{ 0x0985, 0x098C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BENGALI LETTER A..BENGALI LETTER VOCALIC L
		{ 0x098F, 0x0990, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BENGALI LETTER E..BENGALI LETTER AI
		{ 0x0993, 0x09A8, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BENGALI LETTER O..BENGALI LETTER NA
		{ 0x09AA, 0x09B0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BENGALI LETTER PA..BENGALI LETTER RA
		{ 0x09B2, 0x09B2, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BENGALI LETTER LA
		{ 0x09B6, 0x09B9, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BENGALI LETTER SHA..BENGALI LETTER HA
		{ 0x09BC, 0x09BC, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BENGALI SIGN NUKTA
		{ 0x09BD, 0x09BD, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BENGALI SIGN AVAGRAHA
		{ 0x09BE, 0x09C0, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BENGALI VOWEL SIGN AA..BENGALI VOWEL SIGN II
		{ 0x09C1, 0x09C4, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BENGALI VOWEL SIGN U..BENGALI VOWEL SIGN VOCALIC RR
		{ 0x09C7, 0x09C8, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BENGALI VOWEL SIGN E..BENGALI VOWEL SIGN AI
		{ 0x09CB, 0x09CC, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BENGALI VOWEL SIGN O..BENGALI VOWEL SIGN AU
		{ 0x09CD, 0x09CD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BENGALI SIGN VIRAMA
		{ 0x09CE, 0x09CE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BENGALI LETTER KHANDA TA
		{ 0x09D7, 0x09D7, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BENGALI AU LENGTH MARK
		{ 0x09DC, 0x09DD, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BENGALI LETTER RRA..BENGALI LETTER RHA
		{ 0x09DF, 0x09E1, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BENGALI LETTER YYA..BENGALI LETTER VOCALIC LL
		{ 0x09E2, 0x09E3, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BENGALI VOWEL SIGN VOCALIC L..BENGALI VOWEL SIGN VOCALIC LL
		{ 0x09E6, 0x09EF, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// BENGALI DIGIT ZERO..BENGALI DIGIT NINE
		{ 0x09F0, 0x09F1, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BENGALI LETTER RA WITH MIDDLE DIAGONAL..BENGALI LETTER RA WITH LOWER DIAGONAL
		{ 0x09F2, 0x09F3, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// BENGALI RUPEE MARK..BENGALI RUPEE SIGN
		{ 0x09F4, 0x09F9, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// BENGALI CURRENCY NUMERATOR ONE..BENGALI CURRENCY DENOMINATOR SIXTEEN
		{ 0x09FA, 0x09FA, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// BENGALI ISSHAR
		{ 0x09FB, 0x09FB, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// BENGALI GANDA MARK
		{ 0x09FC, 0x09FC, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BENGALI LETTER VEDIC ANUSVARA
		{ 0x09FD, 0x09FD, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// BENGALI ABBREVIATION SIGN
		{ 0x09FE, 0x09FE, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BENGALI SANDHI MARK
		{ 0x0A01, 0x0A02, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GURMUKHI SIGN ADAK BINDI..GURMUKHI SIGN BINDI
		{ 0x0A03, 0x0A03, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GURMUKHI SIGN VISARGA
		{ 0x0A05, 0x0A0A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GURMUKHI LETTER A..GURMUKHI LETTER UU
		{ 0x0A0F, 0x0A10, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GURMUKHI LETTER EE..GURMUKHI LETTER AI
		{ 0x0A13, 0x0A28, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GURMUKHI LETTER OO..GURMUKHI LETTER NA
		{ 0x0A2A, 0x0A30, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GURMUKHI LETTER PA..GURMUKHI LETTER RA
		{ 0x0A32, 0x0A33, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GURMUKHI LETTER LA..GURMUKHI LETTER LLA
		{ 0x0A35, 0x0A36, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GURMUKHI LETTER VA..GURMUKHI LETTER SHA
		{ 0x0A38, 0x0A39, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GURMUKHI LETTER SA..GURMUKHI LETTER HA
		{ 0x0A3C, 0x0A3C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GURMUKHI SIGN NUKTA
		{ 0x0A3E, 0x0A40, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GURMUKHI VOWEL SIGN AA..GURMUKHI VOWEL SIGN II
		{ 0x0A41, 0x0A42, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GURMUKHI VOWEL SIGN U..GURMUKHI VOWEL SIGN UU
		{ 0x0A47, 0x0A48, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GURMUKHI VOWEL SIGN EE..GURMUKHI VOWEL SIGN AI
		{ 0x0A4B, 0x0A4D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GURMUKHI VOWEL SIGN OO..GURMUKHI SIGN VIRAMA
		{ 0x0A51, 0x0A51, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GURMUKHI SIGN UDAAT
		{ 0x0A59, 0x0A5C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GURMUKHI LETTER KHHA..GURMUKHI LETTER RRA
		{ 0x0A5E, 0x0A5E, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GURMUKHI LETTER FA
		{ 0x0A66, 0x0A6F, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// GURMUKHI DIGIT ZERO..GURMUKHI DIGIT NINE
		{ 0x0A70, 0x0A71, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GURMUKHI TIPPI..GURMUKHI ADDAK
		{ 0x0A72, 0x0A74, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GURMUKHI IRI..GURMUKHI EK ONKAR
		{ 0x0A75, 0x0A75, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GURMUKHI SIGN YAKASH
		{ 0x0A76, 0x0A76, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// GURMUKHI ABBREVIATION SIGN
		{ 0x0A81, 0x0A82, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GUJARATI SIGN CANDRABINDU..GUJARATI SIGN ANUSVARA
		{ 0x0A83, 0x0A83, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GUJARATI SIGN VISARGA
		{ 0x0A85, 0x0A8D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUJARATI LETTER A..GUJARATI VOWEL CANDRA E
		{ 0x0A8F, 0x0A91, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUJARATI LETTER E..GUJARATI VOWEL CANDRA O
		{ 0x0A93, 0x0AA8, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUJARATI LETTER O..GUJARATI LETTER NA
		{ 0x0AAA, 0x0AB0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUJARATI LETTER PA..GUJARATI LETTER RA
		{ 0x0AB2, 0x0AB3, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUJARATI LETTER LA..GUJARATI LETTER LLA
		{ 0x0AB5, 0x0AB9, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUJARATI LETTER VA..GUJARATI LETTER HA
		{ 0x0ABC, 0x0ABC, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GUJARATI SIGN NUKTA
		{ 0x0ABD, 0x0ABD, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUJARATI SIGN AVAGRAHA
		{ 0x0ABE, 0x0AC0, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GUJARATI VOWEL SIGN AA..GUJARATI VOWEL SIGN II
		{ 0x0AC1, 0x0AC5, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GUJARATI VOWEL SIGN U..GUJARATI VOWEL SIGN CANDRA E
		{ 0x0AC7, 0x0AC8, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GUJARATI VOWEL SIGN E..GUJARATI VOWEL SIGN AI
		{ 0x0AC9, 0x0AC9, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GUJARATI VOWEL SIGN CANDRA O
		{ 0x0ACB, 0x0ACC, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GUJARATI VOWEL SIGN O..GUJARATI VOWEL SIGN AU
		{ 0x0ACD, 0x0ACD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GUJARATI SIGN VIRAMA
		{ 0x0AD0, 0x0AD0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUJARATI OM
		{ 0x0AE0, 0x0AE1, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUJARATI LETTER VOCALIC RR..GUJARATI LETTER VOCALIC LL
		{ 0x0AE2, 0x0AE3, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GUJARATI VOWEL SIGN VOCALIC L..GUJARATI VOWEL SIGN VOCALIC LL
		{ 0x0AE6, 0x0AEF, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// GUJARATI DIGIT ZERO..GUJARATI DIGIT NINE
		{ 0x0AF0, 0x0AF0, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// GUJARATI ABBREVIATION SIGN
		{ 0x0AF1, 0x0AF1, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// GUJARATI RUPEE SIGN
		{ 0x0AF9, 0x0AF9, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUJARATI LETTER ZHA
		{ 0x0AFA, 0x0AFF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GUJARATI SIGN SUKUN..GUJARATI SIGN TWO-CIRCLE NUKTA ABOVE
		{ 0x0B01, 0x0B01, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ORIYA SIGN CANDRABINDU
		{ 0x0B02, 0x0B03, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// ORIYA SIGN ANUSVARA..ORIYA SIGN VISARGA
		{ 0x0B05, 0x0B0C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ORIYA LETTER A..ORIYA LETTER VOCALIC L
		{ 0x0B0F, 0x0B10, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ORIYA LETTER E..ORIYA LETTER AI
		{ 0x0B13, 0x0B28, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ORIYA LETTER O..ORIYA LETTER NA
		{ 0x0B2A, 0x0B30, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ORIYA LETTER PA..ORIYA LETTER RA
		{ 0x0B32, 0x0B33, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ORIYA LETTER LA..ORIYA LETTER LLA
		{ 0x0B35, 0x0B39, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ORIYA LETTER VA..ORIYA LETTER HA
		{ 0x0B3C, 0x0B3C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ORIYA SIGN NUKTA
		{ 0x0B3D, 0x0B3D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ORIYA SIGN AVAGRAHA
		{ 0x0B3E, 0x0B3E, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// ORIYA VOWEL SIGN AA
		{ 0x0B3F, 0x0B3F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ORIYA VOWEL SIGN I
		{ 0x0B40, 0x0B40, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// ORIYA VOWEL SIGN II
		{ 0x0B41, 0x0B44, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ORIYA VOWEL SIGN U..ORIYA VOWEL SIGN VOCALIC RR
		{ 0x0B47, 0x0B48, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// ORIYA VOWEL SIGN E..ORIYA VOWEL SIGN AI
		{ 0x0B4B, 0x0B4C, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// ORIYA VOWEL SIGN O..ORIYA VOWEL SIGN AU
		{ 0x0B4D, 0x0B4D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ORIYA SIGN VIRAMA
		{ 0x0B55, 0x0B56, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ORIYA SIGN OVERLINE..ORIYA AI LENGTH MARK
		{ 0x0B57, 0x0B57, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// ORIYA AU LENGTH MARK
		{ 0x0B5C, 0x0B5D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ORIYA LETTER RRA..ORIYA LETTER RHA
		{ 0x0B5F, 0x0B61, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ORIYA LETTER YYA..ORIYA LETTER VOCALIC LL
		{ 0x0B62, 0x0B63, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ORIYA VOWEL SIGN VOCALIC L..ORIYA VOWEL SIGN VOCALIC LL
		{ 0x0B66, 0x0B6F, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// ORIYA DIGIT ZERO..ORIYA DIGIT NINE
		{ 0x0B70, 0x0B70, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// ORIYA ISSHAR
		{ 0x0B71, 0x0B71, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ORIYA LETTER WA
		{ 0x0B72, 0x0B77, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// ORIYA FRACTION ONE QUARTER..ORIYA FRACTION THREE SIXTEENTHS
		{ 0x0B82, 0x0B82, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAMIL SIGN ANUSVARA
		{ 0x0B83, 0x0B83, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAMIL SIGN VISARGA
		{ 0x0B85, 0x0B8A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAMIL LETTER A..TAMIL LETTER UU
		{ 0x0B8E, 0x0B90, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAMIL LETTER E..TAMIL LETTER AI
		{ 0x0B92, 0x0B95, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAMIL LETTER O..TAMIL LETTER KA
		{ 0x0B99, 0x0B9A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAMIL LETTER NGA..TAMIL LETTER CA
		{ 0x0B9C, 0x0B9C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAMIL LETTER JA
		{ 0x0B9E, 0x0B9F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAMIL LETTER NYA..TAMIL LETTER TTA
		{ 0x0BA3, 0x0BA4, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAMIL LETTER NNA..TAMIL LETTER TA
		{ 0x0BA8, 0x0BAA, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAMIL LETTER NA..TAMIL LETTER PA
		{ 0x0BAE, 0x0BB9, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAMIL LETTER MA..TAMIL LETTER HA
		{ 0x0BBE, 0x0BBF, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAMIL VOWEL SIGN AA..TAMIL VOWEL SIGN I
		{ 0x0BC0, 0x0BC0, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAMIL VOWEL SIGN II
		{ 0x0BC1, 0x0BC2, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAMIL VOWEL SIGN U..TAMIL VOWEL SIGN UU
		{ 0x0BC6, 0x0BC8, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAMIL VOWEL SIGN E..TAMIL VOWEL SIGN AI
		{ 0x0BCA, 0x0BCC, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAMIL VOWEL SIGN O..TAMIL VOWEL SIGN AU
		{ 0x0BCD, 0x0BCD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAMIL SIGN VIRAMA
		{ 0x0BD0, 0x0BD0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAMIL OM
		{ 0x0BD7, 0x0BD7, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAMIL AU LENGTH MARK
		{ 0x0BE6, 0x0BEF, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// TAMIL DIGIT ZERO..TAMIL DIGIT NINE
		{ 0x0BF0, 0x0BF2, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// TAMIL NUMBER TEN..TAMIL NUMBER ONE THOUSAND
		{ 0x0BF3, 0x0BF8, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// TAMIL DAY SIGN..TAMIL AS ABOVE SIGN
		{ 0x0BF9, 0x0BF9, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// TAMIL RUPEE SIGN
		{ 0x0BFA, 0x0BFA, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// TAMIL NUMBER SIGN
		{ 0x0C00, 0x0C00, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TELUGU SIGN COMBINING CANDRABINDU ABOVE
		{ 0x0C01, 0x0C03, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TELUGU SIGN CANDRABINDU..TELUGU SIGN VISARGA
		{ 0x0C04, 0x0C04, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TELUGU SIGN COMBINING ANUSVARA ABOVE
		{ 0x0C05, 0x0C0C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TELUGU LETTER A..TELUGU LETTER VOCALIC L
		{ 0x0C0E, 0x0C10, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TELUGU LETTER E..TELUGU LETTER AI
		{ 0x0C12, 0x0C28, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TELUGU LETTER O..TELUGU LETTER NA
		{ 0x0C2A, 0x0C39, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TELUGU LETTER PA..TELUGU LETTER HA
		{ 0x0C3C, 0x0C3C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TELUGU SIGN NUKTA
		{ 0x0C3D, 0x0C3D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TELUGU SIGN AVAGRAHA
		{ 0x0C3E, 0x0C40, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TELUGU VOWEL SIGN AA..TELUGU VOWEL SIGN II
		{ 0x0C41, 0x0C44, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TELUGU VOWEL SIGN U..TELUGU VOWEL SIGN VOCALIC RR
		{ 0x0C46, 0x0C48, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TELUGU VOWEL SIGN E..TELUGU VOWEL SIGN AI
		{ 0x0C4A, 0x0C4D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TELUGU VOWEL SIGN O..TELUGU SIGN VIRAMA
		{ 0x0C55, 0x0C56, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TELUGU LENGTH MARK..TELUGU AI LENGTH MARK
		{ 0x0C58, 0x0C5A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TELUGU LETTER TSA..TELUGU LETTER RRRA
		{ 0x0C5C, 0x0C5D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TELUGU ARCHAIC SHRII..TELUGU LETTER NAKAARA POLLU
		{ 0x0C60, 0x0C61, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TELUGU LETTER VOCALIC RR..TELUGU LETTER VOCALIC LL
		{ 0x0C62, 0x0C63, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TELUGU VOWEL SIGN VOCALIC L..TELUGU VOWEL SIGN VOCALIC LL
		{ 0x0C66, 0x0C6F, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// TELUGU DIGIT ZERO..TELUGU DIGIT NINE
		{ 0x0C77, 0x0C77, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TELUGU SIGN SIDDHAM
		{ 0x0C78, 0x0C7E, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// TELUGU FRACTION DIGIT ZERO FOR ODD POWERS OF FOUR..TELUGU FRACTION DIGIT THREE FOR EVEN POWERS OF FOUR
		{ 0x0C7F, 0x0C7F, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// TELUGU SIGN TUUMU
		{ 0x0C80, 0x0C80, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KANNADA SIGN SPACING CANDRABINDU
		{ 0x0C81, 0x0C81, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KANNADA SIGN CANDRABINDU
		{ 0x0C82, 0x0C83, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KANNADA SIGN ANUSVARA..KANNADA SIGN VISARGA
		{ 0x0C84, 0x0C84, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// KANNADA SIGN SIDDHAM
		{ 0x0C85, 0x0C8C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KANNADA LETTER A..KANNADA LETTER VOCALIC L
		{ 0x0C8E, 0x0C90, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KANNADA LETTER E..KANNADA LETTER AI
		{ 0x0C92, 0x0CA8, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KANNADA LETTER O..KANNADA LETTER NA
		{ 0x0CAA, 0x0CB3, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KANNADA LETTER PA..KANNADA LETTER LLA
		{ 0x0CB5, 0x0CB9, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KANNADA LETTER VA..KANNADA LETTER HA
		{ 0x0CBC, 0x0CBC, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KANNADA SIGN NUKTA
		{ 0x0CBD, 0x0CBD, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KANNADA SIGN AVAGRAHA
		{ 0x0CBE, 0x0CBE, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KANNADA VOWEL SIGN AA
		{ 0x0CBF, 0x0CBF, BidiClass::LeftToRight, GeneralCategory::NonspacingMark },	// KANNADA VOWEL SIGN I
		{ 0x0CC0, 0x0CC4, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KANNADA VOWEL SIGN II..KANNADA VOWEL SIGN VOCALIC RR
		{ 0x0CC6, 0x0CC6, BidiClass::LeftToRight, GeneralCategory::NonspacingMark },	// KANNADA VOWEL SIGN E
		{ 0x0CC7, 0x0CC8, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KANNADA VOWEL SIGN EE..KANNADA VOWEL SIGN AI
		{ 0x0CCA, 0x0CCB, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KANNADA VOWEL SIGN O..KANNADA VOWEL SIGN OO
		{ 0x0CCC, 0x0CCD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KANNADA VOWEL SIGN AU..KANNADA SIGN VIRAMA
		{ 0x0CD5, 0x0CD6, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KANNADA LENGTH MARK..KANNADA AI LENGTH MARK
		{ 0x0CDC, 0x0CDE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KANNADA ARCHAIC SHRII..KANNADA LETTER FA
		{ 0x0CE0, 0x0CE1, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KANNADA LETTER VOCALIC RR..KANNADA LETTER VOCALIC LL
		{ 0x0CE2, 0x0CE3, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KANNADA VOWEL SIGN VOCALIC L..KANNADA VOWEL SIGN VOCALIC LL
		{ 0x0CE6, 0x0CEF, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// KANNADA DIGIT ZERO..KANNADA DIGIT NINE
		{ 0x0CF1, 0x0CF2, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KANNADA SIGN JIHVAMULIYA..KANNADA SIGN UPADHMANIYA
		{ 0x0CF3, 0x0CF3, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KANNADA SIGN COMBINING ANUSVARA ABOVE RIGHT
		{ 0x0D00, 0x0D01, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MALAYALAM SIGN COMBINING ANUSVARA ABOVE..MALAYALAM SIGN CANDRABINDU
		{ 0x0D02, 0x0D03, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MALAYALAM SIGN ANUSVARA..MALAYALAM SIGN VISARGA
		{ 0x0D04, 0x0D0C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MALAYALAM LETTER VEDIC ANUSVARA..MALAYALAM LETTER VOCALIC L
		{ 0x0D0E, 0x0D10, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MALAYALAM LETTER E..MALAYALAM LETTER AI
		{ 0x0D12, 0x0D3A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MALAYALAM LETTER O..MALAYALAM LETTER TTTA
		{ 0x0D3B, 0x0D3C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MALAYALAM SIGN VERTICAL BAR VIRAMA..MALAYALAM SIGN CIRCULAR VIRAMA
		{ 0x0D3D, 0x0D3D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MALAYALAM SIGN AVAGRAHA
		{ 0x0D3E, 0x0D40, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MALAYALAM VOWEL SIGN AA..MALAYALAM VOWEL SIGN II
		{ 0x0D41, 0x0D44, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MALAYALAM VOWEL SIGN U..MALAYALAM VOWEL SIGN VOCALIC RR
		{ 0x0D46, 0x0D48, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MALAYALAM VOWEL SIGN E..MALAYALAM VOWEL SIGN AI
		{ 0x0D4A, 0x0D4C, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MALAYALAM VOWEL SIGN O..MALAYALAM VOWEL SIGN AU
		{ 0x0D4D, 0x0D4D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MALAYALAM SIGN VIRAMA
		{ 0x0D4E, 0x0D4E, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MALAYALAM LETTER DOT REPH
		{ 0x0D4F, 0x0D4F, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// MALAYALAM SIGN PARA
		{ 0x0D54, 0x0D56, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MALAYALAM LETTER CHILLU M..MALAYALAM LETTER CHILLU LLL
		{ 0x0D57, 0x0D57, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MALAYALAM AU LENGTH MARK
		{ 0x0D58, 0x0D5E, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// MALAYALAM FRACTION ONE ONE-HUNDRED-AND-SIXTIETH..MALAYALAM FRACTION ONE FIFTH
		{ 0x0D5F, 0x0D61, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MALAYALAM LETTER ARCHAIC II..MALAYALAM LETTER VOCALIC LL
		{ 0x0D62, 0x0D63, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MALAYALAM VOWEL SIGN VOCALIC L..MALAYALAM VOWEL SIGN VOCALIC LL
		{ 0x0D66, 0x0D6F, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// MALAYALAM DIGIT ZERO..MALAYALAM DIGIT NINE
		{ 0x0D70, 0x0D78, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// MALAYALAM NUMBER TEN..MALAYALAM FRACTION THREE SIXTEENTHS
		{ 0x0D79, 0x0D79, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// MALAYALAM DATE MARK
		{ 0x0D7A, 0x0D7F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MALAYALAM LETTER CHILLU NN..MALAYALAM LETTER CHILLU K
		{ 0x0D81, 0x0D81, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SINHALA SIGN CANDRABINDU
		{ 0x0D82, 0x0D83, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SINHALA SIGN ANUSVARAYA..SINHALA SIGN VISARGAYA
		{ 0x0D85, 0x0D96, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SINHALA LETTER AYANNA..SINHALA LETTER AUYANNA
		{ 0x0D9A, 0x0DB1, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SINHALA LETTER ALPAPRAANA KAYANNA..SINHALA LETTER DANTAJA NAYANNA
		{ 0x0DB3, 0x0DBB, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SINHALA LETTER SANYAKA DAYANNA..SINHALA LETTER RAYANNA
		{ 0x0DBD, 0x0DBD, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SINHALA LETTER DANTAJA LAYANNA
		{ 0x0DC0, 0x0DC6, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SINHALA LETTER VAYANNA..SINHALA LETTER FAYANNA
		{ 0x0DCA, 0x0DCA, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SINHALA SIGN AL-LAKUNA
		{ 0x0DCF, 0x0DD1, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SINHALA VOWEL SIGN AELA-PILLA..SINHALA VOWEL SIGN DIGA AEDA-PILLA
		{ 0x0DD2, 0x0DD4, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SINHALA VOWEL SIGN KETTI IS-PILLA..SINHALA VOWEL SIGN KETTI PAA-PILLA
		{ 0x0DD6, 0x0DD6, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SINHALA VOWEL SIGN DIGA PAA-PILLA
		{ 0x0DD8, 0x0DDF, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SINHALA VOWEL SIGN GAETTA-PILLA..SINHALA VOWEL SIGN GAYANUKITTA
		{ 0x0DE6, 0x0DEF, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// SINHALA LITH DIGIT ZERO..SINHALA LITH DIGIT NINE
		{ 0x0DF2, 0x0DF3, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SINHALA VOWEL SIGN DIGA GAETTA-PILLA..SINHALA VOWEL SIGN DIGA GAYANUKITTA
		{ 0x0DF4, 0x0DF4, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// SINHALA PUNCTUATION KUNDDALIYA
		{ 0x0E01, 0x0E30, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// THAI CHARACTER KO KAI..THAI CHARACTER SARA A
		{ 0x0E31, 0x0E31, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// THAI CHARACTER MAI HAN-AKAT
		{ 0x0E32, 0x0E33, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// THAI CHARACTER SARA AA..THAI CHARACTER SARA AM
		{ 0x0E34, 0x0E3A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// THAI CHARACTER SARA I..THAI CHARACTER PHINTHU
		{ 0x0E3F, 0x0E3F, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// THAI CURRENCY SYMBOL BAHT
		{ 0x0E40, 0x0E45, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// THAI CHARACTER SARA E..THAI CHARACTER LAKKHANGYAO
		{ 0x0E46, 0x0E46, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// THAI CHARACTER MAIYAMOK
		{ 0x0E47, 0x0E4E, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// THAI CHARACTER MAITAIKHU..THAI CHARACTER YAMAKKAN
		{ 0x0E4F, 0x0E4F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// THAI CHARACTER FONGMAN
		{ 0x0E50, 0x0E59, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// THAI DIGIT ZERO..THAI DIGIT NINE
		{ 0x0E5A, 0x0E5B, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// THAI CHARACTER ANGKHANKHU..THAI CHARACTER KHOMUT
		{ 0x0E81, 0x0E82, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LAO LETTER KO..LAO LETTER KHO SUNG
		{ 0x0E84, 0x0E84, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LAO LETTER KHO TAM
		{ 0x0E86, 0x0E8A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LAO LETTER PALI GHA..LAO LETTER SO TAM
		{ 0x0E8C, 0x0EA3, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LAO LETTER PALI JHA..LAO LETTER LO LING
		{ 0x0EA5, 0x0EA5, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LAO LETTER LO LOOT
		{ 0x0EA7, 0x0EB0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LAO LETTER WO..LAO VOWEL SIGN A
		{ 0x0EB1, 0x0EB1, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// LAO VOWEL SIGN MAI KAN
		{ 0x0EB2, 0x0EB3, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LAO VOWEL SIGN AA..LAO VOWEL SIGN AM
		{ 0x0EB4, 0x0EBC, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// LAO VOWEL SIGN I..LAO SEMIVOWEL SIGN LO
		{ 0x0EBD, 0x0EBD, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LAO SEMIVOWEL SIGN NYO
		{ 0x0EC0, 0x0EC4, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LAO VOWEL SIGN E..LAO VOWEL SIGN AI
		{ 0x0EC6, 0x0EC6, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// LAO KO LA
		{ 0x0EC8, 0x0ECE, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// LAO TONE MAI EK..LAO YAMAKKAN
		{ 0x0ED0, 0x0ED9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// LAO DIGIT ZERO..LAO DIGIT NINE
		{ 0x0EDC, 0x0EDF, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LAO HO NO..LAO LETTER KHMU NYO
		{ 0x0F00, 0x0F00, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TIBETAN SYLLABLE OM
		{ 0x0F01, 0x0F03, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// TIBETAN MARK GTER YIG MGO TRUNCATED A..TIBETAN MARK GTER YIG MGO -UM GTER TSHEG MA
		{ 0x0F04, 0x0F12, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TIBETAN MARK INITIAL YIG MGO MDUN MA..TIBETAN MARK RGYA GRAM SHAD
		{ 0x0F13, 0x0F13, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// TIBETAN MARK CARET -DZUD RTAGS ME LONG CAN
		{ 0x0F14, 0x0F14, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TIBETAN MARK GTER TSHEG
		{ 0x0F15, 0x0F17, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// TIBETAN LOGOTYPE SIGN CHAD RTAGS..TIBETAN ASTROLOGICAL SIGN SGRA GCAN -CHAR RTAGS
		{ 0x0F18, 0x0F19, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIBETAN ASTROLOGICAL SIGN -KHYUD PA..TIBETAN ASTROLOGICAL SIGN SDONG TSHUGS
		{ 0x0F1A, 0x0F1F, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// TIBETAN SIGN RDEL DKAR GCIG..TIBETAN SIGN RDEL DKAR RDEL NAG
		{ 0x0F20, 0x0F29, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// TIBETAN DIGIT ZERO..TIBETAN DIGIT NINE
		{ 0x0F2A, 0x0F33, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// TIBETAN DIGIT HALF ONE..TIBETAN DIGIT HALF ZERO
		{ 0x0F34, 0x0F34, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// TIBETAN MARK BSDUS RTAGS
		{ 0x0F35, 0x0F35, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIBETAN MARK NGAS BZUNG NYI ZLA
		{ 0x0F36, 0x0F36, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// TIBETAN MARK CARET -DZUD RTAGS BZHI MIG CAN
		{ 0x0F37, 0x0F37, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIBETAN MARK NGAS BZUNG SGOR RTAGS
		{ 0x0F38, 0x0F38, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// TIBETAN MARK CHE MGO
		{ 0x0F39, 0x0F39, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIBETAN MARK TSA -PHRU
		{ 0x0F3A, 0x0F3A, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// TIBETAN MARK GUG RTAGS GYON
		{ 0x0F3B, 0x0F3B, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// TIBETAN MARK GUG RTAGS GYAS
		{ 0x0F3C, 0x0F3C, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// TIBETAN MARK ANG KHANG GYON
		{ 0x0F3D, 0x0F3D, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// TIBETAN MARK ANG KHANG GYAS
		{ 0x0F3E, 0x0F3F, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TIBETAN SIGN YAR TSHES..TIBETAN SIGN MAR TSHES
		{ 0x0F40, 0x0F47, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TIBETAN LETTER KA..TIBETAN LETTER JA
		{ 0x0F49, 0x0F6C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TIBETAN LETTER NYA..TIBETAN LETTER RRA
		{ 0x0F71, 0x0F7E, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIBETAN VOWEL SIGN AA..TIBETAN SIGN RJES SU NGA RO
		{ 0x0F7F, 0x0F7F, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TIBETAN SIGN RNAM BCAD
		{ 0x0F80, 0x0F84, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIBETAN VOWEL SIGN REVERSED I..TIBETAN MARK HALANTA
		{ 0x0F85, 0x0F85, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TIBETAN MARK PALUTA
		{ 0x0F86, 0x0F87, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIBETAN SIGN LCI RTAGS..TIBETAN SIGN YANG RTAGS
		{ 0x0F88, 0x0F8C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TIBETAN SIGN LCE TSA CAN..TIBETAN SIGN INVERTED MCHU CAN
		{ 0x0F8D, 0x0F97, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIBETAN SUBJOINED SIGN LCE TSA CAN..TIBETAN SUBJOINED LETTER JA
		{ 0x0F99, 0x0FBC, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIBETAN SUBJOINED LETTER NYA..TIBETAN SUBJOINED LETTER FIXED-FORM RA
		{ 0x0FBE, 0x0FC5, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// TIBETAN KU RU KHA..TIBETAN SYMBOL RDO RJE
		{ 0x0FC6, 0x0FC6, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIBETAN SYMBOL PADMA GDAN
		{ 0x0FC7, 0x0FCC, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// TIBETAN SYMBOL RDO RJE RGYA GRAM..TIBETAN SYMBOL NOR BU BZHI -KHYIL
		{ 0x0FCE, 0x0FCF, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// TIBETAN SIGN RDEL NAG RDEL DKAR..TIBETAN SIGN RDEL NAG GSUM
		{ 0x0FD0, 0x0FD4, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TIBETAN MARK BSKA- SHOG GI MGO RGYAN..TIBETAN MARK CLOSING BRDA RNYING YIG MGO SGAB MA
		{ 0x0FD5, 0x0FD8, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// RIGHT-FACING SVASTI SIGN..LEFT-FACING SVASTI SIGN WITH DOTS
		{ 0x0FD9, 0x0FDA, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TIBETAN MARK LEADING MCHAN RTAGS..TIBETAN MARK TRAILING MCHAN RTAGS
		{ 0x1000, 0x102A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER KA..MYANMAR LETTER AU
		{ 0x102B, 0x102C, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MYANMAR VOWEL SIGN TALL AA..MYANMAR VOWEL SIGN AA
		{ 0x102D, 0x1030, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MYANMAR VOWEL SIGN I..MYANMAR VOWEL SIGN UU
		{ 0x1031, 0x1031, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MYANMAR VOWEL SIGN E
		{ 0x1032, 0x1037, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MYANMAR VOWEL SIGN AI..MYANMAR SIGN DOT BELOW
		{ 0x1038, 0x1038, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MYANMAR SIGN VISARGA
		{ 0x1039, 0x103A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MYANMAR SIGN VIRAMA..MYANMAR SIGN ASAT
		{ 0x103B, 0x103C, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MYANMAR CONSONANT SIGN MEDIAL YA..MYANMAR CONSONANT SIGN MEDIAL RA
		{ 0x103D, 0x103E, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MYANMAR CONSONANT SIGN MEDIAL WA..MYANMAR CONSONANT SIGN MEDIAL HA
		{ 0x103F, 0x103F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER GREAT SA
		{ 0x1040, 0x1049, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// MYANMAR DIGIT ZERO..MYANMAR DIGIT NINE
		{ 0x104A, 0x104F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// MYANMAR SIGN LITTLE SECTION..MYANMAR SYMBOL GENITIVE
		{ 0x1050, 0x1055, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER SHA..MYANMAR LETTER VOCALIC LL
		{ 0x1056, 0x1057, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MYANMAR VOWEL SIGN VOCALIC R..MYANMAR VOWEL SIGN VOCALIC RR
		{ 0x1058, 0x1059, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MYANMAR VOWEL SIGN VOCALIC L..MYANMAR VOWEL SIGN VOCALIC LL
		{ 0x105A, 0x105D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER MON NGA..MYANMAR LETTER MON BBE
		{ 0x105E, 0x1060, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MYANMAR CONSONANT SIGN MON MEDIAL NA..MYANMAR CONSONANT SIGN MON MEDIAL LA
		{ 0x1061, 0x1061, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER SGAW KAREN SHA
		{ 0x1062, 0x1064, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MYANMAR VOWEL SIGN SGAW KAREN EU..MYANMAR TONE MARK SGAW KAREN KE PHO
		{ 0x1065, 0x1066, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER WESTERN PWO KAREN THA..MYANMAR LETTER WESTERN PWO KAREN PWA
		{ 0x1067, 0x106D, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MYANMAR VOWEL SIGN WESTERN PWO KAREN EU..MYANMAR SIGN WESTERN PWO KAREN TONE-5
		{ 0x106E, 0x1070, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER EASTERN PWO KAREN NNA..MYANMAR LETTER EASTERN PWO KAREN GHWA
		{ 0x1071, 0x1074, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MYANMAR VOWEL SIGN GEBA KAREN I..MYANMAR VOWEL SIGN KAYAH EE
		{ 0x1075, 0x1081, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER SHAN KA..MYANMAR LETTER SHAN HA
		{ 0x1082, 0x1082, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MYANMAR CONSONANT SIGN SHAN MEDIAL WA
		{ 0x1083, 0x1084, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MYANMAR VOWEL SIGN SHAN AA..MYANMAR VOWEL SIGN SHAN E
		{ 0x1085, 0x1086, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MYANMAR VOWEL SIGN SHAN E ABOVE..MYANMAR VOWEL SIGN SHAN FINAL Y
		{ 0x1087, 0x108C, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MYANMAR SIGN SHAN TONE-2..MYANMAR SIGN SHAN COUNCIL TONE-3
		{ 0x108D, 0x108D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MYANMAR SIGN SHAN COUNCIL EMPHATIC TONE
		{ 0x108E, 0x108E, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER RUMAI PALAUNG FA
		{ 0x108F, 0x108F, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MYANMAR SIGN RUMAI PALAUNG TONE-5
		{ 0x1090, 0x1099, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// MYANMAR SHAN DIGIT ZERO..MYANMAR SHAN DIGIT NINE
		{ 0x109A, 0x109C, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MYANMAR SIGN KHAMTI TONE-1..MYANMAR VOWEL SIGN AITON A
		{ 0x109D, 0x109D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MYANMAR VOWEL SIGN AITON AI
		{ 0x109E, 0x109F, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// MYANMAR SYMBOL SHAN ONE..MYANMAR SYMBOL SHAN EXCLAMATION
		{ 0x10A0, 0x10C5, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GEORGIAN CAPITAL LETTER AN..GEORGIAN CAPITAL LETTER HOE
		{ 0x10C7, 0x10C7, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GEORGIAN CAPITAL LETTER YN
		{ 0x10CD, 0x10CD, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GEORGIAN CAPITAL LETTER AEN
		{ 0x10D0, 0x10FA, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GEORGIAN LETTER AN..GEORGIAN LETTER AIN
		{ 0x10FB, 0x10FB, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// GEORGIAN PARAGRAPH SEPARATOR
		{ 0x10FC, 0x10FC, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER GEORGIAN NAR
		{ 0x10FD, 0x10FF, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GEORGIAN LETTER AEN..GEORGIAN LETTER LABIAL SIGN
		{ 0x1100, 0x1248, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HANGUL CHOSEONG KIYEOK..ETHIOPIC SYLLABLE QWA
		{ 0x124A, 0x124D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE QWI..ETHIOPIC SYLLABLE QWE
		{ 0x1250, 0x1256, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE QHA..ETHIOPIC SYLLABLE QHO
		{ 0x1258, 0x1258, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE QHWA
		{ 0x125A, 0x125D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE QHWI..ETHIOPIC SYLLABLE QHWE
		{ 0x1260, 0x1288, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE BA..ETHIOPIC SYLLABLE XWA
		{ 0x128A, 0x128D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE XWI..ETHIOPIC SYLLABLE XWE
		{ 0x1290, 0x12B0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE NA..ETHIOPIC SYLLABLE KWA
		{ 0x12B2, 0x12B5, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE KWI..ETHIOPIC SYLLABLE KWE
		{ 0x12B8, 0x12BE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE KXA..ETHIOPIC SYLLABLE KXO
		{ 0x12C0, 0x12C0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE KXWA
		{ 0x12C2, 0x12C5, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE KXWI..ETHIOPIC SYLLABLE KXWE
		{ 0x12C8, 0x12D6, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE WA..ETHIOPIC SYLLABLE PHARYNGEAL O
		{ 0x12D8, 0x1310, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE ZA..ETHIOPIC SYLLABLE GWA
		{ 0x1312, 0x1315, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE GWI..ETHIOPIC SYLLABLE GWE
		{ 0x1318, 0x135A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE GGA..ETHIOPIC SYLLABLE FYA
		{ 0x135D, 0x135F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ETHIOPIC COMBINING GEMINATION AND VOWEL LENGTH MARK..ETHIOPIC COMBINING GEMINATION MARK
		{ 0x1360, 0x1368, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// ETHIOPIC SECTION MARK..ETHIOPIC PARAGRAPH SEPARATOR
		{ 0x1369, 0x137C, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// ETHIOPIC DIGIT ONE..ETHIOPIC NUMBER TEN THOUSAND
		{ 0x1380, 0x138F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE SEBATBEIT MWA..ETHIOPIC SYLLABLE PWE
		{ 0x1390, 0x1399, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ETHIOPIC TONAL MARK YIZET..ETHIOPIC TONAL MARK KURT
		{ 0x13A0, 0x13F5, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// CHEROKEE LETTER A..CHEROKEE LETTER MV
		{ 0x13F8, 0x13FD, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// CHEROKEE SMALL LETTER YE..CHEROKEE SMALL LETTER MV
		{ 0x1400, 0x1400, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// CANADIAN SYLLABICS HYPHEN
		{ 0x1401, 0x166C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CANADIAN SYLLABICS E..CANADIAN SYLLABICS CARRIER TTSA
		{ 0x166D, 0x166D, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// CANADIAN SYLLABICS CHI SIGN
		{ 0x166E, 0x166E, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// CANADIAN SYLLABICS FULL STOP
		{ 0x166F, 0x167F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CANADIAN SYLLABICS QAI..CANADIAN SYLLABICS BLACKFOOT W
		{ 0x1680, 0x1680, BidiClass::WhiteSpace, GeneralCategory::SpaceSeparator },	// OGHAM SPACE MARK
		{ 0x1681, 0x169A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// OGHAM LETTER BEITH..OGHAM LETTER PEITH
		{ 0x169B, 0x169B, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// OGHAM FEATHER MARK
		{ 0x169C, 0x169C, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// OGHAM REVERSED FEATHER MARK
		{ 0x16A0, 0x16EA, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// RUNIC LETTER FEHU FEOH FE F..RUNIC LETTER X
		{ 0x16EB, 0x16ED, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// RUNIC SINGLE PUNCTUATION..RUNIC CROSS PUNCTUATION
		{ 0x16EE, 0x16F0, BidiClass::LeftToRight, GeneralCategory::LetterNumber },	// RUNIC ARLAUG SYMBOL..RUNIC BELGTHOR SYMBOL
		{ 0x16F1, 0x16F8, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// RUNIC LETTER K..RUNIC LETTER FRANKS CASKET AESC
		{ 0x1700, 0x1711, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAGALOG LETTER A..TAGALOG LETTER HA
		{ 0x1712, 0x1714, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAGALOG VOWEL SIGN I..TAGALOG SIGN VIRAMA
		{ 0x1715, 0x1715, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAGALOG SIGN PAMUDPOD
		{ 0x171F, 0x1731, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAGALOG LETTER ARCHAIC RA..HANUNOO LETTER HA
		{ 0x1732, 0x1733, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// HANUNOO VOWEL SIGN I..HANUNOO VOWEL SIGN U
		{ 0x1734, 0x1734, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// HANUNOO SIGN PAMUDPOD
		{ 0x1735, 0x1736, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// PHILIPPINE SINGLE PUNCTUATION..PHILIPPINE DOUBLE PUNCTUATION
		{ 0x1740, 0x1751, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BUHID LETTER A..BUHID LETTER HA
		{ 0x1752, 0x1753, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BUHID VOWEL SIGN I..BUHID VOWEL SIGN U
		{ 0x1760, 0x176C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAGBANWA LETTER A..TAGBANWA LETTER YA
		{ 0x176E, 0x1770, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAGBANWA LETTER LA..TAGBANWA LETTER SA
		{ 0x1772, 0x1773, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAGBANWA VOWEL SIGN I..TAGBANWA VOWEL SIGN U
		{ 0x1780, 0x17B3, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KHMER LETTER KA..KHMER INDEPENDENT VOWEL QAU
		{ 0x17B4, 0x17B5, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHMER VOWEL INHERENT AQ..KHMER VOWEL INHERENT AA
		{ 0x17B6, 0x17B6, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KHMER VOWEL SIGN AA
		{ 0x17B7, 0x17BD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHMER VOWEL SIGN I..KHMER VOWEL SIGN UA
		{ 0x17BE, 0x17C5, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KHMER VOWEL SIGN OE..KHMER VOWEL SIGN AU
		{ 0x17C6, 0x17C6, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHMER SIGN NIKAHIT
		{ 0x17C7, 0x17C8, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KHMER SIGN REAHMUK..KHMER SIGN YUUKALEAPINTU
		{ 0x17C9, 0x17D3, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHMER SIGN MUUSIKATOAN..KHMER SIGN BATHAMASAT
		{ 0x17D4, 0x17D6, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// KHMER SIGN KHAN..KHMER SIGN CAMNUC PII KUUH
		{ 0x17D7, 0x17D7, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// KHMER SIGN LEK TOO
		{ 0x17D8, 0x17DA, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// KHMER SIGN BEYYAL..KHMER SIGN KOOMUUT
		{ 0x17DB, 0x17DB, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// KHMER CURRENCY SYMBOL RIEL
		{ 0x17DC, 0x17DC, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KHMER SIGN AVAKRAHASANYA
		{ 0x17DD, 0x17DD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHMER SIGN ATTHACAN
		{ 0x17E0, 0x17E9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// KHMER DIGIT ZERO..KHMER DIGIT NINE
		{ 0x17F0, 0x17F9, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// KHMER SYMBOL LEK ATTAK SON..KHMER SYMBOL LEK ATTAK PRAM-BUON
		{ 0x1800, 0x1805, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// MONGOLIAN BIRGA..MONGOLIAN FOUR DOTS
		{ 0x1806, 0x1806, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// MONGOLIAN TODO SOFT HYPHEN
		{ 0x1807, 0x180A, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// MONGOLIAN SIBE SYLLABLE BOUNDARY MARKER..MONGOLIAN NIRUGU
		{ 0x180B, 0x180D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MONGOLIAN FREE VARIATION SELECTOR ONE..MONGOLIAN FREE VARIATION SELECTOR THREE
		{ 0x180E, 0x180E, BidiClass::BoundaryNeutral, GeneralCategory::Format },	// MONGOLIAN VOWEL SEPARATOR
		{ 0x180F, 0x180F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MONGOLIAN FREE VARIATION SELECTOR FOUR
		{ 0x1810, 0x1819, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// MONGOLIAN DIGIT ZERO..MONGOLIAN DIGIT NINE
		{ 0x1820, 0x1842, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MONGOLIAN LETTER A..MONGOLIAN LETTER CHI
		{ 0x1843, 0x1843, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MONGOLIAN LETTER TODO LONG VOWEL SIGN
		{ 0x1844, 0x1878, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MONGOLIAN LETTER TODO E..MONGOLIAN LETTER CHA WITH TWO DOTS
		{ 0x1880, 0x1884, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MONGOLIAN LETTER ALI GALI ANUSVARA ONE..MONGOLIAN LETTER ALI GALI INVERTED UBADAMA
		{ 0x1885, 0x1886, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MONGOLIAN LETTER ALI GALI BALUDA..MONGOLIAN LETTER ALI GALI THREE BALUDA
		{ 0x1887, 0x18A8, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MONGOLIAN LETTER ALI GALI A..MONGOLIAN LETTER MANCHU ALI GALI BHA
		{ 0x18A9, 0x18A9, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MONGOLIAN LETTER ALI GALI DAGALGA
		{ 0x18AA, 0x18AA, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MONGOLIAN LETTER MANCHU ALI GALI LHA
		{ 0x18B0, 0x18F5, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CANADIAN SYLLABICS OY..CANADIAN SYLLABICS CARRIER DENTAL S
		{ 0x1900, 0x191E, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LIMBU VOWEL-CARRIER LETTER..LIMBU LETTER TRA
		{ 0x1920, 0x1922, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// LIMBU VOWEL SIGN A..LIMBU VOWEL SIGN U
		{ 0x1923, 0x1926, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// LIMBU VOWEL SIGN EE..LIMBU VOWEL SIGN AU
		{ 0x1927, 0x1928, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// LIMBU VOWEL SIGN E..LIMBU VOWEL SIGN O
		{ 0x1929, 0x192B, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// LIMBU SUBJOINED LETTER YA..LIMBU SUBJOINED LETTER WA
		{ 0x1930, 0x1931, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// LIMBU SMALL LETTER KA..LIMBU SMALL LETTER NGA
		{ 0x1932, 0x1932, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// LIMBU SMALL LETTER ANUSVARA
		{ 0x1933, 0x1938, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// LIMBU SMALL LETTER TA..LIMBU SMALL LETTER LA
		{ 0x1939, 0x193B, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// LIMBU SIGN MUKPHRENG..LIMBU SIGN SA-I
		{ 0x1940, 0x1940, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// LIMBU SIGN LOO
		{ 0x1944, 0x1945, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// LIMBU EXCLAMATION MARK..LIMBU QUESTION MARK
		{ 0x1946, 0x194F, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// LIMBU DIGIT ZERO..LIMBU DIGIT NINE
		{ 0x1950, 0x196D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI LE LETTER KA..TAI LE LETTER AI
		{ 0x1970, 0x1974, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI LE LETTER TONE-2..TAI LE LETTER TONE-6
		{ 0x1980, 0x19AB, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// NEW TAI LUE LETTER HIGH QA..NEW TAI LUE LETTER LOW SUA
		{ 0x19B0, 0x19C9, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// NEW TAI LUE VOWEL SIGN VOWEL SHORTENER..NEW TAI LUE TONE MARK-2
		{ 0x19D0, 0x19D9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// NEW TAI LUE DIGIT ZERO..NEW TAI LUE DIGIT NINE
		{ 0x19DA, 0x19DA, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// NEW TAI LUE THAM DIGIT ONE
		{ 0x19DE, 0x19FF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// NEW TAI LUE SIGN LAE..KHMER SYMBOL DAP-PRAM ROC
		{ 0x1A00, 0x1A16, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BUGINESE LETTER KA..BUGINESE LETTER HA
		{ 0x1A17, 0x1A18, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BUGINESE VOWEL SIGN I..BUGINESE VOWEL SIGN U
		{ 0x1A19, 0x1A1A, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BUGINESE VOWEL SIGN E..BUGINESE VOWEL SIGN O
		{ 0x1A1B, 0x1A1B, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BUGINESE VOWEL SIGN AE
		{ 0x1A1E, 0x1A1F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// BUGINESE PALLAWA..BUGINESE END OF SECTION
		{ 0x1A20, 0x1A54, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI THAM LETTER HIGH KA..TAI THAM LETTER GREAT SA
		{ 0x1A55, 0x1A55, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAI THAM CONSONANT SIGN MEDIAL RA
		{ 0x1A56, 0x1A56, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI THAM CONSONANT SIGN MEDIAL LA
		{ 0x1A57, 0x1A57, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAI THAM CONSONANT SIGN LA TANG LAI
		{ 0x1A58, 0x1A5E, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI THAM SIGN MAI KANG LAI..TAI THAM CONSONANT SIGN SA
		{ 0x1A60, 0x1A60, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI THAM SIGN SAKOT
		{ 0x1A61, 0x1A61, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAI THAM VOWEL SIGN A
		{ 0x1A62, 0x1A62, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI THAM VOWEL SIGN MAI SAT
		{ 0x1A63, 0x1A64, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAI THAM VOWEL SIGN AA..TAI THAM VOWEL SIGN TALL AA
		{ 0x1A65, 0x1A6C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI THAM VOWEL SIGN I..TAI THAM VOWEL SIGN OA BELOW
		{ 0x1A6D, 0x1A72, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAI THAM VOWEL SIGN OY..TAI THAM VOWEL SIGN THAM AI
		{ 0x1A73, 0x1A7C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI THAM VOWEL SIGN OA ABOVE..TAI THAM SIGN KHUEN-LUE KARAN
		{ 0x1A7F, 0x1A7F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI THAM COMBINING CRYPTOGRAMMIC DOT
		{ 0x1A80, 0x1A89, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// TAI THAM HORA DIGIT ZERO..TAI THAM HORA DIGIT NINE
		{ 0x1A90, 0x1A99, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// TAI THAM THAM DIGIT ZERO..TAI THAM THAM DIGIT NINE
		{ 0x1AA0, 0x1AA6, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TAI THAM SIGN WIANG..TAI THAM SIGN REVERSED ROTATED RANA
		{ 0x1AA7, 0x1AA7, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// TAI THAM SIGN MAI YAMOK
		{ 0x1AA8, 0x1AAD, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TAI THAM SIGN KAAN..TAI THAM SIGN CAANG
		{ 0x1AB0, 0x1ABD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING DOUBLED CIRCUMFLEX ACCENT..COMBINING PARENTHESES BELOW
		{ 0x1ABE, 0x1ABE, BidiClass::NonspacingMark, GeneralCategory::EnclosingMark },	// COMBINING PARENTHESES OVERLAY
		{ 0x1ABF, 0x1ADD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING LATIN SMALL LETTER W BELOW..COMBINING DOT-AND-RING BELOW
		{ 0x1AE0, 0x1AEB, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING LEFT TACK ABOVE..COMBINING DOUBLE RIGHTWARDS ARROW ABOVE
		{ 0x1B00, 0x1B03, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BALINESE SIGN ULU RICEM..BALINESE SIGN SURANG
		{ 0x1B04, 0x1B04, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BALINESE SIGN BISAH
		{ 0x1B05, 0x1B33, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BALINESE LETTER AKARA..BALINESE LETTER HA
		{ 0x1B34, 0x1B34, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BALINESE SIGN REREKAN
		{ 0x1B35, 0x1B35, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BALINESE VOWEL SIGN TEDUNG
		{ 0x1B36, 0x1B3A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BALINESE VOWEL SIGN ULU..BALINESE VOWEL SIGN RA REPA
		{ 0x1B3B, 0x1B3B, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BALINESE VOWEL SIGN RA REPA TEDUNG
		{ 0x1B3C, 0x1B3C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BALINESE VOWEL SIGN LA LENGA
		{ 0x1B3D, 0x1B41, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BALINESE VOWEL SIGN LA LENGA TEDUNG..BALINESE VOWEL SIGN TALING REPA TEDUNG
		{ 0x1B42, 0x1B42, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BALINESE VOWEL SIGN PEPET
		{ 0x1B43, 0x1B44, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BALINESE VOWEL SIGN PEPET TEDUNG..BALINESE ADEG ADEG
		{ 0x1B45, 0x1B4C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BALINESE LETTER KAF SASAK..BALINESE LETTER ARCHAIC JNYA
		{ 0x1B4E, 0x1B4F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// BALINESE INVERTED CARIK SIKI..BALINESE INVERTED CARIK PAREREN
		{ 0x1B50, 0x1B59, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// BALINESE DIGIT ZERO..BALINESE DIGIT NINE
		{ 0x1B5A, 0x1B60, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// BALINESE PANTI..BALINESE PAMENENG
		{ 0x1B61, 0x1B6A, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// BALINESE MUSICAL SYMBOL DONG..BALINESE MUSICAL SYMBOL DANG GEDE
		{ 0x1B6B, 0x1B73, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BALINESE MUSICAL SYMBOL COMBINING TEGEH..BALINESE MUSICAL SYMBOL COMBINING GONG
		{ 0x1B74, 0x1B7C, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// BALINESE MUSICAL SYMBOL RIGHT-HAND OPEN DUG..BALINESE MUSICAL SYMBOL LEFT-HAND OPEN PING
		{ 0x1B7D, 0x1B7F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// BALINESE PANTI LANTANG..BALINESE PANTI BAWAK
		{ 0x1B80, 0x1B81, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SUNDANESE SIGN PANYECEK..SUNDANESE SIGN PANGLAYAR
		{ 0x1B82, 0x1B82, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SUNDANESE SIGN PANGWISAD
		{ 0x1B83, 0x1BA0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SUNDANESE LETTER A..SUNDANESE LETTER HA
		{ 0x1BA1, 0x1BA1, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SUNDANESE CONSONANT SIGN PAMINGKAL
		{ 0x1BA2, 0x1BA5, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SUNDANESE CONSONANT SIGN PANYAKRA..SUNDANESE VOWEL SIGN PANYUKU
		{ 0x1BA6, 0x1BA7, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SUNDANESE VOWEL SIGN PANAELAENG..SUNDANESE VOWEL SIGN PANOLONG
		{ 0x1BA8, 0x1BA9, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SUNDANESE VOWEL SIGN PAMEPET..SUNDANESE VOWEL SIGN PANEULEUNG
		{ 0x1BAA, 0x1BAA, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SUNDANESE SIGN PAMAAEH
		{ 0x1BAB, 0x1BAD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SUNDANESE SIGN VIRAMA..SUNDANESE CONSONANT SIGN PASANGAN WA
		{ 0x1BAE, 0x1BAF, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SUNDANESE LETTER KHA..SUNDANESE LETTER SYA
		{ 0x1BB0, 0x1BB9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// SUNDANESE DIGIT ZERO..SUNDANESE DIGIT NINE
		{ 0x1BBA, 0x1BE5, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SUNDANESE AVAGRAHA..BATAK LETTER U
		{ 0x1BE6, 0x1BE6, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BATAK SIGN TOMPI
		{ 0x1BE7, 0x1BE7, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BATAK VOWEL SIGN E
		{ 0x1BE8, 0x1BE9, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BATAK VOWEL SIGN PAKPAK E..BATAK VOWEL SIGN EE
		{ 0x1BEA, 0x1BEC, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BATAK VOWEL SIGN I..BATAK VOWEL SIGN O
		{ 0x1BED, 0x1BED, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BATAK VOWEL SIGN KARO O
		{ 0x1BEE, 0x1BEE, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BATAK VOWEL SIGN U
		{ 0x1BEF, 0x1BF1, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BATAK VOWEL SIGN U FOR SIMALUNGUN SA..BATAK CONSONANT SIGN H
		{ 0x1BF2, 0x1BF3, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BATAK PANGOLAT..BATAK PANONGONAN
		{ 0x1BFC, 0x1BFF, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// BATAK SYMBOL BINDU NA METEK..BATAK SYMBOL BINDU PANGOLAT
		{ 0x1C00, 0x1C23, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LEPCHA LETTER KA..LEPCHA LETTER A
		{ 0x1C24, 0x1C2B, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// LEPCHA SUBJOINED LETTER YA..LEPCHA VOWEL SIGN UU
		{ 0x1C2C, 0x1C33, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// LEPCHA VOWEL SIGN E..LEPCHA CONSONANT SIGN T
		{ 0x1C34, 0x1C35, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// LEPCHA CONSONANT SIGN NYIN-DO..LEPCHA CONSONANT SIGN KANG
		{ 0x1C36, 0x1C37, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// LEPCHA SIGN RAN..LEPCHA SIGN NUKTA
		{ 0x1C3B, 0x1C3F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// LEPCHA PUNCTUATION TA-ROL..LEPCHA PUNCTUATION TSHOOK
		{ 0x1C40, 0x1C49, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// LEPCHA DIGIT ZERO..LEPCHA DIGIT NINE
		{ 0x1C4D, 0x1C4F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LEPCHA LETTER TTA..LEPCHA LETTER DDA
		{ 0x1C50, 0x1C59, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// OL CHIKI DIGIT ZERO..OL CHIKI DIGIT NINE
		{ 0x1C5A, 0x1C77, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// OL CHIKI LETTER LA..OL CHIKI LETTER OH
		{ 0x1C78, 0x1C7D, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// OL CHIKI MU TTUDDAG..OL CHIKI AHAD
		{ 0x1C7E, 0x1C7F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// OL CHIKI PUNCTUATION MUCAAD..OL CHIKI PUNCTUATION DOUBLE MUCAAD
		{ 0x1C80, 0x1C8A, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// CYRILLIC SMALL LETTER ROUNDED VE..CYRILLIC SMALL LETTER TJE
		{ 0x1C90, 0x1CBA, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GEORGIAN MTAVRULI CAPITAL LETTER AN..GEORGIAN MTAVRULI CAPITAL LETTER AIN
		{ 0x1CBD, 0x1CBF, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GEORGIAN MTAVRULI CAPITAL LETTER AEN..GEORGIAN MTAVRULI CAPITAL LETTER LABIAL SIGN
		{ 0x1CC0, 0x1CC7, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// SUNDANESE PUNCTUATION BINDU SURYA..SUNDANESE PUNCTUATION BINDU BA SATANGA
		{ 0x1CD0, 0x1CD2, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// VEDIC TONE KARSHANA..VEDIC TONE PRENKHA
		{ 0x1CD3, 0x1CD3, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// VEDIC SIGN NIHSHVASA
		{ 0x1CD4, 0x1CE0, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// VEDIC SIGN YAJURVEDIC MIDLINE SVARITA..VEDIC TONE RIGVEDIC KASHMIRI INDEPENDENT SVARITA
		{ 0x1CE1, 0x1CE1, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// VEDIC TONE ATHARVAVEDIC INDEPENDENT SVARITA
		{ 0x1CE2, 0x1CE8, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// VEDIC SIGN VISARGA SVARITA..VEDIC SIGN VISARGA ANUDATTA WITH TAIL
		{ 0x1CE9, 0x1CEC, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// VEDIC SIGN ANUSVARA ANTARGOMUKHA..VEDIC SIGN ANUSVARA VAMAGOMUKHA WITH TAIL
		{ 0x1CED, 0x1CED, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// VEDIC SIGN TIRYAK
		{ 0x1CEE, 0x1CF3, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// VEDIC SIGN HEXIFORM LONG ANUSVARA..VEDIC SIGN ROTATED ARDHAVISARGA
		{ 0x1CF4, 0x1CF4, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// VEDIC TONE CANDRA ABOVE
		{ 0x1CF5, 0x1CF6, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// VEDIC SIGN JIHVAMULIYA..VEDIC SIGN UPADHMANIYA
		{ 0x1CF7, 0x1CF7, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// VEDIC SIGN ATIKRAMA
		{ 0x1CF8, 0x1CF9, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// VEDIC TONE RING ABOVE..VEDIC TONE DOUBLE RING ABOVE
		{ 0x1CFA, 0x1CFA, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// VEDIC SIGN DOUBLE ANUSVARA ANTARGOMUKHA
		{ 0x1D00, 0x1D2B, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN LETTER SMALL CAPITAL A..CYRILLIC LETTER SMALL CAPITAL EL
		{ 0x1D2C, 0x1D6A, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER CAPITAL A..GREEK SUBSCRIPT SMALL LETTER CHI
		{ 0x1D6B, 0x1D77, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN SMALL LETTER UE..LATIN SMALL LETTER TURNED G
		{ 0x1D78, 0x1D78, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER CYRILLIC EN
		{ 0x1D79, 0x1D9A, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN SMALL LETTER INSULAR G..LATIN SMALL LETTER EZH WITH RETROFLEX HOOK
		{ 0x1D9B, 0x1DBF, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER SMALL TURNED ALPHA..MODIFIER LETTER SMALL THETA
		{ 0x1DC0, 0x1DFF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING DOTTED GRAVE ACCENT..COMBINING RIGHT ARROWHEAD AND DOWN ARROWHEAD BELOW
		{ 0x1E00, 0x1F15, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN CAPITAL LETTER A WITH RING BELOW..GREEK SMALL LETTER EPSILON WITH DASIA AND OXIA
		{ 0x1F18, 0x1F1D, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER EPSILON WITH PSILI..GREEK CAPITAL LETTER EPSILON WITH DASIA AND OXIA
		{ 0x1F20, 0x1F45, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK SMALL LETTER ETA WITH PSILI..GREEK SMALL LETTER OMICRON WITH DASIA AND OXIA
		{ 0x1F48, 0x1F4D, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER OMICRON WITH PSILI..GREEK CAPITAL LETTER OMICRON WITH DASIA AND OXIA
		{ 0x1F50, 0x1F57, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK SMALL LETTER UPSILON WITH PSILI..GREEK SMALL LETTER UPSILON WITH DASIA AND PERISPOMENI
		{ 0x1F59, 0x1F59, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER UPSILON WITH DASIA
		{ 0x1F5B, 0x1F5B, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER UPSILON WITH DASIA AND VARIA
		{ 0x1F5D, 0x1F5D, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER UPSILON WITH DASIA AND OXIA
		{ 0x1F5F, 0x1F7D, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK CAPITAL LETTER UPSILON WITH DASIA AND PERISPOMENI..GREEK SMALL LETTER OMEGA WITH OXIA
		{ 0x1F80, 0x1FB4, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK SMALL LETTER ALPHA WITH PSILI AND YPOGEGRAMMENI..GREEK SMALL LETTER ALPHA WITH OXIA AND YPOGEGRAMMENI
		{ 0x1FB6, 0x1FBC, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK SMALL LETTER ALPHA WITH PERISPOMENI..GREEK CAPITAL LETTER ALPHA WITH PROSGEGRAMMENI
		{ 0x1FBD, 0x1FBD, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// GREEK KORONIS
		{ 0x1FBE, 0x1FBE, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK PROSGEGRAMMENI
		{ 0x1FBF, 0x1FC1, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// GREEK PSILI..GREEK DIALYTIKA AND PERISPOMENI
		{ 0x1FC2, 0x1FC4, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK SMALL LETTER ETA WITH VARIA AND YPOGEGRAMMENI..GREEK SMALL LETTER ETA WITH OXIA AND YPOGEGRAMMENI
		{ 0x1FC6, 0x1FCC, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK SMALL LETTER ETA WITH PERISPOMENI..GREEK CAPITAL LETTER ETA WITH PROSGEGRAMMENI
		{ 0x1FCD, 0x1FCF, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// GREEK PSILI AND VARIA..GREEK PSILI AND PERISPOMENI
		{ 0x1FD0, 0x1FD3, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK SMALL LETTER IOTA WITH VRACHY..GREEK SMALL LETTER IOTA WITH DIALYTIKA AND OXIA
		{ 0x1FD6, 0x1FDB, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK SMALL LETTER IOTA WITH PERISPOMENI..GREEK CAPITAL LETTER IOTA WITH OXIA
		{ 0x1FDD, 0x1FDF, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// GREEK DASIA AND VARIA..GREEK DASIA AND PERISPOMENI
		{ 0x1FE0, 0x1FEC, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK SMALL LETTER UPSILON WITH VRACHY..GREEK CAPITAL LETTER RHO WITH DASIA
		{ 0x1FED, 0x1FEF, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// GREEK DIALYTIKA AND VARIA..GREEK VARIA
		{ 0x1FF2, 0x1FF4, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK SMALL LETTER OMEGA WITH VARIA AND YPOGEGRAMMENI..GREEK SMALL LETTER OMEGA WITH OXIA AND YPOGEGRAMMENI
		{ 0x1FF6, 0x1FFC, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GREEK SMALL LETTER OMEGA WITH PERISPOMENI..GREEK CAPITAL LETTER OMEGA WITH PROSGEGRAMMENI
		{ 0x1FFD, 0x1FFE, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// GREEK OXIA..GREEK DASIA
		{ 0x2000, 0x200A, BidiClass::WhiteSpace, GeneralCategory::SpaceSeparator },	// EN QUAD..HAIR SPACE
		{ 0x200B, 0x200D, BidiClass::BoundaryNeutral, GeneralCategory::Format },	// ZERO WIDTH SPACE..ZERO WIDTH JOINER
		{ 0x200E, 0x200E, BidiClass::LeftToRight, GeneralCategory::Format },	// LEFT-TO-RIGHT MARK
		{ 0x200F, 0x200F, BidiClass::RightToLeft, GeneralCategory::Format },	// RIGHT-TO-LEFT MARK
		{ 0x2010, 0x2015, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// HYPHEN..HORIZONTAL BAR
		{ 0x2016, 0x2017, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// DOUBLE VERTICAL LINE..DOUBLE LOW LINE
		{ 0x2018, 0x2018, BidiClass::OtherNeutral, GeneralCategory::InitialPunctuation },	// LEFT SINGLE QUOTATION MARK
		{ 0x2019, 0x2019, BidiClass::OtherNeutral, GeneralCategory::FinalPunctuation },	// RIGHT SINGLE QUOTATION MARK
		{ 0x201A, 0x201A, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// SINGLE LOW-9 QUOTATION MARK
		{ 0x201B, 0x201C, BidiClass::OtherNeutral, GeneralCategory::InitialPunctuation },	// SINGLE HIGH-REVERSED-9 QUOTATION MARK..LEFT DOUBLE QUOTATION MARK
		{ 0x201D, 0x201D, BidiClass::OtherNeutral, GeneralCategory::FinalPunctuation },	// RIGHT DOUBLE QUOTATION MARK
		{ 0x201E, 0x201E, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// DOUBLE LOW-9 QUOTATION MARK
		{ 0x201F, 0x201F, BidiClass::OtherNeutral, GeneralCategory::InitialPunctuation },	// DOUBLE HIGH-REVERSED-9 QUOTATION MARK
		{ 0x2020, 0x2027, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// DAGGER..HYPHENATION POINT
		{ 0x2028, 0x2028, BidiClass::WhiteSpace, GeneralCategory::LineSeparator },	// LINE SEPARATOR
		{ 0x2029, 0x2029, BidiClass::ParagraphSeparator, GeneralCategory::ParagraphSeparator },	// PARAGRAPH SEPARATOR
		{ 0x202A, 0x202A, BidiClass::LeftToRightEmbedding, GeneralCategory::Format },	// LEFT-TO-RIGHT EMBEDDING
		{ 0x202B, 0x202B, BidiClass::RightToLeftEmbedding, GeneralCategory::Format },	// RIGHT-TO-LEFT EMBEDDING
		{ 0x202C, 0x202C, BidiClass::PopDirectionalFormat, GeneralCategory::Format },	// POP DIRECTIONAL FORMATTING
		{ 0x202D, 0x202D, BidiClass::LeftToRightOverride, GeneralCategory::Format },	// LEFT-TO-RIGHT OVERRIDE
		{ 0x202E, 0x202E, BidiClass::RightToLeftOverride, GeneralCategory::Format },	// RIGHT-TO-LEFT OVERRIDE
		{ 0x202F, 0x202F, BidiClass::CommonSeparator, GeneralCategory::SpaceSeparator },	// NARROW NO-BREAK SPACE
		{ 0x2030, 0x2034, BidiClass::EuropeanTerminator, GeneralCategory::OtherPunctuation },	// PER MILLE SIGN..TRIPLE PRIME
		{ 0x2035, 0x2038, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// REVERSED PRIME..CARET
		{ 0x2039, 0x2039, BidiClass::OtherNeutral, GeneralCategory::InitialPunctuation },	// SINGLE LEFT-POINTING ANGLE QUOTATION MARK
		{ 0x203A, 0x203A, BidiClass::OtherNeutral, GeneralCategory::FinalPunctuation },	// SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
		{ 0x203B, 0x203E, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// REFERENCE MARK..OVERLINE
		{ 0x203F, 0x2040, BidiClass::OtherNeutral, GeneralCategory::ConnectorPunctuation },	// UNDERTIE..CHARACTER TIE
		{ 0x2041, 0x2043, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// CARET INSERTION POINT..HYPHEN BULLET
		{ 0x2044, 0x2044, BidiClass::CommonSeparator, GeneralCategory::MathSymbol },	// FRACTION SLASH
		{ 0x2045, 0x2045, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT SQUARE BRACKET WITH QUILL
		{ 0x2046, 0x2046, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT SQUARE BRACKET WITH QUILL
		{ 0x2047, 0x2051, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// DOUBLE QUESTION MARK..TWO ASTERISKS ALIGNED VERTICALLY
		{ 0x2052, 0x2052, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// COMMERCIAL MINUS SIGN
		{ 0x2053, 0x2053, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// SWUNG DASH
		{ 0x2054, 0x2054, BidiClass::OtherNeutral, GeneralCategory::ConnectorPunctuation },	// INVERTED UNDERTIE
		{ 0x2055, 0x205E, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// FLOWER PUNCTUATION MARK..VERTICAL FOUR DOTS
		{ 0x205F, 0x205F, BidiClass::WhiteSpace, GeneralCategory::SpaceSeparator },	// MEDIUM MATHEMATICAL SPACE
		{ 0x2060, 0x2064, BidiClass::BoundaryNeutral, GeneralCategory::Format },	// WORD JOINER..INVISIBLE PLUS
		{ 0x2065, 0x2065, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <reserved-2065>
		{ 0x2066, 0x2066, BidiClass::LeftToRightIsolate, GeneralCategory::Format },	// LEFT-TO-RIGHT ISOLATE
		{ 0x2067, 0x2067, BidiClass::RightToLeftIsolate, GeneralCategory::Format },	// RIGHT-TO-LEFT ISOLATE
		{ 0x2068, 0x2068, BidiClass::FirstStrongIsolate, GeneralCategory::Format },	// FIRST STRONG ISOLATE
		{ 0x2069, 0x2069, BidiClass::PopDirectionalIsolate, GeneralCategory::Format },	// POP DIRECTIONAL ISOLATE
		{ 0x206A, 0x206F, BidiClass::BoundaryNeutral, GeneralCategory::Format },	// INHIBIT SYMMETRIC SWAPPING..NOMINAL DIGIT SHAPES
		{ 0x2070, 0x2070, BidiClass::EuropeanNumber, GeneralCategory::OtherNumber },	// SUPERSCRIPT ZERO
		{ 0x2071, 0x2071, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// SUPERSCRIPT LATIN SMALL LETTER I
		{ 0x2074, 0x2079, BidiClass::EuropeanNumber, GeneralCategory::OtherNumber },	// SUPERSCRIPT FOUR..SUPERSCRIPT NINE
		{ 0x207A, 0x207B, BidiClass::EuropeanSeparator, GeneralCategory::MathSymbol },	// SUPERSCRIPT PLUS SIGN..SUPERSCRIPT MINUS
		{ 0x207C, 0x207C, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// SUPERSCRIPT EQUALS SIGN
		{ 0x207D, 0x207D, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// SUPERSCRIPT LEFT PARENTHESIS
		{ 0x207E, 0x207E, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// SUPERSCRIPT RIGHT PARENTHESIS
		{ 0x207F, 0x207F, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// SUPERSCRIPT LATIN SMALL LETTER N
		{ 0x2080, 0x2089, BidiClass::EuropeanNumber, GeneralCategory::OtherNumber },	// SUBSCRIPT ZERO..SUBSCRIPT NINE
		{ 0x208A, 0x208B, BidiClass::EuropeanSeparator, GeneralCategory::MathSymbol },	// SUBSCRIPT PLUS SIGN..SUBSCRIPT MINUS
		{ 0x208C, 0x208C, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// SUBSCRIPT EQUALS SIGN
		{ 0x208D, 0x208D, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// SUBSCRIPT LEFT PARENTHESIS
		{ 0x208E, 0x208E, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// SUBSCRIPT RIGHT PARENTHESIS
		{ 0x2090, 0x209C, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// LATIN SUBSCRIPT SMALL LETTER A..LATIN SUBSCRIPT SMALL LETTER T
		{ 0x20A0, 0x20C1, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// EURO-CURRENCY SIGN..SAUDI RIYAL SIGN
		{ 0x20D0, 0x20DC, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING LEFT HARPOON ABOVE..COMBINING FOUR DOTS ABOVE
		{ 0x20DD, 0x20E0, BidiClass::NonspacingMark, GeneralCategory::EnclosingMark },	// COMBINING ENCLOSING CIRCLE..COMBINING ENCLOSING CIRCLE BACKSLASH
		{ 0x20E1, 0x20E1, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING LEFT RIGHT ARROW ABOVE
		{ 0x20E2, 0x20E4, BidiClass::NonspacingMark, GeneralCategory::EnclosingMark },	// COMBINING ENCLOSING SCREEN..COMBINING ENCLOSING UPWARD POINTING TRIANGLE
		{ 0x20E5, 0x20F0, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING REVERSE SOLIDUS OVERLAY..COMBINING ASTERISK ABOVE
		{ 0x2100, 0x2101, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ACCOUNT OF..ADDRESSED TO THE SUBJECT
		{ 0x2102, 0x2102, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// DOUBLE-STRUCK CAPITAL C
		{ 0x2103, 0x2106, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// DEGREE CELSIUS..CADA UNA
		{ 0x2107, 0x2107, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// EULER CONSTANT
		{ 0x2108, 0x2109, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// SCRUPLE..DEGREE FAHRENHEIT
		{ 0x210A, 0x2113, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// SCRIPT SMALL G..SCRIPT SMALL L
		{ 0x2114, 0x2114, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// L B BAR SYMBOL
		{ 0x2115, 0x2115, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// DOUBLE-STRUCK CAPITAL N
		{ 0x2116, 0x2117, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// NUMERO SIGN..SOUND RECORDING COPYRIGHT
		{ 0x2118, 0x2118, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// SCRIPT CAPITAL P
		{ 0x2119, 0x211D, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// DOUBLE-STRUCK CAPITAL P..DOUBLE-STRUCK CAPITAL R
		{ 0x211E, 0x2123, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// PRESCRIPTION TAKE..VERSICLE
		{ 0x2124, 0x2124, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// DOUBLE-STRUCK CAPITAL Z
		{ 0x2125, 0x2125, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// OUNCE SIGN
		{ 0x2126, 0x2126, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// OHM SIGN
		{ 0x2127, 0x2127, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// INVERTED OHM SIGN
		{ 0x2128, 0x2128, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// BLACK-LETTER CAPITAL Z
		{ 0x2129, 0x2129, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// TURNED GREEK SMALL LETTER IOTA
		{ 0x212A, 0x212D, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// KELVIN SIGN..BLACK-LETTER CAPITAL C
		{ 0x212E, 0x212E, BidiClass::EuropeanTerminator, GeneralCategory::OtherSymbol },	// ESTIMATED SYMBOL
		{ 0x212F, 0x2134, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// SCRIPT SMALL E..SCRIPT SMALL O
		{ 0x2135, 0x2138, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ALEF SYMBOL..DALET SYMBOL
		{ 0x2139, 0x2139, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// INFORMATION SOURCE
		{ 0x213A, 0x213B, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ROTATED CAPITAL Q..FACSIMILE SIGN
		{ 0x213C, 0x213F, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// DOUBLE-STRUCK SMALL PI..DOUBLE-STRUCK CAPITAL PI
		{ 0x2140, 0x2144, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// DOUBLE-STRUCK N-ARY SUMMATION..TURNED SANS-SERIF CAPITAL Y
		{ 0x2145, 0x2149, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// DOUBLE-STRUCK ITALIC CAPITAL D..DOUBLE-STRUCK ITALIC SMALL J
		{ 0x214A, 0x214A, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// PROPERTY LINE
		{ 0x214B, 0x214B, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// TURNED AMPERSAND
		{ 0x214C, 0x214D, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// PER SIGN..AKTIESELSKAB
		{ 0x214E, 0x214E, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// TURNED SMALL F
		{ 0x214F, 0x214F, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// SYMBOL FOR SAMARITAN SOURCE
		{ 0x2150, 0x215F, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// VULGAR FRACTION ONE SEVENTH..FRACTION NUMERATOR ONE
		{ 0x2160, 0x2182, BidiClass::LeftToRight, GeneralCategory::LetterNumber },	// ROMAN NUMERAL ONE..ROMAN NUMERAL TEN THOUSAND
		{ 0x2183, 0x2184, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// ROMAN NUMERAL REVERSED ONE HUNDRED..LATIN SMALL LETTER REVERSED C
		{ 0x2185, 0x2188, BidiClass::LeftToRight, GeneralCategory::LetterNumber },	// ROMAN NUMERAL SIX LATE FORM..ROMAN NUMERAL ONE HUNDRED THOUSAND
		{ 0x2189, 0x2189, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// VULGAR FRACTION ZERO THIRDS
		{ 0x218A, 0x218B, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// TURNED DIGIT TWO..TURNED DIGIT THREE
		{ 0x2190, 0x2194, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// LEFTWARDS ARROW..LEFT RIGHT ARROW
		{ 0x2195, 0x2199, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// UP DOWN ARROW..SOUTH WEST ARROW
		{ 0x219A, 0x219B, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// LEFTWARDS ARROW WITH STROKE..RIGHTWARDS ARROW WITH STROKE
		{ 0x219C, 0x219F, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// LEFTWARDS WAVE ARROW..UPWARDS TWO HEADED ARROW
		{ 0x21A0, 0x21A0, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// RIGHTWARDS TWO HEADED ARROW
		{ 0x21A1, 0x21A2, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// DOWNWARDS TWO HEADED ARROW..LEFTWARDS ARROW WITH TAIL
		{ 0x21A3, 0x21A3, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// RIGHTWARDS ARROW WITH TAIL
		{ 0x21A4, 0x21A5, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// LEFTWARDS ARROW FROM BAR..UPWARDS ARROW FROM BAR
		{ 0x21A6, 0x21A6, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// RIGHTWARDS ARROW FROM BAR
		{ 0x21A7, 0x21AD, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// DOWNWARDS ARROW FROM BAR..LEFT RIGHT WAVE ARROW
		{ 0x21AE, 0x21AE, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// LEFT RIGHT ARROW WITH STROKE
		{ 0x21AF, 0x21CD, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// DOWNWARDS ZIGZAG ARROW..LEFTWARDS DOUBLE ARROW WITH STROKE
		{ 0x21CE, 0x21CF, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// LEFT RIGHT DOUBLE ARROW WITH STROKE..RIGHTWARDS DOUBLE ARROW WITH STROKE
		{ 0x21D0, 0x21D1, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// LEFTWARDS DOUBLE ARROW..UPWARDS DOUBLE ARROW
		{ 0x21D2, 0x21D2, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// RIGHTWARDS DOUBLE ARROW
		{ 0x21D3, 0x21D3, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// DOWNWARDS DOUBLE ARROW
		{ 0x21D4, 0x21D4, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// LEFT RIGHT DOUBLE ARROW
		{ 0x21D5, 0x21F3, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// UP DOWN DOUBLE ARROW..UP DOWN WHITE ARROW
		{ 0x21F4, 0x2211, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// RIGHT ARROW WITH SMALL CIRCLE..N-ARY SUMMATION
		{ 0x2212, 0x2212, BidiClass::EuropeanSeparator, GeneralCategory::MathSymbol },	// MINUS SIGN
		{ 0x2213, 0x2213, BidiClass::EuropeanTerminator, GeneralCategory::MathSymbol },	// MINUS-OR-PLUS SIGN
		{ 0x2214, 0x22FF, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// DOT PLUS..Z NOTATION BAG MEMBERSHIP
		{ 0x2300, 0x2307, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// DIAMETER SIGN..WAVY LINE
		{ 0x2308, 0x2308, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT CEILING
		{ 0x2309, 0x2309, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT CEILING
		{ 0x230A, 0x230A, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT FLOOR
		{ 0x230B, 0x230B, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT FLOOR
		{ 0x230C, 0x231F, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// BOTTOM RIGHT CROP..BOTTOM RIGHT CORNER
		{ 0x2320, 0x2321, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// TOP HALF INTEGRAL..BOTTOM HALF INTEGRAL
		{ 0x2322, 0x2328, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// FROWN..KEYBOARD
		{ 0x2329, 0x2329, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT-POINTING ANGLE BRACKET
		{ 0x232A, 0x232A, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT-POINTING ANGLE BRACKET
		{ 0x232B, 0x2335, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ERASE TO THE LEFT..COUNTERSINK
		{ 0x2336, 0x237A, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// APL FUNCTIONAL SYMBOL I-BEAM..APL FUNCTIONAL SYMBOL ALPHA
		{ 0x237B, 0x237B, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// NOT CHECK MARK
		{ 0x237C, 0x237C, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// RIGHT ANGLE WITH DOWNWARDS ZIGZAG ARROW
		{ 0x237D, 0x2394, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// SHOULDERED OPEN BOX..SOFTWARE-FUNCTION SYMBOL
		{ 0x2395, 0x2395, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// APL FUNCTIONAL SYMBOL QUAD
		{ 0x2396, 0x239A, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// DECIMAL SEPARATOR KEY SYMBOL..CLEAR SCREEN SYMBOL
		{ 0x239B, 0x23B3, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// LEFT PARENTHESIS UPPER HOOK..SUMMATION BOTTOM
		{ 0x23B4, 0x23DB, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// TOP SQUARE BRACKET..FUSE
		{ 0x23DC, 0x23E1, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// TOP PARENTHESIS..BOTTOM TORTOISE SHELL BRACKET
		{ 0x23E2, 0x2429, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// WHITE TRAPEZIUM..SYMBOL FOR DELETE MEDIUM SHADE FORM
		{ 0x2440, 0x244A, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// OCR HOOK..OCR DOUBLE BACKSLASH
		{ 0x2460, 0x2487, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// CIRCLED DIGIT ONE..PARENTHESIZED NUMBER TWENTY
		{ 0x2488, 0x249B, BidiClass::EuropeanNumber, GeneralCategory::OtherNumber },	// DIGIT ONE FULL STOP..NUMBER TWENTY FULL STOP
		{ 0x249C, 0x24E9, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// PARENTHESIZED LATIN SMALL LETTER A..CIRCLED LATIN SMALL LETTER Z
		{ 0x24EA, 0x24FF, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// CIRCLED DIGIT ZERO..NEGATIVE CIRCLED DIGIT ZERO
		{ 0x2500, 0x25B6, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// BOX DRAWINGS LIGHT HORIZONTAL..BLACK RIGHT-POINTING TRIANGLE
		{ 0x25B7, 0x25B7, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// WHITE RIGHT-POINTING TRIANGLE
		{ 0x25B8, 0x25C0, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// BLACK RIGHT-POINTING SMALL TRIANGLE..BLACK LEFT-POINTING TRIANGLE
		{ 0x25C1, 0x25C1, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// WHITE LEFT-POINTING TRIANGLE
		{ 0x25C2, 0x25F7, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// BLACK LEFT-POINTING SMALL TRIANGLE..WHITE CIRCLE WITH UPPER RIGHT QUADRANT
		{ 0x25F8, 0x25FF, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// UPPER LEFT TRIANGLE..LOWER RIGHT TRIANGLE
		{ 0x2600, 0x266E, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// BLACK SUN WITH RAYS..MUSIC NATURAL SIGN
		{ 0x266F, 0x266F, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// MUSIC SHARP SIGN
		{ 0x2670, 0x26AB, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// WEST SYRIAC CROSS..MEDIUM BLACK CIRCLE
		{ 0x26AC, 0x26AC, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// MEDIUM SMALL WHITE CIRCLE
		{ 0x26AD, 0x2767, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// MARRIAGE SYMBOL..ROTATED FLORAL HEART BULLET
		{ 0x2768, 0x2768, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// MEDIUM LEFT PARENTHESIS ORNAMENT
		{ 0x2769, 0x2769, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// MEDIUM RIGHT PARENTHESIS ORNAMENT
		{ 0x276A, 0x276A, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// MEDIUM FLATTENED LEFT PARENTHESIS ORNAMENT
		{ 0x276B, 0x276B, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// MEDIUM FLATTENED RIGHT PARENTHESIS ORNAMENT
		{ 0x276C, 0x276C, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// MEDIUM LEFT-POINTING ANGLE BRACKET ORNAMENT
		{ 0x276D, 0x276D, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// MEDIUM RIGHT-POINTING ANGLE BRACKET ORNAMENT
		{ 0x276E, 0x276E, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// HEAVY LEFT-POINTING ANGLE QUOTATION MARK ORNAMENT
		{ 0x276F, 0x276F, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// HEAVY RIGHT-POINTING ANGLE QUOTATION MARK ORNAMENT
		{ 0x2770, 0x2770, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// HEAVY LEFT-POINTING ANGLE BRACKET ORNAMENT
		{ 0x2771, 0x2771, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// HEAVY RIGHT-POINTING ANGLE BRACKET ORNAMENT
		{ 0x2772, 0x2772, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LIGHT LEFT TORTOISE SHELL BRACKET ORNAMENT
		{ 0x2773, 0x2773, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// LIGHT RIGHT TORTOISE SHELL BRACKET ORNAMENT
		{ 0x2774, 0x2774, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// MEDIUM LEFT CURLY BRACKET ORNAMENT
		{ 0x2775, 0x2775, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// MEDIUM RIGHT CURLY BRACKET ORNAMENT
		{ 0x2776, 0x2793, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// DINGBAT NEGATIVE CIRCLED DIGIT ONE..DINGBAT NEGATIVE CIRCLED SANS-SERIF NUMBER TEN
		{ 0x2794, 0x27BF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// HEAVY WIDE-HEADED RIGHTWARDS ARROW..DOUBLE CURLY LOOP
		{ 0x27C0, 0x27C4, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// THREE DIMENSIONAL ANGLE..OPEN SUPERSET
		{ 0x27C5, 0x27C5, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT S-SHAPED BAG DELIMITER
		{ 0x27C6, 0x27C6, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT S-SHAPED BAG DELIMITER
		{ 0x27C7, 0x27E5, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// OR WITH DOT INSIDE..WHITE SQUARE WITH RIGHTWARDS TICK
		{ 0x27E6, 0x27E6, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// MATHEMATICAL LEFT WHITE SQUARE BRACKET
		{ 0x27E7, 0x27E7, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// MATHEMATICAL RIGHT WHITE SQUARE BRACKET
		{ 0x27E8, 0x27E8, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// MATHEMATICAL LEFT ANGLE BRACKET
		{ 0x27E9, 0x27E9, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// MATHEMATICAL RIGHT ANGLE BRACKET
		{ 0x27EA, 0x27EA, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// MATHEMATICAL LEFT DOUBLE ANGLE BRACKET
		{ 0x27EB, 0x27EB, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// MATHEMATICAL RIGHT DOUBLE ANGLE BRACKET
		{ 0x27EC, 0x27EC, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// MATHEMATICAL LEFT WHITE TORTOISE SHELL BRACKET
		{ 0x27ED, 0x27ED, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// MATHEMATICAL RIGHT WHITE TORTOISE SHELL BRACKET
		{ 0x27EE, 0x27EE, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// MATHEMATICAL LEFT FLATTENED PARENTHESIS
		{ 0x27EF, 0x27EF, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// MATHEMATICAL RIGHT FLATTENED PARENTHESIS
		{ 0x27F0, 0x27FF, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// UPWARDS QUADRUPLE ARROW..LONG RIGHTWARDS SQUIGGLE ARROW
		{ 0x2800, 0x28FF, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// BRAILLE PATTERN BLANK..BRAILLE PATTERN DOTS-12345678
		{ 0x2900, 0x2982, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// RIGHTWARDS TWO-HEADED ARROW WITH VERTICAL STROKE..Z NOTATION TYPE COLON
		{ 0x2983, 0x2983, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT WHITE CURLY BRACKET
		{ 0x2984, 0x2984, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT WHITE CURLY BRACKET
		{ 0x2985, 0x2985, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT WHITE PARENTHESIS
		{ 0x2986, 0x2986, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT WHITE PARENTHESIS
		{ 0x2987, 0x2987, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// Z NOTATION LEFT IMAGE BRACKET
		{ 0x2988, 0x2988, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// Z NOTATION RIGHT IMAGE BRACKET
		{ 0x2989, 0x2989, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// Z NOTATION LEFT BINDING BRACKET
		{ 0x298A, 0x298A, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// Z NOTATION RIGHT BINDING BRACKET
		{ 0x298B, 0x298B, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT SQUARE BRACKET WITH UNDERBAR
		{ 0x298C, 0x298C, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT SQUARE BRACKET WITH UNDERBAR
		{ 0x298D, 0x298D, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT SQUARE BRACKET WITH TICK IN TOP CORNER
		{ 0x298E, 0x298E, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT SQUARE BRACKET WITH TICK IN BOTTOM CORNER
		{ 0x298F, 0x298F, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT SQUARE BRACKET WITH TICK IN BOTTOM CORNER
		{ 0x2990, 0x2990, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT SQUARE BRACKET WITH TICK IN TOP CORNER
		{ 0x2991, 0x2991, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT ANGLE BRACKET WITH DOT
		{ 0x2992, 0x2992, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT ANGLE BRACKET WITH DOT
		{ 0x2993, 0x2993, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT ARC LESS-THAN BRACKET
		{ 0x2994, 0x2994, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT ARC GREATER-THAN BRACKET
		{ 0x2995, 0x2995, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// DOUBLE LEFT ARC GREATER-THAN BRACKET
		{ 0x2996, 0x2996, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// DOUBLE RIGHT ARC LESS-THAN BRACKET
		{ 0x2997, 0x2997, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT BLACK TORTOISE SHELL BRACKET
		{ 0x2998, 0x2998, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT BLACK TORTOISE SHELL BRACKET
		{ 0x2999, 0x29D7, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// DOTTED FENCE..BLACK HOURGLASS
		{ 0x29D8, 0x29D8, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT WIGGLY FENCE
		{ 0x29D9, 0x29D9, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT WIGGLY FENCE
		{ 0x29DA, 0x29DA, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT DOUBLE WIGGLY FENCE
		{ 0x29DB, 0x29DB, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT DOUBLE WIGGLY FENCE
		{ 0x29DC, 0x29FB, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// INCOMPLETE INFINITY..TRIPLE PLUS
		{ 0x29FC, 0x29FC, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT-POINTING CURVED ANGLE BRACKET
		{ 0x29FD, 0x29FD, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT-POINTING CURVED ANGLE BRACKET
		{ 0x29FE, 0x2AFF, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// TINY..N-ARY WHITE VERTICAL BAR
		{ 0x2B00, 0x2B2F, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// NORTH EAST WHITE ARROW..WHITE VERTICAL ELLIPSE
		{ 0x2B30, 0x2B44, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// LEFT ARROW WITH SMALL CIRCLE..RIGHTWARDS ARROW THROUGH SUPERSET
		{ 0x2B45, 0x2B46, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// LEFTWARDS QUADRUPLE ARROW..RIGHTWARDS QUADRUPLE ARROW
		{ 0x2B47, 0x2B4C, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// REVERSE TILDE OPERATOR ABOVE RIGHTWARDS ARROW..RIGHTWARDS ARROW ABOVE REVERSE TILDE OPERATOR
		{ 0x2B4D, 0x2B73, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// DOWNWARDS TRIANGLE-HEADED ZIGZAG ARROW..DOWNWARDS TRIANGLE-HEADED ARROW TO BAR
		{ 0x2B76, 0x2BFF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// NORTH WEST TRIANGLE-HEADED ARROW TO BAR..HELLSCHREIBER PAUSE SYMBOL
		{ 0x2C00, 0x2C7B, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GLAGOLITIC CAPITAL LETTER AZU..LATIN LETTER SMALL CAPITAL TURNED E
		{ 0x2C7C, 0x2C7D, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// LATIN SUBSCRIPT SMALL LETTER J..MODIFIER LETTER CAPITAL V
		{ 0x2C7E, 0x2CE4, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN CAPITAL LETTER S WITH SWASH TAIL..COPTIC SYMBOL KAI
		{ 0x2CE5, 0x2CEA, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// COPTIC SYMBOL MI RO..COPTIC SYMBOL SHIMA SIMA
		{ 0x2CEB, 0x2CEE, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// COPTIC CAPITAL LETTER CRYPTOGRAMMIC SHEI..COPTIC SMALL LETTER CRYPTOGRAMMIC GANGIA
		{ 0x2CEF, 0x2CF1, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COPTIC COMBINING NI ABOVE..COPTIC COMBINING SPIRITUS LENIS
		{ 0x2CF2, 0x2CF3, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// COPTIC CAPITAL LETTER BOHAIRIC KHEI..COPTIC SMALL LETTER BOHAIRIC KHEI
		{ 0x2CF9, 0x2CFC, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// COPTIC OLD NUBIAN FULL STOP..COPTIC OLD NUBIAN VERSE DIVIDER
		{ 0x2CFD, 0x2CFD, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// COPTIC FRACTION ONE HALF
		{ 0x2CFE, 0x2CFF, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// COPTIC FULL STOP..COPTIC MORPHOLOGICAL DIVIDER
		{ 0x2D00, 0x2D25, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GEORGIAN SMALL LETTER AN..GEORGIAN SMALL LETTER HOE
		{ 0x2D27, 0x2D27, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GEORGIAN SMALL LETTER YN
		{ 0x2D2D, 0x2D2D, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// GEORGIAN SMALL LETTER AEN
		{ 0x2D30, 0x2D67, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TIFINAGH LETTER YA..TIFINAGH LETTER YO
		{ 0x2D6F, 0x2D6F, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// TIFINAGH MODIFIER LETTER LABIALIZATION MARK
		{ 0x2D70, 0x2D70, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TIFINAGH SEPARATOR MARK
		{ 0x2D7F, 0x2D7F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIFINAGH CONSONANT JOINER
		{ 0x2D80, 0x2D96, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE LOA..ETHIOPIC SYLLABLE GGWE
		{ 0x2DA0, 0x2DA6, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE SSA..ETHIOPIC SYLLABLE SSO
		{ 0x2DA8, 0x2DAE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE CCA..ETHIOPIC SYLLABLE CCO
		{ 0x2DB0, 0x2DB6, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE ZZA..ETHIOPIC SYLLABLE ZZO
		{ 0x2DB8, 0x2DBE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE CCHA..ETHIOPIC SYLLABLE CCHO
		{ 0x2DC0, 0x2DC6, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE QYA..ETHIOPIC SYLLABLE QYO
		{ 0x2DC8, 0x2DCE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE KYA..ETHIOPIC SYLLABLE KYO
		{ 0x2DD0, 0x2DD6, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE XYA..ETHIOPIC SYLLABLE XYO
		{ 0x2DD8, 0x2DDE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE GYA..ETHIOPIC SYLLABLE GYO
		{ 0x2DE0, 0x2DFF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING CYRILLIC LETTER BE..COMBINING CYRILLIC LETTER IOTIFIED BIG YUS
		{ 0x2E00, 0x2E01, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// RIGHT ANGLE SUBSTITUTION MARKER..RIGHT ANGLE DOTTED SUBSTITUTION MARKER
		{ 0x2E02, 0x2E02, BidiClass::OtherNeutral, GeneralCategory::InitialPunctuation },	// LEFT SUBSTITUTION BRACKET
		{ 0x2E03, 0x2E03, BidiClass::OtherNeutral, GeneralCategory::FinalPunctuation },	// RIGHT SUBSTITUTION BRACKET
		{ 0x2E04, 0x2E04, BidiClass::OtherNeutral, GeneralCategory::InitialPunctuation },	// LEFT DOTTED SUBSTITUTION BRACKET
		{ 0x2E05, 0x2E05, BidiClass::OtherNeutral, GeneralCategory::FinalPunctuation },	// RIGHT DOTTED SUBSTITUTION BRACKET
		{ 0x2E06, 0x2E08, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// RAISED INTERPOLATION MARKER..DOTTED TRANSPOSITION MARKER
		{ 0x2E09, 0x2E09, BidiClass::OtherNeutral, GeneralCategory::InitialPunctuation },	// LEFT TRANSPOSITION BRACKET
		{ 0x2E0A, 0x2E0A, BidiClass::OtherNeutral, GeneralCategory::FinalPunctuation },	// RIGHT TRANSPOSITION BRACKET
		{ 0x2E0B, 0x2E0B, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// RAISED SQUARE
		{ 0x2E0C, 0x2E0C, BidiClass::OtherNeutral, GeneralCategory::InitialPunctuation },	// LEFT RAISED OMISSION BRACKET
		{ 0x2E0D, 0x2E0D, BidiClass::OtherNeutral, GeneralCategory::FinalPunctuation },	// RIGHT RAISED OMISSION BRACKET
		{ 0x2E0E, 0x2E16, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// EDITORIAL CORONIS..DOTTED RIGHT-POINTING ANGLE
		{ 0x2E17, 0x2E17, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// DOUBLE OBLIQUE HYPHEN
		{ 0x2E18, 0x2E19, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// INVERTED INTERROBANG..PALM BRANCH
		{ 0x2E1A, 0x2E1A, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// HYPHEN WITH DIAERESIS
		{ 0x2E1B, 0x2E1B, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// TILDE WITH RING ABOVE
		{ 0x2E1C, 0x2E1C, BidiClass::OtherNeutral, GeneralCategory::InitialPunctuation },	// LEFT LOW PARAPHRASE BRACKET
		{ 0x2E1D, 0x2E1D, BidiClass::OtherNeutral, GeneralCategory::FinalPunctuation },	// RIGHT LOW PARAPHRASE BRACKET
		{ 0x2E1E, 0x2E1F, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// TILDE WITH DOT ABOVE..TILDE WITH DOT BELOW
		{ 0x2E20, 0x2E20, BidiClass::OtherNeutral, GeneralCategory::InitialPunctuation },	// LEFT VERTICAL BAR WITH QUILL
		{ 0x2E21, 0x2E21, BidiClass::OtherNeutral, GeneralCategory::FinalPunctuation },	// RIGHT VERTICAL BAR WITH QUILL
		{ 0x2E22, 0x2E22, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// TOP LEFT HALF BRACKET
		{ 0x2E23, 0x2E23, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// TOP RIGHT HALF BRACKET
		{ 0x2E24, 0x2E24, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// BOTTOM LEFT HALF BRACKET
		{ 0x2E25, 0x2E25, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// BOTTOM RIGHT HALF BRACKET
		{ 0x2E26, 0x2E26, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT SIDEWAYS U BRACKET
		{ 0x2E27, 0x2E27, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT SIDEWAYS U BRACKET
		{ 0x2E28, 0x2E28, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT DOUBLE PARENTHESIS
		{ 0x2E29, 0x2E29, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT DOUBLE PARENTHESIS
		{ 0x2E2A, 0x2E2E, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// TWO DOTS OVER ONE DOT PUNCTUATION..REVERSED QUESTION MARK
		{ 0x2E2F, 0x2E2F, BidiClass::OtherNeutral, GeneralCategory::ModifierLetter },	// VERTICAL TILDE
		{ 0x2E30, 0x2E39, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// RING POINT..TOP HALF SECTION SIGN
		{ 0x2E3A, 0x2E3B, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// TWO-EM DASH..THREE-EM DASH
		{ 0x2E3C, 0x2E3F, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// STENOGRAPHIC FULL STOP..CAPITULUM
		{ 0x2E40, 0x2E40, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// DOUBLE HYPHEN
		{ 0x2E41, 0x2E41, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// REVERSED COMMA
		{ 0x2E42, 0x2E42, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// DOUBLE LOW-REVERSED-9 QUOTATION MARK
		{ 0x2E43, 0x2E4F, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// DASH WITH LEFT UPTURN..CORNISH VERSE DIVIDER
		{ 0x2E50, 0x2E51, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// CROSS PATTY WITH RIGHT CROSSBAR..CROSS PATTY WITH LEFT CROSSBAR
		{ 0x2E52, 0x2E54, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// TIRONIAN SIGN CAPITAL ET..MEDIEVAL QUESTION MARK
		{ 0x2E55, 0x2E55, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT SQUARE BRACKET WITH STROKE
		{ 0x2E56, 0x2E56, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT SQUARE BRACKET WITH STROKE
		{ 0x2E57, 0x2E57, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT SQUARE BRACKET WITH DOUBLE STROKE
		{ 0x2E58, 0x2E58, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT SQUARE BRACKET WITH DOUBLE STROKE
		{ 0x2E59, 0x2E59, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// TOP HALF LEFT PARENTHESIS
		{ 0x2E5A, 0x2E5A, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// TOP HALF RIGHT PARENTHESIS
		{ 0x2E5B, 0x2E5B, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// BOTTOM HALF LEFT PARENTHESIS
		{ 0x2E5C, 0x2E5C, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// BOTTOM HALF RIGHT PARENTHESIS
		{ 0x2E5D, 0x2E5D, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// OBLIQUE HYPHEN
		{ 0x2E80, 0x2E99, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// CJK RADICAL REPEAT..CJK RADICAL RAP
		{ 0x2E9B, 0x2EF3, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// CJK RADICAL CHOKE..CJK RADICAL C-SIMPLIFIED TURTLE
		{ 0x2F00, 0x2FD5, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// KANGXI RADICAL ONE..KANGXI RADICAL FLUTE
		{ 0x2FF0, 0x2FFF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// IDEOGRAPHIC DESCRIPTION CHARACTER LEFT TO RIGHT..IDEOGRAPHIC DESCRIPTION CHARACTER ROTATION
		{ 0x3000, 0x3000, BidiClass::WhiteSpace, GeneralCategory::SpaceSeparator },	// IDEOGRAPHIC SPACE
		{ 0x3001, 0x3003, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// IDEOGRAPHIC COMMA..DITTO MARK
		{ 0x3004, 0x3004, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// JAPANESE INDUSTRIAL STANDARD SYMBOL
		{ 0x3005, 0x3005, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// IDEOGRAPHIC ITERATION MARK
		{ 0x3006, 0x3006, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// IDEOGRAPHIC CLOSING MARK
		{ 0x3007, 0x3007, BidiClass::LeftToRight, GeneralCategory::LetterNumber },	// IDEOGRAPHIC NUMBER ZERO
		{ 0x3008, 0x3008, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT ANGLE BRACKET
		{ 0x3009, 0x3009, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT ANGLE BRACKET
		{ 0x300A, 0x300A, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT DOUBLE ANGLE BRACKET
		{ 0x300B, 0x300B, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT DOUBLE ANGLE BRACKET
		{ 0x300C, 0x300C, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT CORNER BRACKET
		{ 0x300D, 0x300D, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT CORNER BRACKET
		{ 0x300E, 0x300E, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT WHITE CORNER BRACKET
		{ 0x300F, 0x300F, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT WHITE CORNER BRACKET
		{ 0x3010, 0x3010, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT BLACK LENTICULAR BRACKET
		{ 0x3011, 0x3011, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT BLACK LENTICULAR BRACKET
		{ 0x3012, 0x3013, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// POSTAL MARK..GETA MARK
		{ 0x3014, 0x3014, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT TORTOISE SHELL BRACKET
		{ 0x3015, 0x3015, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT TORTOISE SHELL BRACKET
		{ 0x3016, 0x3016, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT WHITE LENTICULAR BRACKET
		{ 0x3017, 0x3017, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT WHITE LENTICULAR BRACKET
		{ 0x3018, 0x3018, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT WHITE TORTOISE SHELL BRACKET
		{ 0x3019, 0x3019, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT WHITE TORTOISE SHELL BRACKET
		{ 0x301A, 0x301A, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// LEFT WHITE SQUARE BRACKET
		{ 0x301B, 0x301B, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// RIGHT WHITE SQUARE BRACKET
		{ 0x301C, 0x301C, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// WAVE DASH
		{ 0x301D, 0x301D, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// REVERSED DOUBLE PRIME QUOTATION MARK
		{ 0x301E, 0x301F, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// DOUBLE PRIME QUOTATION MARK..LOW DOUBLE PRIME QUOTATION MARK
		{ 0x3020, 0x3020, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// POSTAL MARK FACE
		{ 0x3021, 0x3029, BidiClass::LeftToRight, GeneralCategory::LetterNumber },	// HANGZHOU NUMERAL ONE..HANGZHOU NUMERAL NINE
		{ 0x302A, 0x302D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// IDEOGRAPHIC LEVEL TONE MARK..IDEOGRAPHIC ENTERING TONE MARK
		{ 0x302E, 0x302F, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// HANGUL SINGLE DOT TONE MARK..HANGUL DOUBLE DOT TONE MARK
		{ 0x3030, 0x3030, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// WAVY DASH
		{ 0x3031, 0x3035, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// VERTICAL KANA REPEAT MARK..VERTICAL KANA REPEAT MARK LOWER HALF
		{ 0x3036, 0x3037, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// CIRCLED POSTAL MARK..IDEOGRAPHIC TELEGRAPH LINE FEED SEPARATOR SYMBOL
		{ 0x3038, 0x303A, BidiClass::LeftToRight, GeneralCategory::LetterNumber },	// HANGZHOU NUMERAL TEN..HANGZHOU NUMERAL THIRTY
		{ 0x303B, 0x303B, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// VERTICAL IDEOGRAPHIC ITERATION MARK
		{ 0x303C, 0x303C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MASU MARK
		{ 0x303D, 0x303D, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// PART ALTERNATION MARK
		{ 0x303E, 0x303F, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// IDEOGRAPHIC VARIATION INDICATOR..IDEOGRAPHIC HALF FILL SPACE
		{ 0x3041, 0x3096, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HIRAGANA LETTER SMALL A..HIRAGANA LETTER SMALL KE
		{ 0x3099, 0x309A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING KATAKANA-HIRAGANA VOICED SOUND MARK..COMBINING KATAKANA-HIRAGANA SEMI-VOICED SOUND MARK
		{ 0x309B, 0x309C, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// KATAKANA-HIRAGANA VOICED SOUND MARK..KATAKANA-HIRAGANA SEMI-VOICED SOUND MARK
		{ 0x309D, 0x309E, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// HIRAGANA ITERATION MARK..HIRAGANA VOICED ITERATION MARK
		{ 0x309F, 0x309F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HIRAGANA DIGRAPH YORI
		{ 0x30A0, 0x30A0, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// KATAKANA-HIRAGANA DOUBLE HYPHEN
		{ 0x30A1, 0x30FA, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KATAKANA LETTER SMALL A..KATAKANA LETTER VO
		{ 0x30FB, 0x30FB, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// KATAKANA MIDDLE DOT
		{ 0x30FC, 0x30FE, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// KATAKANA-HIRAGANA PROLONGED SOUND MARK..KATAKANA VOICED ITERATION MARK
		{ 0x30FF, 0x30FF, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KATAKANA DIGRAPH KOTO
		{ 0x3105, 0x312F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BOPOMOFO LETTER B..BOPOMOFO LETTER NN
		{ 0x3131, 0x318E, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HANGUL LETTER KIYEOK..HANGUL LETTER ARAEAE
		{ 0x3190, 0x3191, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// IDEOGRAPHIC ANNOTATION LINKING MARK..IDEOGRAPHIC ANNOTATION REVERSE MARK
		{ 0x3192, 0x3195, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// IDEOGRAPHIC ANNOTATION ONE MARK..IDEOGRAPHIC ANNOTATION FOUR MARK
		{ 0x3196, 0x319F, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// IDEOGRAPHIC ANNOTATION TOP MARK..IDEOGRAPHIC ANNOTATION MAN MARK
		{ 0x31A0, 0x31BF, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BOPOMOFO LETTER BU..BOPOMOFO LETTER AH
		{ 0x31C0, 0x31E5, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// CJK STROKE T..CJK STROKE SZP
		{ 0x31EF, 0x31EF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// IDEOGRAPHIC DESCRIPTION CHARACTER SUBTRACTION
		{ 0x31F0, 0x31FF, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KATAKANA LETTER SMALL KU..KATAKANA LETTER SMALL RO
		{ 0x3200, 0x321C, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// PARENTHESIZED HANGUL KIYEOK..PARENTHESIZED HANGUL CIEUC U
		{ 0x321D, 0x321E, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// PARENTHESIZED KOREAN CHARACTER OJEON..PARENTHESIZED KOREAN CHARACTER O HU
		{ 0x3220, 0x3229, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// PARENTHESIZED IDEOGRAPH ONE..PARENTHESIZED IDEOGRAPH TEN
		{ 0x322A, 0x3247, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// PARENTHESIZED IDEOGRAPH MOON..CIRCLED IDEOGRAPH KOTO
		{ 0x3248, 0x324F, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// CIRCLED NUMBER TEN ON BLACK SQUARE..CIRCLED NUMBER EIGHTY ON BLACK SQUARE
		{ 0x3250, 0x3250, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// PARTNERSHIP SIGN
		{ 0x3251, 0x325F, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// CIRCLED NUMBER TWENTY ONE..CIRCLED NUMBER THIRTY FIVE
		{ 0x3260, 0x327B, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// CIRCLED HANGUL KIYEOK..CIRCLED HANGUL HIEUH A
		{ 0x327C, 0x327E, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// CIRCLED KOREAN CHARACTER CHAMKO..CIRCLED HANGUL IEUNG U
		{ 0x327F, 0x327F, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// KOREAN STANDARD SYMBOL
		{ 0x3280, 0x3289, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// CIRCLED IDEOGRAPH ONE..CIRCLED IDEOGRAPH TEN
		{ 0x328A, 0x32B0, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// CIRCLED IDEOGRAPH MOON..CIRCLED IDEOGRAPH NIGHT
		{ 0x32B1, 0x32BF, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// CIRCLED NUMBER THIRTY SIX..CIRCLED NUMBER FIFTY
		{ 0x32C0, 0x32CB, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// IDEOGRAPHIC TELEGRAPH SYMBOL FOR JANUARY..IDEOGRAPHIC TELEGRAPH SYMBOL FOR DECEMBER
		{ 0x32CC, 0x32CF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// SQUARE HG..LIMITED LIABILITY SIGN
		{ 0x32D0, 0x3376, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// CIRCLED KATAKANA A..SQUARE PC
		{ 0x3377, 0x337A, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// SQUARE DM..SQUARE IU
		{ 0x337B, 0x33DD, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// SQUARE ERA NAME HEISEI..SQUARE WB
		{ 0x33DE, 0x33DF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// SQUARE V OVER M..SQUARE A OVER M
		{ 0x33E0, 0x33FE, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// IDEOGRAPHIC TELEGRAPH SYMBOL FOR DAY ONE..IDEOGRAPHIC TELEGRAPH SYMBOL FOR DAY THIRTY-ONE
		{ 0x33FF, 0x33FF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// SQUARE GAL
		{ 0x3400, 0x4DBF, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CJK UNIFIED IDEOGRAPH-3400..CJK UNIFIED IDEOGRAPH-4DBF
		{ 0x4DC0, 0x4DFF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// HEXAGRAM FOR THE CREATIVE HEAVEN..HEXAGRAM FOR BEFORE COMPLETION
		{ 0x4E00, 0xA014, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CJK UNIFIED IDEOGRAPH-4E00..YI SYLLABLE E
		{ 0xA015, 0xA015, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// YI SYLLABLE WU
		{ 0xA016, 0xA48C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// YI SYLLABLE BIT..YI SYLLABLE YYR
		{ 0xA490, 0xA4C6, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// YI RADICAL QOT..YI RADICAL KE
		{ 0xA4D0, 0xA4F7, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LISU LETTER BA..LISU LETTER OE
		{ 0xA4F8, 0xA4FD, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// LISU LETTER TONE MYA TI..LISU LETTER TONE MYA JEU
		{ 0xA4FE, 0xA4FF, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// LISU PUNCTUATION COMMA..LISU PUNCTUATION FULL STOP
		{ 0xA500, 0xA60B, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// VAI SYLLABLE EE..VAI SYLLABLE NG
		{ 0xA60C, 0xA60C, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// VAI SYLLABLE LENGTHENER
		{ 0xA60D, 0xA60F, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// VAI COMMA..VAI QUESTION MARK
		{ 0xA610, 0xA61F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// VAI SYLLABLE NDOLE FA..VAI SYMBOL JONG
		{ 0xA620, 0xA629, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// VAI DIGIT ZERO..VAI DIGIT NINE
		{ 0xA62A, 0xA62B, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// VAI SYLLABLE NDOLE MA..VAI SYLLABLE NDOLE DO
		{ 0xA640, 0xA66D, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// CYRILLIC CAPITAL LETTER ZEMLYA..CYRILLIC SMALL LETTER DOUBLE MONOCULAR O
		{ 0xA66E, 0xA66E, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CYRILLIC LETTER MULTIOCULAR O
		{ 0xA66F, 0xA66F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING CYRILLIC VZMET
		{ 0xA670, 0xA672, BidiClass::NonspacingMark, GeneralCategory::EnclosingMark },	// COMBINING CYRILLIC TEN MILLIONS SIGN..COMBINING CYRILLIC THOUSAND MILLIONS SIGN
		{ 0xA673, 0xA673, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// SLAVONIC ASTERISK
		{ 0xA674, 0xA67D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING CYRILLIC LETTER UKRAINIAN IE..COMBINING CYRILLIC PAYEROK
		{ 0xA67E, 0xA67E, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// CYRILLIC KAVYKA
		{ 0xA67F, 0xA67F, BidiClass::OtherNeutral, GeneralCategory::ModifierLetter },	// CYRILLIC PAYEROK
		{ 0xA680, 0xA69B, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// CYRILLIC CAPITAL LETTER DWE..CYRILLIC SMALL LETTER CROSSED O
		{ 0xA69C, 0xA69D, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER CYRILLIC HARD SIGN..MODIFIER LETTER CYRILLIC SOFT SIGN
		{ 0xA69E, 0xA69F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING CYRILLIC LETTER EF..COMBINING CYRILLIC LETTER IOTIFIED E
		{ 0xA6A0, 0xA6E5, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BAMUM LETTER A..BAMUM LETTER KI
		{ 0xA6E6, 0xA6EF, BidiClass::LeftToRight, GeneralCategory::LetterNumber },	// BAMUM LETTER MO..BAMUM LETTER KOGHOM
		{ 0xA6F0, 0xA6F1, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BAMUM COMBINING MARK KOQNDON..BAMUM COMBINING MARK TUKWENTIS
		{ 0xA6F2, 0xA6F7, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// BAMUM NJAEMLI..BAMUM QUESTION MARK
		{ 0xA700, 0xA716, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// MODIFIER LETTER CHINESE TONE YIN PING..MODIFIER LETTER EXTRA-LOW LEFT-STEM TONE BAR
		{ 0xA717, 0xA71F, BidiClass::OtherNeutral, GeneralCategory::ModifierLetter },	// MODIFIER LETTER DOT VERTICAL BAR..MODIFIER LETTER LOW INVERTED EXCLAMATION MARK
		{ 0xA720, 0xA721, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// MODIFIER LETTER STRESS AND HIGH TONE..MODIFIER LETTER STRESS AND LOW TONE
		{ 0xA722, 0xA76F, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN CAPITAL LETTER EGYPTOLOGICAL ALEF..LATIN SMALL LETTER CON
		{ 0xA770, 0xA770, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER US
		{ 0xA771, 0xA787, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN SMALL LETTER DUM..LATIN SMALL LETTER INSULAR T
		{ 0xA788, 0xA788, BidiClass::OtherNeutral, GeneralCategory::ModifierLetter },	// MODIFIER LETTER LOW CIRCUMFLEX ACCENT
		{ 0xA789, 0xA78A, BidiClass::LeftToRight, GeneralCategory::ModifierSymbol },	// MODIFIER LETTER COLON..MODIFIER LETTER SHORT EQUALS SIGN
		{ 0xA78B, 0xA78E, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN CAPITAL LETTER SALTILLO..LATIN SMALL LETTER L WITH RETROFLEX HOOK AND BELT
		{ 0xA78F, 0xA78F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LATIN LETTER SINOLOGICAL DOT
		{ 0xA790, 0xA7DC, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN CAPITAL LETTER N WITH DESCENDER..LATIN CAPITAL LETTER LAMBDA WITH STROKE
		{ 0xA7F1, 0xA7F4, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER CAPITAL S..MODIFIER LETTER CAPITAL Q
		{ 0xA7F5, 0xA7F6, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN CAPITAL LETTER REVERSED HALF H..LATIN SMALL LETTER REVERSED HALF H
		{ 0xA7F7, 0xA7F7, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LATIN EPIGRAPHIC LETTER SIDEWAYS I
		{ 0xA7F8, 0xA7F9, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER CAPITAL H WITH STROKE..MODIFIER LETTER SMALL LIGATURE OE
		{ 0xA7FA, 0xA7FA, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN LETTER SMALL CAPITAL TURNED M
		{ 0xA7FB, 0xA801, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LATIN EPIGRAPHIC LETTER REVERSED F..SYLOTI NAGRI LETTER I
		{ 0xA802, 0xA802, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SYLOTI NAGRI SIGN DVISVARA
		{ 0xA803, 0xA805, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SYLOTI NAGRI LETTER U..SYLOTI NAGRI LETTER O
		{ 0xA806, 0xA806, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SYLOTI NAGRI SIGN HASANTA
		{ 0xA807, 0xA80A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SYLOTI NAGRI LETTER KO..SYLOTI NAGRI LETTER GHO
		{ 0xA80B, 0xA80B, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SYLOTI NAGRI SIGN ANUSVARA
		{ 0xA80C, 0xA822, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SYLOTI NAGRI LETTER CO..SYLOTI NAGRI LETTER HO
		{ 0xA823, 0xA824, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SYLOTI NAGRI VOWEL SIGN A..SYLOTI NAGRI VOWEL SIGN I
		{ 0xA825, 0xA826, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SYLOTI NAGRI VOWEL SIGN U..SYLOTI NAGRI VOWEL SIGN E
		{ 0xA827, 0xA827, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SYLOTI NAGRI VOWEL SIGN OO
		{ 0xA828, 0xA82B, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// SYLOTI NAGRI POETRY MARK-1..SYLOTI NAGRI POETRY MARK-4
		{ 0xA82C, 0xA82C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SYLOTI NAGRI SIGN ALTERNATE HASANTA
		{ 0xA830, 0xA835, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// NORTH INDIC FRACTION ONE QUARTER..NORTH INDIC FRACTION THREE SIXTEENTHS
		{ 0xA836, 0xA837, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// NORTH INDIC QUARTER MARK..NORTH INDIC PLACEHOLDER MARK
		{ 0xA838, 0xA838, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// NORTH INDIC RUPEE MARK
		{ 0xA839, 0xA839, BidiClass::EuropeanTerminator, GeneralCategory::OtherSymbol },	// NORTH INDIC QUANTITY MARK
		{ 0xA840, 0xA873, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// PHAGS-PA LETTER KA..PHAGS-PA LETTER CANDRABINDU
		{ 0xA874, 0xA877, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// PHAGS-PA SINGLE HEAD MARK..PHAGS-PA MARK DOUBLE SHAD
		{ 0xA880, 0xA881, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SAURASHTRA SIGN ANUSVARA..SAURASHTRA SIGN VISARGA
		{ 0xA882, 0xA8B3, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SAURASHTRA LETTER A..SAURASHTRA LETTER LLA
		{ 0xA8B4, 0xA8C3, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SAURASHTRA CONSONANT SIGN HAARU..SAURASHTRA VOWEL SIGN AU
		{ 0xA8C4, 0xA8C5, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SAURASHTRA SIGN VIRAMA..SAURASHTRA SIGN CANDRABINDU
		{ 0xA8CE, 0xA8CF, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// SAURASHTRA DANDA..SAURASHTRA DOUBLE DANDA
		{ 0xA8D0, 0xA8D9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// SAURASHTRA DIGIT ZERO..SAURASHTRA DIGIT NINE
		{ 0xA8E0, 0xA8F1, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING DEVANAGARI DIGIT ZERO..COMBINING DEVANAGARI SIGN AVAGRAHA
		{ 0xA8F2, 0xA8F7, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DEVANAGARI SIGN SPACING CANDRABINDU..DEVANAGARI SIGN CANDRABINDU AVAGRAHA
		{ 0xA8F8, 0xA8FA, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// DEVANAGARI SIGN PUSHPIKA..DEVANAGARI CARET
		{ 0xA8FB, 0xA8FB, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DEVANAGARI HEADSTROKE
		{ 0xA8FC, 0xA8FC, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// DEVANAGARI SIGN SIDDHAM
		{ 0xA8FD, 0xA8FE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DEVANAGARI JAIN OM..DEVANAGARI LETTER AY
		{ 0xA8FF, 0xA8FF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// DEVANAGARI VOWEL SIGN AY
		{ 0xA900, 0xA909, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// KAYAH LI DIGIT ZERO..KAYAH LI DIGIT NINE
		{ 0xA90A, 0xA925, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KAYAH LI LETTER KA..KAYAH LI LETTER OO
		{ 0xA926, 0xA92D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KAYAH LI VOWEL UE..KAYAH LI TONE CALYA PLOPHU
		{ 0xA92E, 0xA92F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// KAYAH LI SIGN CWI..KAYAH LI SIGN SHYA
		{ 0xA930, 0xA946, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// REJANG LETTER KA..REJANG LETTER A
		{ 0xA947, 0xA951, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// REJANG VOWEL SIGN I..REJANG CONSONANT SIGN R
		{ 0xA952, 0xA953, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// REJANG CONSONANT SIGN H..REJANG VIRAMA
		{ 0xA95F, 0xA95F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// REJANG SECTION MARK
		{ 0xA960, 0xA97C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HANGUL CHOSEONG TIKEUT-MIEUM..HANGUL CHOSEONG SSANGYEORINHIEUH
		{ 0xA980, 0xA982, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// JAVANESE SIGN PANYANGGA..JAVANESE SIGN LAYAR
		{ 0xA983, 0xA983, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// JAVANESE SIGN WIGNYAN
		{ 0xA984, 0xA9B2, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// JAVANESE LETTER A..JAVANESE LETTER HA
		{ 0xA9B3, 0xA9B3, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// JAVANESE SIGN CECAK TELU
		{ 0xA9B4, 0xA9B5, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// JAVANESE VOWEL SIGN TARUNG..JAVANESE VOWEL SIGN TOLONG
		{ 0xA9B6, 0xA9B9, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// JAVANESE VOWEL SIGN WULU..JAVANESE VOWEL SIGN SUKU MENDUT
		{ 0xA9BA, 0xA9BB, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// JAVANESE VOWEL SIGN TALING..JAVANESE VOWEL SIGN DIRGA MURE
		{ 0xA9BC, 0xA9BD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// JAVANESE VOWEL SIGN PEPET..JAVANESE CONSONANT SIGN KERET
		{ 0xA9BE, 0xA9C0, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// JAVANESE CONSONANT SIGN PENGKAL..JAVANESE PANGKON
		{ 0xA9C1, 0xA9CD, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// JAVANESE LEFT RERENGGAN..JAVANESE TURNED PADA PISELEH
		{ 0xA9CF, 0xA9CF, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// JAVANESE PANGRANGKEP
		{ 0xA9D0, 0xA9D9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// JAVANESE DIGIT ZERO..JAVANESE DIGIT NINE
		{ 0xA9DE, 0xA9DF, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// JAVANESE PADA TIRTA TUMETES..JAVANESE PADA ISEN-ISEN
		{ 0xA9E0, 0xA9E4, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER SHAN GHA..MYANMAR LETTER SHAN BHA
		{ 0xA9E5, 0xA9E5, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MYANMAR SIGN SHAN SAW
		{ 0xA9E6, 0xA9E6, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MYANMAR MODIFIER LETTER SHAN REDUPLICATION
		{ 0xA9E7, 0xA9EF, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER TAI LAING NYA..MYANMAR LETTER TAI LAING NNA
		{ 0xA9F0, 0xA9F9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// MYANMAR TAI LAING DIGIT ZERO..MYANMAR TAI LAING DIGIT NINE
		{ 0xA9FA, 0xA9FE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER TAI LAING LLA..MYANMAR LETTER TAI LAING BHA
		{ 0xAA00, 0xAA28, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CHAM LETTER A..CHAM LETTER HA
		{ 0xAA29, 0xAA2E, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// CHAM VOWEL SIGN AA..CHAM VOWEL SIGN OE
		{ 0xAA2F, 0xAA30, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// CHAM VOWEL SIGN O..CHAM VOWEL SIGN AI
		{ 0xAA31, 0xAA32, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// CHAM VOWEL SIGN AU..CHAM VOWEL SIGN UE
		{ 0xAA33, 0xAA34, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// CHAM CONSONANT SIGN YA..CHAM CONSONANT SIGN RA
		{ 0xAA35, 0xAA36, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// CHAM CONSONANT SIGN LA..CHAM CONSONANT SIGN WA
		{ 0xAA40, 0xAA42, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CHAM LETTER FINAL K..CHAM LETTER FINAL NG
		{ 0xAA43, 0xAA43, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// CHAM CONSONANT SIGN FINAL NG
		{ 0xAA44, 0xAA4B, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CHAM LETTER FINAL CH..CHAM LETTER FINAL SS
		{ 0xAA4C, 0xAA4C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// CHAM CONSONANT SIGN FINAL M
		{ 0xAA4D, 0xAA4D, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// CHAM CONSONANT SIGN FINAL H
		{ 0xAA50, 0xAA59, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// CHAM DIGIT ZERO..CHAM DIGIT NINE
		{ 0xAA5C, 0xAA5F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// CHAM PUNCTUATION SPIRAL..CHAM PUNCTUATION TRIPLE DANDA
		{ 0xAA60, 0xAA6F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER KHAMTI GA..MYANMAR LETTER KHAMTI FA
		{ 0xAA70, 0xAA70, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MYANMAR MODIFIER LETTER KHAMTI REDUPLICATION
		{ 0xAA71, 0xAA76, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER KHAMTI XA..MYANMAR LOGOGRAM KHAMTI HM
		{ 0xAA77, 0xAA79, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// MYANMAR SYMBOL AITON EXCLAMATION..MYANMAR SYMBOL AITON TWO
		{ 0xAA7A, 0xAA7A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER AITON RA
		{ 0xAA7B, 0xAA7B, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MYANMAR SIGN PAO KAREN TONE
		{ 0xAA7C, 0xAA7C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MYANMAR SIGN TAI LAING TONE-2
		{ 0xAA7D, 0xAA7D, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MYANMAR SIGN TAI LAING TONE-5
		{ 0xAA7E, 0xAAAF, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MYANMAR LETTER SHWE PALAUNG CHA..TAI VIET LETTER HIGH O
		{ 0xAAB0, 0xAAB0, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI VIET MAI KANG
		{ 0xAAB1, 0xAAB1, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI VIET VOWEL AA
		{ 0xAAB2, 0xAAB4, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI VIET VOWEL I..TAI VIET VOWEL U
		{ 0xAAB5, 0xAAB6, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI VIET VOWEL E..TAI VIET VOWEL O
		{ 0xAAB7, 0xAAB8, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI VIET MAI KHIT..TAI VIET VOWEL IA
		{ 0xAAB9, 0xAABD, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI VIET VOWEL UEA..TAI VIET VOWEL AN
		{ 0xAABE, 0xAABF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI VIET VOWEL AM..TAI VIET TONE MAI EK
		{ 0xAAC0, 0xAAC0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI VIET TONE MAI NUENG
		{ 0xAAC1, 0xAAC1, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI VIET TONE MAI THO
		{ 0xAAC2, 0xAAC2, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI VIET TONE MAI SONG
		{ 0xAADB, 0xAADC, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI VIET SYMBOL KON..TAI VIET SYMBOL NUENG
		{ 0xAADD, 0xAADD, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// TAI VIET SYMBOL SAM
		{ 0xAADE, 0xAADF, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TAI VIET SYMBOL HO HOI..TAI VIET SYMBOL KOI KOI
		{ 0xAAE0, 0xAAEA, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MEETEI MAYEK LETTER E..MEETEI MAYEK LETTER SSA
		{ 0xAAEB, 0xAAEB, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MEETEI MAYEK VOWEL SIGN II
		{ 0xAAEC, 0xAAED, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MEETEI MAYEK VOWEL SIGN UU..MEETEI MAYEK VOWEL SIGN AAI
		{ 0xAAEE, 0xAAEF, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MEETEI MAYEK VOWEL SIGN AU..MEETEI MAYEK VOWEL SIGN AAU
		{ 0xAAF0, 0xAAF1, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// MEETEI MAYEK CHEIKHAN..MEETEI MAYEK AHANG KHUDAM
		{ 0xAAF2, 0xAAF2, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MEETEI MAYEK ANJI
		{ 0xAAF3, 0xAAF4, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MEETEI MAYEK SYLLABLE REPETITION MARK..MEETEI MAYEK WORD REPETITION MARK
		{ 0xAAF5, 0xAAF5, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MEETEI MAYEK VOWEL SIGN VISARGA
		{ 0xAAF6, 0xAAF6, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MEETEI MAYEK VIRAMA
		{ 0xAB01, 0xAB06, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE TTHU..ETHIOPIC SYLLABLE TTHO
		{ 0xAB09, 0xAB0E, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE DDHU..ETHIOPIC SYLLABLE DDHO
		{ 0xAB11, 0xAB16, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE DZU..ETHIOPIC SYLLABLE DZO
		{ 0xAB20, 0xAB26, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE CCHHA..ETHIOPIC SYLLABLE CCHHO
		{ 0xAB28, 0xAB2E, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE BBA..ETHIOPIC SYLLABLE BBO
		{ 0xAB30, 0xAB5A, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN SMALL LETTER BARRED ALPHA..LATIN SMALL LETTER Y WITH SHORT RIGHT LEG
		{ 0xAB5B, 0xAB5B, BidiClass::LeftToRight, GeneralCategory::ModifierSymbol },	// MODIFIER BREVE WITH INVERTED BREVE
		{ 0xAB5C, 0xAB5F, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER SMALL HENG..MODIFIER LETTER SMALL U WITH LEFT HOOK
		{ 0xAB60, 0xAB68, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN SMALL LETTER SAKHA YAT..LATIN SMALL LETTER TURNED R WITH MIDDLE TILDE
		{ 0xAB69, 0xAB69, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER SMALL TURNED W
		{ 0xAB6A, 0xAB6B, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// MODIFIER LETTER LEFT TACK..MODIFIER LETTER RIGHT TACK
		{ 0xAB70, 0xABBF, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// CHEROKEE SMALL LETTER A..CHEROKEE SMALL LETTER YA
		{ 0xABC0, 0xABE2, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MEETEI MAYEK LETTER KOK..MEETEI MAYEK LETTER I LONSUM
		{ 0xABE3, 0xABE4, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MEETEI MAYEK VOWEL SIGN ONAP..MEETEI MAYEK VOWEL SIGN INAP
		{ 0xABE5, 0xABE5, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MEETEI MAYEK VOWEL SIGN ANAP
		{ 0xABE6, 0xABE7, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MEETEI MAYEK VOWEL SIGN YENAP..MEETEI MAYEK VOWEL SIGN SOUNAP
		{ 0xABE8, 0xABE8, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MEETEI MAYEK VOWEL SIGN UNAP
		{ 0xABE9, 0xABEA, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MEETEI MAYEK VOWEL SIGN CHEINAP..MEETEI MAYEK VOWEL SIGN NUNG
		{ 0xABEB, 0xABEB, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// MEETEI MAYEK CHEIKHEI
		{ 0xABEC, 0xABEC, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MEETEI MAYEK LUM IYEK
		{ 0xABED, 0xABED, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MEETEI MAYEK APUN IYEK
		{ 0xABF0, 0xABF9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// MEETEI MAYEK DIGIT ZERO..MEETEI MAYEK DIGIT NINE
		{ 0xAC00, 0xD7A3, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HANGUL SYLLABLE GA..HANGUL SYLLABLE HIH
		{ 0xD7B0, 0xD7C6, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HANGUL JUNGSEONG O-YEO..HANGUL JUNGSEONG ARAEA-E
		{ 0xD7CB, 0xD7FB, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HANGUL JONGSEONG NIEUN-RIEUL..HANGUL JONGSEONG PHIEUPH-THIEUTH
		{ 0xE000, 0xF8FF, BidiClass::LeftToRight, GeneralCategory::PrivateUse },	// <private-use-E000>..<private-use-F8FF>
		{ 0xF900, 0xFA6D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CJK COMPATIBILITY IDEOGRAPH-F900..CJK COMPATIBILITY IDEOGRAPH-FA6D
		{ 0xFA70, 0xFAD9, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CJK COMPATIBILITY IDEOGRAPH-FA70..CJK COMPATIBILITY IDEOGRAPH-FAD9
		{ 0xFB00, 0xFB06, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN SMALL LIGATURE FF..LATIN SMALL LIGATURE ST
		{ 0xFB13, 0xFB17, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// ARMENIAN SMALL LIGATURE MEN NOW..ARMENIAN SMALL LIGATURE MEN XEH
		{ 0xFB1D, 0xFB1D, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// HEBREW LETTER YOD WITH HIRIQ
		{ 0xFB1E, 0xFB1E, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// HEBREW POINT JUDEO-SPANISH VARIKA
		{ 0xFB1F, 0xFB28, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// HEBREW LIGATURE YIDDISH YOD YOD PATAH..HEBREW LETTER WIDE TAV
		{ 0xFB29, 0xFB29, BidiClass::EuropeanSeparator, GeneralCategory::MathSymbol },	// HEBREW LETTER ALTERNATIVE PLUS SIGN
		{ 0xFB2A, 0xFB36, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// HEBREW LETTER SHIN WITH SHIN DOT..HEBREW LETTER ZAYIN WITH DAGESH
		{ 0xFB38, 0xFB3C, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// HEBREW LETTER TET WITH DAGESH..HEBREW LETTER LAMED WITH DAGESH
		{ 0xFB3E, 0xFB3E, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// HEBREW LETTER MEM WITH DAGESH
		{ 0xFB40, 0xFB41, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// HEBREW LETTER NUN WITH DAGESH..HEBREW LETTER SAMEKH WITH DAGESH
		{ 0xFB43, 0xFB44, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// HEBREW LETTER FINAL PE WITH DAGESH..HEBREW LETTER PE WITH DAGESH
		{ 0xFB46, 0xFB4F, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// HEBREW LETTER TSADI WITH DAGESH..HEBREW LIGATURE ALEF LAMED
		{ 0xFB50, 0xFBB1, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER ALEF WASLA ISOLATED FORM..ARABIC LETTER YEH BARREE WITH HAMZA ABOVE FINAL FORM
		{ 0xFBB2, 0xFBC2, BidiClass::ArabicLetter, GeneralCategory::ModifierSymbol },	// ARABIC SYMBOL DOT ABOVE..ARABIC SYMBOL WASLA ABOVE
		{ 0xFBC3, 0xFBD2, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ARABIC LIGATURE JALLA WA-ALAA..ARABIC LIGATURE ALAYHI AR-RAHMAH
		{ 0xFBD3, 0xFD3D, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER NG ISOLATED FORM..ARABIC LIGATURE ALEF WITH FATHATAN ISOLATED FORM
		{ 0xFD3E, 0xFD3E, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// ORNATE LEFT PARENTHESIS
		{ 0xFD3F, 0xFD3F, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// ORNATE RIGHT PARENTHESIS
		{ 0xFD40, 0xFD4F, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ARABIC LIGATURE RAHIMAHU ALLAAH..ARABIC LIGATURE RAHIMAHUM ALLAAH
		{ 0xFD50, 0xFD8F, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LIGATURE TEH WITH JEEM WITH MEEM INITIAL FORM..ARABIC LIGATURE MEEM WITH KHAH WITH MEEM INITIAL FORM
		{ 0xFD90, 0xFD91, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ARABIC LIGATURE RAHMATU ALLAAHI ALAYH..ARABIC LIGATURE RAHMATU ALLAAHI ALAYHAA
		{ 0xFD92, 0xFDC7, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LIGATURE MEEM WITH JEEM WITH KHAH INITIAL FORM..ARABIC LIGATURE NOON WITH JEEM WITH YEH FINAL FORM
		{ 0xFDC8, 0xFDCF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ARABIC LIGATURE RAHIMAHU ALLAAH TAAALAA..ARABIC LIGATURE SALAAMUHU ALAYNAA
		{ 0xFDD0, 0xFDEF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-FDD0>..<noncharacter-FDEF>
		{ 0xFDF0, 0xFDFB, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LIGATURE SALLA USED AS KORANIC STOP SIGN ISOLATED FORM..ARABIC LIGATURE JALLAJALALOUHOU
		{ 0xFDFC, 0xFDFC, BidiClass::ArabicLetter, GeneralCategory::CurrencySymbol },	// RIAL SIGN
		{ 0xFDFD, 0xFDFF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ARABIC LIGATURE BISMILLAH AR-RAHMAN AR-RAHEEM..ARABIC LIGATURE AZZA WA JALL
		{ 0xFE00, 0xFE0F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// VARIATION SELECTOR-1..VARIATION SELECTOR-16
		{ 0xFE10, 0xFE16, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// PRESENTATION FORM FOR VERTICAL COMMA..PRESENTATION FORM FOR VERTICAL QUESTION MARK
		{ 0xFE17, 0xFE17, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT WHITE LENTICULAR BRACKET
		{ 0xFE18, 0xFE18, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT WHITE LENTICULAR BRAKCET
		{ 0xFE19, 0xFE19, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// PRESENTATION FORM FOR VERTICAL HORIZONTAL ELLIPSIS
		{ 0xFE20, 0xFE2F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING LIGATURE LEFT HALF..COMBINING CYRILLIC TITLO RIGHT HALF
		{ 0xFE30, 0xFE30, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// PRESENTATION FORM FOR VERTICAL TWO DOT LEADER
		{ 0xFE31, 0xFE32, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// PRESENTATION FORM FOR VERTICAL EM DASH..PRESENTATION FORM FOR VERTICAL EN DASH
		{ 0xFE33, 0xFE34, BidiClass::OtherNeutral, GeneralCategory::ConnectorPunctuation },	// PRESENTATION FORM FOR VERTICAL LOW LINE..PRESENTATION FORM FOR VERTICAL WAVY LOW LINE
		{ 0xFE35, 0xFE35, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT PARENTHESIS
		{ 0xFE36, 0xFE36, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT PARENTHESIS
		{ 0xFE37, 0xFE37, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT CURLY BRACKET
		{ 0xFE38, 0xFE38, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT CURLY BRACKET
		{ 0xFE39, 0xFE39, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT TORTOISE SHELL BRACKET
		{ 0xFE3A, 0xFE3A, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT TORTOISE SHELL BRACKET
		{ 0xFE3B, 0xFE3B, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT BLACK LENTICULAR BRACKET
		{ 0xFE3C, 0xFE3C, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT BLACK LENTICULAR BRACKET
		{ 0xFE3D, 0xFE3D, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT DOUBLE ANGLE BRACKET
		{ 0xFE3E, 0xFE3E, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT DOUBLE ANGLE BRACKET
		{ 0xFE3F, 0xFE3F, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT ANGLE BRACKET
		{ 0xFE40, 0xFE40, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT ANGLE BRACKET
		{ 0xFE41, 0xFE41, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT CORNER BRACKET
		{ 0xFE42, 0xFE42, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT CORNER BRACKET
		{ 0xFE43, 0xFE43, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT WHITE CORNER BRACKET
		{ 0xFE44, 0xFE44, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT WHITE CORNER BRACKET
		{ 0xFE45, 0xFE46, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// SESAME DOT..WHITE SESAME DOT
		{ 0xFE47, 0xFE47, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT SQUARE BRACKET
		{ 0xFE48, 0xFE48, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT SQUARE BRACKET
		{ 0xFE49, 0xFE4C, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// DASHED OVERLINE..DOUBLE WAVY OVERLINE
		{ 0xFE4D, 0xFE4F, BidiClass::OtherNeutral, GeneralCategory::ConnectorPunctuation },	// DASHED LOW LINE..WAVY LOW LINE
		{ 0xFE50, 0xFE50, BidiClass::CommonSeparator, GeneralCategory::OtherPunctuation },	// SMALL COMMA
		{ 0xFE51, 0xFE51, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// SMALL IDEOGRAPHIC COMMA
		{ 0xFE52, 0xFE52, BidiClass::CommonSeparator, GeneralCategory::OtherPunctuation },	// SMALL FULL STOP
		{ 0xFE54, 0xFE54, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// SMALL SEMICOLON
		{ 0xFE55, 0xFE55, BidiClass::CommonSeparator, GeneralCategory::OtherPunctuation },	// SMALL COLON
		{ 0xFE56, 0xFE57, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// SMALL QUESTION MARK..SMALL EXCLAMATION MARK
		{ 0xFE58, 0xFE58, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// SMALL EM DASH
		{ 0xFE59, 0xFE59, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// SMALL LEFT PARENTHESIS
		{ 0xFE5A, 0xFE5A, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// SMALL RIGHT PARENTHESIS
		{ 0xFE5B, 0xFE5B, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// SMALL LEFT CURLY BRACKET
		{ 0xFE5C, 0xFE5C, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// SMALL RIGHT CURLY BRACKET
		{ 0xFE5D, 0xFE5D, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// SMALL LEFT TORTOISE SHELL BRACKET
		{ 0xFE5E, 0xFE5E, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// SMALL RIGHT TORTOISE SHELL BRACKET
		{ 0xFE5F, 0xFE5F, BidiClass::EuropeanTerminator, GeneralCategory::OtherPunctuation },	// SMALL NUMBER SIGN
		{ 0xFE60, 0xFE61, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// SMALL AMPERSAND..SMALL ASTERISK
		{ 0xFE62, 0xFE62, BidiClass::EuropeanSeparator, GeneralCategory::MathSymbol },	// SMALL PLUS SIGN
		{ 0xFE63, 0xFE63, BidiClass::EuropeanSeparator, GeneralCategory::DashPunctuation },	// SMALL HYPHEN-MINUS
		{ 0xFE64, 0xFE66, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// SMALL LESS-THAN SIGN..SMALL EQUALS SIGN
		{ 0xFE68, 0xFE68, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// SMALL REVERSE SOLIDUS
		{ 0xFE69, 0xFE69, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// SMALL DOLLAR SIGN
		{ 0xFE6A, 0xFE6A, BidiClass::EuropeanTerminator, GeneralCategory::OtherPunctuation },	// SMALL PERCENT SIGN
		{ 0xFE6B, 0xFE6B, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// SMALL COMMERCIAL AT
		{ 0xFE70, 0xFE74, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC FATHATAN ISOLATED FORM..ARABIC KASRATAN ISOLATED FORM
		{ 0xFE76, 0xFEFC, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC FATHA ISOLATED FORM..ARABIC LIGATURE LAM WITH ALEF FINAL FORM
		{ 0xFEFF, 0xFEFF, BidiClass::BoundaryNeutral, GeneralCategory::Format },	// ZERO WIDTH NO-BREAK SPACE
		{ 0xFF01, 0xFF02, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// FULLWIDTH EXCLAMATION MARK..FULLWIDTH QUOTATION MARK
		{ 0xFF03, 0xFF03, BidiClass::EuropeanTerminator, GeneralCategory::OtherPunctuation },	// FULLWIDTH NUMBER SIGN
		{ 0xFF04, 0xFF04, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// FULLWIDTH DOLLAR SIGN
		{ 0xFF05, 0xFF05, BidiClass::EuropeanTerminator, GeneralCategory::OtherPunctuation },	// FULLWIDTH PERCENT SIGN
		{ 0xFF06, 0xFF07, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// FULLWIDTH AMPERSAND..FULLWIDTH APOSTROPHE
		{ 0xFF08, 0xFF08, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// FULLWIDTH LEFT PARENTHESIS
		{ 0xFF09, 0xFF09, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// FULLWIDTH RIGHT PARENTHESIS
		{ 0xFF0A, 0xFF0A, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// FULLWIDTH ASTERISK
		{ 0xFF0B, 0xFF0B, BidiClass::EuropeanSeparator, GeneralCategory::MathSymbol },	// FULLWIDTH PLUS SIGN
		{ 0xFF0C, 0xFF0C, BidiClass::CommonSeparator, GeneralCategory::OtherPunctuation },	// FULLWIDTH COMMA
		{ 0xFF0D, 0xFF0D, BidiClass::EuropeanSeparator, GeneralCategory::DashPunctuation },	// FULLWIDTH HYPHEN-MINUS
		{ 0xFF0E, 0xFF0F, BidiClass::CommonSeparator, GeneralCategory::OtherPunctuation },	// FULLWIDTH FULL STOP..FULLWIDTH SOLIDUS
		{ 0xFF10, 0xFF19, BidiClass::EuropeanNumber, GeneralCategory::DecimalNumber },	// FULLWIDTH DIGIT ZERO..FULLWIDTH DIGIT NINE
		{ 0xFF1A, 0xFF1A, BidiClass::CommonSeparator, GeneralCategory::OtherPunctuation },	// FULLWIDTH COLON
		{ 0xFF1B, 0xFF1B, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// FULLWIDTH SEMICOLON
		{ 0xFF1C, 0xFF1E, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// FULLWIDTH LESS-THAN SIGN..FULLWIDTH GREATER-THAN SIGN
		{ 0xFF1F, 0xFF20, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// FULLWIDTH QUESTION MARK..FULLWIDTH COMMERCIAL AT
		{ 0xFF21, 0xFF3A, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// FULLWIDTH LATIN CAPITAL LETTER A..FULLWIDTH LATIN CAPITAL LETTER Z
		{ 0xFF3B, 0xFF3B, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// FULLWIDTH LEFT SQUARE BRACKET
		{ 0xFF3C, 0xFF3C, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// FULLWIDTH REVERSE SOLIDUS
		{ 0xFF3D, 0xFF3D, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// FULLWIDTH RIGHT SQUARE BRACKET
		{ 0xFF3E, 0xFF3E, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// FULLWIDTH CIRCUMFLEX ACCENT
		{ 0xFF3F, 0xFF3F, BidiClass::OtherNeutral, GeneralCategory::ConnectorPunctuation },	// FULLWIDTH LOW LINE
		{ 0xFF40, 0xFF40, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// FULLWIDTH GRAVE ACCENT
		{ 0xFF41, 0xFF5A, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// FULLWIDTH LATIN SMALL LETTER A..FULLWIDTH LATIN SMALL LETTER Z
		{ 0xFF5B, 0xFF5B, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// FULLWIDTH LEFT CURLY BRACKET
		{ 0xFF5C, 0xFF5C, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// FULLWIDTH VERTICAL LINE
		{ 0xFF5D, 0xFF5D, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// FULLWIDTH RIGHT CURLY BRACKET
		{ 0xFF5E, 0xFF5E, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// FULLWIDTH TILDE
		{ 0xFF5F, 0xFF5F, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// FULLWIDTH LEFT WHITE PARENTHESIS
		{ 0xFF60, 0xFF60, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// FULLWIDTH RIGHT WHITE PARENTHESIS
		{ 0xFF61, 0xFF61, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// HALFWIDTH IDEOGRAPHIC FULL STOP
		{ 0xFF62, 0xFF62, BidiClass::OtherNeutral, GeneralCategory::OpenPunctuation },	// HALFWIDTH LEFT CORNER BRACKET
		{ 0xFF63, 0xFF63, BidiClass::OtherNeutral, GeneralCategory::ClosePunctuation },	// HALFWIDTH RIGHT CORNER BRACKET
		{ 0xFF64, 0xFF65, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// HALFWIDTH IDEOGRAPHIC COMMA..HALFWIDTH KATAKANA MIDDLE DOT
		{ 0xFF66, 0xFF6F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HALFWIDTH KATAKANA LETTER WO..HALFWIDTH KATAKANA LETTER SMALL TU
		{ 0xFF70, 0xFF70, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// HALFWIDTH KATAKANA-HIRAGANA PROLONGED SOUND MARK
		{ 0xFF71, 0xFF9D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HALFWIDTH KATAKANA LETTER A..HALFWIDTH KATAKANA LETTER N
		{ 0xFF9E, 0xFF9F, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// HALFWIDTH KATAKANA VOICED SOUND MARK..HALFWIDTH KATAKANA SEMI-VOICED SOUND MARK
		{ 0xFFA0, 0xFFBE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HALFWIDTH HANGUL FILLER..HALFWIDTH HANGUL LETTER HIEUH
		{ 0xFFC2, 0xFFC7, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HALFWIDTH HANGUL LETTER A..HALFWIDTH HANGUL LETTER E
		{ 0xFFCA, 0xFFCF, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HALFWIDTH HANGUL LETTER YEO..HALFWIDTH HANGUL LETTER OE
		{ 0xFFD2, 0xFFD7, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HALFWIDTH HANGUL LETTER YO..HALFWIDTH HANGUL LETTER YU
		{ 0xFFDA, 0xFFDC, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HALFWIDTH HANGUL LETTER EU..HALFWIDTH HANGUL LETTER I
		{ 0xFFE0, 0xFFE1, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// FULLWIDTH CENT SIGN..FULLWIDTH POUND SIGN
		{ 0xFFE2, 0xFFE2, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// FULLWIDTH NOT SIGN
		{ 0xFFE3, 0xFFE3, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// FULLWIDTH MACRON
		{ 0xFFE4, 0xFFE4, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// FULLWIDTH BROKEN BAR
		{ 0xFFE5, 0xFFE6, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// FULLWIDTH YEN SIGN..FULLWIDTH WON SIGN
		{ 0xFFE8, 0xFFE8, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// HALFWIDTH FORMS LIGHT VERTICAL
		{ 0xFFE9, 0xFFEC, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// HALFWIDTH LEFTWARDS ARROW..HALFWIDTH DOWNWARDS ARROW
		{ 0xFFED, 0xFFEE, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// HALFWIDTH BLACK SQUARE..HALFWIDTH WHITE CIRCLE
		{ 0xFFF0, 0xFFF8, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <reserved-FFF0>..<reserved-FFF8>
		{ 0xFFF9, 0xFFFB, BidiClass::OtherNeutral, GeneralCategory::Format },	// INTERLINEAR ANNOTATION ANCHOR..INTERLINEAR ANNOTATION TERMINATOR
		{ 0xFFFC, 0xFFFD, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// OBJECT REPLACEMENT CHARACTER..REPLACEMENT CHARACTER
		{ 0xFFFE, 0xFFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-FFFE>..<noncharacter-FFFF>
		{ 0x10000, 0x1000B, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LINEAR B SYLLABLE B008 A..LINEAR B SYLLABLE B046 JE
		{ 0x1000D, 0x10026, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LINEAR B SYLLABLE B036 JO..LINEAR B SYLLABLE B032 QO
		{ 0x10028, 0x1003A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LINEAR B SYLLABLE B060 RA..LINEAR B SYLLABLE B042 WO
		{ 0x1003C, 0x1003D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LINEAR B SYLLABLE B017 ZA..LINEAR B SYLLABLE B074 ZE
		{ 0x1003F, 0x1004D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LINEAR B SYLLABLE B020 ZO..LINEAR B SYLLABLE B091 TWO
		{ 0x10050, 0x1005D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LINEAR B SYMBOL B018..LINEAR B SYMBOL B089
		{ 0x10080, 0x100FA, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LINEAR B IDEOGRAM B100 MAN..LINEAR B IDEOGRAM VESSEL B305
		{ 0x10100, 0x10100, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// AEGEAN WORD SEPARATOR LINE
		{ 0x10101, 0x10101, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// AEGEAN WORD SEPARATOR DOT
		{ 0x10102, 0x10102, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// AEGEAN CHECK MARK
		{ 0x10107, 0x10133, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// AEGEAN NUMBER ONE..AEGEAN NUMBER NINETY THOUSAND
		{ 0x10137, 0x1013F, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// AEGEAN WEIGHT BASE UNIT..AEGEAN MEASURE THIRD SUBUNIT
		{ 0x10140, 0x10174, BidiClass::OtherNeutral, GeneralCategory::LetterNumber },	// GREEK ACROPHONIC ATTIC ONE QUARTER..GREEK ACROPHONIC STRATIAN FIFTY MNAS
		{ 0x10175, 0x10178, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// GREEK ONE HALF SIGN..GREEK THREE QUARTERS SIGN
		{ 0x10179, 0x10189, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// GREEK YEAR SIGN..GREEK TRYBLION BASE SIGN
		{ 0x1018A, 0x1018B, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// GREEK ZERO SIGN..GREEK ONE QUARTER SIGN
		{ 0x1018C, 0x1018C, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// GREEK SINUSOID SIGN
		{ 0x1018D, 0x1018E, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// GREEK INDICTION SIGN..NOMISMA SIGN
		{ 0x10190, 0x1019C, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ROMAN SEXTANS SIGN..ASCIA SYMBOL
		{ 0x101A0, 0x101A0, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// GREEK SYMBOL TAU RHO
		{ 0x101D0, 0x101FC, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// PHAISTOS DISC SIGN PEDESTRIAN..PHAISTOS DISC SIGN WAVY BAND
		{ 0x101FD, 0x101FD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// PHAISTOS DISC SIGN COMBINING OBLIQUE STROKE
		{ 0x10280, 0x1029C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LYCIAN LETTER A..LYCIAN LETTER X
		{ 0x102A0, 0x102D0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CARIAN LETTER A..CARIAN LETTER UUU3
		{ 0x102E0, 0x102E0, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COPTIC EPACT THOUSANDS MARK
		{ 0x102E1, 0x102FB, BidiClass::EuropeanNumber, GeneralCategory::OtherNumber },	// COPTIC EPACT DIGIT ONE..COPTIC EPACT NUMBER NINE HUNDRED
		{ 0x10300, 0x1031F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// OLD ITALIC LETTER A..OLD ITALIC LETTER ESS
		{ 0x10320, 0x10323, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// OLD ITALIC NUMERAL ONE..OLD ITALIC NUMERAL FIFTY
		{ 0x1032D, 0x10340, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// OLD ITALIC LETTER YE..GOTHIC LETTER PAIRTHRA
		{ 0x10341, 0x10341, BidiClass::LeftToRight, GeneralCategory::LetterNumber },	// GOTHIC LETTER NINETY
		{ 0x10342, 0x10349, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GOTHIC LETTER RAIDA..GOTHIC LETTER OTHAL
		{ 0x1034A, 0x1034A, BidiClass::LeftToRight, GeneralCategory::LetterNumber },	// GOTHIC LETTER NINE HUNDRED
		{ 0x10350, 0x10375, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// OLD PERMIC LETTER AN..OLD PERMIC LETTER IA
		{ 0x10376, 0x1037A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING OLD PERMIC LETTER AN..COMBINING OLD PERMIC LETTER SII
		{ 0x10380, 0x1039D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// UGARITIC LETTER ALPA..UGARITIC LETTER SSU
		{ 0x1039F, 0x1039F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// UGARITIC WORD DIVIDER
		{ 0x103A0, 0x103C3, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// OLD PERSIAN SIGN A..OLD PERSIAN SIGN HA
		{ 0x103C8, 0x103CF, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// OLD PERSIAN SIGN AURAMAZDAA..OLD PERSIAN SIGN BUUMISH
		{ 0x103D0, 0x103D0, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// OLD PERSIAN WORD DIVIDER
		{ 0x103D1, 0x103D5, BidiClass::LeftToRight, GeneralCategory::LetterNumber },	// OLD PERSIAN NUMBER ONE..OLD PERSIAN NUMBER HUNDRED
		{ 0x10400, 0x1044F, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// DESERET CAPITAL LETTER LONG I..DESERET SMALL LETTER EW
		{ 0x10450, 0x1049D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SHAVIAN LETTER PEEP..OSMANYA LETTER OO
		{ 0x104A0, 0x104A9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// OSMANYA DIGIT ZERO..OSMANYA DIGIT NINE
		{ 0x104B0, 0x104D3, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// OSAGE CAPITAL LETTER A..OSAGE CAPITAL LETTER ZHA
		{ 0x104D8, 0x104FB, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// OSAGE SMALL LETTER A..OSAGE SMALL LETTER ZHA
		{ 0x10500, 0x10527, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ELBASAN LETTER A..ELBASAN LETTER KHE
		{ 0x10530, 0x10563, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CAUCASIAN ALBANIAN LETTER ALT..CAUCASIAN ALBANIAN LETTER KIW
		{ 0x1056F, 0x1056F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// CAUCASIAN ALBANIAN CITATION MARK
		{ 0x10570, 0x1057A, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// VITHKUQI CAPITAL LETTER A..VITHKUQI CAPITAL LETTER GA
		{ 0x1057C, 0x1058A, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// VITHKUQI CAPITAL LETTER HA..VITHKUQI CAPITAL LETTER RE
		{ 0x1058C, 0x10592, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// VITHKUQI CAPITAL LETTER SE..VITHKUQI CAPITAL LETTER XE
		{ 0x10594, 0x10595, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// VITHKUQI CAPITAL LETTER Y..VITHKUQI CAPITAL LETTER ZE
		{ 0x10597, 0x105A1, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// VITHKUQI SMALL LETTER A..VITHKUQI SMALL LETTER GA
		{ 0x105A3, 0x105B1, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// VITHKUQI SMALL LETTER HA..VITHKUQI SMALL LETTER RE
		{ 0x105B3, 0x105B9, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// VITHKUQI SMALL LETTER SE..VITHKUQI SMALL LETTER XE
		{ 0x105BB, 0x105BC, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// VITHKUQI SMALL LETTER Y..VITHKUQI SMALL LETTER ZE
		{ 0x105C0, 0x105F3, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TODHRI LETTER A..TODHRI LETTER OO
		{ 0x10600, 0x10736, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LINEAR A SIGN AB001..LINEAR A SIGN A664
		{ 0x10740, 0x10755, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LINEAR A SIGN A701 A..LINEAR A SIGN A732 JE
		{ 0x10760, 0x10767, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LINEAR A SIGN A800..LINEAR A SIGN A807
		{ 0x10780, 0x10785, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER SMALL CAPITAL AA..MODIFIER LETTER SMALL B WITH HOOK
		{ 0x10787, 0x107B0, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER SMALL DZ DIGRAPH..MODIFIER LETTER SMALL V WITH RIGHT HOOK
		{ 0x107B2, 0x107BA, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER SMALL CAPITAL Y..MODIFIER LETTER SMALL S WITH CURL
		{ 0x10800, 0x10805, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// CYPRIOT SYLLABLE A..CYPRIOT SYLLABLE JA
		{ 0x10808, 0x10808, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// CYPRIOT SYLLABLE JO
		{ 0x1080A, 0x10835, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// CYPRIOT SYLLABLE KA..CYPRIOT SYLLABLE WO
		{ 0x10837, 0x10838, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// CYPRIOT SYLLABLE XA..CYPRIOT SYLLABLE XE
		{ 0x1083C, 0x1083C, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// CYPRIOT SYLLABLE ZA
		{ 0x1083F, 0x10855, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// CYPRIOT SYLLABLE ZO..IMPERIAL ARAMAIC LETTER TAW
		{ 0x10857, 0x10857, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// IMPERIAL ARAMAIC SECTION SIGN
		{ 0x10858, 0x1085F, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// IMPERIAL ARAMAIC NUMBER ONE..IMPERIAL ARAMAIC NUMBER TEN THOUSAND
		{ 0x10860, 0x10876, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// PALMYRENE LETTER ALEPH..PALMYRENE LETTER TAW
		{ 0x10877, 0x10878, BidiClass::RightToLeft, GeneralCategory::OtherSymbol },	// PALMYRENE LEFT-POINTING FLEURON..PALMYRENE RIGHT-POINTING FLEURON
		{ 0x10879, 0x1087F, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// PALMYRENE NUMBER ONE..PALMYRENE NUMBER TWENTY
		{ 0x10880, 0x1089E, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// NABATAEAN LETTER FINAL ALEPH..NABATAEAN LETTER TAW
		{ 0x108A7, 0x108AF, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// NABATAEAN NUMBER ONE..NABATAEAN NUMBER ONE HUNDRED
		{ 0x108E0, 0x108F2, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// HATRAN LETTER ALEPH..HATRAN LETTER QOPH
		{ 0x108F4, 0x108F5, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// HATRAN LETTER SHIN..HATRAN LETTER TAW
		{ 0x108FB, 0x108FF, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// HATRAN NUMBER ONE..HATRAN NUMBER ONE HUNDRED
		{ 0x10900, 0x10915, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// PHOENICIAN LETTER ALF..PHOENICIAN LETTER TAU
		{ 0x10916, 0x1091B, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// PHOENICIAN NUMBER ONE..PHOENICIAN NUMBER THREE
		{ 0x1091F, 0x1091F, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// PHOENICIAN WORD SEPARATOR
		{ 0x10920, 0x10939, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// LYDIAN LETTER A..LYDIAN LETTER C
		{ 0x1093F, 0x1093F, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// LYDIAN TRIANGULAR MARK
		{ 0x10940, 0x10959, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// SIDETIC LETTER N01..SIDETIC LETTER N26
		{ 0x10980, 0x109B7, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// MEROITIC HIEROGLYPHIC LETTER A..MEROITIC CURSIVE LETTER DA
		{ 0x109BC, 0x109BD, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// MEROITIC CURSIVE FRACTION ELEVEN TWELFTHS..MEROITIC CURSIVE FRACTION ONE HALF
		{ 0x109BE, 0x109BF, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// MEROITIC CURSIVE LOGOGRAM RMT..MEROITIC CURSIVE LOGOGRAM IMN
		{ 0x109C0, 0x109CF, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// MEROITIC CURSIVE NUMBER ONE..MEROITIC CURSIVE NUMBER SEVENTY
		{ 0x109D2, 0x109FF, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// MEROITIC CURSIVE NUMBER ONE HUNDRED..MEROITIC CURSIVE FRACTION TEN TWELFTHS
		{ 0x10A00, 0x10A00, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// KHAROSHTHI LETTER A
		{ 0x10A01, 0x10A03, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHAROSHTHI VOWEL SIGN I..KHAROSHTHI VOWEL SIGN VOCALIC R
		{ 0x10A05, 0x10A06, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHAROSHTHI VOWEL SIGN E..KHAROSHTHI VOWEL SIGN O
		{ 0x10A0C, 0x10A0F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHAROSHTHI VOWEL LENGTH MARK..KHAROSHTHI SIGN VISARGA
		{ 0x10A10, 0x10A13, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// KHAROSHTHI LETTER KA..KHAROSHTHI LETTER GHA
		{ 0x10A15, 0x10A17, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// KHAROSHTHI LETTER CA..KHAROSHTHI LETTER JA
		{ 0x10A19, 0x10A35, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// KHAROSHTHI LETTER NYA..KHAROSHTHI LETTER VHA
		{ 0x10A38, 0x10A3A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHAROSHTHI SIGN BAR ABOVE..KHAROSHTHI SIGN DOT BELOW
		{ 0x10A3F, 0x10A3F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHAROSHTHI VIRAMA
		{ 0x10A40, 0x10A48, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// KHAROSHTHI DIGIT ONE..KHAROSHTHI FRACTION ONE HALF
		{ 0x10A50, 0x10A58, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// KHAROSHTHI PUNCTUATION DOT..KHAROSHTHI PUNCTUATION LINES
		{ 0x10A60, 0x10A7C, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// OLD SOUTH ARABIAN LETTER HE..OLD SOUTH ARABIAN LETTER THETH
		{ 0x10A7D, 0x10A7E, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// OLD SOUTH ARABIAN NUMBER ONE..OLD SOUTH ARABIAN NUMBER FIFTY
		{ 0x10A7F, 0x10A7F, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// OLD SOUTH ARABIAN NUMERIC INDICATOR
		{ 0x10A80, 0x10A9C, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// OLD NORTH ARABIAN LETTER HEH..OLD NORTH ARABIAN LETTER ZAH
		{ 0x10A9D, 0x10A9F, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// OLD NORTH ARABIAN NUMBER ONE..OLD NORTH ARABIAN NUMBER TWENTY
		{ 0x10AC0, 0x10AC7, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// MANICHAEAN LETTER ALEPH..MANICHAEAN LETTER WAW
		{ 0x10AC8, 0x10AC8, BidiClass::RightToLeft, GeneralCategory::OtherSymbol },	// MANICHAEAN SIGN UD
		{ 0x10AC9, 0x10AE4, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// MANICHAEAN LETTER ZAYIN..MANICHAEAN LETTER TAW
		{ 0x10AE5, 0x10AE6, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MANICHAEAN ABBREVIATION MARK ABOVE..MANICHAEAN ABBREVIATION MARK BELOW
		{ 0x10AEB, 0x10AEF, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// MANICHAEAN NUMBER ONE..MANICHAEAN NUMBER ONE HUNDRED
		{ 0x10AF0, 0x10AF6, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// MANICHAEAN PUNCTUATION STAR..MANICHAEAN PUNCTUATION LINE FILLER
		{ 0x10B00, 0x10B35, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// AVESTAN LETTER A..AVESTAN LETTER HE
		{ 0x10B39, 0x10B3F, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// AVESTAN ABBREVIATION MARK..LARGE ONE RING OVER TWO RINGS PUNCTUATION
		{ 0x10B40, 0x10B55, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// INSCRIPTIONAL PARTHIAN LETTER ALEPH..INSCRIPTIONAL PARTHIAN LETTER TAW
		{ 0x10B58, 0x10B5F, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// INSCRIPTIONAL PARTHIAN NUMBER ONE..INSCRIPTIONAL PARTHIAN NUMBER ONE THOUSAND
		{ 0x10B60, 0x10B72, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// INSCRIPTIONAL PAHLAVI LETTER ALEPH..INSCRIPTIONAL PAHLAVI LETTER TAW
		{ 0x10B78, 0x10B7F, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// INSCRIPTIONAL PAHLAVI NUMBER ONE..INSCRIPTIONAL PAHLAVI NUMBER ONE THOUSAND
		{ 0x10B80, 0x10B91, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// PSALTER PAHLAVI LETTER ALEPH..PSALTER PAHLAVI LETTER TAW
		{ 0x10B99, 0x10B9C, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// PSALTER PAHLAVI SECTION MARK..PSALTER PAHLAVI FOUR DOTS WITH DOT
		{ 0x10BA9, 0x10BAF, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// PSALTER PAHLAVI NUMBER ONE..PSALTER PAHLAVI NUMBER ONE HUNDRED
		{ 0x10C00, 0x10C48, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// OLD TURKIC LETTER ORKHON A..OLD TURKIC LETTER ORKHON BASH
		{ 0x10C80, 0x10CB2, BidiClass::RightToLeft, GeneralCategory::CasedLetter },	// OLD HUNGARIAN CAPITAL LETTER A..OLD HUNGARIAN CAPITAL LETTER US
		{ 0x10CC0, 0x10CF2, BidiClass::RightToLeft, GeneralCategory::CasedLetter },	// OLD HUNGARIAN SMALL LETTER A..OLD HUNGARIAN SMALL LETTER US
		{ 0x10CFA, 0x10CFF, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// OLD HUNGARIAN NUMBER ONE..OLD HUNGARIAN NUMBER ONE THOUSAND
		{ 0x10D00, 0x10D23, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// HANIFI ROHINGYA LETTER A..HANIFI ROHINGYA MARK NA KHONNA
		{ 0x10D24, 0x10D27, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// HANIFI ROHINGYA SIGN HARBAHAY..HANIFI ROHINGYA SIGN TASSI
		{ 0x10D30, 0x10D39, BidiClass::ArabicNumber, GeneralCategory::DecimalNumber },	// HANIFI ROHINGYA DIGIT ZERO..HANIFI ROHINGYA DIGIT NINE
		{ 0x10D40, 0x10D49, BidiClass::ArabicNumber, GeneralCategory::DecimalNumber },	// GARAY DIGIT ZERO..GARAY DIGIT NINE
		{ 0x10D4A, 0x10D4D, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// GARAY VOWEL SIGN A..GARAY VOWEL SIGN EE
		{ 0x10D4E, 0x10D4E, BidiClass::RightToLeft, GeneralCategory::ModifierLetter },	// GARAY VOWEL LENGTH MARK
		{ 0x10D4F, 0x10D4F, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// GARAY SUKUN
		{ 0x10D50, 0x10D65, BidiClass::RightToLeft, GeneralCategory::CasedLetter },	// GARAY CAPITAL LETTER A..GARAY CAPITAL LETTER OLD NA
		{ 0x10D69, 0x10D6D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GARAY VOWEL SIGN E..GARAY CONSONANT NASALIZATION MARK
		{ 0x10D6E, 0x10D6E, BidiClass::OtherNeutral, GeneralCategory::DashPunctuation },	// GARAY HYPHEN
		{ 0x10D6F, 0x10D6F, BidiClass::RightToLeft, GeneralCategory::ModifierLetter },	// GARAY REDUPLICATION MARK
		{ 0x10D70, 0x10D85, BidiClass::RightToLeft, GeneralCategory::CasedLetter },	// GARAY SMALL LETTER A..GARAY SMALL LETTER OLD NA
		{ 0x10D8E, 0x10D8F, BidiClass::RightToLeft, GeneralCategory::MathSymbol },	// GARAY PLUS SIGN..GARAY MINUS SIGN
		{ 0x10E60, 0x10E7E, BidiClass::ArabicNumber, GeneralCategory::OtherNumber },	// RUMI DIGIT ONE..RUMI FRACTION TWO THIRDS
		{ 0x10E80, 0x10EA9, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// YEZIDI LETTER ELIF..YEZIDI LETTER ET
		{ 0x10EAB, 0x10EAC, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// YEZIDI COMBINING HAMZA MARK..YEZIDI COMBINING MADDA MARK
		{ 0x10EAD, 0x10EAD, BidiClass::RightToLeft, GeneralCategory::DashPunctuation },	// YEZIDI HYPHENATION MARK
		{ 0x10EB0, 0x10EB1, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// YEZIDI LETTER LAM WITH DOT ABOVE..YEZIDI LETTER YOT WITH CIRCUMFLEX ABOVE
		{ 0x10EC2, 0x10EC4, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER DAL WITH TWO DOTS VERTICALLY BELOW..ARABIC LETTER KAF WITH TWO DOTS VERTICALLY BELOW
		{ 0x10EC5, 0x10EC5, BidiClass::ArabicLetter, GeneralCategory::ModifierLetter },	// ARABIC SMALL YEH BARREE WITH TWO DOTS BELOW
		{ 0x10EC6, 0x10EC7, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC LETTER THIN NOON..ARABIC LETTER YEH WITH FOUR DOTS BELOW
		{ 0x10ED0, 0x10ED0, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// ARABIC BIBLICAL END OF VERSE
		{ 0x10ED1, 0x10ED8, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ARABIC LIGATURE ALAYHAA AS-SALAATU WAS-SALAAM..ARABIC LIGATURE NAWWARA ALLAAHU MARQADAH
		{ 0x10EFA, 0x10EFF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ARABIC DOUBLE VERTICAL BAR BELOW..ARABIC SMALL LOW WORD MADDA
		{ 0x10F00, 0x10F1C, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// OLD SOGDIAN LETTER ALEPH..OLD SOGDIAN LETTER FINAL TAW WITH VERTICAL TAIL
		{ 0x10F1D, 0x10F26, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// OLD SOGDIAN NUMBER ONE..OLD SOGDIAN FRACTION ONE HALF
		{ 0x10F27, 0x10F27, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// OLD SOGDIAN LIGATURE AYIN-DALETH
		{ 0x10F30, 0x10F45, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// SOGDIAN LETTER ALEPH..SOGDIAN INDEPENDENT SHIN
		{ 0x10F46, 0x10F50, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SOGDIAN COMBINING DOT BELOW..SOGDIAN COMBINING STROKE BELOW
		{ 0x10F51, 0x10F54, BidiClass::ArabicLetter, GeneralCategory::OtherNumber },	// SOGDIAN NUMBER ONE..SOGDIAN NUMBER ONE HUNDRED
		{ 0x10F55, 0x10F59, BidiClass::ArabicLetter, GeneralCategory::OtherPunctuation },	// SOGDIAN PUNCTUATION TWO VERTICAL BARS..SOGDIAN PUNCTUATION HALF CIRCLE WITH DOT
		{ 0x10F70, 0x10F81, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// OLD UYGHUR LETTER ALEPH..OLD UYGHUR LETTER LESH
		{ 0x10F82, 0x10F85, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// OLD UYGHUR COMBINING DOT ABOVE..OLD UYGHUR COMBINING TWO DOTS BELOW
		{ 0x10F86, 0x10F89, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// OLD UYGHUR PUNCTUATION BAR..OLD UYGHUR PUNCTUATION FOUR DOTS
		{ 0x10FB0, 0x10FC4, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// CHORASMIAN LETTER ALEPH..CHORASMIAN LETTER TAW
		{ 0x10FC5, 0x10FCB, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// CHORASMIAN NUMBER ONE..CHORASMIAN NUMBER ONE HUNDRED
		{ 0x10FE0, 0x10FF6, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// ELYMAIC LETTER ALEPH..ELYMAIC LIGATURE ZAYIN-YODH
		{ 0x11000, 0x11000, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BRAHMI SIGN CANDRABINDU
		{ 0x11001, 0x11001, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BRAHMI SIGN ANUSVARA
		{ 0x11002, 0x11002, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BRAHMI SIGN VISARGA
		{ 0x11003, 0x11037, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BRAHMI SIGN JIHVAMULIYA..BRAHMI LETTER OLD TAMIL NNNA
		{ 0x11038, 0x11046, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BRAHMI VOWEL SIGN AA..BRAHMI VIRAMA
		{ 0x11047, 0x1104D, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// BRAHMI DANDA..BRAHMI PUNCTUATION LOTUS
		{ 0x11052, 0x11065, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// BRAHMI NUMBER ONE..BRAHMI NUMBER ONE THOUSAND
		{ 0x11066, 0x1106F, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// BRAHMI DIGIT ZERO..BRAHMI DIGIT NINE
		{ 0x11070, 0x11070, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BRAHMI SIGN OLD TAMIL VIRAMA
		{ 0x11071, 0x11072, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BRAHMI LETTER OLD TAMIL SHORT E..BRAHMI LETTER OLD TAMIL SHORT O
		{ 0x11073, 0x11074, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BRAHMI VOWEL SIGN OLD TAMIL SHORT E..BRAHMI VOWEL SIGN OLD TAMIL SHORT O
		{ 0x11075, 0x11075, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BRAHMI LETTER OLD TAMIL LLA
		{ 0x1107F, 0x11081, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BRAHMI NUMBER JOINER..KAITHI SIGN ANUSVARA
		{ 0x11082, 0x11082, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KAITHI SIGN VISARGA
		{ 0x11083, 0x110AF, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KAITHI LETTER A..KAITHI LETTER HA
		{ 0x110B0, 0x110B2, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KAITHI VOWEL SIGN AA..KAITHI VOWEL SIGN II
		{ 0x110B3, 0x110B6, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KAITHI VOWEL SIGN U..KAITHI VOWEL SIGN AI
		{ 0x110B7, 0x110B8, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KAITHI VOWEL SIGN O..KAITHI VOWEL SIGN AU
		{ 0x110B9, 0x110BA, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KAITHI SIGN VIRAMA..KAITHI SIGN NUKTA
		{ 0x110BB, 0x110BC, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// KAITHI ABBREVIATION SIGN..KAITHI ENUMERATION SIGN
		{ 0x110BD, 0x110BD, BidiClass::LeftToRight, GeneralCategory::Format },	// KAITHI NUMBER SIGN
		{ 0x110BE, 0x110C1, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// KAITHI SECTION MARK..KAITHI DOUBLE DANDA
		{ 0x110C2, 0x110C2, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KAITHI VOWEL SIGN VOCALIC R
		{ 0x110CD, 0x110CD, BidiClass::LeftToRight, GeneralCategory::Format },	// KAITHI NUMBER SIGN ABOVE
		{ 0x110D0, 0x110E8, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SORA SOMPENG LETTER SAH..SORA SOMPENG LETTER MAE
		{ 0x110F0, 0x110F9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// SORA SOMPENG DIGIT ZERO..SORA SOMPENG DIGIT NINE
		{ 0x11100, 0x11102, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// CHAKMA SIGN CANDRABINDU..CHAKMA SIGN VISARGA
		{ 0x11103, 0x11126, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CHAKMA LETTER AA..CHAKMA LETTER HAA
		{ 0x11127, 0x1112B, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// CHAKMA VOWEL SIGN A..CHAKMA VOWEL SIGN UU
		{ 0x1112C, 0x1112C, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// CHAKMA VOWEL SIGN E
		{ 0x1112D, 0x11134, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// CHAKMA VOWEL SIGN AI..CHAKMA MAAYYAA
		{ 0x11136, 0x1113F, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// CHAKMA DIGIT ZERO..CHAKMA DIGIT NINE
		{ 0x11140, 0x11143, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// CHAKMA SECTION MARK..CHAKMA QUESTION MARK
		{ 0x11144, 0x11144, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CHAKMA LETTER LHAA
		{ 0x11145, 0x11146, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// CHAKMA VOWEL SIGN AA..CHAKMA VOWEL SIGN EI
		{ 0x11147, 0x11147, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CHAKMA LETTER VAA
		{ 0x11150, 0x11172, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MAHAJANI LETTER A..MAHAJANI LETTER RRA
		{ 0x11173, 0x11173, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MAHAJANI SIGN NUKTA
		{ 0x11174, 0x11175, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// MAHAJANI ABBREVIATION SIGN..MAHAJANI SECTION MARK
		{ 0x11176, 0x11176, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MAHAJANI LIGATURE SHRI
		{ 0x11180, 0x11181, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SHARADA SIGN CANDRABINDU..SHARADA SIGN ANUSVARA
		{ 0x11182, 0x11182, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SHARADA SIGN VISARGA
		{ 0x11183, 0x111B2, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SHARADA LETTER A..SHARADA LETTER HA
		{ 0x111B3, 0x111B5, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SHARADA VOWEL SIGN AA..SHARADA VOWEL SIGN II
		{ 0x111B6, 0x111BE, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SHARADA VOWEL SIGN U..SHARADA VOWEL SIGN O
		{ 0x111BF, 0x111C0, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SHARADA VOWEL SIGN AU..SHARADA SIGN VIRAMA
		{ 0x111C1, 0x111C4, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SHARADA SIGN AVAGRAHA..SHARADA OM
		{ 0x111C5, 0x111C8, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// SHARADA DANDA..SHARADA SEPARATOR
		{ 0x111C9, 0x111CC, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SHARADA SANDHI MARK..SHARADA EXTRA SHORT VOWEL MARK
		{ 0x111CD, 0x111CD, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// SHARADA SUTRA MARK
		{ 0x111CE, 0x111CE, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SHARADA VOWEL SIGN PRISHTHAMATRA E
		{ 0x111CF, 0x111CF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SHARADA SIGN INVERTED CANDRABINDU
		{ 0x111D0, 0x111D9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// SHARADA DIGIT ZERO..SHARADA DIGIT NINE
		{ 0x111DA, 0x111DA, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SHARADA EKAM
		{ 0x111DB, 0x111DB, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// SHARADA SIGN SIDDHAM
		{ 0x111DC, 0x111DC, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SHARADA HEADSTROKE
		{ 0x111DD, 0x111DF, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// SHARADA CONTINUATION SIGN..SHARADA SECTION MARK-2
		{ 0x111E1, 0x111F4, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// SINHALA ARCHAIC DIGIT ONE..SINHALA ARCHAIC NUMBER ONE THOUSAND
		{ 0x11200, 0x11211, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KHOJKI LETTER A..KHOJKI LETTER JJA
		{ 0x11213, 0x1122B, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KHOJKI LETTER NYA..KHOJKI LETTER LLA
		{ 0x1122C, 0x1122E, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KHOJKI VOWEL SIGN AA..KHOJKI VOWEL SIGN II
		{ 0x1122F, 0x11231, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHOJKI VOWEL SIGN U..KHOJKI VOWEL SIGN AI
		{ 0x11232, 0x11233, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KHOJKI VOWEL SIGN O..KHOJKI VOWEL SIGN AU
		{ 0x11234, 0x11234, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHOJKI SIGN ANUSVARA
		{ 0x11235, 0x11235, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KHOJKI SIGN VIRAMA
		{ 0x11236, 0x11237, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHOJKI SIGN NUKTA..KHOJKI SIGN SHADDA
		{ 0x11238, 0x1123D, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// KHOJKI DANDA..KHOJKI ABBREVIATION SIGN
		{ 0x1123E, 0x1123E, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHOJKI SIGN SUKUN
		{ 0x1123F, 0x11240, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KHOJKI LETTER QA..KHOJKI LETTER SHORT I
		{ 0x11241, 0x11241, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHOJKI VOWEL SIGN VOCALIC R
		{ 0x11280, 0x11286, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MULTANI LETTER A..MULTANI LETTER GA
		{ 0x11288, 0x11288, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MULTANI LETTER GHA
		{ 0x1128A, 0x1128D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MULTANI LETTER CA..MULTANI LETTER JJA
		{ 0x1128F, 0x1129D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MULTANI LETTER NYA..MULTANI LETTER BA
		{ 0x1129F, 0x112A8, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MULTANI LETTER BHA..MULTANI LETTER RHA
		{ 0x112A9, 0x112A9, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// MULTANI SECTION MARK
		{ 0x112B0, 0x112DE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KHUDAWADI LETTER A..KHUDAWADI LETTER HA
		{ 0x112DF, 0x112DF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHUDAWADI SIGN ANUSVARA
		{ 0x112E0, 0x112E2, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KHUDAWADI VOWEL SIGN AA..KHUDAWADI VOWEL SIGN II
		{ 0x112E3, 0x112EA, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHUDAWADI VOWEL SIGN U..KHUDAWADI SIGN VIRAMA
		{ 0x112F0, 0x112F9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// KHUDAWADI DIGIT ZERO..KHUDAWADI DIGIT NINE
		{ 0x11300, 0x11301, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GRANTHA SIGN COMBINING ANUSVARA ABOVE..GRANTHA SIGN CANDRABINDU
		{ 0x11302, 0x11303, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GRANTHA SIGN ANUSVARA..GRANTHA SIGN VISARGA
		{ 0x11305, 0x1130C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GRANTHA LETTER A..GRANTHA LETTER VOCALIC L
		{ 0x1130F, 0x11310, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GRANTHA LETTER EE..GRANTHA LETTER AI
		{ 0x11313, 0x11328, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GRANTHA LETTER OO..GRANTHA LETTER NA
		{ 0x1132A, 0x11330, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GRANTHA LETTER PA..GRANTHA LETTER RA
		{ 0x11332, 0x11333, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GRANTHA LETTER LA..GRANTHA LETTER LLA
		{ 0x11335, 0x11339, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GRANTHA LETTER VA..GRANTHA LETTER HA
		{ 0x1133B, 0x1133C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING BINDU BELOW..GRANTHA SIGN NUKTA
		{ 0x1133D, 0x1133D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GRANTHA SIGN AVAGRAHA
		{ 0x1133E, 0x1133F, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GRANTHA VOWEL SIGN AA..GRANTHA VOWEL SIGN I
		{ 0x11340, 0x11340, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GRANTHA VOWEL SIGN II
		{ 0x11341, 0x11344, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GRANTHA VOWEL SIGN U..GRANTHA VOWEL SIGN VOCALIC RR
		{ 0x11347, 0x11348, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GRANTHA VOWEL SIGN EE..GRANTHA VOWEL SIGN AI
		{ 0x1134B, 0x1134D, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GRANTHA VOWEL SIGN OO..GRANTHA SIGN VIRAMA
		{ 0x11350, 0x11350, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GRANTHA OM
		{ 0x11357, 0x11357, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GRANTHA AU LENGTH MARK
		{ 0x1135D, 0x11361, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GRANTHA SIGN PLUTA..GRANTHA LETTER VOCALIC LL
		{ 0x11362, 0x11363, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GRANTHA VOWEL SIGN VOCALIC L..GRANTHA VOWEL SIGN VOCALIC LL
		{ 0x11366, 0x1136C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING GRANTHA DIGIT ZERO..COMBINING GRANTHA DIGIT SIX
		{ 0x11370, 0x11374, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING GRANTHA LETTER A..COMBINING GRANTHA LETTER PA
		{ 0x11380, 0x11389, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TULU-TIGALARI LETTER A..TULU-TIGALARI LETTER VOCALIC LL
		{ 0x1138B, 0x1138B, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TULU-TIGALARI LETTER EE
		{ 0x1138E, 0x1138E, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TULU-TIGALARI LETTER AI
		{ 0x11390, 0x113B5, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TULU-TIGALARI LETTER OO..TULU-TIGALARI LETTER LLLA
		{ 0x113B7, 0x113B7, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TULU-TIGALARI SIGN AVAGRAHA
		{ 0x113B8, 0x113BA, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TULU-TIGALARI VOWEL SIGN AA..TULU-TIGALARI VOWEL SIGN II
		{ 0x113BB, 0x113C0, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TULU-TIGALARI VOWEL SIGN U..TULU-TIGALARI VOWEL SIGN VOCALIC LL
		{ 0x113C2, 0x113C2, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TULU-TIGALARI VOWEL SIGN EE
		{ 0x113C5, 0x113C5, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TULU-TIGALARI VOWEL SIGN AI
		{ 0x113C7, 0x113CA, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TULU-TIGALARI VOWEL SIGN OO..TULU-TIGALARI SIGN CANDRA ANUNASIKA
		{ 0x113CC, 0x113CD, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TULU-TIGALARI SIGN ANUSVARA..TULU-TIGALARI SIGN VISARGA
		{ 0x113CE, 0x113CE, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TULU-TIGALARI SIGN VIRAMA
		{ 0x113CF, 0x113CF, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TULU-TIGALARI SIGN LOOPED VIRAMA
		{ 0x113D0, 0x113D0, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TULU-TIGALARI CONJOINER
		{ 0x113D1, 0x113D1, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TULU-TIGALARI REPHA
		{ 0x113D2, 0x113D2, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TULU-TIGALARI GEMINATION MARK
		{ 0x113D3, 0x113D3, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TULU-TIGALARI SIGN PLUTA
		{ 0x113D4, 0x113D5, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TULU-TIGALARI DANDA..TULU-TIGALARI DOUBLE DANDA
		{ 0x113D7, 0x113D8, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TULU-TIGALARI SIGN OM PUSHPIKA..TULU-TIGALARI SIGN SHRII PUSHPIKA
		{ 0x113E1, 0x113E2, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TULU-TIGALARI VEDIC TONE SVARITA..TULU-TIGALARI VEDIC TONE ANUDATTA
		{ 0x11400, 0x11434, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// NEWA LETTER A..NEWA LETTER HA
		{ 0x11435, 0x11437, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// NEWA VOWEL SIGN AA..NEWA VOWEL SIGN II
		{ 0x11438, 0x1143F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// NEWA VOWEL SIGN U..NEWA VOWEL SIGN AI
		{ 0x11440, 0x11441, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// NEWA VOWEL SIGN O..NEWA VOWEL SIGN AU
		{ 0x11442, 0x11444, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// NEWA SIGN VIRAMA..NEWA SIGN ANUSVARA
		{ 0x11445, 0x11445, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// NEWA SIGN VISARGA
		{ 0x11446, 0x11446, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// NEWA SIGN NUKTA
		{ 0x11447, 0x1144A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// NEWA SIGN AVAGRAHA..NEWA SIDDHI
		{ 0x1144B, 0x1144F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// NEWA DANDA..NEWA ABBREVIATION SIGN
		{ 0x11450, 0x11459, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// NEWA DIGIT ZERO..NEWA DIGIT NINE
		{ 0x1145A, 0x1145B, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// NEWA DOUBLE COMMA..NEWA PLACEHOLDER MARK
		{ 0x1145D, 0x1145D, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// NEWA INSERTION SIGN
		{ 0x1145E, 0x1145E, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// NEWA SANDHI MARK
		{ 0x1145F, 0x11461, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// NEWA LETTER VEDIC ANUSVARA..NEWA SIGN UPADHMANIYA
		{ 0x11480, 0x114AF, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TIRHUTA ANJI..TIRHUTA LETTER HA
		{ 0x114B0, 0x114B2, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TIRHUTA VOWEL SIGN AA..TIRHUTA VOWEL SIGN II
		{ 0x114B3, 0x114B8, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIRHUTA VOWEL SIGN U..TIRHUTA VOWEL SIGN VOCALIC LL
		{ 0x114B9, 0x114B9, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TIRHUTA VOWEL SIGN E
		{ 0x114BA, 0x114BA, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIRHUTA VOWEL SIGN SHORT E
		{ 0x114BB, 0x114BE, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TIRHUTA VOWEL SIGN AI..TIRHUTA VOWEL SIGN AU
		{ 0x114BF, 0x114C0, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIRHUTA SIGN CANDRABINDU..TIRHUTA SIGN ANUSVARA
		{ 0x114C1, 0x114C1, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TIRHUTA SIGN VISARGA
		{ 0x114C2, 0x114C3, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TIRHUTA SIGN VIRAMA..TIRHUTA SIGN NUKTA
		{ 0x114C4, 0x114C5, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TIRHUTA SIGN AVAGRAHA..TIRHUTA GVANG
		{ 0x114C6, 0x114C6, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TIRHUTA ABBREVIATION SIGN
		{ 0x114C7, 0x114C7, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TIRHUTA OM
		{ 0x114D0, 0x114D9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// TIRHUTA DIGIT ZERO..TIRHUTA DIGIT NINE
		{ 0x11580, 0x115AE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SIDDHAM LETTER A..SIDDHAM LETTER HA
		{ 0x115AF, 0x115B1, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SIDDHAM VOWEL SIGN AA..SIDDHAM VOWEL SIGN II
		{ 0x115B2, 0x115B5, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SIDDHAM VOWEL SIGN U..SIDDHAM VOWEL SIGN VOCALIC RR
		{ 0x115B8, 0x115BB, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SIDDHAM VOWEL SIGN E..SIDDHAM VOWEL SIGN AU
		{ 0x115BC, 0x115BD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SIDDHAM SIGN CANDRABINDU..SIDDHAM SIGN ANUSVARA
		{ 0x115BE, 0x115BE, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SIDDHAM SIGN VISARGA
		{ 0x115BF, 0x115C0, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SIDDHAM SIGN VIRAMA..SIDDHAM SIGN NUKTA
		{ 0x115C1, 0x115D7, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// SIDDHAM SIGN SIDDHAM..SIDDHAM SECTION MARK WITH CIRCLES AND FOUR ENCLOSURES
		{ 0x115D8, 0x115DB, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SIDDHAM LETTER THREE-CIRCLE ALTERNATE I..SIDDHAM LETTER ALTERNATE U
		{ 0x115DC, 0x115DD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SIDDHAM VOWEL SIGN ALTERNATE U..SIDDHAM VOWEL SIGN ALTERNATE UU
		{ 0x11600, 0x1162F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MODI LETTER A..MODI LETTER LLA
		{ 0x11630, 0x11632, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MODI VOWEL SIGN AA..MODI VOWEL SIGN II
		{ 0x11633, 0x1163A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MODI VOWEL SIGN U..MODI VOWEL SIGN AI
		{ 0x1163B, 0x1163C, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MODI VOWEL SIGN O..MODI VOWEL SIGN AU
		{ 0x1163D, 0x1163D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MODI SIGN ANUSVARA
		{ 0x1163E, 0x1163E, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MODI SIGN VISARGA
		{ 0x1163F, 0x11640, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MODI SIGN VIRAMA..MODI SIGN ARDHACANDRA
		{ 0x11641, 0x11643, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// MODI DANDA..MODI ABBREVIATION SIGN
		{ 0x11644, 0x11644, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MODI SIGN HUVA
		{ 0x11650, 0x11659, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// MODI DIGIT ZERO..MODI DIGIT NINE
		{ 0x11660, 0x1166C, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// MONGOLIAN BIRGA WITH ORNAMENT..MONGOLIAN TURNED SWIRL BIRGA WITH DOUBLE ORNAMENT
		{ 0x11680, 0x116AA, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAKRI LETTER A..TAKRI LETTER RRA
		{ 0x116AB, 0x116AB, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAKRI SIGN ANUSVARA
		{ 0x116AC, 0x116AC, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAKRI SIGN VISARGA
		{ 0x116AD, 0x116AD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAKRI VOWEL SIGN AA
		{ 0x116AE, 0x116AF, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAKRI VOWEL SIGN I..TAKRI VOWEL SIGN II
		{ 0x116B0, 0x116B5, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAKRI VOWEL SIGN U..TAKRI VOWEL SIGN AU
		{ 0x116B6, 0x116B6, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// TAKRI SIGN VIRAMA
		{ 0x116B7, 0x116B7, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAKRI SIGN NUKTA
		{ 0x116B8, 0x116B8, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAKRI LETTER ARCHAIC KHA
		{ 0x116B9, 0x116B9, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TAKRI ABBREVIATION SIGN
		{ 0x116C0, 0x116C9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// TAKRI DIGIT ZERO..TAKRI DIGIT NINE
		{ 0x116D0, 0x116E3, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// MYANMAR PAO DIGIT ZERO..MYANMAR EASTERN PWO KAREN DIGIT NINE
		{ 0x11700, 0x1171A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// AHOM LETTER KA..AHOM LETTER ALTERNATE BA
		{ 0x1171D, 0x1171D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// AHOM CONSONANT SIGN MEDIAL LA
		{ 0x1171E, 0x1171E, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// AHOM CONSONANT SIGN MEDIAL RA
		{ 0x1171F, 0x1171F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// AHOM CONSONANT SIGN MEDIAL LIGATING RA
		{ 0x11720, 0x11721, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// AHOM VOWEL SIGN A..AHOM VOWEL SIGN AA
		{ 0x11722, 0x11725, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// AHOM VOWEL SIGN I..AHOM VOWEL SIGN UU
		{ 0x11726, 0x11726, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// AHOM VOWEL SIGN E
		{ 0x11727, 0x1172B, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// AHOM VOWEL SIGN AW..AHOM SIGN KILLER
		{ 0x11730, 0x11739, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// AHOM DIGIT ZERO..AHOM DIGIT NINE
		{ 0x1173A, 0x1173B, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// AHOM NUMBER TEN..AHOM NUMBER TWENTY
		{ 0x1173C, 0x1173E, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// AHOM SIGN SMALL SECTION..AHOM SIGN RULAI
		{ 0x1173F, 0x1173F, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// AHOM SYMBOL VI
		{ 0x11740, 0x11746, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// AHOM LETTER CA..AHOM LETTER LLA
		{ 0x11800, 0x1182B, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DOGRA LETTER A..DOGRA LETTER RRA
		{ 0x1182C, 0x1182E, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// DOGRA VOWEL SIGN AA..DOGRA VOWEL SIGN II
		{ 0x1182F, 0x11837, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// DOGRA VOWEL SIGN U..DOGRA SIGN ANUSVARA
		{ 0x11838, 0x11838, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// DOGRA SIGN VISARGA
		{ 0x11839, 0x1183A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// DOGRA SIGN VIRAMA..DOGRA SIGN NUKTA
		{ 0x1183B, 0x1183B, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// DOGRA ABBREVIATION SIGN
		{ 0x118A0, 0x118DF, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// WARANG CITI CAPITAL LETTER NGAA..WARANG CITI SMALL LETTER VIYO
		{ 0x118E0, 0x118E9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// WARANG CITI DIGIT ZERO..WARANG CITI DIGIT NINE
		{ 0x118EA, 0x118F2, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// WARANG CITI NUMBER TEN..WARANG CITI NUMBER NINETY
		{ 0x118FF, 0x11906, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// WARANG CITI OM..DIVES AKURU LETTER E
		{ 0x11909, 0x11909, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DIVES AKURU LETTER O
		{ 0x1190C, 0x11913, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DIVES AKURU LETTER KA..DIVES AKURU LETTER JA
		{ 0x11915, 0x11916, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DIVES AKURU LETTER NYA..DIVES AKURU LETTER TTA
		{ 0x11918, 0x1192F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DIVES AKURU LETTER DDA..DIVES AKURU LETTER ZA
		{ 0x11930, 0x11935, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// DIVES AKURU VOWEL SIGN AA..DIVES AKURU VOWEL SIGN E
		{ 0x11937, 0x11938, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// DIVES AKURU VOWEL SIGN AI..DIVES AKURU VOWEL SIGN O
		{ 0x1193B, 0x1193C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// DIVES AKURU SIGN ANUSVARA..DIVES AKURU SIGN CANDRABINDU
		{ 0x1193D, 0x1193D, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// DIVES AKURU SIGN HALANTA
		{ 0x1193E, 0x1193E, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// DIVES AKURU VIRAMA
		{ 0x1193F, 0x1193F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DIVES AKURU PREFIXED NASAL SIGN
		{ 0x11940, 0x11940, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// DIVES AKURU MEDIAL YA
		{ 0x11941, 0x11941, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DIVES AKURU INITIAL RA
		{ 0x11942, 0x11942, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// DIVES AKURU MEDIAL RA
		{ 0x11943, 0x11943, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// DIVES AKURU SIGN NUKTA
		{ 0x11944, 0x11946, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// DIVES AKURU DOUBLE DANDA..DIVES AKURU END OF TEXT MARK
		{ 0x11950, 0x11959, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// DIVES AKURU DIGIT ZERO..DIVES AKURU DIGIT NINE
		{ 0x119A0, 0x119A7, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// NANDINAGARI LETTER A..NANDINAGARI LETTER VOCALIC RR
		{ 0x119AA, 0x119D0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// NANDINAGARI LETTER E..NANDINAGARI LETTER RRA
		{ 0x119D1, 0x119D3, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// NANDINAGARI VOWEL SIGN AA..NANDINAGARI VOWEL SIGN II
		{ 0x119D4, 0x119D7, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// NANDINAGARI VOWEL SIGN U..NANDINAGARI VOWEL SIGN VOCALIC RR
		{ 0x119DA, 0x119DB, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// NANDINAGARI VOWEL SIGN E..NANDINAGARI VOWEL SIGN AI
		{ 0x119DC, 0x119DF, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// NANDINAGARI VOWEL SIGN O..NANDINAGARI SIGN VISARGA
		{ 0x119E0, 0x119E0, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// NANDINAGARI SIGN VIRAMA
		{ 0x119E1, 0x119E1, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// NANDINAGARI SIGN AVAGRAHA
		{ 0x119E2, 0x119E2, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// NANDINAGARI SIGN SIDDHAM
		{ 0x119E3, 0x119E3, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// NANDINAGARI HEADSTROKE
		{ 0x119E4, 0x119E4, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// NANDINAGARI VOWEL SIGN PRISHTHAMATRA E
		{ 0x11A00, 0x11A00, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ZANABAZAR SQUARE LETTER A
		{ 0x11A01, 0x11A06, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ZANABAZAR SQUARE VOWEL SIGN I..ZANABAZAR SQUARE VOWEL SIGN O
		{ 0x11A07, 0x11A08, BidiClass::LeftToRight, GeneralCategory::NonspacingMark },	// ZANABAZAR SQUARE VOWEL SIGN AI..ZANABAZAR SQUARE VOWEL SIGN AU
		{ 0x11A09, 0x11A0A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ZANABAZAR SQUARE VOWEL SIGN REVERSED I..ZANABAZAR SQUARE VOWEL LENGTH MARK
		{ 0x11A0B, 0x11A32, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ZANABAZAR SQUARE LETTER KA..ZANABAZAR SQUARE LETTER KSSA
		{ 0x11A33, 0x11A38, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ZANABAZAR SQUARE FINAL CONSONANT MARK..ZANABAZAR SQUARE SIGN ANUSVARA
		{ 0x11A39, 0x11A39, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// ZANABAZAR SQUARE SIGN VISARGA
		{ 0x11A3A, 0x11A3A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ZANABAZAR SQUARE CLUSTER-INITIAL LETTER RA
		{ 0x11A3B, 0x11A3E, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ZANABAZAR SQUARE CLUSTER-FINAL LETTER YA..ZANABAZAR SQUARE CLUSTER-FINAL LETTER VA
		{ 0x11A3F, 0x11A46, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// ZANABAZAR SQUARE INITIAL HEAD MARK..ZANABAZAR SQUARE CLOSING DOUBLE-LINED HEAD MARK
		{ 0x11A47, 0x11A47, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ZANABAZAR SQUARE SUBJOINER
		{ 0x11A50, 0x11A50, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SOYOMBO LETTER A
		{ 0x11A51, 0x11A56, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SOYOMBO VOWEL SIGN I..SOYOMBO VOWEL SIGN OE
		{ 0x11A57, 0x11A58, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SOYOMBO VOWEL SIGN AI..SOYOMBO VOWEL SIGN AU
		{ 0x11A59, 0x11A5B, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SOYOMBO VOWEL SIGN VOCALIC R..SOYOMBO VOWEL LENGTH MARK
		{ 0x11A5C, 0x11A89, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SOYOMBO LETTER KA..SOYOMBO CLUSTER-INITIAL LETTER SA
		{ 0x11A8A, 0x11A96, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SOYOMBO FINAL CONSONANT SIGN G..SOYOMBO SIGN ANUSVARA
		{ 0x11A97, 0x11A97, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SOYOMBO SIGN VISARGA
		{ 0x11A98, 0x11A99, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SOYOMBO GEMINATION MARK..SOYOMBO SUBJOINER
		{ 0x11A9A, 0x11A9C, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// SOYOMBO MARK TSHEG..SOYOMBO MARK DOUBLE SHAD
		{ 0x11A9D, 0x11A9D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SOYOMBO MARK PLUTA
		{ 0x11A9E, 0x11AA2, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// SOYOMBO HEAD MARK WITH MOON AND SUN AND TRIPLE FLAME..SOYOMBO TERMINAL MARK-2
		{ 0x11AB0, 0x11AF8, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CANADIAN SYLLABICS NATTILIK HI..PAU CIN HAU GLOTTAL STOP FINAL
		{ 0x11B00, 0x11B09, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// DEVANAGARI HEAD MARK..DEVANAGARI SIGN MINDU
		{ 0x11B60, 0x11B60, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SHARADA VOWEL SIGN OE
		{ 0x11B61, 0x11B61, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SHARADA VOWEL SIGN OOE
		{ 0x11B62, 0x11B64, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SHARADA VOWEL SIGN UE..SHARADA VOWEL SIGN SHORT E
		{ 0x11B65, 0x11B65, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SHARADA VOWEL SIGN SHORT O
		{ 0x11B66, 0x11B66, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SHARADA VOWEL SIGN CANDRA E
		{ 0x11B67, 0x11B67, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// SHARADA VOWEL SIGN CANDRA O
		{ 0x11BC0, 0x11BE0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// SUNUWAR LETTER DEVI..SUNUWAR LETTER KLOKO
		{ 0x11BE1, 0x11BE1, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// SUNUWAR SIGN PVO
		{ 0x11BF0, 0x11BF9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// SUNUWAR DIGIT ZERO..SUNUWAR DIGIT NINE
		{ 0x11C00, 0x11C08, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BHAIKSUKI LETTER A..BHAIKSUKI LETTER VOCALIC L
		{ 0x11C0A, 0x11C2E, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BHAIKSUKI LETTER E..BHAIKSUKI LETTER HA
		{ 0x11C2F, 0x11C2F, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BHAIKSUKI VOWEL SIGN AA
		{ 0x11C30, 0x11C36, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BHAIKSUKI VOWEL SIGN I..BHAIKSUKI VOWEL SIGN VOCALIC L
		{ 0x11C38, 0x11C3D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BHAIKSUKI VOWEL SIGN E..BHAIKSUKI SIGN ANUSVARA
		{ 0x11C3E, 0x11C3E, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// BHAIKSUKI SIGN VISARGA
		{ 0x11C3F, 0x11C3F, BidiClass::LeftToRight, GeneralCategory::NonspacingMark },	// BHAIKSUKI SIGN VIRAMA
		{ 0x11C40, 0x11C40, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BHAIKSUKI SIGN AVAGRAHA
		{ 0x11C41, 0x11C45, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// BHAIKSUKI DANDA..BHAIKSUKI GAP FILLER-2
		{ 0x11C50, 0x11C59, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// BHAIKSUKI DIGIT ZERO..BHAIKSUKI DIGIT NINE
		{ 0x11C5A, 0x11C6C, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// BHAIKSUKI NUMBER ONE..BHAIKSUKI HUNDREDS UNIT MARK
		{ 0x11C70, 0x11C71, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// MARCHEN HEAD MARK..MARCHEN MARK SHAD
		{ 0x11C72, 0x11C8F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MARCHEN LETTER KA..MARCHEN LETTER A
		{ 0x11C92, 0x11CA7, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MARCHEN SUBJOINED LETTER KA..MARCHEN SUBJOINED LETTER ZA
		{ 0x11CA9, 0x11CA9, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MARCHEN SUBJOINED LETTER YA
		{ 0x11CAA, 0x11CB0, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MARCHEN SUBJOINED LETTER RA..MARCHEN VOWEL SIGN AA
		{ 0x11CB1, 0x11CB1, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MARCHEN VOWEL SIGN I
		{ 0x11CB2, 0x11CB3, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MARCHEN VOWEL SIGN U..MARCHEN VOWEL SIGN E
		{ 0x11CB4, 0x11CB4, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MARCHEN VOWEL SIGN O
		{ 0x11CB5, 0x11CB6, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MARCHEN SIGN ANUSVARA..MARCHEN SIGN CANDRABINDU
		{ 0x11D00, 0x11D06, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MASARAM GONDI LETTER A..MASARAM GONDI LETTER E
		{ 0x11D08, 0x11D09, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MASARAM GONDI LETTER AI..MASARAM GONDI LETTER O
		{ 0x11D0B, 0x11D30, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MASARAM GONDI LETTER AU..MASARAM GONDI LETTER TRA
		{ 0x11D31, 0x11D36, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MASARAM GONDI VOWEL SIGN AA..MASARAM GONDI VOWEL SIGN VOCALIC R
		{ 0x11D3A, 0x11D3A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MASARAM GONDI VOWEL SIGN E
		{ 0x11D3C, 0x11D3D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MASARAM GONDI VOWEL SIGN AI..MASARAM GONDI VOWEL SIGN O
		{ 0x11D3F, 0x11D45, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MASARAM GONDI VOWEL SIGN AU..MASARAM GONDI VIRAMA
		{ 0x11D46, 0x11D46, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MASARAM GONDI REPHA
		{ 0x11D47, 0x11D47, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MASARAM GONDI RA-KARA
		{ 0x11D50, 0x11D59, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// MASARAM GONDI DIGIT ZERO..MASARAM GONDI DIGIT NINE
		{ 0x11D60, 0x11D65, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUNJALA GONDI LETTER A..GUNJALA GONDI LETTER UU
		{ 0x11D67, 0x11D68, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUNJALA GONDI LETTER EE..GUNJALA GONDI LETTER AI
		{ 0x11D6A, 0x11D89, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUNJALA GONDI LETTER OO..GUNJALA GONDI LETTER SA
		{ 0x11D8A, 0x11D8E, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GUNJALA GONDI VOWEL SIGN AA..GUNJALA GONDI VOWEL SIGN UU
		{ 0x11D90, 0x11D91, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GUNJALA GONDI VOWEL SIGN EE..GUNJALA GONDI VOWEL SIGN AI
		{ 0x11D93, 0x11D94, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GUNJALA GONDI VOWEL SIGN OO..GUNJALA GONDI VOWEL SIGN AU
		{ 0x11D95, 0x11D95, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GUNJALA GONDI SIGN ANUSVARA
		{ 0x11D96, 0x11D96, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GUNJALA GONDI SIGN VISARGA
		{ 0x11D97, 0x11D97, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GUNJALA GONDI VIRAMA
		{ 0x11D98, 0x11D98, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GUNJALA GONDI OM
		{ 0x11DA0, 0x11DA9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// GUNJALA GONDI DIGIT ZERO..GUNJALA GONDI DIGIT NINE
		{ 0x11DB0, 0x11DD8, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TOLONG SIKI LETTER I..TOLONG SIKI LETTER RRH
		{ 0x11DD9, 0x11DD9, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// TOLONG SIKI SIGN SELA
		{ 0x11DDA, 0x11DDB, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TOLONG SIKI SIGN HECAKA..TOLONG SIKI UNGGA
		{ 0x11DE0, 0x11DE9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// TOLONG SIKI DIGIT ZERO..TOLONG SIKI DIGIT NINE
		{ 0x11EE0, 0x11EF2, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MAKASAR LETTER KA..MAKASAR ANGKA
		{ 0x11EF3, 0x11EF4, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MAKASAR VOWEL SIGN I..MAKASAR VOWEL SIGN U
		{ 0x11EF5, 0x11EF6, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MAKASAR VOWEL SIGN E..MAKASAR VOWEL SIGN O
		{ 0x11EF7, 0x11EF8, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// MAKASAR PASSIMBANG..MAKASAR END OF SECTION
		{ 0x11F00, 0x11F01, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KAWI SIGN CANDRABINDU..KAWI SIGN ANUSVARA
		{ 0x11F02, 0x11F02, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KAWI SIGN REPHA
		{ 0x11F03, 0x11F03, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KAWI SIGN VISARGA
		{ 0x11F04, 0x11F10, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KAWI LETTER A..KAWI LETTER O
		{ 0x11F12, 0x11F33, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KAWI LETTER KA..KAWI LETTER JNYA
		{ 0x11F34, 0x11F35, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KAWI VOWEL SIGN AA..KAWI VOWEL SIGN ALTERNATE AA
		{ 0x11F36, 0x11F3A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KAWI VOWEL SIGN I..KAWI VOWEL SIGN VOCALIC R
		{ 0x11F3E, 0x11F3F, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KAWI VOWEL SIGN E..KAWI VOWEL SIGN AI
		{ 0x11F40, 0x11F40, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KAWI VOWEL SIGN EU
		{ 0x11F41, 0x11F41, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// KAWI SIGN KILLER
		{ 0x11F42, 0x11F42, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KAWI CONJOINER
		{ 0x11F43, 0x11F4F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// KAWI DANDA..KAWI PUNCTUATION CLOSING SPIRAL
		{ 0x11F50, 0x11F59, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// KAWI DIGIT ZERO..KAWI DIGIT NINE
		{ 0x11F5A, 0x11F5A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KAWI SIGN NUKTA
		{ 0x11FB0, 0x11FB0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LISU LETTER YHA
		{ 0x11FC0, 0x11FD4, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// TAMIL FRACTION ONE THREE-HUNDRED-AND-TWENTIETH..TAMIL FRACTION DOWNSCALING FACTOR KIIZH
		{ 0x11FD5, 0x11FDC, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// TAMIL SIGN NEL..TAMIL SIGN MUKKURUNI
		{ 0x11FDD, 0x11FE0, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// TAMIL SIGN KAACU..TAMIL SIGN VARAAKAN
		{ 0x11FE1, 0x11FF1, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// TAMIL SIGN PAARAM..TAMIL SIGN VAKAIYARAA
		{ 0x11FFF, 0x11FFF, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// TAMIL PUNCTUATION END OF TEXT
		{ 0x12000, 0x12399, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CUNEIFORM SIGN A..CUNEIFORM SIGN U U
		{ 0x12400, 0x1246E, BidiClass::LeftToRight, GeneralCategory::LetterNumber },	// CUNEIFORM NUMERIC SIGN TWO ASH..CUNEIFORM NUMERIC SIGN NINE U VARIANT FORM
		{ 0x12470, 0x12474, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// CUNEIFORM PUNCTUATION SIGN OLD ASSYRIAN WORD DIVIDER..CUNEIFORM PUNCTUATION SIGN DIAGONAL QUADCOLON
		{ 0x12480, 0x12543, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CUNEIFORM SIGN AB TIMES NUN TENU..CUNEIFORM SIGN ZU5 TIMES THREE DISH TENU
		{ 0x12F90, 0x12FF0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CYPRO-MINOAN SIGN CM001..CYPRO-MINOAN SIGN CM114
		{ 0x12FF1, 0x12FF2, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// CYPRO-MINOAN SIGN CM301..CYPRO-MINOAN SIGN CM302
		{ 0x13000, 0x1342F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// EGYPTIAN HIEROGLYPH A001..EGYPTIAN HIEROGLYPH V011D
		{ 0x13430, 0x1343F, BidiClass::LeftToRight, GeneralCategory::Format },	// EGYPTIAN HIEROGLYPH VERTICAL JOINER..EGYPTIAN HIEROGLYPH END WALLED ENCLOSURE
		{ 0x13440, 0x13440, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// EGYPTIAN HIEROGLYPH MIRROR HORIZONTALLY
		{ 0x13441, 0x13446, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// EGYPTIAN HIEROGLYPH FULL BLANK..EGYPTIAN HIEROGLYPH WIDE LOST SIGN
		{ 0x13447, 0x13455, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// EGYPTIAN HIEROGLYPH MODIFIER DAMAGED AT TOP START..EGYPTIAN HIEROGLYPH MODIFIER DAMAGED
		{ 0x13460, 0x143FA, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// EGYPTIAN HIEROGLYPH-13460..EGYPTIAN HIEROGLYPH-143FA
		{ 0x14400, 0x14646, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ANATOLIAN HIEROGLYPH A001..ANATOLIAN HIEROGLYPH A530
		{ 0x16100, 0x1611D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// GURUNG KHEMA LETTER A..GURUNG KHEMA LETTER SA
		{ 0x1611E, 0x16129, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GURUNG KHEMA VOWEL SIGN AA..GURUNG KHEMA VOWEL LENGTH MARK
		{ 0x1612A, 0x1612C, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// GURUNG KHEMA CONSONANT SIGN MEDIAL YA..GURUNG KHEMA CONSONANT SIGN MEDIAL HA
		{ 0x1612D, 0x1612F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// GURUNG KHEMA SIGN ANUSVARA..GURUNG KHEMA SIGN THOLHOMA
		{ 0x16130, 0x16139, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// GURUNG KHEMA DIGIT ZERO..GURUNG KHEMA DIGIT NINE
		{ 0x16800, 0x16A38, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BAMUM LETTER PHASE-A NGKUE MFON..BAMUM LETTER PHASE-F VUEQ
		{ 0x16A40, 0x16A5E, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MRO LETTER TA..MRO LETTER TEK
		{ 0x16A60, 0x16A69, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// MRO DIGIT ZERO..MRO DIGIT NINE
		{ 0x16A6E, 0x16A6F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// MRO DANDA..MRO DOUBLE DANDA
		{ 0x16A70, 0x16ABE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TANGSA LETTER OZ..TANGSA LETTER ZA
		{ 0x16AC0, 0x16AC9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// TANGSA DIGIT ZERO..TANGSA DIGIT NINE
		{ 0x16AD0, 0x16AED, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// BASSA VAH LETTER ENNI..BASSA VAH LETTER I
		{ 0x16AF0, 0x16AF4, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// BASSA VAH COMBINING HIGH TONE..BASSA VAH COMBINING HIGH-LOW TONE
		{ 0x16AF5, 0x16AF5, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// BASSA VAH FULL STOP
		{ 0x16B00, 0x16B2F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// PAHAWH HMONG VOWEL KEEB..PAHAWH HMONG CONSONANT CAU
		{ 0x16B30, 0x16B36, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// PAHAWH HMONG MARK CIM TUB..PAHAWH HMONG MARK CIM TAUM
		{ 0x16B37, 0x16B3B, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// PAHAWH HMONG SIGN VOS THOM..PAHAWH HMONG SIGN VOS FEEM
		{ 0x16B3C, 0x16B3F, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// PAHAWH HMONG SIGN XYEEM NTXIV..PAHAWH HMONG SIGN XYEEM FAIB
		{ 0x16B40, 0x16B43, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// PAHAWH HMONG SIGN VOS SEEV..PAHAWH HMONG SIGN IB YAM
		{ 0x16B44, 0x16B44, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// PAHAWH HMONG SIGN XAUS
		{ 0x16B45, 0x16B45, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// PAHAWH HMONG SIGN CIM TSOV ROG
		{ 0x16B50, 0x16B59, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// PAHAWH HMONG DIGIT ZERO..PAHAWH HMONG DIGIT NINE
		{ 0x16B5B, 0x16B61, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// PAHAWH HMONG NUMBER TENS..PAHAWH HMONG NUMBER TRILLIONS
		{ 0x16B63, 0x16B77, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// PAHAWH HMONG SIGN VOS LUB..PAHAWH HMONG SIGN CIM NRES TOS
		{ 0x16B7D, 0x16B8F, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// PAHAWH HMONG CLAN SIGN TSHEEJ..PAHAWH HMONG CLAN SIGN VWJ
		{ 0x16D40, 0x16D42, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// KIRAT RAI SIGN ANUSVARA..KIRAT RAI SIGN VISARGA
		{ 0x16D43, 0x16D6A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KIRAT RAI LETTER A..KIRAT RAI VOWEL SIGN AU
		{ 0x16D6B, 0x16D6C, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// KIRAT RAI SIGN VIRAMA..KIRAT RAI SIGN SAAT
		{ 0x16D6D, 0x16D6F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// KIRAT RAI SIGN YUPI..KIRAT RAI DOUBLE DANDA
		{ 0x16D70, 0x16D79, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// KIRAT RAI DIGIT ZERO..KIRAT RAI DIGIT NINE
		{ 0x16E40, 0x16E7F, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MEDEFAIDRIN CAPITAL LETTER M..MEDEFAIDRIN SMALL LETTER Y
		{ 0x16E80, 0x16E96, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// MEDEFAIDRIN DIGIT ZERO..MEDEFAIDRIN DIGIT THREE ALTERNATE FORM
		{ 0x16E97, 0x16E9A, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// MEDEFAIDRIN COMMA..MEDEFAIDRIN EXCLAMATION OH
		{ 0x16EA0, 0x16EB8, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// BERIA ERFE CAPITAL LETTER ARKAB..BERIA ERFE CAPITAL LETTER AY
		{ 0x16EBB, 0x16ED3, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// BERIA ERFE SMALL LETTER ARKAB..BERIA ERFE SMALL LETTER AY
		{ 0x16F00, 0x16F4A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MIAO LETTER PA..MIAO LETTER RTE
		{ 0x16F4F, 0x16F4F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MIAO SIGN CONSONANT MODIFIER BAR
		{ 0x16F50, 0x16F50, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// MIAO LETTER NASALIZATION
		{ 0x16F51, 0x16F87, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MIAO SIGN ASPIRATION..MIAO VOWEL SIGN UI
		{ 0x16F8F, 0x16F92, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MIAO TONE RIGHT..MIAO TONE BELOW
		{ 0x16F93, 0x16F9F, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MIAO LETTER TONE-2..MIAO LETTER REFORMED TONE-8
		{ 0x16FE0, 0x16FE1, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// TANGUT ITERATION MARK..NUSHU ITERATION MARK
		{ 0x16FE2, 0x16FE2, BidiClass::OtherNeutral, GeneralCategory::OtherPunctuation },	// OLD CHINESE HOOK MARK
		{ 0x16FE3, 0x16FE3, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// OLD CHINESE ITERATION MARK
		{ 0x16FE4, 0x16FE4, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// KHITAN SMALL SCRIPT FILLER
		{ 0x16FF0, 0x16FF1, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// VIETNAMESE ALTERNATE READING MARK CA..VIETNAMESE ALTERNATE READING MARK NHAY
		{ 0x16FF2, 0x16FF3, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// CHINESE SMALL SIMPLIFIED ER..CHINESE SMALL TRADITIONAL ER
		{ 0x16FF4, 0x16FF6, BidiClass::LeftToRight, GeneralCategory::LetterNumber },	// YANGQIN SIGN SLOW ONE BEAT..YANGQIN SIGN SLOW TWO BEATS
		{ 0x17000, 0x18CD5, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TANGUT IDEOGRAPH-17000..KHITAN SMALL SCRIPT CHARACTER-18CD5
		{ 0x18CFF, 0x18D1E, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KHITAN SMALL SCRIPT CHARACTER-18CFF..TANGUT IDEOGRAPH-18D1E
		{ 0x18D80, 0x18DF2, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TANGUT COMPONENT-769..TANGUT COMPONENT-883
		{ 0x1AFF0, 0x1AFF3, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// KATAKANA LETTER MINNAN TONE-2..KATAKANA LETTER MINNAN TONE-5
		{ 0x1AFF5, 0x1AFFB, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// KATAKANA LETTER MINNAN TONE-7..KATAKANA LETTER MINNAN NASALIZED TONE-5
		{ 0x1AFFD, 0x1AFFE, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// KATAKANA LETTER MINNAN NASALIZED TONE-7..KATAKANA LETTER MINNAN NASALIZED TONE-8
		{ 0x1B000, 0x1B122, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KATAKANA LETTER ARCHAIC E..KATAKANA LETTER ARCHAIC WU
		{ 0x1B132, 0x1B132, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HIRAGANA LETTER SMALL KO
		{ 0x1B150, 0x1B152, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// HIRAGANA LETTER SMALL WI..HIRAGANA LETTER SMALL WO
		{ 0x1B155, 0x1B155, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KATAKANA LETTER SMALL KO
		{ 0x1B164, 0x1B167, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// KATAKANA LETTER SMALL WI..KATAKANA LETTER SMALL N
		{ 0x1B170, 0x1B2FB, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// NUSHU CHARACTER-1B170..NUSHU CHARACTER-1B2FB
		{ 0x1BC00, 0x1BC6A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DUPLOYAN LETTER H..DUPLOYAN LETTER VOCALIC M
		{ 0x1BC70, 0x1BC7C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DUPLOYAN AFFIX LEFT HORIZONTAL SECANT..DUPLOYAN AFFIX ATTACHED TANGENT HOOK
		{ 0x1BC80, 0x1BC88, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DUPLOYAN AFFIX HIGH ACUTE..DUPLOYAN AFFIX HIGH VERTICAL
		{ 0x1BC90, 0x1BC99, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// DUPLOYAN AFFIX LOW ACUTE..DUPLOYAN AFFIX LOW ARROW
		{ 0x1BC9C, 0x1BC9C, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// DUPLOYAN SIGN O WITH CROSS
		{ 0x1BC9D, 0x1BC9E, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// DUPLOYAN THICK LETTER SELECTOR..DUPLOYAN DOUBLE MARK
		{ 0x1BC9F, 0x1BC9F, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// DUPLOYAN PUNCTUATION CHINOOK FULL STOP
		{ 0x1BCA0, 0x1BCA3, BidiClass::BoundaryNeutral, GeneralCategory::Format },	// SHORTHAND FORMAT LETTER OVERLAP..SHORTHAND FORMAT UP STEP
		{ 0x1CC00, 0x1CCD5, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// UP-POINTING GO-KART..LOWER RIGHT QUADRANT STANDING KNIGHT
		{ 0x1CCD6, 0x1CCEF, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// OUTLINED LATIN CAPITAL LETTER A..OUTLINED LATIN CAPITAL LETTER Z
		{ 0x1CCF0, 0x1CCF9, BidiClass::EuropeanNumber, GeneralCategory::DecimalNumber },	// OUTLINED DIGIT ZERO..OUTLINED DIGIT NINE
		{ 0x1CCFA, 0x1CCFC, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// SNAKE SYMBOL..NOSE SYMBOL
		{ 0x1CD00, 0x1CEB3, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// BLOCK OCTANT-3..BLACK RIGHT TRIANGLE CARET
		{ 0x1CEBA, 0x1CED0, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// FRAGILE SYMBOL..LEUKOTHEA
		{ 0x1CEE0, 0x1CEEF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// GEOMANTIC FIGURE POPULUS..GEOMANTIC FIGURE VIA
		{ 0x1CEF0, 0x1CEF0, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// MEDIUM SMALL WHITE CIRCLE WITH HORIZONTAL BAR
		{ 0x1CF00, 0x1CF2D, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ZNAMENNY COMBINING MARK GORAZDO NIZKO S KRYZHEM ON LEFT..ZNAMENNY COMBINING MARK KRYZH ON LEFT
		{ 0x1CF30, 0x1CF46, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ZNAMENNY COMBINING TONAL RANGE MARK MRACHNO..ZNAMENNY PRIZNAK MODIFIER ROG
		{ 0x1CF50, 0x1CFC3, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// ZNAMENNY NEUME KRYUK..ZNAMENNY NEUME PAUK
		{ 0x1D000, 0x1D0F5, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// BYZANTINE MUSICAL SYMBOL PSILI..BYZANTINE MUSICAL SYMBOL GORGON NEO KATO
		{ 0x1D100, 0x1D126, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// MUSICAL SYMBOL SINGLE BARLINE..MUSICAL SYMBOL DRUM CLEF-2
		{ 0x1D129, 0x1D164, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// MUSICAL SYMBOL MULTIPLE MEASURE REST..MUSICAL SYMBOL ONE HUNDRED TWENTY-EIGHTH NOTE
		{ 0x1D165, 0x1D166, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MUSICAL SYMBOL COMBINING STEM..MUSICAL SYMBOL COMBINING SPRECHGESANG STEM
		{ 0x1D167, 0x1D169, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MUSICAL SYMBOL COMBINING TREMOLO-1..MUSICAL SYMBOL COMBINING TREMOLO-3
		{ 0x1D16A, 0x1D16C, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// MUSICAL SYMBOL FINGERED TREMOLO-1..MUSICAL SYMBOL FINGERED TREMOLO-3
		{ 0x1D16D, 0x1D172, BidiClass::LeftToRight, GeneralCategory::SpacingMark },	// MUSICAL SYMBOL COMBINING AUGMENTATION DOT..MUSICAL SYMBOL COMBINING FLAG-5
		{ 0x1D173, 0x1D17A, BidiClass::BoundaryNeutral, GeneralCategory::Format },	// MUSICAL SYMBOL BEGIN BEAM..MUSICAL SYMBOL END PHRASE
		{ 0x1D17B, 0x1D182, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MUSICAL SYMBOL COMBINING ACCENT..MUSICAL SYMBOL COMBINING LOURE
		{ 0x1D183, 0x1D184, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// MUSICAL SYMBOL ARPEGGIATO UP..MUSICAL SYMBOL ARPEGGIATO DOWN
		{ 0x1D185, 0x1D18B, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MUSICAL SYMBOL COMBINING DOIT..MUSICAL SYMBOL COMBINING TRIPLE TONGUE
		{ 0x1D18C, 0x1D1A9, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// MUSICAL SYMBOL RINFORZANDO..MUSICAL SYMBOL DEGREE SLASH
		{ 0x1D1AA, 0x1D1AD, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MUSICAL SYMBOL COMBINING DOWN BOW..MUSICAL SYMBOL COMBINING SNAP PIZZICATO
		{ 0x1D1AE, 0x1D1E8, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// MUSICAL SYMBOL PEDAL MARK..MUSICAL SYMBOL KIEVAN FLAT SIGN
		{ 0x1D1E9, 0x1D1EA, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// MUSICAL SYMBOL SORI..MUSICAL SYMBOL KORON
		{ 0x1D200, 0x1D241, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// GREEK VOCAL NOTATION SYMBOL-1..GREEK INSTRUMENTAL NOTATION SYMBOL-54
		{ 0x1D242, 0x1D244, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING GREEK MUSICAL TRISEME..COMBINING GREEK MUSICAL PENTASEME
		{ 0x1D245, 0x1D245, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// GREEK MUSICAL LEIMMA
		{ 0x1D2C0, 0x1D2D3, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// KAKTOVIK NUMERAL ZERO..KAKTOVIK NUMERAL NINETEEN
		{ 0x1D2E0, 0x1D2F3, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// MAYAN NUMERAL ZERO..MAYAN NUMERAL NINETEEN
		{ 0x1D300, 0x1D356, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// MONOGRAM FOR EARTH..TETRAGRAM FOR FOSTERING
		{ 0x1D360, 0x1D378, BidiClass::LeftToRight, GeneralCategory::OtherNumber },	// COUNTING ROD UNIT DIGIT ONE..TALLY MARK FIVE
		{ 0x1D400, 0x1D454, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL BOLD CAPITAL A..MATHEMATICAL ITALIC SMALL G
		{ 0x1D456, 0x1D49C, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL ITALIC SMALL I..MATHEMATICAL SCRIPT CAPITAL A
		{ 0x1D49E, 0x1D49F, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL SCRIPT CAPITAL C..MATHEMATICAL SCRIPT CAPITAL D
		{ 0x1D4A2, 0x1D4A2, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL SCRIPT CAPITAL G
		{ 0x1D4A5, 0x1D4A6, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL SCRIPT CAPITAL J..MATHEMATICAL SCRIPT CAPITAL K
		{ 0x1D4A9, 0x1D4AC, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL SCRIPT CAPITAL N..MATHEMATICAL SCRIPT CAPITAL Q
		{ 0x1D4AE, 0x1D4B9, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL SCRIPT CAPITAL S..MATHEMATICAL SCRIPT SMALL D
		{ 0x1D4BB, 0x1D4BB, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL SCRIPT SMALL F
		{ 0x1D4BD, 0x1D4C3, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL SCRIPT SMALL H..MATHEMATICAL SCRIPT SMALL N
		{ 0x1D4C5, 0x1D505, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL SCRIPT SMALL P..MATHEMATICAL FRAKTUR CAPITAL B
		{ 0x1D507, 0x1D50A, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL FRAKTUR CAPITAL D..MATHEMATICAL FRAKTUR CAPITAL G
		{ 0x1D50D, 0x1D514, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL FRAKTUR CAPITAL J..MATHEMATICAL FRAKTUR CAPITAL Q
		{ 0x1D516, 0x1D51C, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL FRAKTUR CAPITAL S..MATHEMATICAL FRAKTUR CAPITAL Y
		{ 0x1D51E, 0x1D539, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL FRAKTUR SMALL A..MATHEMATICAL DOUBLE-STRUCK CAPITAL B
		{ 0x1D53B, 0x1D53E, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL DOUBLE-STRUCK CAPITAL D..MATHEMATICAL DOUBLE-STRUCK CAPITAL G
		{ 0x1D540, 0x1D544, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL DOUBLE-STRUCK CAPITAL I..MATHEMATICAL DOUBLE-STRUCK CAPITAL M
		{ 0x1D546, 0x1D546, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL DOUBLE-STRUCK CAPITAL O
		{ 0x1D54A, 0x1D550, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL DOUBLE-STRUCK CAPITAL S..MATHEMATICAL DOUBLE-STRUCK CAPITAL Y
		{ 0x1D552, 0x1D6A5, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL DOUBLE-STRUCK SMALL A..MATHEMATICAL ITALIC SMALL DOTLESS J
		{ 0x1D6A8, 0x1D6C0, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL BOLD CAPITAL ALPHA..MATHEMATICAL BOLD CAPITAL OMEGA
		{ 0x1D6C1, 0x1D6C1, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// MATHEMATICAL BOLD NABLA
		{ 0x1D6C2, 0x1D6DA, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL BOLD SMALL ALPHA..MATHEMATICAL BOLD SMALL OMEGA
		{ 0x1D6DB, 0x1D6DB, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// MATHEMATICAL BOLD PARTIAL DIFFERENTIAL
		{ 0x1D6DC, 0x1D6FA, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL BOLD EPSILON SYMBOL..MATHEMATICAL ITALIC CAPITAL OMEGA
		{ 0x1D6FB, 0x1D6FB, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// MATHEMATICAL ITALIC NABLA
		{ 0x1D6FC, 0x1D714, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL ITALIC SMALL ALPHA..MATHEMATICAL ITALIC SMALL OMEGA
		{ 0x1D715, 0x1D715, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// MATHEMATICAL ITALIC PARTIAL DIFFERENTIAL
		{ 0x1D716, 0x1D734, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL ITALIC EPSILON SYMBOL..MATHEMATICAL BOLD ITALIC CAPITAL OMEGA
		{ 0x1D735, 0x1D735, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// MATHEMATICAL BOLD ITALIC NABLA
		{ 0x1D736, 0x1D74E, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL BOLD ITALIC SMALL ALPHA..MATHEMATICAL BOLD ITALIC SMALL OMEGA
		{ 0x1D74F, 0x1D74F, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// MATHEMATICAL BOLD ITALIC PARTIAL DIFFERENTIAL
		{ 0x1D750, 0x1D76E, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL BOLD ITALIC EPSILON SYMBOL..MATHEMATICAL SANS-SERIF BOLD CAPITAL OMEGA
		{ 0x1D76F, 0x1D76F, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// MATHEMATICAL SANS-SERIF BOLD NABLA
		{ 0x1D770, 0x1D788, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL SANS-SERIF BOLD SMALL ALPHA..MATHEMATICAL SANS-SERIF BOLD SMALL OMEGA
		{ 0x1D789, 0x1D789, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// MATHEMATICAL SANS-SERIF BOLD PARTIAL DIFFERENTIAL
		{ 0x1D78A, 0x1D7A8, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL SANS-SERIF BOLD EPSILON SYMBOL..MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL OMEGA
		{ 0x1D7A9, 0x1D7A9, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// MATHEMATICAL SANS-SERIF BOLD ITALIC NABLA
		{ 0x1D7AA, 0x1D7C2, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL ALPHA..MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL OMEGA
		{ 0x1D7C3, 0x1D7C3, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// MATHEMATICAL SANS-SERIF BOLD ITALIC PARTIAL DIFFERENTIAL
		{ 0x1D7C4, 0x1D7CB, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// MATHEMATICAL SANS-SERIF BOLD ITALIC EPSILON SYMBOL..MATHEMATICAL BOLD SMALL DIGAMMA
		{ 0x1D7CE, 0x1D7FF, BidiClass::EuropeanNumber, GeneralCategory::DecimalNumber },	// MATHEMATICAL BOLD DIGIT ZERO..MATHEMATICAL MONOSPACE DIGIT NINE
		{ 0x1D800, 0x1D9FF, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// SIGNWRITING HAND-FIST INDEX..SIGNWRITING HEAD
		{ 0x1DA00, 0x1DA36, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SIGNWRITING HEAD RIM..SIGNWRITING AIR SUCKING IN
		{ 0x1DA37, 0x1DA3A, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// SIGNWRITING AIR BLOW SMALL ROTATIONS..SIGNWRITING BREATH EXHALE
		{ 0x1DA3B, 0x1DA6C, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SIGNWRITING MOUTH CLOSED NEUTRAL..SIGNWRITING EXCITEMENT
		{ 0x1DA6D, 0x1DA74, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// SIGNWRITING SHOULDER HIP SPINE..SIGNWRITING TORSO-FLOORPLANE TWISTING
		{ 0x1DA75, 0x1DA75, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SIGNWRITING UPPER BODY TILTING FROM HIP JOINTS
		{ 0x1DA76, 0x1DA83, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// SIGNWRITING LIMB COMBINATION..SIGNWRITING LOCATION DEPTH
		{ 0x1DA84, 0x1DA84, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SIGNWRITING LOCATION HEAD NECK
		{ 0x1DA85, 0x1DA86, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// SIGNWRITING LOCATION TORSO..SIGNWRITING LOCATION LIMBS DIGITS
		{ 0x1DA87, 0x1DA8B, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// SIGNWRITING COMMA..SIGNWRITING PARENTHESIS
		{ 0x1DA9B, 0x1DA9F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SIGNWRITING FILL MODIFIER-2..SIGNWRITING FILL MODIFIER-6
		{ 0x1DAA1, 0x1DAAF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// SIGNWRITING ROTATION MODIFIER-2..SIGNWRITING ROTATION MODIFIER-16
		{ 0x1DF00, 0x1DF09, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN SMALL LETTER FENG DIGRAPH WITH TRILL..LATIN SMALL LETTER T WITH HOOK AND RETROFLEX HOOK
		{ 0x1DF0A, 0x1DF0A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// LATIN LETTER RETROFLEX CLICK WITH RETROFLEX HOOK
		{ 0x1DF0B, 0x1DF1E, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN SMALL LETTER ESH WITH DOUBLE BAR..LATIN SMALL LETTER S WITH CURL
		{ 0x1DF25, 0x1DF2A, BidiClass::LeftToRight, GeneralCategory::CasedLetter },	// LATIN SMALL LETTER D WITH MID-HEIGHT LEFT HOOK..LATIN SMALL LETTER T WITH MID-HEIGHT LEFT HOOK
		{ 0x1E000, 0x1E006, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING GLAGOLITIC LETTER AZU..COMBINING GLAGOLITIC LETTER ZHIVETE
		{ 0x1E008, 0x1E018, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING GLAGOLITIC LETTER ZEMLJA..COMBINING GLAGOLITIC LETTER HERU
		{ 0x1E01B, 0x1E021, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING GLAGOLITIC LETTER SHTA..COMBINING GLAGOLITIC LETTER YATI
		{ 0x1E023, 0x1E024, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING GLAGOLITIC LETTER YU..COMBINING GLAGOLITIC LETTER SMALL YUS
		{ 0x1E026, 0x1E02A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING GLAGOLITIC LETTER YO..COMBINING GLAGOLITIC LETTER FITA
		{ 0x1E030, 0x1E06D, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// MODIFIER LETTER CYRILLIC SMALL A..MODIFIER LETTER CYRILLIC SMALL STRAIGHT U WITH STROKE
		{ 0x1E08F, 0x1E08F, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// COMBINING CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I
		{ 0x1E100, 0x1E12C, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// NYIAKENG PUACHUE HMONG LETTER MA..NYIAKENG PUACHUE HMONG LETTER W
		{ 0x1E130, 0x1E136, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// NYIAKENG PUACHUE HMONG TONE-B..NYIAKENG PUACHUE HMONG TONE-D
		{ 0x1E137, 0x1E13D, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// NYIAKENG PUACHUE HMONG SIGN FOR PERSON..NYIAKENG PUACHUE HMONG SYLLABLE LENGTHENER
		{ 0x1E140, 0x1E149, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// NYIAKENG PUACHUE HMONG DIGIT ZERO..NYIAKENG PUACHUE HMONG DIGIT NINE
		{ 0x1E14E, 0x1E14E, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// NYIAKENG PUACHUE HMONG LOGOGRAM NYAJ
		{ 0x1E14F, 0x1E14F, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// NYIAKENG PUACHUE HMONG CIRCLED CA
		{ 0x1E290, 0x1E2AD, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TOTO LETTER PA..TOTO LETTER A
		{ 0x1E2AE, 0x1E2AE, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TOTO SIGN RISING TONE
		{ 0x1E2C0, 0x1E2EB, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// WANCHO LETTER AA..WANCHO LETTER YIH
		{ 0x1E2EC, 0x1E2EF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// WANCHO TONE TUP..WANCHO TONE KOINI
		{ 0x1E2F0, 0x1E2F9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// WANCHO DIGIT ZERO..WANCHO DIGIT NINE
		{ 0x1E2FF, 0x1E2FF, BidiClass::EuropeanTerminator, GeneralCategory::CurrencySymbol },	// WANCHO NGUN SIGN
		{ 0x1E4D0, 0x1E4EA, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// NAG MUNDARI LETTER O..NAG MUNDARI LETTER ELL
		{ 0x1E4EB, 0x1E4EB, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// NAG MUNDARI SIGN OJOD
		{ 0x1E4EC, 0x1E4EF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// NAG MUNDARI SIGN MUHOR..NAG MUNDARI SIGN SUTUH
		{ 0x1E4F0, 0x1E4F9, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// NAG MUNDARI DIGIT ZERO..NAG MUNDARI DIGIT NINE
		{ 0x1E5D0, 0x1E5ED, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// OL ONAL LETTER O..OL ONAL LETTER EG
		{ 0x1E5EE, 0x1E5EF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// OL ONAL SIGN MU..OL ONAL SIGN IKIR
		{ 0x1E5F0, 0x1E5F0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// OL ONAL SIGN HODDOND
		{ 0x1E5F1, 0x1E5FA, BidiClass::LeftToRight, GeneralCategory::DecimalNumber },	// OL ONAL DIGIT ZERO..OL ONAL DIGIT NINE
		{ 0x1E5FF, 0x1E5FF, BidiClass::LeftToRight, GeneralCategory::OtherPunctuation },	// OL ONAL ABBREVIATION SIGN
		{ 0x1E6C0, 0x1E6DE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI YO LETTER LOW KO..TAI YO LETTER HIGH KVO
		{ 0x1E6E0, 0x1E6E2, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI YO LETTER AA..TAI YO LETTER UE
		{ 0x1E6E3, 0x1E6E3, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI YO SIGN UE
		{ 0x1E6E4, 0x1E6E5, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI YO LETTER U..TAI YO LETTER AE
		{ 0x1E6E6, 0x1E6E6, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI YO SIGN AU
		{ 0x1E6E7, 0x1E6ED, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI YO LETTER O..TAI YO LETTER AUE
		{ 0x1E6EE, 0x1E6EF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI YO SIGN AY..TAI YO SIGN ANG
		{ 0x1E6F0, 0x1E6F4, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI YO LETTER AN..TAI YO LETTER AP
		{ 0x1E6F5, 0x1E6F5, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// TAI YO SIGN OM
		{ 0x1E6FE, 0x1E6FE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// TAI YO SYMBOL MUEANG
		{ 0x1E6FF, 0x1E6FF, BidiClass::LeftToRight, GeneralCategory::ModifierLetter },	// TAI YO XAM LAI
		{ 0x1E7E0, 0x1E7E6, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE HHYA..ETHIOPIC SYLLABLE HHYO
		{ 0x1E7E8, 0x1E7EB, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE GURAGE HHWA..ETHIOPIC SYLLABLE HHWE
		{ 0x1E7ED, 0x1E7EE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE GURAGE MWI..ETHIOPIC SYLLABLE GURAGE MWEE
		{ 0x1E7F0, 0x1E7FE, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// ETHIOPIC SYLLABLE GURAGE QWI..ETHIOPIC SYLLABLE GURAGE PWEE
		{ 0x1E800, 0x1E8C4, BidiClass::RightToLeft, GeneralCategory::OtherLetter },	// MENDE KIKAKUI SYLLABLE M001 KI..MENDE KIKAKUI SYLLABLE M060 NYON
		{ 0x1E8C7, 0x1E8CF, BidiClass::RightToLeft, GeneralCategory::OtherNumber },	// MENDE KIKAKUI DIGIT ONE..MENDE KIKAKUI DIGIT NINE
		{ 0x1E8D0, 0x1E8D6, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// MENDE KIKAKUI COMBINING NUMBER TEENS..MENDE KIKAKUI COMBINING NUMBER MILLIONS
		{ 0x1E900, 0x1E943, BidiClass::RightToLeft, GeneralCategory::CasedLetter },	// ADLAM CAPITAL LETTER ALIF..ADLAM SMALL LETTER SHA
		{ 0x1E944, 0x1E94A, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// ADLAM ALIF LENGTHENER..ADLAM NUKTA
		{ 0x1E94B, 0x1E94B, BidiClass::RightToLeft, GeneralCategory::ModifierLetter },	// ADLAM NASALIZATION MARK
		{ 0x1E950, 0x1E959, BidiClass::RightToLeft, GeneralCategory::DecimalNumber },	// ADLAM DIGIT ZERO..ADLAM DIGIT NINE
		{ 0x1E95E, 0x1E95F, BidiClass::RightToLeft, GeneralCategory::OtherPunctuation },	// ADLAM INITIAL EXCLAMATION MARK..ADLAM INITIAL QUESTION MARK
		{ 0x1EC71, 0x1ECAB, BidiClass::ArabicLetter, GeneralCategory::OtherNumber },	// INDIC SIYAQ NUMBER ONE..INDIC SIYAQ NUMBER PREFIXED NINE
		{ 0x1ECAC, 0x1ECAC, BidiClass::ArabicLetter, GeneralCategory::OtherSymbol },	// INDIC SIYAQ PLACEHOLDER
		{ 0x1ECAD, 0x1ECAF, BidiClass::ArabicLetter, GeneralCategory::OtherNumber },	// INDIC SIYAQ FRACTION ONE QUARTER..INDIC SIYAQ FRACTION THREE QUARTERS
		{ 0x1ECB0, 0x1ECB0, BidiClass::ArabicLetter, GeneralCategory::CurrencySymbol },	// INDIC SIYAQ RUPEE MARK
		{ 0x1ECB1, 0x1ECB4, BidiClass::ArabicLetter, GeneralCategory::OtherNumber },	// INDIC SIYAQ NUMBER ALTERNATE ONE..INDIC SIYAQ ALTERNATE LAKH MARK
		{ 0x1ED01, 0x1ED2D, BidiClass::ArabicLetter, GeneralCategory::OtherNumber },	// OTTOMAN SIYAQ NUMBER ONE..OTTOMAN SIYAQ NUMBER NINETY THOUSAND
		{ 0x1ED2E, 0x1ED2E, BidiClass::ArabicLetter, GeneralCategory::OtherSymbol },	// OTTOMAN SIYAQ MARRATAN
		{ 0x1ED2F, 0x1ED3D, BidiClass::ArabicLetter, GeneralCategory::OtherNumber },	// OTTOMAN SIYAQ ALTERNATE NUMBER TWO..OTTOMAN SIYAQ FRACTION ONE SIXTH
		{ 0x1EE00, 0x1EE03, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL ALEF..ARABIC MATHEMATICAL DAL
		{ 0x1EE05, 0x1EE1F, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL WAW..ARABIC MATHEMATICAL DOTLESS QAF
		{ 0x1EE21, 0x1EE22, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL INITIAL BEH..ARABIC MATHEMATICAL INITIAL JEEM
		{ 0x1EE24, 0x1EE24, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL INITIAL HEH
		{ 0x1EE27, 0x1EE27, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL INITIAL HAH
		{ 0x1EE29, 0x1EE32, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL INITIAL YEH..ARABIC MATHEMATICAL INITIAL QAF
		{ 0x1EE34, 0x1EE37, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL INITIAL SHEEN..ARABIC MATHEMATICAL INITIAL KHAH
		{ 0x1EE39, 0x1EE39, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL INITIAL DAD
		{ 0x1EE3B, 0x1EE3B, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL INITIAL GHAIN
		{ 0x1EE42, 0x1EE42, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL TAILED JEEM
		{ 0x1EE47, 0x1EE47, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL TAILED HAH
		{ 0x1EE49, 0x1EE49, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL TAILED YEH
		{ 0x1EE4B, 0x1EE4B, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL TAILED LAM
		{ 0x1EE4D, 0x1EE4F, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL TAILED NOON..ARABIC MATHEMATICAL TAILED AIN
		{ 0x1EE51, 0x1EE52, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL TAILED SAD..ARABIC MATHEMATICAL TAILED QAF
		{ 0x1EE54, 0x1EE54, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL TAILED SHEEN
		{ 0x1EE57, 0x1EE57, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL TAILED KHAH
		{ 0x1EE59, 0x1EE59, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL TAILED DAD
		{ 0x1EE5B, 0x1EE5B, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL TAILED GHAIN
		{ 0x1EE5D, 0x1EE5D, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL TAILED DOTLESS NOON
		{ 0x1EE5F, 0x1EE5F, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL TAILED DOTLESS QAF
		{ 0x1EE61, 0x1EE62, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED BEH..ARABIC MATHEMATICAL STRETCHED JEEM
		{ 0x1EE64, 0x1EE64, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED HEH
		{ 0x1EE67, 0x1EE6A, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED HAH..ARABIC MATHEMATICAL STRETCHED KAF
		{ 0x1EE6C, 0x1EE72, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED MEEM..ARABIC MATHEMATICAL STRETCHED QAF
		{ 0x1EE74, 0x1EE77, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED SHEEN..ARABIC MATHEMATICAL STRETCHED KHAH
		{ 0x1EE79, 0x1EE7C, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED DAD..ARABIC MATHEMATICAL STRETCHED DOTLESS BEH
		{ 0x1EE7E, 0x1EE7E, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED DOTLESS FEH
		{ 0x1EE80, 0x1EE89, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL LOOPED ALEF..ARABIC MATHEMATICAL LOOPED YEH
		{ 0x1EE8B, 0x1EE9B, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL LOOPED LAM..ARABIC MATHEMATICAL LOOPED GHAIN
		{ 0x1EEA1, 0x1EEA3, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL DOUBLE-STRUCK BEH..ARABIC MATHEMATICAL DOUBLE-STRUCK DAL
		{ 0x1EEA5, 0x1EEA9, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL DOUBLE-STRUCK WAW..ARABIC MATHEMATICAL DOUBLE-STRUCK YEH
		{ 0x1EEAB, 0x1EEBB, BidiClass::ArabicLetter, GeneralCategory::OtherLetter },	// ARABIC MATHEMATICAL DOUBLE-STRUCK LAM..ARABIC MATHEMATICAL DOUBLE-STRUCK GHAIN
		{ 0x1EEF0, 0x1EEF1, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// ARABIC MATHEMATICAL OPERATOR MEEM WITH HAH WITH TATWEEL..ARABIC MATHEMATICAL OPERATOR HAH WITH DAL
		{ 0x1F000, 0x1F02B, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// MAHJONG TILE EAST WIND..MAHJONG TILE BACK
		{ 0x1F030, 0x1F093, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// DOMINO TILE HORIZONTAL BACK..DOMINO TILE VERTICAL-06-06
		{ 0x1F0A0, 0x1F0AE, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// PLAYING CARD BACK..PLAYING CARD KING OF SPADES
		{ 0x1F0B1, 0x1F0BF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// PLAYING CARD ACE OF HEARTS..PLAYING CARD RED JOKER
		{ 0x1F0C1, 0x1F0CF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// PLAYING CARD ACE OF DIAMONDS..PLAYING CARD BLACK JOKER
		{ 0x1F0D1, 0x1F0F5, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// PLAYING CARD ACE OF CLUBS..PLAYING CARD TRUMP-21
		{ 0x1F100, 0x1F10A, BidiClass::EuropeanNumber, GeneralCategory::OtherNumber },	// DIGIT ZERO FULL STOP..DIGIT NINE COMMA
		{ 0x1F10B, 0x1F10C, BidiClass::OtherNeutral, GeneralCategory::OtherNumber },	// DINGBAT CIRCLED SANS-SERIF DIGIT ZERO..DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ZERO
		{ 0x1F10D, 0x1F10F, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// CIRCLED ZERO WITH SLASH..CIRCLED DOLLAR SIGN WITH OVERLAID BACKSLASH
		{ 0x1F110, 0x1F12E, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// PARENTHESIZED LATIN CAPITAL LETTER A..CIRCLED WZ
		{ 0x1F12F, 0x1F12F, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// COPYLEFT SYMBOL
		{ 0x1F130, 0x1F169, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// SQUARED LATIN CAPITAL LETTER A..NEGATIVE CIRCLED LATIN CAPITAL LETTER Z
		{ 0x1F16A, 0x1F16F, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// RAISED MC SIGN..CIRCLED HUMAN FIGURE
		{ 0x1F170, 0x1F1AC, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// NEGATIVE SQUARED LATIN CAPITAL LETTER A..SQUARED VOD
		{ 0x1F1AD, 0x1F1AD, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// MASK WORK SYMBOL
		{ 0x1F1E6, 0x1F202, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// REGIONAL INDICATOR SYMBOL LETTER A..SQUARED KATAKANA SA
		{ 0x1F210, 0x1F23B, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// SQUARED CJK UNIFIED IDEOGRAPH-624B..SQUARED CJK UNIFIED IDEOGRAPH-914D
		{ 0x1F240, 0x1F248, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// TORTOISE SHELL BRACKETED CJK UNIFIED IDEOGRAPH-672C..TORTOISE SHELL BRACKETED CJK UNIFIED IDEOGRAPH-6557
		{ 0x1F250, 0x1F251, BidiClass::LeftToRight, GeneralCategory::OtherSymbol },	// CIRCLED IDEOGRAPH ADVANTAGE..CIRCLED IDEOGRAPH ACCEPT
		{ 0x1F260, 0x1F265, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ROUNDED SYMBOL FOR FU..ROUNDED SYMBOL FOR CAI
		{ 0x1F300, 0x1F3FA, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// CYCLONE..AMPHORA
		{ 0x1F3FB, 0x1F3FF, BidiClass::OtherNeutral, GeneralCategory::ModifierSymbol },	// EMOJI MODIFIER FITZPATRICK TYPE-1-2..EMOJI MODIFIER FITZPATRICK TYPE-6
		{ 0x1F400, 0x1F6D8, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// RAT..LANDSLIDE
		{ 0x1F6DC, 0x1F6EC, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// WIRELESS..AIRPLANE ARRIVING
		{ 0x1F6F0, 0x1F6FC, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// SATELLITE..ROLLER SKATE
		{ 0x1F700, 0x1F7D9, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ALCHEMICAL SYMBOL FOR QUINTESSENCE..NINE POINTED WHITE STAR
		{ 0x1F7E0, 0x1F7EB, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// LARGE ORANGE CIRCLE..LARGE BROWN SQUARE
		{ 0x1F7F0, 0x1F7F0, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// HEAVY EQUALS SIGN
		{ 0x1F800, 0x1F80B, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// LEFTWARDS ARROW WITH SMALL TRIANGLE ARROWHEAD..DOWNWARDS ARROW WITH LARGE TRIANGLE ARROWHEAD
		{ 0x1F810, 0x1F847, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// LEFTWARDS ARROW WITH SMALL EQUILATERAL ARROWHEAD..DOWNWARDS HEAVY ARROW
		{ 0x1F850, 0x1F859, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// LEFTWARDS SANS-SERIF ARROW..UP DOWN SANS-SERIF ARROW
		{ 0x1F860, 0x1F887, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// WIDE-HEADED LEFTWARDS LIGHT BARB ARROW..WIDE-HEADED SOUTH WEST VERY HEAVY BARB ARROW
		{ 0x1F890, 0x1F8AD, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// LEFTWARDS TRIANGLE ARROWHEAD..WHITE ARROW SHAFT WIDTH TWO THIRDS
		{ 0x1F8B0, 0x1F8BB, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ARROW POINTING UPWARDS THEN NORTH WEST..SOUTH WEST ARROW FROM BAR
		{ 0x1F8C0, 0x1F8C1, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// LEFTWARDS ARROW FROM DOWNWARDS ARROW..RIGHTWARDS ARROW FROM DOWNWARDS ARROW
		{ 0x1F8D0, 0x1F8D8, BidiClass::OtherNeutral, GeneralCategory::MathSymbol },	// LONG RIGHTWARDS ARROW OVER LONG LEFTWARDS ARROW..LONG LEFT RIGHT ARROW WITH DEPENDENT LOBE
		{ 0x1F900, 0x1FA57, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// CIRCLED CROSS FORMEE WITH FOUR DOTS..BLACK CHESS ALFIL
		{ 0x1FA60, 0x1FA6D, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// XIANGQI RED GENERAL..XIANGQI BLACK SOLDIER
		{ 0x1FA70, 0x1FA7C, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// BALLET SHOES..CRUTCH
		{ 0x1FA80, 0x1FA8A, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// YO-YO..TROMBONE
		{ 0x1FA8E, 0x1FAC6, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// TREASURE CHEST..FINGERPRINT
		{ 0x1FAC8, 0x1FAC8, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// HAIRY CREATURE
		{ 0x1FACD, 0x1FADC, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ORCA..ROOT VEGETABLE
		{ 0x1FADF, 0x1FAEA, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// SPLATTER..DISTORTED FACE
		{ 0x1FAEF, 0x1FAF8, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// FIGHT CLOUD..RIGHTWARDS PUSHING HAND
		{ 0x1FB00, 0x1FB92, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// BLOCK SEXTANT-1..UPPER HALF INVERSE MEDIUM SHADE AND LOWER HALF BLOCK
		{ 0x1FB94, 0x1FBEF, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// LEFT HALF INVERSE MEDIUM SHADE AND RIGHT HALF BLOCK..TOP LEFT JUSTIFIED LOWER RIGHT QUARTER BLACK CIRCLE
		{ 0x1FBF0, 0x1FBF9, BidiClass::EuropeanNumber, GeneralCategory::DecimalNumber },	// SEGMENTED DIGIT ZERO..SEGMENTED DIGIT NINE
		{ 0x1FBFA, 0x1FBFA, BidiClass::OtherNeutral, GeneralCategory::OtherSymbol },	// ALARM BELL SYMBOL
		{ 0x1FFFE, 0x1FFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-1FFFE>..<noncharacter-1FFFF>
		{ 0x20000, 0x2A6DF, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CJK UNIFIED IDEOGRAPH-20000..CJK UNIFIED IDEOGRAPH-2A6DF
		{ 0x2A700, 0x2B81D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CJK UNIFIED IDEOGRAPH-2A700..CJK UNIFIED IDEOGRAPH-2B81D
		{ 0x2B820, 0x2CEAD, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CJK UNIFIED IDEOGRAPH-2B820..CJK UNIFIED IDEOGRAPH-2CEAD
		{ 0x2CEB0, 0x2EBE0, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CJK UNIFIED IDEOGRAPH-2CEB0..CJK UNIFIED IDEOGRAPH-2EBE0
		{ 0x2EBF0, 0x2EE5D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CJK UNIFIED IDEOGRAPH-2EBF0..CJK UNIFIED IDEOGRAPH-2EE5D
		{ 0x2F800, 0x2FA1D, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CJK COMPATIBILITY IDEOGRAPH-2F800..CJK COMPATIBILITY IDEOGRAPH-2FA1D
		{ 0x2FFFE, 0x2FFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-2FFFE>..<noncharacter-2FFFF>
		{ 0x30000, 0x3134A, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CJK UNIFIED IDEOGRAPH-30000..CJK UNIFIED IDEOGRAPH-3134A
		{ 0x31350, 0x33479, BidiClass::LeftToRight, GeneralCategory::OtherLetter },	// CJK UNIFIED IDEOGRAPH-31350..CJK UNIFIED IDEOGRAPH-33479
		{ 0x3FFFE, 0x3FFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-3FFFE>..<noncharacter-3FFFF>
		{ 0x4FFFE, 0x4FFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-4FFFE>..<noncharacter-4FFFF>
		{ 0x5FFFE, 0x5FFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-5FFFE>..<noncharacter-5FFFF>
		{ 0x6FFFE, 0x6FFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-6FFFE>..<noncharacter-6FFFF>
		{ 0x7FFFE, 0x7FFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-7FFFE>..<noncharacter-7FFFF>
		{ 0x8FFFE, 0x8FFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-8FFFE>..<noncharacter-8FFFF>
		{ 0x9FFFE, 0x9FFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-9FFFE>..<noncharacter-9FFFF>
		{ 0xAFFFE, 0xAFFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-AFFFE>..<noncharacter-AFFFF>
		{ 0xBFFFE, 0xBFFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-BFFFE>..<noncharacter-BFFFF>
		{ 0xCFFFE, 0xCFFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-CFFFE>..<noncharacter-CFFFF>
		{ 0xDFFFE, 0xE0000, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-DFFFE>..<reserved-E0000>
		{ 0xE0001, 0xE0001, BidiClass::BoundaryNeutral, GeneralCategory::Format },	// LANGUAGE TAG
		{ 0xE0002, 0xE001F, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <reserved-E0002>..<reserved-E001F>
		{ 0xE0020, 0xE007F, BidiClass::BoundaryNeutral, GeneralCategory::Format },	// TAG SPACE..CANCEL TAG
		{ 0xE0080, 0xE00FF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <reserved-E0080>..<reserved-E00FF>
		{ 0xE0100, 0xE01EF, BidiClass::NonspacingMark, GeneralCategory::NonspacingMark },	// VARIATION SELECTOR-17..VARIATION SELECTOR-256
		{ 0xE01F0, 0xE0FFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <reserved-E01F0>..<reserved-E0FFF>
		{ 0xEFFFE, 0xEFFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-EFFFE>..<noncharacter-EFFFF>
		{ 0xF0000, 0xFFFFD, BidiClass::LeftToRight, GeneralCategory::PrivateUse },	// <private-use-F0000>..<private-use-FFFFD>
		{ 0xFFFFE, 0xFFFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-FFFFE>..<noncharacter-FFFFF>
		{ 0x100000, 0x10FFFD, BidiClass::LeftToRight, GeneralCategory::PrivateUse },	// <private-use-100000>..<private-use-10FFFD>
		{ 0x10FFFE, 0x10FFFF, BidiClass::BoundaryNeutral, GeneralCategory::Unassigned },	// <noncharacter-10FFFE>..<noncharacter-10FFFF>

	});


	bool IsLeftToRight(uint32_t codePoint)
	{
		auto it = std::upper_bound(Ranges.begin(), Ranges.end(), codePoint, [](uint32_t cp, const BidiRange& range) {
			return range.start < cp;
		});

		if (it != Ranges.end() && codePoint >= it->start && codePoint <= it->end)
		{
			return it->bidiClass == BidiClass::LeftToRight;
		}

		return true;
	}

	bool IsLeftToRight(const Utf32Text& utf32)
	{
		for (size_t i = 0; i < utf32.size(); ++i)
		{
			if (!IsLeftToRight(utf32[i]))
			{
				return false;
			}
		}

		return true;
	}

	//bool IsShaped(uint32_t codePoint)
	//{

	//	return false;
	//}

	//bool IsShaped(const Utf32Text& utf32)
	//{

	//	return false;
	//}

	// Can this codepoint be rendered as a simple glyph.
	bool IsSimple(uint32_t codePoint)
	{
		auto it = std::upper_bound(Ranges.begin(), Ranges.end(), codePoint, [](uint32_t cp, const BidiRange& range) {
			return range.start < cp;
		});

		if (it != Ranges.end())
		{
			if (it->bidiClass == BidiClass::RightToLeft || it->bidiClass == BidiClass::ArabicLetter)
			{
				return false;
			}

			if (it->category == GeneralCategory::NonspacingMark || it->category == GeneralCategory::SpacingMark || it->category == GeneralCategory::EnclosingMark)
			{
				return false;
			}

			// XXX script that requires shaping.

		}

		return true;
	}

	// Can this string be rendered as a left to right sequence of glyphs.
	bool IsSimple(const Utf32Text& utf32)
	{
		for (const auto& cp : utf32)
		{
			if (!IsSimple(cp)) return false;
		}

		return true;
	}

};

