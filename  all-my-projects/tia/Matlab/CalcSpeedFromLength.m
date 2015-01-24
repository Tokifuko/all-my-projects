function speed = CalcSpeedFromLength( len, deep )
% делает массив скорости из массива длинны
mean_l=my_mean(len,1);
mean_l=mean_l(1:(end-deep));
speed=len((deep+1):end);
speed=speed-mean_l;
t(1:deep)=0;
speed=[t speed];
end

