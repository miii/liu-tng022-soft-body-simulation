function [acc] = acceleration(i, m, x, v, n, k, d, r)
%Acceleration
min = 0.15;
max = 1;
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
        acc(1) = f(1)/m; 
        for z=2:n-1
            
            if ((abs_v(z) < min) || (abs_v(z) > max) || (abs_v(z-1) < min) ||  (abs_v(z-1) > max))
                v(i,z) = 0;
                v(i,z-1) = 0;
                v(i, z+1) = 0;
            end
            fk(z) = k*(abs_v(z-1)-r)*dir(z-1) - k*(abs_v(z)-r)*dir(z);
            fd(z) = d*(v(i,z-1)-v(i,z)) - d*(v(i,z)-v(i,z+1));
            f(z) = fk(z) + fd(z);
            acc(z) = f(z)/m; 
        end
        
        if ((abs_v(n-1) < min) || (abs_v(n-1) > max))
            v(i,n-1) = 0;
            v(i,n) = 0;
        end
        fk(n) = k*(abs_v(n-1)-r)*dir(n-1);
        fd(n) = d*(v(i,n-1)-v(i,n));
        f(n) = fk(n) + fd(n);
        acc(n) = f(n)/m; 

end

