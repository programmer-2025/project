#include "PlayScene.h"
#include <DxLib.h>
#include "../Stage.h"
#include "../Player.h"
#include "../Enemy.h"
#include "../ImGui/imgui.h"

PlayScene::PlayScene()
{
	new Stage();
	new Player();
	new Enemy();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(200, 255, 255), TRUE);
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
	static int x = 0, y = 0;
	GetMousePoint(&x, &y);

	ImGui::Begin("Debug");
	ImGui::Text("Mouse: (%d, %d) (%d,%d)", x, y, x / STAGE_WIDTH, y / STAGE_HEIGHT);
	auto enemy = FindGameObject<Enemy>();
	ImGui::Text("Enemy: (%d,%d) (%d,%d)", enemy->pos_.x, enemy->pos_.y, enemy->pos_.x / STAGE_WIDTH, enemy->pos_.y / STAGE_HEIGHT);
	ImGui::End();
}
