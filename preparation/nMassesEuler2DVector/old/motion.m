function v = motion(v, x, r)
%MOTION Function to decrease speed of masses instead of just hard limiting
% to avoid unnatural behavior
%   v = velocity vector with all masses
%   x = position vector with all masses
%   r = rest length of the spring

    [m n] = size(x);
    
    % Number between 0-1
    % 0 will not decrease at all
    % 1 will act like a limiter
    degression = 0.15;
    
    % Threshold for the algorithm to activate
    % Will depend on the rest length of the spring
    threshold = 0.3;
    
    for i = 1:(n-1)
        
        % Decrease speed "naturally" if masses are about to collide
        if v(i) >= 0 && v(i+1) <= 0
           absx = abs(x(i) - x(i+1));
           if absx < r * threshold
               v(i) = v(i) * (1 - degression)^(1/absx);
               v(i+1) = v(i+1) * (1 - degression)^(1/absx);
           end
        
        % Decrease speed "naturally" is masses are about to fall apart
        elseif v(i) <= 0 && v(i+1) >= 0
           absx = abs(x(i) - x(i+1));
           if absx > r * (2 - threshold)
               v(i) = v(i) * (1 - degression)^(1/absx);
               v(i+1) = v(i+1) * (1 - degression)^(1/absx);
           end
        end
        
        % Hard limiter
        if abs(x(i) - x(i+1)) < threshold / 3
            v(i) = 0;
            v(i+1) = 0;
        end
    end

end

