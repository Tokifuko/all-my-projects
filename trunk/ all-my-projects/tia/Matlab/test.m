function test
hF=GetFigHandle();
x=0:pi/10:pi*8;
y=0:pi/20:pi*4;
z=sin(x)+cos(y);
PlotArray3D(hF,x*100,y*100,z*100);
end 