function test


% x=0:pi/10:pi*8;
% y=0:pi/20:pi*4;
% z=sin(x)+cos(y);
len=500;
x=2*pi*rand (len,1);
y=3*pi*rand(len,1);
z=cos(x)+sin(y)+0.5*rand(len,1);
z=z*(-1);
x=x';
y=y';
z=z';
 %PlotArray(hA,x);
 hF1=GetFigHandle();
 hF2=GetFigHandle();



hA=GetAxesHandle(hF1)
 hA1=SplitFigure(hF1,2,1,1)
 
 %hA=GetAxesHandle(hF1);
 hA2=SplitFigure(hF1,2,2,3)
 
 %hA=GetAxesHandle(hF1);
 hA3=SplitFigure(hF1,2,2,4)
hA=GetAxesHandle(hF1)
 SetObjProp(hA,'Title','нулевая');
 SetObjProp(hA1,'Title','первая');
 SetObjProp(hA2,'Title','вторая');
 SetObjProp(hA3,'Title','третья');
 
% SetObjProp(hF,'Name','name');
%PlotSpectr(hA,2,z);

%PlotArray3D(hA,x*1000,y*1000,z*1000);

end 