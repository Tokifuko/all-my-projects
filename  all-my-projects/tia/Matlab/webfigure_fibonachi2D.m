function returnFigure = webfigure_fibonachi2D(figure1)
if(nargin <1) 
    figure1=GetFigHandle();
end
%set(figure1, 'Visible', 'off'); % �������� user guide
fibonachi2D(figure1);

returnFigure = webfigure(figure1); % �������� user guide
%close(figure1); % �������� user guide
end

