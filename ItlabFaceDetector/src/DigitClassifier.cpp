#include "DigitClassifier.hpp"
#include <iostream>

using namespace cv;
using namespace std;

DigitClassifier::DigitClassifier()
{
    L = lua_open();
    luaL_openlibs(L);

    const char *filename = "/scripts/file.lua";
    int s = luaL_dofile (L, filename);
    if (s != 0) reportLuaErrors(L, s);

    lua_getglobal(L, "loadNetModel");
    lua_pushstring(L, "/net/CNN.net");
    s = lua_pcall(L, 1, 0, 0);
    if (s != 0) reportLuaErrors(L, s);
}

DigitClassifier::~DigitClassifier()
{
    lua_close(L);
}

void DigitClassifier::reportLuaErrors(lua_State *L, int status)
{
    if ( status!=0 ) 
    {
        cerr << "-- " << lua_tostring(L, -1) << endl;
        lua_pop(L, 1);
    }
}

Result DigitClassifier::Classify(Mat& img) 
{    
    lua_getglobal(L, "predict");
    // Push data
    lua_newtable(L);
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            lua_pushinteger(L, i * img.cols + j + 1);
            lua_pushinteger(L, img.at<uchar>(i, j));
            lua_settable(L, -3);
        }
    }
    //call function
    int s = lua_pcall(L, 1, 2, 0);
    if (s != 0) reportLuaErrors(L, s);

    Result result;
    while (lua_gettop(L)) {
        result.confidence = lua_tonumber(L, -1);
    	lua_pop(L, 1);
        result.label =  lua_tointeger(L, -1);
        lua_pop(L, 1);
    }

	return result;
}
