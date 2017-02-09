function visualize2D(x, y, interval)
%   Visualize a MSD system with multiple masses in a plot
%   Last updated: 090217
%
%   x: Mass position in the x dimension
%   y: Mass position in the y dimension
%   interval: Pause time between every frame (default: 0.01)
    
    [m n] = size(x);
    colors = ['k', 'm', 'b' 'r', 'g', 'c', 'y'];
    
    if y == 0
        y = zeros(m, n);
    end
    
    if nargin < 3
        interval = 0.01;
    end
    
    if x == 0
       xlimit = [-1 1];
    else
       xlimit = [min(x(:)) max(x(:))];
    end
    
    if y == 0
       ylimit = [-1 1];
    else
       ylimit = [min(y(:)) max(y(:))];
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

