module;

#include <cstdint>

export module unicode.convert;

import core.logger;

import std;

namespace unicode::convert
{
	export using Utf32Text = std::vector<uint32_t>;

	constexpr uint32_t TwoByte		= 0b1100'0000;	//0xc0;
	constexpr uint32_t ThreeByte	= 0b1110'0000;	//0xe0;
	constexpr uint32_t FourByte		= 0b1111'0000;	//0xf0;

	constexpr uint32_t TwoByteMask		= 0b1110'0000;	//0xe0;
	constexpr uint32_t ThreeByteMask	= 0b1111'0000;	//0xf0;
	constexpr uint32_t FourByteMask		= 0b1111'1000;	//0xf8;

	constexpr uint32_t Continuation		= 0b1000'0000;	//0x80
	constexpr uint32_t ContinuationMask = 0b0011'1111;	//0x3f

	bool IsOneByte(uint8_t ch)
	{
		return (ch & 0x80) == 0;
	}

	bool IsTwoByte(uint8_t ch)
	{
		return (ch & TwoByteMask) == TwoByte;
	}

	bool IsThreeByte(uint8_t ch)
	{
		return (ch & ThreeByteMask) == ThreeByte;
	}

	bool IsFourByte(uint8_t ch)
	{
		return (ch & FourByteMask) == FourByte;
	}

	// Convert a UTF-8 string into an array of UTF-32 code points.
	export std::vector<uint32_t> Utf8ToUtf32(std::string_view sv)
	{
		std::vector<uint32_t> utf32;

		uint32_t i {};

		bool decodeError { false };

		while (i < sv.size())
		{
			uint8_t ch = sv[i];

			if (IsOneByte(ch))
			{
				utf32.emplace_back(static_cast<uint32_t>(ch));
				i += 1;
			}
			else if (IsTwoByte(ch))
			{
				// Two byte sequence.
				if (i + 1 < sv.size())
				{
					uint8_t byte1 = ch&~TwoByteMask;
					uint8_t byte2 = sv[i + 1]&ContinuationMask;

					uint32_t codePoint = (byte1 << 6)|(byte2 << 0);

					utf32.emplace_back(codePoint);
				}
				i += 2;
			}
			else if (IsThreeByte(ch))
			{
				// Three byte sequence.
				if (i + 2 < sv.size())
				{
					uint8_t byte1 = ch&~ThreeByteMask;
					uint8_t byte2 = sv[i + 1]&ContinuationMask; 
					uint8_t byte3 = sv[i + 2]&ContinuationMask;

					uint32_t codePoint = (byte1 << 12)|(byte2 << 6)|(byte3 << 0);

					utf32.emplace_back(codePoint);
				}
				i += 3;
			}
			else if (IsFourByte(ch))
			{
				// Four byte sequence.
				if (i + 3 < sv.size())
				{
					uint8_t byte1 = ch&~FourByteMask;
					uint8_t byte2 = sv[i + 1]&ContinuationMask; 
					uint8_t byte3 = sv[i + 2]&ContinuationMask;
					uint8_t byte4 = sv[i + 3]&ContinuationMask;

					uint32_t codePoint = (byte1 << 18)|(byte2 << 12)|(byte3 << 6)|byte4;

					utf32.emplace_back(codePoint);
				}
				i += 4;
			}
			else
			{
				utf32.emplace_back(0xfffd);
				i += 1;
				decodeError = true;
			}
		}

		if (decodeError)
		{
			core::logger::Error("UTF-8 decode error in '{}'\n", sv);
		}

		return utf32;
	}

	// Convert an array of UTF-32 code points into a UTF-8 string.
	export std::string Utf32ToUtf8(const Utf32Text& utf32)
	{
		std::string s;

		bool decodeError { false };

		for (uint32_t i=0; i < utf32.size(); i++)
		{
			uint32_t cp = utf32[i];

			if (cp <= 0x7f)
			{
				s += static_cast<char>(cp);
			}
			else if (cp <= 0x7ff)
			{
				s += static_cast<char>(TwoByte|(cp >> 6));
				s += static_cast<char>(Continuation|(cp & ContinuationMask));
			}
			else if (cp <= 0xffff)
			{
				s += static_cast<char>(ThreeByte|(cp >> 12));
				s += static_cast<char>(Continuation|((cp >> 6) & ContinuationMask));
				s += static_cast<char>(Continuation|(cp & ContinuationMask));
			}
			else if (cp <= 0x10ffff)
			{
				s += static_cast<char>(FourByte|(cp >> 18));
				s += static_cast<char>(Continuation|((cp >> 12) & ContinuationMask));
				s += static_cast<char>(Continuation|((cp >> 6) & ContinuationMask));
				s += static_cast<char>(Continuation|(cp & ContinuationMask));
			}
			else
			{
				decodeError = true;
			}
		}

		if (decodeError)
		{
			core::logger::Error("UTF-8 encode error in '{}'\n", s);
		}

		return s;
	}

};
