--------------------------------------
--�¼�������
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
--�ṩ������Ľӿ�
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
--�߼��ص�����(����Ϊ�˷��㣬�������ټ�һ��Lua�ű���д�ˣ�
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
--�ű����
--------------------------------------
demo = YGELuaUIWnd:new( "demo8.1.layout" )
demo:Load( )
--demo:RegisterEvent( "Demo8/Window1/Controls/Add","Clicked","handleAdd", 1 )
demo:RegisterFunction( "update", "update", 0 )