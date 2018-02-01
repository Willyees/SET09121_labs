#include "levelsystem.h"
#include <fstream>


using namespace std;
using namespace sf;

unique_ptr<LevelSystem::TILE[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;

float LevelSystem::_tileSize(100.f);
vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;

map<LevelSystem::TILE, sf::Color> LevelSystem::_colours{
	{WALL, Color::White}, {END, Color::Red}
};

sf::Color LevelSystem::getColor(LevelSystem::TILE t) {	
	auto it = _colours.find(t);
	if (it == _colours.end()) {
		_colours[t] = Color::Transparent;
	}
	return _colours[t];
}

void LevelSystem::setColor(LevelSystem::TILE t, sf::Color c) {
	auto it = _colours.find(t);
	if (it != _colours.end()) {
		_colours[t] = c;
	}
	else { //add new tile/color if they are not in the map
		_colours.insert(std::pair<LevelSystem::TILE, sf::Color>(t, c));
	}
}