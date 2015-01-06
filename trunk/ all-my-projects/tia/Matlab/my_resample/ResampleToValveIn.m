function ResampleToValveIn( filename )
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
filename=strcat('resample',filename);
save(filename,'ForceArray','PressArray','SpeedArray','LengthArray','ValveInPowerArray','ValveOutPowerArray','ValveInCountArray','ValveOutCountArray');
end

