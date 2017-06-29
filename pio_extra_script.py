from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()
env.Append(CFLAGS=["-std=gnu11"])  # General options that are passed to the C compiler (C only; not C++).
env.Append(CXXFLAGS=["-std=c++11"])  # General options that are passed to the C++ compiler. 
