function z=SurfTest
len=300;
x=2*pi*rand (len,1);
y=3*pi*rand(len,1);
Xin=[x,y];
z=cos(x)+sin(y)+0.5*rand(len,1);
plot3(x,y,z,'.');
hold on
p = polyfitn(Xin,z,5);

[xg,yg]=meshgrid(0:max(x)/50:max(x),0:max(y)/50:max(y));
zg = polyvaln(p,[xg(:),yg(:)]);
surf(xg,yg,reshape(zg,size(xg)))
hold on
plot3(Xin(:,1),Xin(:,2),z,'o')
hold off
end

