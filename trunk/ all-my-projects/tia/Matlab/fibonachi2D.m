function fibonachi2D()
global  globalFigHandler 
figure (globalFigHandler);
clf(globalFigHandler);
%% Create figure
%figure1 = figure('PaperSize',[20.98 29.68]);
%set(figure1, 'Visible', 'off'); % согласно user guide
fg=(1+sqrt(5))/2 ;
step=20;
axis([-2000 2000 -2000 2000]);

%%
start=0;
a=start:pi/20:(start+pi*(step*2));  
b=0:pi/20:2*pi;
rtr=fg.^(a/(pi/2));
xtr=(fg.^((a/(pi/2))-1)).*cos(a-pi/2);
ytr=(fg.^((a/(pi/2))-1)).*sin(a-pi/2);
line (xtr,ytr,rtr,'Color','r');  % это спиралька координат

%% рабочий блок
% for k = 1:length(rtr)
%     x=xtr(k)+rtr(k).*cos(b);
%     y=ytr(k)+rtr(k).*sin(b);
%     z = rtr(k)*ones(1,length(b));
%     line (x,y,z,'Color','b')
% end
%% конец рабочего блока

% start=5*pi/4;
% a=start:pi/20:(start+pi*(step*2)); 
% xfeb=xtr-1.2*rtr.*cos(a);
% yfeb=ytr-1.2*rtr.*sin(a);
% line(xfeb,yfeb,'Color','g');
%  for n=1:1:step
%      %r(n)=((fg^n)-((-fg)^(-n)))/(2*fg-1); 
%      %r(n)=fg^n;
%  end
% 
% for n=3:1:step
%     r(n)=r(n-1)+r(n-2);
%     z0(n)=z0(n-1)+z0(n-2);
%     y0(n)=y0(n-1)+r(n-2)*sin(n*pi/2);
%     x0(n)=x0(n-1)+r(n-2)*cos(n*pi/2);
%     
% end
% %plot(x0(n)+r(n)*sin(t),y0(n)+r(n)*cos(t));
% line(x0,y0,z0);
% 
% t = 0:pi/20:pi/2;
% 
% for n=1:1:step-3
%      x=x0(n);
%      rad=r(n);
%      y=y0(n);
%      z=z0(n);
%     line(x-rad*cos(t+(n*pi*0.5)),y-rad*sin(t+(n*pi*0.5)));
clear fibonachi2D;

end

