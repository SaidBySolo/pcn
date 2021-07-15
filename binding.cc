#include <napi.h>
#include <Python.h>

// 파이썬 바인딩
std::string py()
{

    PyObject *pName, *pModule, *pDict, *pFunc, *presult;

    Py_Initialize();

    // c실행파일 기준 path append
    PyRun_SimpleString("import sys, os");
    PyRun_SimpleString("sys.path.append(os.getcwd())");
    // 모듈이름
    pName = PyUnicode_FromString("impy");
    // 임포트
    pModule = PyImport_Import(pName);

    pDict = PyModule_GetDict(pModule);

    pFunc = PyObject_GetAttrString(pModule, (char *)"main");

    presult = PyObject_CallObject(pFunc, NULL);

    Py_DECREF(pName);
    Py_DECREF(pModule);
    Py_FinalizeEx();

    return PyUnicode_AsUTF8(presult);
}

//바인딩
Napi::String pythonToJSString(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    return Napi::String::New(env, py());
}

// export 지정
Napi::Object init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "pythonMethod"), Napi::Function::New(env, pythonToJSString));
    return exports;
};

NODE_API_MODULE(pythonBinding, init);