#pragma once

#include <memory>
#include <string>

#ifdef IS_NOVA_BUILD
	#define NOVA_API 
#else
	#define NOVA_API 
#endif  

#define BIT(x) (1<<x)
#define BIND_EVENT_FUNC(func) [this](auto&& ...args)->decltype(auto) {  return this->func( std::forward<decltype(args)>(args)... );  }


namespace Nova {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}
