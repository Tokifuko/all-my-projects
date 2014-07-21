function SetObjProp(hHandler, sPropName, vValue)

if (strcmp(sPropName,'Title'))
    title(hHandler,vValue);
%     tx=text('String',vValue); 
%     set(hHandler,sPropName,tx);
else
    set(hHandler,sPropName, vValue);
end

