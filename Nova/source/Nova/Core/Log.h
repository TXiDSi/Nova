#pragma once
#include "Nova/Core/Base.h"
#include "spdlog/spdlog.h"
namespace Nova
{
	class NOVA_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger> GetCoreLogger();
		static std::shared_ptr<spdlog::logger> GetClientLogger();
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

#define NOVA_CORE_TRACE(...)	Nova::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NOVA_CORE_INFO(...)		Nova::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NOVA_CORE_WARN(...)		Nova::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NOVA_CORE_ERROR(...)	Nova::Log::GetCoreLogger()->error(__VA_ARGS__)

#define NOVA_TRACE(...)			Nova::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NOVA_INFO(...)			Nova::Log::GetClientLogger()->info(__VA_ARGS__)
#define NOVA_WARN(...)			Nova::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NOVA_ERROR(...)			Nova::Log::GetClientLogger()->error(__VA_ARGS__)
}


