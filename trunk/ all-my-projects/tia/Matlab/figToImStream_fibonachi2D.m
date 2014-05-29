function returnByteArray = figToImStream_fibonachi2D(figure1,height, width, elevation, rotation, imageFormat )
if(nargin <4) 
    height=500;
    width=500;
    elevation=30;
    rotation=10;
    imageFormat='png';
    figure1=GetFigHandle();
end
%clc
%clear
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
% for k = 1:length(rtr)
%     x=xtr(k)+rtr(k).*cos(b);
%     y=ytr(k)+rtr(k).*sin(b);
%     z = rtr(k)*ones(1,length(b));
%     line (x,y,z,'Color','b')
% end
set(figure1, 'Color', [.8,.9,1]);% согласно user guide
set(figure1, 'Position', [0, 0, width, height]);% согласно user guide

view([rotation, elevation]);% согласно user guide
returnByteArray = figToImStream('figHandle', figure1, ...
'imageFormat', imageFormat, ...
'outputType', 'uint8');% согласно user guide
%close(figure1); % согласно user guide
end