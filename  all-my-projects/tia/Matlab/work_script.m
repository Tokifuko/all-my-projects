% ResampleToValveIn('new030115.mat',5,5);
st=100;
en=250;
% 
order=4;
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

x1=ValveInPowerArray(st:en);
x2=ValveOutPowerArray(st:en);
x3=LengthArray(st:en);
x1=x1.*80;
x2=x2.*80;
hold on
plot(x1);
plot(x2,'r');
plot(x3,'g');







% rForceRate=length(ForceArray)/length(ValveInPowerArray)
% rPressRate=length(PressArray)/length(ValveInPowerArray)
% rPressRate=length(PressArray)/length(ValveInPowerArray)
% rLengthRate=length(LengthArray)/length(ValveInPowerArray)
% rValveOutRate=length(ValveOutPowerArray)/length(ValveInPowerArray)