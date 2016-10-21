#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include "Character.h"
#include "../base/Game.h"


Character::Character(){

	mNumberAnimations = 4;
	mSpriteColumns = 10;
	mSpriteRows = 6;
	isDead = false;
	framesDamaged = 0;

	//Default
	mNumStand = 3;
	mNumMove = 10;
	mNumAttack = 3;
	mNumFly = 0;
	mNumSwallow = 0;

	isSwallable = true;

	//Sprite rows
	START_ROW_STAND_RIGHT = 0;
	START_ROW_STAND_LEFT = 1;
	START_ROW_MOVE_RIGHT = 2;
	START_ROW_MOVE_LEFT = 3;
	START_ROW_ATTACK_RIGHT = 4;
	START_ROW_ATTACK_LEFT = 5;
	START_ROW_FLY_RIGHT = 6;
	START_ROW_FLY_LEFT = 7;
	START_ROW_SWALLOW_RIGHT = 8;
	START_ROW_SWALLOW_LEFT = 9;
}

void Character::init(ShaderProgram &shaderProgram, Scene* scene)
{
	mScene = scene;

	bJumping = false;
	bAttacking = false;

	cout << "START_ROW_STAND_RIGHT  = " << START_ROW_STAND_RIGHT << endl;
	cout << "START_ROW_STAND_LEFT  = " << START_ROW_STAND_LEFT << endl;
	cout << "START_ROW_MOVE_RIGHT  = " << START_ROW_MOVE_RIGHT << endl;
	cout << "START_ROW_MOVE_LEFT  = " << START_ROW_MOVE_LEFT << endl;
	cout << "START_ROW_ATTACK_RIGHT  = " << START_ROW_ATTACK_RIGHT << endl;
	cout << "START_ROW_ATTACK_LEFT  = " << START_ROW_ATTACK_LEFT << endl;


	float columnSize = 1.f / float(mSpriteColumns);
	float rowSize = 1.f / float(mSpriteRows);

	spritesheet.loadFromFile(mPathToSpritesheet, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(columnSize, rowSize), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(mNumberAnimations);


    // ----------- STAND ANIMATIONS -----------
	sprite->setAnimationSpeed(STAND_LEFT, NUM_OF_FRAMES_SLOW);
	sprite->setAnimationSpeed(STAND_RIGHT, NUM_OF_FRAMES_SLOW);
	for (int i = 0; i < mNumStand; ++i) {
		sprite->addKeyframe(STAND_LEFT, glm::vec2(i*columnSize, START_ROW_STAND_LEFT*rowSize));
        sprite->addKeyframe(STAND_RIGHT, glm::vec2(i*columnSize, START_ROW_STAND_RIGHT*rowSize));
	}

    // ----------- MOVE ANIMATIONS -----------
    sprite->setAnimationSpeed(MOVE_LEFT, NUM_OF_FRAMES);
    sprite->setAnimationSpeed(MOVE_RIGHT, NUM_OF_FRAMES);
    for (int i = 0; i < mNumMove; ++i) {
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(i*columnSize, START_ROW_MOVE_LEFT*rowSize));
        sprite->addKeyframe(MOVE_RIGHT, glm::vec2(i*columnSize, START_ROW_MOVE_RIGHT*rowSize));
    }

    // ----------- ATTACK ANIMATIONS -----------
	sprite->setAnimationSpeed(ATTACK_RIGHT, NUM_OF_FRAMES);
    sprite->setAnimationSpeed(ATTACK_LEFT, NUM_OF_FRAMES);

    for (int i = 0; i < mNumAttack; ++i) {
        sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(i*columnSize, START_ROW_ATTACK_RIGHT*rowSize));
        sprite->addKeyframe(ATTACK_LEFT, glm::vec2(i*columnSize, START_ROW_ATTACK_LEFT*rowSize));
    }

    // ----------- FLY ANIMATIONS -----------
    sprite->setAnimationSpeed(FLY_LEFT, NUM_OF_FRAMES);
    sprite->setAnimationSpeed(FLY_RIGHT, NUM_OF_FRAMES);
    for (int i = 0; i < mNumFly; ++i) {
        sprite->addKeyframe(FLY_LEFT, glm::vec2(i*columnSize, START_ROW_FLY_LEFT*rowSize));
        sprite->addKeyframe(FLY_RIGHT, glm::vec2(i*columnSize, START_ROW_FLY_RIGHT*rowSize));
    }

	sprite->changeAnimation(1);
	sprite->setPosition(glm::vec2(float(posCharacter.x), float(posCharacter.y)));

}

void Character::setPathToSpriteSheet(string path){

	mPathToSpritesheet = path;
}

void Character::update(int deltaTime)
{
	if (framesDamaged > 0) { //To test how this behaviour with enemies near
		if (framesDamaged % DAMAGED_RATE == 0) sprite->setIsDamaged(1.0f);
		else sprite->setIsDamaged(0.0f);

		if ((sprite->animation() % 2) == 0) {//looking left, send to right
			posCharacter.x += DAMAGED_DISTANCE;
			if (mScene->collisionMoveRightOnlyMap(this)) {
				posCharacter.x -= DAMAGED_DISTANCE;
			}
		}
		else {
			posCharacter.x -= DAMAGED_DISTANCE;
			if (mScene->collisionMoveLeftOnlyMap(this)) {
				posCharacter.x += DAMAGED_DISTANCE;
			}
		}
		--framesDamaged;
	}
	//cout << framesDamaged << endl;

	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(posCharacter.x), float(posCharacter.y)));
}

void Character::render()
{
	sprite->render();
}

void Character::setPosition(const glm::vec2 &pos)
{
	posCharacter = pos;
	sprite->setPosition(glm::vec2(float(posCharacter.x), float(posCharacter.y)));
}

void Character::justDamaged() {
	if (framesDamaged == 0) 
		framesDamaged = DAMAGED_TIME;
	
}



