// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cstdint>

export module unicode.shaping;

import std;

import unicode.bidiclass;


namespace unicode::shaping
{
	// https://www.unicode.org/Public/UCD/latest/ucd/extracted/DerivedJoiningType.txt

	using Utf32Text = std::vector<uint32_t>;

	export enum struct JoinForm
	{
		Final,
		Initial,
		Isolated,
		Medial,
	};

	export enum struct JoiningType
	{
		JoinCausing,	// C U+0640 ARABIC TATWEEL. These characters are distinguished from the dual-joining characters in that they do not change shape themselves.
		DualJoining,	// D BEH, TEH, THEH, JEEM... (Xm)
		LeftJoining,	// L Xl
		RightJoining,	// R LEF, DAL, THAL, REH, ZAIN... (Xr)
		Transparent,	// T All nonspacing marks (General Category Mn or Me) and most format control characters (General Category Cf) are transparent to cursive joining.
		NonJoining,		// U All spacing characters, except those explicitly mentioned as being one of the other joining types, are non-joining. (Xn)
	};

	struct Form
	{
		uint32_t codePoint{};
		JoinForm joinForm{};
		uint32_t presentationForm{};
	};

	static constexpr auto PresentationForms = std::to_array<Form>(
	{
		{ 0x0621, JoinForm::Isolated, 0xFE80 },
		{ 0x0622, JoinForm::Final, 0xFE82 },
		{ 0x0622, JoinForm::Isolated, 0xFE81 },
		{ 0x0623, JoinForm::Final, 0xFE84 },
		{ 0x0623, JoinForm::Isolated, 0xFE83 },
		{ 0x0624, JoinForm::Final, 0xFE86 },
		{ 0x0624, JoinForm::Isolated, 0xFE85 },
		{ 0x0625, JoinForm::Final, 0xFE88 },
		{ 0x0625, JoinForm::Isolated, 0xFE87 },
		{ 0x0626, JoinForm::Final, 0xFE8A },
		{ 0x0626, JoinForm::Initial, 0xFE8B },
		{ 0x0626, JoinForm::Isolated, 0xFE89 },
		{ 0x0626, JoinForm::Medial, 0xFE8C },
		{ 0x0627, JoinForm::Final, 0xFE8E },
		{ 0x0627, JoinForm::Isolated, 0xFE8D },
		{ 0x0628, JoinForm::Final, 0xFE90 },
		{ 0x0628, JoinForm::Initial, 0xFE91 },
		{ 0x0628, JoinForm::Isolated, 0xFE8F },
		{ 0x0628, JoinForm::Medial, 0xFE92 },
		{ 0x0629, JoinForm::Final, 0xFE94 },
		{ 0x0629, JoinForm::Isolated, 0xFE93 },
		{ 0x062A, JoinForm::Final, 0xFE96 },
		{ 0x062A, JoinForm::Initial, 0xFE97 },
		{ 0x062A, JoinForm::Isolated, 0xFE95 },
		{ 0x062A, JoinForm::Medial, 0xFE98 },
		{ 0x062B, JoinForm::Final, 0xFE9A },
		{ 0x062B, JoinForm::Initial, 0xFE9B },
		{ 0x062B, JoinForm::Isolated, 0xFE99 },
		{ 0x062B, JoinForm::Medial, 0xFE9C },
		{ 0x062C, JoinForm::Final, 0xFE9E },
		{ 0x062C, JoinForm::Initial, 0xFE9F },
		{ 0x062C, JoinForm::Isolated, 0xFE9D },
		{ 0x062C, JoinForm::Medial, 0xFEA0 },
		{ 0x062D, JoinForm::Final, 0xFEA2 },
		{ 0x062D, JoinForm::Initial, 0xFEA3 },
		{ 0x062D, JoinForm::Isolated, 0xFEA1 },
		{ 0x062D, JoinForm::Medial, 0xFEA4 },
		{ 0x062E, JoinForm::Final, 0xFEA6 },
		{ 0x062E, JoinForm::Initial, 0xFEA7 },
		{ 0x062E, JoinForm::Isolated, 0xFEA5 },
		{ 0x062E, JoinForm::Medial, 0xFEA8 },
		{ 0x062F, JoinForm::Final, 0xFEAA },
		{ 0x062F, JoinForm::Isolated, 0xFEA9 },
		{ 0x0630, JoinForm::Final, 0xFEAC },
		{ 0x0630, JoinForm::Isolated, 0xFEAB },
		{ 0x0631, JoinForm::Final, 0xFEAE },
		{ 0x0631, JoinForm::Isolated, 0xFEAD },
		{ 0x0632, JoinForm::Final, 0xFEB0 },
		{ 0x0632, JoinForm::Isolated, 0xFEAF },
		{ 0x0633, JoinForm::Final, 0xFEB2 },
		{ 0x0633, JoinForm::Initial, 0xFEB3 },
		{ 0x0633, JoinForm::Isolated, 0xFEB1 },
		{ 0x0633, JoinForm::Medial, 0xFEB4 },
		{ 0x0634, JoinForm::Final, 0xFEB6 },
		{ 0x0634, JoinForm::Initial, 0xFEB7 },
		{ 0x0634, JoinForm::Isolated, 0xFEB5 },
		{ 0x0634, JoinForm::Medial, 0xFEB8 },
		{ 0x0635, JoinForm::Final, 0xFEBA },
		{ 0x0635, JoinForm::Initial, 0xFEBB },
		{ 0x0635, JoinForm::Isolated, 0xFEB9 },
		{ 0x0635, JoinForm::Medial, 0xFEBC },
		{ 0x0636, JoinForm::Final, 0xFEBE },
		{ 0x0636, JoinForm::Initial, 0xFEBF },
		{ 0x0636, JoinForm::Isolated, 0xFEBD },
		{ 0x0636, JoinForm::Medial, 0xFEC0 },
		{ 0x0637, JoinForm::Final, 0xFEC2 },
		{ 0x0637, JoinForm::Initial, 0xFEC3 },
		{ 0x0637, JoinForm::Isolated, 0xFEC1 },
		{ 0x0637, JoinForm::Medial, 0xFEC4 },
		{ 0x0638, JoinForm::Final, 0xFEC6 },
		{ 0x0638, JoinForm::Initial, 0xFEC7 },
		{ 0x0638, JoinForm::Isolated, 0xFEC5 },
		{ 0x0638, JoinForm::Medial, 0xFEC8 },
		{ 0x0639, JoinForm::Final, 0xFECA },
		{ 0x0639, JoinForm::Initial, 0xFECB },
		{ 0x0639, JoinForm::Isolated, 0xFEC9 },
		{ 0x0639, JoinForm::Medial, 0xFECC },
		{ 0x063A, JoinForm::Final, 0xFECE },
		{ 0x063A, JoinForm::Initial, 0xFECF },
		{ 0x063A, JoinForm::Isolated, 0xFECD },
		{ 0x063A, JoinForm::Medial, 0xFED0 },
		{ 0x0641, JoinForm::Final, 0xFED2 },
		{ 0x0641, JoinForm::Initial, 0xFED3 },
		{ 0x0641, JoinForm::Isolated, 0xFED1 },
		{ 0x0641, JoinForm::Medial, 0xFED4 },
		{ 0x0642, JoinForm::Final, 0xFED6 },
		{ 0x0642, JoinForm::Initial, 0xFED7 },
		{ 0x0642, JoinForm::Isolated, 0xFED5 },
		{ 0x0642, JoinForm::Medial, 0xFED8 },
		{ 0x0643, JoinForm::Final, 0xFEDA },
		{ 0x0643, JoinForm::Initial, 0xFEDB },
		{ 0x0643, JoinForm::Isolated, 0xFED9 },
		{ 0x0643, JoinForm::Medial, 0xFEDC },
		{ 0x0644, JoinForm::Final, 0xFEDE },
		{ 0x0644, JoinForm::Initial, 0xFEDF },
		{ 0x0644, JoinForm::Isolated, 0xFEDD },
		{ 0x0644, JoinForm::Medial, 0xFEE0 },
		{ 0x0645, JoinForm::Final, 0xFEE2 },
		{ 0x0645, JoinForm::Initial, 0xFEE3 },
		{ 0x0645, JoinForm::Isolated, 0xFEE1 },
		{ 0x0645, JoinForm::Medial, 0xFEE4 },
		{ 0x0646, JoinForm::Final, 0xFEE6 },
		{ 0x0646, JoinForm::Initial, 0xFEE7 },
		{ 0x0646, JoinForm::Isolated, 0xFEE5 },
		{ 0x0646, JoinForm::Medial, 0xFEE8 },
		{ 0x0647, JoinForm::Final, 0xFEEA },
		{ 0x0647, JoinForm::Initial, 0xFEEB },
		{ 0x0647, JoinForm::Isolated, 0xFEE9 },
		{ 0x0647, JoinForm::Medial, 0xFEEC },
		{ 0x0648, JoinForm::Final, 0xFEEE },
		{ 0x0648, JoinForm::Isolated, 0xFEED },
		{ 0x0649, JoinForm::Final, 0xFEF0 },
		{ 0x0649, JoinForm::Initial, 0xFBE8 },
		{ 0x0649, JoinForm::Isolated, 0xFEEF },
		{ 0x0649, JoinForm::Medial, 0xFBE9 },
		{ 0x064A, JoinForm::Final, 0xFEF2 },
		{ 0x064A, JoinForm::Initial, 0xFEF3 },
		{ 0x064A, JoinForm::Isolated, 0xFEF1 },
		{ 0x064A, JoinForm::Medial, 0xFEF4 },
		{ 0x0671, JoinForm::Final, 0xFB51 },
		{ 0x0671, JoinForm::Isolated, 0xFB50 },
		{ 0x0677, JoinForm::Isolated, 0xFBDD },
		{ 0x0679, JoinForm::Final, 0xFB67 },
		{ 0x0679, JoinForm::Initial, 0xFB68 },
		{ 0x0679, JoinForm::Isolated, 0xFB66 },
		{ 0x0679, JoinForm::Medial, 0xFB69 },
		{ 0x067A, JoinForm::Final, 0xFB5F },
		{ 0x067A, JoinForm::Initial, 0xFB60 },
		{ 0x067A, JoinForm::Isolated, 0xFB5E },
		{ 0x067A, JoinForm::Medial, 0xFB61 },
		{ 0x067B, JoinForm::Final, 0xFB53 },
		{ 0x067B, JoinForm::Initial, 0xFB54 },
		{ 0x067B, JoinForm::Isolated, 0xFB52 },
		{ 0x067B, JoinForm::Medial, 0xFB55 },
		{ 0x067E, JoinForm::Final, 0xFB57 },
		{ 0x067E, JoinForm::Initial, 0xFB58 },
		{ 0x067E, JoinForm::Isolated, 0xFB56 },
		{ 0x067E, JoinForm::Medial, 0xFB59 },
		{ 0x067F, JoinForm::Final, 0xFB63 },
		{ 0x067F, JoinForm::Initial, 0xFB64 },
		{ 0x067F, JoinForm::Isolated, 0xFB62 },
		{ 0x067F, JoinForm::Medial, 0xFB65 },
		{ 0x0680, JoinForm::Final, 0xFB5B },
		{ 0x0680, JoinForm::Initial, 0xFB5C },
		{ 0x0680, JoinForm::Isolated, 0xFB5A },
		{ 0x0680, JoinForm::Medial, 0xFB5D },
		{ 0x0683, JoinForm::Final, 0xFB77 },
		{ 0x0683, JoinForm::Initial, 0xFB78 },
		{ 0x0683, JoinForm::Isolated, 0xFB76 },
		{ 0x0683, JoinForm::Medial, 0xFB79 },
		{ 0x0684, JoinForm::Final, 0xFB73 },
		{ 0x0684, JoinForm::Initial, 0xFB74 },
		{ 0x0684, JoinForm::Isolated, 0xFB72 },
		{ 0x0684, JoinForm::Medial, 0xFB75 },
		{ 0x0686, JoinForm::Final, 0xFB7B },
		{ 0x0686, JoinForm::Initial, 0xFB7C },
		{ 0x0686, JoinForm::Isolated, 0xFB7A },
		{ 0x0686, JoinForm::Medial, 0xFB7D },
		{ 0x0687, JoinForm::Final, 0xFB7F },
		{ 0x0687, JoinForm::Initial, 0xFB80 },
		{ 0x0687, JoinForm::Isolated, 0xFB7E },
		{ 0x0687, JoinForm::Medial, 0xFB81 },
		{ 0x0688, JoinForm::Final, 0xFB89 },
		{ 0x0688, JoinForm::Isolated, 0xFB88 },
		{ 0x068C, JoinForm::Final, 0xFB85 },
		{ 0x068C, JoinForm::Isolated, 0xFB84 },
		{ 0x068D, JoinForm::Final, 0xFB83 },
		{ 0x068D, JoinForm::Isolated, 0xFB82 },
		{ 0x068E, JoinForm::Final, 0xFB87 },
		{ 0x068E, JoinForm::Isolated, 0xFB86 },
		{ 0x0691, JoinForm::Final, 0xFB8D },
		{ 0x0691, JoinForm::Isolated, 0xFB8C },
		{ 0x0698, JoinForm::Final, 0xFB8B },
		{ 0x0698, JoinForm::Isolated, 0xFB8A },
		{ 0x06A4, JoinForm::Final, 0xFB6B },
		{ 0x06A4, JoinForm::Initial, 0xFB6C },
		{ 0x06A4, JoinForm::Isolated, 0xFB6A },
		{ 0x06A4, JoinForm::Medial, 0xFB6D },
		{ 0x06A6, JoinForm::Final, 0xFB6F },
		{ 0x06A6, JoinForm::Initial, 0xFB70 },
		{ 0x06A6, JoinForm::Isolated, 0xFB6E },
		{ 0x06A6, JoinForm::Medial, 0xFB71 },
		{ 0x06A9, JoinForm::Final, 0xFB8F },
		{ 0x06A9, JoinForm::Initial, 0xFB90 },
		{ 0x06A9, JoinForm::Isolated, 0xFB8E },
		{ 0x06A9, JoinForm::Medial, 0xFB91 },
		{ 0x06AD, JoinForm::Final, 0xFBD4 },
		{ 0x06AD, JoinForm::Initial, 0xFBD5 },
		{ 0x06AD, JoinForm::Isolated, 0xFBD3 },
		{ 0x06AD, JoinForm::Medial, 0xFBD6 },
		{ 0x06AF, JoinForm::Final, 0xFB93 },
		{ 0x06AF, JoinForm::Initial, 0xFB94 },
		{ 0x06AF, JoinForm::Isolated, 0xFB92 },
		{ 0x06AF, JoinForm::Medial, 0xFB95 },
		{ 0x06B1, JoinForm::Final, 0xFB9B },
		{ 0x06B1, JoinForm::Initial, 0xFB9C },
		{ 0x06B1, JoinForm::Isolated, 0xFB9A },
		{ 0x06B1, JoinForm::Medial, 0xFB9D },
		{ 0x06B3, JoinForm::Final, 0xFB97 },
		{ 0x06B3, JoinForm::Initial, 0xFB98 },
		{ 0x06B3, JoinForm::Isolated, 0xFB96 },
		{ 0x06B3, JoinForm::Medial, 0xFB99 },
		{ 0x06BA, JoinForm::Final, 0xFB9F },
		{ 0x06BA, JoinForm::Isolated, 0xFB9E },
		{ 0x06BB, JoinForm::Final, 0xFBA1 },
		{ 0x06BB, JoinForm::Initial, 0xFBA2 },
		{ 0x06BB, JoinForm::Isolated, 0xFBA0 },
		{ 0x06BB, JoinForm::Medial, 0xFBA3 },
		{ 0x06BE, JoinForm::Final, 0xFBAB },
		{ 0x06BE, JoinForm::Initial, 0xFBAC },
		{ 0x06BE, JoinForm::Isolated, 0xFBAA },
		{ 0x06BE, JoinForm::Medial, 0xFBAD },
		{ 0x06C0, JoinForm::Final, 0xFBA5 },
		{ 0x06C0, JoinForm::Isolated, 0xFBA4 },
		{ 0x06C1, JoinForm::Final, 0xFBA7 },
		{ 0x06C1, JoinForm::Initial, 0xFBA8 },
		{ 0x06C1, JoinForm::Isolated, 0xFBA6 },
		{ 0x06C1, JoinForm::Medial, 0xFBA9 },
		{ 0x06C5, JoinForm::Final, 0xFBE1 },
		{ 0x06C5, JoinForm::Isolated, 0xFBE0 },
		{ 0x06C6, JoinForm::Final, 0xFBDA },
		{ 0x06C6, JoinForm::Isolated, 0xFBD9 },
		{ 0x06C7, JoinForm::Final, 0xFBD8 },
		{ 0x06C7, JoinForm::Isolated, 0xFBD7 },
		{ 0x06C8, JoinForm::Final, 0xFBDC },
		{ 0x06C8, JoinForm::Isolated, 0xFBDB },
		{ 0x06C9, JoinForm::Final, 0xFBE3 },
		{ 0x06C9, JoinForm::Isolated, 0xFBE2 },
		{ 0x06CB, JoinForm::Final, 0xFBDF },
		{ 0x06CB, JoinForm::Isolated, 0xFBDE },
		{ 0x06CC, JoinForm::Final, 0xFBFD },
		{ 0x06CC, JoinForm::Initial, 0xFBFE },
		{ 0x06CC, JoinForm::Isolated, 0xFBFC },
		{ 0x06CC, JoinForm::Medial, 0xFBFF },
		{ 0x06D0, JoinForm::Final, 0xFBE5 },
		{ 0x06D0, JoinForm::Initial, 0xFBE6 },
		{ 0x06D0, JoinForm::Isolated, 0xFBE4 },
		{ 0x06D0, JoinForm::Medial, 0xFBE7 },
		{ 0x06D2, JoinForm::Final, 0xFBAF },
		{ 0x06D2, JoinForm::Isolated, 0xFBAE },
		{ 0x06D3, JoinForm::Final, 0xFBB1 },
		{ 0x06D3, JoinForm::Isolated, 0xFBB0 },
	});

	// Unicode spec 9.2.3.
	static constexpr auto LamAlefLigature = std::to_array<Form>(
	{
		{ 0x0622, JoinForm::Final, 0xFEF6 },
		{ 0x0622, JoinForm::Isolated, 0xFEF5 },
		{ 0x0623, JoinForm::Final, 0xFEF8 },
		{ 0x0623, JoinForm::Isolated, 0xFEF7 },
		{ 0x0625, JoinForm::Final, 0xFEFA },
		{ 0x0625, JoinForm::Isolated, 0xFEF9 },
		{ 0x0627, JoinForm::Final, 0xFEFC },
		{ 0x0627, JoinForm::Isolated, 0xFEFB },
	});

	export struct Entry
	{
		uint32_t start;
		uint32_t end;
		JoiningType joiningType;
	};

	constexpr static auto JoiningTypes = std::to_array<Entry>(
	{
		{ 0x0610, 0x061A, JoiningType::Transparent },
		{ 0x061C, 0x061C, JoiningType::Transparent },
		{ 0x0620, 0x0620, JoiningType::DualJoining },
		{ 0x0622, 0x0625, JoiningType::RightJoining },
		{ 0x0626, 0x0626, JoiningType::DualJoining },
		{ 0x0627, 0x0627, JoiningType::RightJoining },
		{ 0x0628, 0x0628, JoiningType::DualJoining },
		{ 0x0629, 0x0629, JoiningType::RightJoining },
		{ 0x062A, 0x062E, JoiningType::DualJoining },
		{ 0x062F, 0x0632, JoiningType::RightJoining },
		{ 0x0633, 0x063F, JoiningType::DualJoining },
		{ 0x0640, 0x0640, JoiningType::JoinCausing },
		{ 0x0641, 0x0647, JoiningType::DualJoining },
		{ 0x0648, 0x0648, JoiningType::RightJoining },
		{ 0x0649, 0x064A, JoiningType::DualJoining },
		{ 0x064B, 0x065F, JoiningType::Transparent },
		{ 0x066E, 0x066F, JoiningType::DualJoining },
		{ 0x0670, 0x0670, JoiningType::Transparent },
		{ 0x0671, 0x0673, JoiningType::RightJoining },
		{ 0x0675, 0x0677, JoiningType::RightJoining },
		{ 0x0678, 0x0687, JoiningType::DualJoining },
		{ 0x0688, 0x0699, JoiningType::RightJoining },
		{ 0x069A, 0x06BF, JoiningType::DualJoining },
		{ 0x06C0, 0x06C0, JoiningType::RightJoining },
		{ 0x06C1, 0x06C2, JoiningType::DualJoining },
		{ 0x06C3, 0x06CB, JoiningType::RightJoining },
		{ 0x06CC, 0x06CC, JoiningType::DualJoining },
		{ 0x06CD, 0x06CD, JoiningType::RightJoining },
		{ 0x06CE, 0x06CE, JoiningType::DualJoining },
		{ 0x06CF, 0x06CF, JoiningType::RightJoining },
		{ 0x06D0, 0x06D1, JoiningType::DualJoining },
		{ 0x06D2, 0x06D3, JoiningType::RightJoining },
		{ 0x06D5, 0x06D5, JoiningType::RightJoining },
		{ 0x06D6, 0x06DC, JoiningType::Transparent },
		{ 0x06DF, 0x06E4, JoiningType::Transparent },
		{ 0x06E7, 0x06E8, JoiningType::Transparent },
		{ 0x06EA, 0x06ED, JoiningType::Transparent },
		{ 0x06EE, 0x06EF, JoiningType::RightJoining },
		{ 0x06FA, 0x06FC, JoiningType::DualJoining },
		{ 0x06FF, 0x06FF, JoiningType::DualJoining },
		{ 0x070F, 0x070F, JoiningType::Transparent },
		{ 0x0710, 0x0710, JoiningType::RightJoining },
		{ 0x0711, 0x0711, JoiningType::Transparent },
		{ 0x0712, 0x0714, JoiningType::DualJoining },
		{ 0x0715, 0x0719, JoiningType::RightJoining },
		{ 0x071A, 0x071D, JoiningType::DualJoining },
		{ 0x071E, 0x071E, JoiningType::RightJoining },
		{ 0x071F, 0x0727, JoiningType::DualJoining },
		{ 0x0728, 0x0728, JoiningType::RightJoining },
		{ 0x0729, 0x0729, JoiningType::DualJoining },
		{ 0x072A, 0x072A, JoiningType::RightJoining },
		{ 0x072B, 0x072B, JoiningType::DualJoining },
		{ 0x072C, 0x072C, JoiningType::RightJoining },
		{ 0x072D, 0x072E, JoiningType::DualJoining },
		{ 0x072F, 0x072F, JoiningType::RightJoining },
		{ 0x0730, 0x074A, JoiningType::Transparent },
		{ 0x074D, 0x074D, JoiningType::RightJoining },
		{ 0x074E, 0x0758, JoiningType::DualJoining },
		{ 0x0759, 0x075B, JoiningType::RightJoining },
		{ 0x075C, 0x076A, JoiningType::DualJoining },
		{ 0x076B, 0x076C, JoiningType::RightJoining },
		{ 0x076D, 0x0770, JoiningType::DualJoining },
		{ 0x0771, 0x0771, JoiningType::RightJoining },
		{ 0x0772, 0x0772, JoiningType::DualJoining },
		{ 0x0773, 0x0774, JoiningType::RightJoining },
		{ 0x0775, 0x0777, JoiningType::DualJoining },
		{ 0x0778, 0x0779, JoiningType::RightJoining },
		{ 0x077A, 0x077F, JoiningType::DualJoining },
		{ 0x07A6, 0x07B0, JoiningType::Transparent },
	});


	export constexpr JoiningType GetJoiningType(uint32_t codePoint)
	{
		const auto it = std::lower_bound(JoiningTypes.begin(), JoiningTypes.end(), codePoint, [](const Entry& entry, uint32_t cp) {
			return entry.end < cp;
		});

		if (it != JoiningTypes.end() && it->start <= codePoint && codePoint <= it->end)
		{
			return it->joiningType;
		}

		return JoiningType::NonJoining;
	}

	export constexpr std::optional<uint32_t> GetPresentationForm(uint32_t codePoint, JoinForm joinForm)
	{
		const auto it = std::lower_bound(PresentationForms.begin(), PresentationForms.end(), std::make_pair(codePoint, joinForm), [](const Form& form, const auto& key) {
			if (form.codePoint != key.first)
				return form.codePoint < key.first;
			return form.joinForm < key.second;
		});

		if (it != PresentationForms.end() && it->codePoint == codePoint && it->joinForm == joinForm)
		{
			return it->presentationForm;
		}

		return std::nullopt;
	}

	export constexpr std::optional<uint32_t> GetLamAlefLigature(uint32_t codePoint, JoinForm joinForm)
	{
		const auto it = std::lower_bound(LamAlefLigature.begin(), LamAlefLigature.end(), std::make_pair(codePoint, joinForm), [](const Form& form, const auto& key) {
			if (form.codePoint != key.first)
				return form.codePoint < key.first;
			return form.joinForm < key.second;
		 });

		if (it != LamAlefLigature.end() && it->codePoint == codePoint && it->joinForm == joinForm)
		{
			return it->presentationForm;
		}

		return std::nullopt;
	}

	// Return true if the given code point is an Alef variant that can be combined with Lam to form a ligature.
	static bool IsAlefVariant(uint32_t codePoint)
	{
		for (auto alef : LamAlefLigature)
		{
			if (alef.codePoint == codePoint) return true;
		}
		
		return false;
	}

	// Asummes logical order, i.e. left-to-right. Output will require reversing for right-to-left display.
	export Utf32Text ShapeArabicText(const std::span<const uint32_t> codePoints)
	{
		Utf32Text shapedText;
		shapedText.reserve(codePoints.size());

		constexpr auto isPrevJoining = [](JoiningType jt) {
			return jt == JoiningType::RightJoining || jt == JoiningType::DualJoining || jt == JoiningType::JoinCausing;
		};

		constexpr auto isNextJoining = [](JoiningType jt) {
			return jt == JoiningType::LeftJoining || jt == JoiningType::DualJoining || jt == JoiningType::JoinCausing;
		};


		constexpr uint32_t LamCodePoint = 0x0644;	// U'ل'

		JoiningType lastJt{ JoiningType::NonJoining };
		bool havePrev = false;

		for (uint32_t i = 0; i<codePoints.size(); i++)
		{
			uint32_t cp = codePoints[i];

			JoiningType jt = GetJoiningType(cp);

			if (jt == JoiningType::Transparent)
			{
				shapedText.push_back(cp);
				continue;
			}

			// Combine Alef-Lam.
			if (cp == LamCodePoint && i < codePoints.size() - 1 && IsAlefVariant(codePoints[i + 1]))
			{
				bool hasPrevLink = isPrevJoining(jt) && havePrev && isNextJoining(lastJt);

				JoinForm joinForm = hasPrevLink ? JoinForm::Final : JoinForm::Isolated;

				shapedText.push_back(GetLamAlefLigature(codePoints[i + 1], joinForm).value_or(codePoints[i + 1]));

				i++;
				lastJt = JoiningType::RightJoining;
				havePrev = true;
				continue;
			}

			JoiningType nextJt = JoiningType::NonJoining;
			bool haveNext = false;

			// Scan ahead to find the next non-transparent JoiningType
			for (uint32_t j = i + 1; j<codePoints.size(); j++)
			{
				nextJt = GetJoiningType(codePoints[j]);
				if (nextJt != JoiningType::Transparent)
				{
					haveNext = true;
					break;
				}
			}

			bool hasPrevLink = isPrevJoining(jt) && havePrev && isNextJoining(lastJt);
			bool hasNextLink = isNextJoining(jt) && haveNext && isPrevJoining(nextJt);

			JoinForm joinForm = JoinForm::Isolated;	// Default for no links.

			if (!hasPrevLink && hasNextLink) joinForm = JoinForm::Initial;
			else if (hasPrevLink && !hasNextLink) joinForm = JoinForm::Final;
			else if (hasPrevLink && hasNextLink) joinForm = JoinForm::Medial;

			shapedText.push_back(GetPresentationForm(cp, joinForm).value_or(cp));

			lastJt = jt;
			havePrev = true;
		}

		return shapedText;

	}

	// In-place shaping of Arabic script code points in the given span.
	//export bool ShapeArabicScript(std::span<uint32_t> codePoints)
	//{
	//	return false;
	//}

	export struct Segment
	{
		bidiclass::BidiClass bidiClass;
		std::span<uint32_t> codePoints;
	};

	export std::vector<Segment> SplitIntoSegments(std::span<uint32_t> codePoints)
	{
		using namespace unicode;

		std::vector<Segment> segments;

		bidiclass::BidiClass lastBc = bidiclass::BidiClass::Unknown;

		std::span<uint32_t> segment;
		size_t start = 0;

		for (size_t i = 0; i<codePoints.size(); i++)
		{
			bidiclass::BidiClass bc = bidiclass::GetBidiClass(codePoints[i]);
			if (bc != lastBc)
			{
				if (bc == bidiclass::BidiClass::NonspacingMark || bc == bidiclass::BidiClass::WhiteSpace)
				{
					// Inherit the previous bidiclass.
					bc = lastBc;
				}
				else if (i > start)
				{
					segments.push_back({ lastBc, codePoints.subspan(start, i - start) });
					start = i;
				}

			}

			lastBc = bc;
		}

		if (start < codePoints.size())
		{
			segments.push_back({ lastBc, codePoints.subspan(start, codePoints.size() - start) });
		}

		return segments;
	}

	export Utf32Text ShapeScript(std::span<uint32_t> codePoints)
	{
		Utf32Text shapedText;
		shapedText.reserve(codePoints.size());

		auto segments = SplitIntoSegments(codePoints);

		for (auto& segment : segments)
		{
			if (segment.bidiClass == bidiclass::BidiClass::ArabicLetter)
			{
				auto shapedSegment = ShapeArabicText(segment.codePoints);

				auto reversed = std::views::reverse(shapedSegment);

				shapedText.insert(shapedText.end(), reversed.begin(), reversed.end());

				//std::copy(shapedSegment.begin(), shapedSegment.end(), shapedText);


			}
		}

		return shapedText;
	}

};

