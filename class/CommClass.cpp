#include "../header/CommClass.h"
vector<string> split(const string& input, string delimiter) {
    vector<string> result;
    auto start = 0;
    auto end = input.find(delimiter);

    // 구분자가 발견될 때까지 반복
    while(end != string::npos) {
        // start부터 end까지 부분 문자열을 추출하여 result에 추가
        result.push_back(input.substr(start, end - start));

        // start를 다음 부분으로 이동
        start = end + delimiter.size();

        // 다음 구분자 위치를 찾음
        end = input.find(delimiter, start);
    }

    // 마지막 부분 문자열을 result에 추가
    result.push_back(input.substr(start));
    return result;
}