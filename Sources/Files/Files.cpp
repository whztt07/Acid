#include "Files.hpp"

#include <algorithm>
#include <ostream>
#include <fstream>
#include <physfs.h>
#include "Helpers/FileSystem.hpp"

namespace acid
{
	Files::Files()
	{
	}

//	Files::~Files()
//	{
//		PHYSFS_deinit();
//	}

	void Files::Update()
	{
	}

	void Files::SetBaseDirectory(const char *argv0)
	{
		PHYSFS_init(argv0);
	}

	void Files::AddSearchPath(const std::string &path)
	{
		if (PHYSFS_mount(path.c_str(), nullptr, true) == 0)
		{
			Log::Error("File System error while adding a path or zip(%s): %s\n", path.c_str(), PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
		}
	}

	void Files::RemoveSearchPath(const std::string &path)
	{
		if (PHYSFS_unmount(path.c_str()) == 0)
		{
			Log::Error("File System error while removing a path: %s\n", path.c_str(), PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
		}
	}

	std::optional<std::string> Files::Read(const std::string &path)
	{
		PHYSFS_file *fs_file = PHYSFS_openRead(path.c_str());

		if (fs_file == nullptr)
		{
			if (!FileSystem::Exists(path) || !FileSystem::IsFile(path))
			{
				Log::Error("Error while opening file to load %s: %s\n", path.c_str(), PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
				return {};
			}

			return FileSystem::ReadTextFile(path);
		}

		PHYSFS_sint64 size = PHYSFS_fileLength(fs_file);
		std::vector<uint8_t> data(size);
		PHYSFS_readBytes(fs_file, data.data(), (PHYSFS_uint64)size);

		if (PHYSFS_close(fs_file) == 0)
		{
			Log::Error("Error while closing file %s: %s\n", path.c_str(), PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
		}

		return std::string(data.begin(), data.end());
	}
}
