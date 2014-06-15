function Repaint (hFig)
% global points;
%global  globalFigHandler 
%plot(points);

hAxes= get(hFig,'CurrentAxes');
points=get (hFig,'UserData');
plot(hAxes,points);

