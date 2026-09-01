// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cstdint>

module unicode.category;

import std;

namespace unicode::category
{
	// https://www.unicode.org/Public/16.0.0/ucd/extracted/DerivedGeneralCategory.txt

	struct Entry
	{
		uint32_t	start{};
		uint32_t	end{};
		Category	category{ Category::Unknown };
	};

	static constexpr auto CategoryRanges = std::to_array<Entry>(
	{
		{ 0x0000, 0x001F, Category::Control },	// <control-0000>..<control-001F>
		{ 0x0020, 0x0020, Category::SpaceSeparator },	// SPACE
		{ 0x0021, 0x0023, Category::OtherPunctuation },	// EXCLAMATION MARK..NUMBER SIGN
		{ 0x0024, 0x0024, Category::CurrencySymbol },	// DOLLAR SIGN
		{ 0x0025, 0x0027, Category::OtherPunctuation },	// PERCENT SIGN..APOSTROPHE
		{ 0x0028, 0x0028, Category::OpenPunctuation },	// LEFT PARENTHESIS
		{ 0x0029, 0x0029, Category::ClosePunctuation },	// RIGHT PARENTHESIS
		{ 0x002A, 0x002A, Category::OtherPunctuation },	// ASTERISK
		{ 0x002B, 0x002B, Category::MathSymbol },	// PLUS SIGN
		{ 0x002C, 0x002C, Category::OtherPunctuation },	// COMMA
		{ 0x002D, 0x002D, Category::DashPunctuation },	// HYPHEN-MINUS
		{ 0x002E, 0x002F, Category::OtherPunctuation },	// FULL STOP..SOLIDUS
		{ 0x0030, 0x0039, Category::DecimalNumber },	// DIGIT ZERO..DIGIT NINE
		{ 0x003A, 0x003B, Category::OtherPunctuation },	// COLON..SEMICOLON
		{ 0x003C, 0x003E, Category::MathSymbol },	// LESS-THAN SIGN..GREATER-THAN SIGN
		{ 0x003F, 0x0040, Category::OtherPunctuation },	// QUESTION MARK..COMMERCIAL AT
		{ 0x0041, 0x005A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A..LATIN CAPITAL LETTER Z
		{ 0x005B, 0x005B, Category::OpenPunctuation },	// LEFT SQUARE BRACKET
		{ 0x005C, 0x005C, Category::OtherPunctuation },	// REVERSE SOLIDUS
		{ 0x005D, 0x005D, Category::ClosePunctuation },	// RIGHT SQUARE BRACKET
		{ 0x005E, 0x005E, Category::ModifierSymbol },	// CIRCUMFLEX ACCENT
		{ 0x005F, 0x005F, Category::ConnectorPunctuation },	// LOW LINE
		{ 0x0060, 0x0060, Category::ModifierSymbol },	// GRAVE ACCENT
		{ 0x0061, 0x007A, Category::LowercaseLetter },	// LATIN SMALL LETTER A..LATIN SMALL LETTER Z
		{ 0x007B, 0x007B, Category::OpenPunctuation },	// LEFT CURLY BRACKET
		{ 0x007C, 0x007C, Category::MathSymbol },	// VERTICAL LINE
		{ 0x007D, 0x007D, Category::ClosePunctuation },	// RIGHT CURLY BRACKET
		{ 0x007E, 0x007E, Category::MathSymbol },	// TILDE
		{ 0x007F, 0x009F, Category::Control },	// <control-007F>..<control-009F>
		{ 0x00A0, 0x00A0, Category::SpaceSeparator },	// NO-BREAK SPACE
		{ 0x00A1, 0x00A1, Category::OtherPunctuation },	// INVERTED EXCLAMATION MARK
		{ 0x00A2, 0x00A5, Category::CurrencySymbol },	// CENT SIGN..YEN SIGN
		{ 0x00A6, 0x00A6, Category::OtherSymbol },	// BROKEN BAR
		{ 0x00A7, 0x00A7, Category::OtherPunctuation },	// SECTION SIGN
		{ 0x00A8, 0x00A8, Category::ModifierSymbol },	// DIAERESIS
		{ 0x00A9, 0x00A9, Category::OtherSymbol },	// COPYRIGHT SIGN
		{ 0x00AA, 0x00AA, Category::OtherLetter },	// FEMININE ORDINAL INDICATOR
		{ 0x00AB, 0x00AB, Category::InitialPunctuation },	// LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
		{ 0x00AC, 0x00AC, Category::MathSymbol },	// NOT SIGN
		{ 0x00AD, 0x00AD, Category::Format },	// SOFT HYPHEN
		{ 0x00AE, 0x00AE, Category::OtherSymbol },	// REGISTERED SIGN
		{ 0x00AF, 0x00AF, Category::ModifierSymbol },	// MACRON
		{ 0x00B0, 0x00B0, Category::OtherSymbol },	// DEGREE SIGN
		{ 0x00B1, 0x00B1, Category::MathSymbol },	// PLUS-MINUS SIGN
		{ 0x00B2, 0x00B3, Category::OtherNumber },	// SUPERSCRIPT TWO..SUPERSCRIPT THREE
		{ 0x00B4, 0x00B4, Category::ModifierSymbol },	// ACUTE ACCENT
		{ 0x00B5, 0x00B5, Category::LowercaseLetter },	// MICRO SIGN
		{ 0x00B6, 0x00B7, Category::OtherPunctuation },	// PILCROW SIGN..MIDDLE DOT
		{ 0x00B8, 0x00B8, Category::ModifierSymbol },	// CEDILLA
		{ 0x00B9, 0x00B9, Category::OtherNumber },	// SUPERSCRIPT ONE
		{ 0x00BA, 0x00BA, Category::OtherLetter },	// MASCULINE ORDINAL INDICATOR
		{ 0x00BB, 0x00BB, Category::FinalPunctuation },	// RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
		{ 0x00BC, 0x00BE, Category::OtherNumber },	// VULGAR FRACTION ONE QUARTER..VULGAR FRACTION THREE QUARTERS
		{ 0x00BF, 0x00BF, Category::OtherPunctuation },	// INVERTED QUESTION MARK
		{ 0x00C0, 0x00D6, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH GRAVE..LATIN CAPITAL LETTER O WITH DIAERESIS
		{ 0x00D7, 0x00D7, Category::MathSymbol },	// MULTIPLICATION SIGN
		{ 0x00D8, 0x00DE, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH STROKE..LATIN CAPITAL LETTER THORN
		{ 0x00DF, 0x00F6, Category::LowercaseLetter },	// LATIN SMALL LETTER SHARP S..LATIN SMALL LETTER O WITH DIAERESIS
		{ 0x00F7, 0x00F7, Category::MathSymbol },	// DIVISION SIGN
		{ 0x00F8, 0x00FF, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH STROKE..LATIN SMALL LETTER Y WITH DIAERESIS
		{ 0x0100, 0x0100, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH MACRON
		{ 0x0101, 0x0101, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH MACRON
		{ 0x0102, 0x0102, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH BREVE
		{ 0x0103, 0x0103, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH BREVE
		{ 0x0104, 0x0104, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH OGONEK
		{ 0x0105, 0x0105, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH OGONEK
		{ 0x0106, 0x0106, Category::UppercaseLetter },	// LATIN CAPITAL LETTER C WITH ACUTE
		{ 0x0107, 0x0107, Category::LowercaseLetter },	// LATIN SMALL LETTER C WITH ACUTE
		{ 0x0108, 0x0108, Category::UppercaseLetter },	// LATIN CAPITAL LETTER C WITH CIRCUMFLEX
		{ 0x0109, 0x0109, Category::LowercaseLetter },	// LATIN SMALL LETTER C WITH CIRCUMFLEX
		{ 0x010A, 0x010A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER C WITH DOT ABOVE
		{ 0x010B, 0x010B, Category::LowercaseLetter },	// LATIN SMALL LETTER C WITH DOT ABOVE
		{ 0x010C, 0x010C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER C WITH CARON
		{ 0x010D, 0x010D, Category::LowercaseLetter },	// LATIN SMALL LETTER C WITH CARON
		{ 0x010E, 0x010E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER D WITH CARON
		{ 0x010F, 0x010F, Category::LowercaseLetter },	// LATIN SMALL LETTER D WITH CARON
		{ 0x0110, 0x0110, Category::UppercaseLetter },	// LATIN CAPITAL LETTER D WITH STROKE
		{ 0x0111, 0x0111, Category::LowercaseLetter },	// LATIN SMALL LETTER D WITH STROKE
		{ 0x0112, 0x0112, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH MACRON
		{ 0x0113, 0x0113, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH MACRON
		{ 0x0114, 0x0114, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH BREVE
		{ 0x0115, 0x0115, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH BREVE
		{ 0x0116, 0x0116, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH DOT ABOVE
		{ 0x0117, 0x0117, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH DOT ABOVE
		{ 0x0118, 0x0118, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH OGONEK
		{ 0x0119, 0x0119, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH OGONEK
		{ 0x011A, 0x011A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH CARON
		{ 0x011B, 0x011B, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH CARON
		{ 0x011C, 0x011C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER G WITH CIRCUMFLEX
		{ 0x011D, 0x011D, Category::LowercaseLetter },	// LATIN SMALL LETTER G WITH CIRCUMFLEX
		{ 0x011E, 0x011E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER G WITH BREVE
		{ 0x011F, 0x011F, Category::LowercaseLetter },	// LATIN SMALL LETTER G WITH BREVE
		{ 0x0120, 0x0120, Category::UppercaseLetter },	// LATIN CAPITAL LETTER G WITH DOT ABOVE
		{ 0x0121, 0x0121, Category::LowercaseLetter },	// LATIN SMALL LETTER G WITH DOT ABOVE
		{ 0x0122, 0x0122, Category::UppercaseLetter },	// LATIN CAPITAL LETTER G WITH CEDILLA
		{ 0x0123, 0x0123, Category::LowercaseLetter },	// LATIN SMALL LETTER G WITH CEDILLA
		{ 0x0124, 0x0124, Category::UppercaseLetter },	// LATIN CAPITAL LETTER H WITH CIRCUMFLEX
		{ 0x0125, 0x0125, Category::LowercaseLetter },	// LATIN SMALL LETTER H WITH CIRCUMFLEX
		{ 0x0126, 0x0126, Category::UppercaseLetter },	// LATIN CAPITAL LETTER H WITH STROKE
		{ 0x0127, 0x0127, Category::LowercaseLetter },	// LATIN SMALL LETTER H WITH STROKE
		{ 0x0128, 0x0128, Category::UppercaseLetter },	// LATIN CAPITAL LETTER I WITH TILDE
		{ 0x0129, 0x0129, Category::LowercaseLetter },	// LATIN SMALL LETTER I WITH TILDE
		{ 0x012A, 0x012A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER I WITH MACRON
		{ 0x012B, 0x012B, Category::LowercaseLetter },	// LATIN SMALL LETTER I WITH MACRON
		{ 0x012C, 0x012C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER I WITH BREVE
		{ 0x012D, 0x012D, Category::LowercaseLetter },	// LATIN SMALL LETTER I WITH BREVE
		{ 0x012E, 0x012E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER I WITH OGONEK
		{ 0x012F, 0x012F, Category::LowercaseLetter },	// LATIN SMALL LETTER I WITH OGONEK
		{ 0x0130, 0x0130, Category::UppercaseLetter },	// LATIN CAPITAL LETTER I WITH DOT ABOVE
		{ 0x0131, 0x0131, Category::LowercaseLetter },	// LATIN SMALL LETTER DOTLESS I
		{ 0x0132, 0x0132, Category::UppercaseLetter },	// LATIN CAPITAL LIGATURE IJ
		{ 0x0133, 0x0133, Category::LowercaseLetter },	// LATIN SMALL LIGATURE IJ
		{ 0x0134, 0x0134, Category::UppercaseLetter },	// LATIN CAPITAL LETTER J WITH CIRCUMFLEX
		{ 0x0135, 0x0135, Category::LowercaseLetter },	// LATIN SMALL LETTER J WITH CIRCUMFLEX
		{ 0x0136, 0x0136, Category::UppercaseLetter },	// LATIN CAPITAL LETTER K WITH CEDILLA
		{ 0x0137, 0x0138, Category::LowercaseLetter },	// LATIN SMALL LETTER K WITH CEDILLA..LATIN SMALL LETTER KRA
		{ 0x0139, 0x0139, Category::UppercaseLetter },	// LATIN CAPITAL LETTER L WITH ACUTE
		{ 0x013A, 0x013A, Category::LowercaseLetter },	// LATIN SMALL LETTER L WITH ACUTE
		{ 0x013B, 0x013B, Category::UppercaseLetter },	// LATIN CAPITAL LETTER L WITH CEDILLA
		{ 0x013C, 0x013C, Category::LowercaseLetter },	// LATIN SMALL LETTER L WITH CEDILLA
		{ 0x013D, 0x013D, Category::UppercaseLetter },	// LATIN CAPITAL LETTER L WITH CARON
		{ 0x013E, 0x013E, Category::LowercaseLetter },	// LATIN SMALL LETTER L WITH CARON
		{ 0x013F, 0x013F, Category::UppercaseLetter },	// LATIN CAPITAL LETTER L WITH MIDDLE DOT
		{ 0x0140, 0x0140, Category::LowercaseLetter },	// LATIN SMALL LETTER L WITH MIDDLE DOT
		{ 0x0141, 0x0141, Category::UppercaseLetter },	// LATIN CAPITAL LETTER L WITH STROKE
		{ 0x0142, 0x0142, Category::LowercaseLetter },	// LATIN SMALL LETTER L WITH STROKE
		{ 0x0143, 0x0143, Category::UppercaseLetter },	// LATIN CAPITAL LETTER N WITH ACUTE
		{ 0x0144, 0x0144, Category::LowercaseLetter },	// LATIN SMALL LETTER N WITH ACUTE
		{ 0x0145, 0x0145, Category::UppercaseLetter },	// LATIN CAPITAL LETTER N WITH CEDILLA
		{ 0x0146, 0x0146, Category::LowercaseLetter },	// LATIN SMALL LETTER N WITH CEDILLA
		{ 0x0147, 0x0147, Category::UppercaseLetter },	// LATIN CAPITAL LETTER N WITH CARON
		{ 0x0148, 0x0149, Category::LowercaseLetter },	// LATIN SMALL LETTER N WITH CARON..LATIN SMALL LETTER N PRECEDED BY APOSTROPHE
		{ 0x014A, 0x014A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER ENG
		{ 0x014B, 0x014B, Category::LowercaseLetter },	// LATIN SMALL LETTER ENG
		{ 0x014C, 0x014C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH MACRON
		{ 0x014D, 0x014D, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH MACRON
		{ 0x014E, 0x014E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH BREVE
		{ 0x014F, 0x014F, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH BREVE
		{ 0x0150, 0x0150, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH DOUBLE ACUTE
		{ 0x0151, 0x0151, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH DOUBLE ACUTE
		{ 0x0152, 0x0152, Category::UppercaseLetter },	// LATIN CAPITAL LIGATURE OE
		{ 0x0153, 0x0153, Category::LowercaseLetter },	// LATIN SMALL LIGATURE OE
		{ 0x0154, 0x0154, Category::UppercaseLetter },	// LATIN CAPITAL LETTER R WITH ACUTE
		{ 0x0155, 0x0155, Category::LowercaseLetter },	// LATIN SMALL LETTER R WITH ACUTE
		{ 0x0156, 0x0156, Category::UppercaseLetter },	// LATIN CAPITAL LETTER R WITH CEDILLA
		{ 0x0157, 0x0157, Category::LowercaseLetter },	// LATIN SMALL LETTER R WITH CEDILLA
		{ 0x0158, 0x0158, Category::UppercaseLetter },	// LATIN CAPITAL LETTER R WITH CARON
		{ 0x0159, 0x0159, Category::LowercaseLetter },	// LATIN SMALL LETTER R WITH CARON
		{ 0x015A, 0x015A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER S WITH ACUTE
		{ 0x015B, 0x015B, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH ACUTE
		{ 0x015C, 0x015C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER S WITH CIRCUMFLEX
		{ 0x015D, 0x015D, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH CIRCUMFLEX
		{ 0x015E, 0x015E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER S WITH CEDILLA
		{ 0x015F, 0x015F, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH CEDILLA
		{ 0x0160, 0x0160, Category::UppercaseLetter },	// LATIN CAPITAL LETTER S WITH CARON
		{ 0x0161, 0x0161, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH CARON
		{ 0x0162, 0x0162, Category::UppercaseLetter },	// LATIN CAPITAL LETTER T WITH CEDILLA
		{ 0x0163, 0x0163, Category::LowercaseLetter },	// LATIN SMALL LETTER T WITH CEDILLA
		{ 0x0164, 0x0164, Category::UppercaseLetter },	// LATIN CAPITAL LETTER T WITH CARON
		{ 0x0165, 0x0165, Category::LowercaseLetter },	// LATIN SMALL LETTER T WITH CARON
		{ 0x0166, 0x0166, Category::UppercaseLetter },	// LATIN CAPITAL LETTER T WITH STROKE
		{ 0x0167, 0x0167, Category::LowercaseLetter },	// LATIN SMALL LETTER T WITH STROKE
		{ 0x0168, 0x0168, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH TILDE
		{ 0x0169, 0x0169, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH TILDE
		{ 0x016A, 0x016A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH MACRON
		{ 0x016B, 0x016B, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH MACRON
		{ 0x016C, 0x016C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH BREVE
		{ 0x016D, 0x016D, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH BREVE
		{ 0x016E, 0x016E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH RING ABOVE
		{ 0x016F, 0x016F, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH RING ABOVE
		{ 0x0170, 0x0170, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH DOUBLE ACUTE
		{ 0x0171, 0x0171, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH DOUBLE ACUTE
		{ 0x0172, 0x0172, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH OGONEK
		{ 0x0173, 0x0173, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH OGONEK
		{ 0x0174, 0x0174, Category::UppercaseLetter },	// LATIN CAPITAL LETTER W WITH CIRCUMFLEX
		{ 0x0175, 0x0175, Category::LowercaseLetter },	// LATIN SMALL LETTER W WITH CIRCUMFLEX
		{ 0x0176, 0x0176, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Y WITH CIRCUMFLEX
		{ 0x0177, 0x0177, Category::LowercaseLetter },	// LATIN SMALL LETTER Y WITH CIRCUMFLEX
		{ 0x0178, 0x0179, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Y WITH DIAERESIS..LATIN CAPITAL LETTER Z WITH ACUTE
		{ 0x017A, 0x017A, Category::LowercaseLetter },	// LATIN SMALL LETTER Z WITH ACUTE
		{ 0x017B, 0x017B, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Z WITH DOT ABOVE
		{ 0x017C, 0x017C, Category::LowercaseLetter },	// LATIN SMALL LETTER Z WITH DOT ABOVE
		{ 0x017D, 0x017D, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Z WITH CARON
		{ 0x017E, 0x0180, Category::LowercaseLetter },	// LATIN SMALL LETTER Z WITH CARON..LATIN SMALL LETTER B WITH STROKE
		{ 0x0181, 0x0182, Category::UppercaseLetter },	// LATIN CAPITAL LETTER B WITH HOOK..LATIN CAPITAL LETTER B WITH TOPBAR
		{ 0x0183, 0x0183, Category::LowercaseLetter },	// LATIN SMALL LETTER B WITH TOPBAR
		{ 0x0184, 0x0184, Category::UppercaseLetter },	// LATIN CAPITAL LETTER TONE SIX
		{ 0x0185, 0x0185, Category::LowercaseLetter },	// LATIN SMALL LETTER TONE SIX
		{ 0x0186, 0x0187, Category::UppercaseLetter },	// LATIN CAPITAL LETTER OPEN O..LATIN CAPITAL LETTER C WITH HOOK
		{ 0x0188, 0x0188, Category::LowercaseLetter },	// LATIN SMALL LETTER C WITH HOOK
		{ 0x0189, 0x018B, Category::UppercaseLetter },	// LATIN CAPITAL LETTER AFRICAN D..LATIN CAPITAL LETTER D WITH TOPBAR
		{ 0x018C, 0x018D, Category::LowercaseLetter },	// LATIN SMALL LETTER D WITH TOPBAR..LATIN SMALL LETTER TURNED DELTA
		{ 0x018E, 0x0191, Category::UppercaseLetter },	// LATIN CAPITAL LETTER REVERSED E..LATIN CAPITAL LETTER F WITH HOOK
		{ 0x0192, 0x0192, Category::LowercaseLetter },	// LATIN SMALL LETTER F WITH HOOK
		{ 0x0193, 0x0194, Category::UppercaseLetter },	// LATIN CAPITAL LETTER G WITH HOOK..LATIN CAPITAL LETTER GAMMA
		{ 0x0195, 0x0195, Category::LowercaseLetter },	// LATIN SMALL LETTER HV
		{ 0x0196, 0x0198, Category::UppercaseLetter },	// LATIN CAPITAL LETTER IOTA..LATIN CAPITAL LETTER K WITH HOOK
		{ 0x0199, 0x019B, Category::LowercaseLetter },	// LATIN SMALL LETTER K WITH HOOK..LATIN SMALL LETTER LAMBDA WITH STROKE
		{ 0x019C, 0x019D, Category::UppercaseLetter },	// LATIN CAPITAL LETTER TURNED M..LATIN CAPITAL LETTER N WITH LEFT HOOK
		{ 0x019E, 0x019E, Category::LowercaseLetter },	// LATIN SMALL LETTER N WITH LONG RIGHT LEG
		{ 0x019F, 0x01A0, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH MIDDLE TILDE..LATIN CAPITAL LETTER O WITH HORN
		{ 0x01A1, 0x01A1, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH HORN
		{ 0x01A2, 0x01A2, Category::UppercaseLetter },	// LATIN CAPITAL LETTER OI
		{ 0x01A3, 0x01A3, Category::LowercaseLetter },	// LATIN SMALL LETTER OI
		{ 0x01A4, 0x01A4, Category::UppercaseLetter },	// LATIN CAPITAL LETTER P WITH HOOK
		{ 0x01A5, 0x01A5, Category::LowercaseLetter },	// LATIN SMALL LETTER P WITH HOOK
		{ 0x01A6, 0x01A7, Category::UppercaseLetter },	// LATIN LETTER YR..LATIN CAPITAL LETTER TONE TWO
		{ 0x01A8, 0x01A8, Category::LowercaseLetter },	// LATIN SMALL LETTER TONE TWO
		{ 0x01A9, 0x01A9, Category::UppercaseLetter },	// LATIN CAPITAL LETTER ESH
		{ 0x01AA, 0x01AB, Category::LowercaseLetter },	// LATIN LETTER REVERSED ESH LOOP..LATIN SMALL LETTER T WITH PALATAL HOOK
		{ 0x01AC, 0x01AC, Category::UppercaseLetter },	// LATIN CAPITAL LETTER T WITH HOOK
		{ 0x01AD, 0x01AD, Category::LowercaseLetter },	// LATIN SMALL LETTER T WITH HOOK
		{ 0x01AE, 0x01AF, Category::UppercaseLetter },	// LATIN CAPITAL LETTER T WITH RETROFLEX HOOK..LATIN CAPITAL LETTER U WITH HORN
		{ 0x01B0, 0x01B0, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH HORN
		{ 0x01B1, 0x01B3, Category::UppercaseLetter },	// LATIN CAPITAL LETTER UPSILON..LATIN CAPITAL LETTER Y WITH HOOK
		{ 0x01B4, 0x01B4, Category::LowercaseLetter },	// LATIN SMALL LETTER Y WITH HOOK
		{ 0x01B5, 0x01B5, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Z WITH STROKE
		{ 0x01B6, 0x01B6, Category::LowercaseLetter },	// LATIN SMALL LETTER Z WITH STROKE
		{ 0x01B7, 0x01B8, Category::UppercaseLetter },	// LATIN CAPITAL LETTER EZH..LATIN CAPITAL LETTER EZH REVERSED
		{ 0x01B9, 0x01BA, Category::LowercaseLetter },	// LATIN SMALL LETTER EZH REVERSED..LATIN SMALL LETTER EZH WITH TAIL
		{ 0x01BB, 0x01BB, Category::OtherLetter },	// LATIN LETTER TWO WITH STROKE
		{ 0x01BC, 0x01BC, Category::UppercaseLetter },	// LATIN CAPITAL LETTER TONE FIVE
		{ 0x01BD, 0x01BF, Category::LowercaseLetter },	// LATIN SMALL LETTER TONE FIVE..LATIN LETTER WYNN
		{ 0x01C0, 0x01C3, Category::OtherLetter },	// LATIN LETTER DENTAL CLICK..LATIN LETTER RETROFLEX CLICK
		{ 0x01C4, 0x01C4, Category::UppercaseLetter },	// LATIN CAPITAL LETTER DZ WITH CARON
		{ 0x01C5, 0x01C5, Category::TitlecaseLetter },	// LATIN CAPITAL LETTER D WITH SMALL LETTER Z WITH CARON
		{ 0x01C6, 0x01C6, Category::LowercaseLetter },	// LATIN SMALL LETTER DZ WITH CARON
		{ 0x01C7, 0x01C7, Category::UppercaseLetter },	// LATIN CAPITAL LETTER LJ
		{ 0x01C8, 0x01C8, Category::TitlecaseLetter },	// LATIN CAPITAL LETTER L WITH SMALL LETTER J
		{ 0x01C9, 0x01C9, Category::LowercaseLetter },	// LATIN SMALL LETTER LJ
		{ 0x01CA, 0x01CA, Category::UppercaseLetter },	// LATIN CAPITAL LETTER NJ
		{ 0x01CB, 0x01CB, Category::TitlecaseLetter },	// LATIN CAPITAL LETTER N WITH SMALL LETTER J
		{ 0x01CC, 0x01CC, Category::LowercaseLetter },	// LATIN SMALL LETTER NJ
		{ 0x01CD, 0x01CD, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH CARON
		{ 0x01CE, 0x01CE, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH CARON
		{ 0x01CF, 0x01CF, Category::UppercaseLetter },	// LATIN CAPITAL LETTER I WITH CARON
		{ 0x01D0, 0x01D0, Category::LowercaseLetter },	// LATIN SMALL LETTER I WITH CARON
		{ 0x01D1, 0x01D1, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH CARON
		{ 0x01D2, 0x01D2, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH CARON
		{ 0x01D3, 0x01D3, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH CARON
		{ 0x01D4, 0x01D4, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH CARON
		{ 0x01D5, 0x01D5, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH DIAERESIS AND MACRON
		{ 0x01D6, 0x01D6, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH DIAERESIS AND MACRON
		{ 0x01D7, 0x01D7, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH DIAERESIS AND ACUTE
		{ 0x01D8, 0x01D8, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH DIAERESIS AND ACUTE
		{ 0x01D9, 0x01D9, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH DIAERESIS AND CARON
		{ 0x01DA, 0x01DA, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH DIAERESIS AND CARON
		{ 0x01DB, 0x01DB, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH DIAERESIS AND GRAVE
		{ 0x01DC, 0x01DD, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH DIAERESIS AND GRAVE..LATIN SMALL LETTER TURNED E
		{ 0x01DE, 0x01DE, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH DIAERESIS AND MACRON
		{ 0x01DF, 0x01DF, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH DIAERESIS AND MACRON
		{ 0x01E0, 0x01E0, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH DOT ABOVE AND MACRON
		{ 0x01E1, 0x01E1, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH DOT ABOVE AND MACRON
		{ 0x01E2, 0x01E2, Category::UppercaseLetter },	// LATIN CAPITAL LETTER AE WITH MACRON
		{ 0x01E3, 0x01E3, Category::LowercaseLetter },	// LATIN SMALL LETTER AE WITH MACRON
		{ 0x01E4, 0x01E4, Category::UppercaseLetter },	// LATIN CAPITAL LETTER G WITH STROKE
		{ 0x01E5, 0x01E5, Category::LowercaseLetter },	// LATIN SMALL LETTER G WITH STROKE
		{ 0x01E6, 0x01E6, Category::UppercaseLetter },	// LATIN CAPITAL LETTER G WITH CARON
		{ 0x01E7, 0x01E7, Category::LowercaseLetter },	// LATIN SMALL LETTER G WITH CARON
		{ 0x01E8, 0x01E8, Category::UppercaseLetter },	// LATIN CAPITAL LETTER K WITH CARON
		{ 0x01E9, 0x01E9, Category::LowercaseLetter },	// LATIN SMALL LETTER K WITH CARON
		{ 0x01EA, 0x01EA, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH OGONEK
		{ 0x01EB, 0x01EB, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH OGONEK
		{ 0x01EC, 0x01EC, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH OGONEK AND MACRON
		{ 0x01ED, 0x01ED, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH OGONEK AND MACRON
		{ 0x01EE, 0x01EE, Category::UppercaseLetter },	// LATIN CAPITAL LETTER EZH WITH CARON
		{ 0x01EF, 0x01F0, Category::LowercaseLetter },	// LATIN SMALL LETTER EZH WITH CARON..LATIN SMALL LETTER J WITH CARON
		{ 0x01F1, 0x01F1, Category::UppercaseLetter },	// LATIN CAPITAL LETTER DZ
		{ 0x01F2, 0x01F2, Category::TitlecaseLetter },	// LATIN CAPITAL LETTER D WITH SMALL LETTER Z
		{ 0x01F3, 0x01F3, Category::LowercaseLetter },	// LATIN SMALL LETTER DZ
		{ 0x01F4, 0x01F4, Category::UppercaseLetter },	// LATIN CAPITAL LETTER G WITH ACUTE
		{ 0x01F5, 0x01F5, Category::LowercaseLetter },	// LATIN SMALL LETTER G WITH ACUTE
		{ 0x01F6, 0x01F8, Category::UppercaseLetter },	// LATIN CAPITAL LETTER HWAIR..LATIN CAPITAL LETTER N WITH GRAVE
		{ 0x01F9, 0x01F9, Category::LowercaseLetter },	// LATIN SMALL LETTER N WITH GRAVE
		{ 0x01FA, 0x01FA, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH RING ABOVE AND ACUTE
		{ 0x01FB, 0x01FB, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH RING ABOVE AND ACUTE
		{ 0x01FC, 0x01FC, Category::UppercaseLetter },	// LATIN CAPITAL LETTER AE WITH ACUTE
		{ 0x01FD, 0x01FD, Category::LowercaseLetter },	// LATIN SMALL LETTER AE WITH ACUTE
		{ 0x01FE, 0x01FE, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH STROKE AND ACUTE
		{ 0x01FF, 0x01FF, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH STROKE AND ACUTE
		{ 0x0200, 0x0200, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH DOUBLE GRAVE
		{ 0x0201, 0x0201, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH DOUBLE GRAVE
		{ 0x0202, 0x0202, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH INVERTED BREVE
		{ 0x0203, 0x0203, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH INVERTED BREVE
		{ 0x0204, 0x0204, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH DOUBLE GRAVE
		{ 0x0205, 0x0205, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH DOUBLE GRAVE
		{ 0x0206, 0x0206, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH INVERTED BREVE
		{ 0x0207, 0x0207, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH INVERTED BREVE
		{ 0x0208, 0x0208, Category::UppercaseLetter },	// LATIN CAPITAL LETTER I WITH DOUBLE GRAVE
		{ 0x0209, 0x0209, Category::LowercaseLetter },	// LATIN SMALL LETTER I WITH DOUBLE GRAVE
		{ 0x020A, 0x020A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER I WITH INVERTED BREVE
		{ 0x020B, 0x020B, Category::LowercaseLetter },	// LATIN SMALL LETTER I WITH INVERTED BREVE
		{ 0x020C, 0x020C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH DOUBLE GRAVE
		{ 0x020D, 0x020D, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH DOUBLE GRAVE
		{ 0x020E, 0x020E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH INVERTED BREVE
		{ 0x020F, 0x020F, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH INVERTED BREVE
		{ 0x0210, 0x0210, Category::UppercaseLetter },	// LATIN CAPITAL LETTER R WITH DOUBLE GRAVE
		{ 0x0211, 0x0211, Category::LowercaseLetter },	// LATIN SMALL LETTER R WITH DOUBLE GRAVE
		{ 0x0212, 0x0212, Category::UppercaseLetter },	// LATIN CAPITAL LETTER R WITH INVERTED BREVE
		{ 0x0213, 0x0213, Category::LowercaseLetter },	// LATIN SMALL LETTER R WITH INVERTED BREVE
		{ 0x0214, 0x0214, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH DOUBLE GRAVE
		{ 0x0215, 0x0215, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH DOUBLE GRAVE
		{ 0x0216, 0x0216, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH INVERTED BREVE
		{ 0x0217, 0x0217, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH INVERTED BREVE
		{ 0x0218, 0x0218, Category::UppercaseLetter },	// LATIN CAPITAL LETTER S WITH COMMA BELOW
		{ 0x0219, 0x0219, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH COMMA BELOW
		{ 0x021A, 0x021A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER T WITH COMMA BELOW
		{ 0x021B, 0x021B, Category::LowercaseLetter },	// LATIN SMALL LETTER T WITH COMMA BELOW
		{ 0x021C, 0x021C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER YOGH
		{ 0x021D, 0x021D, Category::LowercaseLetter },	// LATIN SMALL LETTER YOGH
		{ 0x021E, 0x021E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER H WITH CARON
		{ 0x021F, 0x021F, Category::LowercaseLetter },	// LATIN SMALL LETTER H WITH CARON
		{ 0x0220, 0x0220, Category::UppercaseLetter },	// LATIN CAPITAL LETTER N WITH LONG RIGHT LEG
		{ 0x0221, 0x0221, Category::LowercaseLetter },	// LATIN SMALL LETTER D WITH CURL
		{ 0x0222, 0x0222, Category::UppercaseLetter },	// LATIN CAPITAL LETTER OU
		{ 0x0223, 0x0223, Category::LowercaseLetter },	// LATIN SMALL LETTER OU
		{ 0x0224, 0x0224, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Z WITH HOOK
		{ 0x0225, 0x0225, Category::LowercaseLetter },	// LATIN SMALL LETTER Z WITH HOOK
		{ 0x0226, 0x0226, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH DOT ABOVE
		{ 0x0227, 0x0227, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH DOT ABOVE
		{ 0x0228, 0x0228, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH CEDILLA
		{ 0x0229, 0x0229, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH CEDILLA
		{ 0x022A, 0x022A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH DIAERESIS AND MACRON
		{ 0x022B, 0x022B, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH DIAERESIS AND MACRON
		{ 0x022C, 0x022C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH TILDE AND MACRON
		{ 0x022D, 0x022D, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH TILDE AND MACRON
		{ 0x022E, 0x022E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH DOT ABOVE
		{ 0x022F, 0x022F, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH DOT ABOVE
		{ 0x0230, 0x0230, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH DOT ABOVE AND MACRON
		{ 0x0231, 0x0231, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH DOT ABOVE AND MACRON
		{ 0x0232, 0x0232, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Y WITH MACRON
		{ 0x0233, 0x0239, Category::LowercaseLetter },	// LATIN SMALL LETTER Y WITH MACRON..LATIN SMALL LETTER QP DIGRAPH
		{ 0x023A, 0x023B, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH STROKE..LATIN CAPITAL LETTER C WITH STROKE
		{ 0x023C, 0x023C, Category::LowercaseLetter },	// LATIN SMALL LETTER C WITH STROKE
		{ 0x023D, 0x023E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER L WITH BAR..LATIN CAPITAL LETTER T WITH DIAGONAL STROKE
		{ 0x023F, 0x0240, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH SWASH TAIL..LATIN SMALL LETTER Z WITH SWASH TAIL
		{ 0x0241, 0x0241, Category::UppercaseLetter },	// LATIN CAPITAL LETTER GLOTTAL STOP
		{ 0x0242, 0x0242, Category::LowercaseLetter },	// LATIN SMALL LETTER GLOTTAL STOP
		{ 0x0243, 0x0246, Category::UppercaseLetter },	// LATIN CAPITAL LETTER B WITH STROKE..LATIN CAPITAL LETTER E WITH STROKE
		{ 0x0247, 0x0247, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH STROKE
		{ 0x0248, 0x0248, Category::UppercaseLetter },	// LATIN CAPITAL LETTER J WITH STROKE
		{ 0x0249, 0x0249, Category::LowercaseLetter },	// LATIN SMALL LETTER J WITH STROKE
		{ 0x024A, 0x024A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER SMALL Q WITH HOOK TAIL
		{ 0x024B, 0x024B, Category::LowercaseLetter },	// LATIN SMALL LETTER Q WITH HOOK TAIL
		{ 0x024C, 0x024C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER R WITH STROKE
		{ 0x024D, 0x024D, Category::LowercaseLetter },	// LATIN SMALL LETTER R WITH STROKE
		{ 0x024E, 0x024E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Y WITH STROKE
		{ 0x024F, 0x0293, Category::LowercaseLetter },	// LATIN SMALL LETTER Y WITH STROKE..LATIN SMALL LETTER EZH WITH CURL
		{ 0x0294, 0x0294, Category::OtherLetter },	// LATIN LETTER GLOTTAL STOP
		{ 0x0295, 0x02AF, Category::LowercaseLetter },	// LATIN LETTER PHARYNGEAL VOICED FRICATIVE..LATIN SMALL LETTER TURNED H WITH FISHHOOK AND TAIL
		{ 0x02B0, 0x02C1, Category::ModifierLetter },	// MODIFIER LETTER SMALL H..MODIFIER LETTER REVERSED GLOTTAL STOP
		{ 0x02C2, 0x02C5, Category::ModifierSymbol },	// MODIFIER LETTER LEFT ARROWHEAD..MODIFIER LETTER DOWN ARROWHEAD
		{ 0x02C6, 0x02D1, Category::ModifierLetter },	// MODIFIER LETTER CIRCUMFLEX ACCENT..MODIFIER LETTER HALF TRIANGULAR COLON
		{ 0x02D2, 0x02DF, Category::ModifierSymbol },	// MODIFIER LETTER CENTRED RIGHT HALF RING..MODIFIER LETTER CROSS ACCENT
		{ 0x02E0, 0x02E4, Category::ModifierLetter },	// MODIFIER LETTER SMALL GAMMA..MODIFIER LETTER SMALL REVERSED GLOTTAL STOP
		{ 0x02E5, 0x02EB, Category::ModifierSymbol },	// MODIFIER LETTER EXTRA-HIGH TONE BAR..MODIFIER LETTER YANG DEPARTING TONE MARK
		{ 0x02EC, 0x02EC, Category::ModifierLetter },	// MODIFIER LETTER VOICING
		{ 0x02ED, 0x02ED, Category::ModifierSymbol },	// MODIFIER LETTER UNASPIRATED
		{ 0x02EE, 0x02EE, Category::ModifierLetter },	// MODIFIER LETTER DOUBLE APOSTROPHE
		{ 0x02EF, 0x02FF, Category::ModifierSymbol },	// MODIFIER LETTER LOW DOWN ARROWHEAD..MODIFIER LETTER LOW LEFT ARROW
		{ 0x0300, 0x036F, Category::NonspacingMark },	// COMBINING GRAVE ACCENT..COMBINING LATIN SMALL LETTER X
		{ 0x0370, 0x0370, Category::UppercaseLetter },	// GREEK CAPITAL LETTER HETA
		{ 0x0371, 0x0371, Category::LowercaseLetter },	// GREEK SMALL LETTER HETA
		{ 0x0372, 0x0372, Category::UppercaseLetter },	// GREEK CAPITAL LETTER ARCHAIC SAMPI
		{ 0x0373, 0x0373, Category::LowercaseLetter },	// GREEK SMALL LETTER ARCHAIC SAMPI
		{ 0x0374, 0x0374, Category::ModifierLetter },	// GREEK NUMERAL SIGN
		{ 0x0375, 0x0375, Category::ModifierSymbol },	// GREEK LOWER NUMERAL SIGN
		{ 0x0376, 0x0376, Category::UppercaseLetter },	// GREEK CAPITAL LETTER PAMPHYLIAN DIGAMMA
		{ 0x0377, 0x0377, Category::LowercaseLetter },	// GREEK SMALL LETTER PAMPHYLIAN DIGAMMA
		{ 0x0378, 0x0379, Category::Unassigned },	// <reserved-0378>..<reserved-0379>
		{ 0x037A, 0x037A, Category::ModifierLetter },	// GREEK YPOGEGRAMMENI
		{ 0x037B, 0x037D, Category::LowercaseLetter },	// GREEK SMALL REVERSED LUNATE SIGMA SYMBOL..GREEK SMALL REVERSED DOTTED LUNATE SIGMA SYMBOL
		{ 0x037E, 0x037E, Category::OtherPunctuation },	// GREEK QUESTION MARK
		{ 0x037F, 0x037F, Category::UppercaseLetter },	// GREEK CAPITAL LETTER YOT
		{ 0x0380, 0x0383, Category::Unassigned },	// <reserved-0380>..<reserved-0383>
		{ 0x0384, 0x0385, Category::ModifierSymbol },	// GREEK TONOS..GREEK DIALYTIKA TONOS
		{ 0x0386, 0x0386, Category::UppercaseLetter },	// GREEK CAPITAL LETTER ALPHA WITH TONOS
		{ 0x0387, 0x0387, Category::OtherPunctuation },	// GREEK ANO TELEIA
		{ 0x0388, 0x038A, Category::UppercaseLetter },	// GREEK CAPITAL LETTER EPSILON WITH TONOS..GREEK CAPITAL LETTER IOTA WITH TONOS
		{ 0x038B, 0x038B, Category::Unassigned },	// <reserved-038B>
		{ 0x038C, 0x038C, Category::UppercaseLetter },	// GREEK CAPITAL LETTER OMICRON WITH TONOS
		{ 0x038D, 0x038D, Category::Unassigned },	// <reserved-038D>
		{ 0x038E, 0x038F, Category::UppercaseLetter },	// GREEK CAPITAL LETTER UPSILON WITH TONOS..GREEK CAPITAL LETTER OMEGA WITH TONOS
		{ 0x0390, 0x0390, Category::LowercaseLetter },	// GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS
		{ 0x0391, 0x03A1, Category::UppercaseLetter },	// GREEK CAPITAL LETTER ALPHA..GREEK CAPITAL LETTER RHO
		{ 0x03A2, 0x03A2, Category::Unassigned },	// <reserved-03A2>
		{ 0x03A3, 0x03AB, Category::UppercaseLetter },	// GREEK CAPITAL LETTER SIGMA..GREEK CAPITAL LETTER UPSILON WITH DIALYTIKA
		{ 0x03AC, 0x03CE, Category::LowercaseLetter },	// GREEK SMALL LETTER ALPHA WITH TONOS..GREEK SMALL LETTER OMEGA WITH TONOS
		{ 0x03CF, 0x03CF, Category::UppercaseLetter },	// GREEK CAPITAL KAI SYMBOL
		{ 0x03D0, 0x03D1, Category::LowercaseLetter },	// GREEK BETA SYMBOL..GREEK THETA SYMBOL
		{ 0x03D2, 0x03D4, Category::UppercaseLetter },	// GREEK UPSILON WITH HOOK SYMBOL..GREEK UPSILON WITH DIAERESIS AND HOOK SYMBOL
		{ 0x03D5, 0x03D7, Category::LowercaseLetter },	// GREEK PHI SYMBOL..GREEK KAI SYMBOL
		{ 0x03D8, 0x03D8, Category::UppercaseLetter },	// GREEK LETTER ARCHAIC KOPPA
		{ 0x03D9, 0x03D9, Category::LowercaseLetter },	// GREEK SMALL LETTER ARCHAIC KOPPA
		{ 0x03DA, 0x03DA, Category::UppercaseLetter },	// GREEK LETTER STIGMA
		{ 0x03DB, 0x03DB, Category::LowercaseLetter },	// GREEK SMALL LETTER STIGMA
		{ 0x03DC, 0x03DC, Category::UppercaseLetter },	// GREEK LETTER DIGAMMA
		{ 0x03DD, 0x03DD, Category::LowercaseLetter },	// GREEK SMALL LETTER DIGAMMA
		{ 0x03DE, 0x03DE, Category::UppercaseLetter },	// GREEK LETTER KOPPA
		{ 0x03DF, 0x03DF, Category::LowercaseLetter },	// GREEK SMALL LETTER KOPPA
		{ 0x03E0, 0x03E0, Category::UppercaseLetter },	// GREEK LETTER SAMPI
		{ 0x03E1, 0x03E1, Category::LowercaseLetter },	// GREEK SMALL LETTER SAMPI
		{ 0x03E2, 0x03E2, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER SHEI
		{ 0x03E3, 0x03E3, Category::LowercaseLetter },	// COPTIC SMALL LETTER SHEI
		{ 0x03E4, 0x03E4, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER FEI
		{ 0x03E5, 0x03E5, Category::LowercaseLetter },	// COPTIC SMALL LETTER FEI
		{ 0x03E6, 0x03E6, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER KHEI
		{ 0x03E7, 0x03E7, Category::LowercaseLetter },	// COPTIC SMALL LETTER KHEI
		{ 0x03E8, 0x03E8, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER HORI
		{ 0x03E9, 0x03E9, Category::LowercaseLetter },	// COPTIC SMALL LETTER HORI
		{ 0x03EA, 0x03EA, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER GANGIA
		{ 0x03EB, 0x03EB, Category::LowercaseLetter },	// COPTIC SMALL LETTER GANGIA
		{ 0x03EC, 0x03EC, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER SHIMA
		{ 0x03ED, 0x03ED, Category::LowercaseLetter },	// COPTIC SMALL LETTER SHIMA
		{ 0x03EE, 0x03EE, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER DEI
		{ 0x03EF, 0x03F3, Category::LowercaseLetter },	// COPTIC SMALL LETTER DEI..GREEK LETTER YOT
		{ 0x03F4, 0x03F4, Category::UppercaseLetter },	// GREEK CAPITAL THETA SYMBOL
		{ 0x03F5, 0x03F5, Category::LowercaseLetter },	// GREEK LUNATE EPSILON SYMBOL
		{ 0x03F6, 0x03F6, Category::MathSymbol },	// GREEK REVERSED LUNATE EPSILON SYMBOL
		{ 0x03F7, 0x03F7, Category::UppercaseLetter },	// GREEK CAPITAL LETTER SHO
		{ 0x03F8, 0x03F8, Category::LowercaseLetter },	// GREEK SMALL LETTER SHO
		{ 0x03F9, 0x03FA, Category::UppercaseLetter },	// GREEK CAPITAL LUNATE SIGMA SYMBOL..GREEK CAPITAL LETTER SAN
		{ 0x03FB, 0x03FC, Category::LowercaseLetter },	// GREEK SMALL LETTER SAN..GREEK RHO WITH STROKE SYMBOL
		{ 0x03FD, 0x042F, Category::UppercaseLetter },	// GREEK CAPITAL REVERSED LUNATE SIGMA SYMBOL..CYRILLIC CAPITAL LETTER YA
		{ 0x0430, 0x045F, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER A..CYRILLIC SMALL LETTER DZHE
		{ 0x0460, 0x0460, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER OMEGA
		{ 0x0461, 0x0461, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER OMEGA
		{ 0x0462, 0x0462, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER YAT
		{ 0x0463, 0x0463, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER YAT
		{ 0x0464, 0x0464, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER IOTIFIED E
		{ 0x0465, 0x0465, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER IOTIFIED E
		{ 0x0466, 0x0466, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER LITTLE YUS
		{ 0x0467, 0x0467, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER LITTLE YUS
		{ 0x0468, 0x0468, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER IOTIFIED LITTLE YUS
		{ 0x0469, 0x0469, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER IOTIFIED LITTLE YUS
		{ 0x046A, 0x046A, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER BIG YUS
		{ 0x046B, 0x046B, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER BIG YUS
		{ 0x046C, 0x046C, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER IOTIFIED BIG YUS
		{ 0x046D, 0x046D, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER IOTIFIED BIG YUS
		{ 0x046E, 0x046E, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KSI
		{ 0x046F, 0x046F, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KSI
		{ 0x0470, 0x0470, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER PSI
		{ 0x0471, 0x0471, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER PSI
		{ 0x0472, 0x0472, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER FITA
		{ 0x0473, 0x0473, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER FITA
		{ 0x0474, 0x0474, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER IZHITSA
		{ 0x0475, 0x0475, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER IZHITSA
		{ 0x0476, 0x0476, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER IZHITSA WITH DOUBLE GRAVE ACCENT
		{ 0x0477, 0x0477, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER IZHITSA WITH DOUBLE GRAVE ACCENT
		{ 0x0478, 0x0478, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER UK
		{ 0x0479, 0x0479, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER UK
		{ 0x047A, 0x047A, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ROUND OMEGA
		{ 0x047B, 0x047B, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ROUND OMEGA
		{ 0x047C, 0x047C, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER OMEGA WITH TITLO
		{ 0x047D, 0x047D, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER OMEGA WITH TITLO
		{ 0x047E, 0x047E, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER OT
		{ 0x047F, 0x047F, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER OT
		{ 0x0480, 0x0480, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KOPPA
		{ 0x0481, 0x0481, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KOPPA
		{ 0x0482, 0x0482, Category::OtherSymbol },	// CYRILLIC THOUSANDS SIGN
		{ 0x0483, 0x0487, Category::NonspacingMark },	// COMBINING CYRILLIC TITLO..COMBINING CYRILLIC POKRYTIE
		{ 0x0488, 0x0489, Category::EnclosingMark },	// COMBINING CYRILLIC HUNDRED THOUSANDS SIGN..COMBINING CYRILLIC MILLIONS SIGN
		{ 0x048A, 0x048A, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER SHORT I WITH TAIL
		{ 0x048B, 0x048B, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER SHORT I WITH TAIL
		{ 0x048C, 0x048C, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER SEMISOFT SIGN
		{ 0x048D, 0x048D, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER SEMISOFT SIGN
		{ 0x048E, 0x048E, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ER WITH TICK
		{ 0x048F, 0x048F, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ER WITH TICK
		{ 0x0490, 0x0490, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER GHE WITH UPTURN
		{ 0x0491, 0x0491, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER GHE WITH UPTURN
		{ 0x0492, 0x0492, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER GHE WITH STROKE
		{ 0x0493, 0x0493, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER GHE WITH STROKE
		{ 0x0494, 0x0494, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER GHE WITH MIDDLE HOOK
		{ 0x0495, 0x0495, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER GHE WITH MIDDLE HOOK
		{ 0x0496, 0x0496, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ZHE WITH DESCENDER
		{ 0x0497, 0x0497, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ZHE WITH DESCENDER
		{ 0x0498, 0x0498, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ZE WITH DESCENDER
		{ 0x0499, 0x0499, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ZE WITH DESCENDER
		{ 0x049A, 0x049A, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KA WITH DESCENDER
		{ 0x049B, 0x049B, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KA WITH DESCENDER
		{ 0x049C, 0x049C, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KA WITH VERTICAL STROKE
		{ 0x049D, 0x049D, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KA WITH VERTICAL STROKE
		{ 0x049E, 0x049E, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KA WITH STROKE
		{ 0x049F, 0x049F, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KA WITH STROKE
		{ 0x04A0, 0x04A0, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER BASHKIR KA
		{ 0x04A1, 0x04A1, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER BASHKIR KA
		{ 0x04A2, 0x04A2, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER EN WITH DESCENDER
		{ 0x04A3, 0x04A3, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER EN WITH DESCENDER
		{ 0x04A4, 0x04A4, Category::UppercaseLetter },	// CYRILLIC CAPITAL LIGATURE EN GHE
		{ 0x04A5, 0x04A5, Category::LowercaseLetter },	// CYRILLIC SMALL LIGATURE EN GHE
		{ 0x04A6, 0x04A6, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER PE WITH MIDDLE HOOK
		{ 0x04A7, 0x04A7, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER PE WITH MIDDLE HOOK
		{ 0x04A8, 0x04A8, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ABKHASIAN HA
		{ 0x04A9, 0x04A9, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ABKHASIAN HA
		{ 0x04AA, 0x04AA, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ES WITH DESCENDER
		{ 0x04AB, 0x04AB, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ES WITH DESCENDER
		{ 0x04AC, 0x04AC, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER TE WITH DESCENDER
		{ 0x04AD, 0x04AD, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER TE WITH DESCENDER
		{ 0x04AE, 0x04AE, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER STRAIGHT U
		{ 0x04AF, 0x04AF, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER STRAIGHT U
		{ 0x04B0, 0x04B0, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER STRAIGHT U WITH STROKE
		{ 0x04B1, 0x04B1, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER STRAIGHT U WITH STROKE
		{ 0x04B2, 0x04B2, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER HA WITH DESCENDER
		{ 0x04B3, 0x04B3, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER HA WITH DESCENDER
		{ 0x04B4, 0x04B4, Category::UppercaseLetter },	// CYRILLIC CAPITAL LIGATURE TE TSE
		{ 0x04B5, 0x04B5, Category::LowercaseLetter },	// CYRILLIC SMALL LIGATURE TE TSE
		{ 0x04B6, 0x04B6, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER CHE WITH DESCENDER
		{ 0x04B7, 0x04B7, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER CHE WITH DESCENDER
		{ 0x04B8, 0x04B8, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER CHE WITH VERTICAL STROKE
		{ 0x04B9, 0x04B9, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER CHE WITH VERTICAL STROKE
		{ 0x04BA, 0x04BA, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER SHHA
		{ 0x04BB, 0x04BB, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER SHHA
		{ 0x04BC, 0x04BC, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ABKHASIAN CHE
		{ 0x04BD, 0x04BD, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ABKHASIAN CHE
		{ 0x04BE, 0x04BE, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ABKHASIAN CHE WITH DESCENDER
		{ 0x04BF, 0x04BF, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ABKHASIAN CHE WITH DESCENDER
		{ 0x04C0, 0x04C1, Category::UppercaseLetter },	// CYRILLIC LETTER PALOCHKA..CYRILLIC CAPITAL LETTER ZHE WITH BREVE
		{ 0x04C2, 0x04C2, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ZHE WITH BREVE
		{ 0x04C3, 0x04C3, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KA WITH HOOK
		{ 0x04C4, 0x04C4, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KA WITH HOOK
		{ 0x04C5, 0x04C5, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER EL WITH TAIL
		{ 0x04C6, 0x04C6, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER EL WITH TAIL
		{ 0x04C7, 0x04C7, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER EN WITH HOOK
		{ 0x04C8, 0x04C8, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER EN WITH HOOK
		{ 0x04C9, 0x04C9, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER EN WITH TAIL
		{ 0x04CA, 0x04CA, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER EN WITH TAIL
		{ 0x04CB, 0x04CB, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KHAKASSIAN CHE
		{ 0x04CC, 0x04CC, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KHAKASSIAN CHE
		{ 0x04CD, 0x04CD, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER EM WITH TAIL
		{ 0x04CE, 0x04CF, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER EM WITH TAIL..CYRILLIC SMALL LETTER PALOCHKA
		{ 0x04D0, 0x04D0, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER A WITH BREVE
		{ 0x04D1, 0x04D1, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER A WITH BREVE
		{ 0x04D2, 0x04D2, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER A WITH DIAERESIS
		{ 0x04D3, 0x04D3, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER A WITH DIAERESIS
		{ 0x04D4, 0x04D4, Category::UppercaseLetter },	// CYRILLIC CAPITAL LIGATURE A IE
		{ 0x04D5, 0x04D5, Category::LowercaseLetter },	// CYRILLIC SMALL LIGATURE A IE
		{ 0x04D6, 0x04D6, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER IE WITH BREVE
		{ 0x04D7, 0x04D7, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER IE WITH BREVE
		{ 0x04D8, 0x04D8, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER SCHWA
		{ 0x04D9, 0x04D9, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER SCHWA
		{ 0x04DA, 0x04DA, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER SCHWA WITH DIAERESIS
		{ 0x04DB, 0x04DB, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER SCHWA WITH DIAERESIS
		{ 0x04DC, 0x04DC, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ZHE WITH DIAERESIS
		{ 0x04DD, 0x04DD, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ZHE WITH DIAERESIS
		{ 0x04DE, 0x04DE, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ZE WITH DIAERESIS
		{ 0x04DF, 0x04DF, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ZE WITH DIAERESIS
		{ 0x04E0, 0x04E0, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ABKHASIAN DZE
		{ 0x04E1, 0x04E1, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ABKHASIAN DZE
		{ 0x04E2, 0x04E2, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER I WITH MACRON
		{ 0x04E3, 0x04E3, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER I WITH MACRON
		{ 0x04E4, 0x04E4, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER I WITH DIAERESIS
		{ 0x04E5, 0x04E5, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER I WITH DIAERESIS
		{ 0x04E6, 0x04E6, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER O WITH DIAERESIS
		{ 0x04E7, 0x04E7, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER O WITH DIAERESIS
		{ 0x04E8, 0x04E8, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER BARRED O
		{ 0x04E9, 0x04E9, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER BARRED O
		{ 0x04EA, 0x04EA, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER BARRED O WITH DIAERESIS
		{ 0x04EB, 0x04EB, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER BARRED O WITH DIAERESIS
		{ 0x04EC, 0x04EC, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER E WITH DIAERESIS
		{ 0x04ED, 0x04ED, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER E WITH DIAERESIS
		{ 0x04EE, 0x04EE, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER U WITH MACRON
		{ 0x04EF, 0x04EF, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER U WITH MACRON
		{ 0x04F0, 0x04F0, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER U WITH DIAERESIS
		{ 0x04F1, 0x04F1, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER U WITH DIAERESIS
		{ 0x04F2, 0x04F2, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER U WITH DOUBLE ACUTE
		{ 0x04F3, 0x04F3, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER U WITH DOUBLE ACUTE
		{ 0x04F4, 0x04F4, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER CHE WITH DIAERESIS
		{ 0x04F5, 0x04F5, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER CHE WITH DIAERESIS
		{ 0x04F6, 0x04F6, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER GHE WITH DESCENDER
		{ 0x04F7, 0x04F7, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER GHE WITH DESCENDER
		{ 0x04F8, 0x04F8, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER YERU WITH DIAERESIS
		{ 0x04F9, 0x04F9, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER YERU WITH DIAERESIS
		{ 0x04FA, 0x04FA, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER GHE WITH STROKE AND HOOK
		{ 0x04FB, 0x04FB, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER GHE WITH STROKE AND HOOK
		{ 0x04FC, 0x04FC, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER HA WITH HOOK
		{ 0x04FD, 0x04FD, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER HA WITH HOOK
		{ 0x04FE, 0x04FE, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER HA WITH STROKE
		{ 0x04FF, 0x04FF, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER HA WITH STROKE
		{ 0x0500, 0x0500, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KOMI DE
		{ 0x0501, 0x0501, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KOMI DE
		{ 0x0502, 0x0502, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KOMI DJE
		{ 0x0503, 0x0503, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KOMI DJE
		{ 0x0504, 0x0504, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KOMI ZJE
		{ 0x0505, 0x0505, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KOMI ZJE
		{ 0x0506, 0x0506, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KOMI DZJE
		{ 0x0507, 0x0507, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KOMI DZJE
		{ 0x0508, 0x0508, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KOMI LJE
		{ 0x0509, 0x0509, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KOMI LJE
		{ 0x050A, 0x050A, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KOMI NJE
		{ 0x050B, 0x050B, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KOMI NJE
		{ 0x050C, 0x050C, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KOMI SJE
		{ 0x050D, 0x050D, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KOMI SJE
		{ 0x050E, 0x050E, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER KOMI TJE
		{ 0x050F, 0x050F, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER KOMI TJE
		{ 0x0510, 0x0510, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER REVERSED ZE
		{ 0x0511, 0x0511, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER REVERSED ZE
		{ 0x0512, 0x0512, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER EL WITH HOOK
		{ 0x0513, 0x0513, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER EL WITH HOOK
		{ 0x0514, 0x0514, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER LHA
		{ 0x0515, 0x0515, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER LHA
		{ 0x0516, 0x0516, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER RHA
		{ 0x0517, 0x0517, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER RHA
		{ 0x0518, 0x0518, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER YAE
		{ 0x0519, 0x0519, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER YAE
		{ 0x051A, 0x051A, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER QA
		{ 0x051B, 0x051B, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER QA
		{ 0x051C, 0x051C, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER WE
		{ 0x051D, 0x051D, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER WE
		{ 0x051E, 0x051E, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ALEUT KA
		{ 0x051F, 0x051F, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ALEUT KA
		{ 0x0520, 0x0520, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER EL WITH MIDDLE HOOK
		{ 0x0521, 0x0521, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER EL WITH MIDDLE HOOK
		{ 0x0522, 0x0522, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER EN WITH MIDDLE HOOK
		{ 0x0523, 0x0523, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER EN WITH MIDDLE HOOK
		{ 0x0524, 0x0524, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER PE WITH DESCENDER
		{ 0x0525, 0x0525, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER PE WITH DESCENDER
		{ 0x0526, 0x0526, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER SHHA WITH DESCENDER
		{ 0x0527, 0x0527, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER SHHA WITH DESCENDER
		{ 0x0528, 0x0528, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER EN WITH LEFT HOOK
		{ 0x0529, 0x0529, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER EN WITH LEFT HOOK
		{ 0x052A, 0x052A, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER DZZHE
		{ 0x052B, 0x052B, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER DZZHE
		{ 0x052C, 0x052C, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER DCHE
		{ 0x052D, 0x052D, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER DCHE
		{ 0x052E, 0x052E, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER EL WITH DESCENDER
		{ 0x052F, 0x052F, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER EL WITH DESCENDER
		{ 0x0530, 0x0530, Category::Unassigned },	// <reserved-0530>
		{ 0x0531, 0x0556, Category::UppercaseLetter },	// ARMENIAN CAPITAL LETTER AYB..ARMENIAN CAPITAL LETTER FEH
		{ 0x0557, 0x0558, Category::Unassigned },	// <reserved-0557>..<reserved-0558>
		{ 0x0559, 0x0559, Category::ModifierLetter },	// ARMENIAN MODIFIER LETTER LEFT HALF RING
		{ 0x055A, 0x055F, Category::OtherPunctuation },	// ARMENIAN APOSTROPHE..ARMENIAN ABBREVIATION MARK
		{ 0x0560, 0x0588, Category::LowercaseLetter },	// ARMENIAN SMALL LETTER TURNED AYB..ARMENIAN SMALL LETTER YI WITH STROKE
		{ 0x0589, 0x0589, Category::OtherPunctuation },	// ARMENIAN FULL STOP
		{ 0x058A, 0x058A, Category::DashPunctuation },	// ARMENIAN HYPHEN
		{ 0x058B, 0x058C, Category::Unassigned },	// <reserved-058B>..<reserved-058C>
		{ 0x058D, 0x058E, Category::OtherSymbol },	// RIGHT-FACING ARMENIAN ETERNITY SIGN..LEFT-FACING ARMENIAN ETERNITY SIGN
		{ 0x058F, 0x058F, Category::CurrencySymbol },	// ARMENIAN DRAM SIGN
		{ 0x0590, 0x0590, Category::Unassigned },	// <reserved-0590>
		{ 0x0591, 0x05BD, Category::NonspacingMark },	// HEBREW ACCENT ETNAHTA..HEBREW POINT METEG
		{ 0x05BE, 0x05BE, Category::DashPunctuation },	// HEBREW PUNCTUATION MAQAF
		{ 0x05BF, 0x05BF, Category::NonspacingMark },	// HEBREW POINT RAFE
		{ 0x05C0, 0x05C0, Category::OtherPunctuation },	// HEBREW PUNCTUATION PASEQ
		{ 0x05C1, 0x05C2, Category::NonspacingMark },	// HEBREW POINT SHIN DOT..HEBREW POINT SIN DOT
		{ 0x05C3, 0x05C3, Category::OtherPunctuation },	// HEBREW PUNCTUATION SOF PASUQ
		{ 0x05C4, 0x05C5, Category::NonspacingMark },	// HEBREW MARK UPPER DOT..HEBREW MARK LOWER DOT
		{ 0x05C6, 0x05C6, Category::OtherPunctuation },	// HEBREW PUNCTUATION NUN HAFUKHA
		{ 0x05C7, 0x05C7, Category::NonspacingMark },	// HEBREW POINT QAMATS QATAN
		{ 0x05C8, 0x05CF, Category::Unassigned },	// <reserved-05C8>..<reserved-05CF>
		{ 0x05D0, 0x05EA, Category::OtherLetter },	// HEBREW LETTER ALEF..HEBREW LETTER TAV
		{ 0x05EB, 0x05EE, Category::Unassigned },	// <reserved-05EB>..<reserved-05EE>
		{ 0x05EF, 0x05F2, Category::OtherLetter },	// HEBREW YOD TRIANGLE..HEBREW LIGATURE YIDDISH DOUBLE YOD
		{ 0x05F3, 0x05F4, Category::OtherPunctuation },	// HEBREW PUNCTUATION GERESH..HEBREW PUNCTUATION GERSHAYIM
		{ 0x05F5, 0x05FF, Category::Unassigned },	// <reserved-05F5>..<reserved-05FF>
		{ 0x0600, 0x0605, Category::Format },	// ARABIC NUMBER SIGN..ARABIC NUMBER MARK ABOVE
		{ 0x0606, 0x0608, Category::MathSymbol },	// ARABIC-INDIC CUBE ROOT..ARABIC RAY
		{ 0x0609, 0x060A, Category::OtherPunctuation },	// ARABIC-INDIC PER MILLE SIGN..ARABIC-INDIC PER TEN THOUSAND SIGN
		{ 0x060B, 0x060B, Category::CurrencySymbol },	// AFGHANI SIGN
		{ 0x060C, 0x060D, Category::OtherPunctuation },	// ARABIC COMMA..ARABIC DATE SEPARATOR
		{ 0x060E, 0x060F, Category::OtherSymbol },	// ARABIC POETIC VERSE SIGN..ARABIC SIGN MISRA
		{ 0x0610, 0x061A, Category::NonspacingMark },	// ARABIC SIGN SALLALLAHOU ALAYHE WASSALLAM..ARABIC SMALL KASRA
		{ 0x061B, 0x061B, Category::OtherPunctuation },	// ARABIC SEMICOLON
		{ 0x061C, 0x061C, Category::Format },	// ARABIC LETTER MARK
		{ 0x061D, 0x061F, Category::OtherPunctuation },	// ARABIC END OF TEXT MARK..ARABIC QUESTION MARK
		{ 0x0620, 0x063F, Category::OtherLetter },	// ARABIC LETTER KASHMIRI YEH..ARABIC LETTER FARSI YEH WITH THREE DOTS ABOVE
		{ 0x0640, 0x0640, Category::ModifierLetter },	// ARABIC TATWEEL
		{ 0x0641, 0x064A, Category::OtherLetter },	// ARABIC LETTER FEH..ARABIC LETTER YEH
		{ 0x064B, 0x065F, Category::NonspacingMark },	// ARABIC FATHATAN..ARABIC WAVY HAMZA BELOW
		{ 0x0660, 0x0669, Category::DecimalNumber },	// ARABIC-INDIC DIGIT ZERO..ARABIC-INDIC DIGIT NINE
		{ 0x066A, 0x066D, Category::OtherPunctuation },	// ARABIC PERCENT SIGN..ARABIC FIVE POINTED STAR
		{ 0x066E, 0x066F, Category::OtherLetter },	// ARABIC LETTER DOTLESS BEH..ARABIC LETTER DOTLESS QAF
		{ 0x0670, 0x0670, Category::NonspacingMark },	// ARABIC LETTER SUPERSCRIPT ALEF
		{ 0x0671, 0x06D3, Category::OtherLetter },	// ARABIC LETTER ALEF WASLA..ARABIC LETTER YEH BARREE WITH HAMZA ABOVE
		{ 0x06D4, 0x06D4, Category::OtherPunctuation },	// ARABIC FULL STOP
		{ 0x06D5, 0x06D5, Category::OtherLetter },	// ARABIC LETTER AE
		{ 0x06D6, 0x06DC, Category::NonspacingMark },	// ARABIC SMALL HIGH LIGATURE SAD WITH LAM WITH ALEF MAKSURA..ARABIC SMALL HIGH SEEN
		{ 0x06DD, 0x06DD, Category::Format },	// ARABIC END OF AYAH
		{ 0x06DE, 0x06DE, Category::OtherSymbol },	// ARABIC START OF RUB EL HIZB
		{ 0x06DF, 0x06E4, Category::NonspacingMark },	// ARABIC SMALL HIGH ROUNDED ZERO..ARABIC SMALL HIGH MADDA
		{ 0x06E5, 0x06E6, Category::ModifierLetter },	// ARABIC SMALL WAW..ARABIC SMALL YEH
		{ 0x06E7, 0x06E8, Category::NonspacingMark },	// ARABIC SMALL HIGH YEH..ARABIC SMALL HIGH NOON
		{ 0x06E9, 0x06E9, Category::OtherSymbol },	// ARABIC PLACE OF SAJDAH
		{ 0x06EA, 0x06ED, Category::NonspacingMark },	// ARABIC EMPTY CENTRE LOW STOP..ARABIC SMALL LOW MEEM
		{ 0x06EE, 0x06EF, Category::OtherLetter },	// ARABIC LETTER DAL WITH INVERTED V..ARABIC LETTER REH WITH INVERTED V
		{ 0x06F0, 0x06F9, Category::DecimalNumber },	// EXTENDED ARABIC-INDIC DIGIT ZERO..EXTENDED ARABIC-INDIC DIGIT NINE
		{ 0x06FA, 0x06FC, Category::OtherLetter },	// ARABIC LETTER SHEEN WITH DOT BELOW..ARABIC LETTER GHAIN WITH DOT BELOW
		{ 0x06FD, 0x06FE, Category::OtherSymbol },	// ARABIC SIGN SINDHI AMPERSAND..ARABIC SIGN SINDHI POSTPOSITION MEN
		{ 0x06FF, 0x06FF, Category::OtherLetter },	// ARABIC LETTER HEH WITH INVERTED V
		{ 0x0700, 0x070D, Category::OtherPunctuation },	// SYRIAC END OF PARAGRAPH..SYRIAC HARKLEAN ASTERISCUS
		{ 0x070E, 0x070E, Category::Unassigned },	// <reserved-070E>
		{ 0x070F, 0x070F, Category::Format },	// SYRIAC ABBREVIATION MARK
		{ 0x0710, 0x0710, Category::OtherLetter },	// SYRIAC LETTER ALAPH
		{ 0x0711, 0x0711, Category::NonspacingMark },	// SYRIAC LETTER SUPERSCRIPT ALAPH
		{ 0x0712, 0x072F, Category::OtherLetter },	// SYRIAC LETTER BETH..SYRIAC LETTER PERSIAN DHALATH
		{ 0x0730, 0x074A, Category::NonspacingMark },	// SYRIAC PTHAHA ABOVE..SYRIAC BARREKH
		{ 0x074B, 0x074C, Category::Unassigned },	// <reserved-074B>..<reserved-074C>
		{ 0x074D, 0x07A5, Category::OtherLetter },	// SYRIAC LETTER SOGDIAN ZHAIN..THAANA LETTER WAAVU
		{ 0x07A6, 0x07B0, Category::NonspacingMark },	// THAANA ABAFILI..THAANA SUKUN
		{ 0x07B1, 0x07B1, Category::OtherLetter },	// THAANA LETTER NAA
		{ 0x07B2, 0x07BF, Category::Unassigned },	// <reserved-07B2>..<reserved-07BF>
		{ 0x07C0, 0x07C9, Category::DecimalNumber },	// NKO DIGIT ZERO..NKO DIGIT NINE
		{ 0x07CA, 0x07EA, Category::OtherLetter },	// NKO LETTER A..NKO LETTER JONA RA
		{ 0x07EB, 0x07F3, Category::NonspacingMark },	// NKO COMBINING SHORT HIGH TONE..NKO COMBINING DOUBLE DOT ABOVE
		{ 0x07F4, 0x07F5, Category::ModifierLetter },	// NKO HIGH TONE APOSTROPHE..NKO LOW TONE APOSTROPHE
		{ 0x07F6, 0x07F6, Category::OtherSymbol },	// NKO SYMBOL OO DENNEN
		{ 0x07F7, 0x07F9, Category::OtherPunctuation },	// NKO SYMBOL GBAKURUNEN..NKO EXCLAMATION MARK
		{ 0x07FA, 0x07FA, Category::ModifierLetter },	// NKO LAJANYALAN
		{ 0x07FB, 0x07FC, Category::Unassigned },	// <reserved-07FB>..<reserved-07FC>
		{ 0x07FD, 0x07FD, Category::NonspacingMark },	// NKO DANTAYALAN
		{ 0x07FE, 0x07FF, Category::CurrencySymbol },	// NKO DOROME SIGN..NKO TAMAN SIGN
		{ 0x0800, 0x0815, Category::OtherLetter },	// SAMARITAN LETTER ALAF..SAMARITAN LETTER TAAF
		{ 0x0816, 0x0819, Category::NonspacingMark },	// SAMARITAN MARK IN..SAMARITAN MARK DAGESH
		{ 0x081A, 0x081A, Category::ModifierLetter },	// SAMARITAN MODIFIER LETTER EPENTHETIC YUT
		{ 0x081B, 0x0823, Category::NonspacingMark },	// SAMARITAN MARK EPENTHETIC YUT..SAMARITAN VOWEL SIGN A
		{ 0x0824, 0x0824, Category::ModifierLetter },	// SAMARITAN MODIFIER LETTER SHORT A
		{ 0x0825, 0x0827, Category::NonspacingMark },	// SAMARITAN VOWEL SIGN SHORT A..SAMARITAN VOWEL SIGN U
		{ 0x0828, 0x0828, Category::ModifierLetter },	// SAMARITAN MODIFIER LETTER I
		{ 0x0829, 0x082D, Category::NonspacingMark },	// SAMARITAN VOWEL SIGN LONG I..SAMARITAN MARK NEQUDAA
		{ 0x082E, 0x082F, Category::Unassigned },	// <reserved-082E>..<reserved-082F>
		{ 0x0830, 0x083E, Category::OtherPunctuation },	// SAMARITAN PUNCTUATION NEQUDAA..SAMARITAN PUNCTUATION ANNAAU
		{ 0x083F, 0x083F, Category::Unassigned },	// <reserved-083F>
		{ 0x0840, 0x0858, Category::OtherLetter },	// MANDAIC LETTER HALQA..MANDAIC LETTER AIN
		{ 0x0859, 0x085B, Category::NonspacingMark },	// MANDAIC AFFRICATION MARK..MANDAIC GEMINATION MARK
		{ 0x085C, 0x085D, Category::Unassigned },	// <reserved-085C>..<reserved-085D>
		{ 0x085E, 0x085E, Category::OtherPunctuation },	// MANDAIC PUNCTUATION
		{ 0x085F, 0x085F, Category::Unassigned },	// <reserved-085F>
		{ 0x0860, 0x086A, Category::OtherLetter },	// SYRIAC LETTER MALAYALAM NGA..SYRIAC LETTER MALAYALAM SSA
		{ 0x086B, 0x086F, Category::Unassigned },	// <reserved-086B>..<reserved-086F>
		{ 0x0870, 0x0887, Category::OtherLetter },	// ARABIC LETTER ALEF WITH ATTACHED FATHA..ARABIC BASELINE ROUND DOT
		{ 0x0888, 0x0888, Category::ModifierSymbol },	// ARABIC RAISED ROUND DOT
		{ 0x0889, 0x088E, Category::OtherLetter },	// ARABIC LETTER NOON WITH INVERTED SMALL V..ARABIC VERTICAL TAIL
		{ 0x088F, 0x088F, Category::Unassigned },	// <reserved-088F>
		{ 0x0890, 0x0891, Category::Format },	// ARABIC POUND MARK ABOVE..ARABIC PIASTRE MARK ABOVE
		{ 0x0892, 0x0896, Category::Unassigned },	// <reserved-0892>..<reserved-0896>
		{ 0x0897, 0x089F, Category::NonspacingMark },	// ARABIC PEPET..ARABIC HALF MADDA OVER MADDA
		{ 0x08A0, 0x08C8, Category::OtherLetter },	// ARABIC LETTER BEH WITH SMALL V BELOW..ARABIC LETTER GRAF
		{ 0x08C9, 0x08C9, Category::ModifierLetter },	// ARABIC SMALL FARSI YEH
		{ 0x08CA, 0x08E1, Category::NonspacingMark },	// ARABIC SMALL HIGH FARSI YEH..ARABIC SMALL HIGH SIGN SAFHA
		{ 0x08E2, 0x08E2, Category::Format },	// ARABIC DISPUTED END OF AYAH
		{ 0x08E3, 0x0902, Category::NonspacingMark },	// ARABIC TURNED DAMMA BELOW..DEVANAGARI SIGN ANUSVARA
		{ 0x0903, 0x0903, Category::SpacingMark },	// DEVANAGARI SIGN VISARGA
		{ 0x0904, 0x0939, Category::OtherLetter },	// DEVANAGARI LETTER SHORT A..DEVANAGARI LETTER HA
		{ 0x093A, 0x093A, Category::NonspacingMark },	// DEVANAGARI VOWEL SIGN OE
		{ 0x093B, 0x093B, Category::SpacingMark },	// DEVANAGARI VOWEL SIGN OOE
		{ 0x093C, 0x093C, Category::NonspacingMark },	// DEVANAGARI SIGN NUKTA
		{ 0x093D, 0x093D, Category::OtherLetter },	// DEVANAGARI SIGN AVAGRAHA
		{ 0x093E, 0x0940, Category::SpacingMark },	// DEVANAGARI VOWEL SIGN AA..DEVANAGARI VOWEL SIGN II
		{ 0x0941, 0x0948, Category::NonspacingMark },	// DEVANAGARI VOWEL SIGN U..DEVANAGARI VOWEL SIGN AI
		{ 0x0949, 0x094C, Category::SpacingMark },	// DEVANAGARI VOWEL SIGN CANDRA O..DEVANAGARI VOWEL SIGN AU
		{ 0x094D, 0x094D, Category::NonspacingMark },	// DEVANAGARI SIGN VIRAMA
		{ 0x094E, 0x094F, Category::SpacingMark },	// DEVANAGARI VOWEL SIGN PRISHTHAMATRA E..DEVANAGARI VOWEL SIGN AW
		{ 0x0950, 0x0950, Category::OtherLetter },	// DEVANAGARI OM
		{ 0x0951, 0x0957, Category::NonspacingMark },	// DEVANAGARI STRESS SIGN UDATTA..DEVANAGARI VOWEL SIGN UUE
		{ 0x0958, 0x0961, Category::OtherLetter },	// DEVANAGARI LETTER QA..DEVANAGARI LETTER VOCALIC LL
		{ 0x0962, 0x0963, Category::NonspacingMark },	// DEVANAGARI VOWEL SIGN VOCALIC L..DEVANAGARI VOWEL SIGN VOCALIC LL
		{ 0x0964, 0x0965, Category::OtherPunctuation },	// DEVANAGARI DANDA..DEVANAGARI DOUBLE DANDA
		{ 0x0966, 0x096F, Category::DecimalNumber },	// DEVANAGARI DIGIT ZERO..DEVANAGARI DIGIT NINE
		{ 0x0970, 0x0970, Category::OtherPunctuation },	// DEVANAGARI ABBREVIATION SIGN
		{ 0x0971, 0x0971, Category::ModifierLetter },	// DEVANAGARI SIGN HIGH SPACING DOT
		{ 0x0972, 0x0980, Category::OtherLetter },	// DEVANAGARI LETTER CANDRA A..BENGALI ANJI
		{ 0x0981, 0x0981, Category::NonspacingMark },	// BENGALI SIGN CANDRABINDU
		{ 0x0982, 0x0983, Category::SpacingMark },	// BENGALI SIGN ANUSVARA..BENGALI SIGN VISARGA
		{ 0x0984, 0x0984, Category::Unassigned },	// <reserved-0984>
		{ 0x0985, 0x098C, Category::OtherLetter },	// BENGALI LETTER A..BENGALI LETTER VOCALIC L
		{ 0x098D, 0x098E, Category::Unassigned },	// <reserved-098D>..<reserved-098E>
		{ 0x098F, 0x0990, Category::OtherLetter },	// BENGALI LETTER E..BENGALI LETTER AI
		{ 0x0991, 0x0992, Category::Unassigned },	// <reserved-0991>..<reserved-0992>
		{ 0x0993, 0x09A8, Category::OtherLetter },	// BENGALI LETTER O..BENGALI LETTER NA
		{ 0x09A9, 0x09A9, Category::Unassigned },	// <reserved-09A9>
		{ 0x09AA, 0x09B0, Category::OtherLetter },	// BENGALI LETTER PA..BENGALI LETTER RA
		{ 0x09B1, 0x09B1, Category::Unassigned },	// <reserved-09B1>
		{ 0x09B2, 0x09B2, Category::OtherLetter },	// BENGALI LETTER LA
		{ 0x09B3, 0x09B5, Category::Unassigned },	// <reserved-09B3>..<reserved-09B5>
		{ 0x09B6, 0x09B9, Category::OtherLetter },	// BENGALI LETTER SHA..BENGALI LETTER HA
		{ 0x09BA, 0x09BB, Category::Unassigned },	// <reserved-09BA>..<reserved-09BB>
		{ 0x09BC, 0x09BC, Category::NonspacingMark },	// BENGALI SIGN NUKTA
		{ 0x09BD, 0x09BD, Category::OtherLetter },	// BENGALI SIGN AVAGRAHA
		{ 0x09BE, 0x09C0, Category::SpacingMark },	// BENGALI VOWEL SIGN AA..BENGALI VOWEL SIGN II
		{ 0x09C1, 0x09C4, Category::NonspacingMark },	// BENGALI VOWEL SIGN U..BENGALI VOWEL SIGN VOCALIC RR
		{ 0x09C5, 0x09C6, Category::Unassigned },	// <reserved-09C5>..<reserved-09C6>
		{ 0x09C7, 0x09C8, Category::SpacingMark },	// BENGALI VOWEL SIGN E..BENGALI VOWEL SIGN AI
		{ 0x09C9, 0x09CA, Category::Unassigned },	// <reserved-09C9>..<reserved-09CA>
		{ 0x09CB, 0x09CC, Category::SpacingMark },	// BENGALI VOWEL SIGN O..BENGALI VOWEL SIGN AU
		{ 0x09CD, 0x09CD, Category::NonspacingMark },	// BENGALI SIGN VIRAMA
		{ 0x09CE, 0x09CE, Category::OtherLetter },	// BENGALI LETTER KHANDA TA
		{ 0x09CF, 0x09D6, Category::Unassigned },	// <reserved-09CF>..<reserved-09D6>
		{ 0x09D7, 0x09D7, Category::SpacingMark },	// BENGALI AU LENGTH MARK
		{ 0x09D8, 0x09DB, Category::Unassigned },	// <reserved-09D8>..<reserved-09DB>
		{ 0x09DC, 0x09DD, Category::OtherLetter },	// BENGALI LETTER RRA..BENGALI LETTER RHA
		{ 0x09DE, 0x09DE, Category::Unassigned },	// <reserved-09DE>
		{ 0x09DF, 0x09E1, Category::OtherLetter },	// BENGALI LETTER YYA..BENGALI LETTER VOCALIC LL
		{ 0x09E2, 0x09E3, Category::NonspacingMark },	// BENGALI VOWEL SIGN VOCALIC L..BENGALI VOWEL SIGN VOCALIC LL
		{ 0x09E4, 0x09E5, Category::Unassigned },	// <reserved-09E4>..<reserved-09E5>
		{ 0x09E6, 0x09EF, Category::DecimalNumber },	// BENGALI DIGIT ZERO..BENGALI DIGIT NINE
		{ 0x09F0, 0x09F1, Category::OtherLetter },	// BENGALI LETTER RA WITH MIDDLE DIAGONAL..BENGALI LETTER RA WITH LOWER DIAGONAL
		{ 0x09F2, 0x09F3, Category::CurrencySymbol },	// BENGALI RUPEE MARK..BENGALI RUPEE SIGN
		{ 0x09F4, 0x09F9, Category::OtherNumber },	// BENGALI CURRENCY NUMERATOR ONE..BENGALI CURRENCY DENOMINATOR SIXTEEN
		{ 0x09FA, 0x09FA, Category::OtherSymbol },	// BENGALI ISSHAR
		{ 0x09FB, 0x09FB, Category::CurrencySymbol },	// BENGALI GANDA MARK
		{ 0x09FC, 0x09FC, Category::OtherLetter },	// BENGALI LETTER VEDIC ANUSVARA
		{ 0x09FD, 0x09FD, Category::OtherPunctuation },	// BENGALI ABBREVIATION SIGN
		{ 0x09FE, 0x09FE, Category::NonspacingMark },	// BENGALI SANDHI MARK
		{ 0x09FF, 0x0A00, Category::Unassigned },	// <reserved-09FF>..<reserved-0A00>
		{ 0x0A01, 0x0A02, Category::NonspacingMark },	// GURMUKHI SIGN ADAK BINDI..GURMUKHI SIGN BINDI
		{ 0x0A03, 0x0A03, Category::SpacingMark },	// GURMUKHI SIGN VISARGA
		{ 0x0A04, 0x0A04, Category::Unassigned },	// <reserved-0A04>
		{ 0x0A05, 0x0A0A, Category::OtherLetter },	// GURMUKHI LETTER A..GURMUKHI LETTER UU
		{ 0x0A0B, 0x0A0E, Category::Unassigned },	// <reserved-0A0B>..<reserved-0A0E>
		{ 0x0A0F, 0x0A10, Category::OtherLetter },	// GURMUKHI LETTER EE..GURMUKHI LETTER AI
		{ 0x0A11, 0x0A12, Category::Unassigned },	// <reserved-0A11>..<reserved-0A12>
		{ 0x0A13, 0x0A28, Category::OtherLetter },	// GURMUKHI LETTER OO..GURMUKHI LETTER NA
		{ 0x0A29, 0x0A29, Category::Unassigned },	// <reserved-0A29>
		{ 0x0A2A, 0x0A30, Category::OtherLetter },	// GURMUKHI LETTER PA..GURMUKHI LETTER RA
		{ 0x0A31, 0x0A31, Category::Unassigned },	// <reserved-0A31>
		{ 0x0A32, 0x0A33, Category::OtherLetter },	// GURMUKHI LETTER LA..GURMUKHI LETTER LLA
		{ 0x0A34, 0x0A34, Category::Unassigned },	// <reserved-0A34>
		{ 0x0A35, 0x0A36, Category::OtherLetter },	// GURMUKHI LETTER VA..GURMUKHI LETTER SHA
		{ 0x0A37, 0x0A37, Category::Unassigned },	// <reserved-0A37>
		{ 0x0A38, 0x0A39, Category::OtherLetter },	// GURMUKHI LETTER SA..GURMUKHI LETTER HA
		{ 0x0A3A, 0x0A3B, Category::Unassigned },	// <reserved-0A3A>..<reserved-0A3B>
		{ 0x0A3C, 0x0A3C, Category::NonspacingMark },	// GURMUKHI SIGN NUKTA
		{ 0x0A3D, 0x0A3D, Category::Unassigned },	// <reserved-0A3D>
		{ 0x0A3E, 0x0A40, Category::SpacingMark },	// GURMUKHI VOWEL SIGN AA..GURMUKHI VOWEL SIGN II
		{ 0x0A41, 0x0A42, Category::NonspacingMark },	// GURMUKHI VOWEL SIGN U..GURMUKHI VOWEL SIGN UU
		{ 0x0A43, 0x0A46, Category::Unassigned },	// <reserved-0A43>..<reserved-0A46>
		{ 0x0A47, 0x0A48, Category::NonspacingMark },	// GURMUKHI VOWEL SIGN EE..GURMUKHI VOWEL SIGN AI
		{ 0x0A49, 0x0A4A, Category::Unassigned },	// <reserved-0A49>..<reserved-0A4A>
		{ 0x0A4B, 0x0A4D, Category::NonspacingMark },	// GURMUKHI VOWEL SIGN OO..GURMUKHI SIGN VIRAMA
		{ 0x0A4E, 0x0A50, Category::Unassigned },	// <reserved-0A4E>..<reserved-0A50>
		{ 0x0A51, 0x0A51, Category::NonspacingMark },	// GURMUKHI SIGN UDAAT
		{ 0x0A52, 0x0A58, Category::Unassigned },	// <reserved-0A52>..<reserved-0A58>
		{ 0x0A59, 0x0A5C, Category::OtherLetter },	// GURMUKHI LETTER KHHA..GURMUKHI LETTER RRA
		{ 0x0A5D, 0x0A5D, Category::Unassigned },	// <reserved-0A5D>
		{ 0x0A5E, 0x0A5E, Category::OtherLetter },	// GURMUKHI LETTER FA
		{ 0x0A5F, 0x0A65, Category::Unassigned },	// <reserved-0A5F>..<reserved-0A65>
		{ 0x0A66, 0x0A6F, Category::DecimalNumber },	// GURMUKHI DIGIT ZERO..GURMUKHI DIGIT NINE
		{ 0x0A70, 0x0A71, Category::NonspacingMark },	// GURMUKHI TIPPI..GURMUKHI ADDAK
		{ 0x0A72, 0x0A74, Category::OtherLetter },	// GURMUKHI IRI..GURMUKHI EK ONKAR
		{ 0x0A75, 0x0A75, Category::NonspacingMark },	// GURMUKHI SIGN YAKASH
		{ 0x0A76, 0x0A76, Category::OtherPunctuation },	// GURMUKHI ABBREVIATION SIGN
		{ 0x0A77, 0x0A80, Category::Unassigned },	// <reserved-0A77>..<reserved-0A80>
		{ 0x0A81, 0x0A82, Category::NonspacingMark },	// GUJARATI SIGN CANDRABINDU..GUJARATI SIGN ANUSVARA
		{ 0x0A83, 0x0A83, Category::SpacingMark },	// GUJARATI SIGN VISARGA
		{ 0x0A84, 0x0A84, Category::Unassigned },	// <reserved-0A84>
		{ 0x0A85, 0x0A8D, Category::OtherLetter },	// GUJARATI LETTER A..GUJARATI VOWEL CANDRA E
		{ 0x0A8E, 0x0A8E, Category::Unassigned },	// <reserved-0A8E>
		{ 0x0A8F, 0x0A91, Category::OtherLetter },	// GUJARATI LETTER E..GUJARATI VOWEL CANDRA O
		{ 0x0A92, 0x0A92, Category::Unassigned },	// <reserved-0A92>
		{ 0x0A93, 0x0AA8, Category::OtherLetter },	// GUJARATI LETTER O..GUJARATI LETTER NA
		{ 0x0AA9, 0x0AA9, Category::Unassigned },	// <reserved-0AA9>
		{ 0x0AAA, 0x0AB0, Category::OtherLetter },	// GUJARATI LETTER PA..GUJARATI LETTER RA
		{ 0x0AB1, 0x0AB1, Category::Unassigned },	// <reserved-0AB1>
		{ 0x0AB2, 0x0AB3, Category::OtherLetter },	// GUJARATI LETTER LA..GUJARATI LETTER LLA
		{ 0x0AB4, 0x0AB4, Category::Unassigned },	// <reserved-0AB4>
		{ 0x0AB5, 0x0AB9, Category::OtherLetter },	// GUJARATI LETTER VA..GUJARATI LETTER HA
		{ 0x0ABA, 0x0ABB, Category::Unassigned },	// <reserved-0ABA>..<reserved-0ABB>
		{ 0x0ABC, 0x0ABC, Category::NonspacingMark },	// GUJARATI SIGN NUKTA
		{ 0x0ABD, 0x0ABD, Category::OtherLetter },	// GUJARATI SIGN AVAGRAHA
		{ 0x0ABE, 0x0AC0, Category::SpacingMark },	// GUJARATI VOWEL SIGN AA..GUJARATI VOWEL SIGN II
		{ 0x0AC1, 0x0AC5, Category::NonspacingMark },	// GUJARATI VOWEL SIGN U..GUJARATI VOWEL SIGN CANDRA E
		{ 0x0AC6, 0x0AC6, Category::Unassigned },	// <reserved-0AC6>
		{ 0x0AC7, 0x0AC8, Category::NonspacingMark },	// GUJARATI VOWEL SIGN E..GUJARATI VOWEL SIGN AI
		{ 0x0AC9, 0x0AC9, Category::SpacingMark },	// GUJARATI VOWEL SIGN CANDRA O
		{ 0x0ACA, 0x0ACA, Category::Unassigned },	// <reserved-0ACA>
		{ 0x0ACB, 0x0ACC, Category::SpacingMark },	// GUJARATI VOWEL SIGN O..GUJARATI VOWEL SIGN AU
		{ 0x0ACD, 0x0ACD, Category::NonspacingMark },	// GUJARATI SIGN VIRAMA
		{ 0x0ACE, 0x0ACF, Category::Unassigned },	// <reserved-0ACE>..<reserved-0ACF>
		{ 0x0AD0, 0x0AD0, Category::OtherLetter },	// GUJARATI OM
		{ 0x0AD1, 0x0ADF, Category::Unassigned },	// <reserved-0AD1>..<reserved-0ADF>
		{ 0x0AE0, 0x0AE1, Category::OtherLetter },	// GUJARATI LETTER VOCALIC RR..GUJARATI LETTER VOCALIC LL
		{ 0x0AE2, 0x0AE3, Category::NonspacingMark },	// GUJARATI VOWEL SIGN VOCALIC L..GUJARATI VOWEL SIGN VOCALIC LL
		{ 0x0AE4, 0x0AE5, Category::Unassigned },	// <reserved-0AE4>..<reserved-0AE5>
		{ 0x0AE6, 0x0AEF, Category::DecimalNumber },	// GUJARATI DIGIT ZERO..GUJARATI DIGIT NINE
		{ 0x0AF0, 0x0AF0, Category::OtherPunctuation },	// GUJARATI ABBREVIATION SIGN
		{ 0x0AF1, 0x0AF1, Category::CurrencySymbol },	// GUJARATI RUPEE SIGN
		{ 0x0AF2, 0x0AF8, Category::Unassigned },	// <reserved-0AF2>..<reserved-0AF8>
		{ 0x0AF9, 0x0AF9, Category::OtherLetter },	// GUJARATI LETTER ZHA
		{ 0x0AFA, 0x0AFF, Category::NonspacingMark },	// GUJARATI SIGN SUKUN..GUJARATI SIGN TWO-CIRCLE NUKTA ABOVE
		{ 0x0B00, 0x0B00, Category::Unassigned },	// <reserved-0B00>
		{ 0x0B01, 0x0B01, Category::NonspacingMark },	// ORIYA SIGN CANDRABINDU
		{ 0x0B02, 0x0B03, Category::SpacingMark },	// ORIYA SIGN ANUSVARA..ORIYA SIGN VISARGA
		{ 0x0B04, 0x0B04, Category::Unassigned },	// <reserved-0B04>
		{ 0x0B05, 0x0B0C, Category::OtherLetter },	// ORIYA LETTER A..ORIYA LETTER VOCALIC L
		{ 0x0B0D, 0x0B0E, Category::Unassigned },	// <reserved-0B0D>..<reserved-0B0E>
		{ 0x0B0F, 0x0B10, Category::OtherLetter },	// ORIYA LETTER E..ORIYA LETTER AI
		{ 0x0B11, 0x0B12, Category::Unassigned },	// <reserved-0B11>..<reserved-0B12>
		{ 0x0B13, 0x0B28, Category::OtherLetter },	// ORIYA LETTER O..ORIYA LETTER NA
		{ 0x0B29, 0x0B29, Category::Unassigned },	// <reserved-0B29>
		{ 0x0B2A, 0x0B30, Category::OtherLetter },	// ORIYA LETTER PA..ORIYA LETTER RA
		{ 0x0B31, 0x0B31, Category::Unassigned },	// <reserved-0B31>
		{ 0x0B32, 0x0B33, Category::OtherLetter },	// ORIYA LETTER LA..ORIYA LETTER LLA
		{ 0x0B34, 0x0B34, Category::Unassigned },	// <reserved-0B34>
		{ 0x0B35, 0x0B39, Category::OtherLetter },	// ORIYA LETTER VA..ORIYA LETTER HA
		{ 0x0B3A, 0x0B3B, Category::Unassigned },	// <reserved-0B3A>..<reserved-0B3B>
		{ 0x0B3C, 0x0B3C, Category::NonspacingMark },	// ORIYA SIGN NUKTA
		{ 0x0B3D, 0x0B3D, Category::OtherLetter },	// ORIYA SIGN AVAGRAHA
		{ 0x0B3E, 0x0B3E, Category::SpacingMark },	// ORIYA VOWEL SIGN AA
		{ 0x0B3F, 0x0B3F, Category::NonspacingMark },	// ORIYA VOWEL SIGN I
		{ 0x0B40, 0x0B40, Category::SpacingMark },	// ORIYA VOWEL SIGN II
		{ 0x0B41, 0x0B44, Category::NonspacingMark },	// ORIYA VOWEL SIGN U..ORIYA VOWEL SIGN VOCALIC RR
		{ 0x0B45, 0x0B46, Category::Unassigned },	// <reserved-0B45>..<reserved-0B46>
		{ 0x0B47, 0x0B48, Category::SpacingMark },	// ORIYA VOWEL SIGN E..ORIYA VOWEL SIGN AI
		{ 0x0B49, 0x0B4A, Category::Unassigned },	// <reserved-0B49>..<reserved-0B4A>
		{ 0x0B4B, 0x0B4C, Category::SpacingMark },	// ORIYA VOWEL SIGN O..ORIYA VOWEL SIGN AU
		{ 0x0B4D, 0x0B4D, Category::NonspacingMark },	// ORIYA SIGN VIRAMA
		{ 0x0B4E, 0x0B54, Category::Unassigned },	// <reserved-0B4E>..<reserved-0B54>
		{ 0x0B55, 0x0B56, Category::NonspacingMark },	// ORIYA SIGN OVERLINE..ORIYA AI LENGTH MARK
		{ 0x0B57, 0x0B57, Category::SpacingMark },	// ORIYA AU LENGTH MARK
		{ 0x0B58, 0x0B5B, Category::Unassigned },	// <reserved-0B58>..<reserved-0B5B>
		{ 0x0B5C, 0x0B5D, Category::OtherLetter },	// ORIYA LETTER RRA..ORIYA LETTER RHA
		{ 0x0B5E, 0x0B5E, Category::Unassigned },	// <reserved-0B5E>
		{ 0x0B5F, 0x0B61, Category::OtherLetter },	// ORIYA LETTER YYA..ORIYA LETTER VOCALIC LL
		{ 0x0B62, 0x0B63, Category::NonspacingMark },	// ORIYA VOWEL SIGN VOCALIC L..ORIYA VOWEL SIGN VOCALIC LL
		{ 0x0B64, 0x0B65, Category::Unassigned },	// <reserved-0B64>..<reserved-0B65>
		{ 0x0B66, 0x0B6F, Category::DecimalNumber },	// ORIYA DIGIT ZERO..ORIYA DIGIT NINE
		{ 0x0B70, 0x0B70, Category::OtherSymbol },	// ORIYA ISSHAR
		{ 0x0B71, 0x0B71, Category::OtherLetter },	// ORIYA LETTER WA
		{ 0x0B72, 0x0B77, Category::OtherNumber },	// ORIYA FRACTION ONE QUARTER..ORIYA FRACTION THREE SIXTEENTHS
		{ 0x0B78, 0x0B81, Category::Unassigned },	// <reserved-0B78>..<reserved-0B81>
		{ 0x0B82, 0x0B82, Category::NonspacingMark },	// TAMIL SIGN ANUSVARA
		{ 0x0B83, 0x0B83, Category::OtherLetter },	// TAMIL SIGN VISARGA
		{ 0x0B84, 0x0B84, Category::Unassigned },	// <reserved-0B84>
		{ 0x0B85, 0x0B8A, Category::OtherLetter },	// TAMIL LETTER A..TAMIL LETTER UU
		{ 0x0B8B, 0x0B8D, Category::Unassigned },	// <reserved-0B8B>..<reserved-0B8D>
		{ 0x0B8E, 0x0B90, Category::OtherLetter },	// TAMIL LETTER E..TAMIL LETTER AI
		{ 0x0B91, 0x0B91, Category::Unassigned },	// <reserved-0B91>
		{ 0x0B92, 0x0B95, Category::OtherLetter },	// TAMIL LETTER O..TAMIL LETTER KA
		{ 0x0B96, 0x0B98, Category::Unassigned },	// <reserved-0B96>..<reserved-0B98>
		{ 0x0B99, 0x0B9A, Category::OtherLetter },	// TAMIL LETTER NGA..TAMIL LETTER CA
		{ 0x0B9B, 0x0B9B, Category::Unassigned },	// <reserved-0B9B>
		{ 0x0B9C, 0x0B9C, Category::OtherLetter },	// TAMIL LETTER JA
		{ 0x0B9D, 0x0B9D, Category::Unassigned },	// <reserved-0B9D>
		{ 0x0B9E, 0x0B9F, Category::OtherLetter },	// TAMIL LETTER NYA..TAMIL LETTER TTA
		{ 0x0BA0, 0x0BA2, Category::Unassigned },	// <reserved-0BA0>..<reserved-0BA2>
		{ 0x0BA3, 0x0BA4, Category::OtherLetter },	// TAMIL LETTER NNA..TAMIL LETTER TA
		{ 0x0BA5, 0x0BA7, Category::Unassigned },	// <reserved-0BA5>..<reserved-0BA7>
		{ 0x0BA8, 0x0BAA, Category::OtherLetter },	// TAMIL LETTER NA..TAMIL LETTER PA
		{ 0x0BAB, 0x0BAD, Category::Unassigned },	// <reserved-0BAB>..<reserved-0BAD>
		{ 0x0BAE, 0x0BB9, Category::OtherLetter },	// TAMIL LETTER MA..TAMIL LETTER HA
		{ 0x0BBA, 0x0BBD, Category::Unassigned },	// <reserved-0BBA>..<reserved-0BBD>
		{ 0x0BBE, 0x0BBF, Category::SpacingMark },	// TAMIL VOWEL SIGN AA..TAMIL VOWEL SIGN I
		{ 0x0BC0, 0x0BC0, Category::NonspacingMark },	// TAMIL VOWEL SIGN II
		{ 0x0BC1, 0x0BC2, Category::SpacingMark },	// TAMIL VOWEL SIGN U..TAMIL VOWEL SIGN UU
		{ 0x0BC3, 0x0BC5, Category::Unassigned },	// <reserved-0BC3>..<reserved-0BC5>
		{ 0x0BC6, 0x0BC8, Category::SpacingMark },	// TAMIL VOWEL SIGN E..TAMIL VOWEL SIGN AI
		{ 0x0BC9, 0x0BC9, Category::Unassigned },	// <reserved-0BC9>
		{ 0x0BCA, 0x0BCC, Category::SpacingMark },	// TAMIL VOWEL SIGN O..TAMIL VOWEL SIGN AU
		{ 0x0BCD, 0x0BCD, Category::NonspacingMark },	// TAMIL SIGN VIRAMA
		{ 0x0BCE, 0x0BCF, Category::Unassigned },	// <reserved-0BCE>..<reserved-0BCF>
		{ 0x0BD0, 0x0BD0, Category::OtherLetter },	// TAMIL OM
		{ 0x0BD1, 0x0BD6, Category::Unassigned },	// <reserved-0BD1>..<reserved-0BD6>
		{ 0x0BD7, 0x0BD7, Category::SpacingMark },	// TAMIL AU LENGTH MARK
		{ 0x0BD8, 0x0BE5, Category::Unassigned },	// <reserved-0BD8>..<reserved-0BE5>
		{ 0x0BE6, 0x0BEF, Category::DecimalNumber },	// TAMIL DIGIT ZERO..TAMIL DIGIT NINE
		{ 0x0BF0, 0x0BF2, Category::OtherNumber },	// TAMIL NUMBER TEN..TAMIL NUMBER ONE THOUSAND
		{ 0x0BF3, 0x0BF8, Category::OtherSymbol },	// TAMIL DAY SIGN..TAMIL AS ABOVE SIGN
		{ 0x0BF9, 0x0BF9, Category::CurrencySymbol },	// TAMIL RUPEE SIGN
		{ 0x0BFA, 0x0BFA, Category::OtherSymbol },	// TAMIL NUMBER SIGN
		{ 0x0BFB, 0x0BFF, Category::Unassigned },	// <reserved-0BFB>..<reserved-0BFF>
		{ 0x0C00, 0x0C00, Category::NonspacingMark },	// TELUGU SIGN COMBINING CANDRABINDU ABOVE
		{ 0x0C01, 0x0C03, Category::SpacingMark },	// TELUGU SIGN CANDRABINDU..TELUGU SIGN VISARGA
		{ 0x0C04, 0x0C04, Category::NonspacingMark },	// TELUGU SIGN COMBINING ANUSVARA ABOVE
		{ 0x0C05, 0x0C0C, Category::OtherLetter },	// TELUGU LETTER A..TELUGU LETTER VOCALIC L
		{ 0x0C0D, 0x0C0D, Category::Unassigned },	// <reserved-0C0D>
		{ 0x0C0E, 0x0C10, Category::OtherLetter },	// TELUGU LETTER E..TELUGU LETTER AI
		{ 0x0C11, 0x0C11, Category::Unassigned },	// <reserved-0C11>
		{ 0x0C12, 0x0C28, Category::OtherLetter },	// TELUGU LETTER O..TELUGU LETTER NA
		{ 0x0C29, 0x0C29, Category::Unassigned },	// <reserved-0C29>
		{ 0x0C2A, 0x0C39, Category::OtherLetter },	// TELUGU LETTER PA..TELUGU LETTER HA
		{ 0x0C3A, 0x0C3B, Category::Unassigned },	// <reserved-0C3A>..<reserved-0C3B>
		{ 0x0C3C, 0x0C3C, Category::NonspacingMark },	// TELUGU SIGN NUKTA
		{ 0x0C3D, 0x0C3D, Category::OtherLetter },	// TELUGU SIGN AVAGRAHA
		{ 0x0C3E, 0x0C40, Category::NonspacingMark },	// TELUGU VOWEL SIGN AA..TELUGU VOWEL SIGN II
		{ 0x0C41, 0x0C44, Category::SpacingMark },	// TELUGU VOWEL SIGN U..TELUGU VOWEL SIGN VOCALIC RR
		{ 0x0C45, 0x0C45, Category::Unassigned },	// <reserved-0C45>
		{ 0x0C46, 0x0C48, Category::NonspacingMark },	// TELUGU VOWEL SIGN E..TELUGU VOWEL SIGN AI
		{ 0x0C49, 0x0C49, Category::Unassigned },	// <reserved-0C49>
		{ 0x0C4A, 0x0C4D, Category::NonspacingMark },	// TELUGU VOWEL SIGN O..TELUGU SIGN VIRAMA
		{ 0x0C4E, 0x0C54, Category::Unassigned },	// <reserved-0C4E>..<reserved-0C54>
		{ 0x0C55, 0x0C56, Category::NonspacingMark },	// TELUGU LENGTH MARK..TELUGU AI LENGTH MARK
		{ 0x0C57, 0x0C57, Category::Unassigned },	// <reserved-0C57>
		{ 0x0C58, 0x0C5A, Category::OtherLetter },	// TELUGU LETTER TSA..TELUGU LETTER RRRA
		{ 0x0C5B, 0x0C5C, Category::Unassigned },	// <reserved-0C5B>..<reserved-0C5C>
		{ 0x0C5D, 0x0C5D, Category::OtherLetter },	// TELUGU LETTER NAKAARA POLLU
		{ 0x0C5E, 0x0C5F, Category::Unassigned },	// <reserved-0C5E>..<reserved-0C5F>
		{ 0x0C60, 0x0C61, Category::OtherLetter },	// TELUGU LETTER VOCALIC RR..TELUGU LETTER VOCALIC LL
		{ 0x0C62, 0x0C63, Category::NonspacingMark },	// TELUGU VOWEL SIGN VOCALIC L..TELUGU VOWEL SIGN VOCALIC LL
		{ 0x0C64, 0x0C65, Category::Unassigned },	// <reserved-0C64>..<reserved-0C65>
		{ 0x0C66, 0x0C6F, Category::DecimalNumber },	// TELUGU DIGIT ZERO..TELUGU DIGIT NINE
		{ 0x0C70, 0x0C76, Category::Unassigned },	// <reserved-0C70>..<reserved-0C76>
		{ 0x0C77, 0x0C77, Category::OtherPunctuation },	// TELUGU SIGN SIDDHAM
		{ 0x0C78, 0x0C7E, Category::OtherNumber },	// TELUGU FRACTION DIGIT ZERO FOR ODD POWERS OF FOUR..TELUGU FRACTION DIGIT THREE FOR EVEN POWERS OF FOUR
		{ 0x0C7F, 0x0C7F, Category::OtherSymbol },	// TELUGU SIGN TUUMU
		{ 0x0C80, 0x0C80, Category::OtherLetter },	// KANNADA SIGN SPACING CANDRABINDU
		{ 0x0C81, 0x0C81, Category::NonspacingMark },	// KANNADA SIGN CANDRABINDU
		{ 0x0C82, 0x0C83, Category::SpacingMark },	// KANNADA SIGN ANUSVARA..KANNADA SIGN VISARGA
		{ 0x0C84, 0x0C84, Category::OtherPunctuation },	// KANNADA SIGN SIDDHAM
		{ 0x0C85, 0x0C8C, Category::OtherLetter },	// KANNADA LETTER A..KANNADA LETTER VOCALIC L
		{ 0x0C8D, 0x0C8D, Category::Unassigned },	// <reserved-0C8D>
		{ 0x0C8E, 0x0C90, Category::OtherLetter },	// KANNADA LETTER E..KANNADA LETTER AI
		{ 0x0C91, 0x0C91, Category::Unassigned },	// <reserved-0C91>
		{ 0x0C92, 0x0CA8, Category::OtherLetter },	// KANNADA LETTER O..KANNADA LETTER NA
		{ 0x0CA9, 0x0CA9, Category::Unassigned },	// <reserved-0CA9>
		{ 0x0CAA, 0x0CB3, Category::OtherLetter },	// KANNADA LETTER PA..KANNADA LETTER LLA
		{ 0x0CB4, 0x0CB4, Category::Unassigned },	// <reserved-0CB4>
		{ 0x0CB5, 0x0CB9, Category::OtherLetter },	// KANNADA LETTER VA..KANNADA LETTER HA
		{ 0x0CBA, 0x0CBB, Category::Unassigned },	// <reserved-0CBA>..<reserved-0CBB>
		{ 0x0CBC, 0x0CBC, Category::NonspacingMark },	// KANNADA SIGN NUKTA
		{ 0x0CBD, 0x0CBD, Category::OtherLetter },	// KANNADA SIGN AVAGRAHA
		{ 0x0CBE, 0x0CBE, Category::SpacingMark },	// KANNADA VOWEL SIGN AA
		{ 0x0CBF, 0x0CBF, Category::NonspacingMark },	// KANNADA VOWEL SIGN I
		{ 0x0CC0, 0x0CC4, Category::SpacingMark },	// KANNADA VOWEL SIGN II..KANNADA VOWEL SIGN VOCALIC RR
		{ 0x0CC5, 0x0CC5, Category::Unassigned },	// <reserved-0CC5>
		{ 0x0CC6, 0x0CC6, Category::NonspacingMark },	// KANNADA VOWEL SIGN E
		{ 0x0CC7, 0x0CC8, Category::SpacingMark },	// KANNADA VOWEL SIGN EE..KANNADA VOWEL SIGN AI
		{ 0x0CC9, 0x0CC9, Category::Unassigned },	// <reserved-0CC9>
		{ 0x0CCA, 0x0CCB, Category::SpacingMark },	// KANNADA VOWEL SIGN O..KANNADA VOWEL SIGN OO
		{ 0x0CCC, 0x0CCD, Category::NonspacingMark },	// KANNADA VOWEL SIGN AU..KANNADA SIGN VIRAMA
		{ 0x0CCE, 0x0CD4, Category::Unassigned },	// <reserved-0CCE>..<reserved-0CD4>
		{ 0x0CD5, 0x0CD6, Category::SpacingMark },	// KANNADA LENGTH MARK..KANNADA AI LENGTH MARK
		{ 0x0CD7, 0x0CDC, Category::Unassigned },	// <reserved-0CD7>..<reserved-0CDC>
		{ 0x0CDD, 0x0CDE, Category::OtherLetter },	// KANNADA LETTER NAKAARA POLLU..KANNADA LETTER FA
		{ 0x0CDF, 0x0CDF, Category::Unassigned },	// <reserved-0CDF>
		{ 0x0CE0, 0x0CE1, Category::OtherLetter },	// KANNADA LETTER VOCALIC RR..KANNADA LETTER VOCALIC LL
		{ 0x0CE2, 0x0CE3, Category::NonspacingMark },	// KANNADA VOWEL SIGN VOCALIC L..KANNADA VOWEL SIGN VOCALIC LL
		{ 0x0CE4, 0x0CE5, Category::Unassigned },	// <reserved-0CE4>..<reserved-0CE5>
		{ 0x0CE6, 0x0CEF, Category::DecimalNumber },	// KANNADA DIGIT ZERO..KANNADA DIGIT NINE
		{ 0x0CF0, 0x0CF0, Category::Unassigned },	// <reserved-0CF0>
		{ 0x0CF1, 0x0CF2, Category::OtherLetter },	// KANNADA SIGN JIHVAMULIYA..KANNADA SIGN UPADHMANIYA
		{ 0x0CF3, 0x0CF3, Category::SpacingMark },	// KANNADA SIGN COMBINING ANUSVARA ABOVE RIGHT
		{ 0x0CF4, 0x0CFF, Category::Unassigned },	// <reserved-0CF4>..<reserved-0CFF>
		{ 0x0D00, 0x0D01, Category::NonspacingMark },	// MALAYALAM SIGN COMBINING ANUSVARA ABOVE..MALAYALAM SIGN CANDRABINDU
		{ 0x0D02, 0x0D03, Category::SpacingMark },	// MALAYALAM SIGN ANUSVARA..MALAYALAM SIGN VISARGA
		{ 0x0D04, 0x0D0C, Category::OtherLetter },	// MALAYALAM LETTER VEDIC ANUSVARA..MALAYALAM LETTER VOCALIC L
		{ 0x0D0D, 0x0D0D, Category::Unassigned },	// <reserved-0D0D>
		{ 0x0D0E, 0x0D10, Category::OtherLetter },	// MALAYALAM LETTER E..MALAYALAM LETTER AI
		{ 0x0D11, 0x0D11, Category::Unassigned },	// <reserved-0D11>
		{ 0x0D12, 0x0D3A, Category::OtherLetter },	// MALAYALAM LETTER O..MALAYALAM LETTER TTTA
		{ 0x0D3B, 0x0D3C, Category::NonspacingMark },	// MALAYALAM SIGN VERTICAL BAR VIRAMA..MALAYALAM SIGN CIRCULAR VIRAMA
		{ 0x0D3D, 0x0D3D, Category::OtherLetter },	// MALAYALAM SIGN AVAGRAHA
		{ 0x0D3E, 0x0D40, Category::SpacingMark },	// MALAYALAM VOWEL SIGN AA..MALAYALAM VOWEL SIGN II
		{ 0x0D41, 0x0D44, Category::NonspacingMark },	// MALAYALAM VOWEL SIGN U..MALAYALAM VOWEL SIGN VOCALIC RR
		{ 0x0D45, 0x0D45, Category::Unassigned },	// <reserved-0D45>
		{ 0x0D46, 0x0D48, Category::SpacingMark },	// MALAYALAM VOWEL SIGN E..MALAYALAM VOWEL SIGN AI
		{ 0x0D49, 0x0D49, Category::Unassigned },	// <reserved-0D49>
		{ 0x0D4A, 0x0D4C, Category::SpacingMark },	// MALAYALAM VOWEL SIGN O..MALAYALAM VOWEL SIGN AU
		{ 0x0D4D, 0x0D4D, Category::NonspacingMark },	// MALAYALAM SIGN VIRAMA
		{ 0x0D4E, 0x0D4E, Category::OtherLetter },	// MALAYALAM LETTER DOT REPH
		{ 0x0D4F, 0x0D4F, Category::OtherSymbol },	// MALAYALAM SIGN PARA
		{ 0x0D50, 0x0D53, Category::Unassigned },	// <reserved-0D50>..<reserved-0D53>
		{ 0x0D54, 0x0D56, Category::OtherLetter },	// MALAYALAM LETTER CHILLU M..MALAYALAM LETTER CHILLU LLL
		{ 0x0D57, 0x0D57, Category::SpacingMark },	// MALAYALAM AU LENGTH MARK
		{ 0x0D58, 0x0D5E, Category::OtherNumber },	// MALAYALAM FRACTION ONE ONE-HUNDRED-AND-SIXTIETH..MALAYALAM FRACTION ONE FIFTH
		{ 0x0D5F, 0x0D61, Category::OtherLetter },	// MALAYALAM LETTER ARCHAIC II..MALAYALAM LETTER VOCALIC LL
		{ 0x0D62, 0x0D63, Category::NonspacingMark },	// MALAYALAM VOWEL SIGN VOCALIC L..MALAYALAM VOWEL SIGN VOCALIC LL
		{ 0x0D64, 0x0D65, Category::Unassigned },	// <reserved-0D64>..<reserved-0D65>
		{ 0x0D66, 0x0D6F, Category::DecimalNumber },	// MALAYALAM DIGIT ZERO..MALAYALAM DIGIT NINE
		{ 0x0D70, 0x0D78, Category::OtherNumber },	// MALAYALAM NUMBER TEN..MALAYALAM FRACTION THREE SIXTEENTHS
		{ 0x0D79, 0x0D79, Category::OtherSymbol },	// MALAYALAM DATE MARK
		{ 0x0D7A, 0x0D7F, Category::OtherLetter },	// MALAYALAM LETTER CHILLU NN..MALAYALAM LETTER CHILLU K
		{ 0x0D80, 0x0D80, Category::Unassigned },	// <reserved-0D80>
		{ 0x0D81, 0x0D81, Category::NonspacingMark },	// SINHALA SIGN CANDRABINDU
		{ 0x0D82, 0x0D83, Category::SpacingMark },	// SINHALA SIGN ANUSVARAYA..SINHALA SIGN VISARGAYA
		{ 0x0D84, 0x0D84, Category::Unassigned },	// <reserved-0D84>
		{ 0x0D85, 0x0D96, Category::OtherLetter },	// SINHALA LETTER AYANNA..SINHALA LETTER AUYANNA
		{ 0x0D97, 0x0D99, Category::Unassigned },	// <reserved-0D97>..<reserved-0D99>
		{ 0x0D9A, 0x0DB1, Category::OtherLetter },	// SINHALA LETTER ALPAPRAANA KAYANNA..SINHALA LETTER DANTAJA NAYANNA
		{ 0x0DB2, 0x0DB2, Category::Unassigned },	// <reserved-0DB2>
		{ 0x0DB3, 0x0DBB, Category::OtherLetter },	// SINHALA LETTER SANYAKA DAYANNA..SINHALA LETTER RAYANNA
		{ 0x0DBC, 0x0DBC, Category::Unassigned },	// <reserved-0DBC>
		{ 0x0DBD, 0x0DBD, Category::OtherLetter },	// SINHALA LETTER DANTAJA LAYANNA
		{ 0x0DBE, 0x0DBF, Category::Unassigned },	// <reserved-0DBE>..<reserved-0DBF>
		{ 0x0DC0, 0x0DC6, Category::OtherLetter },	// SINHALA LETTER VAYANNA..SINHALA LETTER FAYANNA
		{ 0x0DC7, 0x0DC9, Category::Unassigned },	// <reserved-0DC7>..<reserved-0DC9>
		{ 0x0DCA, 0x0DCA, Category::NonspacingMark },	// SINHALA SIGN AL-LAKUNA
		{ 0x0DCB, 0x0DCE, Category::Unassigned },	// <reserved-0DCB>..<reserved-0DCE>
		{ 0x0DCF, 0x0DD1, Category::SpacingMark },	// SINHALA VOWEL SIGN AELA-PILLA..SINHALA VOWEL SIGN DIGA AEDA-PILLA
		{ 0x0DD2, 0x0DD4, Category::NonspacingMark },	// SINHALA VOWEL SIGN KETTI IS-PILLA..SINHALA VOWEL SIGN KETTI PAA-PILLA
		{ 0x0DD5, 0x0DD5, Category::Unassigned },	// <reserved-0DD5>
		{ 0x0DD6, 0x0DD6, Category::NonspacingMark },	// SINHALA VOWEL SIGN DIGA PAA-PILLA
		{ 0x0DD7, 0x0DD7, Category::Unassigned },	// <reserved-0DD7>
		{ 0x0DD8, 0x0DDF, Category::SpacingMark },	// SINHALA VOWEL SIGN GAETTA-PILLA..SINHALA VOWEL SIGN GAYANUKITTA
		{ 0x0DE0, 0x0DE5, Category::Unassigned },	// <reserved-0DE0>..<reserved-0DE5>
		{ 0x0DE6, 0x0DEF, Category::DecimalNumber },	// SINHALA LITH DIGIT ZERO..SINHALA LITH DIGIT NINE
		{ 0x0DF0, 0x0DF1, Category::Unassigned },	// <reserved-0DF0>..<reserved-0DF1>
		{ 0x0DF2, 0x0DF3, Category::SpacingMark },	// SINHALA VOWEL SIGN DIGA GAETTA-PILLA..SINHALA VOWEL SIGN DIGA GAYANUKITTA
		{ 0x0DF4, 0x0DF4, Category::OtherPunctuation },	// SINHALA PUNCTUATION KUNDDALIYA
		{ 0x0DF5, 0x0E00, Category::Unassigned },	// <reserved-0DF5>..<reserved-0E00>
		{ 0x0E01, 0x0E30, Category::OtherLetter },	// THAI CHARACTER KO KAI..THAI CHARACTER SARA A
		{ 0x0E31, 0x0E31, Category::NonspacingMark },	// THAI CHARACTER MAI HAN-AKAT
		{ 0x0E32, 0x0E33, Category::OtherLetter },	// THAI CHARACTER SARA AA..THAI CHARACTER SARA AM
		{ 0x0E34, 0x0E3A, Category::NonspacingMark },	// THAI CHARACTER SARA I..THAI CHARACTER PHINTHU
		{ 0x0E3B, 0x0E3E, Category::Unassigned },	// <reserved-0E3B>..<reserved-0E3E>
		{ 0x0E3F, 0x0E3F, Category::CurrencySymbol },	// THAI CURRENCY SYMBOL BAHT
		{ 0x0E40, 0x0E45, Category::OtherLetter },	// THAI CHARACTER SARA E..THAI CHARACTER LAKKHANGYAO
		{ 0x0E46, 0x0E46, Category::ModifierLetter },	// THAI CHARACTER MAIYAMOK
		{ 0x0E47, 0x0E4E, Category::NonspacingMark },	// THAI CHARACTER MAITAIKHU..THAI CHARACTER YAMAKKAN
		{ 0x0E4F, 0x0E4F, Category::OtherPunctuation },	// THAI CHARACTER FONGMAN
		{ 0x0E50, 0x0E59, Category::DecimalNumber },	// THAI DIGIT ZERO..THAI DIGIT NINE
		{ 0x0E5A, 0x0E5B, Category::OtherPunctuation },	// THAI CHARACTER ANGKHANKHU..THAI CHARACTER KHOMUT
		{ 0x0E5C, 0x0E80, Category::Unassigned },	// <reserved-0E5C>..<reserved-0E80>
		{ 0x0E81, 0x0E82, Category::OtherLetter },	// LAO LETTER KO..LAO LETTER KHO SUNG
		{ 0x0E83, 0x0E83, Category::Unassigned },	// <reserved-0E83>
		{ 0x0E84, 0x0E84, Category::OtherLetter },	// LAO LETTER KHO TAM
		{ 0x0E85, 0x0E85, Category::Unassigned },	// <reserved-0E85>
		{ 0x0E86, 0x0E8A, Category::OtherLetter },	// LAO LETTER PALI GHA..LAO LETTER SO TAM
		{ 0x0E8B, 0x0E8B, Category::Unassigned },	// <reserved-0E8B>
		{ 0x0E8C, 0x0EA3, Category::OtherLetter },	// LAO LETTER PALI JHA..LAO LETTER LO LING
		{ 0x0EA4, 0x0EA4, Category::Unassigned },	// <reserved-0EA4>
		{ 0x0EA5, 0x0EA5, Category::OtherLetter },	// LAO LETTER LO LOOT
		{ 0x0EA6, 0x0EA6, Category::Unassigned },	// <reserved-0EA6>
		{ 0x0EA7, 0x0EB0, Category::OtherLetter },	// LAO LETTER WO..LAO VOWEL SIGN A
		{ 0x0EB1, 0x0EB1, Category::NonspacingMark },	// LAO VOWEL SIGN MAI KAN
		{ 0x0EB2, 0x0EB3, Category::OtherLetter },	// LAO VOWEL SIGN AA..LAO VOWEL SIGN AM
		{ 0x0EB4, 0x0EBC, Category::NonspacingMark },	// LAO VOWEL SIGN I..LAO SEMIVOWEL SIGN LO
		{ 0x0EBD, 0x0EBD, Category::OtherLetter },	// LAO SEMIVOWEL SIGN NYO
		{ 0x0EBE, 0x0EBF, Category::Unassigned },	// <reserved-0EBE>..<reserved-0EBF>
		{ 0x0EC0, 0x0EC4, Category::OtherLetter },	// LAO VOWEL SIGN E..LAO VOWEL SIGN AI
		{ 0x0EC5, 0x0EC5, Category::Unassigned },	// <reserved-0EC5>
		{ 0x0EC6, 0x0EC6, Category::ModifierLetter },	// LAO KO LA
		{ 0x0EC7, 0x0EC7, Category::Unassigned },	// <reserved-0EC7>
		{ 0x0EC8, 0x0ECE, Category::NonspacingMark },	// LAO TONE MAI EK..LAO YAMAKKAN
		{ 0x0ECF, 0x0ECF, Category::Unassigned },	// <reserved-0ECF>
		{ 0x0ED0, 0x0ED9, Category::DecimalNumber },	// LAO DIGIT ZERO..LAO DIGIT NINE
		{ 0x0EDA, 0x0EDB, Category::Unassigned },	// <reserved-0EDA>..<reserved-0EDB>
		{ 0x0EDC, 0x0EDF, Category::OtherLetter },	// LAO HO NO..LAO LETTER KHMU NYO
		{ 0x0EE0, 0x0EFF, Category::Unassigned },	// <reserved-0EE0>..<reserved-0EFF>
		{ 0x0F00, 0x0F00, Category::OtherLetter },	// TIBETAN SYLLABLE OM
		{ 0x0F01, 0x0F03, Category::OtherSymbol },	// TIBETAN MARK GTER YIG MGO TRUNCATED A..TIBETAN MARK GTER YIG MGO -UM GTER TSHEG MA
		{ 0x0F04, 0x0F12, Category::OtherPunctuation },	// TIBETAN MARK INITIAL YIG MGO MDUN MA..TIBETAN MARK RGYA GRAM SHAD
		{ 0x0F13, 0x0F13, Category::OtherSymbol },	// TIBETAN MARK CARET -DZUD RTAGS ME LONG CAN
		{ 0x0F14, 0x0F14, Category::OtherPunctuation },	// TIBETAN MARK GTER TSHEG
		{ 0x0F15, 0x0F17, Category::OtherSymbol },	// TIBETAN LOGOTYPE SIGN CHAD RTAGS..TIBETAN ASTROLOGICAL SIGN SGRA GCAN -CHAR RTAGS
		{ 0x0F18, 0x0F19, Category::NonspacingMark },	// TIBETAN ASTROLOGICAL SIGN -KHYUD PA..TIBETAN ASTROLOGICAL SIGN SDONG TSHUGS
		{ 0x0F1A, 0x0F1F, Category::OtherSymbol },	// TIBETAN SIGN RDEL DKAR GCIG..TIBETAN SIGN RDEL DKAR RDEL NAG
		{ 0x0F20, 0x0F29, Category::DecimalNumber },	// TIBETAN DIGIT ZERO..TIBETAN DIGIT NINE
		{ 0x0F2A, 0x0F33, Category::OtherNumber },	// TIBETAN DIGIT HALF ONE..TIBETAN DIGIT HALF ZERO
		{ 0x0F34, 0x0F34, Category::OtherSymbol },	// TIBETAN MARK BSDUS RTAGS
		{ 0x0F35, 0x0F35, Category::NonspacingMark },	// TIBETAN MARK NGAS BZUNG NYI ZLA
		{ 0x0F36, 0x0F36, Category::OtherSymbol },	// TIBETAN MARK CARET -DZUD RTAGS BZHI MIG CAN
		{ 0x0F37, 0x0F37, Category::NonspacingMark },	// TIBETAN MARK NGAS BZUNG SGOR RTAGS
		{ 0x0F38, 0x0F38, Category::OtherSymbol },	// TIBETAN MARK CHE MGO
		{ 0x0F39, 0x0F39, Category::NonspacingMark },	// TIBETAN MARK TSA -PHRU
		{ 0x0F3A, 0x0F3A, Category::OpenPunctuation },	// TIBETAN MARK GUG RTAGS GYON
		{ 0x0F3B, 0x0F3B, Category::ClosePunctuation },	// TIBETAN MARK GUG RTAGS GYAS
		{ 0x0F3C, 0x0F3C, Category::OpenPunctuation },	// TIBETAN MARK ANG KHANG GYON
		{ 0x0F3D, 0x0F3D, Category::ClosePunctuation },	// TIBETAN MARK ANG KHANG GYAS
		{ 0x0F3E, 0x0F3F, Category::SpacingMark },	// TIBETAN SIGN YAR TSHES..TIBETAN SIGN MAR TSHES
		{ 0x0F40, 0x0F47, Category::OtherLetter },	// TIBETAN LETTER KA..TIBETAN LETTER JA
		{ 0x0F48, 0x0F48, Category::Unassigned },	// <reserved-0F48>
		{ 0x0F49, 0x0F6C, Category::OtherLetter },	// TIBETAN LETTER NYA..TIBETAN LETTER RRA
		{ 0x0F6D, 0x0F70, Category::Unassigned },	// <reserved-0F6D>..<reserved-0F70>
		{ 0x0F71, 0x0F7E, Category::NonspacingMark },	// TIBETAN VOWEL SIGN AA..TIBETAN SIGN RJES SU NGA RO
		{ 0x0F7F, 0x0F7F, Category::SpacingMark },	// TIBETAN SIGN RNAM BCAD
		{ 0x0F80, 0x0F84, Category::NonspacingMark },	// TIBETAN VOWEL SIGN REVERSED I..TIBETAN MARK HALANTA
		{ 0x0F85, 0x0F85, Category::OtherPunctuation },	// TIBETAN MARK PALUTA
		{ 0x0F86, 0x0F87, Category::NonspacingMark },	// TIBETAN SIGN LCI RTAGS..TIBETAN SIGN YANG RTAGS
		{ 0x0F88, 0x0F8C, Category::OtherLetter },	// TIBETAN SIGN LCE TSA CAN..TIBETAN SIGN INVERTED MCHU CAN
		{ 0x0F8D, 0x0F97, Category::NonspacingMark },	// TIBETAN SUBJOINED SIGN LCE TSA CAN..TIBETAN SUBJOINED LETTER JA
		{ 0x0F98, 0x0F98, Category::Unassigned },	// <reserved-0F98>
		{ 0x0F99, 0x0FBC, Category::NonspacingMark },	// TIBETAN SUBJOINED LETTER NYA..TIBETAN SUBJOINED LETTER FIXED-FORM RA
		{ 0x0FBD, 0x0FBD, Category::Unassigned },	// <reserved-0FBD>
		{ 0x0FBE, 0x0FC5, Category::OtherSymbol },	// TIBETAN KU RU KHA..TIBETAN SYMBOL RDO RJE
		{ 0x0FC6, 0x0FC6, Category::NonspacingMark },	// TIBETAN SYMBOL PADMA GDAN
		{ 0x0FC7, 0x0FCC, Category::OtherSymbol },	// TIBETAN SYMBOL RDO RJE RGYA GRAM..TIBETAN SYMBOL NOR BU BZHI -KHYIL
		{ 0x0FCD, 0x0FCD, Category::Unassigned },	// <reserved-0FCD>
		{ 0x0FCE, 0x0FCF, Category::OtherSymbol },	// TIBETAN SIGN RDEL NAG RDEL DKAR..TIBETAN SIGN RDEL NAG GSUM
		{ 0x0FD0, 0x0FD4, Category::OtherPunctuation },	// TIBETAN MARK BSKA- SHOG GI MGO RGYAN..TIBETAN MARK CLOSING BRDA RNYING YIG MGO SGAB MA
		{ 0x0FD5, 0x0FD8, Category::OtherSymbol },	// RIGHT-FACING SVASTI SIGN..LEFT-FACING SVASTI SIGN WITH DOTS
		{ 0x0FD9, 0x0FDA, Category::OtherPunctuation },	// TIBETAN MARK LEADING MCHAN RTAGS..TIBETAN MARK TRAILING MCHAN RTAGS
		{ 0x0FDB, 0x0FFF, Category::Unassigned },	// <reserved-0FDB>..<reserved-0FFF>
		{ 0x1000, 0x102A, Category::OtherLetter },	// MYANMAR LETTER KA..MYANMAR LETTER AU
		{ 0x102B, 0x102C, Category::SpacingMark },	// MYANMAR VOWEL SIGN TALL AA..MYANMAR VOWEL SIGN AA
		{ 0x102D, 0x1030, Category::NonspacingMark },	// MYANMAR VOWEL SIGN I..MYANMAR VOWEL SIGN UU
		{ 0x1031, 0x1031, Category::SpacingMark },	// MYANMAR VOWEL SIGN E
		{ 0x1032, 0x1037, Category::NonspacingMark },	// MYANMAR VOWEL SIGN AI..MYANMAR SIGN DOT BELOW
		{ 0x1038, 0x1038, Category::SpacingMark },	// MYANMAR SIGN VISARGA
		{ 0x1039, 0x103A, Category::NonspacingMark },	// MYANMAR SIGN VIRAMA..MYANMAR SIGN ASAT
		{ 0x103B, 0x103C, Category::SpacingMark },	// MYANMAR CONSONANT SIGN MEDIAL YA..MYANMAR CONSONANT SIGN MEDIAL RA
		{ 0x103D, 0x103E, Category::NonspacingMark },	// MYANMAR CONSONANT SIGN MEDIAL WA..MYANMAR CONSONANT SIGN MEDIAL HA
		{ 0x103F, 0x103F, Category::OtherLetter },	// MYANMAR LETTER GREAT SA
		{ 0x1040, 0x1049, Category::DecimalNumber },	// MYANMAR DIGIT ZERO..MYANMAR DIGIT NINE
		{ 0x104A, 0x104F, Category::OtherPunctuation },	// MYANMAR SIGN LITTLE SECTION..MYANMAR SYMBOL GENITIVE
		{ 0x1050, 0x1055, Category::OtherLetter },	// MYANMAR LETTER SHA..MYANMAR LETTER VOCALIC LL
		{ 0x1056, 0x1057, Category::SpacingMark },	// MYANMAR VOWEL SIGN VOCALIC R..MYANMAR VOWEL SIGN VOCALIC RR
		{ 0x1058, 0x1059, Category::NonspacingMark },	// MYANMAR VOWEL SIGN VOCALIC L..MYANMAR VOWEL SIGN VOCALIC LL
		{ 0x105A, 0x105D, Category::OtherLetter },	// MYANMAR LETTER MON NGA..MYANMAR LETTER MON BBE
		{ 0x105E, 0x1060, Category::NonspacingMark },	// MYANMAR CONSONANT SIGN MON MEDIAL NA..MYANMAR CONSONANT SIGN MON MEDIAL LA
		{ 0x1061, 0x1061, Category::OtherLetter },	// MYANMAR LETTER SGAW KAREN SHA
		{ 0x1062, 0x1064, Category::SpacingMark },	// MYANMAR VOWEL SIGN SGAW KAREN EU..MYANMAR TONE MARK SGAW KAREN KE PHO
		{ 0x1065, 0x1066, Category::OtherLetter },	// MYANMAR LETTER WESTERN PWO KAREN THA..MYANMAR LETTER WESTERN PWO KAREN PWA
		{ 0x1067, 0x106D, Category::SpacingMark },	// MYANMAR VOWEL SIGN WESTERN PWO KAREN EU..MYANMAR SIGN WESTERN PWO KAREN TONE-5
		{ 0x106E, 0x1070, Category::OtherLetter },	// MYANMAR LETTER EASTERN PWO KAREN NNA..MYANMAR LETTER EASTERN PWO KAREN GHWA
		{ 0x1071, 0x1074, Category::NonspacingMark },	// MYANMAR VOWEL SIGN GEBA KAREN I..MYANMAR VOWEL SIGN KAYAH EE
		{ 0x1075, 0x1081, Category::OtherLetter },	// MYANMAR LETTER SHAN KA..MYANMAR LETTER SHAN HA
		{ 0x1082, 0x1082, Category::NonspacingMark },	// MYANMAR CONSONANT SIGN SHAN MEDIAL WA
		{ 0x1083, 0x1084, Category::SpacingMark },	// MYANMAR VOWEL SIGN SHAN AA..MYANMAR VOWEL SIGN SHAN E
		{ 0x1085, 0x1086, Category::NonspacingMark },	// MYANMAR VOWEL SIGN SHAN E ABOVE..MYANMAR VOWEL SIGN SHAN FINAL Y
		{ 0x1087, 0x108C, Category::SpacingMark },	// MYANMAR SIGN SHAN TONE-2..MYANMAR SIGN SHAN COUNCIL TONE-3
		{ 0x108D, 0x108D, Category::NonspacingMark },	// MYANMAR SIGN SHAN COUNCIL EMPHATIC TONE
		{ 0x108E, 0x108E, Category::OtherLetter },	// MYANMAR LETTER RUMAI PALAUNG FA
		{ 0x108F, 0x108F, Category::SpacingMark },	// MYANMAR SIGN RUMAI PALAUNG TONE-5
		{ 0x1090, 0x1099, Category::DecimalNumber },	// MYANMAR SHAN DIGIT ZERO..MYANMAR SHAN DIGIT NINE
		{ 0x109A, 0x109C, Category::SpacingMark },	// MYANMAR SIGN KHAMTI TONE-1..MYANMAR VOWEL SIGN AITON A
		{ 0x109D, 0x109D, Category::NonspacingMark },	// MYANMAR VOWEL SIGN AITON AI
		{ 0x109E, 0x109F, Category::OtherSymbol },	// MYANMAR SYMBOL SHAN ONE..MYANMAR SYMBOL SHAN EXCLAMATION
		{ 0x10A0, 0x10C5, Category::UppercaseLetter },	// GEORGIAN CAPITAL LETTER AN..GEORGIAN CAPITAL LETTER HOE
		{ 0x10C6, 0x10C6, Category::Unassigned },	// <reserved-10C6>
		{ 0x10C7, 0x10C7, Category::UppercaseLetter },	// GEORGIAN CAPITAL LETTER YN
		{ 0x10C8, 0x10CC, Category::Unassigned },	// <reserved-10C8>..<reserved-10CC>
		{ 0x10CD, 0x10CD, Category::UppercaseLetter },	// GEORGIAN CAPITAL LETTER AEN
		{ 0x10CE, 0x10CF, Category::Unassigned },	// <reserved-10CE>..<reserved-10CF>
		{ 0x10D0, 0x10FA, Category::LowercaseLetter },	// GEORGIAN LETTER AN..GEORGIAN LETTER AIN
		{ 0x10FB, 0x10FB, Category::OtherPunctuation },	// GEORGIAN PARAGRAPH SEPARATOR
		{ 0x10FC, 0x10FC, Category::ModifierLetter },	// MODIFIER LETTER GEORGIAN NAR
		{ 0x10FD, 0x10FF, Category::LowercaseLetter },	// GEORGIAN LETTER AEN..GEORGIAN LETTER LABIAL SIGN
		{ 0x1100, 0x1248, Category::OtherLetter },	// HANGUL CHOSEONG KIYEOK..ETHIOPIC SYLLABLE QWA
		{ 0x1249, 0x1249, Category::Unassigned },	// <reserved-1249>
		{ 0x124A, 0x124D, Category::OtherLetter },	// ETHIOPIC SYLLABLE QWI..ETHIOPIC SYLLABLE QWE
		{ 0x124E, 0x124F, Category::Unassigned },	// <reserved-124E>..<reserved-124F>
		{ 0x1250, 0x1256, Category::OtherLetter },	// ETHIOPIC SYLLABLE QHA..ETHIOPIC SYLLABLE QHO
		{ 0x1257, 0x1257, Category::Unassigned },	// <reserved-1257>
		{ 0x1258, 0x1258, Category::OtherLetter },	// ETHIOPIC SYLLABLE QHWA
		{ 0x1259, 0x1259, Category::Unassigned },	// <reserved-1259>
		{ 0x125A, 0x125D, Category::OtherLetter },	// ETHIOPIC SYLLABLE QHWI..ETHIOPIC SYLLABLE QHWE
		{ 0x125E, 0x125F, Category::Unassigned },	// <reserved-125E>..<reserved-125F>
		{ 0x1260, 0x1288, Category::OtherLetter },	// ETHIOPIC SYLLABLE BA..ETHIOPIC SYLLABLE XWA
		{ 0x1289, 0x1289, Category::Unassigned },	// <reserved-1289>
		{ 0x128A, 0x128D, Category::OtherLetter },	// ETHIOPIC SYLLABLE XWI..ETHIOPIC SYLLABLE XWE
		{ 0x128E, 0x128F, Category::Unassigned },	// <reserved-128E>..<reserved-128F>
		{ 0x1290, 0x12B0, Category::OtherLetter },	// ETHIOPIC SYLLABLE NA..ETHIOPIC SYLLABLE KWA
		{ 0x12B1, 0x12B1, Category::Unassigned },	// <reserved-12B1>
		{ 0x12B2, 0x12B5, Category::OtherLetter },	// ETHIOPIC SYLLABLE KWI..ETHIOPIC SYLLABLE KWE
		{ 0x12B6, 0x12B7, Category::Unassigned },	// <reserved-12B6>..<reserved-12B7>
		{ 0x12B8, 0x12BE, Category::OtherLetter },	// ETHIOPIC SYLLABLE KXA..ETHIOPIC SYLLABLE KXO
		{ 0x12BF, 0x12BF, Category::Unassigned },	// <reserved-12BF>
		{ 0x12C0, 0x12C0, Category::OtherLetter },	// ETHIOPIC SYLLABLE KXWA
		{ 0x12C1, 0x12C1, Category::Unassigned },	// <reserved-12C1>
		{ 0x12C2, 0x12C5, Category::OtherLetter },	// ETHIOPIC SYLLABLE KXWI..ETHIOPIC SYLLABLE KXWE
		{ 0x12C6, 0x12C7, Category::Unassigned },	// <reserved-12C6>..<reserved-12C7>
		{ 0x12C8, 0x12D6, Category::OtherLetter },	// ETHIOPIC SYLLABLE WA..ETHIOPIC SYLLABLE PHARYNGEAL O
		{ 0x12D7, 0x12D7, Category::Unassigned },	// <reserved-12D7>
		{ 0x12D8, 0x1310, Category::OtherLetter },	// ETHIOPIC SYLLABLE ZA..ETHIOPIC SYLLABLE GWA
		{ 0x1311, 0x1311, Category::Unassigned },	// <reserved-1311>
		{ 0x1312, 0x1315, Category::OtherLetter },	// ETHIOPIC SYLLABLE GWI..ETHIOPIC SYLLABLE GWE
		{ 0x1316, 0x1317, Category::Unassigned },	// <reserved-1316>..<reserved-1317>
		{ 0x1318, 0x135A, Category::OtherLetter },	// ETHIOPIC SYLLABLE GGA..ETHIOPIC SYLLABLE FYA
		{ 0x135B, 0x135C, Category::Unassigned },	// <reserved-135B>..<reserved-135C>
		{ 0x135D, 0x135F, Category::NonspacingMark },	// ETHIOPIC COMBINING GEMINATION AND VOWEL LENGTH MARK..ETHIOPIC COMBINING GEMINATION MARK
		{ 0x1360, 0x1368, Category::OtherPunctuation },	// ETHIOPIC SECTION MARK..ETHIOPIC PARAGRAPH SEPARATOR
		{ 0x1369, 0x137C, Category::OtherNumber },	// ETHIOPIC DIGIT ONE..ETHIOPIC NUMBER TEN THOUSAND
		{ 0x137D, 0x137F, Category::Unassigned },	// <reserved-137D>..<reserved-137F>
		{ 0x1380, 0x138F, Category::OtherLetter },	// ETHIOPIC SYLLABLE SEBATBEIT MWA..ETHIOPIC SYLLABLE PWE
		{ 0x1390, 0x1399, Category::OtherSymbol },	// ETHIOPIC TONAL MARK YIZET..ETHIOPIC TONAL MARK KURT
		{ 0x139A, 0x139F, Category::Unassigned },	// <reserved-139A>..<reserved-139F>
		{ 0x13A0, 0x13F5, Category::UppercaseLetter },	// CHEROKEE LETTER A..CHEROKEE LETTER MV
		{ 0x13F6, 0x13F7, Category::Unassigned },	// <reserved-13F6>..<reserved-13F7>
		{ 0x13F8, 0x13FD, Category::LowercaseLetter },	// CHEROKEE SMALL LETTER YE..CHEROKEE SMALL LETTER MV
		{ 0x13FE, 0x13FF, Category::Unassigned },	// <reserved-13FE>..<reserved-13FF>
		{ 0x1400, 0x1400, Category::DashPunctuation },	// CANADIAN SYLLABICS HYPHEN
		{ 0x1401, 0x166C, Category::OtherLetter },	// CANADIAN SYLLABICS E..CANADIAN SYLLABICS CARRIER TTSA
		{ 0x166D, 0x166D, Category::OtherSymbol },	// CANADIAN SYLLABICS CHI SIGN
		{ 0x166E, 0x166E, Category::OtherPunctuation },	// CANADIAN SYLLABICS FULL STOP
		{ 0x166F, 0x167F, Category::OtherLetter },	// CANADIAN SYLLABICS QAI..CANADIAN SYLLABICS BLACKFOOT W
		{ 0x1680, 0x1680, Category::SpaceSeparator },	// OGHAM SPACE MARK
		{ 0x1681, 0x169A, Category::OtherLetter },	// OGHAM LETTER BEITH..OGHAM LETTER PEITH
		{ 0x169B, 0x169B, Category::OpenPunctuation },	// OGHAM FEATHER MARK
		{ 0x169C, 0x169C, Category::ClosePunctuation },	// OGHAM REVERSED FEATHER MARK
		{ 0x169D, 0x169F, Category::Unassigned },	// <reserved-169D>..<reserved-169F>
		{ 0x16A0, 0x16EA, Category::OtherLetter },	// RUNIC LETTER FEHU FEOH FE F..RUNIC LETTER X
		{ 0x16EB, 0x16ED, Category::OtherPunctuation },	// RUNIC SINGLE PUNCTUATION..RUNIC CROSS PUNCTUATION
		{ 0x16EE, 0x16F0, Category::LetterNumber },	// RUNIC ARLAUG SYMBOL..RUNIC BELGTHOR SYMBOL
		{ 0x16F1, 0x16F8, Category::OtherLetter },	// RUNIC LETTER K..RUNIC LETTER FRANKS CASKET AESC
		{ 0x16F9, 0x16FF, Category::Unassigned },	// <reserved-16F9>..<reserved-16FF>
		{ 0x1700, 0x1711, Category::OtherLetter },	// TAGALOG LETTER A..TAGALOG LETTER HA
		{ 0x1712, 0x1714, Category::NonspacingMark },	// TAGALOG VOWEL SIGN I..TAGALOG SIGN VIRAMA
		{ 0x1715, 0x1715, Category::SpacingMark },	// TAGALOG SIGN PAMUDPOD
		{ 0x1716, 0x171E, Category::Unassigned },	// <reserved-1716>..<reserved-171E>
		{ 0x171F, 0x1731, Category::OtherLetter },	// TAGALOG LETTER ARCHAIC RA..HANUNOO LETTER HA
		{ 0x1732, 0x1733, Category::NonspacingMark },	// HANUNOO VOWEL SIGN I..HANUNOO VOWEL SIGN U
		{ 0x1734, 0x1734, Category::SpacingMark },	// HANUNOO SIGN PAMUDPOD
		{ 0x1735, 0x1736, Category::OtherPunctuation },	// PHILIPPINE SINGLE PUNCTUATION..PHILIPPINE DOUBLE PUNCTUATION
		{ 0x1737, 0x173F, Category::Unassigned },	// <reserved-1737>..<reserved-173F>
		{ 0x1740, 0x1751, Category::OtherLetter },	// BUHID LETTER A..BUHID LETTER HA
		{ 0x1752, 0x1753, Category::NonspacingMark },	// BUHID VOWEL SIGN I..BUHID VOWEL SIGN U
		{ 0x1754, 0x175F, Category::Unassigned },	// <reserved-1754>..<reserved-175F>
		{ 0x1760, 0x176C, Category::OtherLetter },	// TAGBANWA LETTER A..TAGBANWA LETTER YA
		{ 0x176D, 0x176D, Category::Unassigned },	// <reserved-176D>
		{ 0x176E, 0x1770, Category::OtherLetter },	// TAGBANWA LETTER LA..TAGBANWA LETTER SA
		{ 0x1771, 0x1771, Category::Unassigned },	// <reserved-1771>
		{ 0x1772, 0x1773, Category::NonspacingMark },	// TAGBANWA VOWEL SIGN I..TAGBANWA VOWEL SIGN U
		{ 0x1774, 0x177F, Category::Unassigned },	// <reserved-1774>..<reserved-177F>
		{ 0x1780, 0x17B3, Category::OtherLetter },	// KHMER LETTER KA..KHMER INDEPENDENT VOWEL QAU
		{ 0x17B4, 0x17B5, Category::NonspacingMark },	// KHMER VOWEL INHERENT AQ..KHMER VOWEL INHERENT AA
		{ 0x17B6, 0x17B6, Category::SpacingMark },	// KHMER VOWEL SIGN AA
		{ 0x17B7, 0x17BD, Category::NonspacingMark },	// KHMER VOWEL SIGN I..KHMER VOWEL SIGN UA
		{ 0x17BE, 0x17C5, Category::SpacingMark },	// KHMER VOWEL SIGN OE..KHMER VOWEL SIGN AU
		{ 0x17C6, 0x17C6, Category::NonspacingMark },	// KHMER SIGN NIKAHIT
		{ 0x17C7, 0x17C8, Category::SpacingMark },	// KHMER SIGN REAHMUK..KHMER SIGN YUUKALEAPINTU
		{ 0x17C9, 0x17D3, Category::NonspacingMark },	// KHMER SIGN MUUSIKATOAN..KHMER SIGN BATHAMASAT
		{ 0x17D4, 0x17D6, Category::OtherPunctuation },	// KHMER SIGN KHAN..KHMER SIGN CAMNUC PII KUUH
		{ 0x17D7, 0x17D7, Category::ModifierLetter },	// KHMER SIGN LEK TOO
		{ 0x17D8, 0x17DA, Category::OtherPunctuation },	// KHMER SIGN BEYYAL..KHMER SIGN KOOMUUT
		{ 0x17DB, 0x17DB, Category::CurrencySymbol },	// KHMER CURRENCY SYMBOL RIEL
		{ 0x17DC, 0x17DC, Category::OtherLetter },	// KHMER SIGN AVAKRAHASANYA
		{ 0x17DD, 0x17DD, Category::NonspacingMark },	// KHMER SIGN ATTHACAN
		{ 0x17DE, 0x17DF, Category::Unassigned },	// <reserved-17DE>..<reserved-17DF>
		{ 0x17E0, 0x17E9, Category::DecimalNumber },	// KHMER DIGIT ZERO..KHMER DIGIT NINE
		{ 0x17EA, 0x17EF, Category::Unassigned },	// <reserved-17EA>..<reserved-17EF>
		{ 0x17F0, 0x17F9, Category::OtherNumber },	// KHMER SYMBOL LEK ATTAK SON..KHMER SYMBOL LEK ATTAK PRAM-BUON
		{ 0x17FA, 0x17FF, Category::Unassigned },	// <reserved-17FA>..<reserved-17FF>
		{ 0x1800, 0x1805, Category::OtherPunctuation },	// MONGOLIAN BIRGA..MONGOLIAN FOUR DOTS
		{ 0x1806, 0x1806, Category::DashPunctuation },	// MONGOLIAN TODO SOFT HYPHEN
		{ 0x1807, 0x180A, Category::OtherPunctuation },	// MONGOLIAN SIBE SYLLABLE BOUNDARY MARKER..MONGOLIAN NIRUGU
		{ 0x180B, 0x180D, Category::NonspacingMark },	// MONGOLIAN FREE VARIATION SELECTOR ONE..MONGOLIAN FREE VARIATION SELECTOR THREE
		{ 0x180E, 0x180E, Category::Format },	// MONGOLIAN VOWEL SEPARATOR
		{ 0x180F, 0x180F, Category::NonspacingMark },	// MONGOLIAN FREE VARIATION SELECTOR FOUR
		{ 0x1810, 0x1819, Category::DecimalNumber },	// MONGOLIAN DIGIT ZERO..MONGOLIAN DIGIT NINE
		{ 0x181A, 0x181F, Category::Unassigned },	// <reserved-181A>..<reserved-181F>
		{ 0x1820, 0x1842, Category::OtherLetter },	// MONGOLIAN LETTER A..MONGOLIAN LETTER CHI
		{ 0x1843, 0x1843, Category::ModifierLetter },	// MONGOLIAN LETTER TODO LONG VOWEL SIGN
		{ 0x1844, 0x1878, Category::OtherLetter },	// MONGOLIAN LETTER TODO E..MONGOLIAN LETTER CHA WITH TWO DOTS
		{ 0x1879, 0x187F, Category::Unassigned },	// <reserved-1879>..<reserved-187F>
		{ 0x1880, 0x1884, Category::OtherLetter },	// MONGOLIAN LETTER ALI GALI ANUSVARA ONE..MONGOLIAN LETTER ALI GALI INVERTED UBADAMA
		{ 0x1885, 0x1886, Category::NonspacingMark },	// MONGOLIAN LETTER ALI GALI BALUDA..MONGOLIAN LETTER ALI GALI THREE BALUDA
		{ 0x1887, 0x18A8, Category::OtherLetter },	// MONGOLIAN LETTER ALI GALI A..MONGOLIAN LETTER MANCHU ALI GALI BHA
		{ 0x18A9, 0x18A9, Category::NonspacingMark },	// MONGOLIAN LETTER ALI GALI DAGALGA
		{ 0x18AA, 0x18AA, Category::OtherLetter },	// MONGOLIAN LETTER MANCHU ALI GALI LHA
		{ 0x18AB, 0x18AF, Category::Unassigned },	// <reserved-18AB>..<reserved-18AF>
		{ 0x18B0, 0x18F5, Category::OtherLetter },	// CANADIAN SYLLABICS OY..CANADIAN SYLLABICS CARRIER DENTAL S
		{ 0x18F6, 0x18FF, Category::Unassigned },	// <reserved-18F6>..<reserved-18FF>
		{ 0x1900, 0x191E, Category::OtherLetter },	// LIMBU VOWEL-CARRIER LETTER..LIMBU LETTER TRA
		{ 0x191F, 0x191F, Category::Unassigned },	// <reserved-191F>
		{ 0x1920, 0x1922, Category::NonspacingMark },	// LIMBU VOWEL SIGN A..LIMBU VOWEL SIGN U
		{ 0x1923, 0x1926, Category::SpacingMark },	// LIMBU VOWEL SIGN EE..LIMBU VOWEL SIGN AU
		{ 0x1927, 0x1928, Category::NonspacingMark },	// LIMBU VOWEL SIGN E..LIMBU VOWEL SIGN O
		{ 0x1929, 0x192B, Category::SpacingMark },	// LIMBU SUBJOINED LETTER YA..LIMBU SUBJOINED LETTER WA
		{ 0x192C, 0x192F, Category::Unassigned },	// <reserved-192C>..<reserved-192F>
		{ 0x1930, 0x1931, Category::SpacingMark },	// LIMBU SMALL LETTER KA..LIMBU SMALL LETTER NGA
		{ 0x1932, 0x1932, Category::NonspacingMark },	// LIMBU SMALL LETTER ANUSVARA
		{ 0x1933, 0x1938, Category::SpacingMark },	// LIMBU SMALL LETTER TA..LIMBU SMALL LETTER LA
		{ 0x1939, 0x193B, Category::NonspacingMark },	// LIMBU SIGN MUKPHRENG..LIMBU SIGN SA-I
		{ 0x193C, 0x193F, Category::Unassigned },	// <reserved-193C>..<reserved-193F>
		{ 0x1940, 0x1940, Category::OtherSymbol },	// LIMBU SIGN LOO
		{ 0x1941, 0x1943, Category::Unassigned },	// <reserved-1941>..<reserved-1943>
		{ 0x1944, 0x1945, Category::OtherPunctuation },	// LIMBU EXCLAMATION MARK..LIMBU QUESTION MARK
		{ 0x1946, 0x194F, Category::DecimalNumber },	// LIMBU DIGIT ZERO..LIMBU DIGIT NINE
		{ 0x1950, 0x196D, Category::OtherLetter },	// TAI LE LETTER KA..TAI LE LETTER AI
		{ 0x196E, 0x196F, Category::Unassigned },	// <reserved-196E>..<reserved-196F>
		{ 0x1970, 0x1974, Category::OtherLetter },	// TAI LE LETTER TONE-2..TAI LE LETTER TONE-6
		{ 0x1975, 0x197F, Category::Unassigned },	// <reserved-1975>..<reserved-197F>
		{ 0x1980, 0x19AB, Category::OtherLetter },	// NEW TAI LUE LETTER HIGH QA..NEW TAI LUE LETTER LOW SUA
		{ 0x19AC, 0x19AF, Category::Unassigned },	// <reserved-19AC>..<reserved-19AF>
		{ 0x19B0, 0x19C9, Category::OtherLetter },	// NEW TAI LUE VOWEL SIGN VOWEL SHORTENER..NEW TAI LUE TONE MARK-2
		{ 0x19CA, 0x19CF, Category::Unassigned },	// <reserved-19CA>..<reserved-19CF>
		{ 0x19D0, 0x19D9, Category::DecimalNumber },	// NEW TAI LUE DIGIT ZERO..NEW TAI LUE DIGIT NINE
		{ 0x19DA, 0x19DA, Category::OtherNumber },	// NEW TAI LUE THAM DIGIT ONE
		{ 0x19DB, 0x19DD, Category::Unassigned },	// <reserved-19DB>..<reserved-19DD>
		{ 0x19DE, 0x19FF, Category::OtherSymbol },	// NEW TAI LUE SIGN LAE..KHMER SYMBOL DAP-PRAM ROC
		{ 0x1A00, 0x1A16, Category::OtherLetter },	// BUGINESE LETTER KA..BUGINESE LETTER HA
		{ 0x1A17, 0x1A18, Category::NonspacingMark },	// BUGINESE VOWEL SIGN I..BUGINESE VOWEL SIGN U
		{ 0x1A19, 0x1A1A, Category::SpacingMark },	// BUGINESE VOWEL SIGN E..BUGINESE VOWEL SIGN O
		{ 0x1A1B, 0x1A1B, Category::NonspacingMark },	// BUGINESE VOWEL SIGN AE
		{ 0x1A1C, 0x1A1D, Category::Unassigned },	// <reserved-1A1C>..<reserved-1A1D>
		{ 0x1A1E, 0x1A1F, Category::OtherPunctuation },	// BUGINESE PALLAWA..BUGINESE END OF SECTION
		{ 0x1A20, 0x1A54, Category::OtherLetter },	// TAI THAM LETTER HIGH KA..TAI THAM LETTER GREAT SA
		{ 0x1A55, 0x1A55, Category::SpacingMark },	// TAI THAM CONSONANT SIGN MEDIAL RA
		{ 0x1A56, 0x1A56, Category::NonspacingMark },	// TAI THAM CONSONANT SIGN MEDIAL LA
		{ 0x1A57, 0x1A57, Category::SpacingMark },	// TAI THAM CONSONANT SIGN LA TANG LAI
		{ 0x1A58, 0x1A5E, Category::NonspacingMark },	// TAI THAM SIGN MAI KANG LAI..TAI THAM CONSONANT SIGN SA
		{ 0x1A5F, 0x1A5F, Category::Unassigned },	// <reserved-1A5F>
		{ 0x1A60, 0x1A60, Category::NonspacingMark },	// TAI THAM SIGN SAKOT
		{ 0x1A61, 0x1A61, Category::SpacingMark },	// TAI THAM VOWEL SIGN A
		{ 0x1A62, 0x1A62, Category::NonspacingMark },	// TAI THAM VOWEL SIGN MAI SAT
		{ 0x1A63, 0x1A64, Category::SpacingMark },	// TAI THAM VOWEL SIGN AA..TAI THAM VOWEL SIGN TALL AA
		{ 0x1A65, 0x1A6C, Category::NonspacingMark },	// TAI THAM VOWEL SIGN I..TAI THAM VOWEL SIGN OA BELOW
		{ 0x1A6D, 0x1A72, Category::SpacingMark },	// TAI THAM VOWEL SIGN OY..TAI THAM VOWEL SIGN THAM AI
		{ 0x1A73, 0x1A7C, Category::NonspacingMark },	// TAI THAM VOWEL SIGN OA ABOVE..TAI THAM SIGN KHUEN-LUE KARAN
		{ 0x1A7D, 0x1A7E, Category::Unassigned },	// <reserved-1A7D>..<reserved-1A7E>
		{ 0x1A7F, 0x1A7F, Category::NonspacingMark },	// TAI THAM COMBINING CRYPTOGRAMMIC DOT
		{ 0x1A80, 0x1A89, Category::DecimalNumber },	// TAI THAM HORA DIGIT ZERO..TAI THAM HORA DIGIT NINE
		{ 0x1A8A, 0x1A8F, Category::Unassigned },	// <reserved-1A8A>..<reserved-1A8F>
		{ 0x1A90, 0x1A99, Category::DecimalNumber },	// TAI THAM THAM DIGIT ZERO..TAI THAM THAM DIGIT NINE
		{ 0x1A9A, 0x1A9F, Category::Unassigned },	// <reserved-1A9A>..<reserved-1A9F>
		{ 0x1AA0, 0x1AA6, Category::OtherPunctuation },	// TAI THAM SIGN WIANG..TAI THAM SIGN REVERSED ROTATED RANA
		{ 0x1AA7, 0x1AA7, Category::ModifierLetter },	// TAI THAM SIGN MAI YAMOK
		{ 0x1AA8, 0x1AAD, Category::OtherPunctuation },	// TAI THAM SIGN KAAN..TAI THAM SIGN CAANG
		{ 0x1AAE, 0x1AAF, Category::Unassigned },	// <reserved-1AAE>..<reserved-1AAF>
		{ 0x1AB0, 0x1ABD, Category::NonspacingMark },	// COMBINING DOUBLED CIRCUMFLEX ACCENT..COMBINING PARENTHESES BELOW
		{ 0x1ABE, 0x1ABE, Category::EnclosingMark },	// COMBINING PARENTHESES OVERLAY
		{ 0x1ABF, 0x1ACE, Category::NonspacingMark },	// COMBINING LATIN SMALL LETTER W BELOW..COMBINING LATIN SMALL LETTER INSULAR T
		{ 0x1ACF, 0x1AFF, Category::Unassigned },	// <reserved-1ACF>..<reserved-1AFF>
		{ 0x1B00, 0x1B03, Category::NonspacingMark },	// BALINESE SIGN ULU RICEM..BALINESE SIGN SURANG
		{ 0x1B04, 0x1B04, Category::SpacingMark },	// BALINESE SIGN BISAH
		{ 0x1B05, 0x1B33, Category::OtherLetter },	// BALINESE LETTER AKARA..BALINESE LETTER HA
		{ 0x1B34, 0x1B34, Category::NonspacingMark },	// BALINESE SIGN REREKAN
		{ 0x1B35, 0x1B35, Category::SpacingMark },	// BALINESE VOWEL SIGN TEDUNG
		{ 0x1B36, 0x1B3A, Category::NonspacingMark },	// BALINESE VOWEL SIGN ULU..BALINESE VOWEL SIGN RA REPA
		{ 0x1B3B, 0x1B3B, Category::SpacingMark },	// BALINESE VOWEL SIGN RA REPA TEDUNG
		{ 0x1B3C, 0x1B3C, Category::NonspacingMark },	// BALINESE VOWEL SIGN LA LENGA
		{ 0x1B3D, 0x1B41, Category::SpacingMark },	// BALINESE VOWEL SIGN LA LENGA TEDUNG..BALINESE VOWEL SIGN TALING REPA TEDUNG
		{ 0x1B42, 0x1B42, Category::NonspacingMark },	// BALINESE VOWEL SIGN PEPET
		{ 0x1B43, 0x1B44, Category::SpacingMark },	// BALINESE VOWEL SIGN PEPET TEDUNG..BALINESE ADEG ADEG
		{ 0x1B45, 0x1B4C, Category::OtherLetter },	// BALINESE LETTER KAF SASAK..BALINESE LETTER ARCHAIC JNYA
		{ 0x1B4D, 0x1B4D, Category::Unassigned },	// <reserved-1B4D>
		{ 0x1B4E, 0x1B4F, Category::OtherPunctuation },	// BALINESE INVERTED CARIK SIKI..BALINESE INVERTED CARIK PAREREN
		{ 0x1B50, 0x1B59, Category::DecimalNumber },	// BALINESE DIGIT ZERO..BALINESE DIGIT NINE
		{ 0x1B5A, 0x1B60, Category::OtherPunctuation },	// BALINESE PANTI..BALINESE PAMENENG
		{ 0x1B61, 0x1B6A, Category::OtherSymbol },	// BALINESE MUSICAL SYMBOL DONG..BALINESE MUSICAL SYMBOL DANG GEDE
		{ 0x1B6B, 0x1B73, Category::NonspacingMark },	// BALINESE MUSICAL SYMBOL COMBINING TEGEH..BALINESE MUSICAL SYMBOL COMBINING GONG
		{ 0x1B74, 0x1B7C, Category::OtherSymbol },	// BALINESE MUSICAL SYMBOL RIGHT-HAND OPEN DUG..BALINESE MUSICAL SYMBOL LEFT-HAND OPEN PING
		{ 0x1B7D, 0x1B7F, Category::OtherPunctuation },	// BALINESE PANTI LANTANG..BALINESE PANTI BAWAK
		{ 0x1B80, 0x1B81, Category::NonspacingMark },	// SUNDANESE SIGN PANYECEK..SUNDANESE SIGN PANGLAYAR
		{ 0x1B82, 0x1B82, Category::SpacingMark },	// SUNDANESE SIGN PANGWISAD
		{ 0x1B83, 0x1BA0, Category::OtherLetter },	// SUNDANESE LETTER A..SUNDANESE LETTER HA
		{ 0x1BA1, 0x1BA1, Category::SpacingMark },	// SUNDANESE CONSONANT SIGN PAMINGKAL
		{ 0x1BA2, 0x1BA5, Category::NonspacingMark },	// SUNDANESE CONSONANT SIGN PANYAKRA..SUNDANESE VOWEL SIGN PANYUKU
		{ 0x1BA6, 0x1BA7, Category::SpacingMark },	// SUNDANESE VOWEL SIGN PANAELAENG..SUNDANESE VOWEL SIGN PANOLONG
		{ 0x1BA8, 0x1BA9, Category::NonspacingMark },	// SUNDANESE VOWEL SIGN PAMEPET..SUNDANESE VOWEL SIGN PANEULEUNG
		{ 0x1BAA, 0x1BAA, Category::SpacingMark },	// SUNDANESE SIGN PAMAAEH
		{ 0x1BAB, 0x1BAD, Category::NonspacingMark },	// SUNDANESE SIGN VIRAMA..SUNDANESE CONSONANT SIGN PASANGAN WA
		{ 0x1BAE, 0x1BAF, Category::OtherLetter },	// SUNDANESE LETTER KHA..SUNDANESE LETTER SYA
		{ 0x1BB0, 0x1BB9, Category::DecimalNumber },	// SUNDANESE DIGIT ZERO..SUNDANESE DIGIT NINE
		{ 0x1BBA, 0x1BE5, Category::OtherLetter },	// SUNDANESE AVAGRAHA..BATAK LETTER U
		{ 0x1BE6, 0x1BE6, Category::NonspacingMark },	// BATAK SIGN TOMPI
		{ 0x1BE7, 0x1BE7, Category::SpacingMark },	// BATAK VOWEL SIGN E
		{ 0x1BE8, 0x1BE9, Category::NonspacingMark },	// BATAK VOWEL SIGN PAKPAK E..BATAK VOWEL SIGN EE
		{ 0x1BEA, 0x1BEC, Category::SpacingMark },	// BATAK VOWEL SIGN I..BATAK VOWEL SIGN O
		{ 0x1BED, 0x1BED, Category::NonspacingMark },	// BATAK VOWEL SIGN KARO O
		{ 0x1BEE, 0x1BEE, Category::SpacingMark },	// BATAK VOWEL SIGN U
		{ 0x1BEF, 0x1BF1, Category::NonspacingMark },	// BATAK VOWEL SIGN U FOR SIMALUNGUN SA..BATAK CONSONANT SIGN H
		{ 0x1BF2, 0x1BF3, Category::SpacingMark },	// BATAK PANGOLAT..BATAK PANONGONAN
		{ 0x1BF4, 0x1BFB, Category::Unassigned },	// <reserved-1BF4>..<reserved-1BFB>
		{ 0x1BFC, 0x1BFF, Category::OtherPunctuation },	// BATAK SYMBOL BINDU NA METEK..BATAK SYMBOL BINDU PANGOLAT
		{ 0x1C00, 0x1C23, Category::OtherLetter },	// LEPCHA LETTER KA..LEPCHA LETTER A
		{ 0x1C24, 0x1C2B, Category::SpacingMark },	// LEPCHA SUBJOINED LETTER YA..LEPCHA VOWEL SIGN UU
		{ 0x1C2C, 0x1C33, Category::NonspacingMark },	// LEPCHA VOWEL SIGN E..LEPCHA CONSONANT SIGN T
		{ 0x1C34, 0x1C35, Category::SpacingMark },	// LEPCHA CONSONANT SIGN NYIN-DO..LEPCHA CONSONANT SIGN KANG
		{ 0x1C36, 0x1C37, Category::NonspacingMark },	// LEPCHA SIGN RAN..LEPCHA SIGN NUKTA
		{ 0x1C38, 0x1C3A, Category::Unassigned },	// <reserved-1C38>..<reserved-1C3A>
		{ 0x1C3B, 0x1C3F, Category::OtherPunctuation },	// LEPCHA PUNCTUATION TA-ROL..LEPCHA PUNCTUATION TSHOOK
		{ 0x1C40, 0x1C49, Category::DecimalNumber },	// LEPCHA DIGIT ZERO..LEPCHA DIGIT NINE
		{ 0x1C4A, 0x1C4C, Category::Unassigned },	// <reserved-1C4A>..<reserved-1C4C>
		{ 0x1C4D, 0x1C4F, Category::OtherLetter },	// LEPCHA LETTER TTA..LEPCHA LETTER DDA
		{ 0x1C50, 0x1C59, Category::DecimalNumber },	// OL CHIKI DIGIT ZERO..OL CHIKI DIGIT NINE
		{ 0x1C5A, 0x1C77, Category::OtherLetter },	// OL CHIKI LETTER LA..OL CHIKI LETTER OH
		{ 0x1C78, 0x1C7D, Category::ModifierLetter },	// OL CHIKI MU TTUDDAG..OL CHIKI AHAD
		{ 0x1C7E, 0x1C7F, Category::OtherPunctuation },	// OL CHIKI PUNCTUATION MUCAAD..OL CHIKI PUNCTUATION DOUBLE MUCAAD
		{ 0x1C80, 0x1C88, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ROUNDED VE..CYRILLIC SMALL LETTER UNBLENDED UK
		{ 0x1C89, 0x1C89, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER TJE
		{ 0x1C8A, 0x1C8A, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER TJE
		{ 0x1C8B, 0x1C8F, Category::Unassigned },	// <reserved-1C8B>..<reserved-1C8F>
		{ 0x1C90, 0x1CBA, Category::UppercaseLetter },	// GEORGIAN MTAVRULI CAPITAL LETTER AN..GEORGIAN MTAVRULI CAPITAL LETTER AIN
		{ 0x1CBB, 0x1CBC, Category::Unassigned },	// <reserved-1CBB>..<reserved-1CBC>
		{ 0x1CBD, 0x1CBF, Category::UppercaseLetter },	// GEORGIAN MTAVRULI CAPITAL LETTER AEN..GEORGIAN MTAVRULI CAPITAL LETTER LABIAL SIGN
		{ 0x1CC0, 0x1CC7, Category::OtherPunctuation },	// SUNDANESE PUNCTUATION BINDU SURYA..SUNDANESE PUNCTUATION BINDU BA SATANGA
		{ 0x1CC8, 0x1CCF, Category::Unassigned },	// <reserved-1CC8>..<reserved-1CCF>
		{ 0x1CD0, 0x1CD2, Category::NonspacingMark },	// VEDIC TONE KARSHANA..VEDIC TONE PRENKHA
		{ 0x1CD3, 0x1CD3, Category::OtherPunctuation },	// VEDIC SIGN NIHSHVASA
		{ 0x1CD4, 0x1CE0, Category::NonspacingMark },	// VEDIC SIGN YAJURVEDIC MIDLINE SVARITA..VEDIC TONE RIGVEDIC KASHMIRI INDEPENDENT SVARITA
		{ 0x1CE1, 0x1CE1, Category::SpacingMark },	// VEDIC TONE ATHARVAVEDIC INDEPENDENT SVARITA
		{ 0x1CE2, 0x1CE8, Category::NonspacingMark },	// VEDIC SIGN VISARGA SVARITA..VEDIC SIGN VISARGA ANUDATTA WITH TAIL
		{ 0x1CE9, 0x1CEC, Category::OtherLetter },	// VEDIC SIGN ANUSVARA ANTARGOMUKHA..VEDIC SIGN ANUSVARA VAMAGOMUKHA WITH TAIL
		{ 0x1CED, 0x1CED, Category::NonspacingMark },	// VEDIC SIGN TIRYAK
		{ 0x1CEE, 0x1CF3, Category::OtherLetter },	// VEDIC SIGN HEXIFORM LONG ANUSVARA..VEDIC SIGN ROTATED ARDHAVISARGA
		{ 0x1CF4, 0x1CF4, Category::NonspacingMark },	// VEDIC TONE CANDRA ABOVE
		{ 0x1CF5, 0x1CF6, Category::OtherLetter },	// VEDIC SIGN JIHVAMULIYA..VEDIC SIGN UPADHMANIYA
		{ 0x1CF7, 0x1CF7, Category::SpacingMark },	// VEDIC SIGN ATIKRAMA
		{ 0x1CF8, 0x1CF9, Category::NonspacingMark },	// VEDIC TONE RING ABOVE..VEDIC TONE DOUBLE RING ABOVE
		{ 0x1CFA, 0x1CFA, Category::OtherLetter },	// VEDIC SIGN DOUBLE ANUSVARA ANTARGOMUKHA
		{ 0x1CFB, 0x1CFF, Category::Unassigned },	// <reserved-1CFB>..<reserved-1CFF>
		{ 0x1D00, 0x1D2B, Category::LowercaseLetter },	// LATIN LETTER SMALL CAPITAL A..CYRILLIC LETTER SMALL CAPITAL EL
		{ 0x1D2C, 0x1D6A, Category::ModifierLetter },	// MODIFIER LETTER CAPITAL A..GREEK SUBSCRIPT SMALL LETTER CHI
		{ 0x1D6B, 0x1D77, Category::LowercaseLetter },	// LATIN SMALL LETTER UE..LATIN SMALL LETTER TURNED G
		{ 0x1D78, 0x1D78, Category::ModifierLetter },	// MODIFIER LETTER CYRILLIC EN
		{ 0x1D79, 0x1D9A, Category::LowercaseLetter },	// LATIN SMALL LETTER INSULAR G..LATIN SMALL LETTER EZH WITH RETROFLEX HOOK
		{ 0x1D9B, 0x1DBF, Category::ModifierLetter },	// MODIFIER LETTER SMALL TURNED ALPHA..MODIFIER LETTER SMALL THETA
		{ 0x1DC0, 0x1DFF, Category::NonspacingMark },	// COMBINING DOTTED GRAVE ACCENT..COMBINING RIGHT ARROWHEAD AND DOWN ARROWHEAD BELOW
		{ 0x1E00, 0x1E00, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH RING BELOW
		{ 0x1E01, 0x1E01, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH RING BELOW
		{ 0x1E02, 0x1E02, Category::UppercaseLetter },	// LATIN CAPITAL LETTER B WITH DOT ABOVE
		{ 0x1E03, 0x1E03, Category::LowercaseLetter },	// LATIN SMALL LETTER B WITH DOT ABOVE
		{ 0x1E04, 0x1E04, Category::UppercaseLetter },	// LATIN CAPITAL LETTER B WITH DOT BELOW
		{ 0x1E05, 0x1E05, Category::LowercaseLetter },	// LATIN SMALL LETTER B WITH DOT BELOW
		{ 0x1E06, 0x1E06, Category::UppercaseLetter },	// LATIN CAPITAL LETTER B WITH LINE BELOW
		{ 0x1E07, 0x1E07, Category::LowercaseLetter },	// LATIN SMALL LETTER B WITH LINE BELOW
		{ 0x1E08, 0x1E08, Category::UppercaseLetter },	// LATIN CAPITAL LETTER C WITH CEDILLA AND ACUTE
		{ 0x1E09, 0x1E09, Category::LowercaseLetter },	// LATIN SMALL LETTER C WITH CEDILLA AND ACUTE
		{ 0x1E0A, 0x1E0A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER D WITH DOT ABOVE
		{ 0x1E0B, 0x1E0B, Category::LowercaseLetter },	// LATIN SMALL LETTER D WITH DOT ABOVE
		{ 0x1E0C, 0x1E0C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER D WITH DOT BELOW
		{ 0x1E0D, 0x1E0D, Category::LowercaseLetter },	// LATIN SMALL LETTER D WITH DOT BELOW
		{ 0x1E0E, 0x1E0E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER D WITH LINE BELOW
		{ 0x1E0F, 0x1E0F, Category::LowercaseLetter },	// LATIN SMALL LETTER D WITH LINE BELOW
		{ 0x1E10, 0x1E10, Category::UppercaseLetter },	// LATIN CAPITAL LETTER D WITH CEDILLA
		{ 0x1E11, 0x1E11, Category::LowercaseLetter },	// LATIN SMALL LETTER D WITH CEDILLA
		{ 0x1E12, 0x1E12, Category::UppercaseLetter },	// LATIN CAPITAL LETTER D WITH CIRCUMFLEX BELOW
		{ 0x1E13, 0x1E13, Category::LowercaseLetter },	// LATIN SMALL LETTER D WITH CIRCUMFLEX BELOW
		{ 0x1E14, 0x1E14, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH MACRON AND GRAVE
		{ 0x1E15, 0x1E15, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH MACRON AND GRAVE
		{ 0x1E16, 0x1E16, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH MACRON AND ACUTE
		{ 0x1E17, 0x1E17, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH MACRON AND ACUTE
		{ 0x1E18, 0x1E18, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX BELOW
		{ 0x1E19, 0x1E19, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH CIRCUMFLEX BELOW
		{ 0x1E1A, 0x1E1A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH TILDE BELOW
		{ 0x1E1B, 0x1E1B, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH TILDE BELOW
		{ 0x1E1C, 0x1E1C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH CEDILLA AND BREVE
		{ 0x1E1D, 0x1E1D, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH CEDILLA AND BREVE
		{ 0x1E1E, 0x1E1E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER F WITH DOT ABOVE
		{ 0x1E1F, 0x1E1F, Category::LowercaseLetter },	// LATIN SMALL LETTER F WITH DOT ABOVE
		{ 0x1E20, 0x1E20, Category::UppercaseLetter },	// LATIN CAPITAL LETTER G WITH MACRON
		{ 0x1E21, 0x1E21, Category::LowercaseLetter },	// LATIN SMALL LETTER G WITH MACRON
		{ 0x1E22, 0x1E22, Category::UppercaseLetter },	// LATIN CAPITAL LETTER H WITH DOT ABOVE
		{ 0x1E23, 0x1E23, Category::LowercaseLetter },	// LATIN SMALL LETTER H WITH DOT ABOVE
		{ 0x1E24, 0x1E24, Category::UppercaseLetter },	// LATIN CAPITAL LETTER H WITH DOT BELOW
		{ 0x1E25, 0x1E25, Category::LowercaseLetter },	// LATIN SMALL LETTER H WITH DOT BELOW
		{ 0x1E26, 0x1E26, Category::UppercaseLetter },	// LATIN CAPITAL LETTER H WITH DIAERESIS
		{ 0x1E27, 0x1E27, Category::LowercaseLetter },	// LATIN SMALL LETTER H WITH DIAERESIS
		{ 0x1E28, 0x1E28, Category::UppercaseLetter },	// LATIN CAPITAL LETTER H WITH CEDILLA
		{ 0x1E29, 0x1E29, Category::LowercaseLetter },	// LATIN SMALL LETTER H WITH CEDILLA
		{ 0x1E2A, 0x1E2A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER H WITH BREVE BELOW
		{ 0x1E2B, 0x1E2B, Category::LowercaseLetter },	// LATIN SMALL LETTER H WITH BREVE BELOW
		{ 0x1E2C, 0x1E2C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER I WITH TILDE BELOW
		{ 0x1E2D, 0x1E2D, Category::LowercaseLetter },	// LATIN SMALL LETTER I WITH TILDE BELOW
		{ 0x1E2E, 0x1E2E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER I WITH DIAERESIS AND ACUTE
		{ 0x1E2F, 0x1E2F, Category::LowercaseLetter },	// LATIN SMALL LETTER I WITH DIAERESIS AND ACUTE
		{ 0x1E30, 0x1E30, Category::UppercaseLetter },	// LATIN CAPITAL LETTER K WITH ACUTE
		{ 0x1E31, 0x1E31, Category::LowercaseLetter },	// LATIN SMALL LETTER K WITH ACUTE
		{ 0x1E32, 0x1E32, Category::UppercaseLetter },	// LATIN CAPITAL LETTER K WITH DOT BELOW
		{ 0x1E33, 0x1E33, Category::LowercaseLetter },	// LATIN SMALL LETTER K WITH DOT BELOW
		{ 0x1E34, 0x1E34, Category::UppercaseLetter },	// LATIN CAPITAL LETTER K WITH LINE BELOW
		{ 0x1E35, 0x1E35, Category::LowercaseLetter },	// LATIN SMALL LETTER K WITH LINE BELOW
		{ 0x1E36, 0x1E36, Category::UppercaseLetter },	// LATIN CAPITAL LETTER L WITH DOT BELOW
		{ 0x1E37, 0x1E37, Category::LowercaseLetter },	// LATIN SMALL LETTER L WITH DOT BELOW
		{ 0x1E38, 0x1E38, Category::UppercaseLetter },	// LATIN CAPITAL LETTER L WITH DOT BELOW AND MACRON
		{ 0x1E39, 0x1E39, Category::LowercaseLetter },	// LATIN SMALL LETTER L WITH DOT BELOW AND MACRON
		{ 0x1E3A, 0x1E3A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER L WITH LINE BELOW
		{ 0x1E3B, 0x1E3B, Category::LowercaseLetter },	// LATIN SMALL LETTER L WITH LINE BELOW
		{ 0x1E3C, 0x1E3C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER L WITH CIRCUMFLEX BELOW
		{ 0x1E3D, 0x1E3D, Category::LowercaseLetter },	// LATIN SMALL LETTER L WITH CIRCUMFLEX BELOW
		{ 0x1E3E, 0x1E3E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER M WITH ACUTE
		{ 0x1E3F, 0x1E3F, Category::LowercaseLetter },	// LATIN SMALL LETTER M WITH ACUTE
		{ 0x1E40, 0x1E40, Category::UppercaseLetter },	// LATIN CAPITAL LETTER M WITH DOT ABOVE
		{ 0x1E41, 0x1E41, Category::LowercaseLetter },	// LATIN SMALL LETTER M WITH DOT ABOVE
		{ 0x1E42, 0x1E42, Category::UppercaseLetter },	// LATIN CAPITAL LETTER M WITH DOT BELOW
		{ 0x1E43, 0x1E43, Category::LowercaseLetter },	// LATIN SMALL LETTER M WITH DOT BELOW
		{ 0x1E44, 0x1E44, Category::UppercaseLetter },	// LATIN CAPITAL LETTER N WITH DOT ABOVE
		{ 0x1E45, 0x1E45, Category::LowercaseLetter },	// LATIN SMALL LETTER N WITH DOT ABOVE
		{ 0x1E46, 0x1E46, Category::UppercaseLetter },	// LATIN CAPITAL LETTER N WITH DOT BELOW
		{ 0x1E47, 0x1E47, Category::LowercaseLetter },	// LATIN SMALL LETTER N WITH DOT BELOW
		{ 0x1E48, 0x1E48, Category::UppercaseLetter },	// LATIN CAPITAL LETTER N WITH LINE BELOW
		{ 0x1E49, 0x1E49, Category::LowercaseLetter },	// LATIN SMALL LETTER N WITH LINE BELOW
		{ 0x1E4A, 0x1E4A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER N WITH CIRCUMFLEX BELOW
		{ 0x1E4B, 0x1E4B, Category::LowercaseLetter },	// LATIN SMALL LETTER N WITH CIRCUMFLEX BELOW
		{ 0x1E4C, 0x1E4C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH TILDE AND ACUTE
		{ 0x1E4D, 0x1E4D, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH TILDE AND ACUTE
		{ 0x1E4E, 0x1E4E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH TILDE AND DIAERESIS
		{ 0x1E4F, 0x1E4F, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH TILDE AND DIAERESIS
		{ 0x1E50, 0x1E50, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH MACRON AND GRAVE
		{ 0x1E51, 0x1E51, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH MACRON AND GRAVE
		{ 0x1E52, 0x1E52, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH MACRON AND ACUTE
		{ 0x1E53, 0x1E53, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH MACRON AND ACUTE
		{ 0x1E54, 0x1E54, Category::UppercaseLetter },	// LATIN CAPITAL LETTER P WITH ACUTE
		{ 0x1E55, 0x1E55, Category::LowercaseLetter },	// LATIN SMALL LETTER P WITH ACUTE
		{ 0x1E56, 0x1E56, Category::UppercaseLetter },	// LATIN CAPITAL LETTER P WITH DOT ABOVE
		{ 0x1E57, 0x1E57, Category::LowercaseLetter },	// LATIN SMALL LETTER P WITH DOT ABOVE
		{ 0x1E58, 0x1E58, Category::UppercaseLetter },	// LATIN CAPITAL LETTER R WITH DOT ABOVE
		{ 0x1E59, 0x1E59, Category::LowercaseLetter },	// LATIN SMALL LETTER R WITH DOT ABOVE
		{ 0x1E5A, 0x1E5A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER R WITH DOT BELOW
		{ 0x1E5B, 0x1E5B, Category::LowercaseLetter },	// LATIN SMALL LETTER R WITH DOT BELOW
		{ 0x1E5C, 0x1E5C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER R WITH DOT BELOW AND MACRON
		{ 0x1E5D, 0x1E5D, Category::LowercaseLetter },	// LATIN SMALL LETTER R WITH DOT BELOW AND MACRON
		{ 0x1E5E, 0x1E5E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER R WITH LINE BELOW
		{ 0x1E5F, 0x1E5F, Category::LowercaseLetter },	// LATIN SMALL LETTER R WITH LINE BELOW
		{ 0x1E60, 0x1E60, Category::UppercaseLetter },	// LATIN CAPITAL LETTER S WITH DOT ABOVE
		{ 0x1E61, 0x1E61, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH DOT ABOVE
		{ 0x1E62, 0x1E62, Category::UppercaseLetter },	// LATIN CAPITAL LETTER S WITH DOT BELOW
		{ 0x1E63, 0x1E63, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH DOT BELOW
		{ 0x1E64, 0x1E64, Category::UppercaseLetter },	// LATIN CAPITAL LETTER S WITH ACUTE AND DOT ABOVE
		{ 0x1E65, 0x1E65, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH ACUTE AND DOT ABOVE
		{ 0x1E66, 0x1E66, Category::UppercaseLetter },	// LATIN CAPITAL LETTER S WITH CARON AND DOT ABOVE
		{ 0x1E67, 0x1E67, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH CARON AND DOT ABOVE
		{ 0x1E68, 0x1E68, Category::UppercaseLetter },	// LATIN CAPITAL LETTER S WITH DOT BELOW AND DOT ABOVE
		{ 0x1E69, 0x1E69, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH DOT BELOW AND DOT ABOVE
		{ 0x1E6A, 0x1E6A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER T WITH DOT ABOVE
		{ 0x1E6B, 0x1E6B, Category::LowercaseLetter },	// LATIN SMALL LETTER T WITH DOT ABOVE
		{ 0x1E6C, 0x1E6C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER T WITH DOT BELOW
		{ 0x1E6D, 0x1E6D, Category::LowercaseLetter },	// LATIN SMALL LETTER T WITH DOT BELOW
		{ 0x1E6E, 0x1E6E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER T WITH LINE BELOW
		{ 0x1E6F, 0x1E6F, Category::LowercaseLetter },	// LATIN SMALL LETTER T WITH LINE BELOW
		{ 0x1E70, 0x1E70, Category::UppercaseLetter },	// LATIN CAPITAL LETTER T WITH CIRCUMFLEX BELOW
		{ 0x1E71, 0x1E71, Category::LowercaseLetter },	// LATIN SMALL LETTER T WITH CIRCUMFLEX BELOW
		{ 0x1E72, 0x1E72, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH DIAERESIS BELOW
		{ 0x1E73, 0x1E73, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH DIAERESIS BELOW
		{ 0x1E74, 0x1E74, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH TILDE BELOW
		{ 0x1E75, 0x1E75, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH TILDE BELOW
		{ 0x1E76, 0x1E76, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH CIRCUMFLEX BELOW
		{ 0x1E77, 0x1E77, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH CIRCUMFLEX BELOW
		{ 0x1E78, 0x1E78, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH TILDE AND ACUTE
		{ 0x1E79, 0x1E79, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH TILDE AND ACUTE
		{ 0x1E7A, 0x1E7A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH MACRON AND DIAERESIS
		{ 0x1E7B, 0x1E7B, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH MACRON AND DIAERESIS
		{ 0x1E7C, 0x1E7C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER V WITH TILDE
		{ 0x1E7D, 0x1E7D, Category::LowercaseLetter },	// LATIN SMALL LETTER V WITH TILDE
		{ 0x1E7E, 0x1E7E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER V WITH DOT BELOW
		{ 0x1E7F, 0x1E7F, Category::LowercaseLetter },	// LATIN SMALL LETTER V WITH DOT BELOW
		{ 0x1E80, 0x1E80, Category::UppercaseLetter },	// LATIN CAPITAL LETTER W WITH GRAVE
		{ 0x1E81, 0x1E81, Category::LowercaseLetter },	// LATIN SMALL LETTER W WITH GRAVE
		{ 0x1E82, 0x1E82, Category::UppercaseLetter },	// LATIN CAPITAL LETTER W WITH ACUTE
		{ 0x1E83, 0x1E83, Category::LowercaseLetter },	// LATIN SMALL LETTER W WITH ACUTE
		{ 0x1E84, 0x1E84, Category::UppercaseLetter },	// LATIN CAPITAL LETTER W WITH DIAERESIS
		{ 0x1E85, 0x1E85, Category::LowercaseLetter },	// LATIN SMALL LETTER W WITH DIAERESIS
		{ 0x1E86, 0x1E86, Category::UppercaseLetter },	// LATIN CAPITAL LETTER W WITH DOT ABOVE
		{ 0x1E87, 0x1E87, Category::LowercaseLetter },	// LATIN SMALL LETTER W WITH DOT ABOVE
		{ 0x1E88, 0x1E88, Category::UppercaseLetter },	// LATIN CAPITAL LETTER W WITH DOT BELOW
		{ 0x1E89, 0x1E89, Category::LowercaseLetter },	// LATIN SMALL LETTER W WITH DOT BELOW
		{ 0x1E8A, 0x1E8A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER X WITH DOT ABOVE
		{ 0x1E8B, 0x1E8B, Category::LowercaseLetter },	// LATIN SMALL LETTER X WITH DOT ABOVE
		{ 0x1E8C, 0x1E8C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER X WITH DIAERESIS
		{ 0x1E8D, 0x1E8D, Category::LowercaseLetter },	// LATIN SMALL LETTER X WITH DIAERESIS
		{ 0x1E8E, 0x1E8E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Y WITH DOT ABOVE
		{ 0x1E8F, 0x1E8F, Category::LowercaseLetter },	// LATIN SMALL LETTER Y WITH DOT ABOVE
		{ 0x1E90, 0x1E90, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Z WITH CIRCUMFLEX
		{ 0x1E91, 0x1E91, Category::LowercaseLetter },	// LATIN SMALL LETTER Z WITH CIRCUMFLEX
		{ 0x1E92, 0x1E92, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Z WITH DOT BELOW
		{ 0x1E93, 0x1E93, Category::LowercaseLetter },	// LATIN SMALL LETTER Z WITH DOT BELOW
		{ 0x1E94, 0x1E94, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Z WITH LINE BELOW
		{ 0x1E95, 0x1E9D, Category::LowercaseLetter },	// LATIN SMALL LETTER Z WITH LINE BELOW..LATIN SMALL LETTER LONG S WITH HIGH STROKE
		{ 0x1E9E, 0x1E9E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER SHARP S
		{ 0x1E9F, 0x1E9F, Category::LowercaseLetter },	// LATIN SMALL LETTER DELTA
		{ 0x1EA0, 0x1EA0, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH DOT BELOW
		{ 0x1EA1, 0x1EA1, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH DOT BELOW
		{ 0x1EA2, 0x1EA2, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH HOOK ABOVE
		{ 0x1EA3, 0x1EA3, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH HOOK ABOVE
		{ 0x1EA4, 0x1EA4, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND ACUTE
		{ 0x1EA5, 0x1EA5, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH CIRCUMFLEX AND ACUTE
		{ 0x1EA6, 0x1EA6, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND GRAVE
		{ 0x1EA7, 0x1EA7, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH CIRCUMFLEX AND GRAVE
		{ 0x1EA8, 0x1EA8, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND HOOK ABOVE
		{ 0x1EA9, 0x1EA9, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH CIRCUMFLEX AND HOOK ABOVE
		{ 0x1EAA, 0x1EAA, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND TILDE
		{ 0x1EAB, 0x1EAB, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH CIRCUMFLEX AND TILDE
		{ 0x1EAC, 0x1EAC, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND DOT BELOW
		{ 0x1EAD, 0x1EAD, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH CIRCUMFLEX AND DOT BELOW
		{ 0x1EAE, 0x1EAE, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH BREVE AND ACUTE
		{ 0x1EAF, 0x1EAF, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH BREVE AND ACUTE
		{ 0x1EB0, 0x1EB0, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH BREVE AND GRAVE
		{ 0x1EB1, 0x1EB1, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH BREVE AND GRAVE
		{ 0x1EB2, 0x1EB2, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH BREVE AND HOOK ABOVE
		{ 0x1EB3, 0x1EB3, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH BREVE AND HOOK ABOVE
		{ 0x1EB4, 0x1EB4, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH BREVE AND TILDE
		{ 0x1EB5, 0x1EB5, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH BREVE AND TILDE
		{ 0x1EB6, 0x1EB6, Category::UppercaseLetter },	// LATIN CAPITAL LETTER A WITH BREVE AND DOT BELOW
		{ 0x1EB7, 0x1EB7, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH BREVE AND DOT BELOW
		{ 0x1EB8, 0x1EB8, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH DOT BELOW
		{ 0x1EB9, 0x1EB9, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH DOT BELOW
		{ 0x1EBA, 0x1EBA, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH HOOK ABOVE
		{ 0x1EBB, 0x1EBB, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH HOOK ABOVE
		{ 0x1EBC, 0x1EBC, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH TILDE
		{ 0x1EBD, 0x1EBD, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH TILDE
		{ 0x1EBE, 0x1EBE, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND ACUTE
		{ 0x1EBF, 0x1EBF, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH CIRCUMFLEX AND ACUTE
		{ 0x1EC0, 0x1EC0, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND GRAVE
		{ 0x1EC1, 0x1EC1, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH CIRCUMFLEX AND GRAVE
		{ 0x1EC2, 0x1EC2, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND HOOK ABOVE
		{ 0x1EC3, 0x1EC3, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH CIRCUMFLEX AND HOOK ABOVE
		{ 0x1EC4, 0x1EC4, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND TILDE
		{ 0x1EC5, 0x1EC5, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH CIRCUMFLEX AND TILDE
		{ 0x1EC6, 0x1EC6, Category::UppercaseLetter },	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND DOT BELOW
		{ 0x1EC7, 0x1EC7, Category::LowercaseLetter },	// LATIN SMALL LETTER E WITH CIRCUMFLEX AND DOT BELOW
		{ 0x1EC8, 0x1EC8, Category::UppercaseLetter },	// LATIN CAPITAL LETTER I WITH HOOK ABOVE
		{ 0x1EC9, 0x1EC9, Category::LowercaseLetter },	// LATIN SMALL LETTER I WITH HOOK ABOVE
		{ 0x1ECA, 0x1ECA, Category::UppercaseLetter },	// LATIN CAPITAL LETTER I WITH DOT BELOW
		{ 0x1ECB, 0x1ECB, Category::LowercaseLetter },	// LATIN SMALL LETTER I WITH DOT BELOW
		{ 0x1ECC, 0x1ECC, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH DOT BELOW
		{ 0x1ECD, 0x1ECD, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH DOT BELOW
		{ 0x1ECE, 0x1ECE, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH HOOK ABOVE
		{ 0x1ECF, 0x1ECF, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH HOOK ABOVE
		{ 0x1ED0, 0x1ED0, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND ACUTE
		{ 0x1ED1, 0x1ED1, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH CIRCUMFLEX AND ACUTE
		{ 0x1ED2, 0x1ED2, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND GRAVE
		{ 0x1ED3, 0x1ED3, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH CIRCUMFLEX AND GRAVE
		{ 0x1ED4, 0x1ED4, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE
		{ 0x1ED5, 0x1ED5, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE
		{ 0x1ED6, 0x1ED6, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND TILDE
		{ 0x1ED7, 0x1ED7, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH CIRCUMFLEX AND TILDE
		{ 0x1ED8, 0x1ED8, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND DOT BELOW
		{ 0x1ED9, 0x1ED9, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH CIRCUMFLEX AND DOT BELOW
		{ 0x1EDA, 0x1EDA, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH HORN AND ACUTE
		{ 0x1EDB, 0x1EDB, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH HORN AND ACUTE
		{ 0x1EDC, 0x1EDC, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH HORN AND GRAVE
		{ 0x1EDD, 0x1EDD, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH HORN AND GRAVE
		{ 0x1EDE, 0x1EDE, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH HORN AND HOOK ABOVE
		{ 0x1EDF, 0x1EDF, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH HORN AND HOOK ABOVE
		{ 0x1EE0, 0x1EE0, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH HORN AND TILDE
		{ 0x1EE1, 0x1EE1, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH HORN AND TILDE
		{ 0x1EE2, 0x1EE2, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH HORN AND DOT BELOW
		{ 0x1EE3, 0x1EE3, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH HORN AND DOT BELOW
		{ 0x1EE4, 0x1EE4, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH DOT BELOW
		{ 0x1EE5, 0x1EE5, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH DOT BELOW
		{ 0x1EE6, 0x1EE6, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH HOOK ABOVE
		{ 0x1EE7, 0x1EE7, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH HOOK ABOVE
		{ 0x1EE8, 0x1EE8, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH HORN AND ACUTE
		{ 0x1EE9, 0x1EE9, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH HORN AND ACUTE
		{ 0x1EEA, 0x1EEA, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH HORN AND GRAVE
		{ 0x1EEB, 0x1EEB, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH HORN AND GRAVE
		{ 0x1EEC, 0x1EEC, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH HORN AND HOOK ABOVE
		{ 0x1EED, 0x1EED, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH HORN AND HOOK ABOVE
		{ 0x1EEE, 0x1EEE, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH HORN AND TILDE
		{ 0x1EEF, 0x1EEF, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH HORN AND TILDE
		{ 0x1EF0, 0x1EF0, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH HORN AND DOT BELOW
		{ 0x1EF1, 0x1EF1, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH HORN AND DOT BELOW
		{ 0x1EF2, 0x1EF2, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Y WITH GRAVE
		{ 0x1EF3, 0x1EF3, Category::LowercaseLetter },	// LATIN SMALL LETTER Y WITH GRAVE
		{ 0x1EF4, 0x1EF4, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Y WITH DOT BELOW
		{ 0x1EF5, 0x1EF5, Category::LowercaseLetter },	// LATIN SMALL LETTER Y WITH DOT BELOW
		{ 0x1EF6, 0x1EF6, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Y WITH HOOK ABOVE
		{ 0x1EF7, 0x1EF7, Category::LowercaseLetter },	// LATIN SMALL LETTER Y WITH HOOK ABOVE
		{ 0x1EF8, 0x1EF8, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Y WITH TILDE
		{ 0x1EF9, 0x1EF9, Category::LowercaseLetter },	// LATIN SMALL LETTER Y WITH TILDE
		{ 0x1EFA, 0x1EFA, Category::UppercaseLetter },	// LATIN CAPITAL LETTER MIDDLE-WELSH LL
		{ 0x1EFB, 0x1EFB, Category::LowercaseLetter },	// LATIN SMALL LETTER MIDDLE-WELSH LL
		{ 0x1EFC, 0x1EFC, Category::UppercaseLetter },	// LATIN CAPITAL LETTER MIDDLE-WELSH V
		{ 0x1EFD, 0x1EFD, Category::LowercaseLetter },	// LATIN SMALL LETTER MIDDLE-WELSH V
		{ 0x1EFE, 0x1EFE, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Y WITH LOOP
		{ 0x1EFF, 0x1F07, Category::LowercaseLetter },	// LATIN SMALL LETTER Y WITH LOOP..GREEK SMALL LETTER ALPHA WITH DASIA AND PERISPOMENI
		{ 0x1F08, 0x1F0F, Category::UppercaseLetter },	// GREEK CAPITAL LETTER ALPHA WITH PSILI..GREEK CAPITAL LETTER ALPHA WITH DASIA AND PERISPOMENI
		{ 0x1F10, 0x1F15, Category::LowercaseLetter },	// GREEK SMALL LETTER EPSILON WITH PSILI..GREEK SMALL LETTER EPSILON WITH DASIA AND OXIA
		{ 0x1F16, 0x1F17, Category::Unassigned },	// <reserved-1F16>..<reserved-1F17>
		{ 0x1F18, 0x1F1D, Category::UppercaseLetter },	// GREEK CAPITAL LETTER EPSILON WITH PSILI..GREEK CAPITAL LETTER EPSILON WITH DASIA AND OXIA
		{ 0x1F1E, 0x1F1F, Category::Unassigned },	// <reserved-1F1E>..<reserved-1F1F>
		{ 0x1F20, 0x1F27, Category::LowercaseLetter },	// GREEK SMALL LETTER ETA WITH PSILI..GREEK SMALL LETTER ETA WITH DASIA AND PERISPOMENI
		{ 0x1F28, 0x1F2F, Category::UppercaseLetter },	// GREEK CAPITAL LETTER ETA WITH PSILI..GREEK CAPITAL LETTER ETA WITH DASIA AND PERISPOMENI
		{ 0x1F30, 0x1F37, Category::LowercaseLetter },	// GREEK SMALL LETTER IOTA WITH PSILI..GREEK SMALL LETTER IOTA WITH DASIA AND PERISPOMENI
		{ 0x1F38, 0x1F3F, Category::UppercaseLetter },	// GREEK CAPITAL LETTER IOTA WITH PSILI..GREEK CAPITAL LETTER IOTA WITH DASIA AND PERISPOMENI
		{ 0x1F40, 0x1F45, Category::LowercaseLetter },	// GREEK SMALL LETTER OMICRON WITH PSILI..GREEK SMALL LETTER OMICRON WITH DASIA AND OXIA
		{ 0x1F46, 0x1F47, Category::Unassigned },	// <reserved-1F46>..<reserved-1F47>
		{ 0x1F48, 0x1F4D, Category::UppercaseLetter },	// GREEK CAPITAL LETTER OMICRON WITH PSILI..GREEK CAPITAL LETTER OMICRON WITH DASIA AND OXIA
		{ 0x1F4E, 0x1F4F, Category::Unassigned },	// <reserved-1F4E>..<reserved-1F4F>
		{ 0x1F50, 0x1F57, Category::LowercaseLetter },	// GREEK SMALL LETTER UPSILON WITH PSILI..GREEK SMALL LETTER UPSILON WITH DASIA AND PERISPOMENI
		{ 0x1F58, 0x1F58, Category::Unassigned },	// <reserved-1F58>
		{ 0x1F59, 0x1F59, Category::UppercaseLetter },	// GREEK CAPITAL LETTER UPSILON WITH DASIA
		{ 0x1F5A, 0x1F5A, Category::Unassigned },	// <reserved-1F5A>
		{ 0x1F5B, 0x1F5B, Category::UppercaseLetter },	// GREEK CAPITAL LETTER UPSILON WITH DASIA AND VARIA
		{ 0x1F5C, 0x1F5C, Category::Unassigned },	// <reserved-1F5C>
		{ 0x1F5D, 0x1F5D, Category::UppercaseLetter },	// GREEK CAPITAL LETTER UPSILON WITH DASIA AND OXIA
		{ 0x1F5E, 0x1F5E, Category::Unassigned },	// <reserved-1F5E>
		{ 0x1F5F, 0x1F5F, Category::UppercaseLetter },	// GREEK CAPITAL LETTER UPSILON WITH DASIA AND PERISPOMENI
		{ 0x1F60, 0x1F67, Category::LowercaseLetter },	// GREEK SMALL LETTER OMEGA WITH PSILI..GREEK SMALL LETTER OMEGA WITH DASIA AND PERISPOMENI
		{ 0x1F68, 0x1F6F, Category::UppercaseLetter },	// GREEK CAPITAL LETTER OMEGA WITH PSILI..GREEK CAPITAL LETTER OMEGA WITH DASIA AND PERISPOMENI
		{ 0x1F70, 0x1F7D, Category::LowercaseLetter },	// GREEK SMALL LETTER ALPHA WITH VARIA..GREEK SMALL LETTER OMEGA WITH OXIA
		{ 0x1F7E, 0x1F7F, Category::Unassigned },	// <reserved-1F7E>..<reserved-1F7F>
		{ 0x1F80, 0x1F87, Category::LowercaseLetter },	// GREEK SMALL LETTER ALPHA WITH PSILI AND YPOGEGRAMMENI..GREEK SMALL LETTER ALPHA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
		{ 0x1F88, 0x1F8F, Category::TitlecaseLetter },	// GREEK CAPITAL LETTER ALPHA WITH PSILI AND PROSGEGRAMMENI..GREEK CAPITAL LETTER ALPHA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
		{ 0x1F90, 0x1F97, Category::LowercaseLetter },	// GREEK SMALL LETTER ETA WITH PSILI AND YPOGEGRAMMENI..GREEK SMALL LETTER ETA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
		{ 0x1F98, 0x1F9F, Category::TitlecaseLetter },	// GREEK CAPITAL LETTER ETA WITH PSILI AND PROSGEGRAMMENI..GREEK CAPITAL LETTER ETA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
		{ 0x1FA0, 0x1FA7, Category::LowercaseLetter },	// GREEK SMALL LETTER OMEGA WITH PSILI AND YPOGEGRAMMENI..GREEK SMALL LETTER OMEGA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
		{ 0x1FA8, 0x1FAF, Category::TitlecaseLetter },	// GREEK CAPITAL LETTER OMEGA WITH PSILI AND PROSGEGRAMMENI..GREEK CAPITAL LETTER OMEGA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
		{ 0x1FB0, 0x1FB4, Category::LowercaseLetter },	// GREEK SMALL LETTER ALPHA WITH VRACHY..GREEK SMALL LETTER ALPHA WITH OXIA AND YPOGEGRAMMENI
		{ 0x1FB5, 0x1FB5, Category::Unassigned },	// <reserved-1FB5>
		{ 0x1FB6, 0x1FB7, Category::LowercaseLetter },	// GREEK SMALL LETTER ALPHA WITH PERISPOMENI..GREEK SMALL LETTER ALPHA WITH PERISPOMENI AND YPOGEGRAMMENI
		{ 0x1FB8, 0x1FBB, Category::UppercaseLetter },	// GREEK CAPITAL LETTER ALPHA WITH VRACHY..GREEK CAPITAL LETTER ALPHA WITH OXIA
		{ 0x1FBC, 0x1FBC, Category::TitlecaseLetter },	// GREEK CAPITAL LETTER ALPHA WITH PROSGEGRAMMENI
		{ 0x1FBD, 0x1FBD, Category::ModifierSymbol },	// GREEK KORONIS
		{ 0x1FBE, 0x1FBE, Category::LowercaseLetter },	// GREEK PROSGEGRAMMENI
		{ 0x1FBF, 0x1FC1, Category::ModifierSymbol },	// GREEK PSILI..GREEK DIALYTIKA AND PERISPOMENI
		{ 0x1FC2, 0x1FC4, Category::LowercaseLetter },	// GREEK SMALL LETTER ETA WITH VARIA AND YPOGEGRAMMENI..GREEK SMALL LETTER ETA WITH OXIA AND YPOGEGRAMMENI
		{ 0x1FC5, 0x1FC5, Category::Unassigned },	// <reserved-1FC5>
		{ 0x1FC6, 0x1FC7, Category::LowercaseLetter },	// GREEK SMALL LETTER ETA WITH PERISPOMENI..GREEK SMALL LETTER ETA WITH PERISPOMENI AND YPOGEGRAMMENI
		{ 0x1FC8, 0x1FCB, Category::UppercaseLetter },	// GREEK CAPITAL LETTER EPSILON WITH VARIA..GREEK CAPITAL LETTER ETA WITH OXIA
		{ 0x1FCC, 0x1FCC, Category::TitlecaseLetter },	// GREEK CAPITAL LETTER ETA WITH PROSGEGRAMMENI
		{ 0x1FCD, 0x1FCF, Category::ModifierSymbol },	// GREEK PSILI AND VARIA..GREEK PSILI AND PERISPOMENI
		{ 0x1FD0, 0x1FD3, Category::LowercaseLetter },	// GREEK SMALL LETTER IOTA WITH VRACHY..GREEK SMALL LETTER IOTA WITH DIALYTIKA AND OXIA
		{ 0x1FD4, 0x1FD5, Category::Unassigned },	// <reserved-1FD4>..<reserved-1FD5>
		{ 0x1FD6, 0x1FD7, Category::LowercaseLetter },	// GREEK SMALL LETTER IOTA WITH PERISPOMENI..GREEK SMALL LETTER IOTA WITH DIALYTIKA AND PERISPOMENI
		{ 0x1FD8, 0x1FDB, Category::UppercaseLetter },	// GREEK CAPITAL LETTER IOTA WITH VRACHY..GREEK CAPITAL LETTER IOTA WITH OXIA
		{ 0x1FDC, 0x1FDC, Category::Unassigned },	// <reserved-1FDC>
		{ 0x1FDD, 0x1FDF, Category::ModifierSymbol },	// GREEK DASIA AND VARIA..GREEK DASIA AND PERISPOMENI
		{ 0x1FE0, 0x1FE7, Category::LowercaseLetter },	// GREEK SMALL LETTER UPSILON WITH VRACHY..GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND PERISPOMENI
		{ 0x1FE8, 0x1FEC, Category::UppercaseLetter },	// GREEK CAPITAL LETTER UPSILON WITH VRACHY..GREEK CAPITAL LETTER RHO WITH DASIA
		{ 0x1FED, 0x1FEF, Category::ModifierSymbol },	// GREEK DIALYTIKA AND VARIA..GREEK VARIA
		{ 0x1FF0, 0x1FF1, Category::Unassigned },	// <reserved-1FF0>..<reserved-1FF1>
		{ 0x1FF2, 0x1FF4, Category::LowercaseLetter },	// GREEK SMALL LETTER OMEGA WITH VARIA AND YPOGEGRAMMENI..GREEK SMALL LETTER OMEGA WITH OXIA AND YPOGEGRAMMENI
		{ 0x1FF5, 0x1FF5, Category::Unassigned },	// <reserved-1FF5>
		{ 0x1FF6, 0x1FF7, Category::LowercaseLetter },	// GREEK SMALL LETTER OMEGA WITH PERISPOMENI..GREEK SMALL LETTER OMEGA WITH PERISPOMENI AND YPOGEGRAMMENI
		{ 0x1FF8, 0x1FFB, Category::UppercaseLetter },	// GREEK CAPITAL LETTER OMICRON WITH VARIA..GREEK CAPITAL LETTER OMEGA WITH OXIA
		{ 0x1FFC, 0x1FFC, Category::TitlecaseLetter },	// GREEK CAPITAL LETTER OMEGA WITH PROSGEGRAMMENI
		{ 0x1FFD, 0x1FFE, Category::ModifierSymbol },	// GREEK OXIA..GREEK DASIA
		{ 0x1FFF, 0x1FFF, Category::Unassigned },	// <reserved-1FFF>
		{ 0x2000, 0x200A, Category::SpaceSeparator },	// EN QUAD..HAIR SPACE
		{ 0x200B, 0x200F, Category::Format },	// ZERO WIDTH SPACE..RIGHT-TO-LEFT MARK
		{ 0x2010, 0x2015, Category::DashPunctuation },	// HYPHEN..HORIZONTAL BAR
		{ 0x2016, 0x2017, Category::OtherPunctuation },	// DOUBLE VERTICAL LINE..DOUBLE LOW LINE
		{ 0x2018, 0x2018, Category::InitialPunctuation },	// LEFT SINGLE QUOTATION MARK
		{ 0x2019, 0x2019, Category::FinalPunctuation },	// RIGHT SINGLE QUOTATION MARK
		{ 0x201A, 0x201A, Category::OpenPunctuation },	// SINGLE LOW-9 QUOTATION MARK
		{ 0x201B, 0x201C, Category::InitialPunctuation },	// SINGLE HIGH-REVERSED-9 QUOTATION MARK..LEFT DOUBLE QUOTATION MARK
		{ 0x201D, 0x201D, Category::FinalPunctuation },	// RIGHT DOUBLE QUOTATION MARK
		{ 0x201E, 0x201E, Category::OpenPunctuation },	// DOUBLE LOW-9 QUOTATION MARK
		{ 0x201F, 0x201F, Category::InitialPunctuation },	// DOUBLE HIGH-REVERSED-9 QUOTATION MARK
		{ 0x2020, 0x2027, Category::OtherPunctuation },	// DAGGER..HYPHENATION POINT
		{ 0x2028, 0x2028, Category::LineSeparator },	// LINE SEPARATOR
		{ 0x2029, 0x2029, Category::ParagraphSeparator },	// PARAGRAPH SEPARATOR
		{ 0x202A, 0x202E, Category::Format },	// LEFT-TO-RIGHT EMBEDDING..RIGHT-TO-LEFT OVERRIDE
		{ 0x202F, 0x202F, Category::SpaceSeparator },	// NARROW NO-BREAK SPACE
		{ 0x2030, 0x2038, Category::OtherPunctuation },	// PER MILLE SIGN..CARET
		{ 0x2039, 0x2039, Category::InitialPunctuation },	// SINGLE LEFT-POINTING ANGLE QUOTATION MARK
		{ 0x203A, 0x203A, Category::FinalPunctuation },	// SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
		{ 0x203B, 0x203E, Category::OtherPunctuation },	// REFERENCE MARK..OVERLINE
		{ 0x203F, 0x2040, Category::ConnectorPunctuation },	// UNDERTIE..CHARACTER TIE
		{ 0x2041, 0x2043, Category::OtherPunctuation },	// CARET INSERTION POINT..HYPHEN BULLET
		{ 0x2044, 0x2044, Category::MathSymbol },	// FRACTION SLASH
		{ 0x2045, 0x2045, Category::OpenPunctuation },	// LEFT SQUARE BRACKET WITH QUILL
		{ 0x2046, 0x2046, Category::ClosePunctuation },	// RIGHT SQUARE BRACKET WITH QUILL
		{ 0x2047, 0x2051, Category::OtherPunctuation },	// DOUBLE QUESTION MARK..TWO ASTERISKS ALIGNED VERTICALLY
		{ 0x2052, 0x2052, Category::MathSymbol },	// COMMERCIAL MINUS SIGN
		{ 0x2053, 0x2053, Category::OtherPunctuation },	// SWUNG DASH
		{ 0x2054, 0x2054, Category::ConnectorPunctuation },	// INVERTED UNDERTIE
		{ 0x2055, 0x205E, Category::OtherPunctuation },	// FLOWER PUNCTUATION MARK..VERTICAL FOUR DOTS
		{ 0x205F, 0x205F, Category::SpaceSeparator },	// MEDIUM MATHEMATICAL SPACE
		{ 0x2060, 0x2064, Category::Format },	// WORD JOINER..INVISIBLE PLUS
		{ 0x2065, 0x2065, Category::Unassigned },	// <reserved-2065>
		{ 0x2066, 0x206F, Category::Format },	// LEFT-TO-RIGHT ISOLATE..NOMINAL DIGIT SHAPES
		{ 0x2070, 0x2070, Category::OtherNumber },	// SUPERSCRIPT ZERO
		{ 0x2071, 0x2071, Category::ModifierLetter },	// SUPERSCRIPT LATIN SMALL LETTER I
		{ 0x2072, 0x2073, Category::Unassigned },	// <reserved-2072>..<reserved-2073>
		{ 0x2074, 0x2079, Category::OtherNumber },	// SUPERSCRIPT FOUR..SUPERSCRIPT NINE
		{ 0x207A, 0x207C, Category::MathSymbol },	// SUPERSCRIPT PLUS SIGN..SUPERSCRIPT EQUALS SIGN
		{ 0x207D, 0x207D, Category::OpenPunctuation },	// SUPERSCRIPT LEFT PARENTHESIS
		{ 0x207E, 0x207E, Category::ClosePunctuation },	// SUPERSCRIPT RIGHT PARENTHESIS
		{ 0x207F, 0x207F, Category::ModifierLetter },	// SUPERSCRIPT LATIN SMALL LETTER N
		{ 0x2080, 0x2089, Category::OtherNumber },	// SUBSCRIPT ZERO..SUBSCRIPT NINE
		{ 0x208A, 0x208C, Category::MathSymbol },	// SUBSCRIPT PLUS SIGN..SUBSCRIPT EQUALS SIGN
		{ 0x208D, 0x208D, Category::OpenPunctuation },	// SUBSCRIPT LEFT PARENTHESIS
		{ 0x208E, 0x208E, Category::ClosePunctuation },	// SUBSCRIPT RIGHT PARENTHESIS
		{ 0x208F, 0x208F, Category::Unassigned },	// <reserved-208F>
		{ 0x2090, 0x209C, Category::ModifierLetter },	// LATIN SUBSCRIPT SMALL LETTER A..LATIN SUBSCRIPT SMALL LETTER T
		{ 0x209D, 0x209F, Category::Unassigned },	// <reserved-209D>..<reserved-209F>
		{ 0x20A0, 0x20C0, Category::CurrencySymbol },	// EURO-CURRENCY SIGN..SOM SIGN
		{ 0x20C1, 0x20CF, Category::Unassigned },	// <reserved-20C1>..<reserved-20CF>
		{ 0x20D0, 0x20DC, Category::NonspacingMark },	// COMBINING LEFT HARPOON ABOVE..COMBINING FOUR DOTS ABOVE
		{ 0x20DD, 0x20E0, Category::EnclosingMark },	// COMBINING ENCLOSING CIRCLE..COMBINING ENCLOSING CIRCLE BACKSLASH
		{ 0x20E1, 0x20E1, Category::NonspacingMark },	// COMBINING LEFT RIGHT ARROW ABOVE
		{ 0x20E2, 0x20E4, Category::EnclosingMark },	// COMBINING ENCLOSING SCREEN..COMBINING ENCLOSING UPWARD POINTING TRIANGLE
		{ 0x20E5, 0x20F0, Category::NonspacingMark },	// COMBINING REVERSE SOLIDUS OVERLAY..COMBINING ASTERISK ABOVE
		{ 0x20F1, 0x20FF, Category::Unassigned },	// <reserved-20F1>..<reserved-20FF>
		{ 0x2100, 0x2101, Category::OtherSymbol },	// ACCOUNT OF..ADDRESSED TO THE SUBJECT
		{ 0x2102, 0x2102, Category::UppercaseLetter },	// DOUBLE-STRUCK CAPITAL C
		{ 0x2103, 0x2106, Category::OtherSymbol },	// DEGREE CELSIUS..CADA UNA
		{ 0x2107, 0x2107, Category::UppercaseLetter },	// EULER CONSTANT
		{ 0x2108, 0x2109, Category::OtherSymbol },	// SCRUPLE..DEGREE FAHRENHEIT
		{ 0x210A, 0x210A, Category::LowercaseLetter },	// SCRIPT SMALL G
		{ 0x210B, 0x210D, Category::UppercaseLetter },	// SCRIPT CAPITAL H..DOUBLE-STRUCK CAPITAL H
		{ 0x210E, 0x210F, Category::LowercaseLetter },	// PLANCK CONSTANT..PLANCK CONSTANT OVER TWO PI
		{ 0x2110, 0x2112, Category::UppercaseLetter },	// SCRIPT CAPITAL I..SCRIPT CAPITAL L
		{ 0x2113, 0x2113, Category::LowercaseLetter },	// SCRIPT SMALL L
		{ 0x2114, 0x2114, Category::OtherSymbol },	// L B BAR SYMBOL
		{ 0x2115, 0x2115, Category::UppercaseLetter },	// DOUBLE-STRUCK CAPITAL N
		{ 0x2116, 0x2117, Category::OtherSymbol },	// NUMERO SIGN..SOUND RECORDING COPYRIGHT
		{ 0x2118, 0x2118, Category::MathSymbol },	// SCRIPT CAPITAL P
		{ 0x2119, 0x211D, Category::UppercaseLetter },	// DOUBLE-STRUCK CAPITAL P..DOUBLE-STRUCK CAPITAL R
		{ 0x211E, 0x2123, Category::OtherSymbol },	// PRESCRIPTION TAKE..VERSICLE
		{ 0x2124, 0x2124, Category::UppercaseLetter },	// DOUBLE-STRUCK CAPITAL Z
		{ 0x2125, 0x2125, Category::OtherSymbol },	// OUNCE SIGN
		{ 0x2126, 0x2126, Category::UppercaseLetter },	// OHM SIGN
		{ 0x2127, 0x2127, Category::OtherSymbol },	// INVERTED OHM SIGN
		{ 0x2128, 0x2128, Category::UppercaseLetter },	// BLACK-LETTER CAPITAL Z
		{ 0x2129, 0x2129, Category::OtherSymbol },	// TURNED GREEK SMALL LETTER IOTA
		{ 0x212A, 0x212D, Category::UppercaseLetter },	// KELVIN SIGN..BLACK-LETTER CAPITAL C
		{ 0x212E, 0x212E, Category::OtherSymbol },	// ESTIMATED SYMBOL
		{ 0x212F, 0x212F, Category::LowercaseLetter },	// SCRIPT SMALL E
		{ 0x2130, 0x2133, Category::UppercaseLetter },	// SCRIPT CAPITAL E..SCRIPT CAPITAL M
		{ 0x2134, 0x2134, Category::LowercaseLetter },	// SCRIPT SMALL O
		{ 0x2135, 0x2138, Category::OtherLetter },	// ALEF SYMBOL..DALET SYMBOL
		{ 0x2139, 0x2139, Category::LowercaseLetter },	// INFORMATION SOURCE
		{ 0x213A, 0x213B, Category::OtherSymbol },	// ROTATED CAPITAL Q..FACSIMILE SIGN
		{ 0x213C, 0x213D, Category::LowercaseLetter },	// DOUBLE-STRUCK SMALL PI..DOUBLE-STRUCK SMALL GAMMA
		{ 0x213E, 0x213F, Category::UppercaseLetter },	// DOUBLE-STRUCK CAPITAL GAMMA..DOUBLE-STRUCK CAPITAL PI
		{ 0x2140, 0x2144, Category::MathSymbol },	// DOUBLE-STRUCK N-ARY SUMMATION..TURNED SANS-SERIF CAPITAL Y
		{ 0x2145, 0x2145, Category::UppercaseLetter },	// DOUBLE-STRUCK ITALIC CAPITAL D
		{ 0x2146, 0x2149, Category::LowercaseLetter },	// DOUBLE-STRUCK ITALIC SMALL D..DOUBLE-STRUCK ITALIC SMALL J
		{ 0x214A, 0x214A, Category::OtherSymbol },	// PROPERTY LINE
		{ 0x214B, 0x214B, Category::MathSymbol },	// TURNED AMPERSAND
		{ 0x214C, 0x214D, Category::OtherSymbol },	// PER SIGN..AKTIESELSKAB
		{ 0x214E, 0x214E, Category::LowercaseLetter },	// TURNED SMALL F
		{ 0x214F, 0x214F, Category::OtherSymbol },	// SYMBOL FOR SAMARITAN SOURCE
		{ 0x2150, 0x215F, Category::OtherNumber },	// VULGAR FRACTION ONE SEVENTH..FRACTION NUMERATOR ONE
		{ 0x2160, 0x2182, Category::LetterNumber },	// ROMAN NUMERAL ONE..ROMAN NUMERAL TEN THOUSAND
		{ 0x2183, 0x2183, Category::UppercaseLetter },	// ROMAN NUMERAL REVERSED ONE HUNDRED
		{ 0x2184, 0x2184, Category::LowercaseLetter },	// LATIN SMALL LETTER REVERSED C
		{ 0x2185, 0x2188, Category::LetterNumber },	// ROMAN NUMERAL SIX LATE FORM..ROMAN NUMERAL ONE HUNDRED THOUSAND
		{ 0x2189, 0x2189, Category::OtherNumber },	// VULGAR FRACTION ZERO THIRDS
		{ 0x218A, 0x218B, Category::OtherSymbol },	// TURNED DIGIT TWO..TURNED DIGIT THREE
		{ 0x218C, 0x218F, Category::Unassigned },	// <reserved-218C>..<reserved-218F>
		{ 0x2190, 0x2194, Category::MathSymbol },	// LEFTWARDS ARROW..LEFT RIGHT ARROW
		{ 0x2195, 0x2199, Category::OtherSymbol },	// UP DOWN ARROW..SOUTH WEST ARROW
		{ 0x219A, 0x219B, Category::MathSymbol },	// LEFTWARDS ARROW WITH STROKE..RIGHTWARDS ARROW WITH STROKE
		{ 0x219C, 0x219F, Category::OtherSymbol },	// LEFTWARDS WAVE ARROW..UPWARDS TWO HEADED ARROW
		{ 0x21A0, 0x21A0, Category::MathSymbol },	// RIGHTWARDS TWO HEADED ARROW
		{ 0x21A1, 0x21A2, Category::OtherSymbol },	// DOWNWARDS TWO HEADED ARROW..LEFTWARDS ARROW WITH TAIL
		{ 0x21A3, 0x21A3, Category::MathSymbol },	// RIGHTWARDS ARROW WITH TAIL
		{ 0x21A4, 0x21A5, Category::OtherSymbol },	// LEFTWARDS ARROW FROM BAR..UPWARDS ARROW FROM BAR
		{ 0x21A6, 0x21A6, Category::MathSymbol },	// RIGHTWARDS ARROW FROM BAR
		{ 0x21A7, 0x21AD, Category::OtherSymbol },	// DOWNWARDS ARROW FROM BAR..LEFT RIGHT WAVE ARROW
		{ 0x21AE, 0x21AE, Category::MathSymbol },	// LEFT RIGHT ARROW WITH STROKE
		{ 0x21AF, 0x21CD, Category::OtherSymbol },	// DOWNWARDS ZIGZAG ARROW..LEFTWARDS DOUBLE ARROW WITH STROKE
		{ 0x21CE, 0x21CF, Category::MathSymbol },	// LEFT RIGHT DOUBLE ARROW WITH STROKE..RIGHTWARDS DOUBLE ARROW WITH STROKE
		{ 0x21D0, 0x21D1, Category::OtherSymbol },	// LEFTWARDS DOUBLE ARROW..UPWARDS DOUBLE ARROW
		{ 0x21D2, 0x21D2, Category::MathSymbol },	// RIGHTWARDS DOUBLE ARROW
		{ 0x21D3, 0x21D3, Category::OtherSymbol },	// DOWNWARDS DOUBLE ARROW
		{ 0x21D4, 0x21D4, Category::MathSymbol },	// LEFT RIGHT DOUBLE ARROW
		{ 0x21D5, 0x21F3, Category::OtherSymbol },	// UP DOWN DOUBLE ARROW..UP DOWN WHITE ARROW
		{ 0x21F4, 0x22FF, Category::MathSymbol },	// RIGHT ARROW WITH SMALL CIRCLE..Z NOTATION BAG MEMBERSHIP
		{ 0x2300, 0x2307, Category::OtherSymbol },	// DIAMETER SIGN..WAVY LINE
		{ 0x2308, 0x2308, Category::OpenPunctuation },	// LEFT CEILING
		{ 0x2309, 0x2309, Category::ClosePunctuation },	// RIGHT CEILING
		{ 0x230A, 0x230A, Category::OpenPunctuation },	// LEFT FLOOR
		{ 0x230B, 0x230B, Category::ClosePunctuation },	// RIGHT FLOOR
		{ 0x230C, 0x231F, Category::OtherSymbol },	// BOTTOM RIGHT CROP..BOTTOM RIGHT CORNER
		{ 0x2320, 0x2321, Category::MathSymbol },	// TOP HALF INTEGRAL..BOTTOM HALF INTEGRAL
		{ 0x2322, 0x2328, Category::OtherSymbol },	// FROWN..KEYBOARD
		{ 0x2329, 0x2329, Category::OpenPunctuation },	// LEFT-POINTING ANGLE BRACKET
		{ 0x232A, 0x232A, Category::ClosePunctuation },	// RIGHT-POINTING ANGLE BRACKET
		{ 0x232B, 0x237B, Category::OtherSymbol },	// ERASE TO THE LEFT..NOT CHECK MARK
		{ 0x237C, 0x237C, Category::MathSymbol },	// RIGHT ANGLE WITH DOWNWARDS ZIGZAG ARROW
		{ 0x237D, 0x239A, Category::OtherSymbol },	// SHOULDERED OPEN BOX..CLEAR SCREEN SYMBOL
		{ 0x239B, 0x23B3, Category::MathSymbol },	// LEFT PARENTHESIS UPPER HOOK..SUMMATION BOTTOM
		{ 0x23B4, 0x23DB, Category::OtherSymbol },	// TOP SQUARE BRACKET..FUSE
		{ 0x23DC, 0x23E1, Category::MathSymbol },	// TOP PARENTHESIS..BOTTOM TORTOISE SHELL BRACKET
		{ 0x23E2, 0x2429, Category::OtherSymbol },	// WHITE TRAPEZIUM..SYMBOL FOR DELETE MEDIUM SHADE FORM
		{ 0x242A, 0x243F, Category::Unassigned },	// <reserved-242A>..<reserved-243F>
		{ 0x2440, 0x244A, Category::OtherSymbol },	// OCR HOOK..OCR DOUBLE BACKSLASH
		{ 0x244B, 0x245F, Category::Unassigned },	// <reserved-244B>..<reserved-245F>
		{ 0x2460, 0x249B, Category::OtherNumber },	// CIRCLED DIGIT ONE..NUMBER TWENTY FULL STOP
		{ 0x249C, 0x24E9, Category::OtherSymbol },	// PARENTHESIZED LATIN SMALL LETTER A..CIRCLED LATIN SMALL LETTER Z
		{ 0x24EA, 0x24FF, Category::OtherNumber },	// CIRCLED DIGIT ZERO..NEGATIVE CIRCLED DIGIT ZERO
		{ 0x2500, 0x25B6, Category::OtherSymbol },	// BOX DRAWINGS LIGHT HORIZONTAL..BLACK RIGHT-POINTING TRIANGLE
		{ 0x25B7, 0x25B7, Category::MathSymbol },	// WHITE RIGHT-POINTING TRIANGLE
		{ 0x25B8, 0x25C0, Category::OtherSymbol },	// BLACK RIGHT-POINTING SMALL TRIANGLE..BLACK LEFT-POINTING TRIANGLE
		{ 0x25C1, 0x25C1, Category::MathSymbol },	// WHITE LEFT-POINTING TRIANGLE
		{ 0x25C2, 0x25F7, Category::OtherSymbol },	// BLACK LEFT-POINTING SMALL TRIANGLE..WHITE CIRCLE WITH UPPER RIGHT QUADRANT
		{ 0x25F8, 0x25FF, Category::MathSymbol },	// UPPER LEFT TRIANGLE..LOWER RIGHT TRIANGLE
		{ 0x2600, 0x266E, Category::OtherSymbol },	// BLACK SUN WITH RAYS..MUSIC NATURAL SIGN
		{ 0x266F, 0x266F, Category::MathSymbol },	// MUSIC SHARP SIGN
		{ 0x2670, 0x2767, Category::OtherSymbol },	// WEST SYRIAC CROSS..ROTATED FLORAL HEART BULLET
		{ 0x2768, 0x2768, Category::OpenPunctuation },	// MEDIUM LEFT PARENTHESIS ORNAMENT
		{ 0x2769, 0x2769, Category::ClosePunctuation },	// MEDIUM RIGHT PARENTHESIS ORNAMENT
		{ 0x276A, 0x276A, Category::OpenPunctuation },	// MEDIUM FLATTENED LEFT PARENTHESIS ORNAMENT
		{ 0x276B, 0x276B, Category::ClosePunctuation },	// MEDIUM FLATTENED RIGHT PARENTHESIS ORNAMENT
		{ 0x276C, 0x276C, Category::OpenPunctuation },	// MEDIUM LEFT-POINTING ANGLE BRACKET ORNAMENT
		{ 0x276D, 0x276D, Category::ClosePunctuation },	// MEDIUM RIGHT-POINTING ANGLE BRACKET ORNAMENT
		{ 0x276E, 0x276E, Category::OpenPunctuation },	// HEAVY LEFT-POINTING ANGLE QUOTATION MARK ORNAMENT
		{ 0x276F, 0x276F, Category::ClosePunctuation },	// HEAVY RIGHT-POINTING ANGLE QUOTATION MARK ORNAMENT
		{ 0x2770, 0x2770, Category::OpenPunctuation },	// HEAVY LEFT-POINTING ANGLE BRACKET ORNAMENT
		{ 0x2771, 0x2771, Category::ClosePunctuation },	// HEAVY RIGHT-POINTING ANGLE BRACKET ORNAMENT
		{ 0x2772, 0x2772, Category::OpenPunctuation },	// LIGHT LEFT TORTOISE SHELL BRACKET ORNAMENT
		{ 0x2773, 0x2773, Category::ClosePunctuation },	// LIGHT RIGHT TORTOISE SHELL BRACKET ORNAMENT
		{ 0x2774, 0x2774, Category::OpenPunctuation },	// MEDIUM LEFT CURLY BRACKET ORNAMENT
		{ 0x2775, 0x2775, Category::ClosePunctuation },	// MEDIUM RIGHT CURLY BRACKET ORNAMENT
		{ 0x2776, 0x2793, Category::OtherNumber },	// DINGBAT NEGATIVE CIRCLED DIGIT ONE..DINGBAT NEGATIVE CIRCLED SANS-SERIF NUMBER TEN
		{ 0x2794, 0x27BF, Category::OtherSymbol },	// HEAVY WIDE-HEADED RIGHTWARDS ARROW..DOUBLE CURLY LOOP
		{ 0x27C0, 0x27C4, Category::MathSymbol },	// THREE DIMENSIONAL ANGLE..OPEN SUPERSET
		{ 0x27C5, 0x27C5, Category::OpenPunctuation },	// LEFT S-SHAPED BAG DELIMITER
		{ 0x27C6, 0x27C6, Category::ClosePunctuation },	// RIGHT S-SHAPED BAG DELIMITER
		{ 0x27C7, 0x27E5, Category::MathSymbol },	// OR WITH DOT INSIDE..WHITE SQUARE WITH RIGHTWARDS TICK
		{ 0x27E6, 0x27E6, Category::OpenPunctuation },	// MATHEMATICAL LEFT WHITE SQUARE BRACKET
		{ 0x27E7, 0x27E7, Category::ClosePunctuation },	// MATHEMATICAL RIGHT WHITE SQUARE BRACKET
		{ 0x27E8, 0x27E8, Category::OpenPunctuation },	// MATHEMATICAL LEFT ANGLE BRACKET
		{ 0x27E9, 0x27E9, Category::ClosePunctuation },	// MATHEMATICAL RIGHT ANGLE BRACKET
		{ 0x27EA, 0x27EA, Category::OpenPunctuation },	// MATHEMATICAL LEFT DOUBLE ANGLE BRACKET
		{ 0x27EB, 0x27EB, Category::ClosePunctuation },	// MATHEMATICAL RIGHT DOUBLE ANGLE BRACKET
		{ 0x27EC, 0x27EC, Category::OpenPunctuation },	// MATHEMATICAL LEFT WHITE TORTOISE SHELL BRACKET
		{ 0x27ED, 0x27ED, Category::ClosePunctuation },	// MATHEMATICAL RIGHT WHITE TORTOISE SHELL BRACKET
		{ 0x27EE, 0x27EE, Category::OpenPunctuation },	// MATHEMATICAL LEFT FLATTENED PARENTHESIS
		{ 0x27EF, 0x27EF, Category::ClosePunctuation },	// MATHEMATICAL RIGHT FLATTENED PARENTHESIS
		{ 0x27F0, 0x27FF, Category::MathSymbol },	// UPWARDS QUADRUPLE ARROW..LONG RIGHTWARDS SQUIGGLE ARROW
		{ 0x2800, 0x28FF, Category::OtherSymbol },	// BRAILLE PATTERN BLANK..BRAILLE PATTERN DOTS-12345678
		{ 0x2900, 0x2982, Category::MathSymbol },	// RIGHTWARDS TWO-HEADED ARROW WITH VERTICAL STROKE..Z NOTATION TYPE COLON
		{ 0x2983, 0x2983, Category::OpenPunctuation },	// LEFT WHITE CURLY BRACKET
		{ 0x2984, 0x2984, Category::ClosePunctuation },	// RIGHT WHITE CURLY BRACKET
		{ 0x2985, 0x2985, Category::OpenPunctuation },	// LEFT WHITE PARENTHESIS
		{ 0x2986, 0x2986, Category::ClosePunctuation },	// RIGHT WHITE PARENTHESIS
		{ 0x2987, 0x2987, Category::OpenPunctuation },	// Z NOTATION LEFT IMAGE BRACKET
		{ 0x2988, 0x2988, Category::ClosePunctuation },	// Z NOTATION RIGHT IMAGE BRACKET
		{ 0x2989, 0x2989, Category::OpenPunctuation },	// Z NOTATION LEFT BINDING BRACKET
		{ 0x298A, 0x298A, Category::ClosePunctuation },	// Z NOTATION RIGHT BINDING BRACKET
		{ 0x298B, 0x298B, Category::OpenPunctuation },	// LEFT SQUARE BRACKET WITH UNDERBAR
		{ 0x298C, 0x298C, Category::ClosePunctuation },	// RIGHT SQUARE BRACKET WITH UNDERBAR
		{ 0x298D, 0x298D, Category::OpenPunctuation },	// LEFT SQUARE BRACKET WITH TICK IN TOP CORNER
		{ 0x298E, 0x298E, Category::ClosePunctuation },	// RIGHT SQUARE BRACKET WITH TICK IN BOTTOM CORNER
		{ 0x298F, 0x298F, Category::OpenPunctuation },	// LEFT SQUARE BRACKET WITH TICK IN BOTTOM CORNER
		{ 0x2990, 0x2990, Category::ClosePunctuation },	// RIGHT SQUARE BRACKET WITH TICK IN TOP CORNER
		{ 0x2991, 0x2991, Category::OpenPunctuation },	// LEFT ANGLE BRACKET WITH DOT
		{ 0x2992, 0x2992, Category::ClosePunctuation },	// RIGHT ANGLE BRACKET WITH DOT
		{ 0x2993, 0x2993, Category::OpenPunctuation },	// LEFT ARC LESS-THAN BRACKET
		{ 0x2994, 0x2994, Category::ClosePunctuation },	// RIGHT ARC GREATER-THAN BRACKET
		{ 0x2995, 0x2995, Category::OpenPunctuation },	// DOUBLE LEFT ARC GREATER-THAN BRACKET
		{ 0x2996, 0x2996, Category::ClosePunctuation },	// DOUBLE RIGHT ARC LESS-THAN BRACKET
		{ 0x2997, 0x2997, Category::OpenPunctuation },	// LEFT BLACK TORTOISE SHELL BRACKET
		{ 0x2998, 0x2998, Category::ClosePunctuation },	// RIGHT BLACK TORTOISE SHELL BRACKET
		{ 0x2999, 0x29D7, Category::MathSymbol },	// DOTTED FENCE..BLACK HOURGLASS
		{ 0x29D8, 0x29D8, Category::OpenPunctuation },	// LEFT WIGGLY FENCE
		{ 0x29D9, 0x29D9, Category::ClosePunctuation },	// RIGHT WIGGLY FENCE
		{ 0x29DA, 0x29DA, Category::OpenPunctuation },	// LEFT DOUBLE WIGGLY FENCE
		{ 0x29DB, 0x29DB, Category::ClosePunctuation },	// RIGHT DOUBLE WIGGLY FENCE
		{ 0x29DC, 0x29FB, Category::MathSymbol },	// INCOMPLETE INFINITY..TRIPLE PLUS
		{ 0x29FC, 0x29FC, Category::OpenPunctuation },	// LEFT-POINTING CURVED ANGLE BRACKET
		{ 0x29FD, 0x29FD, Category::ClosePunctuation },	// RIGHT-POINTING CURVED ANGLE BRACKET
		{ 0x29FE, 0x2AFF, Category::MathSymbol },	// TINY..N-ARY WHITE VERTICAL BAR
		{ 0x2B00, 0x2B2F, Category::OtherSymbol },	// NORTH EAST WHITE ARROW..WHITE VERTICAL ELLIPSE
		{ 0x2B30, 0x2B44, Category::MathSymbol },	// LEFT ARROW WITH SMALL CIRCLE..RIGHTWARDS ARROW THROUGH SUPERSET
		{ 0x2B45, 0x2B46, Category::OtherSymbol },	// LEFTWARDS QUADRUPLE ARROW..RIGHTWARDS QUADRUPLE ARROW
		{ 0x2B47, 0x2B4C, Category::MathSymbol },	// REVERSE TILDE OPERATOR ABOVE RIGHTWARDS ARROW..RIGHTWARDS ARROW ABOVE REVERSE TILDE OPERATOR
		{ 0x2B4D, 0x2B73, Category::OtherSymbol },	// DOWNWARDS TRIANGLE-HEADED ZIGZAG ARROW..DOWNWARDS TRIANGLE-HEADED ARROW TO BAR
		{ 0x2B74, 0x2B75, Category::Unassigned },	// <reserved-2B74>..<reserved-2B75>
		{ 0x2B76, 0x2B95, Category::OtherSymbol },	// NORTH WEST TRIANGLE-HEADED ARROW TO BAR..RIGHTWARDS BLACK ARROW
		{ 0x2B96, 0x2B96, Category::Unassigned },	// <reserved-2B96>
		{ 0x2B97, 0x2BFF, Category::OtherSymbol },	// SYMBOL FOR TYPE A ELECTRONICS..HELLSCHREIBER PAUSE SYMBOL
		{ 0x2C00, 0x2C2F, Category::UppercaseLetter },	// GLAGOLITIC CAPITAL LETTER AZU..GLAGOLITIC CAPITAL LETTER CAUDATE CHRIVI
		{ 0x2C30, 0x2C5F, Category::LowercaseLetter },	// GLAGOLITIC SMALL LETTER AZU..GLAGOLITIC SMALL LETTER CAUDATE CHRIVI
		{ 0x2C60, 0x2C60, Category::UppercaseLetter },	// LATIN CAPITAL LETTER L WITH DOUBLE BAR
		{ 0x2C61, 0x2C61, Category::LowercaseLetter },	// LATIN SMALL LETTER L WITH DOUBLE BAR
		{ 0x2C62, 0x2C64, Category::UppercaseLetter },	// LATIN CAPITAL LETTER L WITH MIDDLE TILDE..LATIN CAPITAL LETTER R WITH TAIL
		{ 0x2C65, 0x2C66, Category::LowercaseLetter },	// LATIN SMALL LETTER A WITH STROKE..LATIN SMALL LETTER T WITH DIAGONAL STROKE
		{ 0x2C67, 0x2C67, Category::UppercaseLetter },	// LATIN CAPITAL LETTER H WITH DESCENDER
		{ 0x2C68, 0x2C68, Category::LowercaseLetter },	// LATIN SMALL LETTER H WITH DESCENDER
		{ 0x2C69, 0x2C69, Category::UppercaseLetter },	// LATIN CAPITAL LETTER K WITH DESCENDER
		{ 0x2C6A, 0x2C6A, Category::LowercaseLetter },	// LATIN SMALL LETTER K WITH DESCENDER
		{ 0x2C6B, 0x2C6B, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Z WITH DESCENDER
		{ 0x2C6C, 0x2C6C, Category::LowercaseLetter },	// LATIN SMALL LETTER Z WITH DESCENDER
		{ 0x2C6D, 0x2C70, Category::UppercaseLetter },	// LATIN CAPITAL LETTER ALPHA..LATIN CAPITAL LETTER TURNED ALPHA
		{ 0x2C71, 0x2C71, Category::LowercaseLetter },	// LATIN SMALL LETTER V WITH RIGHT HOOK
		{ 0x2C72, 0x2C72, Category::UppercaseLetter },	// LATIN CAPITAL LETTER W WITH HOOK
		{ 0x2C73, 0x2C74, Category::LowercaseLetter },	// LATIN SMALL LETTER W WITH HOOK..LATIN SMALL LETTER V WITH CURL
		{ 0x2C75, 0x2C75, Category::UppercaseLetter },	// LATIN CAPITAL LETTER HALF H
		{ 0x2C76, 0x2C7B, Category::LowercaseLetter },	// LATIN SMALL LETTER HALF H..LATIN LETTER SMALL CAPITAL TURNED E
		{ 0x2C7C, 0x2C7D, Category::ModifierLetter },	// LATIN SUBSCRIPT SMALL LETTER J..MODIFIER LETTER CAPITAL V
		{ 0x2C7E, 0x2C80, Category::UppercaseLetter },	// LATIN CAPITAL LETTER S WITH SWASH TAIL..COPTIC CAPITAL LETTER ALFA
		{ 0x2C81, 0x2C81, Category::LowercaseLetter },	// COPTIC SMALL LETTER ALFA
		{ 0x2C82, 0x2C82, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER VIDA
		{ 0x2C83, 0x2C83, Category::LowercaseLetter },	// COPTIC SMALL LETTER VIDA
		{ 0x2C84, 0x2C84, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER GAMMA
		{ 0x2C85, 0x2C85, Category::LowercaseLetter },	// COPTIC SMALL LETTER GAMMA
		{ 0x2C86, 0x2C86, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER DALDA
		{ 0x2C87, 0x2C87, Category::LowercaseLetter },	// COPTIC SMALL LETTER DALDA
		{ 0x2C88, 0x2C88, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER EIE
		{ 0x2C89, 0x2C89, Category::LowercaseLetter },	// COPTIC SMALL LETTER EIE
		{ 0x2C8A, 0x2C8A, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER SOU
		{ 0x2C8B, 0x2C8B, Category::LowercaseLetter },	// COPTIC SMALL LETTER SOU
		{ 0x2C8C, 0x2C8C, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER ZATA
		{ 0x2C8D, 0x2C8D, Category::LowercaseLetter },	// COPTIC SMALL LETTER ZATA
		{ 0x2C8E, 0x2C8E, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER HATE
		{ 0x2C8F, 0x2C8F, Category::LowercaseLetter },	// COPTIC SMALL LETTER HATE
		{ 0x2C90, 0x2C90, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER THETHE
		{ 0x2C91, 0x2C91, Category::LowercaseLetter },	// COPTIC SMALL LETTER THETHE
		{ 0x2C92, 0x2C92, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER IAUDA
		{ 0x2C93, 0x2C93, Category::LowercaseLetter },	// COPTIC SMALL LETTER IAUDA
		{ 0x2C94, 0x2C94, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER KAPA
		{ 0x2C95, 0x2C95, Category::LowercaseLetter },	// COPTIC SMALL LETTER KAPA
		{ 0x2C96, 0x2C96, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER LAULA
		{ 0x2C97, 0x2C97, Category::LowercaseLetter },	// COPTIC SMALL LETTER LAULA
		{ 0x2C98, 0x2C98, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER MI
		{ 0x2C99, 0x2C99, Category::LowercaseLetter },	// COPTIC SMALL LETTER MI
		{ 0x2C9A, 0x2C9A, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER NI
		{ 0x2C9B, 0x2C9B, Category::LowercaseLetter },	// COPTIC SMALL LETTER NI
		{ 0x2C9C, 0x2C9C, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER KSI
		{ 0x2C9D, 0x2C9D, Category::LowercaseLetter },	// COPTIC SMALL LETTER KSI
		{ 0x2C9E, 0x2C9E, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER O
		{ 0x2C9F, 0x2C9F, Category::LowercaseLetter },	// COPTIC SMALL LETTER O
		{ 0x2CA0, 0x2CA0, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER PI
		{ 0x2CA1, 0x2CA1, Category::LowercaseLetter },	// COPTIC SMALL LETTER PI
		{ 0x2CA2, 0x2CA2, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER RO
		{ 0x2CA3, 0x2CA3, Category::LowercaseLetter },	// COPTIC SMALL LETTER RO
		{ 0x2CA4, 0x2CA4, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER SIMA
		{ 0x2CA5, 0x2CA5, Category::LowercaseLetter },	// COPTIC SMALL LETTER SIMA
		{ 0x2CA6, 0x2CA6, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER TAU
		{ 0x2CA7, 0x2CA7, Category::LowercaseLetter },	// COPTIC SMALL LETTER TAU
		{ 0x2CA8, 0x2CA8, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER UA
		{ 0x2CA9, 0x2CA9, Category::LowercaseLetter },	// COPTIC SMALL LETTER UA
		{ 0x2CAA, 0x2CAA, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER FI
		{ 0x2CAB, 0x2CAB, Category::LowercaseLetter },	// COPTIC SMALL LETTER FI
		{ 0x2CAC, 0x2CAC, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER KHI
		{ 0x2CAD, 0x2CAD, Category::LowercaseLetter },	// COPTIC SMALL LETTER KHI
		{ 0x2CAE, 0x2CAE, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER PSI
		{ 0x2CAF, 0x2CAF, Category::LowercaseLetter },	// COPTIC SMALL LETTER PSI
		{ 0x2CB0, 0x2CB0, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OOU
		{ 0x2CB1, 0x2CB1, Category::LowercaseLetter },	// COPTIC SMALL LETTER OOU
		{ 0x2CB2, 0x2CB2, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER DIALECT-P ALEF
		{ 0x2CB3, 0x2CB3, Category::LowercaseLetter },	// COPTIC SMALL LETTER DIALECT-P ALEF
		{ 0x2CB4, 0x2CB4, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD COPTIC AIN
		{ 0x2CB5, 0x2CB5, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD COPTIC AIN
		{ 0x2CB6, 0x2CB6, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER CRYPTOGRAMMIC EIE
		{ 0x2CB7, 0x2CB7, Category::LowercaseLetter },	// COPTIC SMALL LETTER CRYPTOGRAMMIC EIE
		{ 0x2CB8, 0x2CB8, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER DIALECT-P KAPA
		{ 0x2CB9, 0x2CB9, Category::LowercaseLetter },	// COPTIC SMALL LETTER DIALECT-P KAPA
		{ 0x2CBA, 0x2CBA, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER DIALECT-P NI
		{ 0x2CBB, 0x2CBB, Category::LowercaseLetter },	// COPTIC SMALL LETTER DIALECT-P NI
		{ 0x2CBC, 0x2CBC, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER CRYPTOGRAMMIC NI
		{ 0x2CBD, 0x2CBD, Category::LowercaseLetter },	// COPTIC SMALL LETTER CRYPTOGRAMMIC NI
		{ 0x2CBE, 0x2CBE, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD COPTIC OOU
		{ 0x2CBF, 0x2CBF, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD COPTIC OOU
		{ 0x2CC0, 0x2CC0, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER SAMPI
		{ 0x2CC1, 0x2CC1, Category::LowercaseLetter },	// COPTIC SMALL LETTER SAMPI
		{ 0x2CC2, 0x2CC2, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER CROSSED SHEI
		{ 0x2CC3, 0x2CC3, Category::LowercaseLetter },	// COPTIC SMALL LETTER CROSSED SHEI
		{ 0x2CC4, 0x2CC4, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD COPTIC SHEI
		{ 0x2CC5, 0x2CC5, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD COPTIC SHEI
		{ 0x2CC6, 0x2CC6, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD COPTIC ESH
		{ 0x2CC7, 0x2CC7, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD COPTIC ESH
		{ 0x2CC8, 0x2CC8, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER AKHMIMIC KHEI
		{ 0x2CC9, 0x2CC9, Category::LowercaseLetter },	// COPTIC SMALL LETTER AKHMIMIC KHEI
		{ 0x2CCA, 0x2CCA, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER DIALECT-P HORI
		{ 0x2CCB, 0x2CCB, Category::LowercaseLetter },	// COPTIC SMALL LETTER DIALECT-P HORI
		{ 0x2CCC, 0x2CCC, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD COPTIC HORI
		{ 0x2CCD, 0x2CCD, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD COPTIC HORI
		{ 0x2CCE, 0x2CCE, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD COPTIC HA
		{ 0x2CCF, 0x2CCF, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD COPTIC HA
		{ 0x2CD0, 0x2CD0, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER L-SHAPED HA
		{ 0x2CD1, 0x2CD1, Category::LowercaseLetter },	// COPTIC SMALL LETTER L-SHAPED HA
		{ 0x2CD2, 0x2CD2, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD COPTIC HEI
		{ 0x2CD3, 0x2CD3, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD COPTIC HEI
		{ 0x2CD4, 0x2CD4, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD COPTIC HAT
		{ 0x2CD5, 0x2CD5, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD COPTIC HAT
		{ 0x2CD6, 0x2CD6, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD COPTIC GANGIA
		{ 0x2CD7, 0x2CD7, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD COPTIC GANGIA
		{ 0x2CD8, 0x2CD8, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD COPTIC DJA
		{ 0x2CD9, 0x2CD9, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD COPTIC DJA
		{ 0x2CDA, 0x2CDA, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD COPTIC SHIMA
		{ 0x2CDB, 0x2CDB, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD COPTIC SHIMA
		{ 0x2CDC, 0x2CDC, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD NUBIAN SHIMA
		{ 0x2CDD, 0x2CDD, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD NUBIAN SHIMA
		{ 0x2CDE, 0x2CDE, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD NUBIAN NGI
		{ 0x2CDF, 0x2CDF, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD NUBIAN NGI
		{ 0x2CE0, 0x2CE0, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD NUBIAN NYI
		{ 0x2CE1, 0x2CE1, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD NUBIAN NYI
		{ 0x2CE2, 0x2CE2, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER OLD NUBIAN WAU
		{ 0x2CE3, 0x2CE4, Category::LowercaseLetter },	// COPTIC SMALL LETTER OLD NUBIAN WAU..COPTIC SYMBOL KAI
		{ 0x2CE5, 0x2CEA, Category::OtherSymbol },	// COPTIC SYMBOL MI RO..COPTIC SYMBOL SHIMA SIMA
		{ 0x2CEB, 0x2CEB, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER CRYPTOGRAMMIC SHEI
		{ 0x2CEC, 0x2CEC, Category::LowercaseLetter },	// COPTIC SMALL LETTER CRYPTOGRAMMIC SHEI
		{ 0x2CED, 0x2CED, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER CRYPTOGRAMMIC GANGIA
		{ 0x2CEE, 0x2CEE, Category::LowercaseLetter },	// COPTIC SMALL LETTER CRYPTOGRAMMIC GANGIA
		{ 0x2CEF, 0x2CF1, Category::NonspacingMark },	// COPTIC COMBINING NI ABOVE..COPTIC COMBINING SPIRITUS LENIS
		{ 0x2CF2, 0x2CF2, Category::UppercaseLetter },	// COPTIC CAPITAL LETTER BOHAIRIC KHEI
		{ 0x2CF3, 0x2CF3, Category::LowercaseLetter },	// COPTIC SMALL LETTER BOHAIRIC KHEI
		{ 0x2CF4, 0x2CF8, Category::Unassigned },	// <reserved-2CF4>..<reserved-2CF8>
		{ 0x2CF9, 0x2CFC, Category::OtherPunctuation },	// COPTIC OLD NUBIAN FULL STOP..COPTIC OLD NUBIAN VERSE DIVIDER
		{ 0x2CFD, 0x2CFD, Category::OtherNumber },	// COPTIC FRACTION ONE HALF
		{ 0x2CFE, 0x2CFF, Category::OtherPunctuation },	// COPTIC FULL STOP..COPTIC MORPHOLOGICAL DIVIDER
		{ 0x2D00, 0x2D25, Category::LowercaseLetter },	// GEORGIAN SMALL LETTER AN..GEORGIAN SMALL LETTER HOE
		{ 0x2D26, 0x2D26, Category::Unassigned },	// <reserved-2D26>
		{ 0x2D27, 0x2D27, Category::LowercaseLetter },	// GEORGIAN SMALL LETTER YN
		{ 0x2D28, 0x2D2C, Category::Unassigned },	// <reserved-2D28>..<reserved-2D2C>
		{ 0x2D2D, 0x2D2D, Category::LowercaseLetter },	// GEORGIAN SMALL LETTER AEN
		{ 0x2D2E, 0x2D2F, Category::Unassigned },	// <reserved-2D2E>..<reserved-2D2F>
		{ 0x2D30, 0x2D67, Category::OtherLetter },	// TIFINAGH LETTER YA..TIFINAGH LETTER YO
		{ 0x2D68, 0x2D6E, Category::Unassigned },	// <reserved-2D68>..<reserved-2D6E>
		{ 0x2D6F, 0x2D6F, Category::ModifierLetter },	// TIFINAGH MODIFIER LETTER LABIALIZATION MARK
		{ 0x2D70, 0x2D70, Category::OtherPunctuation },	// TIFINAGH SEPARATOR MARK
		{ 0x2D71, 0x2D7E, Category::Unassigned },	// <reserved-2D71>..<reserved-2D7E>
		{ 0x2D7F, 0x2D7F, Category::NonspacingMark },	// TIFINAGH CONSONANT JOINER
		{ 0x2D80, 0x2D96, Category::OtherLetter },	// ETHIOPIC SYLLABLE LOA..ETHIOPIC SYLLABLE GGWE
		{ 0x2D97, 0x2D9F, Category::Unassigned },	// <reserved-2D97>..<reserved-2D9F>
		{ 0x2DA0, 0x2DA6, Category::OtherLetter },	// ETHIOPIC SYLLABLE SSA..ETHIOPIC SYLLABLE SSO
		{ 0x2DA7, 0x2DA7, Category::Unassigned },	// <reserved-2DA7>
		{ 0x2DA8, 0x2DAE, Category::OtherLetter },	// ETHIOPIC SYLLABLE CCA..ETHIOPIC SYLLABLE CCO
		{ 0x2DAF, 0x2DAF, Category::Unassigned },	// <reserved-2DAF>
		{ 0x2DB0, 0x2DB6, Category::OtherLetter },	// ETHIOPIC SYLLABLE ZZA..ETHIOPIC SYLLABLE ZZO
		{ 0x2DB7, 0x2DB7, Category::Unassigned },	// <reserved-2DB7>
		{ 0x2DB8, 0x2DBE, Category::OtherLetter },	// ETHIOPIC SYLLABLE CCHA..ETHIOPIC SYLLABLE CCHO
		{ 0x2DBF, 0x2DBF, Category::Unassigned },	// <reserved-2DBF>
		{ 0x2DC0, 0x2DC6, Category::OtherLetter },	// ETHIOPIC SYLLABLE QYA..ETHIOPIC SYLLABLE QYO
		{ 0x2DC7, 0x2DC7, Category::Unassigned },	// <reserved-2DC7>
		{ 0x2DC8, 0x2DCE, Category::OtherLetter },	// ETHIOPIC SYLLABLE KYA..ETHIOPIC SYLLABLE KYO
		{ 0x2DCF, 0x2DCF, Category::Unassigned },	// <reserved-2DCF>
		{ 0x2DD0, 0x2DD6, Category::OtherLetter },	// ETHIOPIC SYLLABLE XYA..ETHIOPIC SYLLABLE XYO
		{ 0x2DD7, 0x2DD7, Category::Unassigned },	// <reserved-2DD7>
		{ 0x2DD8, 0x2DDE, Category::OtherLetter },	// ETHIOPIC SYLLABLE GYA..ETHIOPIC SYLLABLE GYO
		{ 0x2DDF, 0x2DDF, Category::Unassigned },	// <reserved-2DDF>
		{ 0x2DE0, 0x2DFF, Category::NonspacingMark },	// COMBINING CYRILLIC LETTER BE..COMBINING CYRILLIC LETTER IOTIFIED BIG YUS
		{ 0x2E00, 0x2E01, Category::OtherPunctuation },	// RIGHT ANGLE SUBSTITUTION MARKER..RIGHT ANGLE DOTTED SUBSTITUTION MARKER
		{ 0x2E02, 0x2E02, Category::InitialPunctuation },	// LEFT SUBSTITUTION BRACKET
		{ 0x2E03, 0x2E03, Category::FinalPunctuation },	// RIGHT SUBSTITUTION BRACKET
		{ 0x2E04, 0x2E04, Category::InitialPunctuation },	// LEFT DOTTED SUBSTITUTION BRACKET
		{ 0x2E05, 0x2E05, Category::FinalPunctuation },	// RIGHT DOTTED SUBSTITUTION BRACKET
		{ 0x2E06, 0x2E08, Category::OtherPunctuation },	// RAISED INTERPOLATION MARKER..DOTTED TRANSPOSITION MARKER
		{ 0x2E09, 0x2E09, Category::InitialPunctuation },	// LEFT TRANSPOSITION BRACKET
		{ 0x2E0A, 0x2E0A, Category::FinalPunctuation },	// RIGHT TRANSPOSITION BRACKET
		{ 0x2E0B, 0x2E0B, Category::OtherPunctuation },	// RAISED SQUARE
		{ 0x2E0C, 0x2E0C, Category::InitialPunctuation },	// LEFT RAISED OMISSION BRACKET
		{ 0x2E0D, 0x2E0D, Category::FinalPunctuation },	// RIGHT RAISED OMISSION BRACKET
		{ 0x2E0E, 0x2E16, Category::OtherPunctuation },	// EDITORIAL CORONIS..DOTTED RIGHT-POINTING ANGLE
		{ 0x2E17, 0x2E17, Category::DashPunctuation },	// DOUBLE OBLIQUE HYPHEN
		{ 0x2E18, 0x2E19, Category::OtherPunctuation },	// INVERTED INTERROBANG..PALM BRANCH
		{ 0x2E1A, 0x2E1A, Category::DashPunctuation },	// HYPHEN WITH DIAERESIS
		{ 0x2E1B, 0x2E1B, Category::OtherPunctuation },	// TILDE WITH RING ABOVE
		{ 0x2E1C, 0x2E1C, Category::InitialPunctuation },	// LEFT LOW PARAPHRASE BRACKET
		{ 0x2E1D, 0x2E1D, Category::FinalPunctuation },	// RIGHT LOW PARAPHRASE BRACKET
		{ 0x2E1E, 0x2E1F, Category::OtherPunctuation },	// TILDE WITH DOT ABOVE..TILDE WITH DOT BELOW
		{ 0x2E20, 0x2E20, Category::InitialPunctuation },	// LEFT VERTICAL BAR WITH QUILL
		{ 0x2E21, 0x2E21, Category::FinalPunctuation },	// RIGHT VERTICAL BAR WITH QUILL
		{ 0x2E22, 0x2E22, Category::OpenPunctuation },	// TOP LEFT HALF BRACKET
		{ 0x2E23, 0x2E23, Category::ClosePunctuation },	// TOP RIGHT HALF BRACKET
		{ 0x2E24, 0x2E24, Category::OpenPunctuation },	// BOTTOM LEFT HALF BRACKET
		{ 0x2E25, 0x2E25, Category::ClosePunctuation },	// BOTTOM RIGHT HALF BRACKET
		{ 0x2E26, 0x2E26, Category::OpenPunctuation },	// LEFT SIDEWAYS U BRACKET
		{ 0x2E27, 0x2E27, Category::ClosePunctuation },	// RIGHT SIDEWAYS U BRACKET
		{ 0x2E28, 0x2E28, Category::OpenPunctuation },	// LEFT DOUBLE PARENTHESIS
		{ 0x2E29, 0x2E29, Category::ClosePunctuation },	// RIGHT DOUBLE PARENTHESIS
		{ 0x2E2A, 0x2E2E, Category::OtherPunctuation },	// TWO DOTS OVER ONE DOT PUNCTUATION..REVERSED QUESTION MARK
		{ 0x2E2F, 0x2E2F, Category::ModifierLetter },	// VERTICAL TILDE
		{ 0x2E30, 0x2E39, Category::OtherPunctuation },	// RING POINT..TOP HALF SECTION SIGN
		{ 0x2E3A, 0x2E3B, Category::DashPunctuation },	// TWO-EM DASH..THREE-EM DASH
		{ 0x2E3C, 0x2E3F, Category::OtherPunctuation },	// STENOGRAPHIC FULL STOP..CAPITULUM
		{ 0x2E40, 0x2E40, Category::DashPunctuation },	// DOUBLE HYPHEN
		{ 0x2E41, 0x2E41, Category::OtherPunctuation },	// REVERSED COMMA
		{ 0x2E42, 0x2E42, Category::OpenPunctuation },	// DOUBLE LOW-REVERSED-9 QUOTATION MARK
		{ 0x2E43, 0x2E4F, Category::OtherPunctuation },	// DASH WITH LEFT UPTURN..CORNISH VERSE DIVIDER
		{ 0x2E50, 0x2E51, Category::OtherSymbol },	// CROSS PATTY WITH RIGHT CROSSBAR..CROSS PATTY WITH LEFT CROSSBAR
		{ 0x2E52, 0x2E54, Category::OtherPunctuation },	// TIRONIAN SIGN CAPITAL ET..MEDIEVAL QUESTION MARK
		{ 0x2E55, 0x2E55, Category::OpenPunctuation },	// LEFT SQUARE BRACKET WITH STROKE
		{ 0x2E56, 0x2E56, Category::ClosePunctuation },	// RIGHT SQUARE BRACKET WITH STROKE
		{ 0x2E57, 0x2E57, Category::OpenPunctuation },	// LEFT SQUARE BRACKET WITH DOUBLE STROKE
		{ 0x2E58, 0x2E58, Category::ClosePunctuation },	// RIGHT SQUARE BRACKET WITH DOUBLE STROKE
		{ 0x2E59, 0x2E59, Category::OpenPunctuation },	// TOP HALF LEFT PARENTHESIS
		{ 0x2E5A, 0x2E5A, Category::ClosePunctuation },	// TOP HALF RIGHT PARENTHESIS
		{ 0x2E5B, 0x2E5B, Category::OpenPunctuation },	// BOTTOM HALF LEFT PARENTHESIS
		{ 0x2E5C, 0x2E5C, Category::ClosePunctuation },	// BOTTOM HALF RIGHT PARENTHESIS
		{ 0x2E5D, 0x2E5D, Category::DashPunctuation },	// OBLIQUE HYPHEN
		{ 0x2E5E, 0x2E7F, Category::Unassigned },	// <reserved-2E5E>..<reserved-2E7F>
		{ 0x2E80, 0x2E99, Category::OtherSymbol },	// CJK RADICAL REPEAT..CJK RADICAL RAP
		{ 0x2E9A, 0x2E9A, Category::Unassigned },	// <reserved-2E9A>
		{ 0x2E9B, 0x2EF3, Category::OtherSymbol },	// CJK RADICAL CHOKE..CJK RADICAL C-SIMPLIFIED TURTLE
		{ 0x2EF4, 0x2EFF, Category::Unassigned },	// <reserved-2EF4>..<reserved-2EFF>
		{ 0x2F00, 0x2FD5, Category::OtherSymbol },	// KANGXI RADICAL ONE..KANGXI RADICAL FLUTE
		{ 0x2FD6, 0x2FEF, Category::Unassigned },	// <reserved-2FD6>..<reserved-2FEF>
		{ 0x2FF0, 0x2FFF, Category::OtherSymbol },	// IDEOGRAPHIC DESCRIPTION CHARACTER LEFT TO RIGHT..IDEOGRAPHIC DESCRIPTION CHARACTER ROTATION
		{ 0x3000, 0x3000, Category::SpaceSeparator },	// IDEOGRAPHIC SPACE
		{ 0x3001, 0x3003, Category::OtherPunctuation },	// IDEOGRAPHIC COMMA..DITTO MARK
		{ 0x3004, 0x3004, Category::OtherSymbol },	// JAPANESE INDUSTRIAL STANDARD SYMBOL
		{ 0x3005, 0x3005, Category::ModifierLetter },	// IDEOGRAPHIC ITERATION MARK
		{ 0x3006, 0x3006, Category::OtherLetter },	// IDEOGRAPHIC CLOSING MARK
		{ 0x3007, 0x3007, Category::LetterNumber },	// IDEOGRAPHIC NUMBER ZERO
		{ 0x3008, 0x3008, Category::OpenPunctuation },	// LEFT ANGLE BRACKET
		{ 0x3009, 0x3009, Category::ClosePunctuation },	// RIGHT ANGLE BRACKET
		{ 0x300A, 0x300A, Category::OpenPunctuation },	// LEFT DOUBLE ANGLE BRACKET
		{ 0x300B, 0x300B, Category::ClosePunctuation },	// RIGHT DOUBLE ANGLE BRACKET
		{ 0x300C, 0x300C, Category::OpenPunctuation },	// LEFT CORNER BRACKET
		{ 0x300D, 0x300D, Category::ClosePunctuation },	// RIGHT CORNER BRACKET
		{ 0x300E, 0x300E, Category::OpenPunctuation },	// LEFT WHITE CORNER BRACKET
		{ 0x300F, 0x300F, Category::ClosePunctuation },	// RIGHT WHITE CORNER BRACKET
		{ 0x3010, 0x3010, Category::OpenPunctuation },	// LEFT BLACK LENTICULAR BRACKET
		{ 0x3011, 0x3011, Category::ClosePunctuation },	// RIGHT BLACK LENTICULAR BRACKET
		{ 0x3012, 0x3013, Category::OtherSymbol },	// POSTAL MARK..GETA MARK
		{ 0x3014, 0x3014, Category::OpenPunctuation },	// LEFT TORTOISE SHELL BRACKET
		{ 0x3015, 0x3015, Category::ClosePunctuation },	// RIGHT TORTOISE SHELL BRACKET
		{ 0x3016, 0x3016, Category::OpenPunctuation },	// LEFT WHITE LENTICULAR BRACKET
		{ 0x3017, 0x3017, Category::ClosePunctuation },	// RIGHT WHITE LENTICULAR BRACKET
		{ 0x3018, 0x3018, Category::OpenPunctuation },	// LEFT WHITE TORTOISE SHELL BRACKET
		{ 0x3019, 0x3019, Category::ClosePunctuation },	// RIGHT WHITE TORTOISE SHELL BRACKET
		{ 0x301A, 0x301A, Category::OpenPunctuation },	// LEFT WHITE SQUARE BRACKET
		{ 0x301B, 0x301B, Category::ClosePunctuation },	// RIGHT WHITE SQUARE BRACKET
		{ 0x301C, 0x301C, Category::DashPunctuation },	// WAVE DASH
		{ 0x301D, 0x301D, Category::OpenPunctuation },	// REVERSED DOUBLE PRIME QUOTATION MARK
		{ 0x301E, 0x301F, Category::ClosePunctuation },	// DOUBLE PRIME QUOTATION MARK..LOW DOUBLE PRIME QUOTATION MARK
		{ 0x3020, 0x3020, Category::OtherSymbol },	// POSTAL MARK FACE
		{ 0x3021, 0x3029, Category::LetterNumber },	// HANGZHOU NUMERAL ONE..HANGZHOU NUMERAL NINE
		{ 0x302A, 0x302D, Category::NonspacingMark },	// IDEOGRAPHIC LEVEL TONE MARK..IDEOGRAPHIC ENTERING TONE MARK
		{ 0x302E, 0x302F, Category::SpacingMark },	// HANGUL SINGLE DOT TONE MARK..HANGUL DOUBLE DOT TONE MARK
		{ 0x3030, 0x3030, Category::DashPunctuation },	// WAVY DASH
		{ 0x3031, 0x3035, Category::ModifierLetter },	// VERTICAL KANA REPEAT MARK..VERTICAL KANA REPEAT MARK LOWER HALF
		{ 0x3036, 0x3037, Category::OtherSymbol },	// CIRCLED POSTAL MARK..IDEOGRAPHIC TELEGRAPH LINE FEED SEPARATOR SYMBOL
		{ 0x3038, 0x303A, Category::LetterNumber },	// HANGZHOU NUMERAL TEN..HANGZHOU NUMERAL THIRTY
		{ 0x303B, 0x303B, Category::ModifierLetter },	// VERTICAL IDEOGRAPHIC ITERATION MARK
		{ 0x303C, 0x303C, Category::OtherLetter },	// MASU MARK
		{ 0x303D, 0x303D, Category::OtherPunctuation },	// PART ALTERNATION MARK
		{ 0x303E, 0x303F, Category::OtherSymbol },	// IDEOGRAPHIC VARIATION INDICATOR..IDEOGRAPHIC HALF FILL SPACE
		{ 0x3040, 0x3040, Category::Unassigned },	// <reserved-3040>
		{ 0x3041, 0x3096, Category::OtherLetter },	// HIRAGANA LETTER SMALL A..HIRAGANA LETTER SMALL KE
		{ 0x3097, 0x3098, Category::Unassigned },	// <reserved-3097>..<reserved-3098>
		{ 0x3099, 0x309A, Category::NonspacingMark },	// COMBINING KATAKANA-HIRAGANA VOICED SOUND MARK..COMBINING KATAKANA-HIRAGANA SEMI-VOICED SOUND MARK
		{ 0x309B, 0x309C, Category::ModifierSymbol },	// KATAKANA-HIRAGANA VOICED SOUND MARK..KATAKANA-HIRAGANA SEMI-VOICED SOUND MARK
		{ 0x309D, 0x309E, Category::ModifierLetter },	// HIRAGANA ITERATION MARK..HIRAGANA VOICED ITERATION MARK
		{ 0x309F, 0x309F, Category::OtherLetter },	// HIRAGANA DIGRAPH YORI
		{ 0x30A0, 0x30A0, Category::DashPunctuation },	// KATAKANA-HIRAGANA DOUBLE HYPHEN
		{ 0x30A1, 0x30FA, Category::OtherLetter },	// KATAKANA LETTER SMALL A..KATAKANA LETTER VO
		{ 0x30FB, 0x30FB, Category::OtherPunctuation },	// KATAKANA MIDDLE DOT
		{ 0x30FC, 0x30FE, Category::ModifierLetter },	// KATAKANA-HIRAGANA PROLONGED SOUND MARK..KATAKANA VOICED ITERATION MARK
		{ 0x30FF, 0x30FF, Category::OtherLetter },	// KATAKANA DIGRAPH KOTO
		{ 0x3100, 0x3104, Category::Unassigned },	// <reserved-3100>..<reserved-3104>
		{ 0x3105, 0x312F, Category::OtherLetter },	// BOPOMOFO LETTER B..BOPOMOFO LETTER NN
		{ 0x3130, 0x3130, Category::Unassigned },	// <reserved-3130>
		{ 0x3131, 0x318E, Category::OtherLetter },	// HANGUL LETTER KIYEOK..HANGUL LETTER ARAEAE
		{ 0x318F, 0x318F, Category::Unassigned },	// <reserved-318F>
		{ 0x3190, 0x3191, Category::OtherSymbol },	// IDEOGRAPHIC ANNOTATION LINKING MARK..IDEOGRAPHIC ANNOTATION REVERSE MARK
		{ 0x3192, 0x3195, Category::OtherNumber },	// IDEOGRAPHIC ANNOTATION ONE MARK..IDEOGRAPHIC ANNOTATION FOUR MARK
		{ 0x3196, 0x319F, Category::OtherSymbol },	// IDEOGRAPHIC ANNOTATION TOP MARK..IDEOGRAPHIC ANNOTATION MAN MARK
		{ 0x31A0, 0x31BF, Category::OtherLetter },	// BOPOMOFO LETTER BU..BOPOMOFO LETTER AH
		{ 0x31C0, 0x31E5, Category::OtherSymbol },	// CJK STROKE T..CJK STROKE SZP
		{ 0x31E6, 0x31EE, Category::Unassigned },	// <reserved-31E6>..<reserved-31EE>
		{ 0x31EF, 0x31EF, Category::OtherSymbol },	// IDEOGRAPHIC DESCRIPTION CHARACTER SUBTRACTION
		{ 0x31F0, 0x31FF, Category::OtherLetter },	// KATAKANA LETTER SMALL KU..KATAKANA LETTER SMALL RO
		{ 0x3200, 0x321E, Category::OtherSymbol },	// PARENTHESIZED HANGUL KIYEOK..PARENTHESIZED KOREAN CHARACTER O HU
		{ 0x321F, 0x321F, Category::Unassigned },	// <reserved-321F>
		{ 0x3220, 0x3229, Category::OtherNumber },	// PARENTHESIZED IDEOGRAPH ONE..PARENTHESIZED IDEOGRAPH TEN
		{ 0x322A, 0x3247, Category::OtherSymbol },	// PARENTHESIZED IDEOGRAPH MOON..CIRCLED IDEOGRAPH KOTO
		{ 0x3248, 0x324F, Category::OtherNumber },	// CIRCLED NUMBER TEN ON BLACK SQUARE..CIRCLED NUMBER EIGHTY ON BLACK SQUARE
		{ 0x3250, 0x3250, Category::OtherSymbol },	// PARTNERSHIP SIGN
		{ 0x3251, 0x325F, Category::OtherNumber },	// CIRCLED NUMBER TWENTY ONE..CIRCLED NUMBER THIRTY FIVE
		{ 0x3260, 0x327F, Category::OtherSymbol },	// CIRCLED HANGUL KIYEOK..KOREAN STANDARD SYMBOL
		{ 0x3280, 0x3289, Category::OtherNumber },	// CIRCLED IDEOGRAPH ONE..CIRCLED IDEOGRAPH TEN
		{ 0x328A, 0x32B0, Category::OtherSymbol },	// CIRCLED IDEOGRAPH MOON..CIRCLED IDEOGRAPH NIGHT
		{ 0x32B1, 0x32BF, Category::OtherNumber },	// CIRCLED NUMBER THIRTY SIX..CIRCLED NUMBER FIFTY
		{ 0x32C0, 0x33FF, Category::OtherSymbol },	// IDEOGRAPHIC TELEGRAPH SYMBOL FOR JANUARY..SQUARE GAL
		{ 0x3400, 0x4DBF, Category::OtherLetter },	// CJK UNIFIED IDEOGRAPH-3400..CJK UNIFIED IDEOGRAPH-4DBF
		{ 0x4DC0, 0x4DFF, Category::OtherSymbol },	// HEXAGRAM FOR THE CREATIVE HEAVEN..HEXAGRAM FOR BEFORE COMPLETION
		{ 0x4E00, 0xA014, Category::OtherLetter },	// CJK UNIFIED IDEOGRAPH-4E00..YI SYLLABLE E
		{ 0xA015, 0xA015, Category::ModifierLetter },	// YI SYLLABLE WU
		{ 0xA016, 0xA48C, Category::OtherLetter },	// YI SYLLABLE BIT..YI SYLLABLE YYR
		{ 0xA48D, 0xA48F, Category::Unassigned },	// <reserved-A48D>..<reserved-A48F>
		{ 0xA490, 0xA4C6, Category::OtherSymbol },	// YI RADICAL QOT..YI RADICAL KE
		{ 0xA4C7, 0xA4CF, Category::Unassigned },	// <reserved-A4C7>..<reserved-A4CF>
		{ 0xA4D0, 0xA4F7, Category::OtherLetter },	// LISU LETTER BA..LISU LETTER OE
		{ 0xA4F8, 0xA4FD, Category::ModifierLetter },	// LISU LETTER TONE MYA TI..LISU LETTER TONE MYA JEU
		{ 0xA4FE, 0xA4FF, Category::OtherPunctuation },	// LISU PUNCTUATION COMMA..LISU PUNCTUATION FULL STOP
		{ 0xA500, 0xA60B, Category::OtherLetter },	// VAI SYLLABLE EE..VAI SYLLABLE NG
		{ 0xA60C, 0xA60C, Category::ModifierLetter },	// VAI SYLLABLE LENGTHENER
		{ 0xA60D, 0xA60F, Category::OtherPunctuation },	// VAI COMMA..VAI QUESTION MARK
		{ 0xA610, 0xA61F, Category::OtherLetter },	// VAI SYLLABLE NDOLE FA..VAI SYMBOL JONG
		{ 0xA620, 0xA629, Category::DecimalNumber },	// VAI DIGIT ZERO..VAI DIGIT NINE
		{ 0xA62A, 0xA62B, Category::OtherLetter },	// VAI SYLLABLE NDOLE MA..VAI SYLLABLE NDOLE DO
		{ 0xA62C, 0xA63F, Category::Unassigned },	// <reserved-A62C>..<reserved-A63F>
		{ 0xA640, 0xA640, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ZEMLYA
		{ 0xA641, 0xA641, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ZEMLYA
		{ 0xA642, 0xA642, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER DZELO
		{ 0xA643, 0xA643, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER DZELO
		{ 0xA644, 0xA644, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER REVERSED DZE
		{ 0xA645, 0xA645, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER REVERSED DZE
		{ 0xA646, 0xA646, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER IOTA
		{ 0xA647, 0xA647, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER IOTA
		{ 0xA648, 0xA648, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER DJERV
		{ 0xA649, 0xA649, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER DJERV
		{ 0xA64A, 0xA64A, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER MONOGRAPH UK
		{ 0xA64B, 0xA64B, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER MONOGRAPH UK
		{ 0xA64C, 0xA64C, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER BROAD OMEGA
		{ 0xA64D, 0xA64D, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER BROAD OMEGA
		{ 0xA64E, 0xA64E, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER NEUTRAL YER
		{ 0xA64F, 0xA64F, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER NEUTRAL YER
		{ 0xA650, 0xA650, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER YERU WITH BACK YER
		{ 0xA651, 0xA651, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER YERU WITH BACK YER
		{ 0xA652, 0xA652, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER IOTIFIED YAT
		{ 0xA653, 0xA653, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER IOTIFIED YAT
		{ 0xA654, 0xA654, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER REVERSED YU
		{ 0xA655, 0xA655, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER REVERSED YU
		{ 0xA656, 0xA656, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER IOTIFIED A
		{ 0xA657, 0xA657, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER IOTIFIED A
		{ 0xA658, 0xA658, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER CLOSED LITTLE YUS
		{ 0xA659, 0xA659, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER CLOSED LITTLE YUS
		{ 0xA65A, 0xA65A, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER BLENDED YUS
		{ 0xA65B, 0xA65B, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER BLENDED YUS
		{ 0xA65C, 0xA65C, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER IOTIFIED CLOSED LITTLE YUS
		{ 0xA65D, 0xA65D, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER IOTIFIED CLOSED LITTLE YUS
		{ 0xA65E, 0xA65E, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER YN
		{ 0xA65F, 0xA65F, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER YN
		{ 0xA660, 0xA660, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER REVERSED TSE
		{ 0xA661, 0xA661, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER REVERSED TSE
		{ 0xA662, 0xA662, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER SOFT DE
		{ 0xA663, 0xA663, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER SOFT DE
		{ 0xA664, 0xA664, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER SOFT EL
		{ 0xA665, 0xA665, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER SOFT EL
		{ 0xA666, 0xA666, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER SOFT EM
		{ 0xA667, 0xA667, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER SOFT EM
		{ 0xA668, 0xA668, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER MONOCULAR O
		{ 0xA669, 0xA669, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER MONOCULAR O
		{ 0xA66A, 0xA66A, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER BINOCULAR O
		{ 0xA66B, 0xA66B, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER BINOCULAR O
		{ 0xA66C, 0xA66C, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER DOUBLE MONOCULAR O
		{ 0xA66D, 0xA66D, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER DOUBLE MONOCULAR O
		{ 0xA66E, 0xA66E, Category::OtherLetter },	// CYRILLIC LETTER MULTIOCULAR O
		{ 0xA66F, 0xA66F, Category::NonspacingMark },	// COMBINING CYRILLIC VZMET
		{ 0xA670, 0xA672, Category::EnclosingMark },	// COMBINING CYRILLIC TEN MILLIONS SIGN..COMBINING CYRILLIC THOUSAND MILLIONS SIGN
		{ 0xA673, 0xA673, Category::OtherPunctuation },	// SLAVONIC ASTERISK
		{ 0xA674, 0xA67D, Category::NonspacingMark },	// COMBINING CYRILLIC LETTER UKRAINIAN IE..COMBINING CYRILLIC PAYEROK
		{ 0xA67E, 0xA67E, Category::OtherPunctuation },	// CYRILLIC KAVYKA
		{ 0xA67F, 0xA67F, Category::ModifierLetter },	// CYRILLIC PAYEROK
		{ 0xA680, 0xA680, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER DWE
		{ 0xA681, 0xA681, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER DWE
		{ 0xA682, 0xA682, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER DZWE
		{ 0xA683, 0xA683, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER DZWE
		{ 0xA684, 0xA684, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER ZHWE
		{ 0xA685, 0xA685, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER ZHWE
		{ 0xA686, 0xA686, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER CCHE
		{ 0xA687, 0xA687, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER CCHE
		{ 0xA688, 0xA688, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER DZZE
		{ 0xA689, 0xA689, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER DZZE
		{ 0xA68A, 0xA68A, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER TE WITH MIDDLE HOOK
		{ 0xA68B, 0xA68B, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER TE WITH MIDDLE HOOK
		{ 0xA68C, 0xA68C, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER TWE
		{ 0xA68D, 0xA68D, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER TWE
		{ 0xA68E, 0xA68E, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER TSWE
		{ 0xA68F, 0xA68F, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER TSWE
		{ 0xA690, 0xA690, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER TSSE
		{ 0xA691, 0xA691, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER TSSE
		{ 0xA692, 0xA692, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER TCHE
		{ 0xA693, 0xA693, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER TCHE
		{ 0xA694, 0xA694, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER HWE
		{ 0xA695, 0xA695, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER HWE
		{ 0xA696, 0xA696, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER SHWE
		{ 0xA697, 0xA697, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER SHWE
		{ 0xA698, 0xA698, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER DOUBLE O
		{ 0xA699, 0xA699, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER DOUBLE O
		{ 0xA69A, 0xA69A, Category::UppercaseLetter },	// CYRILLIC CAPITAL LETTER CROSSED O
		{ 0xA69B, 0xA69B, Category::LowercaseLetter },	// CYRILLIC SMALL LETTER CROSSED O
		{ 0xA69C, 0xA69D, Category::ModifierLetter },	// MODIFIER LETTER CYRILLIC HARD SIGN..MODIFIER LETTER CYRILLIC SOFT SIGN
		{ 0xA69E, 0xA69F, Category::NonspacingMark },	// COMBINING CYRILLIC LETTER EF..COMBINING CYRILLIC LETTER IOTIFIED E
		{ 0xA6A0, 0xA6E5, Category::OtherLetter },	// BAMUM LETTER A..BAMUM LETTER KI
		{ 0xA6E6, 0xA6EF, Category::LetterNumber },	// BAMUM LETTER MO..BAMUM LETTER KOGHOM
		{ 0xA6F0, 0xA6F1, Category::NonspacingMark },	// BAMUM COMBINING MARK KOQNDON..BAMUM COMBINING MARK TUKWENTIS
		{ 0xA6F2, 0xA6F7, Category::OtherPunctuation },	// BAMUM NJAEMLI..BAMUM QUESTION MARK
		{ 0xA6F8, 0xA6FF, Category::Unassigned },	// <reserved-A6F8>..<reserved-A6FF>
		{ 0xA700, 0xA716, Category::ModifierSymbol },	// MODIFIER LETTER CHINESE TONE YIN PING..MODIFIER LETTER EXTRA-LOW LEFT-STEM TONE BAR
		{ 0xA717, 0xA71F, Category::ModifierLetter },	// MODIFIER LETTER DOT VERTICAL BAR..MODIFIER LETTER LOW INVERTED EXCLAMATION MARK
		{ 0xA720, 0xA721, Category::ModifierSymbol },	// MODIFIER LETTER STRESS AND HIGH TONE..MODIFIER LETTER STRESS AND LOW TONE
		{ 0xA722, 0xA722, Category::UppercaseLetter },	// LATIN CAPITAL LETTER EGYPTOLOGICAL ALEF
		{ 0xA723, 0xA723, Category::LowercaseLetter },	// LATIN SMALL LETTER EGYPTOLOGICAL ALEF
		{ 0xA724, 0xA724, Category::UppercaseLetter },	// LATIN CAPITAL LETTER EGYPTOLOGICAL AIN
		{ 0xA725, 0xA725, Category::LowercaseLetter },	// LATIN SMALL LETTER EGYPTOLOGICAL AIN
		{ 0xA726, 0xA726, Category::UppercaseLetter },	// LATIN CAPITAL LETTER HENG
		{ 0xA727, 0xA727, Category::LowercaseLetter },	// LATIN SMALL LETTER HENG
		{ 0xA728, 0xA728, Category::UppercaseLetter },	// LATIN CAPITAL LETTER TZ
		{ 0xA729, 0xA729, Category::LowercaseLetter },	// LATIN SMALL LETTER TZ
		{ 0xA72A, 0xA72A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER TRESILLO
		{ 0xA72B, 0xA72B, Category::LowercaseLetter },	// LATIN SMALL LETTER TRESILLO
		{ 0xA72C, 0xA72C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER CUATRILLO
		{ 0xA72D, 0xA72D, Category::LowercaseLetter },	// LATIN SMALL LETTER CUATRILLO
		{ 0xA72E, 0xA72E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER CUATRILLO WITH COMMA
		{ 0xA72F, 0xA731, Category::LowercaseLetter },	// LATIN SMALL LETTER CUATRILLO WITH COMMA..LATIN LETTER SMALL CAPITAL S
		{ 0xA732, 0xA732, Category::UppercaseLetter },	// LATIN CAPITAL LETTER AA
		{ 0xA733, 0xA733, Category::LowercaseLetter },	// LATIN SMALL LETTER AA
		{ 0xA734, 0xA734, Category::UppercaseLetter },	// LATIN CAPITAL LETTER AO
		{ 0xA735, 0xA735, Category::LowercaseLetter },	// LATIN SMALL LETTER AO
		{ 0xA736, 0xA736, Category::UppercaseLetter },	// LATIN CAPITAL LETTER AU
		{ 0xA737, 0xA737, Category::LowercaseLetter },	// LATIN SMALL LETTER AU
		{ 0xA738, 0xA738, Category::UppercaseLetter },	// LATIN CAPITAL LETTER AV
		{ 0xA739, 0xA739, Category::LowercaseLetter },	// LATIN SMALL LETTER AV
		{ 0xA73A, 0xA73A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER AV WITH HORIZONTAL BAR
		{ 0xA73B, 0xA73B, Category::LowercaseLetter },	// LATIN SMALL LETTER AV WITH HORIZONTAL BAR
		{ 0xA73C, 0xA73C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER AY
		{ 0xA73D, 0xA73D, Category::LowercaseLetter },	// LATIN SMALL LETTER AY
		{ 0xA73E, 0xA73E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER REVERSED C WITH DOT
		{ 0xA73F, 0xA73F, Category::LowercaseLetter },	// LATIN SMALL LETTER REVERSED C WITH DOT
		{ 0xA740, 0xA740, Category::UppercaseLetter },	// LATIN CAPITAL LETTER K WITH STROKE
		{ 0xA741, 0xA741, Category::LowercaseLetter },	// LATIN SMALL LETTER K WITH STROKE
		{ 0xA742, 0xA742, Category::UppercaseLetter },	// LATIN CAPITAL LETTER K WITH DIAGONAL STROKE
		{ 0xA743, 0xA743, Category::LowercaseLetter },	// LATIN SMALL LETTER K WITH DIAGONAL STROKE
		{ 0xA744, 0xA744, Category::UppercaseLetter },	// LATIN CAPITAL LETTER K WITH STROKE AND DIAGONAL STROKE
		{ 0xA745, 0xA745, Category::LowercaseLetter },	// LATIN SMALL LETTER K WITH STROKE AND DIAGONAL STROKE
		{ 0xA746, 0xA746, Category::UppercaseLetter },	// LATIN CAPITAL LETTER BROKEN L
		{ 0xA747, 0xA747, Category::LowercaseLetter },	// LATIN SMALL LETTER BROKEN L
		{ 0xA748, 0xA748, Category::UppercaseLetter },	// LATIN CAPITAL LETTER L WITH HIGH STROKE
		{ 0xA749, 0xA749, Category::LowercaseLetter },	// LATIN SMALL LETTER L WITH HIGH STROKE
		{ 0xA74A, 0xA74A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH LONG STROKE OVERLAY
		{ 0xA74B, 0xA74B, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH LONG STROKE OVERLAY
		{ 0xA74C, 0xA74C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER O WITH LOOP
		{ 0xA74D, 0xA74D, Category::LowercaseLetter },	// LATIN SMALL LETTER O WITH LOOP
		{ 0xA74E, 0xA74E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER OO
		{ 0xA74F, 0xA74F, Category::LowercaseLetter },	// LATIN SMALL LETTER OO
		{ 0xA750, 0xA750, Category::UppercaseLetter },	// LATIN CAPITAL LETTER P WITH STROKE THROUGH DESCENDER
		{ 0xA751, 0xA751, Category::LowercaseLetter },	// LATIN SMALL LETTER P WITH STROKE THROUGH DESCENDER
		{ 0xA752, 0xA752, Category::UppercaseLetter },	// LATIN CAPITAL LETTER P WITH FLOURISH
		{ 0xA753, 0xA753, Category::LowercaseLetter },	// LATIN SMALL LETTER P WITH FLOURISH
		{ 0xA754, 0xA754, Category::UppercaseLetter },	// LATIN CAPITAL LETTER P WITH SQUIRREL TAIL
		{ 0xA755, 0xA755, Category::LowercaseLetter },	// LATIN SMALL LETTER P WITH SQUIRREL TAIL
		{ 0xA756, 0xA756, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Q WITH STROKE THROUGH DESCENDER
		{ 0xA757, 0xA757, Category::LowercaseLetter },	// LATIN SMALL LETTER Q WITH STROKE THROUGH DESCENDER
		{ 0xA758, 0xA758, Category::UppercaseLetter },	// LATIN CAPITAL LETTER Q WITH DIAGONAL STROKE
		{ 0xA759, 0xA759, Category::LowercaseLetter },	// LATIN SMALL LETTER Q WITH DIAGONAL STROKE
		{ 0xA75A, 0xA75A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER R ROTUNDA
		{ 0xA75B, 0xA75B, Category::LowercaseLetter },	// LATIN SMALL LETTER R ROTUNDA
		{ 0xA75C, 0xA75C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER RUM ROTUNDA
		{ 0xA75D, 0xA75D, Category::LowercaseLetter },	// LATIN SMALL LETTER RUM ROTUNDA
		{ 0xA75E, 0xA75E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER V WITH DIAGONAL STROKE
		{ 0xA75F, 0xA75F, Category::LowercaseLetter },	// LATIN SMALL LETTER V WITH DIAGONAL STROKE
		{ 0xA760, 0xA760, Category::UppercaseLetter },	// LATIN CAPITAL LETTER VY
		{ 0xA761, 0xA761, Category::LowercaseLetter },	// LATIN SMALL LETTER VY
		{ 0xA762, 0xA762, Category::UppercaseLetter },	// LATIN CAPITAL LETTER VISIGOTHIC Z
		{ 0xA763, 0xA763, Category::LowercaseLetter },	// LATIN SMALL LETTER VISIGOTHIC Z
		{ 0xA764, 0xA764, Category::UppercaseLetter },	// LATIN CAPITAL LETTER THORN WITH STROKE
		{ 0xA765, 0xA765, Category::LowercaseLetter },	// LATIN SMALL LETTER THORN WITH STROKE
		{ 0xA766, 0xA766, Category::UppercaseLetter },	// LATIN CAPITAL LETTER THORN WITH STROKE THROUGH DESCENDER
		{ 0xA767, 0xA767, Category::LowercaseLetter },	// LATIN SMALL LETTER THORN WITH STROKE THROUGH DESCENDER
		{ 0xA768, 0xA768, Category::UppercaseLetter },	// LATIN CAPITAL LETTER VEND
		{ 0xA769, 0xA769, Category::LowercaseLetter },	// LATIN SMALL LETTER VEND
		{ 0xA76A, 0xA76A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER ET
		{ 0xA76B, 0xA76B, Category::LowercaseLetter },	// LATIN SMALL LETTER ET
		{ 0xA76C, 0xA76C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER IS
		{ 0xA76D, 0xA76D, Category::LowercaseLetter },	// LATIN SMALL LETTER IS
		{ 0xA76E, 0xA76E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER CON
		{ 0xA76F, 0xA76F, Category::LowercaseLetter },	// LATIN SMALL LETTER CON
		{ 0xA770, 0xA770, Category::ModifierLetter },	// MODIFIER LETTER US
		{ 0xA771, 0xA778, Category::LowercaseLetter },	// LATIN SMALL LETTER DUM..LATIN SMALL LETTER UM
		{ 0xA779, 0xA779, Category::UppercaseLetter },	// LATIN CAPITAL LETTER INSULAR D
		{ 0xA77A, 0xA77A, Category::LowercaseLetter },	// LATIN SMALL LETTER INSULAR D
		{ 0xA77B, 0xA77B, Category::UppercaseLetter },	// LATIN CAPITAL LETTER INSULAR F
		{ 0xA77C, 0xA77C, Category::LowercaseLetter },	// LATIN SMALL LETTER INSULAR F
		{ 0xA77D, 0xA77E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER INSULAR G..LATIN CAPITAL LETTER TURNED INSULAR G
		{ 0xA77F, 0xA77F, Category::LowercaseLetter },	// LATIN SMALL LETTER TURNED INSULAR G
		{ 0xA780, 0xA780, Category::UppercaseLetter },	// LATIN CAPITAL LETTER TURNED L
		{ 0xA781, 0xA781, Category::LowercaseLetter },	// LATIN SMALL LETTER TURNED L
		{ 0xA782, 0xA782, Category::UppercaseLetter },	// LATIN CAPITAL LETTER INSULAR R
		{ 0xA783, 0xA783, Category::LowercaseLetter },	// LATIN SMALL LETTER INSULAR R
		{ 0xA784, 0xA784, Category::UppercaseLetter },	// LATIN CAPITAL LETTER INSULAR S
		{ 0xA785, 0xA785, Category::LowercaseLetter },	// LATIN SMALL LETTER INSULAR S
		{ 0xA786, 0xA786, Category::UppercaseLetter },	// LATIN CAPITAL LETTER INSULAR T
		{ 0xA787, 0xA787, Category::LowercaseLetter },	// LATIN SMALL LETTER INSULAR T
		{ 0xA788, 0xA788, Category::ModifierLetter },	// MODIFIER LETTER LOW CIRCUMFLEX ACCENT
		{ 0xA789, 0xA78A, Category::ModifierSymbol },	// MODIFIER LETTER COLON..MODIFIER LETTER SHORT EQUALS SIGN
		{ 0xA78B, 0xA78B, Category::UppercaseLetter },	// LATIN CAPITAL LETTER SALTILLO
		{ 0xA78C, 0xA78C, Category::LowercaseLetter },	// LATIN SMALL LETTER SALTILLO
		{ 0xA78D, 0xA78D, Category::UppercaseLetter },	// LATIN CAPITAL LETTER TURNED H
		{ 0xA78E, 0xA78E, Category::LowercaseLetter },	// LATIN SMALL LETTER L WITH RETROFLEX HOOK AND BELT
		{ 0xA78F, 0xA78F, Category::OtherLetter },	// LATIN LETTER SINOLOGICAL DOT
		{ 0xA790, 0xA790, Category::UppercaseLetter },	// LATIN CAPITAL LETTER N WITH DESCENDER
		{ 0xA791, 0xA791, Category::LowercaseLetter },	// LATIN SMALL LETTER N WITH DESCENDER
		{ 0xA792, 0xA792, Category::UppercaseLetter },	// LATIN CAPITAL LETTER C WITH BAR
		{ 0xA793, 0xA795, Category::LowercaseLetter },	// LATIN SMALL LETTER C WITH BAR..LATIN SMALL LETTER H WITH PALATAL HOOK
		{ 0xA796, 0xA796, Category::UppercaseLetter },	// LATIN CAPITAL LETTER B WITH FLOURISH
		{ 0xA797, 0xA797, Category::LowercaseLetter },	// LATIN SMALL LETTER B WITH FLOURISH
		{ 0xA798, 0xA798, Category::UppercaseLetter },	// LATIN CAPITAL LETTER F WITH STROKE
		{ 0xA799, 0xA799, Category::LowercaseLetter },	// LATIN SMALL LETTER F WITH STROKE
		{ 0xA79A, 0xA79A, Category::UppercaseLetter },	// LATIN CAPITAL LETTER VOLAPUK AE
		{ 0xA79B, 0xA79B, Category::LowercaseLetter },	// LATIN SMALL LETTER VOLAPUK AE
		{ 0xA79C, 0xA79C, Category::UppercaseLetter },	// LATIN CAPITAL LETTER VOLAPUK OE
		{ 0xA79D, 0xA79D, Category::LowercaseLetter },	// LATIN SMALL LETTER VOLAPUK OE
		{ 0xA79E, 0xA79E, Category::UppercaseLetter },	// LATIN CAPITAL LETTER VOLAPUK UE
		{ 0xA79F, 0xA79F, Category::LowercaseLetter },	// LATIN SMALL LETTER VOLAPUK UE
		{ 0xA7A0, 0xA7A0, Category::UppercaseLetter },	// LATIN CAPITAL LETTER G WITH OBLIQUE STROKE
		{ 0xA7A1, 0xA7A1, Category::LowercaseLetter },	// LATIN SMALL LETTER G WITH OBLIQUE STROKE
		{ 0xA7A2, 0xA7A2, Category::UppercaseLetter },	// LATIN CAPITAL LETTER K WITH OBLIQUE STROKE
		{ 0xA7A3, 0xA7A3, Category::LowercaseLetter },	// LATIN SMALL LETTER K WITH OBLIQUE STROKE
		{ 0xA7A4, 0xA7A4, Category::UppercaseLetter },	// LATIN CAPITAL LETTER N WITH OBLIQUE STROKE
		{ 0xA7A5, 0xA7A5, Category::LowercaseLetter },	// LATIN SMALL LETTER N WITH OBLIQUE STROKE
		{ 0xA7A6, 0xA7A6, Category::UppercaseLetter },	// LATIN CAPITAL LETTER R WITH OBLIQUE STROKE
		{ 0xA7A7, 0xA7A7, Category::LowercaseLetter },	// LATIN SMALL LETTER R WITH OBLIQUE STROKE
		{ 0xA7A8, 0xA7A8, Category::UppercaseLetter },	// LATIN CAPITAL LETTER S WITH OBLIQUE STROKE
		{ 0xA7A9, 0xA7A9, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH OBLIQUE STROKE
		{ 0xA7AA, 0xA7AE, Category::UppercaseLetter },	// LATIN CAPITAL LETTER H WITH HOOK..LATIN CAPITAL LETTER SMALL CAPITAL I
		{ 0xA7AF, 0xA7AF, Category::LowercaseLetter },	// LATIN LETTER SMALL CAPITAL Q
		{ 0xA7B0, 0xA7B4, Category::UppercaseLetter },	// LATIN CAPITAL LETTER TURNED K..LATIN CAPITAL LETTER BETA
		{ 0xA7B5, 0xA7B5, Category::LowercaseLetter },	// LATIN SMALL LETTER BETA
		{ 0xA7B6, 0xA7B6, Category::UppercaseLetter },	// LATIN CAPITAL LETTER OMEGA
		{ 0xA7B7, 0xA7B7, Category::LowercaseLetter },	// LATIN SMALL LETTER OMEGA
		{ 0xA7B8, 0xA7B8, Category::UppercaseLetter },	// LATIN CAPITAL LETTER U WITH STROKE
		{ 0xA7B9, 0xA7B9, Category::LowercaseLetter },	// LATIN SMALL LETTER U WITH STROKE
		{ 0xA7BA, 0xA7BA, Category::UppercaseLetter },	// LATIN CAPITAL LETTER GLOTTAL A
		{ 0xA7BB, 0xA7BB, Category::LowercaseLetter },	// LATIN SMALL LETTER GLOTTAL A
		{ 0xA7BC, 0xA7BC, Category::UppercaseLetter },	// LATIN CAPITAL LETTER GLOTTAL I
		{ 0xA7BD, 0xA7BD, Category::LowercaseLetter },	// LATIN SMALL LETTER GLOTTAL I
		{ 0xA7BE, 0xA7BE, Category::UppercaseLetter },	// LATIN CAPITAL LETTER GLOTTAL U
		{ 0xA7BF, 0xA7BF, Category::LowercaseLetter },	// LATIN SMALL LETTER GLOTTAL U
		{ 0xA7C0, 0xA7C0, Category::UppercaseLetter },	// LATIN CAPITAL LETTER OLD POLISH O
		{ 0xA7C1, 0xA7C1, Category::LowercaseLetter },	// LATIN SMALL LETTER OLD POLISH O
		{ 0xA7C2, 0xA7C2, Category::UppercaseLetter },	// LATIN CAPITAL LETTER ANGLICANA W
		{ 0xA7C3, 0xA7C3, Category::LowercaseLetter },	// LATIN SMALL LETTER ANGLICANA W
		{ 0xA7C4, 0xA7C7, Category::UppercaseLetter },	// LATIN CAPITAL LETTER C WITH PALATAL HOOK..LATIN CAPITAL LETTER D WITH SHORT STROKE OVERLAY
		{ 0xA7C8, 0xA7C8, Category::LowercaseLetter },	// LATIN SMALL LETTER D WITH SHORT STROKE OVERLAY
		{ 0xA7C9, 0xA7C9, Category::UppercaseLetter },	// LATIN CAPITAL LETTER S WITH SHORT STROKE OVERLAY
		{ 0xA7CA, 0xA7CA, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH SHORT STROKE OVERLAY
		{ 0xA7CB, 0xA7CC, Category::UppercaseLetter },	// LATIN CAPITAL LETTER RAMS HORN..LATIN CAPITAL LETTER S WITH DIAGONAL STROKE
		{ 0xA7CD, 0xA7CD, Category::LowercaseLetter },	// LATIN SMALL LETTER S WITH DIAGONAL STROKE
		{ 0xA7CE, 0xA7CF, Category::Unassigned },	// <reserved-A7CE>..<reserved-A7CF>
		{ 0xA7D0, 0xA7D0, Category::UppercaseLetter },	// LATIN CAPITAL LETTER CLOSED INSULAR G
		{ 0xA7D1, 0xA7D1, Category::LowercaseLetter },	// LATIN SMALL LETTER CLOSED INSULAR G
		{ 0xA7D2, 0xA7D2, Category::Unassigned },	// <reserved-A7D2>
		{ 0xA7D3, 0xA7D3, Category::LowercaseLetter },	// LATIN SMALL LETTER DOUBLE THORN
		{ 0xA7D4, 0xA7D4, Category::Unassigned },	// <reserved-A7D4>
		{ 0xA7D5, 0xA7D5, Category::LowercaseLetter },	// LATIN SMALL LETTER DOUBLE WYNN
		{ 0xA7D6, 0xA7D6, Category::UppercaseLetter },	// LATIN CAPITAL LETTER MIDDLE SCOTS S
		{ 0xA7D7, 0xA7D7, Category::LowercaseLetter },	// LATIN SMALL LETTER MIDDLE SCOTS S
		{ 0xA7D8, 0xA7D8, Category::UppercaseLetter },	// LATIN CAPITAL LETTER SIGMOID S
		{ 0xA7D9, 0xA7D9, Category::LowercaseLetter },	// LATIN SMALL LETTER SIGMOID S
		{ 0xA7DA, 0xA7DA, Category::UppercaseLetter },	// LATIN CAPITAL LETTER LAMBDA
		{ 0xA7DB, 0xA7DB, Category::LowercaseLetter },	// LATIN SMALL LETTER LAMBDA
		{ 0xA7DC, 0xA7DC, Category::UppercaseLetter },	// LATIN CAPITAL LETTER LAMBDA WITH STROKE
		{ 0xA7DD, 0xA7F1, Category::Unassigned },	// <reserved-A7DD>..<reserved-A7F1>
		{ 0xA7F2, 0xA7F4, Category::ModifierLetter },	// MODIFIER LETTER CAPITAL C..MODIFIER LETTER CAPITAL Q
		{ 0xA7F5, 0xA7F5, Category::UppercaseLetter },	// LATIN CAPITAL LETTER REVERSED HALF H
		{ 0xA7F6, 0xA7F6, Category::LowercaseLetter },	// LATIN SMALL LETTER REVERSED HALF H
		{ 0xA7F7, 0xA7F7, Category::OtherLetter },	// LATIN EPIGRAPHIC LETTER SIDEWAYS I
		{ 0xA7F8, 0xA7F9, Category::ModifierLetter },	// MODIFIER LETTER CAPITAL H WITH STROKE..MODIFIER LETTER SMALL LIGATURE OE
		{ 0xA7FA, 0xA7FA, Category::LowercaseLetter },	// LATIN LETTER SMALL CAPITAL TURNED M
		{ 0xA7FB, 0xA801, Category::OtherLetter },	// LATIN EPIGRAPHIC LETTER REVERSED F..SYLOTI NAGRI LETTER I
		{ 0xA802, 0xA802, Category::NonspacingMark },	// SYLOTI NAGRI SIGN DVISVARA
		{ 0xA803, 0xA805, Category::OtherLetter },	// SYLOTI NAGRI LETTER U..SYLOTI NAGRI LETTER O
		{ 0xA806, 0xA806, Category::NonspacingMark },	// SYLOTI NAGRI SIGN HASANTA
		{ 0xA807, 0xA80A, Category::OtherLetter },	// SYLOTI NAGRI LETTER KO..SYLOTI NAGRI LETTER GHO
		{ 0xA80B, 0xA80B, Category::NonspacingMark },	// SYLOTI NAGRI SIGN ANUSVARA
		{ 0xA80C, 0xA822, Category::OtherLetter },	// SYLOTI NAGRI LETTER CO..SYLOTI NAGRI LETTER HO
		{ 0xA823, 0xA824, Category::SpacingMark },	// SYLOTI NAGRI VOWEL SIGN A..SYLOTI NAGRI VOWEL SIGN I
		{ 0xA825, 0xA826, Category::NonspacingMark },	// SYLOTI NAGRI VOWEL SIGN U..SYLOTI NAGRI VOWEL SIGN E
		{ 0xA827, 0xA827, Category::SpacingMark },	// SYLOTI NAGRI VOWEL SIGN OO
		{ 0xA828, 0xA82B, Category::OtherSymbol },	// SYLOTI NAGRI POETRY MARK-1..SYLOTI NAGRI POETRY MARK-4
		{ 0xA82C, 0xA82C, Category::NonspacingMark },	// SYLOTI NAGRI SIGN ALTERNATE HASANTA
		{ 0xA82D, 0xA82F, Category::Unassigned },	// <reserved-A82D>..<reserved-A82F>
		{ 0xA830, 0xA835, Category::OtherNumber },	// NORTH INDIC FRACTION ONE QUARTER..NORTH INDIC FRACTION THREE SIXTEENTHS
		{ 0xA836, 0xA837, Category::OtherSymbol },	// NORTH INDIC QUARTER MARK..NORTH INDIC PLACEHOLDER MARK
		{ 0xA838, 0xA838, Category::CurrencySymbol },	// NORTH INDIC RUPEE MARK
		{ 0xA839, 0xA839, Category::OtherSymbol },	// NORTH INDIC QUANTITY MARK
		{ 0xA83A, 0xA83F, Category::Unassigned },	// <reserved-A83A>..<reserved-A83F>
		{ 0xA840, 0xA873, Category::OtherLetter },	// PHAGS-PA LETTER KA..PHAGS-PA LETTER CANDRABINDU
		{ 0xA874, 0xA877, Category::OtherPunctuation },	// PHAGS-PA SINGLE HEAD MARK..PHAGS-PA MARK DOUBLE SHAD
		{ 0xA878, 0xA87F, Category::Unassigned },	// <reserved-A878>..<reserved-A87F>
		{ 0xA880, 0xA881, Category::SpacingMark },	// SAURASHTRA SIGN ANUSVARA..SAURASHTRA SIGN VISARGA
		{ 0xA882, 0xA8B3, Category::OtherLetter },	// SAURASHTRA LETTER A..SAURASHTRA LETTER LLA
		{ 0xA8B4, 0xA8C3, Category::SpacingMark },	// SAURASHTRA CONSONANT SIGN HAARU..SAURASHTRA VOWEL SIGN AU
		{ 0xA8C4, 0xA8C5, Category::NonspacingMark },	// SAURASHTRA SIGN VIRAMA..SAURASHTRA SIGN CANDRABINDU
		{ 0xA8C6, 0xA8CD, Category::Unassigned },	// <reserved-A8C6>..<reserved-A8CD>
		{ 0xA8CE, 0xA8CF, Category::OtherPunctuation },	// SAURASHTRA DANDA..SAURASHTRA DOUBLE DANDA
		{ 0xA8D0, 0xA8D9, Category::DecimalNumber },	// SAURASHTRA DIGIT ZERO..SAURASHTRA DIGIT NINE
		{ 0xA8DA, 0xA8DF, Category::Unassigned },	// <reserved-A8DA>..<reserved-A8DF>
		{ 0xA8E0, 0xA8F1, Category::NonspacingMark },	// COMBINING DEVANAGARI DIGIT ZERO..COMBINING DEVANAGARI SIGN AVAGRAHA
		{ 0xA8F2, 0xA8F7, Category::OtherLetter },	// DEVANAGARI SIGN SPACING CANDRABINDU..DEVANAGARI SIGN CANDRABINDU AVAGRAHA
		{ 0xA8F8, 0xA8FA, Category::OtherPunctuation },	// DEVANAGARI SIGN PUSHPIKA..DEVANAGARI CARET
		{ 0xA8FB, 0xA8FB, Category::OtherLetter },	// DEVANAGARI HEADSTROKE
		{ 0xA8FC, 0xA8FC, Category::OtherPunctuation },	// DEVANAGARI SIGN SIDDHAM
		{ 0xA8FD, 0xA8FE, Category::OtherLetter },	// DEVANAGARI JAIN OM..DEVANAGARI LETTER AY
		{ 0xA8FF, 0xA8FF, Category::NonspacingMark },	// DEVANAGARI VOWEL SIGN AY
		{ 0xA900, 0xA909, Category::DecimalNumber },	// KAYAH LI DIGIT ZERO..KAYAH LI DIGIT NINE
		{ 0xA90A, 0xA925, Category::OtherLetter },	// KAYAH LI LETTER KA..KAYAH LI LETTER OO
		{ 0xA926, 0xA92D, Category::NonspacingMark },	// KAYAH LI VOWEL UE..KAYAH LI TONE CALYA PLOPHU
		{ 0xA92E, 0xA92F, Category::OtherPunctuation },	// KAYAH LI SIGN CWI..KAYAH LI SIGN SHYA
		{ 0xA930, 0xA946, Category::OtherLetter },	// REJANG LETTER KA..REJANG LETTER A
		{ 0xA947, 0xA951, Category::NonspacingMark },	// REJANG VOWEL SIGN I..REJANG CONSONANT SIGN R
		{ 0xA952, 0xA953, Category::SpacingMark },	// REJANG CONSONANT SIGN H..REJANG VIRAMA
		{ 0xA954, 0xA95E, Category::Unassigned },	// <reserved-A954>..<reserved-A95E>
		{ 0xA95F, 0xA95F, Category::OtherPunctuation },	// REJANG SECTION MARK
		{ 0xA960, 0xA97C, Category::OtherLetter },	// HANGUL CHOSEONG TIKEUT-MIEUM..HANGUL CHOSEONG SSANGYEORINHIEUH
		{ 0xA97D, 0xA97F, Category::Unassigned },	// <reserved-A97D>..<reserved-A97F>
		{ 0xA980, 0xA982, Category::NonspacingMark },	// JAVANESE SIGN PANYANGGA..JAVANESE SIGN LAYAR
		{ 0xA983, 0xA983, Category::SpacingMark },	// JAVANESE SIGN WIGNYAN
		{ 0xA984, 0xA9B2, Category::OtherLetter },	// JAVANESE LETTER A..JAVANESE LETTER HA
		{ 0xA9B3, 0xA9B3, Category::NonspacingMark },	// JAVANESE SIGN CECAK TELU
		{ 0xA9B4, 0xA9B5, Category::SpacingMark },	// JAVANESE VOWEL SIGN TARUNG..JAVANESE VOWEL SIGN TOLONG
		{ 0xA9B6, 0xA9B9, Category::NonspacingMark },	// JAVANESE VOWEL SIGN WULU..JAVANESE VOWEL SIGN SUKU MENDUT
		{ 0xA9BA, 0xA9BB, Category::SpacingMark },	// JAVANESE VOWEL SIGN TALING..JAVANESE VOWEL SIGN DIRGA MURE
		{ 0xA9BC, 0xA9BD, Category::NonspacingMark },	// JAVANESE VOWEL SIGN PEPET..JAVANESE CONSONANT SIGN KERET
		{ 0xA9BE, 0xA9C0, Category::SpacingMark },	// JAVANESE CONSONANT SIGN PENGKAL..JAVANESE PANGKON
		{ 0xA9C1, 0xA9CD, Category::OtherPunctuation },	// JAVANESE LEFT RERENGGAN..JAVANESE TURNED PADA PISELEH
		{ 0xA9CE, 0xA9CE, Category::Unassigned },	// <reserved-A9CE>
		{ 0xA9CF, 0xA9CF, Category::ModifierLetter },	// JAVANESE PANGRANGKEP
		{ 0xA9D0, 0xA9D9, Category::DecimalNumber },	// JAVANESE DIGIT ZERO..JAVANESE DIGIT NINE
		{ 0xA9DA, 0xA9DD, Category::Unassigned },	// <reserved-A9DA>..<reserved-A9DD>
		{ 0xA9DE, 0xA9DF, Category::OtherPunctuation },	// JAVANESE PADA TIRTA TUMETES..JAVANESE PADA ISEN-ISEN
		{ 0xA9E0, 0xA9E4, Category::OtherLetter },	// MYANMAR LETTER SHAN GHA..MYANMAR LETTER SHAN BHA
		{ 0xA9E5, 0xA9E5, Category::NonspacingMark },	// MYANMAR SIGN SHAN SAW
		{ 0xA9E6, 0xA9E6, Category::ModifierLetter },	// MYANMAR MODIFIER LETTER SHAN REDUPLICATION
		{ 0xA9E7, 0xA9EF, Category::OtherLetter },	// MYANMAR LETTER TAI LAING NYA..MYANMAR LETTER TAI LAING NNA
		{ 0xA9F0, 0xA9F9, Category::DecimalNumber },	// MYANMAR TAI LAING DIGIT ZERO..MYANMAR TAI LAING DIGIT NINE
		{ 0xA9FA, 0xA9FE, Category::OtherLetter },	// MYANMAR LETTER TAI LAING LLA..MYANMAR LETTER TAI LAING BHA
		{ 0xA9FF, 0xA9FF, Category::Unassigned },	// <reserved-A9FF>
		{ 0xAA00, 0xAA28, Category::OtherLetter },	// CHAM LETTER A..CHAM LETTER HA
		{ 0xAA29, 0xAA2E, Category::NonspacingMark },	// CHAM VOWEL SIGN AA..CHAM VOWEL SIGN OE
		{ 0xAA2F, 0xAA30, Category::SpacingMark },	// CHAM VOWEL SIGN O..CHAM VOWEL SIGN AI
		{ 0xAA31, 0xAA32, Category::NonspacingMark },	// CHAM VOWEL SIGN AU..CHAM VOWEL SIGN UE
		{ 0xAA33, 0xAA34, Category::SpacingMark },	// CHAM CONSONANT SIGN YA..CHAM CONSONANT SIGN RA
		{ 0xAA35, 0xAA36, Category::NonspacingMark },	// CHAM CONSONANT SIGN LA..CHAM CONSONANT SIGN WA
		{ 0xAA37, 0xAA3F, Category::Unassigned },	// <reserved-AA37>..<reserved-AA3F>
		{ 0xAA40, 0xAA42, Category::OtherLetter },	// CHAM LETTER FINAL K..CHAM LETTER FINAL NG
		{ 0xAA43, 0xAA43, Category::NonspacingMark },	// CHAM CONSONANT SIGN FINAL NG
		{ 0xAA44, 0xAA4B, Category::OtherLetter },	// CHAM LETTER FINAL CH..CHAM LETTER FINAL SS
		{ 0xAA4C, 0xAA4C, Category::NonspacingMark },	// CHAM CONSONANT SIGN FINAL M
		{ 0xAA4D, 0xAA4D, Category::SpacingMark },	// CHAM CONSONANT SIGN FINAL H
		{ 0xAA4E, 0xAA4F, Category::Unassigned },	// <reserved-AA4E>..<reserved-AA4F>
		{ 0xAA50, 0xAA59, Category::DecimalNumber },	// CHAM DIGIT ZERO..CHAM DIGIT NINE
		{ 0xAA5A, 0xAA5B, Category::Unassigned },	// <reserved-AA5A>..<reserved-AA5B>
		{ 0xAA5C, 0xAA5F, Category::OtherPunctuation },	// CHAM PUNCTUATION SPIRAL..CHAM PUNCTUATION TRIPLE DANDA
		{ 0xAA60, 0xAA6F, Category::OtherLetter },	// MYANMAR LETTER KHAMTI GA..MYANMAR LETTER KHAMTI FA
		{ 0xAA70, 0xAA70, Category::ModifierLetter },	// MYANMAR MODIFIER LETTER KHAMTI REDUPLICATION
		{ 0xAA71, 0xAA76, Category::OtherLetter },	// MYANMAR LETTER KHAMTI XA..MYANMAR LOGOGRAM KHAMTI HM
		{ 0xAA77, 0xAA79, Category::OtherSymbol },	// MYANMAR SYMBOL AITON EXCLAMATION..MYANMAR SYMBOL AITON TWO
		{ 0xAA7A, 0xAA7A, Category::OtherLetter },	// MYANMAR LETTER AITON RA
		{ 0xAA7B, 0xAA7B, Category::SpacingMark },	// MYANMAR SIGN PAO KAREN TONE
		{ 0xAA7C, 0xAA7C, Category::NonspacingMark },	// MYANMAR SIGN TAI LAING TONE-2
		{ 0xAA7D, 0xAA7D, Category::SpacingMark },	// MYANMAR SIGN TAI LAING TONE-5
		{ 0xAA7E, 0xAAAF, Category::OtherLetter },	// MYANMAR LETTER SHWE PALAUNG CHA..TAI VIET LETTER HIGH O
		{ 0xAAB0, 0xAAB0, Category::NonspacingMark },	// TAI VIET MAI KANG
		{ 0xAAB1, 0xAAB1, Category::OtherLetter },	// TAI VIET VOWEL AA
		{ 0xAAB2, 0xAAB4, Category::NonspacingMark },	// TAI VIET VOWEL I..TAI VIET VOWEL U
		{ 0xAAB5, 0xAAB6, Category::OtherLetter },	// TAI VIET VOWEL E..TAI VIET VOWEL O
		{ 0xAAB7, 0xAAB8, Category::NonspacingMark },	// TAI VIET MAI KHIT..TAI VIET VOWEL IA
		{ 0xAAB9, 0xAABD, Category::OtherLetter },	// TAI VIET VOWEL UEA..TAI VIET VOWEL AN
		{ 0xAABE, 0xAABF, Category::NonspacingMark },	// TAI VIET VOWEL AM..TAI VIET TONE MAI EK
		{ 0xAAC0, 0xAAC0, Category::OtherLetter },	// TAI VIET TONE MAI NUENG
		{ 0xAAC1, 0xAAC1, Category::NonspacingMark },	// TAI VIET TONE MAI THO
		{ 0xAAC2, 0xAAC2, Category::OtherLetter },	// TAI VIET TONE MAI SONG
		{ 0xAAC3, 0xAADA, Category::Unassigned },	// <reserved-AAC3>..<reserved-AADA>
		{ 0xAADB, 0xAADC, Category::OtherLetter },	// TAI VIET SYMBOL KON..TAI VIET SYMBOL NUENG
		{ 0xAADD, 0xAADD, Category::ModifierLetter },	// TAI VIET SYMBOL SAM
		{ 0xAADE, 0xAADF, Category::OtherPunctuation },	// TAI VIET SYMBOL HO HOI..TAI VIET SYMBOL KOI KOI
		{ 0xAAE0, 0xAAEA, Category::OtherLetter },	// MEETEI MAYEK LETTER E..MEETEI MAYEK LETTER SSA
		{ 0xAAEB, 0xAAEB, Category::SpacingMark },	// MEETEI MAYEK VOWEL SIGN II
		{ 0xAAEC, 0xAAED, Category::NonspacingMark },	// MEETEI MAYEK VOWEL SIGN UU..MEETEI MAYEK VOWEL SIGN AAI
		{ 0xAAEE, 0xAAEF, Category::SpacingMark },	// MEETEI MAYEK VOWEL SIGN AU..MEETEI MAYEK VOWEL SIGN AAU
		{ 0xAAF0, 0xAAF1, Category::OtherPunctuation },	// MEETEI MAYEK CHEIKHAN..MEETEI MAYEK AHANG KHUDAM
		{ 0xAAF2, 0xAAF2, Category::OtherLetter },	// MEETEI MAYEK ANJI
		{ 0xAAF3, 0xAAF4, Category::ModifierLetter },	// MEETEI MAYEK SYLLABLE REPETITION MARK..MEETEI MAYEK WORD REPETITION MARK
		{ 0xAAF5, 0xAAF5, Category::SpacingMark },	// MEETEI MAYEK VOWEL SIGN VISARGA
		{ 0xAAF6, 0xAAF6, Category::NonspacingMark },	// MEETEI MAYEK VIRAMA
		{ 0xAAF7, 0xAB00, Category::Unassigned },	// <reserved-AAF7>..<reserved-AB00>
		{ 0xAB01, 0xAB06, Category::OtherLetter },	// ETHIOPIC SYLLABLE TTHU..ETHIOPIC SYLLABLE TTHO
		{ 0xAB07, 0xAB08, Category::Unassigned },	// <reserved-AB07>..<reserved-AB08>
		{ 0xAB09, 0xAB0E, Category::OtherLetter },	// ETHIOPIC SYLLABLE DDHU..ETHIOPIC SYLLABLE DDHO
		{ 0xAB0F, 0xAB10, Category::Unassigned },	// <reserved-AB0F>..<reserved-AB10>
		{ 0xAB11, 0xAB16, Category::OtherLetter },	// ETHIOPIC SYLLABLE DZU..ETHIOPIC SYLLABLE DZO
		{ 0xAB17, 0xAB1F, Category::Unassigned },	// <reserved-AB17>..<reserved-AB1F>
		{ 0xAB20, 0xAB26, Category::OtherLetter },	// ETHIOPIC SYLLABLE CCHHA..ETHIOPIC SYLLABLE CCHHO
		{ 0xAB27, 0xAB27, Category::Unassigned },	// <reserved-AB27>
		{ 0xAB28, 0xAB2E, Category::OtherLetter },	// ETHIOPIC SYLLABLE BBA..ETHIOPIC SYLLABLE BBO
		{ 0xAB2F, 0xAB2F, Category::Unassigned },	// <reserved-AB2F>
		{ 0xAB30, 0xAB5A, Category::LowercaseLetter },	// LATIN SMALL LETTER BARRED ALPHA..LATIN SMALL LETTER Y WITH SHORT RIGHT LEG
		{ 0xAB5B, 0xAB5B, Category::ModifierSymbol },	// MODIFIER BREVE WITH INVERTED BREVE
		{ 0xAB5C, 0xAB5F, Category::ModifierLetter },	// MODIFIER LETTER SMALL HENG..MODIFIER LETTER SMALL U WITH LEFT HOOK
		{ 0xAB60, 0xAB68, Category::LowercaseLetter },	// LATIN SMALL LETTER SAKHA YAT..LATIN SMALL LETTER TURNED R WITH MIDDLE TILDE
		{ 0xAB69, 0xAB69, Category::ModifierLetter },	// MODIFIER LETTER SMALL TURNED W
		{ 0xAB6A, 0xAB6B, Category::ModifierSymbol },	// MODIFIER LETTER LEFT TACK..MODIFIER LETTER RIGHT TACK
		{ 0xAB6C, 0xAB6F, Category::Unassigned },	// <reserved-AB6C>..<reserved-AB6F>
		{ 0xAB70, 0xABBF, Category::LowercaseLetter },	// CHEROKEE SMALL LETTER A..CHEROKEE SMALL LETTER YA
		{ 0xABC0, 0xABE2, Category::OtherLetter },	// MEETEI MAYEK LETTER KOK..MEETEI MAYEK LETTER I LONSUM
		{ 0xABE3, 0xABE4, Category::SpacingMark },	// MEETEI MAYEK VOWEL SIGN ONAP..MEETEI MAYEK VOWEL SIGN INAP
		{ 0xABE5, 0xABE5, Category::NonspacingMark },	// MEETEI MAYEK VOWEL SIGN ANAP
		{ 0xABE6, 0xABE7, Category::SpacingMark },	// MEETEI MAYEK VOWEL SIGN YENAP..MEETEI MAYEK VOWEL SIGN SOUNAP
		{ 0xABE8, 0xABE8, Category::NonspacingMark },	// MEETEI MAYEK VOWEL SIGN UNAP
		{ 0xABE9, 0xABEA, Category::SpacingMark },	// MEETEI MAYEK VOWEL SIGN CHEINAP..MEETEI MAYEK VOWEL SIGN NUNG
		{ 0xABEB, 0xABEB, Category::OtherPunctuation },	// MEETEI MAYEK CHEIKHEI
		{ 0xABEC, 0xABEC, Category::SpacingMark },	// MEETEI MAYEK LUM IYEK
		{ 0xABED, 0xABED, Category::NonspacingMark },	// MEETEI MAYEK APUN IYEK
		{ 0xABEE, 0xABEF, Category::Unassigned },	// <reserved-ABEE>..<reserved-ABEF>
		{ 0xABF0, 0xABF9, Category::DecimalNumber },	// MEETEI MAYEK DIGIT ZERO..MEETEI MAYEK DIGIT NINE
		{ 0xABFA, 0xABFF, Category::Unassigned },	// <reserved-ABFA>..<reserved-ABFF>
		{ 0xAC00, 0xD7A3, Category::OtherLetter },	// HANGUL SYLLABLE GA..HANGUL SYLLABLE HIH
		{ 0xD7A4, 0xD7AF, Category::Unassigned },	// <reserved-D7A4>..<reserved-D7AF>
		{ 0xD7B0, 0xD7C6, Category::OtherLetter },	// HANGUL JUNGSEONG O-YEO..HANGUL JUNGSEONG ARAEA-E
		{ 0xD7C7, 0xD7CA, Category::Unassigned },	// <reserved-D7C7>..<reserved-D7CA>
		{ 0xD7CB, 0xD7FB, Category::OtherLetter },	// HANGUL JONGSEONG NIEUN-RIEUL..HANGUL JONGSEONG PHIEUPH-THIEUTH
		{ 0xD7FC, 0xD7FF, Category::Unassigned },	// <reserved-D7FC>..<reserved-D7FF>
		{ 0xD800, 0xDFFF, Category::Surrogate },	// <surrogate-D800>..<surrogate-DFFF>
		{ 0xE000, 0xF8FF, Category::PrivateUse },	// <private-use-E000>..<private-use-F8FF>
		{ 0xF900, 0xFA6D, Category::OtherLetter },	// CJK COMPATIBILITY IDEOGRAPH-F900..CJK COMPATIBILITY IDEOGRAPH-FA6D
		{ 0xFA6E, 0xFA6F, Category::Unassigned },	// <reserved-FA6E>..<reserved-FA6F>
		{ 0xFA70, 0xFAD9, Category::OtherLetter },	// CJK COMPATIBILITY IDEOGRAPH-FA70..CJK COMPATIBILITY IDEOGRAPH-FAD9
		{ 0xFADA, 0xFAFF, Category::Unassigned },	// <reserved-FADA>..<reserved-FAFF>
		{ 0xFB00, 0xFB06, Category::LowercaseLetter },	// LATIN SMALL LIGATURE FF..LATIN SMALL LIGATURE ST
		{ 0xFB07, 0xFB12, Category::Unassigned },	// <reserved-FB07>..<reserved-FB12>
		{ 0xFB13, 0xFB17, Category::LowercaseLetter },	// ARMENIAN SMALL LIGATURE MEN NOW..ARMENIAN SMALL LIGATURE MEN XEH
		{ 0xFB18, 0xFB1C, Category::Unassigned },	// <reserved-FB18>..<reserved-FB1C>
		{ 0xFB1D, 0xFB1D, Category::OtherLetter },	// HEBREW LETTER YOD WITH HIRIQ
		{ 0xFB1E, 0xFB1E, Category::NonspacingMark },	// HEBREW POINT JUDEO-SPANISH VARIKA
		{ 0xFB1F, 0xFB28, Category::OtherLetter },	// HEBREW LIGATURE YIDDISH YOD YOD PATAH..HEBREW LETTER WIDE TAV
		{ 0xFB29, 0xFB29, Category::MathSymbol },	// HEBREW LETTER ALTERNATIVE PLUS SIGN
		{ 0xFB2A, 0xFB36, Category::OtherLetter },	// HEBREW LETTER SHIN WITH SHIN DOT..HEBREW LETTER ZAYIN WITH DAGESH
		{ 0xFB37, 0xFB37, Category::Unassigned },	// <reserved-FB37>
		{ 0xFB38, 0xFB3C, Category::OtherLetter },	// HEBREW LETTER TET WITH DAGESH..HEBREW LETTER LAMED WITH DAGESH
		{ 0xFB3D, 0xFB3D, Category::Unassigned },	// <reserved-FB3D>
		{ 0xFB3E, 0xFB3E, Category::OtherLetter },	// HEBREW LETTER MEM WITH DAGESH
		{ 0xFB3F, 0xFB3F, Category::Unassigned },	// <reserved-FB3F>
		{ 0xFB40, 0xFB41, Category::OtherLetter },	// HEBREW LETTER NUN WITH DAGESH..HEBREW LETTER SAMEKH WITH DAGESH
		{ 0xFB42, 0xFB42, Category::Unassigned },	// <reserved-FB42>
		{ 0xFB43, 0xFB44, Category::OtherLetter },	// HEBREW LETTER FINAL PE WITH DAGESH..HEBREW LETTER PE WITH DAGESH
		{ 0xFB45, 0xFB45, Category::Unassigned },	// <reserved-FB45>
		{ 0xFB46, 0xFBB1, Category::OtherLetter },	// HEBREW LETTER TSADI WITH DAGESH..ARABIC LETTER YEH BARREE WITH HAMZA ABOVE FINAL FORM
		{ 0xFBB2, 0xFBC2, Category::ModifierSymbol },	// ARABIC SYMBOL DOT ABOVE..ARABIC SYMBOL WASLA ABOVE
		{ 0xFBC3, 0xFBD2, Category::Unassigned },	// <reserved-FBC3>..<reserved-FBD2>
		{ 0xFBD3, 0xFD3D, Category::OtherLetter },	// ARABIC LETTER NG ISOLATED FORM..ARABIC LIGATURE ALEF WITH FATHATAN ISOLATED FORM
		{ 0xFD3E, 0xFD3E, Category::ClosePunctuation },	// ORNATE LEFT PARENTHESIS
		{ 0xFD3F, 0xFD3F, Category::OpenPunctuation },	// ORNATE RIGHT PARENTHESIS
		{ 0xFD40, 0xFD4F, Category::OtherSymbol },	// ARABIC LIGATURE RAHIMAHU ALLAAH..ARABIC LIGATURE RAHIMAHUM ALLAAH
		{ 0xFD50, 0xFD8F, Category::OtherLetter },	// ARABIC LIGATURE TEH WITH JEEM WITH MEEM INITIAL FORM..ARABIC LIGATURE MEEM WITH KHAH WITH MEEM INITIAL FORM
		{ 0xFD90, 0xFD91, Category::Unassigned },	// <reserved-FD90>..<reserved-FD91>
		{ 0xFD92, 0xFDC7, Category::OtherLetter },	// ARABIC LIGATURE MEEM WITH JEEM WITH KHAH INITIAL FORM..ARABIC LIGATURE NOON WITH JEEM WITH YEH FINAL FORM
		{ 0xFDC8, 0xFDCE, Category::Unassigned },	// <reserved-FDC8>..<reserved-FDCE>
		{ 0xFDCF, 0xFDCF, Category::OtherSymbol },	// ARABIC LIGATURE SALAAMUHU ALAYNAA
		{ 0xFDD0, 0xFDEF, Category::Unassigned },	// <noncharacter-FDD0>..<noncharacter-FDEF>
		{ 0xFDF0, 0xFDFB, Category::OtherLetter },	// ARABIC LIGATURE SALLA USED AS KORANIC STOP SIGN ISOLATED FORM..ARABIC LIGATURE JALLAJALALOUHOU
		{ 0xFDFC, 0xFDFC, Category::CurrencySymbol },	// RIAL SIGN
		{ 0xFDFD, 0xFDFF, Category::OtherSymbol },	// ARABIC LIGATURE BISMILLAH AR-RAHMAN AR-RAHEEM..ARABIC LIGATURE AZZA WA JALL
		{ 0xFE00, 0xFE0F, Category::NonspacingMark },	// VARIATION SELECTOR-1..VARIATION SELECTOR-16
		{ 0xFE10, 0xFE16, Category::OtherPunctuation },	// PRESENTATION FORM FOR VERTICAL COMMA..PRESENTATION FORM FOR VERTICAL QUESTION MARK
		{ 0xFE17, 0xFE17, Category::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT WHITE LENTICULAR BRACKET
		{ 0xFE18, 0xFE18, Category::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT WHITE LENTICULAR BRAKCET
		{ 0xFE19, 0xFE19, Category::OtherPunctuation },	// PRESENTATION FORM FOR VERTICAL HORIZONTAL ELLIPSIS
		{ 0xFE1A, 0xFE1F, Category::Unassigned },	// <reserved-FE1A>..<reserved-FE1F>
		{ 0xFE20, 0xFE2F, Category::NonspacingMark },	// COMBINING LIGATURE LEFT HALF..COMBINING CYRILLIC TITLO RIGHT HALF
		{ 0xFE30, 0xFE30, Category::OtherPunctuation },	// PRESENTATION FORM FOR VERTICAL TWO DOT LEADER
		{ 0xFE31, 0xFE32, Category::DashPunctuation },	// PRESENTATION FORM FOR VERTICAL EM DASH..PRESENTATION FORM FOR VERTICAL EN DASH
		{ 0xFE33, 0xFE34, Category::ConnectorPunctuation },	// PRESENTATION FORM FOR VERTICAL LOW LINE..PRESENTATION FORM FOR VERTICAL WAVY LOW LINE
		{ 0xFE35, 0xFE35, Category::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT PARENTHESIS
		{ 0xFE36, 0xFE36, Category::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT PARENTHESIS
		{ 0xFE37, 0xFE37, Category::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT CURLY BRACKET
		{ 0xFE38, 0xFE38, Category::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT CURLY BRACKET
		{ 0xFE39, 0xFE39, Category::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT TORTOISE SHELL BRACKET
		{ 0xFE3A, 0xFE3A, Category::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT TORTOISE SHELL BRACKET
		{ 0xFE3B, 0xFE3B, Category::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT BLACK LENTICULAR BRACKET
		{ 0xFE3C, 0xFE3C, Category::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT BLACK LENTICULAR BRACKET
		{ 0xFE3D, 0xFE3D, Category::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT DOUBLE ANGLE BRACKET
		{ 0xFE3E, 0xFE3E, Category::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT DOUBLE ANGLE BRACKET
		{ 0xFE3F, 0xFE3F, Category::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT ANGLE BRACKET
		{ 0xFE40, 0xFE40, Category::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT ANGLE BRACKET
		{ 0xFE41, 0xFE41, Category::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT CORNER BRACKET
		{ 0xFE42, 0xFE42, Category::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT CORNER BRACKET
		{ 0xFE43, 0xFE43, Category::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT WHITE CORNER BRACKET
		{ 0xFE44, 0xFE44, Category::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT WHITE CORNER BRACKET
		{ 0xFE45, 0xFE46, Category::OtherPunctuation },	// SESAME DOT..WHITE SESAME DOT
		{ 0xFE47, 0xFE47, Category::OpenPunctuation },	// PRESENTATION FORM FOR VERTICAL LEFT SQUARE BRACKET
		{ 0xFE48, 0xFE48, Category::ClosePunctuation },	// PRESENTATION FORM FOR VERTICAL RIGHT SQUARE BRACKET
		{ 0xFE49, 0xFE4C, Category::OtherPunctuation },	// DASHED OVERLINE..DOUBLE WAVY OVERLINE
		{ 0xFE4D, 0xFE4F, Category::ConnectorPunctuation },	// DASHED LOW LINE..WAVY LOW LINE
		{ 0xFE50, 0xFE52, Category::OtherPunctuation },	// SMALL COMMA..SMALL FULL STOP
		{ 0xFE53, 0xFE53, Category::Unassigned },	// <reserved-FE53>
		{ 0xFE54, 0xFE57, Category::OtherPunctuation },	// SMALL SEMICOLON..SMALL EXCLAMATION MARK
		{ 0xFE58, 0xFE58, Category::DashPunctuation },	// SMALL EM DASH
		{ 0xFE59, 0xFE59, Category::OpenPunctuation },	// SMALL LEFT PARENTHESIS
		{ 0xFE5A, 0xFE5A, Category::ClosePunctuation },	// SMALL RIGHT PARENTHESIS
		{ 0xFE5B, 0xFE5B, Category::OpenPunctuation },	// SMALL LEFT CURLY BRACKET
		{ 0xFE5C, 0xFE5C, Category::ClosePunctuation },	// SMALL RIGHT CURLY BRACKET
		{ 0xFE5D, 0xFE5D, Category::OpenPunctuation },	// SMALL LEFT TORTOISE SHELL BRACKET
		{ 0xFE5E, 0xFE5E, Category::ClosePunctuation },	// SMALL RIGHT TORTOISE SHELL BRACKET
		{ 0xFE5F, 0xFE61, Category::OtherPunctuation },	// SMALL NUMBER SIGN..SMALL ASTERISK
		{ 0xFE62, 0xFE62, Category::MathSymbol },	// SMALL PLUS SIGN
		{ 0xFE63, 0xFE63, Category::DashPunctuation },	// SMALL HYPHEN-MINUS
		{ 0xFE64, 0xFE66, Category::MathSymbol },	// SMALL LESS-THAN SIGN..SMALL EQUALS SIGN
		{ 0xFE67, 0xFE67, Category::Unassigned },	// <reserved-FE67>
		{ 0xFE68, 0xFE68, Category::OtherPunctuation },	// SMALL REVERSE SOLIDUS
		{ 0xFE69, 0xFE69, Category::CurrencySymbol },	// SMALL DOLLAR SIGN
		{ 0xFE6A, 0xFE6B, Category::OtherPunctuation },	// SMALL PERCENT SIGN..SMALL COMMERCIAL AT
		{ 0xFE6C, 0xFE6F, Category::Unassigned },	// <reserved-FE6C>..<reserved-FE6F>
		{ 0xFE70, 0xFE74, Category::OtherLetter },	// ARABIC FATHATAN ISOLATED FORM..ARABIC KASRATAN ISOLATED FORM
		{ 0xFE75, 0xFE75, Category::Unassigned },	// <reserved-FE75>
		{ 0xFE76, 0xFEFC, Category::OtherLetter },	// ARABIC FATHA ISOLATED FORM..ARABIC LIGATURE LAM WITH ALEF FINAL FORM
		{ 0xFEFD, 0xFEFE, Category::Unassigned },	// <reserved-FEFD>..<reserved-FEFE>
		{ 0xFEFF, 0xFEFF, Category::Format },	// ZERO WIDTH NO-BREAK SPACE
		{ 0xFF00, 0xFF00, Category::Unassigned },	// <reserved-FF00>
		{ 0xFF01, 0xFF03, Category::OtherPunctuation },	// FULLWIDTH EXCLAMATION MARK..FULLWIDTH NUMBER SIGN
		{ 0xFF04, 0xFF04, Category::CurrencySymbol },	// FULLWIDTH DOLLAR SIGN
		{ 0xFF05, 0xFF07, Category::OtherPunctuation },	// FULLWIDTH PERCENT SIGN..FULLWIDTH APOSTROPHE
		{ 0xFF08, 0xFF08, Category::OpenPunctuation },	// FULLWIDTH LEFT PARENTHESIS
		{ 0xFF09, 0xFF09, Category::ClosePunctuation },	// FULLWIDTH RIGHT PARENTHESIS
		{ 0xFF0A, 0xFF0A, Category::OtherPunctuation },	// FULLWIDTH ASTERISK
		{ 0xFF0B, 0xFF0B, Category::MathSymbol },	// FULLWIDTH PLUS SIGN
		{ 0xFF0C, 0xFF0C, Category::OtherPunctuation },	// FULLWIDTH COMMA
		{ 0xFF0D, 0xFF0D, Category::DashPunctuation },	// FULLWIDTH HYPHEN-MINUS
		{ 0xFF0E, 0xFF0F, Category::OtherPunctuation },	// FULLWIDTH FULL STOP..FULLWIDTH SOLIDUS
		{ 0xFF10, 0xFF19, Category::DecimalNumber },	// FULLWIDTH DIGIT ZERO..FULLWIDTH DIGIT NINE
		{ 0xFF1A, 0xFF1B, Category::OtherPunctuation },	// FULLWIDTH COLON..FULLWIDTH SEMICOLON
		{ 0xFF1C, 0xFF1E, Category::MathSymbol },	// FULLWIDTH LESS-THAN SIGN..FULLWIDTH GREATER-THAN SIGN
		{ 0xFF1F, 0xFF20, Category::OtherPunctuation },	// FULLWIDTH QUESTION MARK..FULLWIDTH COMMERCIAL AT
		{ 0xFF21, 0xFF3A, Category::UppercaseLetter },	// FULLWIDTH LATIN CAPITAL LETTER A..FULLWIDTH LATIN CAPITAL LETTER Z
		{ 0xFF3B, 0xFF3B, Category::OpenPunctuation },	// FULLWIDTH LEFT SQUARE BRACKET
		{ 0xFF3C, 0xFF3C, Category::OtherPunctuation },	// FULLWIDTH REVERSE SOLIDUS
		{ 0xFF3D, 0xFF3D, Category::ClosePunctuation },	// FULLWIDTH RIGHT SQUARE BRACKET
		{ 0xFF3E, 0xFF3E, Category::ModifierSymbol },	// FULLWIDTH CIRCUMFLEX ACCENT
		{ 0xFF3F, 0xFF3F, Category::ConnectorPunctuation },	// FULLWIDTH LOW LINE
		{ 0xFF40, 0xFF40, Category::ModifierSymbol },	// FULLWIDTH GRAVE ACCENT
		{ 0xFF41, 0xFF5A, Category::LowercaseLetter },	// FULLWIDTH LATIN SMALL LETTER A..FULLWIDTH LATIN SMALL LETTER Z
		{ 0xFF5B, 0xFF5B, Category::OpenPunctuation },	// FULLWIDTH LEFT CURLY BRACKET
		{ 0xFF5C, 0xFF5C, Category::MathSymbol },	// FULLWIDTH VERTICAL LINE
		{ 0xFF5D, 0xFF5D, Category::ClosePunctuation },	// FULLWIDTH RIGHT CURLY BRACKET
		{ 0xFF5E, 0xFF5E, Category::MathSymbol },	// FULLWIDTH TILDE
		{ 0xFF5F, 0xFF5F, Category::OpenPunctuation },	// FULLWIDTH LEFT WHITE PARENTHESIS
		{ 0xFF60, 0xFF60, Category::ClosePunctuation },	// FULLWIDTH RIGHT WHITE PARENTHESIS
		{ 0xFF61, 0xFF61, Category::OtherPunctuation },	// HALFWIDTH IDEOGRAPHIC FULL STOP
		{ 0xFF62, 0xFF62, Category::OpenPunctuation },	// HALFWIDTH LEFT CORNER BRACKET
		{ 0xFF63, 0xFF63, Category::ClosePunctuation },	// HALFWIDTH RIGHT CORNER BRACKET
		{ 0xFF64, 0xFF65, Category::OtherPunctuation },	// HALFWIDTH IDEOGRAPHIC COMMA..HALFWIDTH KATAKANA MIDDLE DOT
		{ 0xFF66, 0xFF6F, Category::OtherLetter },	// HALFWIDTH KATAKANA LETTER WO..HALFWIDTH KATAKANA LETTER SMALL TU
		{ 0xFF70, 0xFF70, Category::ModifierLetter },	// HALFWIDTH KATAKANA-HIRAGANA PROLONGED SOUND MARK
		{ 0xFF71, 0xFF9D, Category::OtherLetter },	// HALFWIDTH KATAKANA LETTER A..HALFWIDTH KATAKANA LETTER N
		{ 0xFF9E, 0xFF9F, Category::ModifierLetter },	// HALFWIDTH KATAKANA VOICED SOUND MARK..HALFWIDTH KATAKANA SEMI-VOICED SOUND MARK
		{ 0xFFA0, 0xFFBE, Category::OtherLetter },	// HALFWIDTH HANGUL FILLER..HALFWIDTH HANGUL LETTER HIEUH
		{ 0xFFBF, 0xFFC1, Category::Unassigned },	// <reserved-FFBF>..<reserved-FFC1>
		{ 0xFFC2, 0xFFC7, Category::OtherLetter },	// HALFWIDTH HANGUL LETTER A..HALFWIDTH HANGUL LETTER E
		{ 0xFFC8, 0xFFC9, Category::Unassigned },	// <reserved-FFC8>..<reserved-FFC9>
		{ 0xFFCA, 0xFFCF, Category::OtherLetter },	// HALFWIDTH HANGUL LETTER YEO..HALFWIDTH HANGUL LETTER OE
		{ 0xFFD0, 0xFFD1, Category::Unassigned },	// <reserved-FFD0>..<reserved-FFD1>
		{ 0xFFD2, 0xFFD7, Category::OtherLetter },	// HALFWIDTH HANGUL LETTER YO..HALFWIDTH HANGUL LETTER YU
		{ 0xFFD8, 0xFFD9, Category::Unassigned },	// <reserved-FFD8>..<reserved-FFD9>
		{ 0xFFDA, 0xFFDC, Category::OtherLetter },	// HALFWIDTH HANGUL LETTER EU..HALFWIDTH HANGUL LETTER I
		{ 0xFFDD, 0xFFDF, Category::Unassigned },	// <reserved-FFDD>..<reserved-FFDF>
		{ 0xFFE0, 0xFFE1, Category::CurrencySymbol },	// FULLWIDTH CENT SIGN..FULLWIDTH POUND SIGN
		{ 0xFFE2, 0xFFE2, Category::MathSymbol },	// FULLWIDTH NOT SIGN
		{ 0xFFE3, 0xFFE3, Category::ModifierSymbol },	// FULLWIDTH MACRON
		{ 0xFFE4, 0xFFE4, Category::OtherSymbol },	// FULLWIDTH BROKEN BAR
		{ 0xFFE5, 0xFFE6, Category::CurrencySymbol },	// FULLWIDTH YEN SIGN..FULLWIDTH WON SIGN
		{ 0xFFE7, 0xFFE7, Category::Unassigned },	// <reserved-FFE7>
		{ 0xFFE8, 0xFFE8, Category::OtherSymbol },	// HALFWIDTH FORMS LIGHT VERTICAL
		{ 0xFFE9, 0xFFEC, Category::MathSymbol },	// HALFWIDTH LEFTWARDS ARROW..HALFWIDTH DOWNWARDS ARROW
		{ 0xFFED, 0xFFEE, Category::OtherSymbol },	// HALFWIDTH BLACK SQUARE..HALFWIDTH WHITE CIRCLE
		{ 0xFFEF, 0xFFF8, Category::Unassigned },	// <reserved-FFEF>..<reserved-FFF8>
		{ 0xFFF9, 0xFFFB, Category::Format },	// INTERLINEAR ANNOTATION ANCHOR..INTERLINEAR ANNOTATION TERMINATOR
		{ 0xFFFC, 0xFFFD, Category::OtherSymbol },	// OBJECT REPLACEMENT CHARACTER..REPLACEMENT CHARACTER
		{ 0xFFFE, 0xFFFF, Category::Unassigned },	// <noncharacter-FFFE>..<noncharacter-FFFF>
		{ 0x10000, 0x1000B, Category::OtherLetter },	// LINEAR B SYLLABLE B008 A..LINEAR B SYLLABLE B046 JE
		{ 0x1000C, 0x1000C, Category::Unassigned },	// <reserved-1000C>
		{ 0x1000D, 0x10026, Category::OtherLetter },	// LINEAR B SYLLABLE B036 JO..LINEAR B SYLLABLE B032 QO
		{ 0x10027, 0x10027, Category::Unassigned },	// <reserved-10027>
		{ 0x10028, 0x1003A, Category::OtherLetter },	// LINEAR B SYLLABLE B060 RA..LINEAR B SYLLABLE B042 WO
		{ 0x1003B, 0x1003B, Category::Unassigned },	// <reserved-1003B>
		{ 0x1003C, 0x1003D, Category::OtherLetter },	// LINEAR B SYLLABLE B017 ZA..LINEAR B SYLLABLE B074 ZE
		{ 0x1003E, 0x1003E, Category::Unassigned },	// <reserved-1003E>
		{ 0x1003F, 0x1004D, Category::OtherLetter },	// LINEAR B SYLLABLE B020 ZO..LINEAR B SYLLABLE B091 TWO
		{ 0x1004E, 0x1004F, Category::Unassigned },	// <reserved-1004E>..<reserved-1004F>
		{ 0x10050, 0x1005D, Category::OtherLetter },	// LINEAR B SYMBOL B018..LINEAR B SYMBOL B089
		{ 0x1005E, 0x1007F, Category::Unassigned },	// <reserved-1005E>..<reserved-1007F>
		{ 0x10080, 0x100FA, Category::OtherLetter },	// LINEAR B IDEOGRAM B100 MAN..LINEAR B IDEOGRAM VESSEL B305
		{ 0x100FB, 0x100FF, Category::Unassigned },	// <reserved-100FB>..<reserved-100FF>
		{ 0x10100, 0x10102, Category::OtherPunctuation },	// AEGEAN WORD SEPARATOR LINE..AEGEAN CHECK MARK
		{ 0x10103, 0x10106, Category::Unassigned },	// <reserved-10103>..<reserved-10106>
		{ 0x10107, 0x10133, Category::OtherNumber },	// AEGEAN NUMBER ONE..AEGEAN NUMBER NINETY THOUSAND
		{ 0x10134, 0x10136, Category::Unassigned },	// <reserved-10134>..<reserved-10136>
		{ 0x10137, 0x1013F, Category::OtherSymbol },	// AEGEAN WEIGHT BASE UNIT..AEGEAN MEASURE THIRD SUBUNIT
		{ 0x10140, 0x10174, Category::LetterNumber },	// GREEK ACROPHONIC ATTIC ONE QUARTER..GREEK ACROPHONIC STRATIAN FIFTY MNAS
		{ 0x10175, 0x10178, Category::OtherNumber },	// GREEK ONE HALF SIGN..GREEK THREE QUARTERS SIGN
		{ 0x10179, 0x10189, Category::OtherSymbol },	// GREEK YEAR SIGN..GREEK TRYBLION BASE SIGN
		{ 0x1018A, 0x1018B, Category::OtherNumber },	// GREEK ZERO SIGN..GREEK ONE QUARTER SIGN
		{ 0x1018C, 0x1018E, Category::OtherSymbol },	// GREEK SINUSOID SIGN..NOMISMA SIGN
		{ 0x1018F, 0x1018F, Category::Unassigned },	// <reserved-1018F>
		{ 0x10190, 0x1019C, Category::OtherSymbol },	// ROMAN SEXTANS SIGN..ASCIA SYMBOL
		{ 0x1019D, 0x1019F, Category::Unassigned },	// <reserved-1019D>..<reserved-1019F>
		{ 0x101A0, 0x101A0, Category::OtherSymbol },	// GREEK SYMBOL TAU RHO
		{ 0x101A1, 0x101CF, Category::Unassigned },	// <reserved-101A1>..<reserved-101CF>
		{ 0x101D0, 0x101FC, Category::OtherSymbol },	// PHAISTOS DISC SIGN PEDESTRIAN..PHAISTOS DISC SIGN WAVY BAND
		{ 0x101FD, 0x101FD, Category::NonspacingMark },	// PHAISTOS DISC SIGN COMBINING OBLIQUE STROKE
		{ 0x101FE, 0x1027F, Category::Unassigned },	// <reserved-101FE>..<reserved-1027F>
		{ 0x10280, 0x1029C, Category::OtherLetter },	// LYCIAN LETTER A..LYCIAN LETTER X
		{ 0x1029D, 0x1029F, Category::Unassigned },	// <reserved-1029D>..<reserved-1029F>
		{ 0x102A0, 0x102D0, Category::OtherLetter },	// CARIAN LETTER A..CARIAN LETTER UUU3
		{ 0x102D1, 0x102DF, Category::Unassigned },	// <reserved-102D1>..<reserved-102DF>
		{ 0x102E0, 0x102E0, Category::NonspacingMark },	// COPTIC EPACT THOUSANDS MARK
		{ 0x102E1, 0x102FB, Category::OtherNumber },	// COPTIC EPACT DIGIT ONE..COPTIC EPACT NUMBER NINE HUNDRED
		{ 0x102FC, 0x102FF, Category::Unassigned },	// <reserved-102FC>..<reserved-102FF>
		{ 0x10300, 0x1031F, Category::OtherLetter },	// OLD ITALIC LETTER A..OLD ITALIC LETTER ESS
		{ 0x10320, 0x10323, Category::OtherNumber },	// OLD ITALIC NUMERAL ONE..OLD ITALIC NUMERAL FIFTY
		{ 0x10324, 0x1032C, Category::Unassigned },	// <reserved-10324>..<reserved-1032C>
		{ 0x1032D, 0x10340, Category::OtherLetter },	// OLD ITALIC LETTER YE..GOTHIC LETTER PAIRTHRA
		{ 0x10341, 0x10341, Category::LetterNumber },	// GOTHIC LETTER NINETY
		{ 0x10342, 0x10349, Category::OtherLetter },	// GOTHIC LETTER RAIDA..GOTHIC LETTER OTHAL
		{ 0x1034A, 0x1034A, Category::LetterNumber },	// GOTHIC LETTER NINE HUNDRED
		{ 0x1034B, 0x1034F, Category::Unassigned },	// <reserved-1034B>..<reserved-1034F>
		{ 0x10350, 0x10375, Category::OtherLetter },	// OLD PERMIC LETTER AN..OLD PERMIC LETTER IA
		{ 0x10376, 0x1037A, Category::NonspacingMark },	// COMBINING OLD PERMIC LETTER AN..COMBINING OLD PERMIC LETTER SII
		{ 0x1037B, 0x1037F, Category::Unassigned },	// <reserved-1037B>..<reserved-1037F>
		{ 0x10380, 0x1039D, Category::OtherLetter },	// UGARITIC LETTER ALPA..UGARITIC LETTER SSU
		{ 0x1039E, 0x1039E, Category::Unassigned },	// <reserved-1039E>
		{ 0x1039F, 0x1039F, Category::OtherPunctuation },	// UGARITIC WORD DIVIDER
		{ 0x103A0, 0x103C3, Category::OtherLetter },	// OLD PERSIAN SIGN A..OLD PERSIAN SIGN HA
		{ 0x103C4, 0x103C7, Category::Unassigned },	// <reserved-103C4>..<reserved-103C7>
		{ 0x103C8, 0x103CF, Category::OtherLetter },	// OLD PERSIAN SIGN AURAMAZDAA..OLD PERSIAN SIGN BUUMISH
		{ 0x103D0, 0x103D0, Category::OtherPunctuation },	// OLD PERSIAN WORD DIVIDER
		{ 0x103D1, 0x103D5, Category::LetterNumber },	// OLD PERSIAN NUMBER ONE..OLD PERSIAN NUMBER HUNDRED
		{ 0x103D6, 0x103FF, Category::Unassigned },	// <reserved-103D6>..<reserved-103FF>
		{ 0x10400, 0x10427, Category::UppercaseLetter },	// DESERET CAPITAL LETTER LONG I..DESERET CAPITAL LETTER EW
		{ 0x10428, 0x1044F, Category::LowercaseLetter },	// DESERET SMALL LETTER LONG I..DESERET SMALL LETTER EW
		{ 0x10450, 0x1049D, Category::OtherLetter },	// SHAVIAN LETTER PEEP..OSMANYA LETTER OO
		{ 0x1049E, 0x1049F, Category::Unassigned },	// <reserved-1049E>..<reserved-1049F>
		{ 0x104A0, 0x104A9, Category::DecimalNumber },	// OSMANYA DIGIT ZERO..OSMANYA DIGIT NINE
		{ 0x104AA, 0x104AF, Category::Unassigned },	// <reserved-104AA>..<reserved-104AF>
		{ 0x104B0, 0x104D3, Category::UppercaseLetter },	// OSAGE CAPITAL LETTER A..OSAGE CAPITAL LETTER ZHA
		{ 0x104D4, 0x104D7, Category::Unassigned },	// <reserved-104D4>..<reserved-104D7>
		{ 0x104D8, 0x104FB, Category::LowercaseLetter },	// OSAGE SMALL LETTER A..OSAGE SMALL LETTER ZHA
		{ 0x104FC, 0x104FF, Category::Unassigned },	// <reserved-104FC>..<reserved-104FF>
		{ 0x10500, 0x10527, Category::OtherLetter },	// ELBASAN LETTER A..ELBASAN LETTER KHE
		{ 0x10528, 0x1052F, Category::Unassigned },	// <reserved-10528>..<reserved-1052F>
		{ 0x10530, 0x10563, Category::OtherLetter },	// CAUCASIAN ALBANIAN LETTER ALT..CAUCASIAN ALBANIAN LETTER KIW
		{ 0x10564, 0x1056E, Category::Unassigned },	// <reserved-10564>..<reserved-1056E>
		{ 0x1056F, 0x1056F, Category::OtherPunctuation },	// CAUCASIAN ALBANIAN CITATION MARK
		{ 0x10570, 0x1057A, Category::UppercaseLetter },	// VITHKUQI CAPITAL LETTER A..VITHKUQI CAPITAL LETTER GA
		{ 0x1057B, 0x1057B, Category::Unassigned },	// <reserved-1057B>
		{ 0x1057C, 0x1058A, Category::UppercaseLetter },	// VITHKUQI CAPITAL LETTER HA..VITHKUQI CAPITAL LETTER RE
		{ 0x1058B, 0x1058B, Category::Unassigned },	// <reserved-1058B>
		{ 0x1058C, 0x10592, Category::UppercaseLetter },	// VITHKUQI CAPITAL LETTER SE..VITHKUQI CAPITAL LETTER XE
		{ 0x10593, 0x10593, Category::Unassigned },	// <reserved-10593>
		{ 0x10594, 0x10595, Category::UppercaseLetter },	// VITHKUQI CAPITAL LETTER Y..VITHKUQI CAPITAL LETTER ZE
		{ 0x10596, 0x10596, Category::Unassigned },	// <reserved-10596>
		{ 0x10597, 0x105A1, Category::LowercaseLetter },	// VITHKUQI SMALL LETTER A..VITHKUQI SMALL LETTER GA
		{ 0x105A2, 0x105A2, Category::Unassigned },	// <reserved-105A2>
		{ 0x105A3, 0x105B1, Category::LowercaseLetter },	// VITHKUQI SMALL LETTER HA..VITHKUQI SMALL LETTER RE
		{ 0x105B2, 0x105B2, Category::Unassigned },	// <reserved-105B2>
		{ 0x105B3, 0x105B9, Category::LowercaseLetter },	// VITHKUQI SMALL LETTER SE..VITHKUQI SMALL LETTER XE
		{ 0x105BA, 0x105BA, Category::Unassigned },	// <reserved-105BA>
		{ 0x105BB, 0x105BC, Category::LowercaseLetter },	// VITHKUQI SMALL LETTER Y..VITHKUQI SMALL LETTER ZE
		{ 0x105BD, 0x105BF, Category::Unassigned },	// <reserved-105BD>..<reserved-105BF>
		{ 0x105C0, 0x105F3, Category::OtherLetter },	// TODHRI LETTER A..TODHRI LETTER OO
		{ 0x105F4, 0x105FF, Category::Unassigned },	// <reserved-105F4>..<reserved-105FF>
		{ 0x10600, 0x10736, Category::OtherLetter },	// LINEAR A SIGN AB001..LINEAR A SIGN A664
		{ 0x10737, 0x1073F, Category::Unassigned },	// <reserved-10737>..<reserved-1073F>
		{ 0x10740, 0x10755, Category::OtherLetter },	// LINEAR A SIGN A701 A..LINEAR A SIGN A732 JE
		{ 0x10756, 0x1075F, Category::Unassigned },	// <reserved-10756>..<reserved-1075F>
		{ 0x10760, 0x10767, Category::OtherLetter },	// LINEAR A SIGN A800..LINEAR A SIGN A807
		{ 0x10768, 0x1077F, Category::Unassigned },	// <reserved-10768>..<reserved-1077F>
		{ 0x10780, 0x10785, Category::ModifierLetter },	// MODIFIER LETTER SMALL CAPITAL AA..MODIFIER LETTER SMALL B WITH HOOK
		{ 0x10786, 0x10786, Category::Unassigned },	// <reserved-10786>
		{ 0x10787, 0x107B0, Category::ModifierLetter },	// MODIFIER LETTER SMALL DZ DIGRAPH..MODIFIER LETTER SMALL V WITH RIGHT HOOK
		{ 0x107B1, 0x107B1, Category::Unassigned },	// <reserved-107B1>
		{ 0x107B2, 0x107BA, Category::ModifierLetter },	// MODIFIER LETTER SMALL CAPITAL Y..MODIFIER LETTER SMALL S WITH CURL
		{ 0x107BB, 0x107FF, Category::Unassigned },	// <reserved-107BB>..<reserved-107FF>
		{ 0x10800, 0x10805, Category::OtherLetter },	// CYPRIOT SYLLABLE A..CYPRIOT SYLLABLE JA
		{ 0x10806, 0x10807, Category::Unassigned },	// <reserved-10806>..<reserved-10807>
		{ 0x10808, 0x10808, Category::OtherLetter },	// CYPRIOT SYLLABLE JO
		{ 0x10809, 0x10809, Category::Unassigned },	// <reserved-10809>
		{ 0x1080A, 0x10835, Category::OtherLetter },	// CYPRIOT SYLLABLE KA..CYPRIOT SYLLABLE WO
		{ 0x10836, 0x10836, Category::Unassigned },	// <reserved-10836>
		{ 0x10837, 0x10838, Category::OtherLetter },	// CYPRIOT SYLLABLE XA..CYPRIOT SYLLABLE XE
		{ 0x10839, 0x1083B, Category::Unassigned },	// <reserved-10839>..<reserved-1083B>
		{ 0x1083C, 0x1083C, Category::OtherLetter },	// CYPRIOT SYLLABLE ZA
		{ 0x1083D, 0x1083E, Category::Unassigned },	// <reserved-1083D>..<reserved-1083E>
		{ 0x1083F, 0x10855, Category::OtherLetter },	// CYPRIOT SYLLABLE ZO..IMPERIAL ARAMAIC LETTER TAW
		{ 0x10856, 0x10856, Category::Unassigned },	// <reserved-10856>
		{ 0x10857, 0x10857, Category::OtherPunctuation },	// IMPERIAL ARAMAIC SECTION SIGN
		{ 0x10858, 0x1085F, Category::OtherNumber },	// IMPERIAL ARAMAIC NUMBER ONE..IMPERIAL ARAMAIC NUMBER TEN THOUSAND
		{ 0x10860, 0x10876, Category::OtherLetter },	// PALMYRENE LETTER ALEPH..PALMYRENE LETTER TAW
		{ 0x10877, 0x10878, Category::OtherSymbol },	// PALMYRENE LEFT-POINTING FLEURON..PALMYRENE RIGHT-POINTING FLEURON
		{ 0x10879, 0x1087F, Category::OtherNumber },	// PALMYRENE NUMBER ONE..PALMYRENE NUMBER TWENTY
		{ 0x10880, 0x1089E, Category::OtherLetter },	// NABATAEAN LETTER FINAL ALEPH..NABATAEAN LETTER TAW
		{ 0x1089F, 0x108A6, Category::Unassigned },	// <reserved-1089F>..<reserved-108A6>
		{ 0x108A7, 0x108AF, Category::OtherNumber },	// NABATAEAN NUMBER ONE..NABATAEAN NUMBER ONE HUNDRED
		{ 0x108B0, 0x108DF, Category::Unassigned },	// <reserved-108B0>..<reserved-108DF>
		{ 0x108E0, 0x108F2, Category::OtherLetter },	// HATRAN LETTER ALEPH..HATRAN LETTER QOPH
		{ 0x108F3, 0x108F3, Category::Unassigned },	// <reserved-108F3>
		{ 0x108F4, 0x108F5, Category::OtherLetter },	// HATRAN LETTER SHIN..HATRAN LETTER TAW
		{ 0x108F6, 0x108FA, Category::Unassigned },	// <reserved-108F6>..<reserved-108FA>
		{ 0x108FB, 0x108FF, Category::OtherNumber },	// HATRAN NUMBER ONE..HATRAN NUMBER ONE HUNDRED
		{ 0x10900, 0x10915, Category::OtherLetter },	// PHOENICIAN LETTER ALF..PHOENICIAN LETTER TAU
		{ 0x10916, 0x1091B, Category::OtherNumber },	// PHOENICIAN NUMBER ONE..PHOENICIAN NUMBER THREE
		{ 0x1091C, 0x1091E, Category::Unassigned },	// <reserved-1091C>..<reserved-1091E>
		{ 0x1091F, 0x1091F, Category::OtherPunctuation },	// PHOENICIAN WORD SEPARATOR
		{ 0x10920, 0x10939, Category::OtherLetter },	// LYDIAN LETTER A..LYDIAN LETTER C
		{ 0x1093A, 0x1093E, Category::Unassigned },	// <reserved-1093A>..<reserved-1093E>
		{ 0x1093F, 0x1093F, Category::OtherPunctuation },	// LYDIAN TRIANGULAR MARK
		{ 0x10940, 0x1097F, Category::Unassigned },	// <reserved-10940>..<reserved-1097F>
		{ 0x10980, 0x109B7, Category::OtherLetter },	// MEROITIC HIEROGLYPHIC LETTER A..MEROITIC CURSIVE LETTER DA
		{ 0x109B8, 0x109BB, Category::Unassigned },	// <reserved-109B8>..<reserved-109BB>
		{ 0x109BC, 0x109BD, Category::OtherNumber },	// MEROITIC CURSIVE FRACTION ELEVEN TWELFTHS..MEROITIC CURSIVE FRACTION ONE HALF
		{ 0x109BE, 0x109BF, Category::OtherLetter },	// MEROITIC CURSIVE LOGOGRAM RMT..MEROITIC CURSIVE LOGOGRAM IMN
		{ 0x109C0, 0x109CF, Category::OtherNumber },	// MEROITIC CURSIVE NUMBER ONE..MEROITIC CURSIVE NUMBER SEVENTY
		{ 0x109D0, 0x109D1, Category::Unassigned },	// <reserved-109D0>..<reserved-109D1>
		{ 0x109D2, 0x109FF, Category::OtherNumber },	// MEROITIC CURSIVE NUMBER ONE HUNDRED..MEROITIC CURSIVE FRACTION TEN TWELFTHS
		{ 0x10A00, 0x10A00, Category::OtherLetter },	// KHAROSHTHI LETTER A
		{ 0x10A01, 0x10A03, Category::NonspacingMark },	// KHAROSHTHI VOWEL SIGN I..KHAROSHTHI VOWEL SIGN VOCALIC R
		{ 0x10A04, 0x10A04, Category::Unassigned },	// <reserved-10A04>
		{ 0x10A05, 0x10A06, Category::NonspacingMark },	// KHAROSHTHI VOWEL SIGN E..KHAROSHTHI VOWEL SIGN O
		{ 0x10A07, 0x10A0B, Category::Unassigned },	// <reserved-10A07>..<reserved-10A0B>
		{ 0x10A0C, 0x10A0F, Category::NonspacingMark },	// KHAROSHTHI VOWEL LENGTH MARK..KHAROSHTHI SIGN VISARGA
		{ 0x10A10, 0x10A13, Category::OtherLetter },	// KHAROSHTHI LETTER KA..KHAROSHTHI LETTER GHA
		{ 0x10A14, 0x10A14, Category::Unassigned },	// <reserved-10A14>
		{ 0x10A15, 0x10A17, Category::OtherLetter },	// KHAROSHTHI LETTER CA..KHAROSHTHI LETTER JA
		{ 0x10A18, 0x10A18, Category::Unassigned },	// <reserved-10A18>
		{ 0x10A19, 0x10A35, Category::OtherLetter },	// KHAROSHTHI LETTER NYA..KHAROSHTHI LETTER VHA
		{ 0x10A36, 0x10A37, Category::Unassigned },	// <reserved-10A36>..<reserved-10A37>
		{ 0x10A38, 0x10A3A, Category::NonspacingMark },	// KHAROSHTHI SIGN BAR ABOVE..KHAROSHTHI SIGN DOT BELOW
		{ 0x10A3B, 0x10A3E, Category::Unassigned },	// <reserved-10A3B>..<reserved-10A3E>
		{ 0x10A3F, 0x10A3F, Category::NonspacingMark },	// KHAROSHTHI VIRAMA
		{ 0x10A40, 0x10A48, Category::OtherNumber },	// KHAROSHTHI DIGIT ONE..KHAROSHTHI FRACTION ONE HALF
		{ 0x10A49, 0x10A4F, Category::Unassigned },	// <reserved-10A49>..<reserved-10A4F>
		{ 0x10A50, 0x10A58, Category::OtherPunctuation },	// KHAROSHTHI PUNCTUATION DOT..KHAROSHTHI PUNCTUATION LINES
		{ 0x10A59, 0x10A5F, Category::Unassigned },	// <reserved-10A59>..<reserved-10A5F>
		{ 0x10A60, 0x10A7C, Category::OtherLetter },	// OLD SOUTH ARABIAN LETTER HE..OLD SOUTH ARABIAN LETTER THETH
		{ 0x10A7D, 0x10A7E, Category::OtherNumber },	// OLD SOUTH ARABIAN NUMBER ONE..OLD SOUTH ARABIAN NUMBER FIFTY
		{ 0x10A7F, 0x10A7F, Category::OtherPunctuation },	// OLD SOUTH ARABIAN NUMERIC INDICATOR
		{ 0x10A80, 0x10A9C, Category::OtherLetter },	// OLD NORTH ARABIAN LETTER HEH..OLD NORTH ARABIAN LETTER ZAH
		{ 0x10A9D, 0x10A9F, Category::OtherNumber },	// OLD NORTH ARABIAN NUMBER ONE..OLD NORTH ARABIAN NUMBER TWENTY
		{ 0x10AA0, 0x10ABF, Category::Unassigned },	// <reserved-10AA0>..<reserved-10ABF>
		{ 0x10AC0, 0x10AC7, Category::OtherLetter },	// MANICHAEAN LETTER ALEPH..MANICHAEAN LETTER WAW
		{ 0x10AC8, 0x10AC8, Category::OtherSymbol },	// MANICHAEAN SIGN UD
		{ 0x10AC9, 0x10AE4, Category::OtherLetter },	// MANICHAEAN LETTER ZAYIN..MANICHAEAN LETTER TAW
		{ 0x10AE5, 0x10AE6, Category::NonspacingMark },	// MANICHAEAN ABBREVIATION MARK ABOVE..MANICHAEAN ABBREVIATION MARK BELOW
		{ 0x10AE7, 0x10AEA, Category::Unassigned },	// <reserved-10AE7>..<reserved-10AEA>
		{ 0x10AEB, 0x10AEF, Category::OtherNumber },	// MANICHAEAN NUMBER ONE..MANICHAEAN NUMBER ONE HUNDRED
		{ 0x10AF0, 0x10AF6, Category::OtherPunctuation },	// MANICHAEAN PUNCTUATION STAR..MANICHAEAN PUNCTUATION LINE FILLER
		{ 0x10AF7, 0x10AFF, Category::Unassigned },	// <reserved-10AF7>..<reserved-10AFF>
		{ 0x10B00, 0x10B35, Category::OtherLetter },	// AVESTAN LETTER A..AVESTAN LETTER HE
		{ 0x10B36, 0x10B38, Category::Unassigned },	// <reserved-10B36>..<reserved-10B38>
		{ 0x10B39, 0x10B3F, Category::OtherPunctuation },	// AVESTAN ABBREVIATION MARK..LARGE ONE RING OVER TWO RINGS PUNCTUATION
		{ 0x10B40, 0x10B55, Category::OtherLetter },	// INSCRIPTIONAL PARTHIAN LETTER ALEPH..INSCRIPTIONAL PARTHIAN LETTER TAW
		{ 0x10B56, 0x10B57, Category::Unassigned },	// <reserved-10B56>..<reserved-10B57>
		{ 0x10B58, 0x10B5F, Category::OtherNumber },	// INSCRIPTIONAL PARTHIAN NUMBER ONE..INSCRIPTIONAL PARTHIAN NUMBER ONE THOUSAND
		{ 0x10B60, 0x10B72, Category::OtherLetter },	// INSCRIPTIONAL PAHLAVI LETTER ALEPH..INSCRIPTIONAL PAHLAVI LETTER TAW
		{ 0x10B73, 0x10B77, Category::Unassigned },	// <reserved-10B73>..<reserved-10B77>
		{ 0x10B78, 0x10B7F, Category::OtherNumber },	// INSCRIPTIONAL PAHLAVI NUMBER ONE..INSCRIPTIONAL PAHLAVI NUMBER ONE THOUSAND
		{ 0x10B80, 0x10B91, Category::OtherLetter },	// PSALTER PAHLAVI LETTER ALEPH..PSALTER PAHLAVI LETTER TAW
		{ 0x10B92, 0x10B98, Category::Unassigned },	// <reserved-10B92>..<reserved-10B98>
		{ 0x10B99, 0x10B9C, Category::OtherPunctuation },	// PSALTER PAHLAVI SECTION MARK..PSALTER PAHLAVI FOUR DOTS WITH DOT
		{ 0x10B9D, 0x10BA8, Category::Unassigned },	// <reserved-10B9D>..<reserved-10BA8>
		{ 0x10BA9, 0x10BAF, Category::OtherNumber },	// PSALTER PAHLAVI NUMBER ONE..PSALTER PAHLAVI NUMBER ONE HUNDRED
		{ 0x10BB0, 0x10BFF, Category::Unassigned },	// <reserved-10BB0>..<reserved-10BFF>
		{ 0x10C00, 0x10C48, Category::OtherLetter },	// OLD TURKIC LETTER ORKHON A..OLD TURKIC LETTER ORKHON BASH
		{ 0x10C49, 0x10C7F, Category::Unassigned },	// <reserved-10C49>..<reserved-10C7F>
		{ 0x10C80, 0x10CB2, Category::UppercaseLetter },	// OLD HUNGARIAN CAPITAL LETTER A..OLD HUNGARIAN CAPITAL LETTER US
		{ 0x10CB3, 0x10CBF, Category::Unassigned },	// <reserved-10CB3>..<reserved-10CBF>
		{ 0x10CC0, 0x10CF2, Category::LowercaseLetter },	// OLD HUNGARIAN SMALL LETTER A..OLD HUNGARIAN SMALL LETTER US
		{ 0x10CF3, 0x10CF9, Category::Unassigned },	// <reserved-10CF3>..<reserved-10CF9>
		{ 0x10CFA, 0x10CFF, Category::OtherNumber },	// OLD HUNGARIAN NUMBER ONE..OLD HUNGARIAN NUMBER ONE THOUSAND
		{ 0x10D00, 0x10D23, Category::OtherLetter },	// HANIFI ROHINGYA LETTER A..HANIFI ROHINGYA MARK NA KHONNA
		{ 0x10D24, 0x10D27, Category::NonspacingMark },	// HANIFI ROHINGYA SIGN HARBAHAY..HANIFI ROHINGYA SIGN TASSI
		{ 0x10D28, 0x10D2F, Category::Unassigned },	// <reserved-10D28>..<reserved-10D2F>
		{ 0x10D30, 0x10D39, Category::DecimalNumber },	// HANIFI ROHINGYA DIGIT ZERO..HANIFI ROHINGYA DIGIT NINE
		{ 0x10D3A, 0x10D3F, Category::Unassigned },	// <reserved-10D3A>..<reserved-10D3F>
		{ 0x10D40, 0x10D49, Category::DecimalNumber },	// GARAY DIGIT ZERO..GARAY DIGIT NINE
		{ 0x10D4A, 0x10D4D, Category::OtherLetter },	// GARAY VOWEL SIGN A..GARAY VOWEL SIGN EE
		{ 0x10D4E, 0x10D4E, Category::ModifierLetter },	// GARAY VOWEL LENGTH MARK
		{ 0x10D4F, 0x10D4F, Category::OtherLetter },	// GARAY SUKUN
		{ 0x10D50, 0x10D65, Category::UppercaseLetter },	// GARAY CAPITAL LETTER A..GARAY CAPITAL LETTER OLD NA
		{ 0x10D66, 0x10D68, Category::Unassigned },	// <reserved-10D66>..<reserved-10D68>
		{ 0x10D69, 0x10D6D, Category::NonspacingMark },	// GARAY VOWEL SIGN E..GARAY CONSONANT NASALIZATION MARK
		{ 0x10D6E, 0x10D6E, Category::DashPunctuation },	// GARAY HYPHEN
		{ 0x10D6F, 0x10D6F, Category::ModifierLetter },	// GARAY REDUPLICATION MARK
		{ 0x10D70, 0x10D85, Category::LowercaseLetter },	// GARAY SMALL LETTER A..GARAY SMALL LETTER OLD NA
		{ 0x10D86, 0x10D8D, Category::Unassigned },	// <reserved-10D86>..<reserved-10D8D>
		{ 0x10D8E, 0x10D8F, Category::MathSymbol },	// GARAY PLUS SIGN..GARAY MINUS SIGN
		{ 0x10D90, 0x10E5F, Category::Unassigned },	// <reserved-10D90>..<reserved-10E5F>
		{ 0x10E60, 0x10E7E, Category::OtherNumber },	// RUMI DIGIT ONE..RUMI FRACTION TWO THIRDS
		{ 0x10E7F, 0x10E7F, Category::Unassigned },	// <reserved-10E7F>
		{ 0x10E80, 0x10EA9, Category::OtherLetter },	// YEZIDI LETTER ELIF..YEZIDI LETTER ET
		{ 0x10EAA, 0x10EAA, Category::Unassigned },	// <reserved-10EAA>
		{ 0x10EAB, 0x10EAC, Category::NonspacingMark },	// YEZIDI COMBINING HAMZA MARK..YEZIDI COMBINING MADDA MARK
		{ 0x10EAD, 0x10EAD, Category::DashPunctuation },	// YEZIDI HYPHENATION MARK
		{ 0x10EAE, 0x10EAF, Category::Unassigned },	// <reserved-10EAE>..<reserved-10EAF>
		{ 0x10EB0, 0x10EB1, Category::OtherLetter },	// YEZIDI LETTER LAM WITH DOT ABOVE..YEZIDI LETTER YOT WITH CIRCUMFLEX ABOVE
		{ 0x10EB2, 0x10EC1, Category::Unassigned },	// <reserved-10EB2>..<reserved-10EC1>
		{ 0x10EC2, 0x10EC4, Category::OtherLetter },	// ARABIC LETTER DAL WITH TWO DOTS VERTICALLY BELOW..ARABIC LETTER KAF WITH TWO DOTS VERTICALLY BELOW
		{ 0x10EC5, 0x10EFB, Category::Unassigned },	// <reserved-10EC5>..<reserved-10EFB>
		{ 0x10EFC, 0x10EFF, Category::NonspacingMark },	// ARABIC COMBINING ALEF OVERLAY..ARABIC SMALL LOW WORD MADDA
		{ 0x10F00, 0x10F1C, Category::OtherLetter },	// OLD SOGDIAN LETTER ALEPH..OLD SOGDIAN LETTER FINAL TAW WITH VERTICAL TAIL
		{ 0x10F1D, 0x10F26, Category::OtherNumber },	// OLD SOGDIAN NUMBER ONE..OLD SOGDIAN FRACTION ONE HALF
		{ 0x10F27, 0x10F27, Category::OtherLetter },	// OLD SOGDIAN LIGATURE AYIN-DALETH
		{ 0x10F28, 0x10F2F, Category::Unassigned },	// <reserved-10F28>..<reserved-10F2F>
		{ 0x10F30, 0x10F45, Category::OtherLetter },	// SOGDIAN LETTER ALEPH..SOGDIAN INDEPENDENT SHIN
		{ 0x10F46, 0x10F50, Category::NonspacingMark },	// SOGDIAN COMBINING DOT BELOW..SOGDIAN COMBINING STROKE BELOW
		{ 0x10F51, 0x10F54, Category::OtherNumber },	// SOGDIAN NUMBER ONE..SOGDIAN NUMBER ONE HUNDRED
		{ 0x10F55, 0x10F59, Category::OtherPunctuation },	// SOGDIAN PUNCTUATION TWO VERTICAL BARS..SOGDIAN PUNCTUATION HALF CIRCLE WITH DOT
		{ 0x10F5A, 0x10F6F, Category::Unassigned },	// <reserved-10F5A>..<reserved-10F6F>
		{ 0x10F70, 0x10F81, Category::OtherLetter },	// OLD UYGHUR LETTER ALEPH..OLD UYGHUR LETTER LESH
		{ 0x10F82, 0x10F85, Category::NonspacingMark },	// OLD UYGHUR COMBINING DOT ABOVE..OLD UYGHUR COMBINING TWO DOTS BELOW
		{ 0x10F86, 0x10F89, Category::OtherPunctuation },	// OLD UYGHUR PUNCTUATION BAR..OLD UYGHUR PUNCTUATION FOUR DOTS
		{ 0x10F8A, 0x10FAF, Category::Unassigned },	// <reserved-10F8A>..<reserved-10FAF>
		{ 0x10FB0, 0x10FC4, Category::OtherLetter },	// CHORASMIAN LETTER ALEPH..CHORASMIAN LETTER TAW
		{ 0x10FC5, 0x10FCB, Category::OtherNumber },	// CHORASMIAN NUMBER ONE..CHORASMIAN NUMBER ONE HUNDRED
		{ 0x10FCC, 0x10FDF, Category::Unassigned },	// <reserved-10FCC>..<reserved-10FDF>
		{ 0x10FE0, 0x10FF6, Category::OtherLetter },	// ELYMAIC LETTER ALEPH..ELYMAIC LIGATURE ZAYIN-YODH
		{ 0x10FF7, 0x10FFF, Category::Unassigned },	// <reserved-10FF7>..<reserved-10FFF>
		{ 0x11000, 0x11000, Category::SpacingMark },	// BRAHMI SIGN CANDRABINDU
		{ 0x11001, 0x11001, Category::NonspacingMark },	// BRAHMI SIGN ANUSVARA
		{ 0x11002, 0x11002, Category::SpacingMark },	// BRAHMI SIGN VISARGA
		{ 0x11003, 0x11037, Category::OtherLetter },	// BRAHMI SIGN JIHVAMULIYA..BRAHMI LETTER OLD TAMIL NNNA
		{ 0x11038, 0x11046, Category::NonspacingMark },	// BRAHMI VOWEL SIGN AA..BRAHMI VIRAMA
		{ 0x11047, 0x1104D, Category::OtherPunctuation },	// BRAHMI DANDA..BRAHMI PUNCTUATION LOTUS
		{ 0x1104E, 0x11051, Category::Unassigned },	// <reserved-1104E>..<reserved-11051>
		{ 0x11052, 0x11065, Category::OtherNumber },	// BRAHMI NUMBER ONE..BRAHMI NUMBER ONE THOUSAND
		{ 0x11066, 0x1106F, Category::DecimalNumber },	// BRAHMI DIGIT ZERO..BRAHMI DIGIT NINE
		{ 0x11070, 0x11070, Category::NonspacingMark },	// BRAHMI SIGN OLD TAMIL VIRAMA
		{ 0x11071, 0x11072, Category::OtherLetter },	// BRAHMI LETTER OLD TAMIL SHORT E..BRAHMI LETTER OLD TAMIL SHORT O
		{ 0x11073, 0x11074, Category::NonspacingMark },	// BRAHMI VOWEL SIGN OLD TAMIL SHORT E..BRAHMI VOWEL SIGN OLD TAMIL SHORT O
		{ 0x11075, 0x11075, Category::OtherLetter },	// BRAHMI LETTER OLD TAMIL LLA
		{ 0x11076, 0x1107E, Category::Unassigned },	// <reserved-11076>..<reserved-1107E>
		{ 0x1107F, 0x11081, Category::NonspacingMark },	// BRAHMI NUMBER JOINER..KAITHI SIGN ANUSVARA
		{ 0x11082, 0x11082, Category::SpacingMark },	// KAITHI SIGN VISARGA
		{ 0x11083, 0x110AF, Category::OtherLetter },	// KAITHI LETTER A..KAITHI LETTER HA
		{ 0x110B0, 0x110B2, Category::SpacingMark },	// KAITHI VOWEL SIGN AA..KAITHI VOWEL SIGN II
		{ 0x110B3, 0x110B6, Category::NonspacingMark },	// KAITHI VOWEL SIGN U..KAITHI VOWEL SIGN AI
		{ 0x110B7, 0x110B8, Category::SpacingMark },	// KAITHI VOWEL SIGN O..KAITHI VOWEL SIGN AU
		{ 0x110B9, 0x110BA, Category::NonspacingMark },	// KAITHI SIGN VIRAMA..KAITHI SIGN NUKTA
		{ 0x110BB, 0x110BC, Category::OtherPunctuation },	// KAITHI ABBREVIATION SIGN..KAITHI ENUMERATION SIGN
		{ 0x110BD, 0x110BD, Category::Format },	// KAITHI NUMBER SIGN
		{ 0x110BE, 0x110C1, Category::OtherPunctuation },	// KAITHI SECTION MARK..KAITHI DOUBLE DANDA
		{ 0x110C2, 0x110C2, Category::NonspacingMark },	// KAITHI VOWEL SIGN VOCALIC R
		{ 0x110C3, 0x110CC, Category::Unassigned },	// <reserved-110C3>..<reserved-110CC>
		{ 0x110CD, 0x110CD, Category::Format },	// KAITHI NUMBER SIGN ABOVE
		{ 0x110CE, 0x110CF, Category::Unassigned },	// <reserved-110CE>..<reserved-110CF>
		{ 0x110D0, 0x110E8, Category::OtherLetter },	// SORA SOMPENG LETTER SAH..SORA SOMPENG LETTER MAE
		{ 0x110E9, 0x110EF, Category::Unassigned },	// <reserved-110E9>..<reserved-110EF>
		{ 0x110F0, 0x110F9, Category::DecimalNumber },	// SORA SOMPENG DIGIT ZERO..SORA SOMPENG DIGIT NINE
		{ 0x110FA, 0x110FF, Category::Unassigned },	// <reserved-110FA>..<reserved-110FF>
		{ 0x11100, 0x11102, Category::NonspacingMark },	// CHAKMA SIGN CANDRABINDU..CHAKMA SIGN VISARGA
		{ 0x11103, 0x11126, Category::OtherLetter },	// CHAKMA LETTER AA..CHAKMA LETTER HAA
		{ 0x11127, 0x1112B, Category::NonspacingMark },	// CHAKMA VOWEL SIGN A..CHAKMA VOWEL SIGN UU
		{ 0x1112C, 0x1112C, Category::SpacingMark },	// CHAKMA VOWEL SIGN E
		{ 0x1112D, 0x11134, Category::NonspacingMark },	// CHAKMA VOWEL SIGN AI..CHAKMA MAAYYAA
		{ 0x11135, 0x11135, Category::Unassigned },	// <reserved-11135>
		{ 0x11136, 0x1113F, Category::DecimalNumber },	// CHAKMA DIGIT ZERO..CHAKMA DIGIT NINE
		{ 0x11140, 0x11143, Category::OtherPunctuation },	// CHAKMA SECTION MARK..CHAKMA QUESTION MARK
		{ 0x11144, 0x11144, Category::OtherLetter },	// CHAKMA LETTER LHAA
		{ 0x11145, 0x11146, Category::SpacingMark },	// CHAKMA VOWEL SIGN AA..CHAKMA VOWEL SIGN EI
		{ 0x11147, 0x11147, Category::OtherLetter },	// CHAKMA LETTER VAA
		{ 0x11148, 0x1114F, Category::Unassigned },	// <reserved-11148>..<reserved-1114F>
		{ 0x11150, 0x11172, Category::OtherLetter },	// MAHAJANI LETTER A..MAHAJANI LETTER RRA
		{ 0x11173, 0x11173, Category::NonspacingMark },	// MAHAJANI SIGN NUKTA
		{ 0x11174, 0x11175, Category::OtherPunctuation },	// MAHAJANI ABBREVIATION SIGN..MAHAJANI SECTION MARK
		{ 0x11176, 0x11176, Category::OtherLetter },	// MAHAJANI LIGATURE SHRI
		{ 0x11177, 0x1117F, Category::Unassigned },	// <reserved-11177>..<reserved-1117F>
		{ 0x11180, 0x11181, Category::NonspacingMark },	// SHARADA SIGN CANDRABINDU..SHARADA SIGN ANUSVARA
		{ 0x11182, 0x11182, Category::SpacingMark },	// SHARADA SIGN VISARGA
		{ 0x11183, 0x111B2, Category::OtherLetter },	// SHARADA LETTER A..SHARADA LETTER HA
		{ 0x111B3, 0x111B5, Category::SpacingMark },	// SHARADA VOWEL SIGN AA..SHARADA VOWEL SIGN II
		{ 0x111B6, 0x111BE, Category::NonspacingMark },	// SHARADA VOWEL SIGN U..SHARADA VOWEL SIGN O
		{ 0x111BF, 0x111C0, Category::SpacingMark },	// SHARADA VOWEL SIGN AU..SHARADA SIGN VIRAMA
		{ 0x111C1, 0x111C4, Category::OtherLetter },	// SHARADA SIGN AVAGRAHA..SHARADA OM
		{ 0x111C5, 0x111C8, Category::OtherPunctuation },	// SHARADA DANDA..SHARADA SEPARATOR
		{ 0x111C9, 0x111CC, Category::NonspacingMark },	// SHARADA SANDHI MARK..SHARADA EXTRA SHORT VOWEL MARK
		{ 0x111CD, 0x111CD, Category::OtherPunctuation },	// SHARADA SUTRA MARK
		{ 0x111CE, 0x111CE, Category::SpacingMark },	// SHARADA VOWEL SIGN PRISHTHAMATRA E
		{ 0x111CF, 0x111CF, Category::NonspacingMark },	// SHARADA SIGN INVERTED CANDRABINDU
		{ 0x111D0, 0x111D9, Category::DecimalNumber },	// SHARADA DIGIT ZERO..SHARADA DIGIT NINE
		{ 0x111DA, 0x111DA, Category::OtherLetter },	// SHARADA EKAM
		{ 0x111DB, 0x111DB, Category::OtherPunctuation },	// SHARADA SIGN SIDDHAM
		{ 0x111DC, 0x111DC, Category::OtherLetter },	// SHARADA HEADSTROKE
		{ 0x111DD, 0x111DF, Category::OtherPunctuation },	// SHARADA CONTINUATION SIGN..SHARADA SECTION MARK-2
		{ 0x111E0, 0x111E0, Category::Unassigned },	// <reserved-111E0>
		{ 0x111E1, 0x111F4, Category::OtherNumber },	// SINHALA ARCHAIC DIGIT ONE..SINHALA ARCHAIC NUMBER ONE THOUSAND
		{ 0x111F5, 0x111FF, Category::Unassigned },	// <reserved-111F5>..<reserved-111FF>
		{ 0x11200, 0x11211, Category::OtherLetter },	// KHOJKI LETTER A..KHOJKI LETTER JJA
		{ 0x11212, 0x11212, Category::Unassigned },	// <reserved-11212>
		{ 0x11213, 0x1122B, Category::OtherLetter },	// KHOJKI LETTER NYA..KHOJKI LETTER LLA
		{ 0x1122C, 0x1122E, Category::SpacingMark },	// KHOJKI VOWEL SIGN AA..KHOJKI VOWEL SIGN II
		{ 0x1122F, 0x11231, Category::NonspacingMark },	// KHOJKI VOWEL SIGN U..KHOJKI VOWEL SIGN AI
		{ 0x11232, 0x11233, Category::SpacingMark },	// KHOJKI VOWEL SIGN O..KHOJKI VOWEL SIGN AU
		{ 0x11234, 0x11234, Category::NonspacingMark },	// KHOJKI SIGN ANUSVARA
		{ 0x11235, 0x11235, Category::SpacingMark },	// KHOJKI SIGN VIRAMA
		{ 0x11236, 0x11237, Category::NonspacingMark },	// KHOJKI SIGN NUKTA..KHOJKI SIGN SHADDA
		{ 0x11238, 0x1123D, Category::OtherPunctuation },	// KHOJKI DANDA..KHOJKI ABBREVIATION SIGN
		{ 0x1123E, 0x1123E, Category::NonspacingMark },	// KHOJKI SIGN SUKUN
		{ 0x1123F, 0x11240, Category::OtherLetter },	// KHOJKI LETTER QA..KHOJKI LETTER SHORT I
		{ 0x11241, 0x11241, Category::NonspacingMark },	// KHOJKI VOWEL SIGN VOCALIC R
		{ 0x11242, 0x1127F, Category::Unassigned },	// <reserved-11242>..<reserved-1127F>
		{ 0x11280, 0x11286, Category::OtherLetter },	// MULTANI LETTER A..MULTANI LETTER GA
		{ 0x11287, 0x11287, Category::Unassigned },	// <reserved-11287>
		{ 0x11288, 0x11288, Category::OtherLetter },	// MULTANI LETTER GHA
		{ 0x11289, 0x11289, Category::Unassigned },	// <reserved-11289>
		{ 0x1128A, 0x1128D, Category::OtherLetter },	// MULTANI LETTER CA..MULTANI LETTER JJA
		{ 0x1128E, 0x1128E, Category::Unassigned },	// <reserved-1128E>
		{ 0x1128F, 0x1129D, Category::OtherLetter },	// MULTANI LETTER NYA..MULTANI LETTER BA
		{ 0x1129E, 0x1129E, Category::Unassigned },	// <reserved-1129E>
		{ 0x1129F, 0x112A8, Category::OtherLetter },	// MULTANI LETTER BHA..MULTANI LETTER RHA
		{ 0x112A9, 0x112A9, Category::OtherPunctuation },	// MULTANI SECTION MARK
		{ 0x112AA, 0x112AF, Category::Unassigned },	// <reserved-112AA>..<reserved-112AF>
		{ 0x112B0, 0x112DE, Category::OtherLetter },	// KHUDAWADI LETTER A..KHUDAWADI LETTER HA
		{ 0x112DF, 0x112DF, Category::NonspacingMark },	// KHUDAWADI SIGN ANUSVARA
		{ 0x112E0, 0x112E2, Category::SpacingMark },	// KHUDAWADI VOWEL SIGN AA..KHUDAWADI VOWEL SIGN II
		{ 0x112E3, 0x112EA, Category::NonspacingMark },	// KHUDAWADI VOWEL SIGN U..KHUDAWADI SIGN VIRAMA
		{ 0x112EB, 0x112EF, Category::Unassigned },	// <reserved-112EB>..<reserved-112EF>
		{ 0x112F0, 0x112F9, Category::DecimalNumber },	// KHUDAWADI DIGIT ZERO..KHUDAWADI DIGIT NINE
		{ 0x112FA, 0x112FF, Category::Unassigned },	// <reserved-112FA>..<reserved-112FF>
		{ 0x11300, 0x11301, Category::NonspacingMark },	// GRANTHA SIGN COMBINING ANUSVARA ABOVE..GRANTHA SIGN CANDRABINDU
		{ 0x11302, 0x11303, Category::SpacingMark },	// GRANTHA SIGN ANUSVARA..GRANTHA SIGN VISARGA
		{ 0x11304, 0x11304, Category::Unassigned },	// <reserved-11304>
		{ 0x11305, 0x1130C, Category::OtherLetter },	// GRANTHA LETTER A..GRANTHA LETTER VOCALIC L
		{ 0x1130D, 0x1130E, Category::Unassigned },	// <reserved-1130D>..<reserved-1130E>
		{ 0x1130F, 0x11310, Category::OtherLetter },	// GRANTHA LETTER EE..GRANTHA LETTER AI
		{ 0x11311, 0x11312, Category::Unassigned },	// <reserved-11311>..<reserved-11312>
		{ 0x11313, 0x11328, Category::OtherLetter },	// GRANTHA LETTER OO..GRANTHA LETTER NA
		{ 0x11329, 0x11329, Category::Unassigned },	// <reserved-11329>
		{ 0x1132A, 0x11330, Category::OtherLetter },	// GRANTHA LETTER PA..GRANTHA LETTER RA
		{ 0x11331, 0x11331, Category::Unassigned },	// <reserved-11331>
		{ 0x11332, 0x11333, Category::OtherLetter },	// GRANTHA LETTER LA..GRANTHA LETTER LLA
		{ 0x11334, 0x11334, Category::Unassigned },	// <reserved-11334>
		{ 0x11335, 0x11339, Category::OtherLetter },	// GRANTHA LETTER VA..GRANTHA LETTER HA
		{ 0x1133A, 0x1133A, Category::Unassigned },	// <reserved-1133A>
		{ 0x1133B, 0x1133C, Category::NonspacingMark },	// COMBINING BINDU BELOW..GRANTHA SIGN NUKTA
		{ 0x1133D, 0x1133D, Category::OtherLetter },	// GRANTHA SIGN AVAGRAHA
		{ 0x1133E, 0x1133F, Category::SpacingMark },	// GRANTHA VOWEL SIGN AA..GRANTHA VOWEL SIGN I
		{ 0x11340, 0x11340, Category::NonspacingMark },	// GRANTHA VOWEL SIGN II
		{ 0x11341, 0x11344, Category::SpacingMark },	// GRANTHA VOWEL SIGN U..GRANTHA VOWEL SIGN VOCALIC RR
		{ 0x11345, 0x11346, Category::Unassigned },	// <reserved-11345>..<reserved-11346>
		{ 0x11347, 0x11348, Category::SpacingMark },	// GRANTHA VOWEL SIGN EE..GRANTHA VOWEL SIGN AI
		{ 0x11349, 0x1134A, Category::Unassigned },	// <reserved-11349>..<reserved-1134A>
		{ 0x1134B, 0x1134D, Category::SpacingMark },	// GRANTHA VOWEL SIGN OO..GRANTHA SIGN VIRAMA
		{ 0x1134E, 0x1134F, Category::Unassigned },	// <reserved-1134E>..<reserved-1134F>
		{ 0x11350, 0x11350, Category::OtherLetter },	// GRANTHA OM
		{ 0x11351, 0x11356, Category::Unassigned },	// <reserved-11351>..<reserved-11356>
		{ 0x11357, 0x11357, Category::SpacingMark },	// GRANTHA AU LENGTH MARK
		{ 0x11358, 0x1135C, Category::Unassigned },	// <reserved-11358>..<reserved-1135C>
		{ 0x1135D, 0x11361, Category::OtherLetter },	// GRANTHA SIGN PLUTA..GRANTHA LETTER VOCALIC LL
		{ 0x11362, 0x11363, Category::SpacingMark },	// GRANTHA VOWEL SIGN VOCALIC L..GRANTHA VOWEL SIGN VOCALIC LL
		{ 0x11364, 0x11365, Category::Unassigned },	// <reserved-11364>..<reserved-11365>
		{ 0x11366, 0x1136C, Category::NonspacingMark },	// COMBINING GRANTHA DIGIT ZERO..COMBINING GRANTHA DIGIT SIX
		{ 0x1136D, 0x1136F, Category::Unassigned },	// <reserved-1136D>..<reserved-1136F>
		{ 0x11370, 0x11374, Category::NonspacingMark },	// COMBINING GRANTHA LETTER A..COMBINING GRANTHA LETTER PA
		{ 0x11375, 0x1137F, Category::Unassigned },	// <reserved-11375>..<reserved-1137F>
		{ 0x11380, 0x11389, Category::OtherLetter },	// TULU-TIGALARI LETTER A..TULU-TIGALARI LETTER VOCALIC LL
		{ 0x1138A, 0x1138A, Category::Unassigned },	// <reserved-1138A>
		{ 0x1138B, 0x1138B, Category::OtherLetter },	// TULU-TIGALARI LETTER EE
		{ 0x1138C, 0x1138D, Category::Unassigned },	// <reserved-1138C>..<reserved-1138D>
		{ 0x1138E, 0x1138E, Category::OtherLetter },	// TULU-TIGALARI LETTER AI
		{ 0x1138F, 0x1138F, Category::Unassigned },	// <reserved-1138F>
		{ 0x11390, 0x113B5, Category::OtherLetter },	// TULU-TIGALARI LETTER OO..TULU-TIGALARI LETTER LLLA
		{ 0x113B6, 0x113B6, Category::Unassigned },	// <reserved-113B6>
		{ 0x113B7, 0x113B7, Category::OtherLetter },	// TULU-TIGALARI SIGN AVAGRAHA
		{ 0x113B8, 0x113BA, Category::SpacingMark },	// TULU-TIGALARI VOWEL SIGN AA..TULU-TIGALARI VOWEL SIGN II
		{ 0x113BB, 0x113C0, Category::NonspacingMark },	// TULU-TIGALARI VOWEL SIGN U..TULU-TIGALARI VOWEL SIGN VOCALIC LL
		{ 0x113C1, 0x113C1, Category::Unassigned },	// <reserved-113C1>
		{ 0x113C2, 0x113C2, Category::SpacingMark },	// TULU-TIGALARI VOWEL SIGN EE
		{ 0x113C3, 0x113C4, Category::Unassigned },	// <reserved-113C3>..<reserved-113C4>
		{ 0x113C5, 0x113C5, Category::SpacingMark },	// TULU-TIGALARI VOWEL SIGN AI
		{ 0x113C6, 0x113C6, Category::Unassigned },	// <reserved-113C6>
		{ 0x113C7, 0x113CA, Category::SpacingMark },	// TULU-TIGALARI VOWEL SIGN OO..TULU-TIGALARI SIGN CANDRA ANUNASIKA
		{ 0x113CB, 0x113CB, Category::Unassigned },	// <reserved-113CB>
		{ 0x113CC, 0x113CD, Category::SpacingMark },	// TULU-TIGALARI SIGN ANUSVARA..TULU-TIGALARI SIGN VISARGA
		{ 0x113CE, 0x113CE, Category::NonspacingMark },	// TULU-TIGALARI SIGN VIRAMA
		{ 0x113CF, 0x113CF, Category::SpacingMark },	// TULU-TIGALARI SIGN LOOPED VIRAMA
		{ 0x113D0, 0x113D0, Category::NonspacingMark },	// TULU-TIGALARI CONJOINER
		{ 0x113D1, 0x113D1, Category::OtherLetter },	// TULU-TIGALARI REPHA
		{ 0x113D2, 0x113D2, Category::NonspacingMark },	// TULU-TIGALARI GEMINATION MARK
		{ 0x113D3, 0x113D3, Category::OtherLetter },	// TULU-TIGALARI SIGN PLUTA
		{ 0x113D4, 0x113D5, Category::OtherPunctuation },	// TULU-TIGALARI DANDA..TULU-TIGALARI DOUBLE DANDA
		{ 0x113D6, 0x113D6, Category::Unassigned },	// <reserved-113D6>
		{ 0x113D7, 0x113D8, Category::OtherPunctuation },	// TULU-TIGALARI SIGN OM PUSHPIKA..TULU-TIGALARI SIGN SHRII PUSHPIKA
		{ 0x113D9, 0x113E0, Category::Unassigned },	// <reserved-113D9>..<reserved-113E0>
		{ 0x113E1, 0x113E2, Category::NonspacingMark },	// TULU-TIGALARI VEDIC TONE SVARITA..TULU-TIGALARI VEDIC TONE ANUDATTA
		{ 0x113E3, 0x113FF, Category::Unassigned },	// <reserved-113E3>..<reserved-113FF>
		{ 0x11400, 0x11434, Category::OtherLetter },	// NEWA LETTER A..NEWA LETTER HA
		{ 0x11435, 0x11437, Category::SpacingMark },	// NEWA VOWEL SIGN AA..NEWA VOWEL SIGN II
		{ 0x11438, 0x1143F, Category::NonspacingMark },	// NEWA VOWEL SIGN U..NEWA VOWEL SIGN AI
		{ 0x11440, 0x11441, Category::SpacingMark },	// NEWA VOWEL SIGN O..NEWA VOWEL SIGN AU
		{ 0x11442, 0x11444, Category::NonspacingMark },	// NEWA SIGN VIRAMA..NEWA SIGN ANUSVARA
		{ 0x11445, 0x11445, Category::SpacingMark },	// NEWA SIGN VISARGA
		{ 0x11446, 0x11446, Category::NonspacingMark },	// NEWA SIGN NUKTA
		{ 0x11447, 0x1144A, Category::OtherLetter },	// NEWA SIGN AVAGRAHA..NEWA SIDDHI
		{ 0x1144B, 0x1144F, Category::OtherPunctuation },	// NEWA DANDA..NEWA ABBREVIATION SIGN
		{ 0x11450, 0x11459, Category::DecimalNumber },	// NEWA DIGIT ZERO..NEWA DIGIT NINE
		{ 0x1145A, 0x1145B, Category::OtherPunctuation },	// NEWA DOUBLE COMMA..NEWA PLACEHOLDER MARK
		{ 0x1145C, 0x1145C, Category::Unassigned },	// <reserved-1145C>
		{ 0x1145D, 0x1145D, Category::OtherPunctuation },	// NEWA INSERTION SIGN
		{ 0x1145E, 0x1145E, Category::NonspacingMark },	// NEWA SANDHI MARK
		{ 0x1145F, 0x11461, Category::OtherLetter },	// NEWA LETTER VEDIC ANUSVARA..NEWA SIGN UPADHMANIYA
		{ 0x11462, 0x1147F, Category::Unassigned },	// <reserved-11462>..<reserved-1147F>
		{ 0x11480, 0x114AF, Category::OtherLetter },	// TIRHUTA ANJI..TIRHUTA LETTER HA
		{ 0x114B0, 0x114B2, Category::SpacingMark },	// TIRHUTA VOWEL SIGN AA..TIRHUTA VOWEL SIGN II
		{ 0x114B3, 0x114B8, Category::NonspacingMark },	// TIRHUTA VOWEL SIGN U..TIRHUTA VOWEL SIGN VOCALIC LL
		{ 0x114B9, 0x114B9, Category::SpacingMark },	// TIRHUTA VOWEL SIGN E
		{ 0x114BA, 0x114BA, Category::NonspacingMark },	// TIRHUTA VOWEL SIGN SHORT E
		{ 0x114BB, 0x114BE, Category::SpacingMark },	// TIRHUTA VOWEL SIGN AI..TIRHUTA VOWEL SIGN AU
		{ 0x114BF, 0x114C0, Category::NonspacingMark },	// TIRHUTA SIGN CANDRABINDU..TIRHUTA SIGN ANUSVARA
		{ 0x114C1, 0x114C1, Category::SpacingMark },	// TIRHUTA SIGN VISARGA
		{ 0x114C2, 0x114C3, Category::NonspacingMark },	// TIRHUTA SIGN VIRAMA..TIRHUTA SIGN NUKTA
		{ 0x114C4, 0x114C5, Category::OtherLetter },	// TIRHUTA SIGN AVAGRAHA..TIRHUTA GVANG
		{ 0x114C6, 0x114C6, Category::OtherPunctuation },	// TIRHUTA ABBREVIATION SIGN
		{ 0x114C7, 0x114C7, Category::OtherLetter },	// TIRHUTA OM
		{ 0x114C8, 0x114CF, Category::Unassigned },	// <reserved-114C8>..<reserved-114CF>
		{ 0x114D0, 0x114D9, Category::DecimalNumber },	// TIRHUTA DIGIT ZERO..TIRHUTA DIGIT NINE
		{ 0x114DA, 0x1157F, Category::Unassigned },	// <reserved-114DA>..<reserved-1157F>
		{ 0x11580, 0x115AE, Category::OtherLetter },	// SIDDHAM LETTER A..SIDDHAM LETTER HA
		{ 0x115AF, 0x115B1, Category::SpacingMark },	// SIDDHAM VOWEL SIGN AA..SIDDHAM VOWEL SIGN II
		{ 0x115B2, 0x115B5, Category::NonspacingMark },	// SIDDHAM VOWEL SIGN U..SIDDHAM VOWEL SIGN VOCALIC RR
		{ 0x115B6, 0x115B7, Category::Unassigned },	// <reserved-115B6>..<reserved-115B7>
		{ 0x115B8, 0x115BB, Category::SpacingMark },	// SIDDHAM VOWEL SIGN E..SIDDHAM VOWEL SIGN AU
		{ 0x115BC, 0x115BD, Category::NonspacingMark },	// SIDDHAM SIGN CANDRABINDU..SIDDHAM SIGN ANUSVARA
		{ 0x115BE, 0x115BE, Category::SpacingMark },	// SIDDHAM SIGN VISARGA
		{ 0x115BF, 0x115C0, Category::NonspacingMark },	// SIDDHAM SIGN VIRAMA..SIDDHAM SIGN NUKTA
		{ 0x115C1, 0x115D7, Category::OtherPunctuation },	// SIDDHAM SIGN SIDDHAM..SIDDHAM SECTION MARK WITH CIRCLES AND FOUR ENCLOSURES
		{ 0x115D8, 0x115DB, Category::OtherLetter },	// SIDDHAM LETTER THREE-CIRCLE ALTERNATE I..SIDDHAM LETTER ALTERNATE U
		{ 0x115DC, 0x115DD, Category::NonspacingMark },	// SIDDHAM VOWEL SIGN ALTERNATE U..SIDDHAM VOWEL SIGN ALTERNATE UU
		{ 0x115DE, 0x115FF, Category::Unassigned },	// <reserved-115DE>..<reserved-115FF>
		{ 0x11600, 0x1162F, Category::OtherLetter },	// MODI LETTER A..MODI LETTER LLA
		{ 0x11630, 0x11632, Category::SpacingMark },	// MODI VOWEL SIGN AA..MODI VOWEL SIGN II
		{ 0x11633, 0x1163A, Category::NonspacingMark },	// MODI VOWEL SIGN U..MODI VOWEL SIGN AI
		{ 0x1163B, 0x1163C, Category::SpacingMark },	// MODI VOWEL SIGN O..MODI VOWEL SIGN AU
		{ 0x1163D, 0x1163D, Category::NonspacingMark },	// MODI SIGN ANUSVARA
		{ 0x1163E, 0x1163E, Category::SpacingMark },	// MODI SIGN VISARGA
		{ 0x1163F, 0x11640, Category::NonspacingMark },	// MODI SIGN VIRAMA..MODI SIGN ARDHACANDRA
		{ 0x11641, 0x11643, Category::OtherPunctuation },	// MODI DANDA..MODI ABBREVIATION SIGN
		{ 0x11644, 0x11644, Category::OtherLetter },	// MODI SIGN HUVA
		{ 0x11645, 0x1164F, Category::Unassigned },	// <reserved-11645>..<reserved-1164F>
		{ 0x11650, 0x11659, Category::DecimalNumber },	// MODI DIGIT ZERO..MODI DIGIT NINE
		{ 0x1165A, 0x1165F, Category::Unassigned },	// <reserved-1165A>..<reserved-1165F>
		{ 0x11660, 0x1166C, Category::OtherPunctuation },	// MONGOLIAN BIRGA WITH ORNAMENT..MONGOLIAN TURNED SWIRL BIRGA WITH DOUBLE ORNAMENT
		{ 0x1166D, 0x1167F, Category::Unassigned },	// <reserved-1166D>..<reserved-1167F>
		{ 0x11680, 0x116AA, Category::OtherLetter },	// TAKRI LETTER A..TAKRI LETTER RRA
		{ 0x116AB, 0x116AB, Category::NonspacingMark },	// TAKRI SIGN ANUSVARA
		{ 0x116AC, 0x116AC, Category::SpacingMark },	// TAKRI SIGN VISARGA
		{ 0x116AD, 0x116AD, Category::NonspacingMark },	// TAKRI VOWEL SIGN AA
		{ 0x116AE, 0x116AF, Category::SpacingMark },	// TAKRI VOWEL SIGN I..TAKRI VOWEL SIGN II
		{ 0x116B0, 0x116B5, Category::NonspacingMark },	// TAKRI VOWEL SIGN U..TAKRI VOWEL SIGN AU
		{ 0x116B6, 0x116B6, Category::SpacingMark },	// TAKRI SIGN VIRAMA
		{ 0x116B7, 0x116B7, Category::NonspacingMark },	// TAKRI SIGN NUKTA
		{ 0x116B8, 0x116B8, Category::OtherLetter },	// TAKRI LETTER ARCHAIC KHA
		{ 0x116B9, 0x116B9, Category::OtherPunctuation },	// TAKRI ABBREVIATION SIGN
		{ 0x116BA, 0x116BF, Category::Unassigned },	// <reserved-116BA>..<reserved-116BF>
		{ 0x116C0, 0x116C9, Category::DecimalNumber },	// TAKRI DIGIT ZERO..TAKRI DIGIT NINE
		{ 0x116CA, 0x116CF, Category::Unassigned },	// <reserved-116CA>..<reserved-116CF>
		{ 0x116D0, 0x116E3, Category::DecimalNumber },	// MYANMAR PAO DIGIT ZERO..MYANMAR EASTERN PWO KAREN DIGIT NINE
		{ 0x116E4, 0x116FF, Category::Unassigned },	// <reserved-116E4>..<reserved-116FF>
		{ 0x11700, 0x1171A, Category::OtherLetter },	// AHOM LETTER KA..AHOM LETTER ALTERNATE BA
		{ 0x1171B, 0x1171C, Category::Unassigned },	// <reserved-1171B>..<reserved-1171C>
		{ 0x1171D, 0x1171D, Category::NonspacingMark },	// AHOM CONSONANT SIGN MEDIAL LA
		{ 0x1171E, 0x1171E, Category::SpacingMark },	// AHOM CONSONANT SIGN MEDIAL RA
		{ 0x1171F, 0x1171F, Category::NonspacingMark },	// AHOM CONSONANT SIGN MEDIAL LIGATING RA
		{ 0x11720, 0x11721, Category::SpacingMark },	// AHOM VOWEL SIGN A..AHOM VOWEL SIGN AA
		{ 0x11722, 0x11725, Category::NonspacingMark },	// AHOM VOWEL SIGN I..AHOM VOWEL SIGN UU
		{ 0x11726, 0x11726, Category::SpacingMark },	// AHOM VOWEL SIGN E
		{ 0x11727, 0x1172B, Category::NonspacingMark },	// AHOM VOWEL SIGN AW..AHOM SIGN KILLER
		{ 0x1172C, 0x1172F, Category::Unassigned },	// <reserved-1172C>..<reserved-1172F>
		{ 0x11730, 0x11739, Category::DecimalNumber },	// AHOM DIGIT ZERO..AHOM DIGIT NINE
		{ 0x1173A, 0x1173B, Category::OtherNumber },	// AHOM NUMBER TEN..AHOM NUMBER TWENTY
		{ 0x1173C, 0x1173E, Category::OtherPunctuation },	// AHOM SIGN SMALL SECTION..AHOM SIGN RULAI
		{ 0x1173F, 0x1173F, Category::OtherSymbol },	// AHOM SYMBOL VI
		{ 0x11740, 0x11746, Category::OtherLetter },	// AHOM LETTER CA..AHOM LETTER LLA
		{ 0x11747, 0x117FF, Category::Unassigned },	// <reserved-11747>..<reserved-117FF>
		{ 0x11800, 0x1182B, Category::OtherLetter },	// DOGRA LETTER A..DOGRA LETTER RRA
		{ 0x1182C, 0x1182E, Category::SpacingMark },	// DOGRA VOWEL SIGN AA..DOGRA VOWEL SIGN II
		{ 0x1182F, 0x11837, Category::NonspacingMark },	// DOGRA VOWEL SIGN U..DOGRA SIGN ANUSVARA
		{ 0x11838, 0x11838, Category::SpacingMark },	// DOGRA SIGN VISARGA
		{ 0x11839, 0x1183A, Category::NonspacingMark },	// DOGRA SIGN VIRAMA..DOGRA SIGN NUKTA
		{ 0x1183B, 0x1183B, Category::OtherPunctuation },	// DOGRA ABBREVIATION SIGN
		{ 0x1183C, 0x1189F, Category::Unassigned },	// <reserved-1183C>..<reserved-1189F>
		{ 0x118A0, 0x118BF, Category::UppercaseLetter },	// WARANG CITI CAPITAL LETTER NGAA..WARANG CITI CAPITAL LETTER VIYO
		{ 0x118C0, 0x118DF, Category::LowercaseLetter },	// WARANG CITI SMALL LETTER NGAA..WARANG CITI SMALL LETTER VIYO
		{ 0x118E0, 0x118E9, Category::DecimalNumber },	// WARANG CITI DIGIT ZERO..WARANG CITI DIGIT NINE
		{ 0x118EA, 0x118F2, Category::OtherNumber },	// WARANG CITI NUMBER TEN..WARANG CITI NUMBER NINETY
		{ 0x118F3, 0x118FE, Category::Unassigned },	// <reserved-118F3>..<reserved-118FE>
		{ 0x118FF, 0x11906, Category::OtherLetter },	// WARANG CITI OM..DIVES AKURU LETTER E
		{ 0x11907, 0x11908, Category::Unassigned },	// <reserved-11907>..<reserved-11908>
		{ 0x11909, 0x11909, Category::OtherLetter },	// DIVES AKURU LETTER O
		{ 0x1190A, 0x1190B, Category::Unassigned },	// <reserved-1190A>..<reserved-1190B>
		{ 0x1190C, 0x11913, Category::OtherLetter },	// DIVES AKURU LETTER KA..DIVES AKURU LETTER JA
		{ 0x11914, 0x11914, Category::Unassigned },	// <reserved-11914>
		{ 0x11915, 0x11916, Category::OtherLetter },	// DIVES AKURU LETTER NYA..DIVES AKURU LETTER TTA
		{ 0x11917, 0x11917, Category::Unassigned },	// <reserved-11917>
		{ 0x11918, 0x1192F, Category::OtherLetter },	// DIVES AKURU LETTER DDA..DIVES AKURU LETTER ZA
		{ 0x11930, 0x11935, Category::SpacingMark },	// DIVES AKURU VOWEL SIGN AA..DIVES AKURU VOWEL SIGN E
		{ 0x11936, 0x11936, Category::Unassigned },	// <reserved-11936>
		{ 0x11937, 0x11938, Category::SpacingMark },	// DIVES AKURU VOWEL SIGN AI..DIVES AKURU VOWEL SIGN O
		{ 0x11939, 0x1193A, Category::Unassigned },	// <reserved-11939>..<reserved-1193A>
		{ 0x1193B, 0x1193C, Category::NonspacingMark },	// DIVES AKURU SIGN ANUSVARA..DIVES AKURU SIGN CANDRABINDU
		{ 0x1193D, 0x1193D, Category::SpacingMark },	// DIVES AKURU SIGN HALANTA
		{ 0x1193E, 0x1193E, Category::NonspacingMark },	// DIVES AKURU VIRAMA
		{ 0x1193F, 0x1193F, Category::OtherLetter },	// DIVES AKURU PREFIXED NASAL SIGN
		{ 0x11940, 0x11940, Category::SpacingMark },	// DIVES AKURU MEDIAL YA
		{ 0x11941, 0x11941, Category::OtherLetter },	// DIVES AKURU INITIAL RA
		{ 0x11942, 0x11942, Category::SpacingMark },	// DIVES AKURU MEDIAL RA
		{ 0x11943, 0x11943, Category::NonspacingMark },	// DIVES AKURU SIGN NUKTA
		{ 0x11944, 0x11946, Category::OtherPunctuation },	// DIVES AKURU DOUBLE DANDA..DIVES AKURU END OF TEXT MARK
		{ 0x11947, 0x1194F, Category::Unassigned },	// <reserved-11947>..<reserved-1194F>
		{ 0x11950, 0x11959, Category::DecimalNumber },	// DIVES AKURU DIGIT ZERO..DIVES AKURU DIGIT NINE
		{ 0x1195A, 0x1199F, Category::Unassigned },	// <reserved-1195A>..<reserved-1199F>
		{ 0x119A0, 0x119A7, Category::OtherLetter },	// NANDINAGARI LETTER A..NANDINAGARI LETTER VOCALIC RR
		{ 0x119A8, 0x119A9, Category::Unassigned },	// <reserved-119A8>..<reserved-119A9>
		{ 0x119AA, 0x119D0, Category::OtherLetter },	// NANDINAGARI LETTER E..NANDINAGARI LETTER RRA
		{ 0x119D1, 0x119D3, Category::SpacingMark },	// NANDINAGARI VOWEL SIGN AA..NANDINAGARI VOWEL SIGN II
		{ 0x119D4, 0x119D7, Category::NonspacingMark },	// NANDINAGARI VOWEL SIGN U..NANDINAGARI VOWEL SIGN VOCALIC RR
		{ 0x119D8, 0x119D9, Category::Unassigned },	// <reserved-119D8>..<reserved-119D9>
		{ 0x119DA, 0x119DB, Category::NonspacingMark },	// NANDINAGARI VOWEL SIGN E..NANDINAGARI VOWEL SIGN AI
		{ 0x119DC, 0x119DF, Category::SpacingMark },	// NANDINAGARI VOWEL SIGN O..NANDINAGARI SIGN VISARGA
		{ 0x119E0, 0x119E0, Category::NonspacingMark },	// NANDINAGARI SIGN VIRAMA
		{ 0x119E1, 0x119E1, Category::OtherLetter },	// NANDINAGARI SIGN AVAGRAHA
		{ 0x119E2, 0x119E2, Category::OtherPunctuation },	// NANDINAGARI SIGN SIDDHAM
		{ 0x119E3, 0x119E3, Category::OtherLetter },	// NANDINAGARI HEADSTROKE
		{ 0x119E4, 0x119E4, Category::SpacingMark },	// NANDINAGARI VOWEL SIGN PRISHTHAMATRA E
		{ 0x119E5, 0x119FF, Category::Unassigned },	// <reserved-119E5>..<reserved-119FF>
		{ 0x11A00, 0x11A00, Category::OtherLetter },	// ZANABAZAR SQUARE LETTER A
		{ 0x11A01, 0x11A0A, Category::NonspacingMark },	// ZANABAZAR SQUARE VOWEL SIGN I..ZANABAZAR SQUARE VOWEL LENGTH MARK
		{ 0x11A0B, 0x11A32, Category::OtherLetter },	// ZANABAZAR SQUARE LETTER KA..ZANABAZAR SQUARE LETTER KSSA
		{ 0x11A33, 0x11A38, Category::NonspacingMark },	// ZANABAZAR SQUARE FINAL CONSONANT MARK..ZANABAZAR SQUARE SIGN ANUSVARA
		{ 0x11A39, 0x11A39, Category::SpacingMark },	// ZANABAZAR SQUARE SIGN VISARGA
		{ 0x11A3A, 0x11A3A, Category::OtherLetter },	// ZANABAZAR SQUARE CLUSTER-INITIAL LETTER RA
		{ 0x11A3B, 0x11A3E, Category::NonspacingMark },	// ZANABAZAR SQUARE CLUSTER-FINAL LETTER YA..ZANABAZAR SQUARE CLUSTER-FINAL LETTER VA
		{ 0x11A3F, 0x11A46, Category::OtherPunctuation },	// ZANABAZAR SQUARE INITIAL HEAD MARK..ZANABAZAR SQUARE CLOSING DOUBLE-LINED HEAD MARK
		{ 0x11A47, 0x11A47, Category::NonspacingMark },	// ZANABAZAR SQUARE SUBJOINER
		{ 0x11A48, 0x11A4F, Category::Unassigned },	// <reserved-11A48>..<reserved-11A4F>
		{ 0x11A50, 0x11A50, Category::OtherLetter },	// SOYOMBO LETTER A
		{ 0x11A51, 0x11A56, Category::NonspacingMark },	// SOYOMBO VOWEL SIGN I..SOYOMBO VOWEL SIGN OE
		{ 0x11A57, 0x11A58, Category::SpacingMark },	// SOYOMBO VOWEL SIGN AI..SOYOMBO VOWEL SIGN AU
		{ 0x11A59, 0x11A5B, Category::NonspacingMark },	// SOYOMBO VOWEL SIGN VOCALIC R..SOYOMBO VOWEL LENGTH MARK
		{ 0x11A5C, 0x11A89, Category::OtherLetter },	// SOYOMBO LETTER KA..SOYOMBO CLUSTER-INITIAL LETTER SA
		{ 0x11A8A, 0x11A96, Category::NonspacingMark },	// SOYOMBO FINAL CONSONANT SIGN G..SOYOMBO SIGN ANUSVARA
		{ 0x11A97, 0x11A97, Category::SpacingMark },	// SOYOMBO SIGN VISARGA
		{ 0x11A98, 0x11A99, Category::NonspacingMark },	// SOYOMBO GEMINATION MARK..SOYOMBO SUBJOINER
		{ 0x11A9A, 0x11A9C, Category::OtherPunctuation },	// SOYOMBO MARK TSHEG..SOYOMBO MARK DOUBLE SHAD
		{ 0x11A9D, 0x11A9D, Category::OtherLetter },	// SOYOMBO MARK PLUTA
		{ 0x11A9E, 0x11AA2, Category::OtherPunctuation },	// SOYOMBO HEAD MARK WITH MOON AND SUN AND TRIPLE FLAME..SOYOMBO TERMINAL MARK-2
		{ 0x11AA3, 0x11AAF, Category::Unassigned },	// <reserved-11AA3>..<reserved-11AAF>
		{ 0x11AB0, 0x11AF8, Category::OtherLetter },	// CANADIAN SYLLABICS NATTILIK HI..PAU CIN HAU GLOTTAL STOP FINAL
		{ 0x11AF9, 0x11AFF, Category::Unassigned },	// <reserved-11AF9>..<reserved-11AFF>
		{ 0x11B00, 0x11B09, Category::OtherPunctuation },	// DEVANAGARI HEAD MARK..DEVANAGARI SIGN MINDU
		{ 0x11B0A, 0x11BBF, Category::Unassigned },	// <reserved-11B0A>..<reserved-11BBF>
		{ 0x11BC0, 0x11BE0, Category::OtherLetter },	// SUNUWAR LETTER DEVI..SUNUWAR LETTER KLOKO
		{ 0x11BE1, 0x11BE1, Category::OtherPunctuation },	// SUNUWAR SIGN PVO
		{ 0x11BE2, 0x11BEF, Category::Unassigned },	// <reserved-11BE2>..<reserved-11BEF>
		{ 0x11BF0, 0x11BF9, Category::DecimalNumber },	// SUNUWAR DIGIT ZERO..SUNUWAR DIGIT NINE
		{ 0x11BFA, 0x11BFF, Category::Unassigned },	// <reserved-11BFA>..<reserved-11BFF>
		{ 0x11C00, 0x11C08, Category::OtherLetter },	// BHAIKSUKI LETTER A..BHAIKSUKI LETTER VOCALIC L
		{ 0x11C09, 0x11C09, Category::Unassigned },	// <reserved-11C09>
		{ 0x11C0A, 0x11C2E, Category::OtherLetter },	// BHAIKSUKI LETTER E..BHAIKSUKI LETTER HA
		{ 0x11C2F, 0x11C2F, Category::SpacingMark },	// BHAIKSUKI VOWEL SIGN AA
		{ 0x11C30, 0x11C36, Category::NonspacingMark },	// BHAIKSUKI VOWEL SIGN I..BHAIKSUKI VOWEL SIGN VOCALIC L
		{ 0x11C37, 0x11C37, Category::Unassigned },	// <reserved-11C37>
		{ 0x11C38, 0x11C3D, Category::NonspacingMark },	// BHAIKSUKI VOWEL SIGN E..BHAIKSUKI SIGN ANUSVARA
		{ 0x11C3E, 0x11C3E, Category::SpacingMark },	// BHAIKSUKI SIGN VISARGA
		{ 0x11C3F, 0x11C3F, Category::NonspacingMark },	// BHAIKSUKI SIGN VIRAMA
		{ 0x11C40, 0x11C40, Category::OtherLetter },	// BHAIKSUKI SIGN AVAGRAHA
		{ 0x11C41, 0x11C45, Category::OtherPunctuation },	// BHAIKSUKI DANDA..BHAIKSUKI GAP FILLER-2
		{ 0x11C46, 0x11C4F, Category::Unassigned },	// <reserved-11C46>..<reserved-11C4F>
		{ 0x11C50, 0x11C59, Category::DecimalNumber },	// BHAIKSUKI DIGIT ZERO..BHAIKSUKI DIGIT NINE
		{ 0x11C5A, 0x11C6C, Category::OtherNumber },	// BHAIKSUKI NUMBER ONE..BHAIKSUKI HUNDREDS UNIT MARK
		{ 0x11C6D, 0x11C6F, Category::Unassigned },	// <reserved-11C6D>..<reserved-11C6F>
		{ 0x11C70, 0x11C71, Category::OtherPunctuation },	// MARCHEN HEAD MARK..MARCHEN MARK SHAD
		{ 0x11C72, 0x11C8F, Category::OtherLetter },	// MARCHEN LETTER KA..MARCHEN LETTER A
		{ 0x11C90, 0x11C91, Category::Unassigned },	// <reserved-11C90>..<reserved-11C91>
		{ 0x11C92, 0x11CA7, Category::NonspacingMark },	// MARCHEN SUBJOINED LETTER KA..MARCHEN SUBJOINED LETTER ZA
		{ 0x11CA8, 0x11CA8, Category::Unassigned },	// <reserved-11CA8>
		{ 0x11CA9, 0x11CA9, Category::SpacingMark },	// MARCHEN SUBJOINED LETTER YA
		{ 0x11CAA, 0x11CB0, Category::NonspacingMark },	// MARCHEN SUBJOINED LETTER RA..MARCHEN VOWEL SIGN AA
		{ 0x11CB1, 0x11CB1, Category::SpacingMark },	// MARCHEN VOWEL SIGN I
		{ 0x11CB2, 0x11CB3, Category::NonspacingMark },	// MARCHEN VOWEL SIGN U..MARCHEN VOWEL SIGN E
		{ 0x11CB4, 0x11CB4, Category::SpacingMark },	// MARCHEN VOWEL SIGN O
		{ 0x11CB5, 0x11CB6, Category::NonspacingMark },	// MARCHEN SIGN ANUSVARA..MARCHEN SIGN CANDRABINDU
		{ 0x11CB7, 0x11CFF, Category::Unassigned },	// <reserved-11CB7>..<reserved-11CFF>
		{ 0x11D00, 0x11D06, Category::OtherLetter },	// MASARAM GONDI LETTER A..MASARAM GONDI LETTER E
		{ 0x11D07, 0x11D07, Category::Unassigned },	// <reserved-11D07>
		{ 0x11D08, 0x11D09, Category::OtherLetter },	// MASARAM GONDI LETTER AI..MASARAM GONDI LETTER O
		{ 0x11D0A, 0x11D0A, Category::Unassigned },	// <reserved-11D0A>
		{ 0x11D0B, 0x11D30, Category::OtherLetter },	// MASARAM GONDI LETTER AU..MASARAM GONDI LETTER TRA
		{ 0x11D31, 0x11D36, Category::NonspacingMark },	// MASARAM GONDI VOWEL SIGN AA..MASARAM GONDI VOWEL SIGN VOCALIC R
		{ 0x11D37, 0x11D39, Category::Unassigned },	// <reserved-11D37>..<reserved-11D39>
		{ 0x11D3A, 0x11D3A, Category::NonspacingMark },	// MASARAM GONDI VOWEL SIGN E
		{ 0x11D3B, 0x11D3B, Category::Unassigned },	// <reserved-11D3B>
		{ 0x11D3C, 0x11D3D, Category::NonspacingMark },	// MASARAM GONDI VOWEL SIGN AI..MASARAM GONDI VOWEL SIGN O
		{ 0x11D3E, 0x11D3E, Category::Unassigned },	// <reserved-11D3E>
		{ 0x11D3F, 0x11D45, Category::NonspacingMark },	// MASARAM GONDI VOWEL SIGN AU..MASARAM GONDI VIRAMA
		{ 0x11D46, 0x11D46, Category::OtherLetter },	// MASARAM GONDI REPHA
		{ 0x11D47, 0x11D47, Category::NonspacingMark },	// MASARAM GONDI RA-KARA
		{ 0x11D48, 0x11D4F, Category::Unassigned },	// <reserved-11D48>..<reserved-11D4F>
		{ 0x11D50, 0x11D59, Category::DecimalNumber },	// MASARAM GONDI DIGIT ZERO..MASARAM GONDI DIGIT NINE
		{ 0x11D5A, 0x11D5F, Category::Unassigned },	// <reserved-11D5A>..<reserved-11D5F>
		{ 0x11D60, 0x11D65, Category::OtherLetter },	// GUNJALA GONDI LETTER A..GUNJALA GONDI LETTER UU
		{ 0x11D66, 0x11D66, Category::Unassigned },	// <reserved-11D66>
		{ 0x11D67, 0x11D68, Category::OtherLetter },	// GUNJALA GONDI LETTER EE..GUNJALA GONDI LETTER AI
		{ 0x11D69, 0x11D69, Category::Unassigned },	// <reserved-11D69>
		{ 0x11D6A, 0x11D89, Category::OtherLetter },	// GUNJALA GONDI LETTER OO..GUNJALA GONDI LETTER SA
		{ 0x11D8A, 0x11D8E, Category::SpacingMark },	// GUNJALA GONDI VOWEL SIGN AA..GUNJALA GONDI VOWEL SIGN UU
		{ 0x11D8F, 0x11D8F, Category::Unassigned },	// <reserved-11D8F>
		{ 0x11D90, 0x11D91, Category::NonspacingMark },	// GUNJALA GONDI VOWEL SIGN EE..GUNJALA GONDI VOWEL SIGN AI
		{ 0x11D92, 0x11D92, Category::Unassigned },	// <reserved-11D92>
		{ 0x11D93, 0x11D94, Category::SpacingMark },	// GUNJALA GONDI VOWEL SIGN OO..GUNJALA GONDI VOWEL SIGN AU
		{ 0x11D95, 0x11D95, Category::NonspacingMark },	// GUNJALA GONDI SIGN ANUSVARA
		{ 0x11D96, 0x11D96, Category::SpacingMark },	// GUNJALA GONDI SIGN VISARGA
		{ 0x11D97, 0x11D97, Category::NonspacingMark },	// GUNJALA GONDI VIRAMA
		{ 0x11D98, 0x11D98, Category::OtherLetter },	// GUNJALA GONDI OM
		{ 0x11D99, 0x11D9F, Category::Unassigned },	// <reserved-11D99>..<reserved-11D9F>
		{ 0x11DA0, 0x11DA9, Category::DecimalNumber },	// GUNJALA GONDI DIGIT ZERO..GUNJALA GONDI DIGIT NINE
		{ 0x11DAA, 0x11EDF, Category::Unassigned },	// <reserved-11DAA>..<reserved-11EDF>
		{ 0x11EE0, 0x11EF2, Category::OtherLetter },	// MAKASAR LETTER KA..MAKASAR ANGKA
		{ 0x11EF3, 0x11EF4, Category::NonspacingMark },	// MAKASAR VOWEL SIGN I..MAKASAR VOWEL SIGN U
		{ 0x11EF5, 0x11EF6, Category::SpacingMark },	// MAKASAR VOWEL SIGN E..MAKASAR VOWEL SIGN O
		{ 0x11EF7, 0x11EF8, Category::OtherPunctuation },	// MAKASAR PASSIMBANG..MAKASAR END OF SECTION
		{ 0x11EF9, 0x11EFF, Category::Unassigned },	// <reserved-11EF9>..<reserved-11EFF>
		{ 0x11F00, 0x11F01, Category::NonspacingMark },	// KAWI SIGN CANDRABINDU..KAWI SIGN ANUSVARA
		{ 0x11F02, 0x11F02, Category::OtherLetter },	// KAWI SIGN REPHA
		{ 0x11F03, 0x11F03, Category::SpacingMark },	// KAWI SIGN VISARGA
		{ 0x11F04, 0x11F10, Category::OtherLetter },	// KAWI LETTER A..KAWI LETTER O
		{ 0x11F11, 0x11F11, Category::Unassigned },	// <reserved-11F11>
		{ 0x11F12, 0x11F33, Category::OtherLetter },	// KAWI LETTER KA..KAWI LETTER JNYA
		{ 0x11F34, 0x11F35, Category::SpacingMark },	// KAWI VOWEL SIGN AA..KAWI VOWEL SIGN ALTERNATE AA
		{ 0x11F36, 0x11F3A, Category::NonspacingMark },	// KAWI VOWEL SIGN I..KAWI VOWEL SIGN VOCALIC R
		{ 0x11F3B, 0x11F3D, Category::Unassigned },	// <reserved-11F3B>..<reserved-11F3D>
		{ 0x11F3E, 0x11F3F, Category::SpacingMark },	// KAWI VOWEL SIGN E..KAWI VOWEL SIGN AI
		{ 0x11F40, 0x11F40, Category::NonspacingMark },	// KAWI VOWEL SIGN EU
		{ 0x11F41, 0x11F41, Category::SpacingMark },	// KAWI SIGN KILLER
		{ 0x11F42, 0x11F42, Category::NonspacingMark },	// KAWI CONJOINER
		{ 0x11F43, 0x11F4F, Category::OtherPunctuation },	// KAWI DANDA..KAWI PUNCTUATION CLOSING SPIRAL
		{ 0x11F50, 0x11F59, Category::DecimalNumber },	// KAWI DIGIT ZERO..KAWI DIGIT NINE
		{ 0x11F5A, 0x11F5A, Category::NonspacingMark },	// KAWI SIGN NUKTA
		{ 0x11F5B, 0x11FAF, Category::Unassigned },	// <reserved-11F5B>..<reserved-11FAF>
		{ 0x11FB0, 0x11FB0, Category::OtherLetter },	// LISU LETTER YHA
		{ 0x11FB1, 0x11FBF, Category::Unassigned },	// <reserved-11FB1>..<reserved-11FBF>
		{ 0x11FC0, 0x11FD4, Category::OtherNumber },	// TAMIL FRACTION ONE THREE-HUNDRED-AND-TWENTIETH..TAMIL FRACTION DOWNSCALING FACTOR KIIZH
		{ 0x11FD5, 0x11FDC, Category::OtherSymbol },	// TAMIL SIGN NEL..TAMIL SIGN MUKKURUNI
		{ 0x11FDD, 0x11FE0, Category::CurrencySymbol },	// TAMIL SIGN KAACU..TAMIL SIGN VARAAKAN
		{ 0x11FE1, 0x11FF1, Category::OtherSymbol },	// TAMIL SIGN PAARAM..TAMIL SIGN VAKAIYARAA
		{ 0x11FF2, 0x11FFE, Category::Unassigned },	// <reserved-11FF2>..<reserved-11FFE>
		{ 0x11FFF, 0x11FFF, Category::OtherPunctuation },	// TAMIL PUNCTUATION END OF TEXT
		{ 0x12000, 0x12399, Category::OtherLetter },	// CUNEIFORM SIGN A..CUNEIFORM SIGN U U
		{ 0x1239A, 0x123FF, Category::Unassigned },	// <reserved-1239A>..<reserved-123FF>
		{ 0x12400, 0x1246E, Category::LetterNumber },	// CUNEIFORM NUMERIC SIGN TWO ASH..CUNEIFORM NUMERIC SIGN NINE U VARIANT FORM
		{ 0x1246F, 0x1246F, Category::Unassigned },	// <reserved-1246F>
		{ 0x12470, 0x12474, Category::OtherPunctuation },	// CUNEIFORM PUNCTUATION SIGN OLD ASSYRIAN WORD DIVIDER..CUNEIFORM PUNCTUATION SIGN DIAGONAL QUADCOLON
		{ 0x12475, 0x1247F, Category::Unassigned },	// <reserved-12475>..<reserved-1247F>
		{ 0x12480, 0x12543, Category::OtherLetter },	// CUNEIFORM SIGN AB TIMES NUN TENU..CUNEIFORM SIGN ZU5 TIMES THREE DISH TENU
		{ 0x12544, 0x12F8F, Category::Unassigned },	// <reserved-12544>..<reserved-12F8F>
		{ 0x12F90, 0x12FF0, Category::OtherLetter },	// CYPRO-MINOAN SIGN CM001..CYPRO-MINOAN SIGN CM114
		{ 0x12FF1, 0x12FF2, Category::OtherPunctuation },	// CYPRO-MINOAN SIGN CM301..CYPRO-MINOAN SIGN CM302
		{ 0x12FF3, 0x12FFF, Category::Unassigned },	// <reserved-12FF3>..<reserved-12FFF>
		{ 0x13000, 0x1342F, Category::OtherLetter },	// EGYPTIAN HIEROGLYPH A001..EGYPTIAN HIEROGLYPH V011D
		{ 0x13430, 0x1343F, Category::Format },	// EGYPTIAN HIEROGLYPH VERTICAL JOINER..EGYPTIAN HIEROGLYPH END WALLED ENCLOSURE
		{ 0x13440, 0x13440, Category::NonspacingMark },	// EGYPTIAN HIEROGLYPH MIRROR HORIZONTALLY
		{ 0x13441, 0x13446, Category::OtherLetter },	// EGYPTIAN HIEROGLYPH FULL BLANK..EGYPTIAN HIEROGLYPH WIDE LOST SIGN
		{ 0x13447, 0x13455, Category::NonspacingMark },	// EGYPTIAN HIEROGLYPH MODIFIER DAMAGED AT TOP START..EGYPTIAN HIEROGLYPH MODIFIER DAMAGED
		{ 0x13456, 0x1345F, Category::Unassigned },	// <reserved-13456>..<reserved-1345F>
		{ 0x13460, 0x143FA, Category::OtherLetter },	// EGYPTIAN HIEROGLYPH-13460..EGYPTIAN HIEROGLYPH-143FA
		{ 0x143FB, 0x143FF, Category::Unassigned },	// <reserved-143FB>..<reserved-143FF>
		{ 0x14400, 0x14646, Category::OtherLetter },	// ANATOLIAN HIEROGLYPH A001..ANATOLIAN HIEROGLYPH A530
		{ 0x14647, 0x160FF, Category::Unassigned },	// <reserved-14647>..<reserved-160FF>
		{ 0x16100, 0x1611D, Category::OtherLetter },	// GURUNG KHEMA LETTER A..GURUNG KHEMA LETTER SA
		{ 0x1611E, 0x16129, Category::NonspacingMark },	// GURUNG KHEMA VOWEL SIGN AA..GURUNG KHEMA VOWEL LENGTH MARK
		{ 0x1612A, 0x1612C, Category::SpacingMark },	// GURUNG KHEMA CONSONANT SIGN MEDIAL YA..GURUNG KHEMA CONSONANT SIGN MEDIAL HA
		{ 0x1612D, 0x1612F, Category::NonspacingMark },	// GURUNG KHEMA SIGN ANUSVARA..GURUNG KHEMA SIGN THOLHOMA
		{ 0x16130, 0x16139, Category::DecimalNumber },	// GURUNG KHEMA DIGIT ZERO..GURUNG KHEMA DIGIT NINE
		{ 0x1613A, 0x167FF, Category::Unassigned },	// <reserved-1613A>..<reserved-167FF>
		{ 0x16800, 0x16A38, Category::OtherLetter },	// BAMUM LETTER PHASE-A NGKUE MFON..BAMUM LETTER PHASE-F VUEQ
		{ 0x16A39, 0x16A3F, Category::Unassigned },	// <reserved-16A39>..<reserved-16A3F>
		{ 0x16A40, 0x16A5E, Category::OtherLetter },	// MRO LETTER TA..MRO LETTER TEK
		{ 0x16A5F, 0x16A5F, Category::Unassigned },	// <reserved-16A5F>
		{ 0x16A60, 0x16A69, Category::DecimalNumber },	// MRO DIGIT ZERO..MRO DIGIT NINE
		{ 0x16A6A, 0x16A6D, Category::Unassigned },	// <reserved-16A6A>..<reserved-16A6D>
		{ 0x16A6E, 0x16A6F, Category::OtherPunctuation },	// MRO DANDA..MRO DOUBLE DANDA
		{ 0x16A70, 0x16ABE, Category::OtherLetter },	// TANGSA LETTER OZ..TANGSA LETTER ZA
		{ 0x16ABF, 0x16ABF, Category::Unassigned },	// <reserved-16ABF>
		{ 0x16AC0, 0x16AC9, Category::DecimalNumber },	// TANGSA DIGIT ZERO..TANGSA DIGIT NINE
		{ 0x16ACA, 0x16ACF, Category::Unassigned },	// <reserved-16ACA>..<reserved-16ACF>
		{ 0x16AD0, 0x16AED, Category::OtherLetter },	// BASSA VAH LETTER ENNI..BASSA VAH LETTER I
		{ 0x16AEE, 0x16AEF, Category::Unassigned },	// <reserved-16AEE>..<reserved-16AEF>
		{ 0x16AF0, 0x16AF4, Category::NonspacingMark },	// BASSA VAH COMBINING HIGH TONE..BASSA VAH COMBINING HIGH-LOW TONE
		{ 0x16AF5, 0x16AF5, Category::OtherPunctuation },	// BASSA VAH FULL STOP
		{ 0x16AF6, 0x16AFF, Category::Unassigned },	// <reserved-16AF6>..<reserved-16AFF>
		{ 0x16B00, 0x16B2F, Category::OtherLetter },	// PAHAWH HMONG VOWEL KEEB..PAHAWH HMONG CONSONANT CAU
		{ 0x16B30, 0x16B36, Category::NonspacingMark },	// PAHAWH HMONG MARK CIM TUB..PAHAWH HMONG MARK CIM TAUM
		{ 0x16B37, 0x16B3B, Category::OtherPunctuation },	// PAHAWH HMONG SIGN VOS THOM..PAHAWH HMONG SIGN VOS FEEM
		{ 0x16B3C, 0x16B3F, Category::OtherSymbol },	// PAHAWH HMONG SIGN XYEEM NTXIV..PAHAWH HMONG SIGN XYEEM FAIB
		{ 0x16B40, 0x16B43, Category::ModifierLetter },	// PAHAWH HMONG SIGN VOS SEEV..PAHAWH HMONG SIGN IB YAM
		{ 0x16B44, 0x16B44, Category::OtherPunctuation },	// PAHAWH HMONG SIGN XAUS
		{ 0x16B45, 0x16B45, Category::OtherSymbol },	// PAHAWH HMONG SIGN CIM TSOV ROG
		{ 0x16B46, 0x16B4F, Category::Unassigned },	// <reserved-16B46>..<reserved-16B4F>
		{ 0x16B50, 0x16B59, Category::DecimalNumber },	// PAHAWH HMONG DIGIT ZERO..PAHAWH HMONG DIGIT NINE
		{ 0x16B5A, 0x16B5A, Category::Unassigned },	// <reserved-16B5A>
		{ 0x16B5B, 0x16B61, Category::OtherNumber },	// PAHAWH HMONG NUMBER TENS..PAHAWH HMONG NUMBER TRILLIONS
		{ 0x16B62, 0x16B62, Category::Unassigned },	// <reserved-16B62>
		{ 0x16B63, 0x16B77, Category::OtherLetter },	// PAHAWH HMONG SIGN VOS LUB..PAHAWH HMONG SIGN CIM NRES TOS
		{ 0x16B78, 0x16B7C, Category::Unassigned },	// <reserved-16B78>..<reserved-16B7C>
		{ 0x16B7D, 0x16B8F, Category::OtherLetter },	// PAHAWH HMONG CLAN SIGN TSHEEJ..PAHAWH HMONG CLAN SIGN VWJ
		{ 0x16B90, 0x16D3F, Category::Unassigned },	// <reserved-16B90>..<reserved-16D3F>
		{ 0x16D40, 0x16D42, Category::ModifierLetter },	// KIRAT RAI SIGN ANUSVARA..KIRAT RAI SIGN VISARGA
		{ 0x16D43, 0x16D6A, Category::OtherLetter },	// KIRAT RAI LETTER A..KIRAT RAI VOWEL SIGN AU
		{ 0x16D6B, 0x16D6C, Category::ModifierLetter },	// KIRAT RAI SIGN VIRAMA..KIRAT RAI SIGN SAAT
		{ 0x16D6D, 0x16D6F, Category::OtherPunctuation },	// KIRAT RAI SIGN YUPI..KIRAT RAI DOUBLE DANDA
		{ 0x16D70, 0x16D79, Category::DecimalNumber },	// KIRAT RAI DIGIT ZERO..KIRAT RAI DIGIT NINE
		{ 0x16D7A, 0x16E3F, Category::Unassigned },	// <reserved-16D7A>..<reserved-16E3F>
		{ 0x16E40, 0x16E5F, Category::UppercaseLetter },	// MEDEFAIDRIN CAPITAL LETTER M..MEDEFAIDRIN CAPITAL LETTER Y
		{ 0x16E60, 0x16E7F, Category::LowercaseLetter },	// MEDEFAIDRIN SMALL LETTER M..MEDEFAIDRIN SMALL LETTER Y
		{ 0x16E80, 0x16E96, Category::OtherNumber },	// MEDEFAIDRIN DIGIT ZERO..MEDEFAIDRIN DIGIT THREE ALTERNATE FORM
		{ 0x16E97, 0x16E9A, Category::OtherPunctuation },	// MEDEFAIDRIN COMMA..MEDEFAIDRIN EXCLAMATION OH
		{ 0x16E9B, 0x16EFF, Category::Unassigned },	// <reserved-16E9B>..<reserved-16EFF>
		{ 0x16F00, 0x16F4A, Category::OtherLetter },	// MIAO LETTER PA..MIAO LETTER RTE
		{ 0x16F4B, 0x16F4E, Category::Unassigned },	// <reserved-16F4B>..<reserved-16F4E>
		{ 0x16F4F, 0x16F4F, Category::NonspacingMark },	// MIAO SIGN CONSONANT MODIFIER BAR
		{ 0x16F50, 0x16F50, Category::OtherLetter },	// MIAO LETTER NASALIZATION
		{ 0x16F51, 0x16F87, Category::SpacingMark },	// MIAO SIGN ASPIRATION..MIAO VOWEL SIGN UI
		{ 0x16F88, 0x16F8E, Category::Unassigned },	// <reserved-16F88>..<reserved-16F8E>
		{ 0x16F8F, 0x16F92, Category::NonspacingMark },	// MIAO TONE RIGHT..MIAO TONE BELOW
		{ 0x16F93, 0x16F9F, Category::ModifierLetter },	// MIAO LETTER TONE-2..MIAO LETTER REFORMED TONE-8
		{ 0x16FA0, 0x16FDF, Category::Unassigned },	// <reserved-16FA0>..<reserved-16FDF>
		{ 0x16FE0, 0x16FE1, Category::ModifierLetter },	// TANGUT ITERATION MARK..NUSHU ITERATION MARK
		{ 0x16FE2, 0x16FE2, Category::OtherPunctuation },	// OLD CHINESE HOOK MARK
		{ 0x16FE3, 0x16FE3, Category::ModifierLetter },	// OLD CHINESE ITERATION MARK
		{ 0x16FE4, 0x16FE4, Category::NonspacingMark },	// KHITAN SMALL SCRIPT FILLER
		{ 0x16FE5, 0x16FEF, Category::Unassigned },	// <reserved-16FE5>..<reserved-16FEF>
		{ 0x16FF0, 0x16FF1, Category::SpacingMark },	// VIETNAMESE ALTERNATE READING MARK CA..VIETNAMESE ALTERNATE READING MARK NHAY
		{ 0x16FF2, 0x16FFF, Category::Unassigned },	// <reserved-16FF2>..<reserved-16FFF>
		{ 0x17000, 0x187F7, Category::OtherLetter },	// TANGUT IDEOGRAPH-17000..TANGUT IDEOGRAPH-187F7
		{ 0x187F8, 0x187FF, Category::Unassigned },	// <reserved-187F8>..<reserved-187FF>
		{ 0x18800, 0x18CD5, Category::OtherLetter },	// TANGUT COMPONENT-001..KHITAN SMALL SCRIPT CHARACTER-18CD5
		{ 0x18CD6, 0x18CFE, Category::Unassigned },	// <reserved-18CD6>..<reserved-18CFE>
		{ 0x18CFF, 0x18D08, Category::OtherLetter },	// KHITAN SMALL SCRIPT CHARACTER-18CFF..TANGUT IDEOGRAPH-18D08
		{ 0x18D09, 0x1AFEF, Category::Unassigned },	// <reserved-18D09>..<reserved-1AFEF>
		{ 0x1AFF0, 0x1AFF3, Category::ModifierLetter },	// KATAKANA LETTER MINNAN TONE-2..KATAKANA LETTER MINNAN TONE-5
		{ 0x1AFF4, 0x1AFF4, Category::Unassigned },	// <reserved-1AFF4>
		{ 0x1AFF5, 0x1AFFB, Category::ModifierLetter },	// KATAKANA LETTER MINNAN TONE-7..KATAKANA LETTER MINNAN NASALIZED TONE-5
		{ 0x1AFFC, 0x1AFFC, Category::Unassigned },	// <reserved-1AFFC>
		{ 0x1AFFD, 0x1AFFE, Category::ModifierLetter },	// KATAKANA LETTER MINNAN NASALIZED TONE-7..KATAKANA LETTER MINNAN NASALIZED TONE-8
		{ 0x1AFFF, 0x1AFFF, Category::Unassigned },	// <reserved-1AFFF>
		{ 0x1B000, 0x1B122, Category::OtherLetter },	// KATAKANA LETTER ARCHAIC E..KATAKANA LETTER ARCHAIC WU
		{ 0x1B123, 0x1B131, Category::Unassigned },	// <reserved-1B123>..<reserved-1B131>
		{ 0x1B132, 0x1B132, Category::OtherLetter },	// HIRAGANA LETTER SMALL KO
		{ 0x1B133, 0x1B14F, Category::Unassigned },	// <reserved-1B133>..<reserved-1B14F>
		{ 0x1B150, 0x1B152, Category::OtherLetter },	// HIRAGANA LETTER SMALL WI..HIRAGANA LETTER SMALL WO
		{ 0x1B153, 0x1B154, Category::Unassigned },	// <reserved-1B153>..<reserved-1B154>
		{ 0x1B155, 0x1B155, Category::OtherLetter },	// KATAKANA LETTER SMALL KO
		{ 0x1B156, 0x1B163, Category::Unassigned },	// <reserved-1B156>..<reserved-1B163>
		{ 0x1B164, 0x1B167, Category::OtherLetter },	// KATAKANA LETTER SMALL WI..KATAKANA LETTER SMALL N
		{ 0x1B168, 0x1B16F, Category::Unassigned },	// <reserved-1B168>..<reserved-1B16F>
		{ 0x1B170, 0x1B2FB, Category::OtherLetter },	// NUSHU CHARACTER-1B170..NUSHU CHARACTER-1B2FB
		{ 0x1B2FC, 0x1BBFF, Category::Unassigned },	// <reserved-1B2FC>..<reserved-1BBFF>
		{ 0x1BC00, 0x1BC6A, Category::OtherLetter },	// DUPLOYAN LETTER H..DUPLOYAN LETTER VOCALIC M
		{ 0x1BC6B, 0x1BC6F, Category::Unassigned },	// <reserved-1BC6B>..<reserved-1BC6F>
		{ 0x1BC70, 0x1BC7C, Category::OtherLetter },	// DUPLOYAN AFFIX LEFT HORIZONTAL SECANT..DUPLOYAN AFFIX ATTACHED TANGENT HOOK
		{ 0x1BC7D, 0x1BC7F, Category::Unassigned },	// <reserved-1BC7D>..<reserved-1BC7F>
		{ 0x1BC80, 0x1BC88, Category::OtherLetter },	// DUPLOYAN AFFIX HIGH ACUTE..DUPLOYAN AFFIX HIGH VERTICAL
		{ 0x1BC89, 0x1BC8F, Category::Unassigned },	// <reserved-1BC89>..<reserved-1BC8F>
		{ 0x1BC90, 0x1BC99, Category::OtherLetter },	// DUPLOYAN AFFIX LOW ACUTE..DUPLOYAN AFFIX LOW ARROW
		{ 0x1BC9A, 0x1BC9B, Category::Unassigned },	// <reserved-1BC9A>..<reserved-1BC9B>
		{ 0x1BC9C, 0x1BC9C, Category::OtherSymbol },	// DUPLOYAN SIGN O WITH CROSS
		{ 0x1BC9D, 0x1BC9E, Category::NonspacingMark },	// DUPLOYAN THICK LETTER SELECTOR..DUPLOYAN DOUBLE MARK
		{ 0x1BC9F, 0x1BC9F, Category::OtherPunctuation },	// DUPLOYAN PUNCTUATION CHINOOK FULL STOP
		{ 0x1BCA0, 0x1BCA3, Category::Format },	// SHORTHAND FORMAT LETTER OVERLAP..SHORTHAND FORMAT UP STEP
		{ 0x1BCA4, 0x1CBFF, Category::Unassigned },	// <reserved-1BCA4>..<reserved-1CBFF>
		{ 0x1CC00, 0x1CCEF, Category::OtherSymbol },	// UP-POINTING GO-KART..OUTLINED LATIN CAPITAL LETTER Z
		{ 0x1CCF0, 0x1CCF9, Category::DecimalNumber },	// OUTLINED DIGIT ZERO..OUTLINED DIGIT NINE
		{ 0x1CCFA, 0x1CCFF, Category::Unassigned },	// <reserved-1CCFA>..<reserved-1CCFF>
		{ 0x1CD00, 0x1CEB3, Category::OtherSymbol },	// BLOCK OCTANT-3..BLACK RIGHT TRIANGLE CARET
		{ 0x1CEB4, 0x1CEFF, Category::Unassigned },	// <reserved-1CEB4>..<reserved-1CEFF>
		{ 0x1CF00, 0x1CF2D, Category::NonspacingMark },	// ZNAMENNY COMBINING MARK GORAZDO NIZKO S KRYZHEM ON LEFT..ZNAMENNY COMBINING MARK KRYZH ON LEFT
		{ 0x1CF2E, 0x1CF2F, Category::Unassigned },	// <reserved-1CF2E>..<reserved-1CF2F>
		{ 0x1CF30, 0x1CF46, Category::NonspacingMark },	// ZNAMENNY COMBINING TONAL RANGE MARK MRACHNO..ZNAMENNY PRIZNAK MODIFIER ROG
		{ 0x1CF47, 0x1CF4F, Category::Unassigned },	// <reserved-1CF47>..<reserved-1CF4F>
		{ 0x1CF50, 0x1CFC3, Category::OtherSymbol },	// ZNAMENNY NEUME KRYUK..ZNAMENNY NEUME PAUK
		{ 0x1CFC4, 0x1CFFF, Category::Unassigned },	// <reserved-1CFC4>..<reserved-1CFFF>
		{ 0x1D000, 0x1D0F5, Category::OtherSymbol },	// BYZANTINE MUSICAL SYMBOL PSILI..BYZANTINE MUSICAL SYMBOL GORGON NEO KATO
		{ 0x1D0F6, 0x1D0FF, Category::Unassigned },	// <reserved-1D0F6>..<reserved-1D0FF>
		{ 0x1D100, 0x1D126, Category::OtherSymbol },	// MUSICAL SYMBOL SINGLE BARLINE..MUSICAL SYMBOL DRUM CLEF-2
		{ 0x1D127, 0x1D128, Category::Unassigned },	// <reserved-1D127>..<reserved-1D128>
		{ 0x1D129, 0x1D164, Category::OtherSymbol },	// MUSICAL SYMBOL MULTIPLE MEASURE REST..MUSICAL SYMBOL ONE HUNDRED TWENTY-EIGHTH NOTE
		{ 0x1D165, 0x1D166, Category::SpacingMark },	// MUSICAL SYMBOL COMBINING STEM..MUSICAL SYMBOL COMBINING SPRECHGESANG STEM
		{ 0x1D167, 0x1D169, Category::NonspacingMark },	// MUSICAL SYMBOL COMBINING TREMOLO-1..MUSICAL SYMBOL COMBINING TREMOLO-3
		{ 0x1D16A, 0x1D16C, Category::OtherSymbol },	// MUSICAL SYMBOL FINGERED TREMOLO-1..MUSICAL SYMBOL FINGERED TREMOLO-3
		{ 0x1D16D, 0x1D172, Category::SpacingMark },	// MUSICAL SYMBOL COMBINING AUGMENTATION DOT..MUSICAL SYMBOL COMBINING FLAG-5
		{ 0x1D173, 0x1D17A, Category::Format },	// MUSICAL SYMBOL BEGIN BEAM..MUSICAL SYMBOL END PHRASE
		{ 0x1D17B, 0x1D182, Category::NonspacingMark },	// MUSICAL SYMBOL COMBINING ACCENT..MUSICAL SYMBOL COMBINING LOURE
		{ 0x1D183, 0x1D184, Category::OtherSymbol },	// MUSICAL SYMBOL ARPEGGIATO UP..MUSICAL SYMBOL ARPEGGIATO DOWN
		{ 0x1D185, 0x1D18B, Category::NonspacingMark },	// MUSICAL SYMBOL COMBINING DOIT..MUSICAL SYMBOL COMBINING TRIPLE TONGUE
		{ 0x1D18C, 0x1D1A9, Category::OtherSymbol },	// MUSICAL SYMBOL RINFORZANDO..MUSICAL SYMBOL DEGREE SLASH
		{ 0x1D1AA, 0x1D1AD, Category::NonspacingMark },	// MUSICAL SYMBOL COMBINING DOWN BOW..MUSICAL SYMBOL COMBINING SNAP PIZZICATO
		{ 0x1D1AE, 0x1D1EA, Category::OtherSymbol },	// MUSICAL SYMBOL PEDAL MARK..MUSICAL SYMBOL KORON
		{ 0x1D1EB, 0x1D1FF, Category::Unassigned },	// <reserved-1D1EB>..<reserved-1D1FF>
		{ 0x1D200, 0x1D241, Category::OtherSymbol },	// GREEK VOCAL NOTATION SYMBOL-1..GREEK INSTRUMENTAL NOTATION SYMBOL-54
		{ 0x1D242, 0x1D244, Category::NonspacingMark },	// COMBINING GREEK MUSICAL TRISEME..COMBINING GREEK MUSICAL PENTASEME
		{ 0x1D245, 0x1D245, Category::OtherSymbol },	// GREEK MUSICAL LEIMMA
		{ 0x1D246, 0x1D2BF, Category::Unassigned },	// <reserved-1D246>..<reserved-1D2BF>
		{ 0x1D2C0, 0x1D2D3, Category::OtherNumber },	// KAKTOVIK NUMERAL ZERO..KAKTOVIK NUMERAL NINETEEN
		{ 0x1D2D4, 0x1D2DF, Category::Unassigned },	// <reserved-1D2D4>..<reserved-1D2DF>
		{ 0x1D2E0, 0x1D2F3, Category::OtherNumber },	// MAYAN NUMERAL ZERO..MAYAN NUMERAL NINETEEN
		{ 0x1D2F4, 0x1D2FF, Category::Unassigned },	// <reserved-1D2F4>..<reserved-1D2FF>
		{ 0x1D300, 0x1D356, Category::OtherSymbol },	// MONOGRAM FOR EARTH..TETRAGRAM FOR FOSTERING
		{ 0x1D357, 0x1D35F, Category::Unassigned },	// <reserved-1D357>..<reserved-1D35F>
		{ 0x1D360, 0x1D378, Category::OtherNumber },	// COUNTING ROD UNIT DIGIT ONE..TALLY MARK FIVE
		{ 0x1D379, 0x1D3FF, Category::Unassigned },	// <reserved-1D379>..<reserved-1D3FF>
		{ 0x1D400, 0x1D419, Category::UppercaseLetter },	// MATHEMATICAL BOLD CAPITAL A..MATHEMATICAL BOLD CAPITAL Z
		{ 0x1D41A, 0x1D433, Category::LowercaseLetter },	// MATHEMATICAL BOLD SMALL A..MATHEMATICAL BOLD SMALL Z
		{ 0x1D434, 0x1D44D, Category::UppercaseLetter },	// MATHEMATICAL ITALIC CAPITAL A..MATHEMATICAL ITALIC CAPITAL Z
		{ 0x1D44E, 0x1D454, Category::LowercaseLetter },	// MATHEMATICAL ITALIC SMALL A..MATHEMATICAL ITALIC SMALL G
		{ 0x1D455, 0x1D455, Category::Unassigned },	// <reserved-1D455>
		{ 0x1D456, 0x1D467, Category::LowercaseLetter },	// MATHEMATICAL ITALIC SMALL I..MATHEMATICAL ITALIC SMALL Z
		{ 0x1D468, 0x1D481, Category::UppercaseLetter },	// MATHEMATICAL BOLD ITALIC CAPITAL A..MATHEMATICAL BOLD ITALIC CAPITAL Z
		{ 0x1D482, 0x1D49B, Category::LowercaseLetter },	// MATHEMATICAL BOLD ITALIC SMALL A..MATHEMATICAL BOLD ITALIC SMALL Z
		{ 0x1D49C, 0x1D49C, Category::UppercaseLetter },	// MATHEMATICAL SCRIPT CAPITAL A
		{ 0x1D49D, 0x1D49D, Category::Unassigned },	// <reserved-1D49D>
		{ 0x1D49E, 0x1D49F, Category::UppercaseLetter },	// MATHEMATICAL SCRIPT CAPITAL C..MATHEMATICAL SCRIPT CAPITAL D
		{ 0x1D4A0, 0x1D4A1, Category::Unassigned },	// <reserved-1D4A0>..<reserved-1D4A1>
		{ 0x1D4A2, 0x1D4A2, Category::UppercaseLetter },	// MATHEMATICAL SCRIPT CAPITAL G
		{ 0x1D4A3, 0x1D4A4, Category::Unassigned },	// <reserved-1D4A3>..<reserved-1D4A4>
		{ 0x1D4A5, 0x1D4A6, Category::UppercaseLetter },	// MATHEMATICAL SCRIPT CAPITAL J..MATHEMATICAL SCRIPT CAPITAL K
		{ 0x1D4A7, 0x1D4A8, Category::Unassigned },	// <reserved-1D4A7>..<reserved-1D4A8>
		{ 0x1D4A9, 0x1D4AC, Category::UppercaseLetter },	// MATHEMATICAL SCRIPT CAPITAL N..MATHEMATICAL SCRIPT CAPITAL Q
		{ 0x1D4AD, 0x1D4AD, Category::Unassigned },	// <reserved-1D4AD>
		{ 0x1D4AE, 0x1D4B5, Category::UppercaseLetter },	// MATHEMATICAL SCRIPT CAPITAL S..MATHEMATICAL SCRIPT CAPITAL Z
		{ 0x1D4B6, 0x1D4B9, Category::LowercaseLetter },	// MATHEMATICAL SCRIPT SMALL A..MATHEMATICAL SCRIPT SMALL D
		{ 0x1D4BA, 0x1D4BA, Category::Unassigned },	// <reserved-1D4BA>
		{ 0x1D4BB, 0x1D4BB, Category::LowercaseLetter },	// MATHEMATICAL SCRIPT SMALL F
		{ 0x1D4BC, 0x1D4BC, Category::Unassigned },	// <reserved-1D4BC>
		{ 0x1D4BD, 0x1D4C3, Category::LowercaseLetter },	// MATHEMATICAL SCRIPT SMALL H..MATHEMATICAL SCRIPT SMALL N
		{ 0x1D4C4, 0x1D4C4, Category::Unassigned },	// <reserved-1D4C4>
		{ 0x1D4C5, 0x1D4CF, Category::LowercaseLetter },	// MATHEMATICAL SCRIPT SMALL P..MATHEMATICAL SCRIPT SMALL Z
		{ 0x1D4D0, 0x1D4E9, Category::UppercaseLetter },	// MATHEMATICAL BOLD SCRIPT CAPITAL A..MATHEMATICAL BOLD SCRIPT CAPITAL Z
		{ 0x1D4EA, 0x1D503, Category::LowercaseLetter },	// MATHEMATICAL BOLD SCRIPT SMALL A..MATHEMATICAL BOLD SCRIPT SMALL Z
		{ 0x1D504, 0x1D505, Category::UppercaseLetter },	// MATHEMATICAL FRAKTUR CAPITAL A..MATHEMATICAL FRAKTUR CAPITAL B
		{ 0x1D506, 0x1D506, Category::Unassigned },	// <reserved-1D506>
		{ 0x1D507, 0x1D50A, Category::UppercaseLetter },	// MATHEMATICAL FRAKTUR CAPITAL D..MATHEMATICAL FRAKTUR CAPITAL G
		{ 0x1D50B, 0x1D50C, Category::Unassigned },	// <reserved-1D50B>..<reserved-1D50C>
		{ 0x1D50D, 0x1D514, Category::UppercaseLetter },	// MATHEMATICAL FRAKTUR CAPITAL J..MATHEMATICAL FRAKTUR CAPITAL Q
		{ 0x1D515, 0x1D515, Category::Unassigned },	// <reserved-1D515>
		{ 0x1D516, 0x1D51C, Category::UppercaseLetter },	// MATHEMATICAL FRAKTUR CAPITAL S..MATHEMATICAL FRAKTUR CAPITAL Y
		{ 0x1D51D, 0x1D51D, Category::Unassigned },	// <reserved-1D51D>
		{ 0x1D51E, 0x1D537, Category::LowercaseLetter },	// MATHEMATICAL FRAKTUR SMALL A..MATHEMATICAL FRAKTUR SMALL Z
		{ 0x1D538, 0x1D539, Category::UppercaseLetter },	// MATHEMATICAL DOUBLE-STRUCK CAPITAL A..MATHEMATICAL DOUBLE-STRUCK CAPITAL B
		{ 0x1D53A, 0x1D53A, Category::Unassigned },	// <reserved-1D53A>
		{ 0x1D53B, 0x1D53E, Category::UppercaseLetter },	// MATHEMATICAL DOUBLE-STRUCK CAPITAL D..MATHEMATICAL DOUBLE-STRUCK CAPITAL G
		{ 0x1D53F, 0x1D53F, Category::Unassigned },	// <reserved-1D53F>
		{ 0x1D540, 0x1D544, Category::UppercaseLetter },	// MATHEMATICAL DOUBLE-STRUCK CAPITAL I..MATHEMATICAL DOUBLE-STRUCK CAPITAL M
		{ 0x1D545, 0x1D545, Category::Unassigned },	// <reserved-1D545>
		{ 0x1D546, 0x1D546, Category::UppercaseLetter },	// MATHEMATICAL DOUBLE-STRUCK CAPITAL O
		{ 0x1D547, 0x1D549, Category::Unassigned },	// <reserved-1D547>..<reserved-1D549>
		{ 0x1D54A, 0x1D550, Category::UppercaseLetter },	// MATHEMATICAL DOUBLE-STRUCK CAPITAL S..MATHEMATICAL DOUBLE-STRUCK CAPITAL Y
		{ 0x1D551, 0x1D551, Category::Unassigned },	// <reserved-1D551>
		{ 0x1D552, 0x1D56B, Category::LowercaseLetter },	// MATHEMATICAL DOUBLE-STRUCK SMALL A..MATHEMATICAL DOUBLE-STRUCK SMALL Z
		{ 0x1D56C, 0x1D585, Category::UppercaseLetter },	// MATHEMATICAL BOLD FRAKTUR CAPITAL A..MATHEMATICAL BOLD FRAKTUR CAPITAL Z
		{ 0x1D586, 0x1D59F, Category::LowercaseLetter },	// MATHEMATICAL BOLD FRAKTUR SMALL A..MATHEMATICAL BOLD FRAKTUR SMALL Z
		{ 0x1D5A0, 0x1D5B9, Category::UppercaseLetter },	// MATHEMATICAL SANS-SERIF CAPITAL A..MATHEMATICAL SANS-SERIF CAPITAL Z
		{ 0x1D5BA, 0x1D5D3, Category::LowercaseLetter },	// MATHEMATICAL SANS-SERIF SMALL A..MATHEMATICAL SANS-SERIF SMALL Z
		{ 0x1D5D4, 0x1D5ED, Category::UppercaseLetter },	// MATHEMATICAL SANS-SERIF BOLD CAPITAL A..MATHEMATICAL SANS-SERIF BOLD CAPITAL Z
		{ 0x1D5EE, 0x1D607, Category::LowercaseLetter },	// MATHEMATICAL SANS-SERIF BOLD SMALL A..MATHEMATICAL SANS-SERIF BOLD SMALL Z
		{ 0x1D608, 0x1D621, Category::UppercaseLetter },	// MATHEMATICAL SANS-SERIF ITALIC CAPITAL A..MATHEMATICAL SANS-SERIF ITALIC CAPITAL Z
		{ 0x1D622, 0x1D63B, Category::LowercaseLetter },	// MATHEMATICAL SANS-SERIF ITALIC SMALL A..MATHEMATICAL SANS-SERIF ITALIC SMALL Z
		{ 0x1D63C, 0x1D655, Category::UppercaseLetter },	// MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL A..MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL Z
		{ 0x1D656, 0x1D66F, Category::LowercaseLetter },	// MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL A..MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL Z
		{ 0x1D670, 0x1D689, Category::UppercaseLetter },	// MATHEMATICAL MONOSPACE CAPITAL A..MATHEMATICAL MONOSPACE CAPITAL Z
		{ 0x1D68A, 0x1D6A5, Category::LowercaseLetter },	// MATHEMATICAL MONOSPACE SMALL A..MATHEMATICAL ITALIC SMALL DOTLESS J
		{ 0x1D6A6, 0x1D6A7, Category::Unassigned },	// <reserved-1D6A6>..<reserved-1D6A7>
		{ 0x1D6A8, 0x1D6C0, Category::UppercaseLetter },	// MATHEMATICAL BOLD CAPITAL ALPHA..MATHEMATICAL BOLD CAPITAL OMEGA
		{ 0x1D6C1, 0x1D6C1, Category::MathSymbol },	// MATHEMATICAL BOLD NABLA
		{ 0x1D6C2, 0x1D6DA, Category::LowercaseLetter },	// MATHEMATICAL BOLD SMALL ALPHA..MATHEMATICAL BOLD SMALL OMEGA
		{ 0x1D6DB, 0x1D6DB, Category::MathSymbol },	// MATHEMATICAL BOLD PARTIAL DIFFERENTIAL
		{ 0x1D6DC, 0x1D6E1, Category::LowercaseLetter },	// MATHEMATICAL BOLD EPSILON SYMBOL..MATHEMATICAL BOLD PI SYMBOL
		{ 0x1D6E2, 0x1D6FA, Category::UppercaseLetter },	// MATHEMATICAL ITALIC CAPITAL ALPHA..MATHEMATICAL ITALIC CAPITAL OMEGA
		{ 0x1D6FB, 0x1D6FB, Category::MathSymbol },	// MATHEMATICAL ITALIC NABLA
		{ 0x1D6FC, 0x1D714, Category::LowercaseLetter },	// MATHEMATICAL ITALIC SMALL ALPHA..MATHEMATICAL ITALIC SMALL OMEGA
		{ 0x1D715, 0x1D715, Category::MathSymbol },	// MATHEMATICAL ITALIC PARTIAL DIFFERENTIAL
		{ 0x1D716, 0x1D71B, Category::LowercaseLetter },	// MATHEMATICAL ITALIC EPSILON SYMBOL..MATHEMATICAL ITALIC PI SYMBOL
		{ 0x1D71C, 0x1D734, Category::UppercaseLetter },	// MATHEMATICAL BOLD ITALIC CAPITAL ALPHA..MATHEMATICAL BOLD ITALIC CAPITAL OMEGA
		{ 0x1D735, 0x1D735, Category::MathSymbol },	// MATHEMATICAL BOLD ITALIC NABLA
		{ 0x1D736, 0x1D74E, Category::LowercaseLetter },	// MATHEMATICAL BOLD ITALIC SMALL ALPHA..MATHEMATICAL BOLD ITALIC SMALL OMEGA
		{ 0x1D74F, 0x1D74F, Category::MathSymbol },	// MATHEMATICAL BOLD ITALIC PARTIAL DIFFERENTIAL
		{ 0x1D750, 0x1D755, Category::LowercaseLetter },	// MATHEMATICAL BOLD ITALIC EPSILON SYMBOL..MATHEMATICAL BOLD ITALIC PI SYMBOL
		{ 0x1D756, 0x1D76E, Category::UppercaseLetter },	// MATHEMATICAL SANS-SERIF BOLD CAPITAL ALPHA..MATHEMATICAL SANS-SERIF BOLD CAPITAL OMEGA
		{ 0x1D76F, 0x1D76F, Category::MathSymbol },	// MATHEMATICAL SANS-SERIF BOLD NABLA
		{ 0x1D770, 0x1D788, Category::LowercaseLetter },	// MATHEMATICAL SANS-SERIF BOLD SMALL ALPHA..MATHEMATICAL SANS-SERIF BOLD SMALL OMEGA
		{ 0x1D789, 0x1D789, Category::MathSymbol },	// MATHEMATICAL SANS-SERIF BOLD PARTIAL DIFFERENTIAL
		{ 0x1D78A, 0x1D78F, Category::LowercaseLetter },	// MATHEMATICAL SANS-SERIF BOLD EPSILON SYMBOL..MATHEMATICAL SANS-SERIF BOLD PI SYMBOL
		{ 0x1D790, 0x1D7A8, Category::UppercaseLetter },	// MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL ALPHA..MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL OMEGA
		{ 0x1D7A9, 0x1D7A9, Category::MathSymbol },	// MATHEMATICAL SANS-SERIF BOLD ITALIC NABLA
		{ 0x1D7AA, 0x1D7C2, Category::LowercaseLetter },	// MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL ALPHA..MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL OMEGA
		{ 0x1D7C3, 0x1D7C3, Category::MathSymbol },	// MATHEMATICAL SANS-SERIF BOLD ITALIC PARTIAL DIFFERENTIAL
		{ 0x1D7C4, 0x1D7C9, Category::LowercaseLetter },	// MATHEMATICAL SANS-SERIF BOLD ITALIC EPSILON SYMBOL..MATHEMATICAL SANS-SERIF BOLD ITALIC PI SYMBOL
		{ 0x1D7CA, 0x1D7CA, Category::UppercaseLetter },	// MATHEMATICAL BOLD CAPITAL DIGAMMA
		{ 0x1D7CB, 0x1D7CB, Category::LowercaseLetter },	// MATHEMATICAL BOLD SMALL DIGAMMA
		{ 0x1D7CC, 0x1D7CD, Category::Unassigned },	// <reserved-1D7CC>..<reserved-1D7CD>
		{ 0x1D7CE, 0x1D7FF, Category::DecimalNumber },	// MATHEMATICAL BOLD DIGIT ZERO..MATHEMATICAL MONOSPACE DIGIT NINE
		{ 0x1D800, 0x1D9FF, Category::OtherSymbol },	// SIGNWRITING HAND-FIST INDEX..SIGNWRITING HEAD
		{ 0x1DA00, 0x1DA36, Category::NonspacingMark },	// SIGNWRITING HEAD RIM..SIGNWRITING AIR SUCKING IN
		{ 0x1DA37, 0x1DA3A, Category::OtherSymbol },	// SIGNWRITING AIR BLOW SMALL ROTATIONS..SIGNWRITING BREATH EXHALE
		{ 0x1DA3B, 0x1DA6C, Category::NonspacingMark },	// SIGNWRITING MOUTH CLOSED NEUTRAL..SIGNWRITING EXCITEMENT
		{ 0x1DA6D, 0x1DA74, Category::OtherSymbol },	// SIGNWRITING SHOULDER HIP SPINE..SIGNWRITING TORSO-FLOORPLANE TWISTING
		{ 0x1DA75, 0x1DA75, Category::NonspacingMark },	// SIGNWRITING UPPER BODY TILTING FROM HIP JOINTS
		{ 0x1DA76, 0x1DA83, Category::OtherSymbol },	// SIGNWRITING LIMB COMBINATION..SIGNWRITING LOCATION DEPTH
		{ 0x1DA84, 0x1DA84, Category::NonspacingMark },	// SIGNWRITING LOCATION HEAD NECK
		{ 0x1DA85, 0x1DA86, Category::OtherSymbol },	// SIGNWRITING LOCATION TORSO..SIGNWRITING LOCATION LIMBS DIGITS
		{ 0x1DA87, 0x1DA8B, Category::OtherPunctuation },	// SIGNWRITING COMMA..SIGNWRITING PARENTHESIS
		{ 0x1DA8C, 0x1DA9A, Category::Unassigned },	// <reserved-1DA8C>..<reserved-1DA9A>
		{ 0x1DA9B, 0x1DA9F, Category::NonspacingMark },	// SIGNWRITING FILL MODIFIER-2..SIGNWRITING FILL MODIFIER-6
		{ 0x1DAA0, 0x1DAA0, Category::Unassigned },	// <reserved-1DAA0>
		{ 0x1DAA1, 0x1DAAF, Category::NonspacingMark },	// SIGNWRITING ROTATION MODIFIER-2..SIGNWRITING ROTATION MODIFIER-16
		{ 0x1DAB0, 0x1DEFF, Category::Unassigned },	// <reserved-1DAB0>..<reserved-1DEFF>
		{ 0x1DF00, 0x1DF09, Category::LowercaseLetter },	// LATIN SMALL LETTER FENG DIGRAPH WITH TRILL..LATIN SMALL LETTER T WITH HOOK AND RETROFLEX HOOK
		{ 0x1DF0A, 0x1DF0A, Category::OtherLetter },	// LATIN LETTER RETROFLEX CLICK WITH RETROFLEX HOOK
		{ 0x1DF0B, 0x1DF1E, Category::LowercaseLetter },	// LATIN SMALL LETTER ESH WITH DOUBLE BAR..LATIN SMALL LETTER S WITH CURL
		{ 0x1DF1F, 0x1DF24, Category::Unassigned },	// <reserved-1DF1F>..<reserved-1DF24>
		{ 0x1DF25, 0x1DF2A, Category::LowercaseLetter },	// LATIN SMALL LETTER D WITH MID-HEIGHT LEFT HOOK..LATIN SMALL LETTER T WITH MID-HEIGHT LEFT HOOK
		{ 0x1DF2B, 0x1DFFF, Category::Unassigned },	// <reserved-1DF2B>..<reserved-1DFFF>
		{ 0x1E000, 0x1E006, Category::NonspacingMark },	// COMBINING GLAGOLITIC LETTER AZU..COMBINING GLAGOLITIC LETTER ZHIVETE
		{ 0x1E007, 0x1E007, Category::Unassigned },	// <reserved-1E007>
		{ 0x1E008, 0x1E018, Category::NonspacingMark },	// COMBINING GLAGOLITIC LETTER ZEMLJA..COMBINING GLAGOLITIC LETTER HERU
		{ 0x1E019, 0x1E01A, Category::Unassigned },	// <reserved-1E019>..<reserved-1E01A>
		{ 0x1E01B, 0x1E021, Category::NonspacingMark },	// COMBINING GLAGOLITIC LETTER SHTA..COMBINING GLAGOLITIC LETTER YATI
		{ 0x1E022, 0x1E022, Category::Unassigned },	// <reserved-1E022>
		{ 0x1E023, 0x1E024, Category::NonspacingMark },	// COMBINING GLAGOLITIC LETTER YU..COMBINING GLAGOLITIC LETTER SMALL YUS
		{ 0x1E025, 0x1E025, Category::Unassigned },	// <reserved-1E025>
		{ 0x1E026, 0x1E02A, Category::NonspacingMark },	// COMBINING GLAGOLITIC LETTER YO..COMBINING GLAGOLITIC LETTER FITA
		{ 0x1E02B, 0x1E02F, Category::Unassigned },	// <reserved-1E02B>..<reserved-1E02F>
		{ 0x1E030, 0x1E06D, Category::ModifierLetter },	// MODIFIER LETTER CYRILLIC SMALL A..MODIFIER LETTER CYRILLIC SMALL STRAIGHT U WITH STROKE
		{ 0x1E06E, 0x1E08E, Category::Unassigned },	// <reserved-1E06E>..<reserved-1E08E>
		{ 0x1E08F, 0x1E08F, Category::NonspacingMark },	// COMBINING CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I
		{ 0x1E090, 0x1E0FF, Category::Unassigned },	// <reserved-1E090>..<reserved-1E0FF>
		{ 0x1E100, 0x1E12C, Category::OtherLetter },	// NYIAKENG PUACHUE HMONG LETTER MA..NYIAKENG PUACHUE HMONG LETTER W
		{ 0x1E12D, 0x1E12F, Category::Unassigned },	// <reserved-1E12D>..<reserved-1E12F>
		{ 0x1E130, 0x1E136, Category::NonspacingMark },	// NYIAKENG PUACHUE HMONG TONE-B..NYIAKENG PUACHUE HMONG TONE-D
		{ 0x1E137, 0x1E13D, Category::ModifierLetter },	// NYIAKENG PUACHUE HMONG SIGN FOR PERSON..NYIAKENG PUACHUE HMONG SYLLABLE LENGTHENER
		{ 0x1E13E, 0x1E13F, Category::Unassigned },	// <reserved-1E13E>..<reserved-1E13F>
		{ 0x1E140, 0x1E149, Category::DecimalNumber },	// NYIAKENG PUACHUE HMONG DIGIT ZERO..NYIAKENG PUACHUE HMONG DIGIT NINE
		{ 0x1E14A, 0x1E14D, Category::Unassigned },	// <reserved-1E14A>..<reserved-1E14D>
		{ 0x1E14E, 0x1E14E, Category::OtherLetter },	// NYIAKENG PUACHUE HMONG LOGOGRAM NYAJ
		{ 0x1E14F, 0x1E14F, Category::OtherSymbol },	// NYIAKENG PUACHUE HMONG CIRCLED CA
		{ 0x1E150, 0x1E28F, Category::Unassigned },	// <reserved-1E150>..<reserved-1E28F>
		{ 0x1E290, 0x1E2AD, Category::OtherLetter },	// TOTO LETTER PA..TOTO LETTER A
		{ 0x1E2AE, 0x1E2AE, Category::NonspacingMark },	// TOTO SIGN RISING TONE
		{ 0x1E2AF, 0x1E2BF, Category::Unassigned },	// <reserved-1E2AF>..<reserved-1E2BF>
		{ 0x1E2C0, 0x1E2EB, Category::OtherLetter },	// WANCHO LETTER AA..WANCHO LETTER YIH
		{ 0x1E2EC, 0x1E2EF, Category::NonspacingMark },	// WANCHO TONE TUP..WANCHO TONE KOINI
		{ 0x1E2F0, 0x1E2F9, Category::DecimalNumber },	// WANCHO DIGIT ZERO..WANCHO DIGIT NINE
		{ 0x1E2FA, 0x1E2FE, Category::Unassigned },	// <reserved-1E2FA>..<reserved-1E2FE>
		{ 0x1E2FF, 0x1E2FF, Category::CurrencySymbol },	// WANCHO NGUN SIGN
		{ 0x1E300, 0x1E4CF, Category::Unassigned },	// <reserved-1E300>..<reserved-1E4CF>
		{ 0x1E4D0, 0x1E4EA, Category::OtherLetter },	// NAG MUNDARI LETTER O..NAG MUNDARI LETTER ELL
		{ 0x1E4EB, 0x1E4EB, Category::ModifierLetter },	// NAG MUNDARI SIGN OJOD
		{ 0x1E4EC, 0x1E4EF, Category::NonspacingMark },	// NAG MUNDARI SIGN MUHOR..NAG MUNDARI SIGN SUTUH
		{ 0x1E4F0, 0x1E4F9, Category::DecimalNumber },	// NAG MUNDARI DIGIT ZERO..NAG MUNDARI DIGIT NINE
		{ 0x1E4FA, 0x1E5CF, Category::Unassigned },	// <reserved-1E4FA>..<reserved-1E5CF>
		{ 0x1E5D0, 0x1E5ED, Category::OtherLetter },	// OL ONAL LETTER O..OL ONAL LETTER EG
		{ 0x1E5EE, 0x1E5EF, Category::NonspacingMark },	// OL ONAL SIGN MU..OL ONAL SIGN IKIR
		{ 0x1E5F0, 0x1E5F0, Category::OtherLetter },	// OL ONAL SIGN HODDOND
		{ 0x1E5F1, 0x1E5FA, Category::DecimalNumber },	// OL ONAL DIGIT ZERO..OL ONAL DIGIT NINE
		{ 0x1E5FB, 0x1E5FE, Category::Unassigned },	// <reserved-1E5FB>..<reserved-1E5FE>
		{ 0x1E5FF, 0x1E5FF, Category::OtherPunctuation },	// OL ONAL ABBREVIATION SIGN
		{ 0x1E600, 0x1E7DF, Category::Unassigned },	// <reserved-1E600>..<reserved-1E7DF>
		{ 0x1E7E0, 0x1E7E6, Category::OtherLetter },	// ETHIOPIC SYLLABLE HHYA..ETHIOPIC SYLLABLE HHYO
		{ 0x1E7E7, 0x1E7E7, Category::Unassigned },	// <reserved-1E7E7>
		{ 0x1E7E8, 0x1E7EB, Category::OtherLetter },	// ETHIOPIC SYLLABLE GURAGE HHWA..ETHIOPIC SYLLABLE HHWE
		{ 0x1E7EC, 0x1E7EC, Category::Unassigned },	// <reserved-1E7EC>
		{ 0x1E7ED, 0x1E7EE, Category::OtherLetter },	// ETHIOPIC SYLLABLE GURAGE MWI..ETHIOPIC SYLLABLE GURAGE MWEE
		{ 0x1E7EF, 0x1E7EF, Category::Unassigned },	// <reserved-1E7EF>
		{ 0x1E7F0, 0x1E7FE, Category::OtherLetter },	// ETHIOPIC SYLLABLE GURAGE QWI..ETHIOPIC SYLLABLE GURAGE PWEE
		{ 0x1E7FF, 0x1E7FF, Category::Unassigned },	// <reserved-1E7FF>
		{ 0x1E800, 0x1E8C4, Category::OtherLetter },	// MENDE KIKAKUI SYLLABLE M001 KI..MENDE KIKAKUI SYLLABLE M060 NYON
		{ 0x1E8C5, 0x1E8C6, Category::Unassigned },	// <reserved-1E8C5>..<reserved-1E8C6>
		{ 0x1E8C7, 0x1E8CF, Category::OtherNumber },	// MENDE KIKAKUI DIGIT ONE..MENDE KIKAKUI DIGIT NINE
		{ 0x1E8D0, 0x1E8D6, Category::NonspacingMark },	// MENDE KIKAKUI COMBINING NUMBER TEENS..MENDE KIKAKUI COMBINING NUMBER MILLIONS
		{ 0x1E8D7, 0x1E8FF, Category::Unassigned },	// <reserved-1E8D7>..<reserved-1E8FF>
		{ 0x1E900, 0x1E921, Category::UppercaseLetter },	// ADLAM CAPITAL LETTER ALIF..ADLAM CAPITAL LETTER SHA
		{ 0x1E922, 0x1E943, Category::LowercaseLetter },	// ADLAM SMALL LETTER ALIF..ADLAM SMALL LETTER SHA
		{ 0x1E944, 0x1E94A, Category::NonspacingMark },	// ADLAM ALIF LENGTHENER..ADLAM NUKTA
		{ 0x1E94B, 0x1E94B, Category::ModifierLetter },	// ADLAM NASALIZATION MARK
		{ 0x1E94C, 0x1E94F, Category::Unassigned },	// <reserved-1E94C>..<reserved-1E94F>
		{ 0x1E950, 0x1E959, Category::DecimalNumber },	// ADLAM DIGIT ZERO..ADLAM DIGIT NINE
		{ 0x1E95A, 0x1E95D, Category::Unassigned },	// <reserved-1E95A>..<reserved-1E95D>
		{ 0x1E95E, 0x1E95F, Category::OtherPunctuation },	// ADLAM INITIAL EXCLAMATION MARK..ADLAM INITIAL QUESTION MARK
		{ 0x1E960, 0x1EC70, Category::Unassigned },	// <reserved-1E960>..<reserved-1EC70>
		{ 0x1EC71, 0x1ECAB, Category::OtherNumber },	// INDIC SIYAQ NUMBER ONE..INDIC SIYAQ NUMBER PREFIXED NINE
		{ 0x1ECAC, 0x1ECAC, Category::OtherSymbol },	// INDIC SIYAQ PLACEHOLDER
		{ 0x1ECAD, 0x1ECAF, Category::OtherNumber },	// INDIC SIYAQ FRACTION ONE QUARTER..INDIC SIYAQ FRACTION THREE QUARTERS
		{ 0x1ECB0, 0x1ECB0, Category::CurrencySymbol },	// INDIC SIYAQ RUPEE MARK
		{ 0x1ECB1, 0x1ECB4, Category::OtherNumber },	// INDIC SIYAQ NUMBER ALTERNATE ONE..INDIC SIYAQ ALTERNATE LAKH MARK
		{ 0x1ECB5, 0x1ED00, Category::Unassigned },	// <reserved-1ECB5>..<reserved-1ED00>
		{ 0x1ED01, 0x1ED2D, Category::OtherNumber },	// OTTOMAN SIYAQ NUMBER ONE..OTTOMAN SIYAQ NUMBER NINETY THOUSAND
		{ 0x1ED2E, 0x1ED2E, Category::OtherSymbol },	// OTTOMAN SIYAQ MARRATAN
		{ 0x1ED2F, 0x1ED3D, Category::OtherNumber },	// OTTOMAN SIYAQ ALTERNATE NUMBER TWO..OTTOMAN SIYAQ FRACTION ONE SIXTH
		{ 0x1ED3E, 0x1EDFF, Category::Unassigned },	// <reserved-1ED3E>..<reserved-1EDFF>
		{ 0x1EE00, 0x1EE03, Category::OtherLetter },	// ARABIC MATHEMATICAL ALEF..ARABIC MATHEMATICAL DAL
		{ 0x1EE04, 0x1EE04, Category::Unassigned },	// <reserved-1EE04>
		{ 0x1EE05, 0x1EE1F, Category::OtherLetter },	// ARABIC MATHEMATICAL WAW..ARABIC MATHEMATICAL DOTLESS QAF
		{ 0x1EE20, 0x1EE20, Category::Unassigned },	// <reserved-1EE20>
		{ 0x1EE21, 0x1EE22, Category::OtherLetter },	// ARABIC MATHEMATICAL INITIAL BEH..ARABIC MATHEMATICAL INITIAL JEEM
		{ 0x1EE23, 0x1EE23, Category::Unassigned },	// <reserved-1EE23>
		{ 0x1EE24, 0x1EE24, Category::OtherLetter },	// ARABIC MATHEMATICAL INITIAL HEH
		{ 0x1EE25, 0x1EE26, Category::Unassigned },	// <reserved-1EE25>..<reserved-1EE26>
		{ 0x1EE27, 0x1EE27, Category::OtherLetter },	// ARABIC MATHEMATICAL INITIAL HAH
		{ 0x1EE28, 0x1EE28, Category::Unassigned },	// <reserved-1EE28>
		{ 0x1EE29, 0x1EE32, Category::OtherLetter },	// ARABIC MATHEMATICAL INITIAL YEH..ARABIC MATHEMATICAL INITIAL QAF
		{ 0x1EE33, 0x1EE33, Category::Unassigned },	// <reserved-1EE33>
		{ 0x1EE34, 0x1EE37, Category::OtherLetter },	// ARABIC MATHEMATICAL INITIAL SHEEN..ARABIC MATHEMATICAL INITIAL KHAH
		{ 0x1EE38, 0x1EE38, Category::Unassigned },	// <reserved-1EE38>
		{ 0x1EE39, 0x1EE39, Category::OtherLetter },	// ARABIC MATHEMATICAL INITIAL DAD
		{ 0x1EE3A, 0x1EE3A, Category::Unassigned },	// <reserved-1EE3A>
		{ 0x1EE3B, 0x1EE3B, Category::OtherLetter },	// ARABIC MATHEMATICAL INITIAL GHAIN
		{ 0x1EE3C, 0x1EE41, Category::Unassigned },	// <reserved-1EE3C>..<reserved-1EE41>
		{ 0x1EE42, 0x1EE42, Category::OtherLetter },	// ARABIC MATHEMATICAL TAILED JEEM
		{ 0x1EE43, 0x1EE46, Category::Unassigned },	// <reserved-1EE43>..<reserved-1EE46>
		{ 0x1EE47, 0x1EE47, Category::OtherLetter },	// ARABIC MATHEMATICAL TAILED HAH
		{ 0x1EE48, 0x1EE48, Category::Unassigned },	// <reserved-1EE48>
		{ 0x1EE49, 0x1EE49, Category::OtherLetter },	// ARABIC MATHEMATICAL TAILED YEH
		{ 0x1EE4A, 0x1EE4A, Category::Unassigned },	// <reserved-1EE4A>
		{ 0x1EE4B, 0x1EE4B, Category::OtherLetter },	// ARABIC MATHEMATICAL TAILED LAM
		{ 0x1EE4C, 0x1EE4C, Category::Unassigned },	// <reserved-1EE4C>
		{ 0x1EE4D, 0x1EE4F, Category::OtherLetter },	// ARABIC MATHEMATICAL TAILED NOON..ARABIC MATHEMATICAL TAILED AIN
		{ 0x1EE50, 0x1EE50, Category::Unassigned },	// <reserved-1EE50>
		{ 0x1EE51, 0x1EE52, Category::OtherLetter },	// ARABIC MATHEMATICAL TAILED SAD..ARABIC MATHEMATICAL TAILED QAF
		{ 0x1EE53, 0x1EE53, Category::Unassigned },	// <reserved-1EE53>
		{ 0x1EE54, 0x1EE54, Category::OtherLetter },	// ARABIC MATHEMATICAL TAILED SHEEN
		{ 0x1EE55, 0x1EE56, Category::Unassigned },	// <reserved-1EE55>..<reserved-1EE56>
		{ 0x1EE57, 0x1EE57, Category::OtherLetter },	// ARABIC MATHEMATICAL TAILED KHAH
		{ 0x1EE58, 0x1EE58, Category::Unassigned },	// <reserved-1EE58>
		{ 0x1EE59, 0x1EE59, Category::OtherLetter },	// ARABIC MATHEMATICAL TAILED DAD
		{ 0x1EE5A, 0x1EE5A, Category::Unassigned },	// <reserved-1EE5A>
		{ 0x1EE5B, 0x1EE5B, Category::OtherLetter },	// ARABIC MATHEMATICAL TAILED GHAIN
		{ 0x1EE5C, 0x1EE5C, Category::Unassigned },	// <reserved-1EE5C>
		{ 0x1EE5D, 0x1EE5D, Category::OtherLetter },	// ARABIC MATHEMATICAL TAILED DOTLESS NOON
		{ 0x1EE5E, 0x1EE5E, Category::Unassigned },	// <reserved-1EE5E>
		{ 0x1EE5F, 0x1EE5F, Category::OtherLetter },	// ARABIC MATHEMATICAL TAILED DOTLESS QAF
		{ 0x1EE60, 0x1EE60, Category::Unassigned },	// <reserved-1EE60>
		{ 0x1EE61, 0x1EE62, Category::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED BEH..ARABIC MATHEMATICAL STRETCHED JEEM
		{ 0x1EE63, 0x1EE63, Category::Unassigned },	// <reserved-1EE63>
		{ 0x1EE64, 0x1EE64, Category::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED HEH
		{ 0x1EE65, 0x1EE66, Category::Unassigned },	// <reserved-1EE65>..<reserved-1EE66>
		{ 0x1EE67, 0x1EE6A, Category::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED HAH..ARABIC MATHEMATICAL STRETCHED KAF
		{ 0x1EE6B, 0x1EE6B, Category::Unassigned },	// <reserved-1EE6B>
		{ 0x1EE6C, 0x1EE72, Category::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED MEEM..ARABIC MATHEMATICAL STRETCHED QAF
		{ 0x1EE73, 0x1EE73, Category::Unassigned },	// <reserved-1EE73>
		{ 0x1EE74, 0x1EE77, Category::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED SHEEN..ARABIC MATHEMATICAL STRETCHED KHAH
		{ 0x1EE78, 0x1EE78, Category::Unassigned },	// <reserved-1EE78>
		{ 0x1EE79, 0x1EE7C, Category::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED DAD..ARABIC MATHEMATICAL STRETCHED DOTLESS BEH
		{ 0x1EE7D, 0x1EE7D, Category::Unassigned },	// <reserved-1EE7D>
		{ 0x1EE7E, 0x1EE7E, Category::OtherLetter },	// ARABIC MATHEMATICAL STRETCHED DOTLESS FEH
		{ 0x1EE7F, 0x1EE7F, Category::Unassigned },	// <reserved-1EE7F>
		{ 0x1EE80, 0x1EE89, Category::OtherLetter },	// ARABIC MATHEMATICAL LOOPED ALEF..ARABIC MATHEMATICAL LOOPED YEH
		{ 0x1EE8A, 0x1EE8A, Category::Unassigned },	// <reserved-1EE8A>
		{ 0x1EE8B, 0x1EE9B, Category::OtherLetter },	// ARABIC MATHEMATICAL LOOPED LAM..ARABIC MATHEMATICAL LOOPED GHAIN
		{ 0x1EE9C, 0x1EEA0, Category::Unassigned },	// <reserved-1EE9C>..<reserved-1EEA0>
		{ 0x1EEA1, 0x1EEA3, Category::OtherLetter },	// ARABIC MATHEMATICAL DOUBLE-STRUCK BEH..ARABIC MATHEMATICAL DOUBLE-STRUCK DAL
		{ 0x1EEA4, 0x1EEA4, Category::Unassigned },	// <reserved-1EEA4>
		{ 0x1EEA5, 0x1EEA9, Category::OtherLetter },	// ARABIC MATHEMATICAL DOUBLE-STRUCK WAW..ARABIC MATHEMATICAL DOUBLE-STRUCK YEH
		{ 0x1EEAA, 0x1EEAA, Category::Unassigned },	// <reserved-1EEAA>
		{ 0x1EEAB, 0x1EEBB, Category::OtherLetter },	// ARABIC MATHEMATICAL DOUBLE-STRUCK LAM..ARABIC MATHEMATICAL DOUBLE-STRUCK GHAIN
		{ 0x1EEBC, 0x1EEEF, Category::Unassigned },	// <reserved-1EEBC>..<reserved-1EEEF>
		{ 0x1EEF0, 0x1EEF1, Category::MathSymbol },	// ARABIC MATHEMATICAL OPERATOR MEEM WITH HAH WITH TATWEEL..ARABIC MATHEMATICAL OPERATOR HAH WITH DAL
		{ 0x1EEF2, 0x1EFFF, Category::Unassigned },	// <reserved-1EEF2>..<reserved-1EFFF>
		{ 0x1F000, 0x1F02B, Category::OtherSymbol },	// MAHJONG TILE EAST WIND..MAHJONG TILE BACK
		{ 0x1F02C, 0x1F02F, Category::Unassigned },	// <reserved-1F02C>..<reserved-1F02F>
		{ 0x1F030, 0x1F093, Category::OtherSymbol },	// DOMINO TILE HORIZONTAL BACK..DOMINO TILE VERTICAL-06-06
		{ 0x1F094, 0x1F09F, Category::Unassigned },	// <reserved-1F094>..<reserved-1F09F>
		{ 0x1F0A0, 0x1F0AE, Category::OtherSymbol },	// PLAYING CARD BACK..PLAYING CARD KING OF SPADES
		{ 0x1F0AF, 0x1F0B0, Category::Unassigned },	// <reserved-1F0AF>..<reserved-1F0B0>
		{ 0x1F0B1, 0x1F0BF, Category::OtherSymbol },	// PLAYING CARD ACE OF HEARTS..PLAYING CARD RED JOKER
		{ 0x1F0C0, 0x1F0C0, Category::Unassigned },	// <reserved-1F0C0>
		{ 0x1F0C1, 0x1F0CF, Category::OtherSymbol },	// PLAYING CARD ACE OF DIAMONDS..PLAYING CARD BLACK JOKER
		{ 0x1F0D0, 0x1F0D0, Category::Unassigned },	// <reserved-1F0D0>
		{ 0x1F0D1, 0x1F0F5, Category::OtherSymbol },	// PLAYING CARD ACE OF CLUBS..PLAYING CARD TRUMP-21
		{ 0x1F0F6, 0x1F0FF, Category::Unassigned },	// <reserved-1F0F6>..<reserved-1F0FF>
		{ 0x1F100, 0x1F10C, Category::OtherNumber },	// DIGIT ZERO FULL STOP..DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ZERO
		{ 0x1F10D, 0x1F1AD, Category::OtherSymbol },	// CIRCLED ZERO WITH SLASH..MASK WORK SYMBOL
		{ 0x1F1AE, 0x1F1E5, Category::Unassigned },	// <reserved-1F1AE>..<reserved-1F1E5>
		{ 0x1F1E6, 0x1F202, Category::OtherSymbol },	// REGIONAL INDICATOR SYMBOL LETTER A..SQUARED KATAKANA SA
		{ 0x1F203, 0x1F20F, Category::Unassigned },	// <reserved-1F203>..<reserved-1F20F>
		{ 0x1F210, 0x1F23B, Category::OtherSymbol },	// SQUARED CJK UNIFIED IDEOGRAPH-624B..SQUARED CJK UNIFIED IDEOGRAPH-914D
		{ 0x1F23C, 0x1F23F, Category::Unassigned },	// <reserved-1F23C>..<reserved-1F23F>
		{ 0x1F240, 0x1F248, Category::OtherSymbol },	// TORTOISE SHELL BRACKETED CJK UNIFIED IDEOGRAPH-672C..TORTOISE SHELL BRACKETED CJK UNIFIED IDEOGRAPH-6557
		{ 0x1F249, 0x1F24F, Category::Unassigned },	// <reserved-1F249>..<reserved-1F24F>
		{ 0x1F250, 0x1F251, Category::OtherSymbol },	// CIRCLED IDEOGRAPH ADVANTAGE..CIRCLED IDEOGRAPH ACCEPT
		{ 0x1F252, 0x1F25F, Category::Unassigned },	// <reserved-1F252>..<reserved-1F25F>
		{ 0x1F260, 0x1F265, Category::OtherSymbol },	// ROUNDED SYMBOL FOR FU..ROUNDED SYMBOL FOR CAI
		{ 0x1F266, 0x1F2FF, Category::Unassigned },	// <reserved-1F266>..<reserved-1F2FF>
		{ 0x1F300, 0x1F3FA, Category::OtherSymbol },	// CYCLONE..AMPHORA
		{ 0x1F3FB, 0x1F3FF, Category::ModifierSymbol },	// EMOJI MODIFIER FITZPATRICK TYPE-1-2..EMOJI MODIFIER FITZPATRICK TYPE-6
		{ 0x1F400, 0x1F6D7, Category::OtherSymbol },	// RAT..ELEVATOR
		{ 0x1F6D8, 0x1F6DB, Category::Unassigned },	// <reserved-1F6D8>..<reserved-1F6DB>
		{ 0x1F6DC, 0x1F6EC, Category::OtherSymbol },	// WIRELESS..AIRPLANE ARRIVING
		{ 0x1F6ED, 0x1F6EF, Category::Unassigned },	// <reserved-1F6ED>..<reserved-1F6EF>
		{ 0x1F6F0, 0x1F6FC, Category::OtherSymbol },	// SATELLITE..ROLLER SKATE
		{ 0x1F6FD, 0x1F6FF, Category::Unassigned },	// <reserved-1F6FD>..<reserved-1F6FF>
		{ 0x1F700, 0x1F776, Category::OtherSymbol },	// ALCHEMICAL SYMBOL FOR QUINTESSENCE..LUNAR ECLIPSE
		{ 0x1F777, 0x1F77A, Category::Unassigned },	// <reserved-1F777>..<reserved-1F77A>
		{ 0x1F77B, 0x1F7D9, Category::OtherSymbol },	// HAUMEA..NINE POINTED WHITE STAR
		{ 0x1F7DA, 0x1F7DF, Category::Unassigned },	// <reserved-1F7DA>..<reserved-1F7DF>
		{ 0x1F7E0, 0x1F7EB, Category::OtherSymbol },	// LARGE ORANGE CIRCLE..LARGE BROWN SQUARE
		{ 0x1F7EC, 0x1F7EF, Category::Unassigned },	// <reserved-1F7EC>..<reserved-1F7EF>
		{ 0x1F7F0, 0x1F7F0, Category::OtherSymbol },	// HEAVY EQUALS SIGN
		{ 0x1F7F1, 0x1F7FF, Category::Unassigned },	// <reserved-1F7F1>..<reserved-1F7FF>
		{ 0x1F800, 0x1F80B, Category::OtherSymbol },	// LEFTWARDS ARROW WITH SMALL TRIANGLE ARROWHEAD..DOWNWARDS ARROW WITH LARGE TRIANGLE ARROWHEAD
		{ 0x1F80C, 0x1F80F, Category::Unassigned },	// <reserved-1F80C>..<reserved-1F80F>
		{ 0x1F810, 0x1F847, Category::OtherSymbol },	// LEFTWARDS ARROW WITH SMALL EQUILATERAL ARROWHEAD..DOWNWARDS HEAVY ARROW
		{ 0x1F848, 0x1F84F, Category::Unassigned },	// <reserved-1F848>..<reserved-1F84F>
		{ 0x1F850, 0x1F859, Category::OtherSymbol },	// LEFTWARDS SANS-SERIF ARROW..UP DOWN SANS-SERIF ARROW
		{ 0x1F85A, 0x1F85F, Category::Unassigned },	// <reserved-1F85A>..<reserved-1F85F>
		{ 0x1F860, 0x1F887, Category::OtherSymbol },	// WIDE-HEADED LEFTWARDS LIGHT BARB ARROW..WIDE-HEADED SOUTH WEST VERY HEAVY BARB ARROW
		{ 0x1F888, 0x1F88F, Category::Unassigned },	// <reserved-1F888>..<reserved-1F88F>
		{ 0x1F890, 0x1F8AD, Category::OtherSymbol },	// LEFTWARDS TRIANGLE ARROWHEAD..WHITE ARROW SHAFT WIDTH TWO THIRDS
		{ 0x1F8AE, 0x1F8AF, Category::Unassigned },	// <reserved-1F8AE>..<reserved-1F8AF>
		{ 0x1F8B0, 0x1F8BB, Category::OtherSymbol },	// ARROW POINTING UPWARDS THEN NORTH WEST..SOUTH WEST ARROW FROM BAR
		{ 0x1F8BC, 0x1F8BF, Category::Unassigned },	// <reserved-1F8BC>..<reserved-1F8BF>
		{ 0x1F8C0, 0x1F8C1, Category::OtherSymbol },	// LEFTWARDS ARROW FROM DOWNWARDS ARROW..RIGHTWARDS ARROW FROM DOWNWARDS ARROW
		{ 0x1F8C2, 0x1F8FF, Category::Unassigned },	// <reserved-1F8C2>..<reserved-1F8FF>
		{ 0x1F900, 0x1FA53, Category::OtherSymbol },	// CIRCLED CROSS FORMEE WITH FOUR DOTS..BLACK CHESS KNIGHT-BISHOP
		{ 0x1FA54, 0x1FA5F, Category::Unassigned },	// <reserved-1FA54>..<reserved-1FA5F>
		{ 0x1FA60, 0x1FA6D, Category::OtherSymbol },	// XIANGQI RED GENERAL..XIANGQI BLACK SOLDIER
		{ 0x1FA6E, 0x1FA6F, Category::Unassigned },	// <reserved-1FA6E>..<reserved-1FA6F>
		{ 0x1FA70, 0x1FA7C, Category::OtherSymbol },	// BALLET SHOES..CRUTCH
		{ 0x1FA7D, 0x1FA7F, Category::Unassigned },	// <reserved-1FA7D>..<reserved-1FA7F>
		{ 0x1FA80, 0x1FA89, Category::OtherSymbol },	// YO-YO..HARP
		{ 0x1FA8A, 0x1FA8E, Category::Unassigned },	// <reserved-1FA8A>..<reserved-1FA8E>
		{ 0x1FA8F, 0x1FAC6, Category::OtherSymbol },	// SHOVEL..FINGERPRINT
		{ 0x1FAC7, 0x1FACD, Category::Unassigned },	// <reserved-1FAC7>..<reserved-1FACD>
		{ 0x1FACE, 0x1FADC, Category::OtherSymbol },	// MOOSE..ROOT VEGETABLE
		{ 0x1FADD, 0x1FADE, Category::Unassigned },	// <reserved-1FADD>..<reserved-1FADE>
		{ 0x1FADF, 0x1FAE9, Category::OtherSymbol },	// SPLATTER..FACE WITH BAGS UNDER EYES
		{ 0x1FAEA, 0x1FAEF, Category::Unassigned },	// <reserved-1FAEA>..<reserved-1FAEF>
		{ 0x1FAF0, 0x1FAF8, Category::OtherSymbol },	// HAND WITH INDEX FINGER AND THUMB CROSSED..RIGHTWARDS PUSHING HAND
		{ 0x1FAF9, 0x1FAFF, Category::Unassigned },	// <reserved-1FAF9>..<reserved-1FAFF>
		{ 0x1FB00, 0x1FB92, Category::OtherSymbol },	// BLOCK SEXTANT-1..UPPER HALF INVERSE MEDIUM SHADE AND LOWER HALF BLOCK
		{ 0x1FB93, 0x1FB93, Category::Unassigned },	// <reserved-1FB93>
		{ 0x1FB94, 0x1FBEF, Category::OtherSymbol },	// LEFT HALF INVERSE MEDIUM SHADE AND RIGHT HALF BLOCK..TOP LEFT JUSTIFIED LOWER RIGHT QUARTER BLACK CIRCLE
		{ 0x1FBF0, 0x1FBF9, Category::DecimalNumber },	// SEGMENTED DIGIT ZERO..SEGMENTED DIGIT NINE
		{ 0x1FBFA, 0x1FFFF, Category::Unassigned },	// <reserved-1FBFA>..<noncharacter-1FFFF>
		{ 0x20000, 0x2A6DF, Category::OtherLetter },	// CJK UNIFIED IDEOGRAPH-20000..CJK UNIFIED IDEOGRAPH-2A6DF
		{ 0x2A6E0, 0x2A6FF, Category::Unassigned },	// <reserved-2A6E0>..<reserved-2A6FF>
		{ 0x2A700, 0x2B739, Category::OtherLetter },	// CJK UNIFIED IDEOGRAPH-2A700..CJK UNIFIED IDEOGRAPH-2B739
		{ 0x2B73A, 0x2B73F, Category::Unassigned },	// <reserved-2B73A>..<reserved-2B73F>
		{ 0x2B740, 0x2B81D, Category::OtherLetter },	// CJK UNIFIED IDEOGRAPH-2B740..CJK UNIFIED IDEOGRAPH-2B81D
		{ 0x2B81E, 0x2B81F, Category::Unassigned },	// <reserved-2B81E>..<reserved-2B81F>
		{ 0x2B820, 0x2CEA1, Category::OtherLetter },	// CJK UNIFIED IDEOGRAPH-2B820..CJK UNIFIED IDEOGRAPH-2CEA1
		{ 0x2CEA2, 0x2CEAF, Category::Unassigned },	// <reserved-2CEA2>..<reserved-2CEAF>
		{ 0x2CEB0, 0x2EBE0, Category::OtherLetter },	// CJK UNIFIED IDEOGRAPH-2CEB0..CJK UNIFIED IDEOGRAPH-2EBE0
		{ 0x2EBE1, 0x2EBEF, Category::Unassigned },	// <reserved-2EBE1>..<reserved-2EBEF>
		{ 0x2EBF0, 0x2EE5D, Category::OtherLetter },	// CJK UNIFIED IDEOGRAPH-2EBF0..CJK UNIFIED IDEOGRAPH-2EE5D
		{ 0x2EE5E, 0x2F7FF, Category::Unassigned },	// <reserved-2EE5E>..<reserved-2F7FF>
		{ 0x2F800, 0x2FA1D, Category::OtherLetter },	// CJK COMPATIBILITY IDEOGRAPH-2F800..CJK COMPATIBILITY IDEOGRAPH-2FA1D
		{ 0x2FA1E, 0x2FFFF, Category::Unassigned },	// <reserved-2FA1E>..<noncharacter-2FFFF>
		{ 0x30000, 0x3134A, Category::OtherLetter },	// CJK UNIFIED IDEOGRAPH-30000..CJK UNIFIED IDEOGRAPH-3134A
		{ 0x3134B, 0x3134F, Category::Unassigned },	// <reserved-3134B>..<reserved-3134F>
		{ 0x31350, 0x323AF, Category::OtherLetter },	// CJK UNIFIED IDEOGRAPH-31350..CJK UNIFIED IDEOGRAPH-323AF
		{ 0x323B0, 0xE0000, Category::Unassigned },	// <reserved-323B0>..<reserved-E0000>
		{ 0xE0001, 0xE0001, Category::Format },	// LANGUAGE TAG
		{ 0xE0002, 0xE001F, Category::Unassigned },	// <reserved-E0002>..<reserved-E001F>
		{ 0xE0020, 0xE007F, Category::Format },	// TAG SPACE..CANCEL TAG
		{ 0xE0080, 0xE00FF, Category::Unassigned },	// <reserved-E0080>..<reserved-E00FF>
		{ 0xE0100, 0xE01EF, Category::NonspacingMark },	// VARIATION SELECTOR-17..VARIATION SELECTOR-256
		{ 0xE01F0, 0xEFFFF, Category::Unassigned },	// <reserved-E01F0>..<noncharacter-EFFFF>
		{ 0xF0000, 0xFFFFD, Category::PrivateUse },	// <private-use-F0000>..<private-use-FFFFD>
		{ 0xFFFFE, 0xFFFFF, Category::Unassigned },	// <noncharacter-FFFFE>..<noncharacter-FFFFF>
		{ 0x100000, 0x10FFFD, Category::PrivateUse },	// <private-use-100000>..<private-use-10FFFD>
		{ 0x10FFFE, 0x10FFFF, Category::Unassigned },	// <noncharacter-10FFFE>..<noncharacter-10FFFF>
	});

	Category GetCategory(uint32_t codePoint)
	{
		// Find first entry whose .end is not < codePoint.
		auto it = std::lower_bound(CategoryRanges.begin(), CategoryRanges.end(), codePoint, [](const Entry& entry, uint32_t cp) {
			return entry.end < cp;
		});

		if (it != CategoryRanges.end() && it->start <= codePoint)
		{
			return it->category;
		}

		return Category::Unknown;
	}



	/*

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

			if (it->category == Category::NonspacingMark || it->category == Category::SpacingMark || it->category == Category::EnclosingMark)
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
	*/
};

