function PlotArray(hAxes, points)
%hAxes= get(hFig,'CurrentAxes');
if (strcmp(get(hAxes,'BeingDeleted'),'on' )) 
    return
end
plot(hAxes,points);
