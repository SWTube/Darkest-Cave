/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module FlatformTimer;

import WindowsTimer;

namespace cave
{
	FlatformTimer* FlatformTimer::mInstance = nullptr;

	FlatformTimer::FlatformTimer()
	{
		mStartTime = 0.f;
	}

	FlatformTimer::~FlatformTimer()
	{

	}

	FlatformTimer* FlatformTimer::Instance()
	{
		if (mInstance == nullptr)
		{
#ifdef _WIN32
			mInstance = new WindowsTimer();
#endif // _WIN32
		}
		return mInstance;
	}
}