%% скрипт удаляет заданное количество процентов отсчетов с конца массива
x=ValveInCountArray;
pr_to_del=0.1;
len=length(x);
len_to_del=round(len*pr_to_del);
x((len-len_to_del):end)=[];
ValveInCountArray=x;