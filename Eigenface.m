close all;clear all;clc;

disp('------------------------------Train------------------------------')
filePath = 'E:\Eigenface\train\';
fileExt = '*.bmp';
files = dir(fullfile(filePath,fileExt));
len = size(files,1);
defaultW = 92;
defaultH = 112;
faceMat = zeros(defaultH * defaultW,len);
label = zeros(1,len);
% Read face images and convert to "defaultH * defaultW" dimensionals column vectors,
% moreover, save them in the 'faceData'.
for i = 1:len
    fileFullName = strcat(filePath,files(i).name);
    srcImg = imread(fileFullName);
    disp(['----------',fileFullName,'----------'])
    srcImgFigHandle = figure(1);
    set(srcImgFigHandle,'name','srcImg','Numbertitle','off');
    subplot(4,10,i);
    imshow(uint8(srcImg),[]);
    faceMat(:,i) = reshape(srcImg,defaultH * defaultW,1);
    label(1,i) = str2double(files(i).name((strfind(files(i).name,'_') + 2):(strfind(files(i).name,'.') - 1)));
end
averFaceVec = sum(faceMat,2) / len;
averFaceImg = reshape(averFaceVec,defaultH,defaultW);
averFaceImgFigHandle = figure(2);
set(averFaceImgFigHandle,'name','averFace','Numbertitle','off');
imshow(uint8(averFaceImg),[]);
diffMat = faceMat - repmat(averFaceVec,1,len);

covMat = (diffMat' * diffMat);
[eigVecMat,~] = eig(covMat);
eigVal = eig(covMat);
[sortedEigVal,index]= sort(eigVal,'descend');
sortedEigVecMat=eigVecMat(:,index);
finalEigVecMat = diffMat * sortedEigVecMat;
for i = 1:len
    feaFaceFigHandle = figure(3);
    set(feaFaceFigHandle,'name','feaFace','Numbertitle','off');
    subplot(4,10,i);
    imshow(uint8(reshape(finalEigVecMat(:,i),defaultH,defaultW)),[]);
end
finalEigVecMat = finalEigVecMat(:,1 : find(sortedEigVal < 1) - 1);
% reduDimMat is the matrix after reducing the dimensionality.
reduDimMat = finalEigVecMat' * diffMat;

disp('------------------------------Test------------------------------')
testPath = 'E:\Eigenface\test\';
subFolders = dir(testPath);
foldersLen = size(subFolders,1);
corrNum = 0;
testNum = 0;
for i = 3:foldersLen
    subFolder = [testPath,subFolders(i).name];
    disp(['----------',subFolder,'----------'])
    testFiles = dir([subFolder,'\*.bmp']);
    testFilesLen = size(testFiles,1);
    testNum = testNum + testFilesLen;
    testLabel = str2double(subFolders(i).name((strfind(subFolders(i).name,'s') + 1):end));
    for j = 1:testFilesLen
        disp(['----------',testFiles(j).name,'----------'])
        testFullPath = strcat(subFolder,'\',testFiles(j).name);
        testImg = imread(testFullPath);
        testFaceVec = reshape(testImg,defaultH * defaultW,1);
        testDiffVec = double(testFaceVec) - averFaceVec;
        testEigVec = finalEigVecMat' * testDiffVec;
        
        testSum = 0;
        testMin = 0;
        testIndex = 1;
        for w = 1:len
            for l = 1 : (find(sortedEigVal < 1) - 1)
                testSum = testSum + (testEigVec(l) - reduDimMat(l,w)).^2;
                if(w == 1)
                    testMin = testSum;
                end
            end
            if(testMin > testSum)
                testMin = testSum;
                testIndex = w;
            end
            testSum = 0;
        end
            if testLabel == label(1,testIndex)
                corrNum = corrNum + 1;
            end
    end
end

percent = corrNum / testNum;



