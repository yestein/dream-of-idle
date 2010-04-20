/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGELuaFunctor.cpp
	created:	2010-04-20 15:31 PM
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose: Package a Lua Function by Name to a Functor, make it can be 
	Call by C++ Directly
************************************************************************/
#include "YGELuaFunctor.h"
/*************************************************************************
	Constructor
*************************************************************************/
YGELuaFunctor::YGELuaFunctor(lua_State* state, int func, int selfIndex):
L(state),
index(func),
self(selfIndex),
needs_lookup(false)
{

}

/*************************************************************************
	Constructor
*************************************************************************/
YGELuaFunctor::YGELuaFunctor(lua_State* state, const String& func, int selfIndex, int EventType) :
L(state),
index(LUA_NOREF),
self(selfIndex),
needs_lookup(true),
function_name(func),
event_type(EventType)
{

}

/*************************************************************************
	Constructor
*************************************************************************/
YGELuaFunctor::YGELuaFunctor(const YGELuaFunctor& cp) :
L(cp.L),
index(cp.index),
self(cp.self),
needs_lookup(cp.needs_lookup),
function_name(cp.function_name)
{

}

/*************************************************************************
	Destructor
*************************************************************************/
YGELuaFunctor::~YGELuaFunctor()
{
	if (self!=LUA_NOREF)
	{
		luaL_unref(L, LUA_REGISTRYINDEX, self);
	}
	if (index!=LUA_NOREF)
	{
		luaL_unref(L, LUA_REGISTRYINDEX, index);
	}
}

/*************************************************************************
	Call operator
*************************************************************************/
bool YGELuaFunctor::operator()(const EventArgs& args) const
{
	switch ( event_type )
	{
	case em_NormalEvent:
		{
			lua_getglobal( L, function_name.c_str( ) );
			lua_pcall( L, 0, 0, 0 );
		}
		break;
	case em_MouseEvent:
		break;
	case em_KeyEvent:
		break;
	}

	return true;
}