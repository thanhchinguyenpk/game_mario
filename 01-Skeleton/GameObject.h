#pragma once

#include <Windows.h>
#include <d3dx9.h>

class CGameObject
{
protected: 
	float x; // mỗi nhân vật đều có tọa độ của mình, đối tượng ẩn?
	float y;

	LPDIRECT3DTEXTURE9 texture;			
public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }

	CGameObject(LPCWSTR texturePath);
	virtual void Update(DWORD dt);
	void Render();
	~CGameObject();
};
typedef CGameObject * LPGAMEOBJECT;
// ủa dòng này là sao ta???
class CMario : public CGameObject
{
public: 
	CMario(LPCWSTR texturePath) :CGameObject(texturePath) {};
	void Update(DWORD dt);
};

class CbrickObject: public CGameObject
{
public:
	CbrickObject(LPCWSTR texturePath):CGameObject(texturePath) {};
	void Update(DWORD dt);

};