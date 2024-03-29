#pragma once

#include "SFML/Graphics.hpp"
#include "../../Graphics_Engine//Space/AABB.h"
struct tbuffer
{
	sf::Texture tbuf;
	std::string name_;
};

class Textures
{
private:
	std::vector<tbuffer>ListOfTextures;

public:
	Textures() {}

	void SetTexturesBuffer(std::string filename);

	sf::Texture* getTexture(std::string filename);

	std::vector<tbuffer>* reTbuf();

	~Textures() {}
};