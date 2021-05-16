/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

export module FlatformTimer;

export import CoreType;

namespace cave
{
	export class FlatformTimer
	{
	public:
		virtual ~FlatformTimer();

		static FlatformTimer* Instance();

		virtual TimePoint GetTimePoint() = 0;
		virtual float GetTimeDiffer(TimePoint begin, TimePoint end) = 0;
		virtual float GetStartTime() const = 0;

		virtual double GetTimeDiffer64(TimePoint begin, TimePoint end) = 0;
		virtual double GetStartTime64() const = 0;


	protected:
		FlatformTimer();

	protected:
		float mStartTime;

	private:
		static FlatformTimer* mInstance;
	};
}