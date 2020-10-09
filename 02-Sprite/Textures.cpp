#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "textures.h"

CTextures * CTextures::__instance = NULL;

CTextures::CTextures()
{

}

CTextures *CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}

void CTextures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	textures[id] = CGame::GetInstance()->LoadTexture(filePath);
	// khi truyền một texture vào thì có một định danh
	// cái id là do ta tự chọn nó giống như là cái tắt, ví dụ như ok đậy là textture của mario, đây là của
	//cumbar, đơn giản một id texture là một file hình lớn. tham số thì có thêm màu transparent, các bài sau 
	//sẽ sửa cách dùng transparent
}

LPDIRECT3DTEXTURE9 CTextures::Get(unsigned int i) 
{
	return textures[i];
}



