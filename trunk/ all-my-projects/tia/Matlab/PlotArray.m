function PlotArray(hAxes, points)
if (strcmp(get(hAxes,'BeingDeleted'),'on' )) 
    return
end
plot(hAxes,points);
