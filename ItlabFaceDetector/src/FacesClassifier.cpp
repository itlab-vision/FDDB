#include "FacesClassifier.hpp"
#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

FacesClassifier::FacesClassifier()
{
    L = lua_open();
    luaL_openlibs(L);

    const char *filename = "/scripts/faces.lua";
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0)) {
        cout << "Cannot run file " << filename
            << "\nError:" << "lua_tostring(L, -1)\n";
    }
    lua_getglobal(L, "load_modules");
    int s = lua_pcall(L, 0, 0, 0);
    if (s != 0) reportLuaErrors(L, s);

    lua_getglobal(L, "loadNetModel");
    lua_pushstring(L, "/net/CNN-face-preproc.net");
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

Result FacesClassifier::Classify(Mat& img)
{
    int len = img.rows * img.cols * img.channels();
    uchar *data = img.ptr<uchar>();

    float *tensorData = new float[len];
    for (int k = 0; k < 3; ++k)
    {
        for (int i = 0; i < img.rows; ++i) 
        {
            for (int j = 0; j < img.cols; ++j) 
            {
                tensorData[k * 3 + i * img.cols + j] = ((float)img.at<Vec3b>(i, j)[2-k]) / 255.0f;
            }
        }
    }

    THFloatStorage *storage = THFloatStorage_newWithData(tensorData, len);
    THFloatTensor *tensor = THFloatTensor_newWithStorage1d(storage, 0, len, 1);

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

    delete[] tensorData;
	return result;
}
