#include "Enemy.h"
#include "time.h"
#include "Stage.h"
#include "Library/ObjectManager.h"
#include "ImGui/imgui.h"

namespace
{
	const int OUT_LINE_POINT = 1;
	const int ENEMY_SIZE = 48; //敵のサイズ 32*32
	const Point ENEMY_START_POS = { OUT_LINE_POINT * CHA_SIZE, OUT_LINE_POINT * CHA_SIZE }; //敵の初期位置
	const DIR INIT_ENEMY_DIR = { RIGHT };
	const int ENEMY_DRAW_SIZE = 32; //敵の描画サイズ
	const int animFrame[4]{ 0, 1, 2, 1 };
	const float ANIM_INTERVAL = 0.2f;

	const int maxX = ((STAGE_WIDTH * CHA_SIZE) / STAGE_WIDTH) - 1;
	const int maxY = ((STAGE_HEIGHT * CHA_SIZE) / STAGE_HEIGHT) - 1;
	const int maxRightX = (maxX - OUT_LINE_POINT);
	const int maxRightY = (maxY - OUT_LINE_POINT);
}


Enemy::Enemy()
	: GameObject() 
{
	hImage_ = LoadGraph("Assets/panda_R.png");
	pos_ = ENEMY_START_POS; //32はブロックの位置pos_
	dir_ = INIT_ENEMY_DIR;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//GetRand(数値)
	//3秒に1回向きをランダムに変える
	static float dir_timer = 3.0f;
	static float prog_timer = 0.5f;
	float dt = Time::DeltaTime();
	dir_timer = dir_timer - dt;
	prog_timer = prog_timer - dt;
	if (dir_timer < 0.0f)
	{
		// dir_ = (DIR)(GetRand(3));		
		int x = pos_.x / STAGE_WIDTH;
		int y = pos_.y / STAGE_HEIGHT;

		if (y == OUT_LINE_POINT) {
			if (x == maxRightX) {
				dir_ = DIR::DOWN;
			}
			else {
				dir_ = DIR::RIGHT;
			}
		}
		else if (y == maxRightY) {
			if (x == maxRightX) {
				dir_ = DIR::LEFT;
			}
			else {
				dir_ = DIR::UP;
			}
		}
		dir_timer = 3.0f + dir_timer;
	}

	Point newPos = pos_;
	if (prog_timer < 0.0f)
	{
		switch (dir_)
		{
		case UP:
			newPos.y -= ENEMY_DRAW_SIZE;
			break;
		case DOWN:
			newPos.y += ENEMY_DRAW_SIZE;
			break;
		case LEFT:
			newPos.x -= ENEMY_DRAW_SIZE;
			break;
		case RIGHT:
			newPos.x += ENEMY_DRAW_SIZE;
			break;
		default:
			break;
		}
		//Point p = ((Stage*) FindGameObject<Stage>())->GetMap(newPos.x / CHA_SIZE, newPos.y / CHA_SIZE);
		int mapValue = FindGameObject<Stage>()->GetMap(newPos.x / CHA_SIZE, newPos.y / CHA_SIZE);
		Stage* stage = FindGameObject<Stage>();
		//移動先がステージの外に出ないようにする

		if (mapValue != 1) {
			pos_ = newPos;
		}

		/*
		if (!(newPos.x < 1 || newPos.x >(STAGE_WIDTH - 2) * ENEMY_DRAW_SIZE
			|| newPos.y < 1 || newPos.y >(STAGE_HEIGHT - 2) * ENEMY_DRAW_SIZE))
		{
			pos_ = newPos;
		}
		*/
		prog_timer = 0.5f + prog_timer;
	}

}

void Enemy::Draw()
{
	static float animTimer = ANIM_INTERVAL;
	static int frame = 0;
	int nowFrame = animFrame[frame];

	Rect iRect[4] = {
		{  nowFrame * ENEMY_SIZE, 3 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE},
		{  nowFrame * ENEMY_SIZE, 0 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE},
		{  nowFrame * ENEMY_SIZE, 1 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE},
		{  nowFrame * ENEMY_SIZE, 2 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE}
	};
	DrawBox(pos_.x, pos_.y, pos_.x + ENEMY_DRAW_SIZE, pos_.y + ENEMY_DRAW_SIZE,
		GetColor(255, 255, 0), FALSE,2);
	DrawRectExtendGraph(pos_.x, pos_.y,pos_.x + ENEMY_DRAW_SIZE, pos_.y + ENEMY_DRAW_SIZE,
		               iRect[dir_].x, iRect[dir_].y, iRect[dir_].w, iRect[dir_].h, hImage_, TRUE);
	if (animTimer < 0) {
		frame = (++frame) % 4;
		animTimer = ANIM_INTERVAL + animTimer;
	}
	animTimer = animTimer - Time::DeltaTime();

}
