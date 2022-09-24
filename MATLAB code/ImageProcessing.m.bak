clc;
clear;
close all;
warning off;
[filename, pathname] = uigetfile('*.*');
if isequal(filename,0)
disp('User selected Cancel')
else
disp(['User selected ', fullfile(pathname, filename)])
end
% % READ THE IMAGE
im=imread([pathname,filename]);
figure,imshow(im),title('input image ');
%%
im = imresize(im,[256 256]);
figure,imshow(im),title('resized image');
[r, c, d] = size(im);
if d == 3
 gray = im2double(rgb2gray(im));
[58]
else
 gray = im2double(im);
end
figure,imshow(gray);
% % %
points11 = detectSURFFeatures(gray);
figure,
imshow(im);
hold on;
plot(selectStrongest(points11,100))
% Extract the features.
[f1,vpts1] = extractFeatures(gray,points11);
f2 = mean(f1);
load feature.mat;
lab = ones(1,37);
[59]
lab(13:37)=2;
mdl = fitcknn(feature,lab);
yfit = predict(mdl,f2);
% % % Decision Making
if yfit == 1
disp('decomposable waste')
elseif yfit == 2
disp('plastics');
end

instrumentObjects=instrfind; 
 delete(instrumentObjects)
[60]
a=serial('COM4','BaudRate',9600);
fopen(a);
 if yfit==1
fwrite(a,'B');
 elseif yfit==2
fwrite(a,'A');
 end
fclose(a);
% closePreview(vid);