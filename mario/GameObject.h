#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Game.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL)
	{ this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:

	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	//float acceleration =0.001;

	int nx = 1;	
	int ny = 1;

	int state;

	bool used = false;

	DWORD dt; 

	vector<LPANIMATION> animations;

public: 
	bool CheckOverLap(float l_a, float t_a, float r_a, float b_a, float l_b, float t_b, float r_b, float b_b){ return (l_a < r_b && r_a > l_b && t_a < b_b && b_a > t_b); }
	void DeleteWhenOutOfCam();																											//return (l_a < r_b&& r_a > l_b && t_a < b_b&& b_a > t_b);	
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	float GetX(){ return this->x; }
	float GetY(){ return this->y; }
	int GetNX() { return this->nx; }
	int GetState() { return this->state; }

	void RenderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);// hai đối tượng di chuyển trả về sk đối tượng va chạm
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	// kiểm tra đối tượng với một danh sách các đối tượng và kq và danh sách các sự kiện va chạm.
	// một sự kiện va chạm gồm một bộ ba: t(cho biết có va chạm hay không), vector pháp tuyến để biết 
	//hướng va chạm , con trỏ đến đối tượng mà có khả năng va chạm với mình
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);// trả về đụng độ gần nhất trên chiều x và chiều y

	void AddAnimation(int aniId);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	

	virtual ~CGameObject();
};

