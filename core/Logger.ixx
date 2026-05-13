// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <chrono>

export module core.logger;

import std;

namespace core::logger
{
	export enum struct Level : uint8_t
	{
		Debug = 0, Info, Warning, Error
	};


	export class LoggerImpl
	{
	public:
		virtual void Write(std::string_view sv) = 0;
	};


	class NullLogger : public LoggerImpl
	{
	public:
		virtual void Write(std::string_view sv) override {}

	};


	export class Logger
	{
		std::unique_ptr<LoggerImpl> mImpl;

		Level mLevel { Level::Debug };

		Logger() { mImpl = std::make_unique<NullLogger>(); }

	public:
		static Logger& Get(void)
		{
			static Logger logger;
			return logger;
		}

		void SetImpl(LoggerImpl* impl)
		{
			mImpl = std::unique_ptr<LoggerImpl>(impl);
		}

		void SetLevel(Level level)
		{
			mLevel = level;
		}

		Level GetLevel(void) const { return mLevel; }

		void Write(std::string_view sv)
		{
			if (mImpl)
			{
				using namespace std::chrono;

				const auto now = system_clock::now();
				auto local = zoned_time{ current_zone(), now };

				std::string timeStamp = std::format("{0:%Y-%m-%d %H:%M:%S}", local);

				std::string log = std::format("{} : {}", timeStamp, sv);
				mImpl->Write(log);
			}
		}

	};


	export void Write(std::string_view sv)
	{
		Logger::Get().Write(sv);
	}


	template<typename... Args>
	void _Write(Level level, std::string_view format, Args&&... args)
	{
		if (level >= Logger::Get().GetLevel())
		{
			std::string s = std::vformat(format, std::make_format_args(std::forward<Args>(args)...));

			switch (level)
			{
				case Level::Debug:		s = "DEBUG: " + s;	 break;
				case Level::Info:		s = "INFO: " + s;	 break;
				case Level::Warning:	s = "WARNING: " + s; break;
				case Level::Error:		s = "ERROR: " + s;	 break;
			}

			Logger::Get().Write(s);
		}
	}

	export template<typename... Args>
	void Debug(const std::string_view format, Args&&... args)
	{
		_Write(Level::Debug, format, std::forward<Args>(args)...);
	}

	export template<typename... Args>
	void Info(const std::string_view format, Args&&... args)
	{
		_Write(Level::Info, format, std::forward<Args>(args)...);
	}

	export template<typename... Args>
	void Warning(const std::string_view format, Args&&... args)
	{
		_Write(Level::Warning, format, std::forward<Args>(args)...);
	}

	export template<typename... Args>
	void Error(const std::string_view format, Args&&... args)
	{
		_Write(Level::Error, format, std::forward<Args>(args)...);
	}



}
