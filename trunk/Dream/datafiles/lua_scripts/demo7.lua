--------------------------------------
--事件处理函数
--------------------------------------
function handleAdd( )
  local commentName = "Demo8/Window2"
  if( demo:IsCommentShow( commentName ) ) then
    demo:HideComment( commentName )
  else
    demo:ShowComment( commentName )
  end
end
--------------------------------------
--提供给程序的接口
--------------------------------------
function update( )
  local commentName = "Demo8/Window2"
  if( demo:IsCommentShow( commentName ) ) then
    demo:HideComment( commentName )
  else
    demo:ShowComment( commentName )
  end
end
--------------------------------------
--逻辑回调函数(这里为了方便，就懒的再加一个Lua脚本来写了）
--------------------------------------
function CoreDataChanged( uDataId, uParam, nParam )
  local commentName = "Demo8/Window2"
  if( demo:IsCommentShow( commentName ) ) then
    demo:HideComment( commentName )
  else
    demo:ShowComment( commentName )
  end
end
--------------------------------------
--脚本入口
--------------------------------------
demo = YGELuaUIWnd:new( "demo8.1.layout" )
demo:Load( )
--demo:RegisterEvent( "Demo8/Window1/Controls/Add","Clicked","handleAdd", 1 )
demo:RegisterFunction( "update", "update", 0 )