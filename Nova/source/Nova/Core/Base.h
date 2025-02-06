#pragma once

#ifdef IS_NOVA_BUILD
	#define NOVA_API 
#else
	#define NOVA_API 
#endif  

#define BIT(x) (1<<x)
#define BIND_EVENT_FUNC(func) [this](auto&& ...args)->decltype(auto) {  return this->func( std::forward<decltype(args)>(args)... );  }
