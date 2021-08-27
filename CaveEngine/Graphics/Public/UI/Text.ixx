module;
#include "GraphicsApiPch.h"
#include "CoreGlobals.h"
export module Text;
import Renderable;

namespace cave
{
	export class Text : public Renderable
	{
	public:
		Text();
		Text(LPCWSTR content, LPCWSTR fontName, float size);
		Text(const Text& other);
		Text(Text&& other);
		Text& operator=(const Text& other);
		Text& operator=(Text&& other);
		~Text();

		virtual void Destroy() override;

		void SetContent(LPCWSTR content);
		void SetFontSize(float size);
		void SetColor(float r,float g, float b, float a = 1.0f);
		void SetFontName(LPCWSTR fontName);
		LPCWSTR GetFontName();
		LPCWSTR GetContent();
		D2D1::ColorF GetColor();

	protected:
		virtual void update() override;
		void creatRenderCommand() override;
		void makeRenderCommand() override;

	private:
		float mFontSize = 0.0f;
		LPCWSTR mFontName = L"";
		LPCWSTR mContent = L"";
		D2D1::ColorF mColor = D2D1::ColorF(0, 0, 0, 1);
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
		TextCommand* command = reinterpret_cast<TextCommand*>(mCommand);
		command->type = RenderCommand::eType::TEXT_COMMAND;
		command->fontName = mFontName;
		command->content = mContent;
		command->fontSize = mFontSize;
		command->position = mPosition;
		command->color = mColor;
	}
	
	Text::Text()
	{

	}

	Text::Text(LPCWSTR content, LPCWSTR fontName, float size)
		:mFontSize(size),
		mFontName(fontName),
		mContent(content)
	{

	}

	Text::Text(const Text& other)
		:Renderable(other),
		mFontSize(other.mFontSize),
		mFontName(other.mFontName),
		mContent(other.mContent),
		mColor(other.mColor)
	{

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

	}

	void Text::SetContent(LPCWSTR content)
	{
		mContent = content;
	}

	void Text::SetFontName(LPCWSTR fontName)
	{
		mFontName = fontName;
	}

	void Text::SetFontSize(float size)
	{
		mFontSize = size;
	}

	void Text::SetColor(float r, float g, float b, float a)
	{
		mColor = D2D1::ColorF(r, g, b, a);
	}

}