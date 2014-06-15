function hFig=GetFigHandle()

% global  globalFigHandler ;
% globalFigHandler= figure('PaperSize',[20.98 29.68]);
% hFig=globalFigHandler;

hFig= figure('PaperSize',[20.98 29.68]);

set(hFig,'CurrentAxes', axes());
%set(globalFigHandler,'WindowStyle','docked');
%xSeries=zeros(50);
%ySeries=zeros(50);
%plotHandler = plot(xSeries, ySeries, 'XDataSource', 'xSeries', 'YDataSource', 'ySeries');
%set(globalFigHandler, 'Visible', 'off')
end