#pragma once
#include"lib.h"

int Random(int Min,int  Max) {
	return (int)(rand() % (Max - Min + 1) + Min);
}

void Random_ID(string& ID) {
	ID.resize(9);
	ID[2] = '-';
	for (int i = 0; i <= 8; i++) {
		if (i == 4) ID[i] =(char)( Random(65, 90));
		else if (i == 2) {
			continue;
		}
		else	
			ID[i] =(char)( Random(48, 57));
}
}

bool IsFormatValid(const std::string& input) {
	// Biểu thức  định dạng "phút giờ ngày tháng năm"
	regex Time(R"(\d{2} \d{2} \d{2} \d{2} \d{4})");
	return regex_match(input, Time);
}

chrono::system_clock::time_point Get_time_from_User() {
	string time;	
	cin.ignore(INT_MAX, '\n');
	do{
	again:
		cout << "Nhap thoi gian theo dinh dang (Gio Phut Ngay Thang Nam): ";
		getline(cin,time);
		if (!IsFormatValid(time)) {
			cout << "nhap sai dinh dang, yeu cau nhap lai" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (!IsFormatValid(time));
	tm Time = {};
	istringstream ss(time);
	ss >> get_time(&Time, "%H %M %d %m %Y");
	if (ss.fail()) {
		cout << "Loi chuyen doi thoi gian .\n";
		cout << "thoi gian khong hop le, moi nhap lai." << endl;
		goto again;
	}
	cout << "nhap thoi gian thanh cong" << endl;
	return std::chrono::system_clock::from_time_t(std::mktime(&Time));
}

chrono::system_clock::time_point String_to_Time(string time) {
	long long seconds = std::stoll(time);
	chrono::seconds time_duration(seconds);
	chrono::system_clock::time_point time_point = std::chrono::system_clock::from_time_t(0) + time_duration;
	return time_point;
}

long long int Money_Calculator(string entrytime,string exittime) {
	long long int money=0;
	chrono::system_clock::time_point Entrytime= String_to_Time(entrytime);
	chrono::system_clock::time_point Exittime;
	if (exittime[0] == '0') Exittime = chrono::system_clock::now();
	else Exittime = String_to_Time(exittime);
	auto duration = Exittime - Entrytime;
	long long int seconds = chrono::duration_cast<std::chrono::seconds>(duration).count();
	long long int time = seconds /1800+1;
	if (time > 0)money = 50000 + 30000 * (time - 1);
	else money = 50000;
	return money;
}

string Time_to_Date(const chrono::system_clock::time_point& time) {
	auto VN_time = time + chrono::hours(7);
	auto time_point = chrono::time_point_cast<chrono::system_clock::duration>(VN_time);
	auto duration = time_point.time_since_epoch();
	time_t time_t_now = chrono::duration_cast<chrono::seconds>(duration).count();
	tm tm_time;
	if (gmtime_s(&tm_time, &time_t_now) != 0) {
		cout << "Lỗi trong quá trình chuyển đổi thời gian.\n";
		return "";
	}
	stringstream ss;
	ss << put_time(&tm_time, "%H-%M::%d/%m/%Y");
	string formatted_time = ss.str();
	return formatted_time;

}