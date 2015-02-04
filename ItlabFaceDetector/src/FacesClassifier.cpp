#include "FacesClassifier.hpp"
#include <iostream>

using namespace cv;
using namespace std;

FacesClassifier::FacesClassifier()
{
    L = lua_open();
    luaL_openlibs(L);

    const char *filename = "../scripts/faces.lua";
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0)) {
        cout << "Cannot run file " << filename
            << "\nError:" << "lua_tostring(L, -1)\n";
    }
    lua_getglobal(L, "load_modules");
    int s = lua_pcall(L, 0, 0, 0);
    if (s != 0) reportLuaErrors(L, s);

    lua_getglobal(L, "loadNetModel");
    lua_pushstring(L, "../net/CNN-face-preproc.net");
    s = lua_pcall(L, 1, 0, 0);
    if (s != 0) reportLuaErrors(L, s);
}

FacesClassifier::~FacesClassifier()
{
    lua_close(L);
}

void FacesClassifier::reportLuaErrors(lua_State *L, int status)
{
    if ( status!=0 )
    {
        cerr << "-- " << lua_tostring(L, -1) << endl;
        lua_pop(L, 1);
    }
}

Result FacesClassifier::Classify(const Mat& img)
{
    float *data = img.ptr<float>();
    int len = img.rows * img.cols * img.channels();
    THFloatStorage *storage = THFloatStorage_newWithData(data, len);
    THFloatTensor *tensor =
        THFloatTensor_newWithStorage1d(storage, 0, len, 1);

    lua_getglobal(L, "predict");
    luaT_pushudata(L, tensor, "torch.FloatTensor");

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
