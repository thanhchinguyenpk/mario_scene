#include "Map.h"
//#include "debug.h"
#include <iostream>
#include <fstream>
#include "Game.h"
#include "debug.h"
#include "Utils.h"


Map::Map() {}

Map::~Map() {}

void Map::LoadMap(int id,
	LPCWSTR mapFilePath,
	int RowMap,
	int ColumnMap,
	LPCWSTR mapFileTexture,
	int RowTile,
	int ColumnTile,
	int TileFrameWidth,
	int TileFrameHeight)
{
	this->idMap = id;
	this->mapFilePath = mapFilePath;
	this->RowMap = RowMap;
	this->ColumnMap = ColumnMap;

	CTextures* mapTexture = CTextures::GetInstance();
	mapTexture->Add(idMap, mapFileTexture, D3DCOLOR_XRGB(255, 255, 0));
	LPDIRECT3DTEXTURE9 tex = mapTexture->Get(idMap);

	int TilesetRow = RowTile;
	int TilesetColumn = ColumnTile;

	FrameWidthTexture = TileFrameWidth;
	FrameHeightTexture = TileFrameHeight;

	int idSpriteIns = 1;
	for (UINT i = 0; i < TilesetRow; i++)
	{
		for (UINT j = 0; j < TilesetColumn; j++)
		{
			int idSprite = idMap + idSpriteIns;
			//tileMapSprite->Add(idSprite, FrameWidthTexture * j, FrameHeightTexture * i, FrameWidthTexture * (j + 1), FrameHeightTexture * (i + 1), tex);
			tileMapSprite->Add(idSprite, FrameWidthTexture * j, FrameHeightTexture * i, 48, 48, tex);
			idSpriteIns++;
		}
	}

	Load();
}

void Map::InitMap(int row, int column)
{
	DebugOut(L"[INFO] Start init map.  \n");


	int const row_const = row;
	int const column_const = column;

	 int **TileMapArray2D = new int* [row_const];

	for (int i = 0; i < row_const; ++i)
	{
		TileMapArray2D[i] = new int[column_const];
	}


	DebugOut(L"[INFO] Finish init map. \n");
}

void Map::FreeMap(int row, int column)
{
	DebugOut(L"[INFO] Start delete map. \n");

	//Free each sub-array
	for (int i = 0; i < row; ++i) {
		//delete[] TileMapArray2D[i];
	}

	//Free the array of pointers
	//delete[] TileMapArray2D;


	DebugOut(L"[INFO] Finish delete map. \n");
}

void Map::Load()
{
	InitMap(RowMap, ColumnMap);

	DebugOut(L"[INFO] Start loading map resources from : %s \n", mapFilePath);

	ifstream f(mapFilePath, ios::in);

	for (int i = 0; i < RowMap; i++)
	{
		for (int j = 0; j < ColumnMap; j++)
		{
			f >> TileMapArray2D[i][j];
			//DebugOut(L"vi tri do la$$$$$$$$$$$$$$$$$$$: %d\n", TileMapArray2D[i][j]);
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading map resources %s\n", mapFilePath);
	DebugOut(L"vi tri do la ^^^^^^^^^^^^^^^^^^: %d\n", RowMap);
	DebugOut(L"vi tri do la ^^^^^^^^^^^^^^^^^^: %d\n", ColumnMap);
	//for (int j = 0; j < ColumnMap; j++)
	//{
	//	DebugOut(L"vi tri do la $$$$$$$$$$$$: %d\n", TileMapArray2D[41 - 1][j]);
		//f >> TileMap[Rowmap-1][j];
	//}

	//for (int j = 0; j < ColumnMap; j++)
	//{
	//	DebugOut(L"vi tri do la$$$$$$$$$$$$$$$$$$$: %d\n", TileMapArray2D[41 - 2][j]);
		//f >> TileMap[Rowmap-1][j];
	//}
	

}

void Map::Draw()
{
	/*//int RowScreen = SCREEN_HEIGHT / FrameHeightTexture;
	int RowScreen = 41;

	//Tinh trong tam ve la tu tam nen posX, posY co bien doi toa do ve tam
	float originX = FrameWidthTexture / 2;
	float originY = FrameHeightTexture / 2;

	//Cot dau tien cua tile, camera de duy tri tinh thuc te' trong game 
	//camera o dau game co pos = 0, di chuyen theo truc ngang thi cameraPosX thay doi se tang firstCol theo frame tilemap mong muon
	//int firstColumn = (int)Camera::GetInstance()->GetCamPosX() / FrameWidthTexture;
	//int lastColumn = firstColumn + SCREEN_WIDTH / FrameWidthTexture;
	int lastColumn = 176;

	for (UINT i = 0; i < RowScreen; i++)	//chay tung totalRow tu tren xuong
	{
		for (UINT j = 0; j <= lastColumn; j++)	//chay tung totalColumn tu trai qua
		{
			//pos cua 1 vien tile
			//FrameWidth * (j - firstCol) de xac dinh vien tile can ve~ trong file tileset.text
			//CameraPosX de dat vi tri camera o ngay giua 
			//Do lech CameraPosX % FrameWidth de tinh so du cua phan thua` phia sau tung tile 
			//(vi firstCol la int nen se co 1 doan du* o giua thisColumn va nextColumn, day la de can bang dieu do)
			float tileMapPosX = (i+j)* FrameWidthTexture ;
			float tileMapPosY = (float)FrameHeightTexture * (i+j) ;

			tileMapSprite->Get(TileMap[i][j] + idMap)->Draw( tileMapPosX, tileMapPosY);
		}
	}

	tileMapSprite->Get(TileMap[0][0] + idMap)->Draw(0, 0);
	tileMapSprite->Get(TileMap[0][2] + idMap)->Draw(50, 0);
	tileMapSprite->Get(TileMap[0][3] + idMap)->Draw(100, 0);
	tileMapSprite->Get(TileMap[0][4] + idMap)->Draw(150, 0);

	tileMapSprite->Get(TileMap[0][5] + idMap)->Draw(200, 0);
	tileMapSprite->Get(TileMap[0][6] + idMap)->Draw(250, 0);
	tileMapSprite->Get(TileMap[0][7] + idMap)->Draw(300, 0);

	tileMapSprite->Get(TileMap[0][8] + idMap)->Draw(350, 0);
	tileMapSprite->Get(TileMap[0][9] + idMap)->Draw(400, 0);
	tileMapSprite->Get(TileMap[0][10] + idMap)->Draw(450, 0);*/


	/*
	int RowScreen = SCREEN_HEIGHT / FrameHeightTexture;

	//Tinh trong tam ve la tu tam nen posX, posY co bien doi toa do ve tam
	float originX = FrameWidthTexture / 2;
	float originY = FrameHeightTexture / 2;

	//Cot dau tien cua tile, camera de duy tri tinh thuc te' trong game 
	//camera o dau game co pos = 0, di chuyen theo truc ngang thi cameraPosX thay doi se tang firstCol theo frame tilemap mong muon
	int firstColumn = (int)CGame::GetInstance()->GetCamX() / FrameWidthTexture;
	int lastColumn = firstColumn + SCREEN_WIDTH / FrameWidthTexture;

	for (UINT i = 15; i < RowScreen; i++)	//chay tung totalRow tu tren xuong
	{
		for (UINT j = firstColumn; j <= lastColumn; j++)	//chay tung totalColumn tu trai qua
		{
			//pos cua 1 vien tile
			//FrameWidth * (j - firstCol) de xac dinh vien tile can ve~ trong file tileset.text
			//CameraPosX de dat vi tri camera o ngay giua 
			//Do lech CameraPosX % FrameWidth de tinh so du cua phan thua` phia sau tung tile 
			//(vi firstCol la int nen se co 1 doan du* o giua thisColumn va nextColumn, day la de can bang dieu do)
			float tileMapPosX = (float)FrameWidthTexture * (j - firstColumn) + CGame::GetInstance()->GetCamX() - (float)((int)CGame::GetInstance()->GetCamX() % FrameWidthTexture) + originX;
			float tileMapPosY = (float)FrameHeightTexture * i  + originY;
			if (TileMap[i][j] == 0)
				continue;
			tileMapSprite->Get(TileMap[i][j] + idMap)->Draw(tileMapPosX, tileMapPosY);
		}
	}
	*/

	
	// get width height of tile
	//int w = CTiles::GetInstance()->GetFrameWidth();
	int w = 48;
	//int h = CTiles::GetInstance()->GetFrameHeight();
	int h = 48;
	CGame::GetInstance()->GetCamX();
	int begin_row = CGame::GetInstance()->GetCamY() / h;
	int end_row = (CGame::GetInstance()->GetCamY() + SCREEN_HEIGHT) / h + 1;

	int begin_column = CGame::GetInstance()->GetCamX() / w;
	int end_column = (CGame::GetInstance()->GetCamX() + SCREEN_WIDTH) / w + 1;

	/*if (end_column > 176)
		end_column = 176;
	if (end_row > 41)
		end_row = 41;*/

	if (begin_column < 0) begin_column = 0;
	if (begin_row < 0) begin_row = 0;

	int x = 15;

	//vector<LPSPRITE> tiles = CTiles::GetInstance()->GetTiles();
	for (int i = begin_row; i < end_row + x; i++) {
		for (int j = begin_column; j < end_column; j++) {
			if (TileMapArray2D[i][j] != 0) {
				tileMapSprite->Get(TileMapArray2D[i][j])->Draw(j*w, i*h, 255);
			}
		}
	}
}