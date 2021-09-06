module;
#include <filesystem>
#include <vector>
#include <unordered_map>
#include "GraphicsApiPch.h"
export module cave.Graphics.Resource.FontManager;

import cave.Core.String;
//import cave.Core.Containers.HashTable;

namespace cave
{
	export class FontManager final
	{
	public:

		static FontManager& GetInstance()
		{
			static FontManager msInstance;
			return msInstance;
		}
		
		void Init(IDWriteFactory3* factory);

		IDWriteTextFormat* GetFont(std::wstring fontName);
		IDWriteFactory3* GetFactory();

	private:
		FontManager() = default;
		FontManager(const FontManager& other) = delete;
		FontManager& operator=(const FontManager& other) = delete;
		~FontManager();

		void loadFontsInFontFolder();

	private:
		IDWriteFactory3* mFactory = nullptr;
		IDWriteFontCollection1* mFontCollection = nullptr;

		std::unordered_map <std::wstring , IDWriteTextFormat* > mFonts;
		IDWriteTextFormat* mDefaultFont;
	};
	
	void FontManager::Init(IDWriteFactory3* factory)
	{
		mFactory = factory;
		loadFontsInFontFolder();
		
		mFactory->CreateTextFormat(
			L"", nullptr,
			DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL,
			10.0f, L"ko", &mDefaultFont);
	}

	IDWriteTextFormat* FontManager::GetFont(std::wstring fontName)
	{
		IDWriteTextFormat* format = mDefaultFont;

		if(mFontCollection != nullptr)
		{
			if (mFonts.contains(fontName))
				format = mFonts[fontName];
			else 
			{
				UINT32 index;
				BOOL exists;
				mFontCollection->FindFamilyName(fontName.c_str(), &index, &exists);
				if (exists)
				{
					mFactory->CreateTextFormat(
						fontName.c_str(), mFontCollection,
						DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL,
						DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL,
						DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL,
						10.0f, L"ko", &format);

					mFonts[fontName] = format;
				}
			}

		}

		return format;
	}
	
	IDWriteFactory3* FontManager::GetFactory()
	{
		return mFactory;
	}

	FontManager::~FontManager()
	{

		for (auto it = mFonts.begin(); it != mFonts.end();) {
			it->second->Release();
			it->second = nullptr;
			mFonts.erase(it++);
		}

		if (mDefaultFont != nullptr)
		{
			mDefaultFont->Release();
			mDefaultFont = nullptr;
		}

		if (mFontCollection != nullptr)
		{
			mFontCollection->Release();
			mFontCollection = nullptr;
		}

	}

	void FontManager::loadFontsInFontFolder()
	{
		std::filesystem::path filePath = PROJECT_DIR;
		filePath /= L"CaveEngine\\Graphics\\Resource\\Fonts\\";
		
		std::wstring folder = filePath.wstring().c_str();
		
		filePath /= L"*.*";
		std::vector<std::wstring> fontfiles;

		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(filePath.generic_wstring().c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if ( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) 
				{
					fontfiles.push_back(fd.cFileName);
				}
			} while (::FindNextFile(hFind, &fd));
			::FindClose(hFind);
			
		}
		
		IDWriteFontSetBuilder* fontSetBuilder;
		if (mFactory->CreateFontSetBuilder(&fontSetBuilder) != S_OK) return;

		for (std::wstring fontName : fontfiles)
		{
			std::wstring fullPath = folder + fontName;
			IDWriteFontFile* fontFile;
			uint32_t result;
			result = mFactory->CreateFontFileReference(fullPath.c_str(),nullptr, &fontFile);

			if (result != S_OK)
				continue;

			BOOL isSupported;
			DWRITE_FONT_FILE_TYPE fileType;
			UINT32 numberOfFonts;

			fontFile->Analyze(&isSupported, &fileType, nullptr, &numberOfFonts);

			if (!isSupported)
				continue;

			// For each font within the font file, get a font face reference and add to the builder.
			for (UINT32 fontIndex = 0; fontIndex < numberOfFonts; fontIndex++)
			{
				IDWriteFontFaceReference* fontFaceReference;
				mFactory->CreateFontFaceReference(fontFile, fontIndex, DWRITE_FONT_SIMULATIONS_NONE, &fontFaceReference);

				// If fonts were assumed known, we could set custom properties, and would do that here.
				// But these are not assumed known, so we'll leave it to DirectWrite to read properties
				// directly out of the font files.

				fontSetBuilder->AddFontFaceReference(fontFaceReference);
				fontFaceReference->Release();
			}

		}

		IDWriteFontSet* fontSet;
		fontSetBuilder->CreateFontSet(&fontSet);
		fontSetBuilder->Release();
		
		mFactory->CreateFontCollectionFromFontSet(fontSet, &mFontCollection);
		
		fontSet->Release();


		/*
		IDWriteFontFile* fontFile;
		uint32_t result;
		result = mFactory->CreateFontFileReference(L"D:\\Desktop\\SW-Project\\Darkist-Cave\\CaveEngine\\Graphics\\Resource\\Fonts\\NotoSansKR-Regular.otf",
			nullptr, &fontFile);

		if (result != S_OK)
			return;

		IDWriteFontSetBuilder* fontSetBuilder;
		result = mFactory->CreateFontSetBuilder(&fontSetBuilder);

		if (result != S_OK)
			return;

		BOOL isSupported;
		DWRITE_FONT_FILE_TYPE fileType;
		UINT32 numberOfFonts;

		fontFile->Analyze(&isSupported, &fileType,  nullptr, &numberOfFonts);

		if (!isSupported)
			return;

		// For each font within the font file, get a font face reference and add to the builder.
		for (UINT32 fontIndex = 0; fontIndex < numberOfFonts; fontIndex++)
		{
			IDWriteFontFaceReference* fontFaceReference;
			mFactory->CreateFontFaceReference(fontFile, fontIndex, DWRITE_FONT_SIMULATIONS_NONE, &fontFaceReference);

			// If fonts were assumed known, we could set custom properties, and would do that here.
			// But these are not assumed known, so we'll leave it to DirectWrite to read properties
			// directly out of the font files.

			fontSetBuilder->AddFontFaceReference(fontFaceReference);
			fontFaceReference->Release();
		}
		IDWriteFontSet* fontSet;

		fontSetBuilder->CreateFontSet(&fontSet);
		fontSetBuilder->Release();

		mFactory->CreateFontCollectionFromFontSet(fontSet, &mFontCollection);

		fontSet->Release();

		IDWriteFontFamily* fontFamily;
		IDWriteLocalizedStrings* localizedFontName;

		TCHAR c_styleFontName[100];

		mFontCollection->GetFontFamily(0, &fontFamily);
		fontFamily->GetFamilyNames(&localizedFontName);
		localizedFontName->GetString(0, c_styleFontName, 100);
		*/
	}

}