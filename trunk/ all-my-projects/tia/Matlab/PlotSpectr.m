function PlotSpectr(hAxes,Fd,points);
if (strcmp(get(hAxes,'BeingDeleted'),'on' )) 
    return
end
%% Спектральное представление сигнала
FftL=1024;% Количество линий Фурье спектра
FftS=abs(fft(points,FftL));% Амплитуды преобразования Фурье сигнала
FftS=2*FftS./FftL;% Нормировка спектра по амплитуде
FftS(1)=FftS(1)/2;% Нормировка постоянной составляющей в спектре
F=0:Fd/FftL:Fd/2-Fd/FftL;% Массив частот вычисляемого спектра Фурье
%% построение спектра
plot(hAxes,F,FftS(1:length(F)));% Построение спектра Фурье сигнала
end

