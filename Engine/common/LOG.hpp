#pragma once
#include <iostream>
#include <filesystem>

#ifndef COUT_DISABLE
	#define COUT_ENABLED
	#define CRED(msg) "\033[31m" msg "\033[0m"
	#define CGREEN(msg) "\033[32m" msg "\033[0m"
	#define CYELLOW(msg) "\033[33m" msg "\033[0m"
	#define CBOLD(msg) "\033[1m" msg "\033[0m"

	#define COUT(...) _COUT(__VA_ARGS__)

	// < WIN32 FIX
	template <typename T>
	auto print_arg(T&& arg) -> decltype(std::cout << std::forward<T>(arg), void()) {
		std::cout << std::forward<T>(arg) << " ";
	}

	inline void print_arg(const char* arg) {
		std::cout << arg << " ";
	}

	inline void print_arg(const std::string& arg) {
		std::cout << arg << " ";
	}
	inline void print_arg(const std::filesystem::path& arg) {
		std::cout << arg.string() << " ";
	}
	// > WIN32 FIX

	template <typename... T>
	inline void _COUT(T&&... args) {
		int dummy[] = { 0, (print_arg(std::forward<T>(args)), 0)... };
		static_cast<void>(dummy); // Avoid unused variable warning
		std::cout << '\n';
	}

	#ifndef LOG_DISABLE
		#define LOG(...) _LOG(__VA_ARGS__)

		template <typename... T>
		inline void _LOG (const char* title, T&&... args) {
			_COUT( CYELLOW("[LOG]"), title, "->", args... );
		}

		#ifdef LOG_VECTOR
			#include <vector>
			template <typename T>
			std::ostream& operator<< (std::ostream& os, std::vector<T>& arr) {
				os << "vector{ ";
				for (auto& a : arr)
					os << a << " ";
				os << "}"; return os;
			}
		#endif
	#endif
#else
	#define COUT(...)
	#define LOG(...)
	#define TEST(...)
#endif
