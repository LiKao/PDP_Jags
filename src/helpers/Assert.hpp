// Just like an ordinary assert, but throws instead

#ifndef NDEBUG

#define AssertXstr(s) AssertStr(s)
#define AssertStr(s) #s
#define Assert(condition,message,T) do{ if(!(condition)) { throw T(message); } } while(0)

#else
#define Assert(condition,message,T) ((void)sizeof(condition))
#endif