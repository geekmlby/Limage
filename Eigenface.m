close all;clear all;clc;

disp('------------------------------Train------------------------------')
trainImgPath = 'E:\Eigenface\train\';
trainImgExt = '*.bmp';
trainImgs = dir(fullfile(trainImgPath,trainImgExt));
trainImgsNum = size(trainImgs,1);
defaultW = 92;
defaultH = 112;
trainImgsLabel = zeros(1,trainImgsNum);
faceDataMat = zeros(defaultH * defaultW,trainImgsNum);

% Read train images and convert to "defaultH * defaultW" dimensionals column vectors,
% moreover, save them in the 'faceDataMat' matrix.
for i = 1:trainImgsNum
    trainImgFullName = strcat(trainImgPath,trainImgs(i).name);
    trainImg = imread(trainImgFullName);
    disp(['----------',trainImgFullName,'----------'])
    trainImgFigHandle = figure(1);
    set(trainImgFigHandle,'name','trainImg','Numbertitle','off');
    subplot(4,10,i);
    imshow(uint8(trainImg),[]);
    trainImgsLabel(1,i) = str2double(trainImgs(i).name((strfind(trainImgs(i).name,'_') + 2):(strfind(trainImgs(i).name,'.') - 1)));
    faceDataMat(:,i) = reshape(trainImg,defaultH * defaultW,1);
end

averFaceVec = sum(faceDataMat,2) / trainImgsNum;
averFaceImg = reshape(averFaceVec,defaultH,defaultW);
averFaceImgFigHandle = figure(2);
set(averFaceImgFigHandle,'name','averFace','Numbertitle','off');
imshow(uint8(averFaceImg),[]);
diffMat = faceDataMat - repmat(averFaceVec,1,trainImgsNum);

% Calculate the covariance matrix.
covMat = (diffMat' * diffMat);
[eigenVecMat,~] = eig(covMat);
eigenValVec = eig(covMat);
[sortedEigenValVec,eigenValIndex]= sort(eigenValVec,'descend');
sortedEigenVecMat=eigenVecMat(:,eigenValIndex);
finalEigenVecMat = SchOrth(diffMat * sortedEigenVecMat);
for i = 1:trainImgsNum
    eigenFaceFigHandle = figure(3);
    set(eigenFaceFigHandle,'name','feaFace','Numbertitle','off');
    subplot(4,10,i);
    imshow(uint8(reshape(finalEigenVecMat(:,i),defaultH,defaultW)),[]);
end
finalEigenVecMat = finalEigenVecMat(:,1 : find(sortedEigenValVec < 1) - 1);
% 'reduDimDataMat' is the matrix after reducing the dimensionality.
reduDimDataMat = finalEigenVecMat' * diffMat;

disp('------------------------------Test------------------------------')
testImgPath = 'E:\Eigenface\test\';
subFolders = dir(testImgPath);
subFoldersNum = size(subFolders,1);
testImgsSum = 0;
corrImgsNum = 0;
for i = 3:subFoldersNum
    subFolder = [testImgPath,subFolders(i).name];
    disp(['----------',subFolder,'----------'])
    testImgs = dir([subFolder,'\*.bmp']);
    testImgsNum = size(testImgs,1);
    testImgsSum = testImgsSum + testImgsNum;
    testImgLabel = str2double(subFolders(i).name((strfind(subFolders(i).name,'s') + 1):end));
    for j = 1:testImgsNum
        disp(['----------',testImgs(j).name,'----------'])
        testImgFullPath = strcat(subFolder,'\',testImgs(j).name);
        testImg = imread(testImgFullPath);
        testImgVec = reshape(testImg,defaultH * defaultW,1);
        testDiffVec = double(testImgVec) - averFaceVec;
        testEigenVec = finalEigenVecMat' * testDiffVec;
        
        sumV = 0;
        minV = 0;
        minIndex = 1;
        for w = 1:trainImgsNum
            for l = 1 : (find(sortedEigenValVec < 1) - 1)
                sumV = sumV + (testEigenVec(l) - reduDimDataMat(l,w)).^2;
                if(w == 1)
                    minV = sumV;
                end
            end
            if(minV > sumV)
                minV = sumV;
                minIndex = w;
            end
            sumV = 0;
        end
        if testImgLabel == trainImgsLabel(1,minIndex)
            corrImgsNum = corrImgsNum + 1;
        end
    end
end

corrPerc = corrImgsNum / testImgsSum;



