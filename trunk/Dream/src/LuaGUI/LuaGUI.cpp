/*
** Lua binding: LuaGUI
** Generated automatically by tolua++-1.0.92 on 04/20/10 18:00:12.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_LuaGUI_open (lua_State* tolua_S);

#include "YGELuaUIWnd.h"  

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_YGELuaUIWnd (lua_State* tolua_S)
{
 YGELuaUIWnd* self = (YGELuaUIWnd*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"YGELuaUIWnd");
}

/* method: new of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_new00
static int tolua_LuaGUI_YGELuaUIWnd_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   YGELuaUIWnd* tolua_ret = (YGELuaUIWnd*)  new YGELuaUIWnd();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"YGELuaUIWnd");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_new00_local
static int tolua_LuaGUI_YGELuaUIWnd_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   YGELuaUIWnd* tolua_ret = (YGELuaUIWnd*)  new YGELuaUIWnd();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"YGELuaUIWnd");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_new01
static int tolua_LuaGUI_YGELuaUIWnd_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   YGELuaUIWnd* tolua_ret = (YGELuaUIWnd*)  new YGELuaUIWnd(fileName);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"YGELuaUIWnd");
  }
 }
 return 1;
tolua_lerror:
 return tolua_LuaGUI_YGELuaUIWnd_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_new01_local
static int tolua_LuaGUI_YGELuaUIWnd_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   YGELuaUIWnd* tolua_ret = (YGELuaUIWnd*)  new YGELuaUIWnd(fileName);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"YGELuaUIWnd");
  }
 }
 return 1;
tolua_lerror:
 return tolua_LuaGUI_YGELuaUIWnd_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_delete00
static int tolua_LuaGUI_YGELuaUIWnd_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Load of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_Load00
static int tolua_LuaGUI_YGELuaUIWnd_Load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Load'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Load();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Reload of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_Reload00
static int tolua_LuaGUI_YGELuaUIWnd_Reload00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Reload'",NULL);
#endif
  {
   self->Reload();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Reload'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Hide of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_Hide00
static int tolua_LuaGUI_YGELuaUIWnd_Hide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Hide'",NULL);
#endif
  {
   self->Hide();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Hide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Show of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_Show00
static int tolua_LuaGUI_YGELuaUIWnd_Show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Show'",NULL);
#endif
  {
   self->Show();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Show'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsVisible of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_IsVisible00
static int tolua_LuaGUI_YGELuaUIWnd_IsVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsVisible'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsVisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterEvent of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_RegisterEvent00
static int tolua_LuaGUI_YGELuaUIWnd_RegisterEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
  const char* commentName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* EventName = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,4,0));
  int EventType = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterEvent'",NULL);
#endif
  {
   self->RegisterEvent(commentName,EventName,funName,EventType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterFunction of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_RegisterFunction00
static int tolua_LuaGUI_YGELuaUIWnd_RegisterFunction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
  const char* funcName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* LuaFuncName = ((const char*)  tolua_tostring(tolua_S,3,0));
  int input = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterFunction'",NULL);
#endif
  {
   self->RegisterFunction(funcName,LuaFuncName,input);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterFunction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCommentPosition of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_SetCommentPosition00
static int tolua_LuaGUI_YGELuaUIWnd_SetCommentPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
  const char* commentName = ((const char*)  tolua_tostring(tolua_S,2,0));
  float PositionX = ((float)  tolua_tonumber(tolua_S,3,0));
  float PositionY = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCommentPosition'",NULL);
#endif
  {
   self->SetCommentPosition(commentName,PositionX,PositionY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCommentPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCommentWidth of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_SetCommentWidth00
static int tolua_LuaGUI_YGELuaUIWnd_SetCommentWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
  const char* commentName = ((const char*)  tolua_tostring(tolua_S,2,0));
  float width = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCommentWidth'",NULL);
#endif
  {
   self->SetCommentWidth(commentName,width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCommentWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCommentHeight of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_SetCommentHeight00
static int tolua_LuaGUI_YGELuaUIWnd_SetCommentHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
  const char* commentName = ((const char*)  tolua_tostring(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCommentHeight'",NULL);
#endif
  {
   self->SetCommentHeight(commentName,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCommentHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowComment of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_ShowComment00
static int tolua_LuaGUI_YGELuaUIWnd_ShowComment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
  const char* commentName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowComment'",NULL);
#endif
  {
   self->ShowComment(commentName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowComment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HideComment of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_HideComment00
static int tolua_LuaGUI_YGELuaUIWnd_HideComment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
  const char* commentName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HideComment'",NULL);
#endif
  {
   self->HideComment(commentName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HideComment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsCommentShow of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_IsCommentShow00
static int tolua_LuaGUI_YGELuaUIWnd_IsCommentShow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
  const char* commentName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsCommentShow'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsCommentShow(commentName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsCommentShow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCommentWidth of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_GetCommentWidth00
static int tolua_LuaGUI_YGELuaUIWnd_GetCommentWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
  const char* commentName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCommentWidth'",NULL);
#endif
  {
   float tolua_ret = (float)  self->GetCommentWidth(commentName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCommentWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetcommentHeight of class  YGELuaUIWnd */
#ifndef TOLUA_DISABLE_tolua_LuaGUI_YGELuaUIWnd_GetcommentHeight00
static int tolua_LuaGUI_YGELuaUIWnd_GetcommentHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"YGELuaUIWnd",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  YGELuaUIWnd* self = (YGELuaUIWnd*)  tolua_tousertype(tolua_S,1,0);
  const char* commentName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetcommentHeight'",NULL);
#endif
  {
   float tolua_ret = (float)  self->GetcommentHeight(commentName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetcommentHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_LuaGUI_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"YGELuaUIWnd","YGELuaUIWnd","",tolua_collect_YGELuaUIWnd);
  #else
  tolua_cclass(tolua_S,"YGELuaUIWnd","YGELuaUIWnd","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"YGELuaUIWnd");
   tolua_function(tolua_S,"new",tolua_LuaGUI_YGELuaUIWnd_new00);
   tolua_function(tolua_S,"new_local",tolua_LuaGUI_YGELuaUIWnd_new00_local);
   tolua_function(tolua_S,".call",tolua_LuaGUI_YGELuaUIWnd_new00_local);
   tolua_function(tolua_S,"new",tolua_LuaGUI_YGELuaUIWnd_new01);
   tolua_function(tolua_S,"new_local",tolua_LuaGUI_YGELuaUIWnd_new01_local);
   tolua_function(tolua_S,".call",tolua_LuaGUI_YGELuaUIWnd_new01_local);
   tolua_function(tolua_S,"delete",tolua_LuaGUI_YGELuaUIWnd_delete00);
   tolua_function(tolua_S,"Load",tolua_LuaGUI_YGELuaUIWnd_Load00);
   tolua_function(tolua_S,"Reload",tolua_LuaGUI_YGELuaUIWnd_Reload00);
   tolua_function(tolua_S,"Hide",tolua_LuaGUI_YGELuaUIWnd_Hide00);
   tolua_function(tolua_S,"Show",tolua_LuaGUI_YGELuaUIWnd_Show00);
   tolua_function(tolua_S,"IsVisible",tolua_LuaGUI_YGELuaUIWnd_IsVisible00);
   tolua_function(tolua_S,"RegisterEvent",tolua_LuaGUI_YGELuaUIWnd_RegisterEvent00);
   tolua_function(tolua_S,"RegisterFunction",tolua_LuaGUI_YGELuaUIWnd_RegisterFunction00);
   tolua_function(tolua_S,"SetCommentPosition",tolua_LuaGUI_YGELuaUIWnd_SetCommentPosition00);
   tolua_function(tolua_S,"SetCommentWidth",tolua_LuaGUI_YGELuaUIWnd_SetCommentWidth00);
   tolua_function(tolua_S,"SetCommentHeight",tolua_LuaGUI_YGELuaUIWnd_SetCommentHeight00);
   tolua_function(tolua_S,"ShowComment",tolua_LuaGUI_YGELuaUIWnd_ShowComment00);
   tolua_function(tolua_S,"HideComment",tolua_LuaGUI_YGELuaUIWnd_HideComment00);
   tolua_function(tolua_S,"IsCommentShow",tolua_LuaGUI_YGELuaUIWnd_IsCommentShow00);
   tolua_function(tolua_S,"GetCommentWidth",tolua_LuaGUI_YGELuaUIWnd_GetCommentWidth00);
   tolua_function(tolua_S,"GetcommentHeight",tolua_LuaGUI_YGELuaUIWnd_GetcommentHeight00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_LuaGUI (lua_State* tolua_S) {
 return tolua_LuaGUI_open(tolua_S);
};
#endif

