Import('env')
env.Append(CFLAGS=["-std=gnu11"], CXXFLAGS=["-std=c++11"], CPPPATH=["src/wakaama", "wakaama"])
