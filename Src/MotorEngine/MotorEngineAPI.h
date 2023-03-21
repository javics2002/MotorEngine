#pragma once
#ifndef __MOTORENGINE_API
#ifdef __MOTORENGINE_EXPORT
#define __MOTORENGINE_API __declspec(dllexport)
#else
#define __MOTORENGINE_API __declspec(dllimport)
#endif
#endif