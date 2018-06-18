Import('env')
env.Append(CFLAGS=["-std=gnu11",  "-Isrc/network/mbedtls/include","-Isrc/include","-DLWM2M_CLIENT_MODE"],
           CXXFLAGS=["-std=c++11","-Isrc/network/mbedtls/include","-Isrc/include","-DLWM2M_CLIENT_MODE"],
           CPPPATH=["src/wakaama"])
