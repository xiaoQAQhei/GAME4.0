#include<graphics.h>
#include<iostream>
#include<windows.h>
#include<vector>
#include<string>
#include<cmath>
#include<conio.h>
#include"scene.h"
#include"menuScene.h"
#include"gameScene.h"
#include"sceneManager.h"
#include"util.h"
#include"map.h"
#include"map1.h"
#include"map2.h"
#include"mapManager.h"
#include"player.h"
#include"bullet.h"
#include"rebound.h"
using namespace std;


SceneManager scene_manager;
MapManager map_manager;

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;

Map* map1 = nullptr;
Map* map2 = nullptr;

vector<IMAGE> startGameButton(3);
vector<IMAGE> exitGameButton(3);
vector<IMAGE> mapChangeButton(2);
vector<IMAGE> gameMaps(2);
vector<IMAGE> shadow(2);
vector<IMAGE> arrow(2);
vector<IMAGE> spectral_arrow(2);
vector<IMAGE> firework(2);

vector<IMAGE> nut_run_left(3);
vector<IMAGE> nut_run_right(3);
vector<IMAGE> nut_die(2);

vector<IMAGE> bow_pulling_left(4);
vector<IMAGE> bow_pulling_right(4);
vector<IMAGE> crossbow_pulling_left(5);
vector<IMAGE> crossbow_pulling_right(5);
IMAGE GameMap;
IMAGE iron_door;
IMAGE signboard;
IMAGE P1;
IMAGE P2;



const int g = 3;
const int GameW = 1600;
const int GameH = 900;
const int startGameButtonW = 500;
const int startGameButtonH = 130;
const int exitGameButtonW = 500;
const int exitGameButtonH = 130;
const int mapChangeButtonW = 65;
const int mapChangeButtonH = 180;

int map_index = 0;

int bkg_x = -224;
int bkg_y = 0;
int bk_w = 2048;
int bk_h = 1440;

bool running = true;
bool gamerunning = false;
bool gameover = false;
bool gameRestart = false;



void loadOtherAnimation() {
	loadimage(&P1, L"img/1P_cursor.png", 100, 100);
	loadimage(&P2, L"img/2P_cursor.png", 100, 100);

	loadimage(&iron_door, L"img/iron_door.png",120,120);
	loadimage(&signboard, L"img/birch_sign.png",120,120);


	for (int i = 0;i < 5;i++) {
		wstring s1 = L"img/crossbow_pulling_" + to_wstring(i) + L".png";
		wstring s2 = L"img/crossbow_pulling_right_" + to_wstring(i) + L".png";
		loadimage(&crossbow_pulling_left[i], s1.c_str(),60,60);
		loadimage(&crossbow_pulling_right[i], s2.c_str(),60,60);
	}

	for (int i = 0;i < 4;i++) {
		wstring s1 = L"img/bow_pulling_" + to_wstring(i) + L".png";
		wstring s2 = L"img/bow_pulling_right_" + to_wstring(i) + L".png";
		loadimage(&bow_pulling_left[i], s1.c_str(),50,50);
		loadimage(&bow_pulling_right[i], s2.c_str(),50,50);
	}

	loadimage(&nut_die[0], L"img/nut_die_left.png");
	loadimage(&nut_die[1], L"img/nut_die_right.png");

	for (int i = 0;i < 3;i++) {
		wstring s1 = L"img/nut_run_left_" + to_wstring(i + 1) + L".png";
		wstring s2 = L"img/nut_run_right_" + to_wstring(i + 1) + L".png";
		loadimage(&nut_run_left[i], s1.c_str());
		loadimage(&nut_run_right[i], s2.c_str());
	}

	loadimage(&firework[0], L"img/firework_rocket.png",120,120);
	loadimage(&firework[1], L"img/firework_rocket_right.png",120,120);

	loadimage(&spectral_arrow[0], L"img/spectral_arrow.png",120,120);
	loadimage(&spectral_arrow[1], L"img/spectral_arrow_right.png",120,120);

	loadimage(&arrow[0], L"img/arrow.png",60,60);
	loadimage(&arrow[1], L"img/arrow_right.png",60,60);

	for (int i = 0;i < 2;i++) {
		wstring s = L"img/shadow_" + to_wstring(i + 1) + L".png";
		loadimage(&shadow[i], s.c_str());
	}

	for (int i = 0;i < 2;i++) {
		wstring s = L"img/map" + to_wstring(i + 1) + L"_bg.png";
		loadimage(&gameMaps[i], s.c_str(),GameW,GameH);
	}


	for (int i = 0;i < 3;i++) {
		wstring s1 = L"img/startGame_" + to_wstring(i + 1) + L".png";
		wstring s2 = L"img/exitGame_" + to_wstring(i + 1) + L".png";
		loadimage(&startGameButton[i], s1.c_str(), startGameButtonW, startGameButtonH);
		loadimage(&exitGameButton[i], s2.c_str(), exitGameButtonW, exitGameButtonH);
	}

	for (int i = 0;i < 2;i++) {
		wstring s = L"img/mapChange_" + to_wstring(i + 1) + L".png";
		loadimage(&mapChangeButton[i], s.c_str(), mapChangeButtonW, mapChangeButtonH);
	}
}

void Show(player& p) {
	if (p.choose == 1) {
		settextcolor(RED);
		settextstyle(40, 15, _T("Î¢ÈíÑÅºÚ"));
		wstring s = L"P1 HP£º" + to_wstring(p.HP);
		outtextxy(0, 0, s.c_str());
	}
	else if (p.choose == 2) {
		settextcolor(LIGHTBLUE);
		settextstyle(40, 15, _T("Î¢ÈíÑÅºÚ"));
		wstring s = L"P2 HP£º" + to_wstring(p.HP);
		outtextxy(GameW - 200, 0, s.c_str());
	}
}

void updateplayer(player& p, player& enemy) {
	p.Move();
	p.Rebound(enemy);
	p.Shot();
	p.Hurt(enemy);
	p.Live();
	p.Counttimer();
	p.Draw();
}


void updateGame(player& p1, player& p2) {
	updateplayer(p1, p2);
	updateplayer(p2, p1);

	updatebullet(p1.bullet_list);
	updatebullet(p2.bullet_list);

	map_manager.on_update(p1);
	map_manager.on_update(p2);
}

void ResetGame(player& p1, player& p2) {
	p1.Reset();
	p2.Reset();
}

int main() {

	initgraph(GameW, GameH);

	player p1(370, 400, 40, L"paimon", 1, 6);
	player p2(1225, 400, 46, L"nut_idle", 2, 3);
	loadOtherAnimation();

	ExMessage msg;
	menu_scene = new MenuScene();
	game_scene = new GameScene();

	map1 = new Map1();
	map2 = new Map2();

	setbkmode(TRANSPARENT);

	scene_manager.set_current_scene(menu_scene);
	map_manager.set_current_map(map1);

	BeginBatchDraw();
	while (running) {
		DWORD start_time = GetTickCount();
		if (gameRestart) {
			ResetGame(p1, p2);
			gameRestart = false;
		}

		while (peekmessage(&msg))
		{
			p1.processdeal(msg);
			p2.processdeal(msg);
			scene_manager.on_input(msg);
		}

		scene_manager.on_update();


		cleardevice();
		scene_manager.on_draw();
		if (gamerunning)updateGame(p1, p2);

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 60) {
			Sleep(1000 / 60 - delta_time);
		}
	}
	EndBatchDraw();

	return 0;
}