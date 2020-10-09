#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left; 
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public: 
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	//hàm khởi tạo này chỉ việc truyền hết tham số thôi
	void Draw(float x, float y);
	// gọi lại làm draw trong lớp tiện ích Cgame.
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;
	//một cái mảng có key, id của từng sprite nó cho mình trỏ ra từng đối tượng của sprite
	//và ta có thể add từng sprite tương ứng với texture của nó

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	// l t r b là vị trí của sprite đó bên trong texture cụ thể, texture trỏ đến texture bên trong texture 
	//DB của mình
	LPSPRITE Get(int id);

	static CSprites * GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;// sprite nào để vẽ
	DWORD time;// tính bằng minilisecon// thời gian để hiển thị cái frame đó trên màn hình cho đến khi hết thì mình nhảy qua
	//frame khác
	// đa phần các trường hợp thì frame giống nhau, tuy nhiên có một vài chuyển động khác nhau
	// 1 animationFrame chỉ đơn giản là một sprite	

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation //1 animation gắn với trạng thái của một nhân vật
{
	// mario đi qua tay trái thì có animation đi qua tay trái, qua phải thì có animation đi qua phải
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;// kiểm soát frame bằng cách có frame hiện tại, mới load lên có giá trị -1
	vector<LPANIMATION_FRAME> frames;// 1 animation có n frame
	// trường hợp mario qua tay phải thì có 3 frame
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y);
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;// một DB có tất cả các animation trên toàn bộ game của 
	//tất cả các đối tượng luôn, hàm add vô hơi khác xíu bên kia


public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations * GetInstance();
};

