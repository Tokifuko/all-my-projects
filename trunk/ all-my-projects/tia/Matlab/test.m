function test(force,press,len,speed)
hFig= figure('PaperSize',[20.98 29.68]);
set(hFig,'CurrentAxes', axes());
set(hFig,'Name','poly');
hAxes= get(hFig,'CurrentAxes');

X=force(5,:);
%X=median(force);


Y=press(5,:);
%Y=median(press);

Z=len(5,:);
SP=speed(5,:);

X=double(X);
Y=double(Y);
Z=double(Z);
SP=double(SP);

X=X';
Y=Y';
Z=Z';
SP=SP';

order=8;
Xin=[X,Y];
p = polyfitn(Xin,Z,order);
Z_calc = polyvaln(p,Xin);

Error=(Z-Z_calc).^2;

%% удаляем из последовательности 1% артефактов с самой большой ошибкой
percent=1;
poz=length(Error)-(length(Error)/100)*percent;
temp_array=sort(Error);
max_Error=temp_array(poz);

X(Error>max_Error)=[];
Y(Error>max_Error)=[];
Z(Error>max_Error)=[];
Z_calc(Error>max_Error)=[];
SP(Error>max_Error)=[];
Error(Error>max_Error)=[];

%% среднеквадратичная ошибка
% med_Error=median(Error);
% plot(med_Error,'.');

%% распределение квадратичного отклонения
% sort_Error=sort(Error);
% plot (sort_Error);

%% Зависимость ошибки от других величин
%plot(Error,X,'.');

%% рисование поверхности%%
% plot3(hAxes,X',Y',Z','.');
% [xg,yg]=meshgrid(min(X):(max(X)-min(X))/50:max(X),min(Y):(max(Y)-min(Y))/50:max(Y));
% hold on
% zg = polyvaln(p,[xg(:),yg(:)]);
% surf(hAxes, xg,yg,reshape(zg,size(xg)))
% hold off

%% график реального и вычисленного значения длинны
hAx1=subplot (2,1,1);
hold on
plot(hAx1,Z(1150:1300),'k');
plot(hAx1,Z_calc(1150:1300),'r');
hAx2=subplot(2,1,2);
semilogy (hAx2,Error(1150:1300),'k');
hold off

end 