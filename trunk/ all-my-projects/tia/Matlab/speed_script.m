%% темп
% d=2;
% s2= zeros(1, d);
% s2=[s2 s1(1:(end-d))];
% Xin=[f1;p1;bvin1;bvout1;s2];
% Z=[vin1;vout1] ;
%% подготавливаем данные дл€ графиков
f1=ForceArray;
p1=PressArray;
l1=LengthArray;
v1=ValveInPowerArray;
v2=ValveOutPowerArray;
c1=ValveInCountArray;
c2=ValveOutCountArray;
p1=PressArray;

%% получаем мометы изменени€ состо€ни€ клапанов
index=2:length(c1);
bc1(index)=c1(index-1)~=c1(index);
index=bc1>0;
index=2:length(c2);
bc2(index)=c2(index-1)~=c2(index);

index=~bc1;
v1(index)=0;

index=~bc2;
v2(index)=0;
%% удал€ем значени€ из всех точек, кроме точек изменени€
index=~bc1;
v1(index)=0;
index=~bc2;
v2(index)=0;

%% удал€ем точки изменени€, где клапан был закрыт
bc1=v1>0;
bc2=v2>0;
bc=bc1|bc2;

s1=CalcSpeedFromLength(l1,1);
% s1=s1+150;
s1=s1.*5;
c1=c1.*100;
c2=c2.*100;
tv=bc.*150;
p1=p1-200000;
p1=p1.*0.002;

l4=l_calc+4000;
l4=l4.*0.1;

% Z_calc=sim(net1,Xin);

%% —троим графики

st=6400;
en=6500;
hold on
axis auto
xlim([st,en])

plot(l4,'m');
plot(c1,'k');
plot(v1,'r');
plot(v2,'b');
plot(p1,'r');
plot(c2,'b');
plot(tv,'g');