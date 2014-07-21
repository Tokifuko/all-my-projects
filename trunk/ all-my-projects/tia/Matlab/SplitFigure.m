function hAxes=SplitFigure( hFig,m,n,p )
hA=GetAxesHandle(hFig);
axes(hA);
hAxes=subplot(m,n,p);
end

