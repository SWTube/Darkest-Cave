/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include <iterator>

import EnableIf;

export module IsIterator;

namespace cave
{
	export template<class Iter>
	concept IsIter = TIsIterator<Iter>::Value;

	template<class Iter>
	concept IsStdIter = std::_Is_iterator_v<Iter>;

	export template<class Iter>
	struct TIsIterator
	{
		static constexpr bool Value = false;
	};

	export template<IsStdIter Iter>
	struct TIsIterator<Iter>
	{
		static constexpr bool Value = true;
	};

	
}