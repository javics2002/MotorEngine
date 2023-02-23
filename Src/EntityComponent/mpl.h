#pragma once
#ifndef __MPL
#define __MPL

#include <cstddef>
#include <type_traits>


namespace me {

	namespace mpl {

		// Compile-time list of types.
		template<typename ... Ts>
		struct TypeList {
			// Size of the list.
			static constexpr std::size_t size{ sizeof...(Ts) };
		};

		template<typename, typename >
		struct IndexOf;

		// IndexOf base case: found the type we're looking for.
		template<typename T, typename ... Ts>
		struct IndexOf<T, TypeList<T, Ts...>> : std::integral_constant<std::size_t, 0> {
		};

	};

};

#endif