function returnFigure = webfigure_fibonachi2D(figure1)
if(nargin <1) 
    figure1=GetFigHandle();
end
%set(figure1, 'Visible', 'off'); % согласно user guide
fibonachi2D(figure1);

returnFigure = webfigure(figure1); % согласно user guide
%close(figure1); % согласно user guide
end

