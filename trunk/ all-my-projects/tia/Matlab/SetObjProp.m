function SetObjProp(hHandler, sPropName, vValue)
if (strcmp(sPropName,'Title'))
    set(hHandler,'Title',text('String',vValue))
else
    set(hHandler,sPropName, vValue);
end

