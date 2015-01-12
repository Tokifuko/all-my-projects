global ForceArray;
global PressArray;
global LengthArray;
global ValveInPowerArray;
global ValveOutPowerArray;
global ValveInCountArray;
global ValveOutCountArray

% global gF; global gP; global gL; gF=[]; gP=[]; gL=[];
% ResampleToValveIn('_данные_090115_94.mat',0,0); gF=[gF; ForceArray];
% gP=[gP; PressArray]; gL=[gL; LengthArray];
%  ForceArray=gF; PressArray=gP; LengthArray=gL;
 
load('data_120115_3.mat','ForceArray','PressArray','LengthArray','ValveInPowerArray','ValveOutPowerArray','ValveInCountArray','ValveOutCountArray');
LengthArray=LengthArray+3000;

shift_len=-1;
if (shift_len>0)
    ForceArray(1:shift_len)=[];
    PressArray(1:shift_len)=[];
    ValveInPowerArray(1:shift_len)=[];
    ValveOutPowerArray(1:shift_len)=[];
    LengthArray((end-shift_len+1):end)=[];
end
if (shift_len<0)
    shift_len=shift_len*(-1);
    ForceArray((end-shift_len+1):end)=[];
    PressArray((end-shift_len+1):end)=[];
    ValveInPowerArray((end-shift_len+1):end)=[];
    ValveOutPowerArray((end-shift_len+1):end)=[];
    LengthArray(1:shift_len)=[];
end


% save('collect_data','ForceArray','PressArray','LengthArray');
st=5000;
en=5700;
% 
order=5;
Xin=[ForceArray; PressArray];
Xin=Xin';
Z=LengthArray';
p = polyfitn(Xin,Z,order);
Z_calc = polyvaln(p,Xin);


z1=Z_calc(st:en);
z2=LengthArray(st:en);
hold on
plot(z1,'r');
plot(z2,'g');
% 
x1=ValveInPowerArray(st:en);
x2=ValveOutPowerArray(st:en);
x3=LengthArray(st:en);
x1=x1.*50;
x2=x2.*50;
hold on
plot(x1);
plot(x2,'r');
plot(x3,'g');
