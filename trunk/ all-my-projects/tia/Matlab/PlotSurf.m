function PlotSurf%( x,y,z )
l=50;
%x=0:pi/10:10*pi;
x=pi*2*rand(l,1);
%y=0:pi/5:20*pi;
y=pi*3*rand(l,1);
z=2.*sin(x) + 3.*cos(y);



1
2
3
4
5
6
7
8
9
10
11
12
13
clear x y p0 p1 p2, close, clc 
x = 1:10
y = sort(randi([0 100], 1, 10))
p0 = polyfit(x,y,0)
p1 = polyfit(x,y,1)
p2 = polyfit(x,y,2)
p3 = polyfit(x,y,3)
figure('Units','normalized','OuterPosition',[0 0 1 1])
plot(x, y, 'rx')
hold on
fplot(@(x)polyval(p0,x), [1 10], 'b')
fplot(@(x)polyval(p1,x), [1 10], 'k')
fplot(@(x)polyval(p2,x), [1 10], 'g')
fplot(@(x)polyval(p3,x), [1 10], 'y')
legend('табличные значения', 'полином 0-й степени', 'полином 1-й степени', 'полином 2-й степени',-1)

polyfitn
%plot3d(x,y,z);
%surf(x,y,z);
end

