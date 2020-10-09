#pragma once
#include <unordered_map>
#include <d3dx9.h>

using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	static CTextures * __instance;

	unordered_map<int, LPDIRECT3DTEXTURE9> textures;
	//cấu trúc từ điển, lưu trữ tất cả các texture
    // cách tiếp cận bạn kia là lưu trữ các textture khác nhau cho các đối tượng khác nhau
	// cái mảng này là duy nhất các tất cả các texture có trong game

public: 
	CTextures();
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	// chẳng qua à gọi lại hàm trong game object
	LPDIRECT3DTEXTURE9 Get(unsigned int i);
	// để lấy texture thì ta truyền vào id của texture tương ứng. một điểm có thể cải tiến: nếu như ta
	//load texture lên rồi mà ta gọi lệnh add thì nó không làm gì hết
	// nhớ là đây là lớp lưu trữ tất cả các texture có trong game của mình luôn
	// có thể hiểu đây là toàn bộ BD các textture có trong game

	static CTextures * GetInstance();
};