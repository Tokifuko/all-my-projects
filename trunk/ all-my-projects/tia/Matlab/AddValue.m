function AddValue(hFig, point)
points=get(hFig,'UserData');
% global points; 

points=[points point];
 if (length(points))>50
      points(1)=[];
 end %if
 
set(hFig,'UserData',points);
