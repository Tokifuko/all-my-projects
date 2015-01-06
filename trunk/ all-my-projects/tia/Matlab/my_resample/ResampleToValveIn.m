function ResampleToValveIn( filename, shift_count)
load(filename,'ForceArray','PressArray','SpeedArray','LengthArray','ValveInPowerArray','ValveOutPowerArray','ValveInCountArray','ValveOutCountArray');
new_len=length(ValveInPowerArray);
ForceArray=myresample(ForceArray,new_len);
PressArray=myresample(PressArray,new_len);
SpeedArray=myresample(SpeedArray,new_len);
LengthArray=myresample(LengthArray,new_len);
ValveInPowerArray=myresample(ValveInPowerArray,new_len);
ValveOutPowerArray=myresample(ValveOutPowerArray,new_len);
ValveInCountArray=myresample(ValveInCountArray,new_len);
ValveOutCountArray=myresample(ValveOutCountArray,new_len);

SpeedArray(1:shift_count)=[];
LengthArray(1:shift_count)=[];
ForceArray((end-shift_count):end)=[];
PressArray((end-shift_count):end)=[];
ValveInPowerArray((end-shift_count):end)=[];
ValveOutPowerArray((end-shift_count):end)=[];
ValveInCountArray((end-shift_count):end)=[];
ValveOutCountArray((end-shift_count):end)=[];

filename=strcat('resample_',filename);
save(filename,'ForceArray','PressArray','SpeedArray','LengthArray','ValveInPowerArray','ValveOutPowerArray','ValveInCountArray','ValveOutCountArray');
end

