// lua_glue.h
//
// Minimal stand-in for <lua.h>/<lauxlib.h>/<lualib.h>.
//
// This is NOT a copy of Lua's real header files — it's a hand-written set of
// declarations for the small subset of the (stable, public, documented) Lua
// 5.4 C API that this project actually calls. lua_State is fully opaque (we
// never touch its internals), so as long as each function signature below
// matches the real one, this links correctly against the system's
// liblua5.4.so, with no need for the lua5.4-dev package to be installed.

#ifndef LUA_GLUE_H
#define LUA_GLUE_H

#include <cstddef>

extern "C" {

typedef struct lua_State lua_State;
typedef int (*lua_CFunction)(lua_State* L);

struct luaL_Reg {
    const char* name;
    lua_CFunction func;
};

// --- state lifecycle ---
lua_State* luaL_newstate(void);
void       luaL_openlibs(lua_State* L);
void       lua_close(lua_State* L);

// --- stack manipulation ---
void lua_pushnil(lua_State* L);
void lua_pushboolean(lua_State* L, int b);
const char* lua_pushstring(lua_State* L, const char* s);
int  lua_toboolean(lua_State* L, int idx);
const char* lua_tolstring(lua_State* L, int idx, size_t* len);
void lua_settop(lua_State* L, int idx);
int  lua_gettop(lua_State* L);

// --- tables / globals ---
void lua_createtable(lua_State* L, int narr, int nrec);
void lua_setfield(lua_State* L, int idx, const char* k);
int  lua_getfield(lua_State* L, int idx, const char* k);
void lua_setglobal(lua_State* L, const char* name);
int  lua_getglobal(lua_State* L, const char* name);

// --- calling into Lua / registering C functions ---
typedef long long lua_KContext;
typedef int (*lua_KFunction)(lua_State* L, int status, lua_KContext ctx);
int  lua_pcallk(lua_State* L, int nargs, int nresults, int errfunc,
                 lua_KContext ctx, lua_KFunction k);
int  luaL_loadstring(lua_State* L, const char* s);
void luaL_setfuncs(lua_State* L, const luaL_Reg* l, int nup);

// --- argument checking helpers ---
const char* luaL_checklstring(lua_State* L, int arg, size_t* l);
const char* luaL_optlstring(lua_State* L, int arg, const char* def, size_t* l);

}  // extern "C"

#define luaL_checkstring(L, n)  (luaL_checklstring((L), (n), nullptr))
#define luaL_optstring(L, n, d) (luaL_optlstring((L), (n), (d), nullptr))
#define lua_pop(L, n)           lua_settop((L), -(n)-1)
#define lua_pcall(L, n, r, f)   lua_pcallk((L), (n), (r), (f), 0, nullptr)

#endif
