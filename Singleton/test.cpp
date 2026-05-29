#include <iostream>
#include <Windows.h>

#include "src/Singleton.hpp"

class Test1 : public Singleton<Test1>
{
	friend class Singleton<Test1>;

private:
	Test1() { std::cout << "Test1 constructor" << std::endl; }
	~Test1() { std::cout << "Test1 destructor" << std::endl; }
};

class Test2 : public Singleton<Test2>
{
	friend class Singleton<Test2>;
private:
	Test2() { std::cout << "Test2 constructor" << std::endl; }
	~Test2() { std::cout << "Test2 destructor" << std::endl; }
};

int main()
{
	// ƒƒ‚ƒŠƒŠ[ƒNŒŸo
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Test1::GetInstance();
	Test2::GetInstance();

	std::cout << std::endl;

	SingletonController::Release();

	system("pause");
	return 0;
}