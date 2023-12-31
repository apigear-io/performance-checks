#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
  #define CPP_API_EXPORT __attribute__ ((dllexport))
#else
  #define CPP_API_EXPORT __declspec(dllexport)
#endif
#else
  #if __GNUC__ >= 4
    #define CPP_API_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define CPP_API_EXPORT
  #endif
#endif
