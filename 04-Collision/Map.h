#pragma once
#include "Textures.h"
#include "Sprites.h"
#define SCREEN_WIDTH	320//760
#define SCREEN_HEIGHT	 340//730


#define BLACKBOARDHEIGHT		72

class Map
{
	CSprites* tileMapSprite = CSprites::GetInstance();

	LPCWSTR mapFilePath;

	int ColumnMap, RowMap;	//So cot, hang cua map, Khoang cach voi day screen cua map

	int FrameWidthTexture, FrameHeightTexture;

	int idMap;

	int TileMap[200][200];
	//So cot va hang toi da phai lon hon Screen Resolution chia cho do cao/dai cua frame tile
	//So cot va hang toi da cua Map (thay doi tuy y, Castlevania khong qua lon nen 100 is ok)
public:
	Map();
	~Map();

	void LoadMap(int id,
		LPCWSTR mapFilePath,
		int RowMap,
		int ColumnMap,
		LPCWSTR mapFileTexture,
		int RowTile,
		int ColumnTile,
		int TileFrameWidth = 48,
		int TileFrameHeight = 48);

	void Load();
	//void Update(DWORD dt); co the se co map dung update
	void Draw();
};


