function PlotArray3D(hAxes, X,Y,Z)
%Invalid or deleted object.
if (strcmp(get(hAxes,'BeingDeleted'),'on' )) 
    return
end
plot3(hAxes,X,Y,Z,'.');
order=5;
if (length(X)<23)order=4; end;
if (length(X)<17)order=3; end;
if (length(X)<12)order=2; end;
if (length(X)<8)order=1; end;
if (length(X)<5)order=0; end;
if (length(X)<2)return;end;  % для апроксимации нужно минимум два элемента
X=X';
Y=Y';
Z=Z';
Xin=[X,Y];
p = polyfitn(Xin,Z,order);
[xg,yg]=meshgrid(min(X):(max(X)-min(X))/50:max(X),min(Y):(max(Y)-min(Y))/50:max(Y));
hold on
zg = polyvaln(p,[xg(:),yg(:)]);
surf(hAxes,xg,yg,reshape(zg,size(xg)))
hold off