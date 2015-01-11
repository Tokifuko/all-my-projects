
global VectorArray;
global ForceArray;
global PressArray;
global SpeedArray;
global LengthArray;
global ValveInPowerArray;
global ValveOutPowerArray;
global ValveInCountArray;
global ValveOutCountArray
global gF;
global gP;
global gL;
% gF=[];
% gP=[];
% gL=[];
ResampleToValveIn('_данные_090115_94.mat',0,0);
% gF=[gF; ForceArray];
% gP=[gP; PressArray];
% gL=[gL; LengthArray];
 ForceArray=gF;
 PressArray=gP;
 LengthArray=gL;
 
shift_len=20;
ForceArray(1:shift_len)=[];
PressArray(1:shift_len)=[];
LengthArray((end-shift_len+1):end)=[];



% save('collect_data','ForceArray','PressArray','LengthArray');
st=5000;
en=5400;
% 
order=8;
Xin=[ForceArray,PressArray];
Xin=Xin;
Z=LengthArray;
p = polyfitn(Xin,Z,order);
Z_calc = polyvaln(p,Xin);


z1=Z_calc(st:en);
z2=LengthArray(st:en);
hold on
plot(z1,'r');
plot(z2,'g');
% 
% x1=ValveInPowerArray(st:en);
% x2=ValveOutPowerArray(st:en);
% x3=LengthArray(st:en);
% x1=x1.*80;
% x2=x2.*80;
% hold on
% plot(x1);
% plot(x2,'r');
% plot(x3,'g');







% rForceRate=length(ForceArray)/length(ValveInPowerArray)
% rPressRate=length(PressArray)/length(ValveInPowerArray)
% rPressRate=length(PressArray)/length(ValveInPowerArray)
% rLengthRate=length(LengthArray)/length(ValveInPowerArray)
% rValveOutRate=length(ValveOutPowerArray)/length(ValveInPowerArray)