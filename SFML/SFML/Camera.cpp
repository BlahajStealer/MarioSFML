#include "Camera.h"

sf::View Camera::MoveCamera(sf::Sprite Player) {
	if (Player.getPosition().x >= 136) {
		sf::View camera({ Player.getPosition().x, 128.f }, { 256, 240 });
		return camera;
	}
	else {
		sf::View camera({ 136.f, 128.f }, { 256, 240 });
		return camera;

	}

}