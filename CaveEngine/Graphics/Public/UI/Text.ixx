/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;
#include <wchar.h>
#include "GraphicsApiPch.h"
#include "CoreGlobals.h"
export module Text;
import Renderable;
import cave.Core.String;
import cave.Graphics.Resource.FontManager;

namespace cave
{
	export class Text : public Renderable
	{
	public:
		Text() = delete;
		Text(WString content, WString fontName, float size);
		Text(const Text& other);
		Text(Text&& other);
		Text& operator=(const Text& other);
		Text& operator=(Text&& other);
		~Text();

		virtual void Destroy() override;

		void SetContent(WString content);
		void SetFontSize(float size);
		void SetColor(float r,float g, float b, float a = 1.0f);
		void SetFontName(WString fontName);
		WString GetFontName();
		WString GetContent();
		D2D1::ColorF GetColor();

	protected:
		virtual void update() override;
		void creatRenderCommand() override;
		void makeRenderCommand() override;

	private:
		void updateLayout();
	
	private:
		float mFontSize = 0.0f;
		WString mFontName = L"";
		WString mContent = L"";
		D2D1::ColorF mColor = D2D1::ColorF(0, 0, 0, 1);

		IDWriteTextLayout* mLayout = nullptr;

	};

	void Text::update()
	{

	}

	void Text::creatRenderCommand()
	{
		TextCommand* command = reinterpret_cast<TextCommand*>(gCoreMemoryPool.Allocate(sizeof(TextCommand)));
		new(command) TextCommand();
		command->type = RenderCommand::eType::TEXT_COMMAND;
		mCommand = command;
	}

	void Text::makeRenderCommand()
	{
		if (mLayout == nullptr)
		{
			updateLayout();
		}

		TextCommand* command = reinterpret_cast<TextCommand*>(mCommand);
		command->type = RenderCommand::eType::TEXT_COMMAND;
		command->textLayout = mLayout;
		mLayout->AddRef();
		command->position = mPosition;
		command->color = mColor;
	}
	

	Text::Text(WString content, WString fontName, float size)
		:Renderable(),
		mFontSize(size),
		mFontName(fontName),
		mContent(content),
		mColor(D2D1::ColorF(0, 0, 0, 1)),
		mLayout(nullptr)
	{

	}

	Text::Text(const Text& other)
		:Renderable(other),
		mFontSize(other.mFontSize),
		mFontName(other.mFontName),
		mContent(other.mContent),
		mColor(other.mColor)
	{
		if (mLayout != nullptr)
		{
			mLayout->Release();
			mLayout = nullptr;
		}
	}

	Text::Text(Text&& other)
		:Renderable(other),
		mFontSize(other.mFontSize),
		mFontName(other.mFontName),
		mContent(other.mContent),
		mColor(other.mColor)
	{

	}

	Text& Text::operator=(const Text& other)
	{
		if (this != &other)
		{
			mFontSize = other.mFontSize;
			mPosition = other.mPosition;
			mContent = other.mContent;
			mFontName = other.mFontName;
			mColor = other.mColor;

			mLayout = nullptr;
			mCommand = nullptr;

		}
		return *this;
	}

	Text& Text::operator=(Text&& other)
	{
		if (this != &other)
		{
			mFontSize = other.mFontSize;
			mPosition = other.mPosition;
			mContent = other.mContent;
			mFontName = other.mFontName;
			mColor = other.mColor;

			mLayout = nullptr;
			mCommand = nullptr;
		}
		return *this;
	}


	Text::~Text()
	{
		Destroy();
	}

	void Text::Destroy()
	{
		if (mCommand != nullptr)
		{
			gCoreMemoryPool.Deallocate(mCommand, sizeof(TextCommand));
			mCommand = nullptr;
		}
		if (mLayout != nullptr)
		{
			mLayout->Release();
			mLayout = nullptr;
		}
	}

	void Text::updateLayout()
	{
		if (mLayout != nullptr)
		{
			mLayout->Release();
			mLayout = nullptr;
		}
		FontManager::GetInstance().GetFactory()->CreateTextLayout(mContent.GetCString(),mContent.GetLength(),
			FontManager::GetInstance().GetFont(mFontName.GetCString()), 800, 500, &mLayout);
		mLayout->SetFontSize(mFontSize, { 0,mContent.GetLength() });
	}

	void Text::SetContent(WString content)
	{
		if (mContent != content)
		{
			mContent = content;
			updateLayout();
		}
	}

	void Text::SetFontName(WString fontName)
	{
		mFontName = fontName;
		updateLayout();
	}

	void Text::SetFontSize(float size)
	{
		mFontSize = size;

		mLayout->SetFontSize(mFontSize, { 0,mContent.GetLength() });
	}

	void Text::SetColor(float r, float g, float b, float a)
	{
		mColor = D2D1::ColorF(r, g, b, a);
	}

}