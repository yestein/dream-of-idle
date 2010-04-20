/************************************************************************
	Copyright (c) Yu Lei. All rights reserved. 

	filename: 	YGELuaFunctor.h
	created:	2010-04-20 15:31 PM
	author:		Yu Lei(nl-nl-@163.com)
	<change list>
	1. create file (Yu Lei)

	purpose: Package a Lua Function by Name to a Functor, make it can be 
	         Call by C++ Directly
************************************************************************/
#ifndef YGE_LUA_FUNCTOR_H
#define YGE_LUA_FUNCTOR_H
//------------------------------------------------------------------------

#include "CEGUI.h"
extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

using namespace CEGUI;

class YGELuaFunctor
{
	enum em_EventType
	{
		em_NormalEvent = 1,
		em_MouseEvent,
		em_KeyEvent,		
	};
public:
	YGELuaFunctor( lua_State* state, int func, int selfIndex );
	YGELuaFunctor( lua_State* state, const String& func, int selfIndex, int EventType );
	YGELuaFunctor( const YGELuaFunctor& cp );
	~YGELuaFunctor( );

	bool operator( )( const EventArgs& args ) const;

	// 	/*!
	// 	\brief
	// 	function used to subscribe any Lua function as event handler.
	// 	References using the Lua registry.
	// 	To be called from Lua only.
	// 	*/
	// 	static Event::Connection SubscribeEvent(EventSet* self, const String& eventName, int funcIndex, int selfIndex, lua_State* L);
	// 
	// 	/*!
	// 	\brief
	// 	Pushes the Lua function named \param name on top of the Lua stack.
	// 	The name may contain '.' (dots) character for (nested) table values.
	// 	*/
	// 	static void pushNamedFunction(lua_State* L, const String& name);

private:
	lua_State* L;
	mutable int index;
	int self;
	int event_type;
	mutable bool needs_lookup;
	mutable String function_name;
};
//------------------------------------------------------------------------
#endif
