/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <concepts>
#include <iterator>
#include <vector>

namespace cave
{
#ifdef __WIN32__
	template<class Iter>
	concept StdIterType = std::_Is_iterator_v<Iter>;
#else
	template<class Iter>
	concept StdIterType = std::iterator_traits<Iter>::iterator_category;
#endif

	template<class Iter>
	struct TIsIterator
	{
		static constexpr bool Value = false;
	};

	template<StdIterType Iter>
	struct TIsIterator<Iter>
	{
		static constexpr bool Value = true;
	};	

	template<class Iter>
	concept IterType = TIsIterator<Iter>::Value;
}