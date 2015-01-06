ind_min=2000;
ind_max=4000;
% input_vector=[[ForceArray];[PressArray];[ValveInPowerArray];ValveOutPowerArray]];
input_vector=[[SpeedArray];[ForceArray];[PressArray];[ValveInPowerArray(1:4,:)];[ValveOutPowerArray(1:4,:)]];
output_vector=[ValveInPowerArray(5,:);ValveOutPowerArray(5,:)];
% nero_input=[[ForceArray(1:3,:)];[PressArray(5,:)]];
nero_input=input_vector(:,ind_min:ind_max);
nero_output=output_vector(:,ind_min:ind_max);

nero_input=double(nero_input);
nero_output=double(nero_output);
% a=fitnet(2);
a=newrbe(nero_input,nero_output);
% a.trainParam.epochs=15;
% a=train(a,nero_input,nero_output);
% a=newlind(nero_input,nero_output);
save('a');

%% вычисляем скорость с помощю неросети на новом интервале
ind_min=1150;
ind_max=1300;
nero_input=input_vector(:,ind_min:ind_max);
Z_calc=sim(a,nero_input);
output_vector=[ValveInPowerArray(5,:);ValveOutPowerArray(5,:)];
Z=output_vector(:,ind_min:ind_max);
Z=double(Z);
Error=(Z-Z_calc).^2;

%% график реального и вычисленного значения длинны
hFig= figure('PaperSize',[20.98 29.68]);
set(hFig,'CurrentAxes', axes());
set(hFig,'Name','Nero');
hAxes= get(hFig,'CurrentAxes');




hAx1=subplot (2,1,1);
hold on
plot(hAx1,Z(1,:),'k');
plot(hAx1,Z_calc(1,:),'r');

hAx2=subplot(2,1,2);
hold on
plot(hAx2,Z(2,:),'k');
plot(hAx2,Z_calc(2,:),'r');

hold off
