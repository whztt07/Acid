﻿#pragma once

#include <Uis/UiObject.hpp>
#include <Maths/Timer.hpp>
#include <Fonts/Text.hpp>

using namespace acid;

namespace test
{
	class OverlayDebug :
		public UiObject
	{
	private:
		std::unique_ptr<Text> m_textInfo;
		std::unique_ptr<Text> m_textFps;
		std::unique_ptr<Text> m_textUps;
		Timer m_timerUpdate;
	public:
		OverlayDebug(UiObject *parent);

		~OverlayDebug();

		virtual void UpdateObject() override;

	private:
		std::unique_ptr<Text> CreateStatus(const std::string &content, const float &positionX, const float &positionY, const TextJustify &justify);
	};
}
