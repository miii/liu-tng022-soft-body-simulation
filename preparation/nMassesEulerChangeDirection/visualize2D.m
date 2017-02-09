function visualize2D(x, y, xlimit, ylimit, interval)
%   Visualize a MSD system with multiple masses in a plot
%   x: Mass position in the x dimension
%   y: Mass position in the y dimension
%   xlimit: Plot limits in the x dimension
%   ylimit: Plot limits in the y dimension
%   interval: Pause time between every frame (default: 0.01)
    
    [m n] = size(x);
    colors = ['k', 'm', 'b' 'r', 'g', 'c', 'y'];
    
    if y == 0
        y = zeros(m, n);
    end
    
    if nargin < 5
        interval = 0.0001;
    end
    
    fig = figure;
    h = gobjects(n, 1);
    
    for i = 1:m
        for j = 1:n
            
            if (ishandle(h(j)))
                delete(h(j));
            end;
            
            style = strcat('O', colors(mod(j, length(colors))));
            h(j) = plot(x(i, j), y(i, j), style);
            hold on
            
            xlim(xlimit)
            ylim(ylimit)
        end
        pause(interval)
    end
    
end

