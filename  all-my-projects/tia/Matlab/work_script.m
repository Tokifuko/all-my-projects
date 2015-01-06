  ResampleToValveIn('new030115.mat',11);
st=1170;
en=1250;
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