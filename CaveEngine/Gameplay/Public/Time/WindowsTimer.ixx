/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

export module WindowsTimer;

import FlatformTimer;

namespace cave
{
	export class WindowsTimer final : public FlatformTimer
	{
	public:
		friend FlatformTimer;
		~WindowsTimer() {}

	private:
		WindowsTimer();

		TimePoint GetTimePoint() override;
		float GetTimeDiffer(TimePoint begin, TimePoint end) override;
		float GetStartTime() const override;

		double GetTimeDiffer64(TimePoint begin, TimePoint end) override;
		double GetStartTime64() const override;
	private:
		float frequency;
		double frequency64;
	};
}