close all;clear all;clc;

filePath = 'E:\FaceRecognition\face\';
fileExt = '*.bmp';
files = dir(fullfile(filePath,fileExt));
len = size(files,1);
w = 92;
h = 112;
dataS = zeros(w * h,len);

% Read face images and convert to "w * h" dimensionals column vectors,
% moreover save them in the 'dataS'.
for i = 1:len
%     disp(['----------',num2str(i),'----------'])
    srcImg = imread(strcat(filePath,files(i,1).name));
    figHandle1 = figure(1);
    set(figHandle1,'name','srcImg','Numbertitle','off');
    subplot(4,10,i);
    imshow(uint8(srcImg),[]);
    coluVec = reshape(srcImg,w * h,1);
    dataS(:,i) = coluVec;
end
% suptitle('srcImg');

% % Calculate the average image and diff.
averS = sum(dataS,2) / len;
averFace = reshape(averS,h,w);
figHandle2 = figure(2);
set(figHandle2,'name','averFace','Numbertitle','off');
imshow(uint8(averFace),[]);
diff = dataS - repmat(averS,1,len);

covMat = (diff' * diff);
[V,~] = eig(covMat);
D = eig(covMat);
[D_sort,D_index]= sort(D,'descend');
V_sort=V(:,D_index);
actuV = diff * V_sort;

% feaFace = zeros(h,w);
for i = 1:len
%     disp(['----------',num2str(i),'----------'])
%     feaFace = actuV(:,i);    
    figHandle3 = figure(3);
    set(figHandle3,'name','feaFace','Numbertitle','off');
    subplot(4,10,i);
    imshow(uint8(reshape(actuV(:,i),h,w)),[]);
%     pause(1);
end

actuV = actuV(:,1 : find(D_sort < 1) - 1);
% conImg是降维之后的图像数据。
conImg = actuV' * diff;

[trainFile,trainPath] = uigetfile({'*.*','All Files'},'Search an image!:');
trainFullPath = strcat(trainPath,trainFile);
trainImg = imread(trainFullPath);
figHandle4 = figure(4);
set(figHandle4,'name','compare','Numbertitle','off');
subplot(1,2,1);
imshow(uint8(trainImg),[]);
title('The searched image');
trainColuVec = reshape(trainImg,w * h,1);
trainDiff = double(trainColuVec) - averS;
trainConImg = actuV' * trainDiff;

sum = 0;
minV = 0;
index = 1;
for i = 1:len
    for j = 1:find(D_sort < 1) - 1
        sum = sum + (trainConImg(j) - conImg(j,i)).^2;
        if(i == 1)
            minV = sum;
        end
    end
    if(minV > sum)
        minV = sum;
        index = i;
    end
    disp(['----------',num2str(i),'----------'])
    sum
    sum = 0;
end

simImg = imread(strcat(filePath,files(index,1).name));
subplot(1,2,2);
imshow(uint8(simImg),[]);
title('The most similar');














