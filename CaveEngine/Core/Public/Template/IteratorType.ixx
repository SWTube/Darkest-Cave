/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
export module IteratorType;

export namespace cave
{
	template<class T>
	concept InputIterator = requires(T a, T b)
	{
		T(a);
		b = a;
		++a;
		a++;

		a == b;
		a != b;

		*a;
	};

	template<class T>
	concept ForwardIterator = InputIterator<T> && requires()
	{
		T();
	};

	template<class T>
	concept BidirectionalIterator = ForwardIterator<T> && requires(T a)
	{
		--a;
		a--;
		*a--;
	};

	template<class T>
	concept RandomAccessIterator = BidirectionalIterator<T> && requires(T a, T b, size_t n)
	{
		a + n;
		n + a;
		a - n;
		a - b;

		a < b;
		a <= b;
		a > b;
		a >= b;
		
		a += n;
		a -= n;

		a[n];
	};
}