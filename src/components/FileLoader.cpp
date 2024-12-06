#include "components/FileLoader.hpp"

FileLoader &FileLoader::Instance()
{
	// согласно стандарту, этот код ленивый и потокобезопасный
	static FileLoader s;
	return s;
}

void FileLoader::loadTextures(
	std::function<void(LoadingTexture &)> before_every_load, std::function<void(LoadingTexture &)> after_every_load
)
{
	for (auto &content: textures)
	{
		before_every_load(content);
		content.load();
		after_every_load(content);
	}
}

void FileLoader::loadFonts(
	std::function<void(LoadingFont &)> before_every_load, std::function<void(LoadingFont &)> after_every_load
)
{
	for (auto &content : fonts)
	{
		before_every_load(content);
		content.load();
		after_every_load(content);
	}
}

void FileLoader::loadSounds(
	std::function<void(LoadingSound &)> before_every_load, std::function<void(LoadingSound &)> after_every_load
)
{
	for (auto &content : sound_buffers)
	{
		before_every_load(content);
		content.load();
		after_every_load(content);
	}
}

size_t FileLoader::getTextureCount() const
{
	return textures.size();
}

size_t FileLoader::getSoundCount() const
{
	return sound_buffers.size();
}

size_t FileLoader::getFontCount() const
{
	return fonts.size();
}

const sf::SoundBuffer *const &FileLoader::addSoundToUpload(const char *path)
{
	return addToUpload(sound_buffers, path);
}

const sf::Font *const &FileLoader::addFontToUpload(const char *path)
{
	return addToUpload(fonts, path);
}

const sf::Texture *const &FileLoader::addTextureToUpload(const char *path)
{
	return addToUpload(textures, path);
}

template<class T>
const T *const &FileLoader::addToUpload(std::vector<LoadingContent<T>> &upload_container, const char *path)
{
	upload_container.emplace_back(path, [](const sf::String &path, T &content) {
		if (!content.loadFromFile(path))
		{
			throw new std::out_of_range("File not found: '" + path + "'");
		}
	});
	return upload_container.back().get();
}