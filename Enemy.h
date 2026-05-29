#pragma once
#include ".\Library\GameObject.h"
#include "global.h"


class Enemy :
    public GameObject
{
	int hImage_;//‰æ‘œID
public:
	Point pos_;//ˆÊ’u
	DIR dir_;//ˆÚ“®•ûŒü
	Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;
};

