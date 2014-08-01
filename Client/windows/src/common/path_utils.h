/**
* @file path_utils.h
*/
#ifndef SECPLATFORM_COMMON_PATHUTILS_H
#define SECPLATFORM_COMMON_PATHUTILS_H

#include <string>

//#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Psapi.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Psapi.lib ")

namespace path_utils
{

/**
 * ��õ�ǰģ���ļ�������·��
 */
static std::string GetModuleFullPath(HMODULE module)
{
    std::string module_full_path;

    unsigned long size = 1024;
    std::string tmp;
    tmp.resize(size);
    unsigned long ret = GetModuleFileNameExA(GetCurrentProcess(), module, &tmp[0], size);
    while (ret == (size-1))
    {
        size *= 2;
        tmp.resize(size);
        ret = GetModuleFileNameExA(GetCurrentProcess(), NULL, &tmp[0], size);
    }
    if (0 == ret)
    {
        throw (std::runtime_error("Failed to get application directory."));
    }

    module_full_path.assign(tmp.data(), ret);

    return module_full_path;
}

/**
 * ��ó����ļ�������·��
 */
static const std::string& GetAppFullPath()
{
    static std::string app_full_path;

    if (app_full_path.empty())
    {
        app_full_path = GetModuleFullPath(NULL);
    }

    return app_full_path;
}

/**
 * ���ģ���ļ�����Ŀ¼
 */
static std::string GetModuleDirectory(HMODULE module)
{
    std::string module_dir;

    std::string tmp;
    tmp = GetModuleFullPath(module);
    PathRemoveFileSpecA(&tmp[0]);
    module_dir = tmp.substr(0, tmp.find('\0'));

    return module_dir;
}

/**
 * ��ó����ļ�����Ŀ¼
 */
static const std::string& GetAppDirectory()
{
    static std::string app_dir;

    if (app_dir.empty())
    {
        app_dir = GetModuleDirectory(NULL);
    }

    return app_dir;
}

/**
 * ���õ�ǰĿ¼Ϊ��������Ŀ¼
 */
static void ResetCurrentDirectory()
{
    SetCurrentDirectoryA(GetAppDirectory().c_str());
}

}

#endif // SECPLATFORM_COMMON_PATHUTILS_H