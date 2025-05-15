#include "player.h"
#include "rebound.h"
#include <string>
#include <cmath>




player::player(int x1, int y1, int r1, std::wstring s1, int choose1, int player_idx)
	: player_left(6), player_right(6), player_pic_idx(player_left[0]),
	x(x1), y(y1), location_r(r1), choose(choose1), temp_x(x1), temp_y(y1), player_idx(player_idx) {
	loadAnimation(s1);
	reb = new rebound();
}

player::~player() {
	delete reb;
	reb = nullptr;
}

void player::loadAnimation(std::wstring s) {
	for (int i = 0; i < player_idx; i++) {
		std::wstring path_left = L"img/" + s + L"_left_" + std::to_wstring(i) + L".png";
		std::wstring path_right = L"img/" + s + L"_right_" + std::to_wstring(i) + L".png";
		loadimage(&player_left[i], path_left.c_str());
		loadimage(&player_right[i], path_right.c_str());
	}
}

void player::processdeal(ExMessage m) {
	if (choose == 1) {
		if (m.message == WM_KEYDOWN) {
			switch (m.vkcode) {
			case'A':leftwalk = true;break;
			case'D':rightwalk = true;break;
			case'W':jumpwalk = true;break;
			case'S':downwalk = true;break;
			case'G':bullet_shot_timer++;break;
			case'H':if (!reb->timer)reb->timer = 1;reb->parryCooldown();break;
			}
		}
		if (m.message == WM_KEYUP) {
			switch (m.vkcode) {
			case'A':leftwalk = false;break;
			case'D':rightwalk = false;break;
			case'W':jumpwalk = false;singlejump = true;break;
			case'S':downwalk = false;break;
			case'G':single_b_s = true;break;
			}
		}
	}
	else if (choose == 2) {
		if (m.message == WM_KEYDOWN) {
			switch (m.vkcode) {
			case VK_LEFT:leftwalk = true;break;
			case VK_RIGHT:rightwalk = true;break;
			case VK_UP:jumpwalk = true;break;
			case VK_DOWN:downwalk = true;break;
			case'M':bullet_shot_timer++;break;
			case'N':if (!reb->timer)reb->timer = 1;reb->parryCooldown();break;
			}
		}
		if (m.message == WM_KEYUP) {
			switch (m.vkcode) {
			case VK_LEFT:leftwalk = false; break;
			case VK_RIGHT:rightwalk = false;break;
			case VK_UP:jumpwalk = false;singlejump = true;break;
			case VK_DOWN:downwalk = false;break;
			case'M':single_b_s = true;break;
			}
		}
	}
	if (bullet_shot_timer)bullet_shot_timer++;//蓄力时间
	if (reb->timer)reb->timer++;

}

void player::Move() {
	if (leftwalk) {
		vx -= speed;
	}
	if (rightwalk) {
		vx += speed;
	}
	if (jumpwalk && jumpfreq && singlejump) {
		vy = -jumpspeed;
		jumpfreq--;
		jumpwalk = false;
		singlejump = false;
	}
	if (downwalk) {
		vy = 1;
	}

	//移动
	y += vy;
	x += vx;

	//转向
	if (vx > 0) {
		vx--;
		player_p = false;
	}
	else if (vx < 0) {
		vx++;
		player_p = true;
	}
	if (player_p) { player_pic_idx = player_left[current_idx]; }
	else { player_pic_idx = player_right[current_idx]; }

	if (abs(vx) > maxSpeed) {
		vx = vx > 0 ? maxSpeed : -maxSpeed;
	}
}

void player::Shot() {
	if (bullet_shot_timer > 0 && single_b_s) {
		shotbullet(x, y, player_p, choose, bullet_shot_timer, bullet_list);
		single_b_s = false;
		bullet_shot_timer = 0;
	}

	if (bullet_shot_timer >= plus_time) { ifplusattack = true; }
}

void player::Rebound(player& enemy) {
	if (goldtimer)reb->isParrying = true;
	if (!reb->isParrying) { return; }
	reb->parryDuration--;
	if (reb->parryDuration < 0) {
		reb->isParrying = false;
		reb->parryDuration = 10;
	}


	for (auto& b : enemy.bullet_list) {
		if (b.isPlusShot) {
			reb->check(*this, b);
			reb->bullet_rebound(b);

			if (reb->canParrying) {
				this->bullet_list.push_back(b);
				swap(b, enemy.bullet_list.back());
				enemy.bullet_list.pop_back();
			}
		}
	}
}

void player::Hurt(player& enemy) {
	for (auto& b : enemy.bullet_list) {
		if (b.isPlusShot) {
			if (distance(b.b_x, b.b_y, x, y) < b.plus_b_r + r) {
				HP -= 5;
				vx += b.getdir() ? -PlusRepelSpeed : PlusRepelSpeed;
				swap(b, enemy.bullet_list.back());
				enemy.bullet_list.pop_back();
			}
		}
		else {
			if (distance(b.b_x, b.b_y, x, y) < b.b_r + r) {
				HP--;
				x += b.getdir() ? -repelamount : repelamount;
				swap(b, enemy.bullet_list.back());
				enemy.bullet_list.pop_back();
			}
		}
	}
}

void player::Live() {
	if (HP <= 0) {
		isDeath = true;
		gameover = true;
	}
	if (y > GameH + 300) {
		HP = 0;
		isDeath = true;
		gameover = true;
	}
}

void player::Counttimer() {
	if (counter++ == 3)current_idx++;
	counter %= 4;
	current_idx %= player_idx;
}

void player::Draw() {
	Show(*this);

	if (enter_player_cursor_timer) {
		enter_player_cursor_timer--;
		if (choose == 1) {
			Alpha_putimage(x-location_r-10, y - location_r-100, P1);
		}else if (choose == 2) {
			Alpha_putimage(x-location_r-10, y - location_r - 100, P2);
		}
	}

	if (choose == 2 && vx != 0) {
		if (vx > 0) {
			Alpha_putimage(x - location_r, y - location_r, nut_run_right[current_idx]);
		}
		else if (vx < 0) {
			Alpha_putimage(x - location_r, y - location_r, nut_run_left[current_idx]);
		}
	}
	else {
		Alpha_putimage(x - location_r, y - location_r, player_pic_idx);
	}
	setfillcolor(WHITE);
	circle(x, y, r);

	if (bullet_shot_timer == 0) {
		weaponState_idx = 0;
	}
	else if (bullet_shot_timer > 0&&bullet_shot_timer<=6) {
		weaponState_idx = 1;
	}
	else if (bullet_shot_timer > 6 && bullet_shot_timer <= 12) {
		weaponState_idx = 2;
	}
	else if (bullet_shot_timer > 12&&bullet_shot_timer<20) {
		weaponState_idx = 3;
	}
	else {
		if (choose == 2) {
			weaponState_idx = 4;
		}
		else if (choose == 1) {

		}
	}

	if (choose == 1) {
		if (player_p) {
			Alpha_putimage(x - location_r-20 , y-20 , bow_pulling_left[weaponState_idx]);
		}
		else {
			Alpha_putimage(x - location_r + 40, y-20 , bow_pulling_right[weaponState_idx]);
		}

	}
	else if (choose == 2) {
		if (player_p) {
			Alpha_putimage(x - location_r-10 , y-20 , crossbow_pulling_left[weaponState_idx]);
		}
		else {
			Alpha_putimage(x - location_r + 50, y-20 , crossbow_pulling_right[weaponState_idx]);
		}
	}

	if (ifplusattack) {
		//setfillcolor(BLUE);
		//solidrectangle(x - r / 2, y - r / 2, x + r / 2, y + r / 2);
		ifplusattack = false;
	}

	if (reb->isParrying) {
		if (choose == 1) {
			if (player_p) {
				Alpha_putimage(x - location_r- 60, y - location_r-10, signboard);
			}
			else {
				Alpha_putimage(x - location_r + 40, y - location_r - 10, signboard);
			}
		}
		else if (choose == 2) {
			if (player_p) {
				Alpha_putimage(x - location_r - 60, y - location_r - 20, iron_door);
			}
			else {
				Alpha_putimage(x - location_r + 40, y - location_r - 20, iron_door);
			}
		}
	}

	if (reb->canParrying || goldtimer) {
		if (reb->canParrying) {
			goldtimer = 100;
			reb->canParrying = false;
		}
		setfillcolor(RGB(255, 215, 0));
		solidcircle(x, y, 2 * r);
		goldtimer--;
	}

	if (isDeath) {
		settextcolor(RGB(255, 215, 0));
		settextstyle(250, 100, _T("微软雅黑"));
		wstring s = L"玩家" + to_wstring(choose) + L"失败";
		outtextxy(GameW / 2 - 500, GameH / 2 - 300, s.c_str());
		settextcolor(BLACK);
		settextstyle(80, 50, _T("微软雅黑"));
		outtextxy(GameW / 2 - 800, GameH / 2 + 250, L"按‘E’键返回菜单");
		outtextxy(GameW / 2 + 50, GameH / 2 + 250, L"按‘Q’键退出游戏");
	}
}

void player::Reset() {
	x = temp_x;
	y = temp_y;
	vx = vy = 0;
	jumpfreq = 2;
	HP = PlayerHP;
	bullet_list.clear();
	reb->Reset();

	isDeath = false;
	bullet_shot_timer = 0;
	player_p = true;

	singlejump = true;

	jumpwalk = false;
	downwalk = false;
	rightwalk = false;
	leftwalk = false;

	single_b_s = false;
	single_reb = false;

	ifplusattack = false;

	enter_player_cursor_timer = enter_player_cursor_delay;
}

