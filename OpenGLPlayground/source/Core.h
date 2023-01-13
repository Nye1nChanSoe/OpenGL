#pragma once 

#include <cstdio>
#include <memory>

#define INFO(...) { printf(__VA_ARGS__); printf("\n"); }
#define WARN(...) { printf("[Warning]: "); printf(__VA_ARGS__); printf("\n"); }
#define ERROR(...) { printf("[Error]: "); printf(__VA_ARGS__); printf("\n"); }


#define glAssert(x, ...) if(!x)\
	{\
		ERROR(__VA_ARGS__);\
		printf("\n");\
		__debugbreak();\
	};

#define BIT(x) 1 << x

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
