/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

export module EnableIf;

export namespace cave
{
	template<bool Predicate, typename Result = void>
	class TEnableIf
	{ };

	template<typename Result>
	class TEnableIf<true, Result>
	{
	public:
		using Type = Result;
	};
}