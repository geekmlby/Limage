% Schmidt orthogonalization
function SchOrthMat = SchOrth(BaseMat)

[rNum,cNum] = size(BaseMat);
SchOrthMat = zeros(rNum,cNum);
for i = 1 : cNum
    if i == 1
        SchOrthMat(:,i) = BaseMat(:,i);
    else
        for j = 1 : i
            if j == 1
                SchOrthMat(:,i) = BaseMat(:,i);
            else
                up = calDotPro(SchOrthMat(:,j - 1),BaseMat(:,i))
                down = calDotPro(SchOrthMat(:,j - 1),SchOrthMat(:,j - 1));
                tmp = up /down;
                SchOrthMat(:,i) = SchOrthMat(:,i) - tmp * SchOrthMat(:,j - 1);
            end
        end
    end
end

for i = 1 : cNum
    sum = calDotPro(SchOrthMat(:,i),SchOrthMat(:,i));
    sum = sqrt(sum);
    SchOrthMat(:,i) = SchOrthMat(:,i) / sum;
end















