function [ direct, scatterd, diff, dir, sca] = illumination(full, pattern1, pattern2)
%ILLUMINATION Summary of this function goes here
%   Detailed explanation goes here
    [x, y, d] =size(full);
    direct = pattern1;
    scatterd = pattern2;
    for i=1:1:x
        for j=1:1:y
            for k=1:1:d
                l_plus = 0;
                l_minus = 0;
                if (pattern1(i, j, k) > pattern2(i,j,k))
                    l_plus = pattern1(i,j,k);
                    l_minus = pattern2(i,j,k);
                else
                    l_plus = pattern2(i,j,k);
                    l_minus = pattern1(i,j,k);
                end
                scatterd(i,j,k) = 2*l_minus;
                direct(i,j,k) = l_plus - l_minus;
            end
        end
    end
    
    pattern1 = double(pattern1);
    pattern2 = double(pattern2);
    diff = pattern1-pattern2;
	
	dir = direct;
	sca = scatterd;    


    up = 100;
    down = 50;

    distance = 5;
    
    for i=1:1:x
         for j=1:1:y
             for k=1:1:d
                 
                 if (abs(diff(i,j,k)) > down && abs(diff(i,j,k)) < up)
                     diff(i,j,k) = 255;
                     left = max(1, i-distance);
                     ceil = max(1, j-distance);
                     right = min(i+distance, y);
                     floor = min(j+distance, y);
                     
					 count = 0;
					 sum_d = 0;
					 sum_s = 0;
					 for a=left:1:right
						for b=ceil:1:floor
							 sum_d = sum_d + direct(a,b,k);
						     sum_s = sum_s + scatterd(a,b,k);
							 count = count + 1;                       
						end
                     end

					 dir(i,j,k) = sum_d/count;
					 sca(i,j,k) = sum_s/count;
                 else
                     diff(i,j,k)=0;
                 end
             end
         end
     end
    diff = uint8(diff);

end

