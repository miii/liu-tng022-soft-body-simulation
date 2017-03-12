function visualize3D(x, y, z, conn, interval, lim)
%   Visualize a MSD system with multiple masses in a plot
%   Last updated: 020317
%
%   x: Mass position in the x dimension
%   y: Mass position in the y dimension
%   z: Mass position in the z dimension
%   interval (optional): Pause time between every frame (default: 0.01)
%   lim (optional): Plot axis limits (default: autoscale)
    
    [m n] = size(x);
    colors = ['k', 'm', 'b' 'r', 'g', 'c', 'y'];
    
    if nargin < 5
        interval = 0.01;
    end
    
    % If no y-axis data is available
    if y == 0
        y = zeros(m, n);
    end
    
    if nargin < 6
        % If no x-axis data is available, set default limits
        xlimit = [min(x(:)) max(x(:))];
        
        % If no y-axis data is available, set default limits
        ylimit = [min(y(:)) max(y(:))];
        
        % If no y-axis data is available, set default limits
        zlimit = [min(z(:))-0.1 max(z(:))+0.1];
        
        sbmin = min([min(x(:)) min(y(:)) min(z(:))]);
        sbmax = max([max(x(:)) max(y(:)) max(z(:))]);
        
        %xlimit = [sbmin sbmax];
        %ylimit = [sbmin sbmax];
        %zlimit = [sbmin sbmax];
    else
        xlimit = lim;
        ylimit = lim;
        zlimit = lim;
    end
    
    figure;
    
    [~, connsize] = size(conn);
    
    % Create empty vector for storing plot data
    h = gobjects(n, 1);
    g = gobjects(n, connsize);
    
    % i = iteration for every frame
    % j = iteration for every mass
    for i = 1:5:m
        for j = 1:n
            
            % Remove point from last frame
            if (ishandle(h(j)))
                delete(h(j));
            end;
            
            % Format plot
            %style = strcat('x', colors(mod((j - 1), length(colors)) + 1));
            style = 'xk';
            
            massconn = conn(j, :);
            
            for k = 1:connsize
                if massconn(k) == 0
                    continue;
                end
                
                if (ishandle(g(j, k)))
                    delete(g(j, k));
                end;
                
                cx = [x(i, j), x(i, massconn(k))];
                cy = [y(i, j), y(i, massconn(k))];
                cz = [z(i, j), z(i, massconn(k))];
                g(j, k) = line(cx, cy, cz);
            end
            
            % Plot point
            h(j) = plot3(x(i, j), y(i, j), z(i, j), style);
            
            % Continue to plot in same figure
            hold on
            
            % Set axis limits
            xlim(xlimit)
            ylim(ylimit)
            zlim(zlimit)
        end
        
        % Pause frame before render new
        pause(interval)
    end
    
end

