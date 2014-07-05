function test

hF=GetFigHandle();
% x=0:pi/10:pi*8;
% y=0:pi/20:pi*4;
% z=sin(x)+cos(y);
len=50;
x=2*pi*rand (len,1);
y=3*pi*rand(len,1);
z=cos(x)+sin(y)+0.5*rand(len,1);
z=z*(-1);
x=x';
y=y';
z=z';

PlotArray3D(hF,x*1000,y*1000,z*1000);

end 