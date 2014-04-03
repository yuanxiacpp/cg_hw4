full=imread('diana/fulllight.tif');
pattern1=imread('diana/pattern1.tif');
pattern2=imread('diana/pattern2.tif');
[direct, scatterd, diff]=illumination(full,pattern1,pattern2);
