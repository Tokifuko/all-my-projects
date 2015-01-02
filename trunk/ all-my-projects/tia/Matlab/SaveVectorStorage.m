% возвращает     0 в случае успеха
%                1- неправильно задан путь
function res= SaveVectorStorage(path, filename  )
%проверяем правильность пути
if (exist(path,'dir')~=7) 
    res=1;
    return;
end;

if (strcmp(filename,'')) 
    filename='noname.mat'; 
end;

global VectorArray;
global ForceArray;
global PressArray;
global SpeedArray;
global LengthArray;
global ValveInPowerArray;
global ValveOutPowerArray;
global ValveInCountArray;
global ValveOutCountArray;
old_dir=cd(path);
save(filename,'VectorArray','ForceArray','PressArray','SpeedArray','LengthArray','ValveInPowerArray','ValveOutPowerArray','ValveInCountArray','ValveOutCountArray');
cd(old_dir);
res=0;
end

