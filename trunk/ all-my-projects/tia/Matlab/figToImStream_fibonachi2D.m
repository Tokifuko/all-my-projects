function returnByteArray = figToImStream_fibonachi2D(figure1,height, width, elevation, rotation, imageFormat )
if(nargin <4) 
    height=500;
    width=500;
    elevation=30;
    rotation=10;
    imageFormat='png';
    figure1=GetFigHandle();
end

%set(figure1, 'Visible', 'off'); % согласно user guide
fibonachi2D(figure1);

set(figure1, 'Color', [.8,.9,1]);% согласно user guide
set(figure1, 'Position', [0, 0, width, height]);% согласно user guide

view([rotation, elevation]);% согласно user guide
returnByteArray = figToImStream('figHandle', figure1, ...
'imageFormat', imageFormat, ...
'outputType', 'uint8');% согласно user guide
%close(figure1); % согласно user guide
end