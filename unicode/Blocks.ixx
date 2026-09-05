// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cstdint>

export module unicode.blocks;

import std;


namespace unicode::blocks
{
	// https://www.unicode.org/Public/12.0.0/ucd/Blocks.txt

	export enum class Name
	{
		Adlam,
		AegeanNumbers, 
		Ahom, 
		AlchemicalSymbols, 
		AlphabeticPresentationForms, 
		AnatolianHieroglyphs, 
		AncientGreekMusicalNotation, 
		AncientGreekNumbers, 
		AncientSymbols, 
		Arabic, 
		ArabicExtendedA, 
		ArabicMathematicalAlphabeticSymbols, 
		ArabicPresentationFormsA, 
		ArabicPresentationFormsB, 
		ArabicSupplement, 
		Armenian, 
		Arrows, 
		Avestan, 
		Balinese, 
		Bamum, 
		BamumSupplement, 
		BasicLatin, 
		BassaVah, 
		Batak, 
		Bengali, 
		Bhaiksuki, 
		BlockElements, 
		Bopomofo, 
		BopomofoExtended, 
		BoxDrawing, 
		Brahmi, 
		BraillePatterns, 
		Buginese, 
		Buhid, 
		ByzantineMusicalSymbols, 
		CJKCompatibility, 
		CJKCompatibilityForms, 
		CJKCompatibilityIdeographs, 
		CJKCompatibilityIdeographsSupplement, 
		CJKRadicalsSupplement, 
		CJKStrokes, 
		CJKSymbolsandPunctuation, 
		CJKUnifiedIdeographs, 
		CJKUnifiedIdeographsExtensionA, 
		CJKUnifiedIdeographsExtensionB, 
		CJKUnifiedIdeographsExtensionC, 
		CJKUnifiedIdeographsExtensionD, 
		CJKUnifiedIdeographsExtensionE, 
		CJKUnifiedIdeographsExtensionF, 
		Carian, 
		CaucasianAlbanian, 
		Chakma, 
		Cham, 
		Cherokee, 
		CherokeeSupplement, 
		ChessSymbols, 
		CombiningDiacriticalMarks, 
		CombiningDiacriticalMarksExtended, 
		CombiningDiacriticalMarksSupplement, 
		CombiningDiacriticalMarksforSymbols, 
		CombiningHalfMarks, 
		CommonIndicNumberForms, 
		ControlPictures, 
		Coptic, 
		CopticEpactNumbers, 
		CountingRodNumerals, 
		Cuneiform, 
		CuneiformNumbersandPunctuation, 
		CurrencySymbols, 
		CypriotSyllabary, 
		Cyrillic, 
		CyrillicExtendedA, 
		CyrillicExtendedB, 
		CyrillicExtendedC, 
		CyrillicSupplement, 
		Deseret, 
		Devanagari, 
		DevanagariExtended, 
		Dingbats, 
		Dogra, 
		DominoTiles, 
		Duployan, 
		EarlyDynasticCuneiform, 
		EgyptianHieroglyphFormatControls, 
		EgyptianHieroglyphs, 
		Elbasan, 
		Elymaic, 
		Emoticons, 
		EnclosedAlphanumericSupplement, 
		EnclosedAlphanumerics, 
		EnclosedCJKLettersandMonths, 
		EnclosedIdeographicSupplement, 
		Ethiopic, 
		EthiopicExtended, 
		EthiopicExtendedA, 
		EthiopicSupplement, 
		GeneralPunctuation, 
		GeometricShapes, 
		GeometricShapesExtended, 
		Georgian, 
		GeorgianExtended, 
		GeorgianSupplement, 
		Glagolitic, 
		GlagoliticSupplement, 
		Gothic, 
		Grantha, 
		GreekExtended, 
		GreekandCoptic, 
		Gujarati, 
		GunjalaGondi, 
		Gurmukhi, 
		HalfwidthandFullwidthForms, 
		HangulCompatibilityJamo, 
		HangulJamo, 
		HangulJamoExtendedA, 
		HangulJamoExtendedB, 
		HangulSyllables, 
		HanifiRohingya, 
		Hanunoo, 
		Hatran, 
		Hebrew, 
		HighPrivateUseSurrogates, 
		HighSurrogates, 
		Hiragana, 
		IPAExtensions, 
		IdeographicDescriptionCharacters, 
		IdeographicSymbolsandPunctuation, 
		ImperialAramaic, 
		IndicSiyaqNumbers, 
		InscriptionalPahlavi, 
		InscriptionalParthian, 
		Javanese, 
		Kaithi, 
		KanaExtendedA, 
		KanaSupplement, 
		Kanbun, 
		KangxiRadicals, 
		Kannada, 
		Katakana, 
		KatakanaPhoneticExtensions, 
		KayahLi, 
		Kharoshthi, 
		Khmer, 
		KhmerSymbols, 
		Khojki, 
		Khudawadi, 
		Lao, 
		Latin1Supplement, 
		LatinExtendedA, 
		LatinExtendedAdditional, 
		LatinExtendedB, 
		LatinExtendedC, 
		LatinExtendedD, 
		LatinExtendedE, 
		Lepcha, 
		LetterlikeSymbols, 
		Limbu, 
		LinearA, 
		LinearBIdeograms, 
		LinearBSyllabary, 
		Lisu, 
		LowSurrogates, 
		Lycian, 
		Lydian, 
		Mahajani, 
		MahjongTiles, 
		Makasar, 
		Malayalam, 
		Mandaic, 
		Manichaean, 
		Marchen, 
		MasaramGondi, 
		MathematicalAlphanumericSymbols, 
		MathematicalOperators, 
		MayanNumerals, 
		Medefaidrin, 
		MeeteiMayek, 
		MeeteiMayekExtensions, 
		MendeKikakui, 
		MeroiticCursive, 
		MeroiticHieroglyphs, 
		Miao, 
		MiscellaneousMathematicalSymbolsA, 
		MiscellaneousMathematicalSymbolsB, 
		MiscellaneousSymbols, 
		MiscellaneousSymbolsandArrows, 
		MiscellaneousSymbolsandPictographs, 
		MiscellaneousTechnical, 
		Modi, 
		ModifierToneLetters, 
		Mongolian, 
		MongolianSupplement, 
		Mro, 
		Multani, 
		MusicalSymbols, 
		Myanmar, 
		MyanmarExtendedA, 
		MyanmarExtendedB, 
		NKo, 
		Nabataean, 
		Nandinagari, 
		NewTaiLue, 
		Newa, 
		NumberForms, 
		Nushu, 
		NyiakengPuachueHmong, 
		Ogham, 
		OlChiki, 
		OldHungarian, 
		OldItalic, 
		OldNorthArabian, 
		OldPermic, 
		OldPersian, 
		OldSogdian, 
		OldSouthArabian, 
		OldTurkic, 
		OpticalCharacterRecognition, 
		Oriya, 
		OrnamentalDingbats, 
		Osage, 
		Osmanya, 
		OttomanSiyaqNumbers, 
		PahawhHmong, 
		Palmyrene, 
		PauCinHau, 
		Phagspa, 
		PhaistosDisc, 
		Phoenician, 
		PhoneticExtensions, 
		PhoneticExtensionsSupplement, 
		PlayingCards, 
		PrivateUseArea, 
		PsalterPahlavi, 
		Rejang, 
		RumiNumeralSymbols, 
		Runic, 
		Samaritan, 
		Saurashtra, 
		Sharada, 
		Shavian, 
		ShorthandFormatControls, 
		Siddham, 
		Sinhala, 
		SinhalaArchaicNumbers, 
		SmallFormVariants, 
		SmallKanaExtension, 
		Sogdian, 
		SoraSompeng, 
		Soyombo, 
		SpacingModifierLetters, 
		Specials, 
		Sundanese, 
		SundaneseSupplement, 
		SuperscriptsandSubscripts, 
		SupplementalArrowsA, 
		SupplementalArrowsB, 
		SupplementalArrowsC, 
		SupplementalMathematicalOperators, 
		SupplementalPunctuation, 
		SupplementalSymbolsandPictographs, 
		SupplementaryPrivateUseAreaA, 
		SupplementaryPrivateUseAreaB, 
		SuttonSignWriting, 
		SylotiNagri, 
		SymbolsandPictographsExtendedA, 
		Syriac, 
		SyriacSupplement, 
		Tagalog, 
		Tagbanwa, 
		Tags, 
		TaiLe, 
		TaiTham, 
		TaiViet, 
		TaiXuanJingSymbols, 
		Takri, 
		Tamil, 
		TamilSupplement, 
		Tangut, 
		TangutComponents, 
		Telugu, 
		Thaana, 
		Thai, 
		Tibetan, 
		Tifinagh, 
		Tirhuta, 
		TransportandMapSymbols, 
		Ugaritic, 
		UnifiedCanadianAboriginalSyllabics, 
		UnifiedCanadianAboriginalSyllabicsExtended, 
		Vai, 
		VariationSelectors, 
		VariationSelectorsSupplement, 
		VedicExtensions, 
		VerticalForms, 
		Wancho, 
		WarangCiti, 
		YiRadicals, 
		YiSyllables, 
		YijingHexagramSymbols, 
		ZanabazarSquare, 
	};


	export struct Entry
	{
		uint32_t start;
		uint32_t end;
		Name name;
	};


	// TODO Needs to be in .ixx file for constexpr GetBlock(). Consider moving to partition.
	static constexpr auto BlockRanges = std::to_array<Entry>(
	{
		{ 0x1E900, 0x1E95F, Name::Adlam },	// Adlam
		{ 0x10100, 0x1013F, Name::AegeanNumbers },	// Aegean Numbers
		{ 0x11700, 0x1173F, Name::Ahom },	// Ahom
		{ 0x1F700, 0x1F77F, Name::AlchemicalSymbols },	// Alchemical Symbols
		{ 0xFB00, 0xFB4F, Name::AlphabeticPresentationForms },	// Alphabetic Presentation Forms
		{ 0x14400, 0x1467F, Name::AnatolianHieroglyphs },	// Anatolian Hieroglyphs
		{ 0x1D200, 0x1D24F, Name::AncientGreekMusicalNotation },	// Ancient Greek Musical Notation
		{ 0x10140, 0x1018F, Name::AncientGreekNumbers },	// Ancient Greek Numbers
		{ 0x10190, 0x101CF, Name::AncientSymbols },	// Ancient Symbols
		{ 0x0600, 0x06FF, Name::Arabic },	// Arabic
		{ 0x08A0, 0x08FF, Name::ArabicExtendedA },	// Arabic Extended-A
		{ 0x1EE00, 0x1EEFF, Name::ArabicMathematicalAlphabeticSymbols },	// Arabic Mathematical Alphabetic Symbols
		{ 0xFB50, 0xFDFF, Name::ArabicPresentationFormsA },	// Arabic Presentation Forms-A
		{ 0xFE70, 0xFEFF, Name::ArabicPresentationFormsB },	// Arabic Presentation Forms-B
		{ 0x0750, 0x077F, Name::ArabicSupplement },	// Arabic Supplement
		{ 0x0530, 0x058F, Name::Armenian },	// Armenian
		{ 0x2190, 0x21FF, Name::Arrows },	// Arrows
		{ 0x10B00, 0x10B3F, Name::Avestan },	// Avestan
		{ 0x1B00, 0x1B7F, Name::Balinese },	// Balinese
		{ 0xA6A0, 0xA6FF, Name::Bamum },	// Bamum
		{ 0x16800, 0x16A3F, Name::BamumSupplement },	// Bamum Supplement
		{ 0x0000, 0x007F, Name::BasicLatin },	// Basic Latin
		{ 0x16AD0, 0x16AFF, Name::BassaVah },	// Bassa Vah
		{ 0x1BC0, 0x1BFF, Name::Batak },	// Batak
		{ 0x0980, 0x09FF, Name::Bengali },	// Bengali
		{ 0x11C00, 0x11C6F, Name::Bhaiksuki },	// Bhaiksuki
		{ 0x2580, 0x259F, Name::BlockElements },	// Block Elements
		{ 0x3100, 0x312F, Name::Bopomofo },	// Bopomofo
		{ 0x31A0, 0x31BF, Name::BopomofoExtended },	// Bopomofo Extended
		{ 0x2500, 0x257F, Name::BoxDrawing },	// Box Drawing
		{ 0x11000, 0x1107F, Name::Brahmi },	// Brahmi
		{ 0x2800, 0x28FF, Name::BraillePatterns },	// Braille Patterns
		{ 0x1A00, 0x1A1F, Name::Buginese },	// Buginese
		{ 0x1740, 0x175F, Name::Buhid },	// Buhid
		{ 0x1D000, 0x1D0FF, Name::ByzantineMusicalSymbols },	// Byzantine Musical Symbols
		{ 0x3300, 0x33FF, Name::CJKCompatibility },	// CJK Compatibility
		{ 0xFE30, 0xFE4F, Name::CJKCompatibilityForms },	// CJK Compatibility Forms
		{ 0xF900, 0xFAFF, Name::CJKCompatibilityIdeographs },	// CJK Compatibility Ideographs
		{ 0x2F800, 0x2FA1F, Name::CJKCompatibilityIdeographsSupplement },	// CJK Compatibility Ideographs Supplement
		{ 0x2E80, 0x2EFF, Name::CJKRadicalsSupplement },	// CJK Radicals Supplement
		{ 0x31C0, 0x31EF, Name::CJKStrokes },	// CJK Strokes
		{ 0x3000, 0x303F, Name::CJKSymbolsandPunctuation },	// CJK Symbols and Punctuation
		{ 0x4E00, 0x9FFF, Name::CJKUnifiedIdeographs },	// CJK Unified Ideographs
		{ 0x3400, 0x4DBF, Name::CJKUnifiedIdeographsExtensionA },	// CJK Unified Ideographs Extension A
		{ 0x20000, 0x2A6DF, Name::CJKUnifiedIdeographsExtensionB },	// CJK Unified Ideographs Extension B
		{ 0x2A700, 0x2B73F, Name::CJKUnifiedIdeographsExtensionC },	// CJK Unified Ideographs Extension C
		{ 0x2B740, 0x2B81F, Name::CJKUnifiedIdeographsExtensionD },	// CJK Unified Ideographs Extension D
		{ 0x2B820, 0x2CEAF, Name::CJKUnifiedIdeographsExtensionE },	// CJK Unified Ideographs Extension E
		{ 0x2CEB0, 0x2EBEF, Name::CJKUnifiedIdeographsExtensionF },	// CJK Unified Ideographs Extension F
		{ 0x102A0, 0x102DF, Name::Carian },	// Carian
		{ 0x10530, 0x1056F, Name::CaucasianAlbanian },	// Caucasian Albanian
		{ 0x11100, 0x1114F, Name::Chakma },	// Chakma
		{ 0xAA00, 0xAA5F, Name::Cham },	// Cham
		{ 0x13A0, 0x13FF, Name::Cherokee },	// Cherokee
		{ 0xAB70, 0xABBF, Name::CherokeeSupplement },	// Cherokee Supplement
		{ 0x1FA00, 0x1FA6F, Name::ChessSymbols },	// Chess Symbols
		{ 0x0300, 0x036F, Name::CombiningDiacriticalMarks },	// Combining Diacritical Marks
		{ 0x1AB0, 0x1AFF, Name::CombiningDiacriticalMarksExtended },	// Combining Diacritical Marks Extended
		{ 0x1DC0, 0x1DFF, Name::CombiningDiacriticalMarksSupplement },	// Combining Diacritical Marks Supplement
		{ 0x20D0, 0x20FF, Name::CombiningDiacriticalMarksforSymbols },	// Combining Diacritical Marks for Symbols
		{ 0xFE20, 0xFE2F, Name::CombiningHalfMarks },	// Combining Half Marks
		{ 0xA830, 0xA83F, Name::CommonIndicNumberForms },	// Common Indic Number Forms
		{ 0x2400, 0x243F, Name::ControlPictures },	// Control Pictures
		{ 0x2C80, 0x2CFF, Name::Coptic },	// Coptic
		{ 0x102E0, 0x102FF, Name::CopticEpactNumbers },	// Coptic Epact Numbers
		{ 0x1D360, 0x1D37F, Name::CountingRodNumerals },	// Counting Rod Numerals
		{ 0x12000, 0x123FF, Name::Cuneiform },	// Cuneiform
		{ 0x12400, 0x1247F, Name::CuneiformNumbersandPunctuation },	// Cuneiform Numbers and Punctuation
		{ 0x20A0, 0x20CF, Name::CurrencySymbols },	// Currency Symbols
		{ 0x10800, 0x1083F, Name::CypriotSyllabary },	// Cypriot Syllabary
		{ 0x0400, 0x04FF, Name::Cyrillic },	// Cyrillic
		{ 0x2DE0, 0x2DFF, Name::CyrillicExtendedA },	// Cyrillic Extended-A
		{ 0xA640, 0xA69F, Name::CyrillicExtendedB },	// Cyrillic Extended-B
		{ 0x1C80, 0x1C8F, Name::CyrillicExtendedC },	// Cyrillic Extended-C
		{ 0x0500, 0x052F, Name::CyrillicSupplement },	// Cyrillic Supplement
		{ 0x10400, 0x1044F, Name::Deseret },	// Deseret
		{ 0x0900, 0x097F, Name::Devanagari },	// Devanagari
		{ 0xA8E0, 0xA8FF, Name::DevanagariExtended },	// Devanagari Extended
		{ 0x2700, 0x27BF, Name::Dingbats },	// Dingbats
		{ 0x11800, 0x1184F, Name::Dogra },	// Dogra
		{ 0x1F030, 0x1F09F, Name::DominoTiles },	// Domino Tiles
		{ 0x1BC00, 0x1BC9F, Name::Duployan },	// Duployan
		{ 0x12480, 0x1254F, Name::EarlyDynasticCuneiform },	// Early Dynastic Cuneiform
		{ 0x13430, 0x1343F, Name::EgyptianHieroglyphFormatControls },	// Egyptian Hieroglyph Format Controls
		{ 0x13000, 0x1342F, Name::EgyptianHieroglyphs },	// Egyptian Hieroglyphs
		{ 0x10500, 0x1052F, Name::Elbasan },	// Elbasan
		{ 0x10FE0, 0x10FFF, Name::Elymaic },	// Elymaic
		{ 0x1F600, 0x1F64F, Name::Emoticons },	// Emoticons
		{ 0x1F100, 0x1F1FF, Name::EnclosedAlphanumericSupplement },	// Enclosed Alphanumeric Supplement
		{ 0x2460, 0x24FF, Name::EnclosedAlphanumerics },	// Enclosed Alphanumerics
		{ 0x3200, 0x32FF, Name::EnclosedCJKLettersandMonths },	// Enclosed CJK Letters and Months
		{ 0x1F200, 0x1F2FF, Name::EnclosedIdeographicSupplement },	// Enclosed Ideographic Supplement
		{ 0x1200, 0x137F, Name::Ethiopic },	// Ethiopic
		{ 0x2D80, 0x2DDF, Name::EthiopicExtended },	// Ethiopic Extended
		{ 0xAB00, 0xAB2F, Name::EthiopicExtendedA },	// Ethiopic Extended-A
		{ 0x1380, 0x139F, Name::EthiopicSupplement },	// Ethiopic Supplement
		{ 0x2000, 0x206F, Name::GeneralPunctuation },	// General Punctuation
		{ 0x25A0, 0x25FF, Name::GeometricShapes },	// Geometric Shapes
		{ 0x1F780, 0x1F7FF, Name::GeometricShapesExtended },	// Geometric Shapes Extended
		{ 0x10A0, 0x10FF, Name::Georgian },	// Georgian
		{ 0x1C90, 0x1CBF, Name::GeorgianExtended },	// Georgian Extended
		{ 0x2D00, 0x2D2F, Name::GeorgianSupplement },	// Georgian Supplement
		{ 0x2C00, 0x2C5F, Name::Glagolitic },	// Glagolitic
		{ 0x1E000, 0x1E02F, Name::GlagoliticSupplement },	// Glagolitic Supplement
		{ 0x10330, 0x1034F, Name::Gothic },	// Gothic
		{ 0x11300, 0x1137F, Name::Grantha },	// Grantha
		{ 0x1F00, 0x1FFF, Name::GreekExtended },	// Greek Extended
		{ 0x0370, 0x03FF, Name::GreekandCoptic },	// Greek and Coptic
		{ 0x0A80, 0x0AFF, Name::Gujarati },	// Gujarati
		{ 0x11D60, 0x11DAF, Name::GunjalaGondi },	// Gunjala Gondi
		{ 0x0A00, 0x0A7F, Name::Gurmukhi },	// Gurmukhi
		{ 0xFF00, 0xFFEF, Name::HalfwidthandFullwidthForms },	// Halfwidth and Fullwidth Forms
		{ 0x3130, 0x318F, Name::HangulCompatibilityJamo },	// Hangul Compatibility Jamo
		{ 0x1100, 0x11FF, Name::HangulJamo },	// Hangul Jamo
		{ 0xA960, 0xA97F, Name::HangulJamoExtendedA },	// Hangul Jamo Extended-A
		{ 0xD7B0, 0xD7FF, Name::HangulJamoExtendedB },	// Hangul Jamo Extended-B
		{ 0xAC00, 0xD7AF, Name::HangulSyllables },	// Hangul Syllables
		{ 0x10D00, 0x10D3F, Name::HanifiRohingya },	// Hanifi Rohingya
		{ 0x1720, 0x173F, Name::Hanunoo },	// Hanunoo
		{ 0x108E0, 0x108FF, Name::Hatran },	// Hatran
		{ 0x0590, 0x05FF, Name::Hebrew },	// Hebrew
		{ 0xDB80, 0xDBFF, Name::HighPrivateUseSurrogates },	// High Private Use Surrogates
		{ 0xD800, 0xDB7F, Name::HighSurrogates },	// High Surrogates
		{ 0x3040, 0x309F, Name::Hiragana },	// Hiragana
		{ 0x0250, 0x02AF, Name::IPAExtensions },	// IPA Extensions
		{ 0x2FF0, 0x2FFF, Name::IdeographicDescriptionCharacters },	// Ideographic Description Characters
		{ 0x16FE0, 0x16FFF, Name::IdeographicSymbolsandPunctuation },	// Ideographic Symbols and Punctuation
		{ 0x10840, 0x1085F, Name::ImperialAramaic },	// Imperial Aramaic
		{ 0x1EC70, 0x1ECBF, Name::IndicSiyaqNumbers },	// Indic Siyaq Numbers
		{ 0x10B60, 0x10B7F, Name::InscriptionalPahlavi },	// Inscriptional Pahlavi
		{ 0x10B40, 0x10B5F, Name::InscriptionalParthian },	// Inscriptional Parthian
		{ 0xA980, 0xA9DF, Name::Javanese },	// Javanese
		{ 0x11080, 0x110CF, Name::Kaithi },	// Kaithi
		{ 0x1B100, 0x1B12F, Name::KanaExtendedA },	// Kana Extended-A
		{ 0x1B000, 0x1B0FF, Name::KanaSupplement },	// Kana Supplement
		{ 0x3190, 0x319F, Name::Kanbun },	// Kanbun
		{ 0x2F00, 0x2FDF, Name::KangxiRadicals },	// Kangxi Radicals
		{ 0x0C80, 0x0CFF, Name::Kannada },	// Kannada
		{ 0x30A0, 0x30FF, Name::Katakana },	// Katakana
		{ 0x31F0, 0x31FF, Name::KatakanaPhoneticExtensions },	// Katakana Phonetic Extensions
		{ 0xA900, 0xA92F, Name::KayahLi },	// Kayah Li
		{ 0x10A00, 0x10A5F, Name::Kharoshthi },	// Kharoshthi
		{ 0x1780, 0x17FF, Name::Khmer },	// Khmer
		{ 0x19E0, 0x19FF, Name::KhmerSymbols },	// Khmer Symbols
		{ 0x11200, 0x1124F, Name::Khojki },	// Khojki
		{ 0x112B0, 0x112FF, Name::Khudawadi },	// Khudawadi
		{ 0x0E80, 0x0EFF, Name::Lao },	// Lao
		{ 0x0080, 0x00FF, Name::Latin1Supplement },	// Latin-1 Supplement
		{ 0x0100, 0x017F, Name::LatinExtendedA },	// Latin Extended-A
		{ 0x1E00, 0x1EFF, Name::LatinExtendedAdditional },	// Latin Extended Additional
		{ 0x0180, 0x024F, Name::LatinExtendedB },	// Latin Extended-B
		{ 0x2C60, 0x2C7F, Name::LatinExtendedC },	// Latin Extended-C
		{ 0xA720, 0xA7FF, Name::LatinExtendedD },	// Latin Extended-D
		{ 0xAB30, 0xAB6F, Name::LatinExtendedE },	// Latin Extended-E
		{ 0x1C00, 0x1C4F, Name::Lepcha },	// Lepcha
		{ 0x2100, 0x214F, Name::LetterlikeSymbols },	// Letterlike Symbols
		{ 0x1900, 0x194F, Name::Limbu },	// Limbu
		{ 0x10600, 0x1077F, Name::LinearA },	// Linear A
		{ 0x10080, 0x100FF, Name::LinearBIdeograms },	// Linear B Ideograms
		{ 0x10000, 0x1007F, Name::LinearBSyllabary },	// Linear B Syllabary
		{ 0xA4D0, 0xA4FF, Name::Lisu },	// Lisu
		{ 0xDC00, 0xDFFF, Name::LowSurrogates },	// Low Surrogates
		{ 0x10280, 0x1029F, Name::Lycian },	// Lycian
		{ 0x10920, 0x1093F, Name::Lydian },	// Lydian
		{ 0x11150, 0x1117F, Name::Mahajani },	// Mahajani
		{ 0x1F000, 0x1F02F, Name::MahjongTiles },	// Mahjong Tiles
		{ 0x11EE0, 0x11EFF, Name::Makasar },	// Makasar
		{ 0x0D00, 0x0D7F, Name::Malayalam },	// Malayalam
		{ 0x0840, 0x085F, Name::Mandaic },	// Mandaic
		{ 0x10AC0, 0x10AFF, Name::Manichaean },	// Manichaean
		{ 0x11C70, 0x11CBF, Name::Marchen },	// Marchen
		{ 0x11D00, 0x11D5F, Name::MasaramGondi },	// Masaram Gondi
		{ 0x1D400, 0x1D7FF, Name::MathematicalAlphanumericSymbols },	// Mathematical Alphanumeric Symbols
		{ 0x2200, 0x22FF, Name::MathematicalOperators },	// Mathematical Operators
		{ 0x1D2E0, 0x1D2FF, Name::MayanNumerals },	// Mayan Numerals
		{ 0x16E40, 0x16E9F, Name::Medefaidrin },	// Medefaidrin
		{ 0xABC0, 0xABFF, Name::MeeteiMayek },	// Meetei Mayek
		{ 0xAAE0, 0xAAFF, Name::MeeteiMayekExtensions },	// Meetei Mayek Extensions
		{ 0x1E800, 0x1E8DF, Name::MendeKikakui },	// Mende Kikakui
		{ 0x109A0, 0x109FF, Name::MeroiticCursive },	// Meroitic Cursive
		{ 0x10980, 0x1099F, Name::MeroiticHieroglyphs },	// Meroitic Hieroglyphs
		{ 0x16F00, 0x16F9F, Name::Miao },	// Miao
		{ 0x27C0, 0x27EF, Name::MiscellaneousMathematicalSymbolsA },	// Miscellaneous Mathematical Symbols-A
		{ 0x2980, 0x29FF, Name::MiscellaneousMathematicalSymbolsB },	// Miscellaneous Mathematical Symbols-B
		{ 0x2600, 0x26FF, Name::MiscellaneousSymbols },	// Miscellaneous Symbols
		{ 0x2B00, 0x2BFF, Name::MiscellaneousSymbolsandArrows },	// Miscellaneous Symbols and Arrows
		{ 0x1F300, 0x1F5FF, Name::MiscellaneousSymbolsandPictographs },	// Miscellaneous Symbols and Pictographs
		{ 0x2300, 0x23FF, Name::MiscellaneousTechnical },	// Miscellaneous Technical
		{ 0x11600, 0x1165F, Name::Modi },	// Modi
		{ 0xA700, 0xA71F, Name::ModifierToneLetters },	// Modifier Tone Letters
		{ 0x1800, 0x18AF, Name::Mongolian },	// Mongolian
		{ 0x11660, 0x1167F, Name::MongolianSupplement },	// Mongolian Supplement
		{ 0x16A40, 0x16A6F, Name::Mro },	// Mro
		{ 0x11280, 0x112AF, Name::Multani },	// Multani
		{ 0x1D100, 0x1D1FF, Name::MusicalSymbols },	// Musical Symbols
		{ 0x1000, 0x109F, Name::Myanmar },	// Myanmar
		{ 0xAA60, 0xAA7F, Name::MyanmarExtendedA },	// Myanmar Extended-A
		{ 0xA9E0, 0xA9FF, Name::MyanmarExtendedB },	// Myanmar Extended-B
		{ 0x07C0, 0x07FF, Name::NKo },	// NKo
		{ 0x10880, 0x108AF, Name::Nabataean },	// Nabataean
		{ 0x119A0, 0x119FF, Name::Nandinagari },	// Nandinagari
		{ 0x1980, 0x19DF, Name::NewTaiLue },	// New Tai Lue
		{ 0x11400, 0x1147F, Name::Newa },	// Newa
		{ 0x2150, 0x218F, Name::NumberForms },	// Number Forms
		{ 0x1B170, 0x1B2FF, Name::Nushu },	// Nushu
		{ 0x1E100, 0x1E14F, Name::NyiakengPuachueHmong },	// Nyiakeng Puachue Hmong
		{ 0x1680, 0x169F, Name::Ogham },	// Ogham
		{ 0x1C50, 0x1C7F, Name::OlChiki },	// Ol Chiki
		{ 0x10C80, 0x10CFF, Name::OldHungarian },	// Old Hungarian
		{ 0x10300, 0x1032F, Name::OldItalic },	// Old Italic
		{ 0x10A80, 0x10A9F, Name::OldNorthArabian },	// Old North Arabian
		{ 0x10350, 0x1037F, Name::OldPermic },	// Old Permic
		{ 0x103A0, 0x103DF, Name::OldPersian },	// Old Persian
		{ 0x10F00, 0x10F2F, Name::OldSogdian },	// Old Sogdian
		{ 0x10A60, 0x10A7F, Name::OldSouthArabian },	// Old South Arabian
		{ 0x10C00, 0x10C4F, Name::OldTurkic },	// Old Turkic
		{ 0x2440, 0x245F, Name::OpticalCharacterRecognition },	// Optical Character Recognition
		{ 0x0B00, 0x0B7F, Name::Oriya },	// Oriya
		{ 0x1F650, 0x1F67F, Name::OrnamentalDingbats },	// Ornamental Dingbats
		{ 0x104B0, 0x104FF, Name::Osage },	// Osage
		{ 0x10480, 0x104AF, Name::Osmanya },	// Osmanya
		{ 0x1ED00, 0x1ED4F, Name::OttomanSiyaqNumbers },	// Ottoman Siyaq Numbers
		{ 0x16B00, 0x16B8F, Name::PahawhHmong },	// Pahawh Hmong
		{ 0x10860, 0x1087F, Name::Palmyrene },	// Palmyrene
		{ 0x11AC0, 0x11AFF, Name::PauCinHau },	// Pau Cin Hau
		{ 0xA840, 0xA87F, Name::Phagspa },	// Phags-pa
		{ 0x101D0, 0x101FF, Name::PhaistosDisc },	// Phaistos Disc
		{ 0x10900, 0x1091F, Name::Phoenician },	// Phoenician
		{ 0x1D00, 0x1D7F, Name::PhoneticExtensions },	// Phonetic Extensions
		{ 0x1D80, 0x1DBF, Name::PhoneticExtensionsSupplement },	// Phonetic Extensions Supplement
		{ 0x1F0A0, 0x1F0FF, Name::PlayingCards },	// Playing Cards
		{ 0xE000, 0xF8FF, Name::PrivateUseArea },	// Private Use Area
		{ 0x10B80, 0x10BAF, Name::PsalterPahlavi },	// Psalter Pahlavi
		{ 0xA930, 0xA95F, Name::Rejang },	// Rejang
		{ 0x10E60, 0x10E7F, Name::RumiNumeralSymbols },	// Rumi Numeral Symbols
		{ 0x16A0, 0x16FF, Name::Runic },	// Runic
		{ 0x0800, 0x083F, Name::Samaritan },	// Samaritan
		{ 0xA880, 0xA8DF, Name::Saurashtra },	// Saurashtra
		{ 0x11180, 0x111DF, Name::Sharada },	// Sharada
		{ 0x10450, 0x1047F, Name::Shavian },	// Shavian
		{ 0x1BCA0, 0x1BCAF, Name::ShorthandFormatControls },	// Shorthand Format Controls
		{ 0x11580, 0x115FF, Name::Siddham },	// Siddham
		{ 0x0D80, 0x0DFF, Name::Sinhala },	// Sinhala
		{ 0x111E0, 0x111FF, Name::SinhalaArchaicNumbers },	// Sinhala Archaic Numbers
		{ 0xFE50, 0xFE6F, Name::SmallFormVariants },	// Small Form Variants
		{ 0x1B130, 0x1B16F, Name::SmallKanaExtension },	// Small Kana Extension
		{ 0x10F30, 0x10F6F, Name::Sogdian },	// Sogdian
		{ 0x110D0, 0x110FF, Name::SoraSompeng },	// Sora Sompeng
		{ 0x11A50, 0x11AAF, Name::Soyombo },	// Soyombo
		{ 0x02B0, 0x02FF, Name::SpacingModifierLetters },	// Spacing Modifier Letters
		{ 0xFFF0, 0xFFFF, Name::Specials },	// Specials
		{ 0x1B80, 0x1BBF, Name::Sundanese },	// Sundanese
		{ 0x1CC0, 0x1CCF, Name::SundaneseSupplement },	// Sundanese Supplement
		{ 0x2070, 0x209F, Name::SuperscriptsandSubscripts },	// Superscripts and Subscripts
		{ 0x27F0, 0x27FF, Name::SupplementalArrowsA },	// Supplemental Arrows-A
		{ 0x2900, 0x297F, Name::SupplementalArrowsB },	// Supplemental Arrows-B
		{ 0x1F800, 0x1F8FF, Name::SupplementalArrowsC },	// Supplemental Arrows-C
		{ 0x2A00, 0x2AFF, Name::SupplementalMathematicalOperators },	// Supplemental Mathematical Operators
		{ 0x2E00, 0x2E7F, Name::SupplementalPunctuation },	// Supplemental Punctuation
		{ 0x1F900, 0x1F9FF, Name::SupplementalSymbolsandPictographs },	// Supplemental Symbols and Pictographs
		{ 0xF0000, 0xFFFFF, Name::SupplementaryPrivateUseAreaA },	// Supplementary Private Use Area-A
		{ 0x100000, 0x10FFFF, Name::SupplementaryPrivateUseAreaB },	// Supplementary Private Use Area-B
		{ 0x1D800, 0x1DAAF, Name::SuttonSignWriting },	// Sutton SignWriting
		{ 0xA800, 0xA82F, Name::SylotiNagri },	// Syloti Nagri
		{ 0x1FA70, 0x1FAFF, Name::SymbolsandPictographsExtendedA },	// Symbols and Pictographs Extended-A
		{ 0x0700, 0x074F, Name::Syriac },	// Syriac
		{ 0x0860, 0x086F, Name::SyriacSupplement },	// Syriac Supplement
		{ 0x1700, 0x171F, Name::Tagalog },	// Tagalog
		{ 0x1760, 0x177F, Name::Tagbanwa },	// Tagbanwa
		{ 0xE0000, 0xE007F, Name::Tags },	// Tags
		{ 0x1950, 0x197F, Name::TaiLe },	// Tai Le
		{ 0x1A20, 0x1AAF, Name::TaiTham },	// Tai Tham
		{ 0xAA80, 0xAADF, Name::TaiViet },	// Tai Viet
		{ 0x1D300, 0x1D35F, Name::TaiXuanJingSymbols },	// Tai Xuan Jing Symbols
		{ 0x11680, 0x116CF, Name::Takri },	// Takri
		{ 0x0B80, 0x0BFF, Name::Tamil },	// Tamil
		{ 0x11FC0, 0x11FFF, Name::TamilSupplement },	// Tamil Supplement
		{ 0x17000, 0x187FF, Name::Tangut },	// Tangut
		{ 0x18800, 0x18AFF, Name::TangutComponents },	// Tangut Components
		{ 0x0C00, 0x0C7F, Name::Telugu },	// Telugu
		{ 0x0780, 0x07BF, Name::Thaana },	// Thaana
		{ 0x0E00, 0x0E7F, Name::Thai },	// Thai
		{ 0x0F00, 0x0FFF, Name::Tibetan },	// Tibetan
		{ 0x2D30, 0x2D7F, Name::Tifinagh },	// Tifinagh
		{ 0x11480, 0x114DF, Name::Tirhuta },	// Tirhuta
		{ 0x1F680, 0x1F6FF, Name::TransportandMapSymbols },	// Transport and Map Symbols
		{ 0x10380, 0x1039F, Name::Ugaritic },	// Ugaritic
		{ 0x1400, 0x167F, Name::UnifiedCanadianAboriginalSyllabics },	// Unified Canadian Aboriginal Syllabics
		{ 0x18B0, 0x18FF, Name::UnifiedCanadianAboriginalSyllabicsExtended },	// Unified Canadian Aboriginal Syllabics Extended
		{ 0xA500, 0xA63F, Name::Vai },	// Vai
		{ 0xFE00, 0xFE0F, Name::VariationSelectors },	// Variation Selectors
		{ 0xE0100, 0xE01EF, Name::VariationSelectorsSupplement },	// Variation Selectors Supplement
		{ 0x1CD0, 0x1CFF, Name::VedicExtensions },	// Vedic Extensions
		{ 0xFE10, 0xFE1F, Name::VerticalForms },	// Vertical Forms
		{ 0x1E2C0, 0x1E2FF, Name::Wancho },	// Wancho
		{ 0x118A0, 0x118FF, Name::WarangCiti },	// Warang Citi
		{ 0xA490, 0xA4CF, Name::YiRadicals },	// Yi Radicals
		{ 0xA000, 0xA48F, Name::YiSyllables },	// Yi Syllables
		{ 0x4DC0, 0x4DFF, Name::YijingHexagramSymbols },	// Yijing Hexagram Symbols
		{ 0x11A00, 0x11A4F, Name::ZanabazarSquare },	// Zanabazar Square
	});


	// Fetch the codepoint range for the specified block name.
	constexpr static Entry GetBlock(Name name)
	{
		const auto it = std::lower_bound(BlockRanges.begin(), BlockRanges.end(), name,
								   [](const Entry& e, Name n) constexpr { return e.name < n; });
		if (it != BlockRanges.end() && it->name == name)
		{
			return *it;
		}

		return {};
	}

	// Check if a codepoint is within the block for 'name'.
	export template<Name name>
	constexpr bool IsInBlock(uint32_t codePoint)
	{
		constexpr auto block = GetBlock(name);
		return codePoint >= block.start && codePoint <= block.end;
	}

	static_assert(GetBlock(Name::Adlam).start == 0x1E900);
	static_assert(GetBlock(Name::AegeanNumbers).end   == 0x1013F);
};
