/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

namespace cave
{
	class Object;

	class ObjectPool final
	{
	public:
		friend class Game;

		~ObjectPool();

		static Object* Allocate();
		static void Deallocate(Object* object);

	private:
		ObjectPool();
		ObjectPool(const ObjectPool&) = delete;
		ObjectPool(ObjectPool&&) = delete;

		ObjectPool& operator=(const ObjectPool&) = delete;
		ObjectPool& operator=(ObjectPool&&) = delete;

	private:
		static Object* mObjectArray;
		static size_t mObjectArrayMaxSize;
		static size_t mObjectArrayIndex;
	};
}