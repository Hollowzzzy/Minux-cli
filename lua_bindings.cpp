#include "lua_glue.h"
#include "open.h"
#include "delete.h"
#include "create.h"
#include "copy.h"
#include "move.h"
#include <string>

// --- open ---
static int l_read_file(lua_State* L) {
    const char* filename = luaL_checkstring(L, 1);

    std::string content;
    if (read_file(filename, content)) {
        lua_pushstring(L, content.c_str());
        return 1;
    } else {
        lua_pushnil(L);
        return 1;
    }
}

// --- delete ---
static int l_delete_file(lua_State* L) {
    const char* filename = luaL_checkstring(L, 1);
    lua_pushboolean(L, delete_file(filename));
    return 1;
}

static int l_delete_folder(lua_State* L) {
    const char* foldername = luaL_checkstring(L, 1);
    bool recursive = lua_toboolean(L, 2);
    lua_pushboolean(L, delete_folder(foldername, recursive));
    return 1;
}

// --- create ---
static int l_create_file(lua_State* L) {
    const char* filename = luaL_checkstring(L, 1);
    const char* content = luaL_optstring(L, 2, "");
    lua_pushboolean(L, create_file(filename, content));
    return 1;
}

static int l_create_folder(lua_State* L) {
    const char* foldername = luaL_checkstring(L, 1);
    lua_pushboolean(L, create_folder(foldername));
    return 1;
}

// --- copy ---
static int l_copy_file(lua_State* L) {
    const char* oldpath = luaL_checkstring(L, 1);
    const char* newpath = luaL_checkstring(L, 2);
    bool destructive = lua_toboolean(L, 3);
    lua_pushboolean(L, copy_file(oldpath, newpath, destructive));
    return 1;
}

static int l_copy_folder(lua_State* L) {
    const char* oldpath = luaL_checkstring(L, 1);
    const char* newpath = luaL_checkstring(L, 2);
    bool recursive = lua_toboolean(L, 3);
    bool destructive = lua_toboolean(L, 4);
    lua_pushboolean(L, copy_folder(oldpath, newpath, recursive, destructive));
    return 1;
}

// --- move ---
static int l_move_file(lua_State* L) {
    const char* oldpath = luaL_checkstring(L, 1);
    const char* newpath = luaL_checkstring(L, 2);
    lua_pushboolean(L, move_file(oldpath, newpath));
    return 1;
}

static int l_move_folder(lua_State* L) {
    const char* oldpath = luaL_checkstring(L, 1);
    const char* newpath = luaL_checkstring(L, 2);
    lua_pushboolean(L, move_folder(oldpath, newpath));
    return 1;
}

static const luaL_Reg minux_functions[] = {
    {"read_file",     l_read_file},
    {"delete_file",   l_delete_file},
    {"delete_folder", l_delete_folder},
    {"create_file",   l_create_file},
    {"create_folder", l_create_folder},
    {"copy_file",     l_copy_file},
    {"copy_folder",   l_copy_folder},
    {"move_file",     l_move_file},
    {"move_folder",   l_move_folder},
    {nullptr, nullptr}
};

extern "C" int luaopen_minux(lua_State* L) {
    int n = (int)(sizeof(minux_functions) / sizeof(minux_functions[0]) - 1);
    lua_createtable(L, 0, n);
    luaL_setfuncs(L, minux_functions, 0);
    return 1;
}
