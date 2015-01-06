function nerotest( force, press,len )
hFig= figure('PaperSize',[20.98 29.68]);
set(hFig,'CurrentAxes', axes());
set(hFig,'Name','Nero');
hAxes= get(hFig,'CurrentAxes');

X=force(5,:);
Y=press(5,:);
Z=len(5,:);

X=double(X);
Y=double(Y);
Z=double(Z);

x_t=X(2000:10000);
y_t=Y(2000:10000);
z_t=Z(2000:10000);
nero_input=[[x_t]; [y_t]];
nero_output=z_t;

net.trainParam.epochs


a=fitnet(5);
a=train(a,nero_input,nero_output);
% a=newlind(nero_input,nero_output);
view (a);

x_t=X(1150:1300);
y_t=Y(1150:1300);
nero_input=[[x_t]; [y_t]];
Z_calc=sim(a,nero_input);
Error=(Z(1150:1300)-Z_calc).^2;

%% график реального и вычисленного значения длинны
hAx1=subplot (2,1,1);
hold on
plot(hAx1,Z(1150:1300),'k');
plot(hAx1,Z_calc,'r');

hAx2=subplot(2,1,2);
semilogy (hAx2,Error,'k');
hold off


end

