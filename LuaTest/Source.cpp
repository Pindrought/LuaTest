#include <iostream>
#include <string>
#include <lua.hpp>

static int FunctionTest(lua_State* L)
{
	int numArgs = lua_gettop(L);
	if (numArgs != 0)
	{
		std::string err = "[FunctionTest] expects 0 arguments. Function was called with [";
		err += std::to_string(numArgs) + "] arguments. Expected prototype FunctionTest().";
		const char* cstr = err.c_str();
		return luaL_error(L, cstr);
	}
	return 0;
}

int main()
{
	lua_State* L = luaL_newstate();
	if (L != NULL)
	{
		lua_pushcfunction(L, FunctionTest);
		lua_setglobal(L, "FunctionTest");
		int result = luaL_dofile(L, "script.lua");
		if (result != 0)
		{
			const char * error = lua_tostring(L, -1);
			std::cout << error << std::endl;
		}
		lua_close(L);
	}

	return 0;
}