#pragma once

#ifdef IS_NOVA_BUILD
	#define NOVA_API __declspec(dllexport)
#else
	#define NOVA_API __declspec(dllimport)
#endif  

