#include "Mario.h"

void CMario::Update(DWORD dt)
{
	CGameObject::Update(dt);

	// simple fall down
	vy += MARIO_GRAVITY*dt*0.1; // sửa lại gắn đt vô nha? // mới sửa lại có thêm *dt*0.1 á
	if (y > 100) 
	{
		vy = 0; y = 100.0f; // nếu nó đụng sàn rồi thì không cho nó rớt xuống nữa?
		// hệ trục y hướng xuống, chú ý nha
	}

	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290; // cho mario đi qua đi lại không vượt ra cửa sổ
	if (vx < 0 && x < 0) x = 0;// cho mario đi qua đi lại không vượt ra cửa sổ
}

void CMario::Render()
{
	int ani;
	if (vx == 0) // đứng yên
	{
		if (nx>0) ani = MARIO_ANI_IDLE_RIGHT;// biết mặt nó bên nào để render cho đúng
		else ani = MARIO_ANI_IDLE_LEFT;
	}
	else if (vx > 0) 
		ani = MARIO_ANI_WALKING_RIGHT; 
	else ani = MARIO_ANI_WALKING_LEFT;

	animations[ani]->Render(x, y);
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);// chỉ là một con số
	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1; // hướng cái mặt qua bên tay phải
		break;
	case MARIO_STATE_WALKING_LEFT: 
		vx = -MARIO_WALKING_SPEED;
		nx = -1;// vector pháp tuyến qua bên tay trái
		// cần vector pháp tuyến để biết khi mario đứng yên mặt của nó hướng qua trái hay hướng qua phải
		break;
	case MARIO_STATE_JUMP: 
		if (y==100) // nếu như mario ở trạng thái nhảy vẫn còn đang ở mặt đất
			vy = -MARIO_JUMP_SPEED_Y;//  thì ta cho nó một lực nhảy ban đầu
		// sau này do trạng thái update của gia tốc thì vận tốc của nó giảm xuống từ từ tạo cảm giác mario
		// đang nhảy
		break;
	case MARIO_STATE_IDLE: // nếu ở trạng thái đứng yên
		vx = 0;
		break;
		// và không thay đổi giá trị vector pháp tuyến để biết mặt mario đang hướng về bên nào
		//để mà render cho đúng
	}
}

void CConCo::Update(DWORD dt)
{
	CGameObject::Update(dt);

	// simple fall down
	vy += CONCO_GRAVITY * dt * 0.1; // sửa lại gắn đt vô nha? // mới sửa lại có thêm *dt*0.1 á
	if (y > 100)
	{
		vy = 0; y = 100.0f; // nếu nó đụng sàn rồi thì không cho nó rớt xuống nữa?
		// hệ trục y hướng xuống, chú ý nha
	}

	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290; // cho mario đi qua đi lại không vượt ra cửa sổ
	if (vx < 0 && x < 0) x = 0;// cho mario đi qua đi lại không vượt ra cửa sổ
}

void CConCo::Render()
{
	int ani;
	if (vx == 0) // đứng yên
	{
		if (nx > 0) ani = CONCO_ANI_IDLE_RIGHT;// biết mặt nó bên nào để render cho đúng
		else ani = CONCO_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = CONCO_ANI_WALKING_RIGHT;
	else ani = CONCO_ANI_WALKING_LEFT;

	animations[ani]->Render(x, y);
}

void CConCo::SetState(int state)
{
	CGameObject::SetState(state);// chỉ là một con số
	switch (state)
	{
	case CONCO_STATE_WALKING_RIGHT:
		vx = CONCO_WALKING_SPEED;
		nx = 1; // hướng cái mặt qua bên tay phải
		break;
	case CONCO_STATE_WALKING_LEFT:
		vx = -CONCO_WALKING_SPEED;
		nx = -1;// vector pháp tuyến qua bên tay trái
		// cần vector pháp tuyến để biết khi mario đứng yên mặt của nó hướng qua trái hay hướng qua phải
		break;
	case CONCO_STATE_JUMP:
		if (y == 100) // nếu như mario ở trạng thái nhảy vẫn còn đang ở mặt đất
			vy = -CONCO_JUMP_SPEED_Y;//  thì ta cho nó một lực nhảy ban đầu
		// sau này do trạng thái update của gia tốc thì vận tốc của nó giảm xuống từ từ tạo cảm giác mario
		// đang nhảy
		break;
	case CONCO_STATE_IDLE: // nếu ở trạng thái đứng yên
		vx = 0;
		break;
		// và không thay đổi giá trị vector pháp tuyến để biết mặt mario đang hướng về bên nào
		//để mà render cho đúng
	}
}
