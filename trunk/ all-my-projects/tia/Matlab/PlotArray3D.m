function PlotArray3D(hFig, X,Y,Z)
hAxes= get(hFig,'CurrentAxes');

//Invalid or deleted object.

plot3(hAxes,X,Y,Z,'.');
order=2;
% if (length(X)<22)order=4; end;
% if (length(X)<16)order=3; end;
% if (length(X)<11)order=2; end;
% if (length(X)<7)order=1; end;
% if (length(X)<4)order=0; end;
if (length(X)<22)return;end;  % для апроксимации нужно минимум два элемента
Xin=[X,Y];
p = polyfitn(Xin,Z,order);
[xg,yg]=meshgrid(0:max(X)/50:max(X),0:max(Y)/50:max(Y));
hold on
zg = polyvaln(p,[xg(:),yg(:)]);
surf(hAxes,xg,yg,reshape(zg,size(xg)))
hold off