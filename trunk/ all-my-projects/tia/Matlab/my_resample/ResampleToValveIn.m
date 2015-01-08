function ResampleToValveIn( filename, shift_len, shift_valve)
% помимо изменени€ длинны массивов данных эта функци€ сдвигает:
% массив длинн и скоростей - влево по оси времени. чтобы компенсировать
% отставание данных штангенцыркул€ от реальных значений.
% ћассив данных клапанов - вправо по оси времени, так как клапана
% открываютс€ не сразу, а выдержав фиксированную паузу. в результате данные
% приход€т раньше, чем клапан реально открываетс€.

resample_shift='shift';

load(filename,'ForceArray','PressArray','SpeedArray','LengthArray','ValveInPowerArray','ValveOutPowerArray','ValveInCountArray','ValveOutCountArray');
new_len=length(ValveInPowerArray);
ForceArray=myresample(ForceArray,new_len,resample_shift);
PressArray=myresample(PressArray,new_len,resample_shift);
SpeedArray=myresample(SpeedArray,new_len,resample_shift);
LengthArray=myresample(LengthArray,new_len,resample_shift);
ValveInPowerArray=myresample(ValveInPowerArray,new_len,resample_shift);
ValveOutPowerArray=myresample(ValveOutPowerArray,new_len,resample_shift);
ValveInCountArray=myresample(ValveInCountArray,new_len,resample_shift);
ValveOutCountArray=myresample(ValveOutCountArray,new_len,resample_shift);

% сдвигаем по длинне
SpeedArray(1:shift_len)=[];
LengthArray(1:shift_len)=[];
ForceArray((end-shift_len+1):end)=[];
PressArray((end-shift_len+1):end)=[];
ValveInPowerArray((end-shift_len+1):end)=[];
ValveOutPowerArray((end-shift_len+1):end)=[];
ValveInCountArray((end-shift_len+1):end)=[];
ValveOutCountArray((end-shift_len+1):end)=[];

% сдвигаем по данным клапанов
SpeedArray(1:shift_valve)=[];
LengthArray(1:shift_valve)=[];
ForceArray(1:shift_valve)=[];
PressArray(1:shift_valve)=[];
ValveInPowerArray((end-shift_valve+1):end)=[];
ValveOutPowerArray((end-shift_valve+1):end)=[];
ValveInCountArray((end-shift_valve+1):end)=[];
ValveOutCountArray((end-shift_valve+1):end)=[];

filename=strcat('resample_',filename);
save(filename,'ForceArray','PressArray','SpeedArray','LengthArray','ValveInPowerArray','ValveOutPowerArray','ValveInCountArray','ValveOutCountArray');
end

