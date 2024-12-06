#pragma once
#include <RuneEngine/Engine.hpp>

class FileLoader
{
	template<class T>
	class LoadingContent
	{
		T **texture;
		sf::String path;
		std::function<void(const sf::String &path, T &)> load_function;

	public:
		LoadingContent()
			: load_function([](const sf::String &, T &) {})
		{}
		LoadingContent(const sf::String &path, std::function<void(const sf::String &, T &)> load_function);
		LoadingContent(const LoadingContent &other) = delete;
		LoadingContent(LoadingContent &&other) noexcept;
		~LoadingContent();
		void load();

		const sf::String &getLoadPath() const;
		bool isLoaded() const;
		const T *const &get() const;

		void setLoadPath(const sf::String &path);
		void setLoadFunction(std::function<void(const sf::String &, T &)> load_function);

		LoadingContent &operator=(const LoadingContent &other) = delete;
		LoadingContent &operator=(LoadingContent &&other) noexcept;
	};

public:
	using LoadingTexture = LoadingContent<sf::Texture>;
	using LoadingSound	 = LoadingContent<sf::SoundBuffer>;
	using LoadingFont	 = LoadingContent<sf::Font>;

	static FileLoader &Instance();
	void loadTextures(
		std::function<void(LoadingTexture &)> before_every_load = [](LoadingTexture &) {},
		std::function<void(LoadingTexture &)> after_every_load	= [](LoadingTexture &) {}
	);
	void loadFonts(
		std::function<void(LoadingFont &)> before_every_load = [](LoadingFont &) {},
		std::function<void(LoadingFont &)> after_every_load	 = [](LoadingFont &) {}
	);
	void loadSounds(
		std::function<void(LoadingSound &)> before_every_load = [](LoadingSound &) {},
		std::function<void(LoadingSound &)> after_every_load  = [](LoadingSound &) {}
	);
	size_t getTextureCount() const;
	size_t getSoundCount() const;
	size_t getFontCount() const;
	const sf::SoundBuffer *const &addSoundToUpload(const char *path);
	const sf::Font *const &addFontToUpload(const char *path);
	const sf::Texture *const &addTextureToUpload(const char *path);

private:
	template<class T>
	const T *const &addToUpload(std::vector<LoadingContent<T>> &upload_container, const char *path);

	std::vector<LoadingContent<sf::SoundBuffer>> sound_buffers;
	std::vector<LoadingContent<sf::Font>> fonts;
	std::vector<LoadingContent<sf::Texture>> textures;

	FileLoader() {}
	~FileLoader() {}

	FileLoader(FileLoader const &);
	FileLoader &operator=(FileLoader const &);
};
///////////////////////////
//
// template implementation
//
template<class T>
inline FileLoader::LoadingContent<T>::LoadingContent(
	const sf::String &path, std::function<void(const sf::String &, T &)> load_function
)
	: texture(new T *(nullptr)),
	  path(path),
	  load_function(load_function)
{}

template<class T>
inline FileLoader::LoadingContent<T>::LoadingContent(LoadingContent &&other) noexcept
	: texture(other.texture),
	  path(other.path)
{
	delete *other.texture;
	*other.texture = nullptr;
	delete other.texture;
	other.texture = nullptr;
}

template<class T>
inline FileLoader::LoadingContent<T>::~LoadingContent()
{
	delete *texture;
	delete texture;
}

template<class T>
inline void FileLoader::LoadingContent<T>::load()
{
	delete *texture;
	*texture = new T;
	load_function(path, **texture);
}

template<class T>
inline const sf::String &FileLoader::LoadingContent<T>::getLoadPath() const
{
	return path;
}

template<class T>
inline void FileLoader::LoadingContent<T>::setLoadFunction(std::function<void(const sf::String &, T &)> load_function)
{
	this->load_function = load_function;
}

template<class T>
inline bool FileLoader::LoadingContent<T>::isLoaded() const
{
	return texture;
}

template<class T>
inline const T *const &FileLoader::LoadingContent<T>::get() const
{
	return *texture;
}

template<class T>
inline void FileLoader::LoadingContent<T>::setLoadPath(const sf::String &path)
{
	this->path = path;
}

template<class T>
inline FileLoader::LoadingContent<T> &FileLoader::LoadingContent<T>::operator=(LoadingContent &&other) noexcept
{
	if (&other != this)
	{
		delete *texture;
		*texture = *other.texture;
		delete *other.texture;
		*other.texture = nullptr;
		delete other.texture;
		other.texture = nullptr;
	}
	return *this;
}
