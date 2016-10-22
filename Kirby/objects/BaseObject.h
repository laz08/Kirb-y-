#pragma once

#include "../base/Sprite.h"
#include "../base/TileMap.h"

class Scene;

class BaseObject
{
public:
	BaseObject();
	~BaseObject(){}

	virtual void init(ShaderProgram &shaderProgram, Scene* scene);
	virtual void update(int deltaTime);
	void render();

	void setPathToSpriteSheet(string pathToSpriteSheet); //must be called before init

	void setTexturePosition(const glm::fvec2 &pos); //must be called before init
	void setPosition(const glm::ivec2 &pos);

	glm::ivec2 getPosition() { return posObj; }
	glm::ivec2 getSize() { return glm::ivec2(16, 16); }

	bool isTaken() { return bTaken; }

protected:
	string mPathToSpritesheet;
	Texture spritesheet;
	Sprite *sprite;
	Scene* mScene;
	glm::fvec2 mTexturePosition;

	bool bTaken; //Object has been taken, make it dissapear on the next frames
	int mNumberAnimations;
	glm::ivec2 posObj;

};

