#pragma once

void drawText(const int x, const int y, const char *text)
{
	Rect r;
	r.x = x; r.y = y;
	SDL_Surface *surface = TTF_RenderText_Solid(gfx.font, text, gfx.fontColor);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(gfx.renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
	SDL_RenderCopy(gfx.renderer, texture, NULL, &r);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

Coord drawTextCoord(const Coord pos, const char *text)
{
	Rect r;
	r.x = pos.x; r.y = pos.y;
	SDL_Surface *surface = TTF_RenderText_Solid(gfx.font, text, gfx.fontColor);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(gfx.renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
	SDL_RenderCopy(gfx.renderer, texture, NULL, &r);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	return (const Coord){pos.x+r.w, pos.y};
}

void drawTextCentered(const int x, const int y, const char *text)
{
	Rect r;
	r.x = x; r.y = y;
	SDL_Surface *surface = TTF_RenderText_Solid(gfx.font, text, gfx.fontColor);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(gfx.renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
	r.x-=r.w/2;
	r.y-=r.h/2;
	SDL_RenderCopy(gfx.renderer, texture, NULL, &r);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

static inline
void drawTextCenteredCoord(const Coord pos, const char *text)
{
	drawTextCentered(pos.x, pos.y, text);
}

static inline
Length getTextLength(const char *text)
{
	Length len = {0};
	TTF_SizeText(gfx.font, text, &len.x, &len.y);
	return len;
}

static inline
int getTextXLen(const char *text)
{
	Length len = {0};
	TTF_SizeText(gfx.font, text, &len.x, &len.y);
	return len.x;
}

static inline
int getTextYLen(const char *text)
{
	Length len = {0};
	TTF_SizeText(gfx.font, text, &len.x, &len.y);
	return len.y;
}

Coord* spanTextListCoords(Coord *coords, const Coord start, const Coord stop, const uint num, const char **textList)
{
	if(num == 0 || coords == NULL)
		return coords;
	const Length step = coordDiv(coordSub(stop, start), num>1?num-1:1);
	for(uint i = 0; i < num; i++)
		coords[i] = coordOffset(start, coordMul(step, i));
	return coords;
}

Coord* spanTextListCoordsCentered(Coord *coords, const Coord start, const Coord stop, const uint num, const char **textList)
{
	if(num == 0 || coords == NULL)
		return coords;
	const Length step = coordDiv(coordSub(stop, start), num+1);
	for(uint i = 1; i < num+1; i++)
		coords[i-1] = coordOffset(start, coordMul(step, i));
	return coords;
}

Rect* getTextListRect(Rect *const rect, const Coord start, const Coord stop, const uint num, const char **textList)
{
	if(num == 0 || rect == NULL)
		return rect;

	const Length step = coordDiv(coordSub(stop, start), num>1?num-1:1);
	for(uint i = 0; i < num; i++){
		const Length len = getTextLength(textList[i]);
		const Coord pos = coordSub(
			coordOffset(start, coordMul(step, i)),
			coordDiv(len,2)
		);
		rect[i].x = pos.x;
		rect[i].y = pos.y;
		rect[i].w = len.x;
		rect[i].h = len.y;
	}
	return rect;
}

Rect* getTextListRectCentered(Rect *const rect, const Coord start, const Coord stop, const uint num, const char **textList)
{
	if(num == 0 || rect == NULL)
		return rect;

	const Length step = coordDiv(coordSub(stop, start), num+1);
	for(uint i = 1; i < num+1; i++){
		const Length len = getTextLength(textList[i-1]);
		const Coord pos = coordSub(
			coordOffset(start, coordMul(step, i)),
			coordDiv(len,2)
		);
		rect[i-1].x = pos.x;
		rect[i-1].y = pos.y;
		rect[i-1].w = len.x;
		rect[i-1].h = len.y;
	}
	return rect;
}

int coordInRectList(const Coord coord, Rect *const rect, const int num)
{
	if(num < 1)
		return -1;
	for(int i = 0; i < num; i++)
		if(coordInRect(coord, rect[i]))
			return i;
	return -1;
}

// draws a collection of strings evenly spaced between 2 points
void spanTextList(const Coord start, const Coord stop, const uint num, const char **textList)
{
	if(num == 0)
		return;
	const Length step = coordDiv(coordSub(stop, start), num>1?num-1:1);
	for(uint i = 0; i < num; i++){
		drawTextCenteredCoord(coordOffset(start, coordMul(step, i)), textList[i]);
	}
}

void spanTextListCentered(const Coord start, const Coord stop, const uint num, const char **textList)
{
	if(num == 0)
		return;
	const Length step = coordDiv(coordSub(stop, start), num+1);
	for(uint i = 1; i < num+1; i++){
		drawTextCenteredCoord(coordOffset(start, coordMul(step, i)), textList[i-1]);
	}
}

void setTextSize(const uint size)
{
	if(size == gfx.fontSize)
		return;
	if(gfx.font != NULL)
		TTF_CloseFont(gfx.font);
	gfx.fontSize = size;
	gfx.font = TTF_OpenFont("./FiraCode-Medium.ttf", gfx.fontSize);
}

int getTextSize(void)
{
	return gfx.fontSize;
}

void setTextColor(const Color c)
{
	gfx.fontColor = c;
}

Color getTextColor(void)
{
	return gfx.fontColor;
}

void text_quit(void)
{
	if(gfx.font != NULL){
		TTF_CloseFont(gfx.font);
	}
	TTF_Quit();
}

void text_init(void)
{
	if(TTF_Init()){
		printf("SDL_ttf borked! Error: %s\n", TTF_GetError());
		exit(0);

	}
	gfx.fontColor = WHITE;
	setTextSize(32);
	if(!gfx.font){
		printf("Unable to open font or set font size! Error: %s\n", TTF_GetError());
		exit(0);
	}
	printf("Adding text_quit to atexit()\n");
	atexit(text_quit);
}
