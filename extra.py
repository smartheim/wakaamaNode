Import('env')
env.Append(CXXFLAGS=["-std=c++11"], CPPPATH=["src/wakaama", "wakaama"])
