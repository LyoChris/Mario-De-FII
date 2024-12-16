#pragma once

struct pozitii {
	int ibegin, jbegin;
	int ifinal, jfinal;
};

struct ImageBuffer {
	void* data;
	int width, height;
};

void preloadImage(const char* filename, int width, void*& buffer);
void MapReaderandSetter();
void MapLoader();
void MapLoader2();
void MapLoaderNextRight();
void MapLoaderPrevLeft();