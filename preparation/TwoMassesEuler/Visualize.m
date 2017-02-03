function Visualize(x, y, xlimit, ylimit)
%   Visualize a MSD system with multiple masses in a plot
%   x: Mass position in the x dimension
%   y: Mass position in the y dimension
%   xlimit: Plot limits in the x dimension
%   ylimit: Plot limits in the y dimension
    
    [m n] = size(x);
    colors = ['k', 'm', 'c' 'r', 'g', 'b', 'w', 'y'];
    
    if y == 0
        y = zeros(m, n);
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
            
            pause(0.001)
            
        end
    end
    
end

