full=imread('glass/fulllight.tif');
pattern1=imread('glass/pattern1.tif');
pattern2=imread('glass/pattern2.tif');
[direct, scatterd]=illumination_fixed(full,pattern1,pattern2);
