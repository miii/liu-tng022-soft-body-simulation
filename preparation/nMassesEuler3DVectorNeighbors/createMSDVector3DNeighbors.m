function [outpos, outvel] = createMSDVector3DNeighbors(masses, velocity, connections, mass, ks, kd, r, h, samples)
%[outpos, outvel] = createMSDVector2D(masses, velocity, mass, k, d, r, h, samples)
%   Simulates a 2D mass-spring-damper system using vectors.
%
%   outpos contains simulated positions of all masses
%   outvel contains simulated velocities of all masses
%
%   masses = 2D vector with masses start positions
%   velocity = 2D vector with masses start velocity
%   connections = 2D vector with all connections for every mass
%   mass = Mass
%   ks = Spring constant
%   kd = Damper constant
%   r = Rest length of spring
%   h = Step size
%   samples = Number of samples

    % Kill if wrong input data
    if ~isequal(size(masses), size(velocity))
        error('Masses and velocity vector must have same dimension')
    end
    
    % Store initial states in output vectors
    outpos(1, :, :) = masses;
    outvel(1, :, :) = velocity;
    
    % Get number of masses (m)
    [m, ~] = size(masses);
    
    % Loop through all samples
    for i = 2:samples
        
        % Copy values from last (calculated) frame
        outpos(i, :, :) = outpos((i - 1), :, :);
        outvel(i, :, :) = outvel((i - 1), :, :);
        
        % Stores all velocity vectors for this frame
        dvel = zeros(size(masses));
        
        dvel(:, 3) = dvel(:, 3) - 9.82;
        
        % Loop through all masses
        for j = 1:m
            
            % Get number of neighbor masses
            kk = length(connections(j, :));
            
            %connrand = connections(j, randperm(length(connections(j, :))));
            
            % Loop through all neighbors of current mass
            for k = 1:kk
                
                % Get neighbor index
                %ni = connrand(k);
                ni = connections(j, k);
                
                % Zero value can be seen as NULL
                if ni == 0
                   continue;
                end
                
                % If mass is given as neighbor with itself
                if j == ni
                	error('Mass cannot be neighbor with itself')
                end
                
                % Set index for mass 1 and 2
                i1 = j;
                i2 = ni;
                
                % Calculate MSD forces for x and y components
                % fp1 is a 1x3 vector with x and y force for mass 1
                % fp2 is a 1x3 vector with x and y force for mass 2
                [fp1, fp2] = calcMSDForce3DNeighbors(i, i1, i2, outpos, outvel, ks, kd, r);
                
%                 % Get current velocity of both masses
%                 rsvel1 = reshape(outvel(i, i1, :), [1 3]);
%                 rsvel2 = reshape(outvel(i, i2, :), [1 3]);
% 
%                 % Get current position of both masses
%                 rspos1 = reshape(outpos(i, i1, :), [1 3]);
%                 rspos2 = reshape(outpos(i, i2, :), [1 3]);
                
                % New code
                dvel(j, :) = dvel(j, :) + fp1;
                dvel(ni, :) = dvel(ni, :) + fp2;
                
            end
            
        end
%         
%             % Euler for velocity
%             vel1 = rsvel1 + h * fp1 / m;
%             vel2 = rsvel2 + h * fp2 / m;
% 
%             % Euler for position
%             pos1 = rspos1 + h * vel1;
%             pos2 = rspos2 + h * vel2;
% 
%             % Store new calculated velocity
%             outvel(i, i1, :) = vel1;
%             outvel(i, i2, :) = vel2;
% 
%             % Store new calculated positon
%             outpos(i, i1, :) = pos1;
%             outpos(i, i2, :) = pos2;

        if i < 800
            dvel(1, :) = 0;
        end
        if i < 1400
            dvel(3, :) = 0;
        end
        if i < 2000
            dvel(2, :) = 0;
        end

        ov = reshape(outvel(i, :, :), size(masses));
        outvel(i, :, :) = ov + h * dvel / m;
        outpos(i, :, :) = outpos(i, :, :) + h * outvel(i, :, :);
        
    end

end

