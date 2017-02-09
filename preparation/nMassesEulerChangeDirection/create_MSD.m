function [ x, v ] = create_MSD( x, v, samples, n, m, k, d, r, h )
% The function creates the values of vectors x and v using Euler
% approximation
% The function uses two other functions: abs_val and direction
% 
% Parameter explanation:
% x = displacement, v = velocity, samples = number of samples, n = number
% of masses, m = mass, k = spring constants, d = damper constant, r = rest
% length of the spring, h = step length for Euler approximation

min = 0.15;
max = 1;
% n has to be greater than 2
if n<3
    disp('n has to be greater than 2')
    return
else

    % f is a vector containing the forces of the masses
    f = zeros(1,n);
    fk = zeros(1,n);
    fd = zeros(1,n);

    for i=1:samples
        % abs_v is a vector containing the absolute value of two adjacent
        % values in vector x
        abs_v = abs_val(x, i, n);
        % dir is a vector containing the direction between two adjacent
        % values in vector x
        dir = direction(x, i, n);

        % Calculate the force for each mass
        if ((abs_v(1) < min) || (abs_v(1) > max))

            v(i,1) = 0;
            v(i,2) = 0;
        end
        fk(1) = -k*(abs_v(1)-r)*dir(1);
        fd(1) = -d*(v(i,1)-v(i,2));
        f(1) = fk(1) + fd(1);
        for z=2:n-1
            
            if ((abs_v(z) < min) || (abs_v(z) > max) || (abs_v(z-1) < min) ||  (abs_v(z-1) > max))
                v(i,z) = 0;
                v(i,z-1) = 0;
            end
            fk(z) = k*(abs_v(z-1)-r)*dir(z-1) - k*(abs_v(z)-r)*dir(z);
            fd(z) = d*(v(i,z-1)-v(i,z)) - d*(v(i,z)-v(i,z+1));
            f(z) = fk(z) + fd(z);
        end
        
        if ((abs_v(n-1) < min) || (abs_v(n-1) > max))
            v(i,n-1) = 0;
            v(i,n) = 0;
        end
        fk(n) = k*(abs_v(n-1)-r)*dir(n-1);
        fd(n) = d*(v(i,n-1)-v(i,n));
        f(n) = fk(n) + fd(n);
            
        % Euler approximation
        v(i+1,1:n) = v(i,1:n) + h*f(1:n)/m;
        x(i+1,1:n) = x(i,1:n) + h*v(i+1,1:n);

    end
end

end

