#include "Sound.h"


Sound::Sound(std::string filename)
{
	if (filename.size() > 0) {
		if (filename.find(".wav") != std::string::npos) {
			sbuffer* nbuf = new sbuffer;
			nbuf->name_ = filename;
			nbuf->sbuf.loadFromFile(filename);
			ListOfSongs.push_back(*nbuf);
		}
	}
}

void Sound::SetMusicBuffer(std::string filename)
{
	if (filename.size() > 0) {
		if (filename.find(".wav") != std::string::npos) {
			sbuffer* nbuf = new sbuffer;
			nbuf->name_ = filename;
			nbuf->sbuf.loadFromFile(filename);
			ListOfSongs.push_back(*nbuf);
		}
	}
}
void Sound::SetSFXBuffer(std::string filename)
{
	if (filename.size() > 0) {
		if (filename.find(".wav") != std::string::npos) {
			sbuffer* nbuf = new sbuffer;
			nbuf->name_ = filename;
			nbuf->sbuf.loadFromFile(filename);
			ListOfSfx.push_back(*nbuf);
		}
	}
}

sf::SoundBuffer* Sound::GetBuffer(std::string filename)
{
	for (short i = 0; i < ListOfSongs.size(); i++)
	{
		if (ListOfSongs.at(i).name_ == filename)
			return &ListOfSongs.at(i).sbuf;
	}
	return nullptr;
}

std::vector<sbuffer>* Sound::reSfx()
{
	return &ListOfSfx;
}

std::vector<sbuffer>* Sound::reSound()
{
	return &ListOfSongs;
}



