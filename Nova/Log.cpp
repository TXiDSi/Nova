#include "NovaPch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Nova
{
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
		s_CoreLogger   = spdlog::stdout_color_mt("NOVA");
		s_CoreLogger->set_level(spdlog::level::trace);
	}
	std::shared_ptr<spdlog::logger> Log::GetClientLogger()
	{
		return s_ClientLogger;
	}
	std::shared_ptr<spdlog::logger> Log::GetCoreLogger()
	{
		return s_CoreLogger;
	}
}

