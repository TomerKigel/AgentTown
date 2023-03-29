#include "Textures.h"

void Textures::SetTexturesBuffer(std::string filename)
{
	if (filename.size() > 0) {
		if (filename.find(".png") != std::string::npos) {
			tbuffer* nbuf = new tbuffer;
			nbuf->name = filename;
			if (!nbuf->tbuf.loadFromFile(filename))
				throw(filename);
			ListOfTextures.push_back(*nbuf);
		}
	}
}

sf::Texture* Textures::getTexture(std::string filename)
{
	for (short i = 0; i < ListOfTextures.size(); i++)
	{
		if (ListOfTextures.at(i).name == filename)
			return &ListOfTextures.at(i).tbuf;
	}
	return nullptr;
}


std::vector<tbuffer>* Textures::reTbuf()
{
	return &ListOfTextures;
}
