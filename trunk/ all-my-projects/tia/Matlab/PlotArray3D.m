function PlotArray3D(hFig, X,Y,Z)
hAxes= get(hFig,'CurrentAxes');
plot3(hAxes,X,Y,Z,'.');