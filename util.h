#pragma once

#include<graphics.h>
#include<cmath>
#include<string>
#include<iostream>
#include"player.h"

class player;

inline void flip_image(IMAGE* src, IMAGE* dst) {
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx_src = y * w + x;
			int idx_dst = y * w + (w - x - 1);
			dst_buffer[idx_dst] = src_buffer[idx_src];
		}
	}
}

#pragma comment(lib,"MSIMG32.LIB")
inline void Alpha_putimage(int x, int y, IMAGE img, unsigned char alpha = 255) {
	int w = img.getwidth();
	int h = img.getheight();
	AlphaBlend(GetImageHDC(), x, y, w, h, GetImageHDC(&img), 0, 0, w, h, { AC_SRC_OVER,0,alpha,AC_SRC_ALPHA });
}

inline double distance(int x1, int y1, int x2, int y2) {
	double d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return d;
}

void CollisionBoxDetction(player& p, const int& bx, const int& by, const int& bw, const int& bh);

