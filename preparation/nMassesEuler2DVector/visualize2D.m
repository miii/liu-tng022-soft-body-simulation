function visualize2D(x, y, interval)
%   Visualize a MSD system with multiple masses in a plot
%   Last updated: 090217
%
%   x: Mass position in the x dimension
%   y: Mass position in the y dimension
%   interval (optional): Pause time between every frame (default: 0.01)
    
    [m n] = size(x);
    colors = ['k', 'm', 'b' 'r', 'g', 'c', 'y'];
    
    if nargin < 3
        interval = 0.01;
    end
    
    % If no y-axis data is available
    if y == 0
        y = zeros(m, n);
    end
    
    % If no x-axis data is available, set default limits
    if x == 0
       xlimit = [-1 1];
    else
       xlimit = [min(x(:)) max(x(:))];
    end
    
    % If no y-axis data is available, set default limits
    if y == 0
       ylimit = [-1 1];
    else
       ylimit = [min(y(:)) max(y(:))];
    end
    
    figure;
    
    % Create empty vector for storing plot data
    h = gobjects(n, 1);
    
    % i = iteration for every frame
    % j = iteration for every mass
    for i = 1:m
        for j = 1:n
            
            % Remove point from last frame
            if (ishandle(h(j)))
                delete(h(j));
            end;
            
            % Format plot
            style = strcat('O', colors(mod((j - 1), length(colors)) + 1));
            
            % Plot point
            h(j) = plot(x(i, j), y(i, j), style);
            
            % Continue to plot in same figure
            hold on
            
            % Set axis limits
            xlim(xlimit)
            ylim(ylimit)
        end
        
        % Pause frame before render new
        pause(interval)
    end
    
end

