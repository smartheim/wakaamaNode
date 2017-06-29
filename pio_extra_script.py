from SCons.Script import DefaultEnvironment

env = Environment()
env.Append(CFLAGS=["-std=c11"])  # General options that are passed to the C compiler (C only; not C++).
env.Append(CXXFLAGS=["-std=c++11"])  # General options that are passed to the C++ compiler. 
