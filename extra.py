Import('env')
env.Append(CFLAGS=["-std=gnu11"],
           CXXFLAGS=["-std=c++11","-Isrc/network/mbedtls/library","-Isrc/network/mbedtls/include","-Isrc/wakaama","-Isrc","-DLWM2M_CLIENT_MODE","-DLWM2M_BIG_ENDIAN"],
           CPPPATH=["src/wakaama","-Isrc/network/mbedtls/library","-Isrc/network/mbedtls/include","-Isrc/wakaama","-Isrc","-DLWM2M_CLIENT_MODE","-DLWM2M_BIG_ENDIAN"])
