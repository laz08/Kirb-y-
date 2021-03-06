//
// Created by quokka on 20/10/16.
//

#include "Kirby.h"
#include "../base/Game.h"

Kirby::Kirby() {

    setPathToSpriteSheet("images/kirby_spritesheet.png");
    mSpriteRows = 11;
    mNumberAnimations = 9;

	START_ROW_DEATH = 10;

    mNumDeath = 8;
    mNumFly = 6;
    mNumSwallow = 2;
}

void Kirby::init(ShaderProgram &shaderProgram, Scene *scene) {

    Player::init(shaderProgram, scene);

}

int Kirby::getAttackSound() {
	return SOUND_VACUUMING;
}