module;

#include <chrono>

export module core.logger;

import std;

namespace core::logger
{

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

}
