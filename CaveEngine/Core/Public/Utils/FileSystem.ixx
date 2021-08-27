/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "Debug/Log.h"

export module cave.Core.Utils.FileSystem;

import std.core;
import std.filesystem;

import cave.Core.String;

namespace cave
{
	export std::vector<std::filesystem::path> GetFilesInDirectoryByExtension(const WString& directory, const WString& extension);
	export std::vector<std::filesystem::path> GetFilesInDirectoryByExtension(const std::filesystem::path& directory, const WString& extension);

	std::vector<std::filesystem::path> GetFilesInDirectoryByExtension(const WString& directory, const WString& extension)
	{
		std::filesystem::path directoryPath = directory.GetCString();

		return GetFilesInDirectoryByExtension(directoryPath, extension);
	}

	std::vector<std::filesystem::path> GetFilesInDirectoryByExtension(const std::filesystem::path& directory, const WString& extension)
	{
		std::vector<std::filesystem::path> files;

		if (std::filesystem::exists(directory) && std::filesystem::is_directory(directory))
		{
			for (const auto& it : std::filesystem::directory_iterator(directory))
			{
				if (extension == it.path().extension().c_str())
				{
					files.push_back(it.path().filename());
				}
			}
		}

		return files;
	}

#ifdef CAVE_BUILD_DEBUG
	export namespace FileSystemTest
	{
		void Main();

		void Main()
		{
			std::filesystem::path currentPath = std::filesystem::current_path();
			
			WLOGDF(eLogChannel::CORE, L"Current Path: %s", currentPath.c_str());

			std::vector<std::filesystem::path> files = GetFilesInDirectoryByExtension(currentPath, L".cpp");

			for (const std::filesystem::path& path : files)
			{
				WLOGDF(eLogChannel::CORE, L"\tFile: %s", path.c_str());
			}
		}
	}
#endif
}