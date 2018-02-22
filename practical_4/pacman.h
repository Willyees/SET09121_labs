#include <memory>
#include "scene.h"


extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene {
private:
	sf::Text text;

public:
	MenuScene();
	void update(double dt) override;
	void render() override;
	void load() override;
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock; 
	void respawn();
public:
	std::shared_ptr<Entity> makeNibble(const sf::Vector2ul& nl, bool big);
	GameScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};


