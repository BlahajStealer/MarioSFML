#include "Bowser.h"


void Bowser::Jump() {
	int RandomJump = rand()*16;
	if (RandomJump == 1) {
		speed.y = -2.f;
		Jumping = true;
	}
	if (Jumping) {
		speed.y += .1f;
		if (speed.y >= 2.2f) {
			Jumping = false;
		}
	}
}
void Bowser::Fireball() {
	int RandomFireball = rand() * 16;
	if (RandomFireball == 1) {
		BowserFireball tempFB;
		
	}

}