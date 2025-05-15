#pragma once
#include"scene.h"
#include"sceneManager.h"
#include<vector>
#include"util.h"


extern IMAGE GameMap;
extern vector<int> GameMaps;
extern bool gamerunning;
extern bool gameover;
extern bool gameRestart;

extern IMAGE P1;
extern IMAGE P2;


class GameScene :public Scene {
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter() {
		gamerunning = true;

		BeginBatchDraw();
		while (game_enter_timer--) {
			cleardevice();
			unsigned char alpha = 255 * (game_enter_delay - game_enter_timer) / game_enter_delay;
			Alpha_putimage(0, 0, GameMap, alpha);

			FlushBatchDraw();
		}
		EndBatchDraw();
		game_enter_timer = game_enter_delay;
	}
	void on_update() {}
	void on_draw() {
		putimage(0, 0, &GameMap);

	}
	void on_input(const ExMessage& msg) {
		if (gameover && msg.vkcode == 'E') {
			scene_manager.switch_to(SceneManager::SceneType::Menu);
		}
		else if (gameover && msg.vkcode == 'Q') {
			running=false;
		}
	}
	void on_exit() {
		gameRestart = true;
		gameover = false;
		gamerunning = false;
	}

private:
	const int game_enter_delay = 200;
	int game_enter_timer = game_enter_delay;//游戏界面进入动画计时器


};