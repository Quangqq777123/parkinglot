#pragma once
#include"lib.h"
#include"calculator.h"
struct Parking_Lot {
    string Name_Parking_Lot;
    int rows=0, cols=0, Parking_spot = 0;
    vector<vector<int>> Parking_lots_matrix;
    bool Is_active = true;
    Parking_Lot() {
        Name_Parking_Lot = "none";
    }
    Parking_Lot(string Name, int r, int c, bool active, int parkingspot) : Name_Parking_Lot(Name), rows(r), cols(c), Is_active(active), Parking_spot(parkingspot) {}
};

struct car {
    string parking_lot;
    string ID;
    chrono::system_clock::time_point Entry_time, Exit_time;
    int Position_X=0, Position_Y=0;
    bool test=false;
    car() {
        ID = "00-0A0000";   
    }
    car(string& parkinglot, string& ID, chrono::system_clock::time_point& entry, chrono::system_clock::time_point& exit, int& x, int& y,bool& t) :parking_lot(parkinglot), ID(ID), Entry_time(entry), Exit_time(exit), Position_X(x), Position_Y(y),test(t) {};
};

void Add_File(const string& Folder_Path, const string& File_Name) {
    ifstream logFileCheck(Folder_Path + "/" + File_Name + ".txt");//kiểm tra tệp đã tồn tại hay không
    if (!logFileCheck.is_open()) {
        ofstream createLogFile(Folder_Path + "/" + File_Name + ".txt"); //tạo mới tệp
        createLogFile.close();
    }
    logFileCheck.close();
}

void Add_Data_To_File_TXT(const string& Folder_Path, const string& File_Name, const Parking_Lot& parkingLot) {
    ofstream file(Folder_Path + "/" + File_Name + ".txt");
    if (file.is_open()) {
        file << parkingLot.Name_Parking_Lot << " " << parkingLot.rows << " " << parkingLot.cols << " " << parkingLot.Is_active << " " << parkingLot.Parking_spot << endl;
        for (int i = 0; i < parkingLot.rows; ++i) {
            for (int j = 0; j < parkingLot.cols; ++j) {
                file << parkingLot.Parking_lots_matrix[i][j] << " ";
            }
            file << endl;
        }
    }
    else {
        cout << "Khong mo duoc file: " << File_Name << endl; return;
    }
    file.close();
}

void Add_Parking_Lot(const string& Folder_Path, const string& history,const string& list) {
    Parking_Lot New_Parking_lot; int temp1, temp2;
    cin.ignore(INT_MAX, '\n');
    cout << "Nhap ten bai do xe: ";
    getline(cin, New_Parking_lot.Name_Parking_Lot);
    ifstream logFileCheck(Folder_Path + "/" + New_Parking_lot.Name_Parking_Lot + ".txt");
     if (logFileCheck.is_open()) {
         cout << "bai xe da ton tai" << endl;
         logFileCheck.close();
         return;
        }
     logFileCheck.close();
    cout << "Nhap so hang cua bai do xe: ";
    cin >> temp1;
    cout << "Nhap so cot cua bai do xe: ";
    cin >> temp2;
    New_Parking_lot.rows = abs(temp1);
    New_Parking_lot.cols = abs(temp2);
    New_Parking_lot.Is_active = true;
    New_Parking_lot.Parking_spot = New_Parking_lot.cols * New_Parking_lot.rows;
    New_Parking_lot.Parking_lots_matrix.resize(New_Parking_lot.rows, vector<int>(New_Parking_lot.cols, 0));
    for (int i = 0; i < New_Parking_lot.rows; i++) {
        for (int j = 0; j < New_Parking_lot.cols; j++) {
            New_Parking_lot.Parking_lots_matrix[i][j] = 0;
        }
    }
    Add_Data_To_File_TXT(Folder_Path, New_Parking_lot.Name_Parking_Lot, New_Parking_lot);
    ofstream listTXT(Folder_Path + "/" + list + ".txt",ios::app);
    if (listTXT.is_open()) {
        listTXT << New_Parking_lot.Name_Parking_Lot<<endl;   
    }
    else {
        listTXT.close();
        cout << "loi nhap du lieu vao list." << endl;
        return;
    }
    listTXT.close();
    ofstream History(Folder_Path + "/" + history + ".txt", ios::app);
    if (History.is_open()) {
        History << "da tao bai xe \'" << New_Parking_lot.Name_Parking_Lot << "\' voi so hang la: " << New_Parking_lot.rows << " ,so cot la: " << New_Parking_lot.cols << ".\n";  
    }
    else {
        History.close();
        cout << "loi nhap du lieu vao history." << endl;
        return;
    }
    History.close();
}

bool Check_ID(const string& Folder_Path, const string& ID, const string& id) {
    fstream ID_file(Folder_Path + "/" + ID + ".txt", ios::in | ios::out);
    string line;
    car Car;
    while (getline(ID_file, line)) {
        if (line.substr(0, 9) == id) {
            ID_file.close();
            return true;
        }
    }
    ID_file.close();
    return false;
}

string Get_ID(const string& Folder_Path, const string& ID) {
    string id;
    bool test = false;
    string error = "error";
    cin.ignore(INT_MAX, '\n');
    while (!test) {
        cout << "Nhap bien so xe: ";
        getline(cin, id);
        if (id.length() != 9 || id[2] != '-' || (id[4] < 'A') || (id[4] > 'Z')) {
            cout << "Nhap bien so sai, yeu cau nhap lai." << endl;
        }
        else {
            bool KT_So = true;
            for (int i = 0; i < 9; i++) {
                if (i == 2 || i == 4) {
                    continue;
                }
                else {
                    if (id[i] < '0' || id[i] > '9') {
                        KT_So = false;
                        break;
                    }
                }
            }
            if (!KT_So) {
                cout << "Nhap bien so sai, yeu cau nhap lai." << endl;
            }
            else {
                if (Check_ID(Folder_Path, ID, id)) {
                    cout << "ID da duoc su dung truoc do." << endl<< "Yeu cau nhap lai." << endl;
                }
                else test = true;
            }
        }
    }
    return id;
}

void Car_in(const string& Folder_Path, const string& filename, const string& ID, const string& history) {
    Parking_Lot Parkinglot;
    car Car;
    if (filename == "Exit") return;
    int x, y,recommend_x,recommend_y,parking_spot = 0;
    ifstream txt(Folder_Path + "/" + filename + ".txt");
    if (!txt.is_open()) {
        cout << "khong the mo file " << filename << endl;
        txt.close();
        return;
    }
    while(txt >> Parkinglot.Name_Parking_Lot >> Parkinglot.rows >> Parkinglot.cols >> Parkinglot.Is_active >> Parkinglot.Parking_spot) {
        Parkinglot.Parking_lots_matrix.resize(Parkinglot.rows, vector<int>(Parkinglot.cols, 0));
        for (int i = 0; i < Parkinglot.rows; i++) {
            for (int j = 0; j < Parkinglot.cols; j++)
                txt >> Parkinglot.Parking_lots_matrix[i][j];
        }
    }
    txt.close();
    if (Parkinglot.Is_active == false || Parkinglot.Parking_spot <= 0) {
        cout << "bai xe khong hop le" << endl;
        return;
    }
    recommend_x = Parkinglot.rows;
    recommend_y = Parkinglot.cols;
    for (int i = 0; i < Parkinglot.rows; i++) {
        for (int j = 0; j < Parkinglot.cols; j++){
            if (i < recommend_x && j < recommend_y&&Parkinglot.Parking_lots_matrix[i][j]==0)
                { recommend_x = i; recommend_y = j;}          
        }
    }
    Car.ID = Get_ID(Folder_Path, ID);
    Car.parking_lot = filename;
    bool position_car = false;
    while (!position_car) {
        cout << "goi y vi tri dau xe: x= " << recommend_x << " y= " << recommend_y << endl;
        cout << "nhap vi tri ban muon dau xe:(x: hang,y: cot)" << endl;
        cout << "vi tri hang bat dau tu 0 cho den " << Parkinglot.rows - 1 << endl;
        cout << "vi tri cot bat dau tu 0 cho den " << Parkinglot.cols - 1 << endl;
        cout << "x = "; cin >> x;
        cout << "y = "; cin >> y;
        if (x >= Parkinglot.rows || y >= Parkinglot.cols || Parkinglot.Parking_lots_matrix[x][y] == 1 || x < 0 || y < 0) {
            cout << "Vi tri khong hop le, moi nhap lai" << endl;
        }
        else {
            cout << "vi tri hop le" << endl;
            Car.Position_X = x;
            Car.Position_Y = y;
            Parkinglot.Parking_lots_matrix[x][y] = 1;
            position_car = true;
            Parkinglot.Parking_spot -= 1;

        }
    }
    Car.Entry_time = chrono::system_clock::now();
    char Exit;
    while (true) {
        cout << "Ban co muon hen thoi gian lay xe ra khong?(Y/N)" << endl;
        cin >> Exit;
        if (Exit == 'N' || Exit == 'n') {
            break;
        }
        else if (Exit == 'Y' || Exit == 'y') {
            Car.Exit_time = Get_time_from_User();
            break;
        }
        else {
            cout << "du lieu nhap khong hop le, moi nhap lai" << endl;
        }
    }
    Add_Data_To_File_TXT(Folder_Path, filename, Parkinglot);
    ofstream TXT(Folder_Path + "/" + ID + ".txt", ios::app);
    if (TXT.is_open()) {
        TXT << Car.ID << " " << Car.parking_lot << " " << chrono::system_clock::to_time_t(Car.Entry_time) << " " << chrono::system_clock::to_time_t(Car.Exit_time) << " " << Car.Position_X << " " << Car.Position_Y<<" " << Car.test <<" " << endl;
    }
    else {
        cout << "khong nhap duoc vao file" << endl;
    }
    TXT.close();
    ofstream History(Folder_Path + "/" + history + ".txt", ios::app);
    if (History.is_open()) {
        History << "da cho xe co bien so " << Car.ID << " vao bai xe \'" << Car.parking_lot << "\'";
        if (Car.test) {
            History << " (xe gia lap)" << endl;
        }
        else {
            History << endl;
        }
    }
    else { 
        cout << "loi nhap du lieu vao history." << endl;
    }
    History.close();
}

string Get_Parking_lot_Name(const string& Folder_Path,const string& list ){
    again:
    system("cls");
    cout << "Cac bai do xe da khoi tao:" << endl;
    fstream List(Folder_Path + "/" + list + ".txt");
    string line;
    vector<string> lines;
    while (getline(List, line)) {
        cout << line << endl;
        lines.push_back(line);
    }
    bool finded=false;
    string name;
    cin.ignore(INT_MAX, '\n');
    cout << "Moi nhap ten bai xe(nhap Exit de thoat): ";
    getline(cin, name);
    for (auto l : lines) {
        if (l == name) {
            finded = true;
            break;
        }
    }
    if (finded == true) {
        return name;
    }
    else if (name == "Exit") {
        return name;
    }
    else {
        cout << "Khong tim thay bai xe, moi nhap lai" << endl;
        goto again;
    }
    List.close();
}

void Car_in_simulator(const string& Folder_Path, const string& filename,const string& ID, const string& history) {
    Parking_Lot Parkinglot;
    if (filename == "Exit") return;
    car Car;
    int x, y,parking_spot = 0;
    string id;
    ifstream txt(Folder_Path + "/" + filename + ".txt");
    if (!txt.is_open()) {
        txt.close();
        cout << "khong the mo file " << filename << endl;
        return;
    }
    while (txt >> Parkinglot.Name_Parking_Lot >> Parkinglot.rows >> Parkinglot.cols >> Parkinglot.Is_active >> Parkinglot.Parking_spot) {
        Parkinglot.Parking_lots_matrix.resize(Parkinglot.rows, vector<int>(Parkinglot.cols, 0));
        for (int i = 0; i < Parkinglot.rows; i++) {
            for (int j = 0; j < Parkinglot.cols; j++)
                txt >> Parkinglot.Parking_lots_matrix[i][j];
        }
    }
    txt.close();
    if (Parkinglot.Is_active == false || Parkinglot.Parking_spot <= 0) {    //kiểm tra bãi xe còn trống hay còn hoạt động hay không
        cout << "bai xe khong hop le" << endl;
        return;
    }
    Car.Position_X = Parkinglot.rows;
    Car.Position_Y = Parkinglot.cols;
    for (int i = 0; i < Parkinglot.rows; i++) {
        for (int j = 0; j < Parkinglot.cols; j++) {
            if (i < Car.Position_X && j < Car.Position_Y && Parkinglot.Parking_lots_matrix[i][j] == 0)
            {
                Car.Position_X = i;
                Car.Position_Y = j;
            }
        }
    }
    Parkinglot.Parking_lots_matrix[Car.Position_X][Car.Position_Y]=1;
    Parkinglot.Parking_spot -= 1;
    rand_ID:
    Random_ID(id);
    if (Check_ID(Folder_Path, ID, id)) {
        goto rand_ID;
    }
    Car.ID = id;
    Car.parking_lot = filename;
    Car.test = true;
    Car.Entry_time = chrono::system_clock::now();    //Lấy thời gian hiện tại của xe
    Add_Data_To_File_TXT(Folder_Path, filename, Parkinglot);
    ofstream TXT(Folder_Path + "/" + ID + ".txt", ios::app);
    if (TXT.is_open()) {
        TXT << Car.ID << " " << Car.parking_lot << " " << chrono::system_clock::to_time_t(Car.Entry_time) << " " << chrono::system_clock::to_time_t(Car.Exit_time) << " " << Car.Position_X << " " << Car.Position_Y << " " << Car.test <<" " << endl;
    }
    else {
        TXT.close();
        cout << "khong nhap duoc vao file" << endl;
        return;
    }
    TXT.close();
    ofstream History(Folder_Path + "/" + history + ".txt", ios::app);
    if (History.is_open()) {
        History << "da cho xe co bien so " << Car.ID << " vao bai xe \'" << Car.parking_lot<<"\'";
        if (Car.test) {
            History << " (xe gia lap)" << endl;
        }
        else {
            History << endl;
        }
    }
    else {
        cout << "loi nhap du lieu vao history." << endl;
    }
    History.close();
}

void Delete_Parking_lot(const string& Folder_Path, const string& filename) {
    string link = Folder_Path + "/" + filename + ".txt";
    remove(link.c_str());
}

void Car_out(const string& Folder_Path, const string& ID, const string& history, const string& Save_ID,string &id,bool Auto) {
    car Car;
    vector<string> lines;
    Parking_Lot Parkinglot;
    long long int money;
    cin.ignore(INT_MAX, '\n');
    if (Auto == true) goto func;
    id.clear();
    while (true) {
        cout << "Nhap bien so xe(nhap Exit de thoat): ";
        getline(cin, id);
        if (id == "Exit") return;
        if (id.length() != 9 || id[2] != '-' || (id[4] < 'A') || (id[4] > 'Z')) {
            cout << "Nhap bien so sai, yeu cau nhap lai." << endl;
        }
        else {
            bool KT_So = true;
            for (int i = 0; i < 9; i++) {
                if (i == 2 || i == 4) {
                    continue;
                }
                else {
                    if (id[i] < '0' || id[i] > '9') {
                        KT_So = false;
                        break;
                    }
                }
            }
            if (!KT_So) cout << "Nhap bien so sai, yeu cau nhap lai." << endl;
            else break;
            }
    }
func:
    string ID_path = Folder_Path + "/" + ID + ".txt";
    fstream Temp(ID_path);
    if (!Temp.is_open()) {
        Temp.close();
        cout << "lỗi không mở được file ID"<<endl;
        return;
    }
    string line;
    string temp;
    bool flag=false;
    while (getline(Temp, line)) {
        if (line.substr(0, 9) == id) {
            temp = line;
            flag = true;
        }
        else lines.push_back(line);
    }
    Temp.close();
    if (!flag) {       
        lines.clear();
        cout << "khong tim thay bien so xe!" << endl;
        return;
    }
    ofstream ID_list(ID_path);
    for (const auto& str : lines) {
        
        ID_list << str << endl;
    }
    ID_list.close();
    lines.clear();
    vector<string> details;
    string detail;
    string entrytime;
    string exittime;
    for (int i = 0; i <= temp.size();i++) {
        if (temp[i] != ' ') {
            detail += temp[i];
        }
        else{
            if (!detail.empty()) {
                details.push_back(detail);
            }
            detail.clear();
        }
    }
    Car.ID = details[0];
    Car.parking_lot = details[1];
    money=Money_Calculator(details[2],details[3]);
    if(Auto==false)cout <<"So tien can tra la: "    << money << endl;
    Car.Position_X = stoi(details[4]);
    Car.Position_Y = stoi(details[5]);
    ifstream txt(Folder_Path + "/" + Car.parking_lot + ".txt");
    if (!txt.is_open()) {
        cout << "khong the mo file " << Car.parking_lot << endl;
        txt.close();
        return;
    }
    while (txt >> Parkinglot.Name_Parking_Lot >> Parkinglot.rows >> Parkinglot.cols >> Parkinglot.Is_active >> Parkinglot.Parking_spot) {
        Parkinglot.Parking_lots_matrix.resize(Parkinglot.rows, vector<int>(Parkinglot.cols, 0));
        for (int i = 0; i < Parkinglot.rows; i++) {
            for (int j = 0; j < Parkinglot.cols; j++)
                txt >> Parkinglot.Parking_lots_matrix[i][j];
        }
    }
    txt.close();
    Parkinglot.Parking_lots_matrix[Car.Position_X][Car.Position_Y] = 0;
    Parkinglot.Parking_spot++;
    Add_Data_To_File_TXT(Folder_Path, Car.parking_lot, Parkinglot);
    ofstream History(Folder_Path + "/" + history + ".txt", ios::app);
    if (History.is_open()) {
        History << "Xe co bien so " << Car.ID << " da ra khoi bai \'"<< Car.parking_lot <<"\' voi so tien can tra la: " << money << endl;
    }
    History.close();
    ofstream save(Folder_Path + "/" + Save_ID + ".txt", ios::app);
    if(save.is_open()){
        chrono::system_clock::time_point Entrytime = String_to_Time(details[2]);
        chrono::system_clock::time_point Exittime;
        temp = details[3];
        if (temp[0] == '0') {
            Exittime= chrono::system_clock::now();
        }
        else Exittime= String_to_Time(details[3]);
        string get_in = Time_to_Date(Entrytime);
        string get_out = Time_to_Date(Exittime);
        save << Car.ID << " " << money << " " << get_in << " " << get_out << " " << endl;
    }
    save.close();
}

void Auto_Car_out(const string& Folder_Path, const string& ID, const string& history, const string& Save_ID) {
    car Car;
    string id;
    vector<string> lines;
    string ID_path = Folder_Path + "/" + ID + ".txt";
    fstream Temp(ID_path);
    if (!Temp.is_open()) {
        Temp.close();
        cout << "lỗi không mở được file ID" << endl;
        return;
    }
    string line;
    
    bool flag = false;
    while (getline(Temp, line)) {
        string detail;
        vector<string> details;
        for (int i = 0; i <= line.size(); i++) {
            if (line[i] != ' ') {
                detail += line[i];
            }
            else {
                if (!detail.empty()) {
                    details.push_back(detail);
                }
                detail.clear();
            }
        }
        string test = details[3];
        auto exittime = String_to_Time(details[3]);
        auto now = chrono::system_clock::now();
       
        if (exittime <= now&&test[0]!='0') {
            Car_out(Folder_Path, ID, history, Save_ID,details[0],true);
        }
        details.clear();
    }
    Temp.close();
    
}

void Find_ID(const string& Folder_Path, const string& ID) {
    system("cls");
    cout << "TINH NANG TIM XE" << endl;
    string id;
    cin.ignore(INT_MAX, '\n');
    while (true) {
        cout << "Nhap bien so xe: ";
        getline(cin, id);
        if (id.length() != 9 || id[2] != '-' || (id[4] < 'A') || (id[4] > 'Z')) {
            cout << "Nhap bien so sai, yeu cau nhap lai." << endl;
        }
        else {
            bool KT_So = true;
            for (int i = 0; i < 9; i++) {
                if (i == 2 || i == 4) {
                    continue;
                }
                else {
                    if (id[i] < '0' || id[i] > '9') {
                        KT_So = false;
                        break;
                    }
                }
            }
            if (!KT_So) cout << "Nhap bien so sai, yeu cau nhap lai." << endl;
            else break;
        }
    }
    string ID_path = Folder_Path + "/" + ID + ".txt";
    fstream Temp(ID_path);
    if (!Temp.is_open()) {
        Temp.close();
        cout << "lỗi không mở được file ID" << endl;
        return;
    }
    string line;
    string temp;
    bool flag = false;
    while (getline(Temp, line)) {
        if (line.substr(0, 9) == id) {
            temp = line;
            flag = true;
            break;
        }
    }
    Temp.close();
    if (!flag) {
        cout << "khong tim thay bien so xe!" << endl;
        return;
    }
    vector<string> details;
    string detail;
    for (int i = 0; i <= temp.size(); i++) {
        if (temp[i] != ' ') {
            detail += temp[i];
        }
        else {
            if (!detail.empty()) {
                details.push_back(detail);
            }
            detail.clear();
        }
    }
    cout << "Xe dang nam o bai xe \'" << details[1] << "\' voi vi tri x = " << details[4] << ", y = " << details[5] << endl;
}

void LOG(const string& Folder_Path, const string& history) {
    cout << "Lich su lam viec:" << endl;
    string line;
    fstream log(Folder_Path + "/" + history + ".txt");
    while (getline(log, line)) {
        cout << line << endl;
    }
    log.close();
}

void Parkinglot_data(const string& Folder_Path, const string& filename) {
    string line;
    if (filename == "Exit") return;
    fstream txt(Folder_Path + "/" + filename + ".txt");
    while (getline(txt, line)) {
        cout << line << endl;
    }
    txt.close();
}

void Save_Data(const string& Folder_Path, const string& Save_ID) {
    string line;
    long long int tong=0;
    fstream file(Folder_Path + "/" + Save_ID + ".txt");
    while (getline(file, line)) {
        cout << line << endl;
        string detail;
        vector<string> details;
        for (int i = 0; i <= line.size(); i++) {
            if (line[i] != ' ') {
                detail += line[i];
            }
            else {
                if (!detail.empty()) {
                    details.push_back(detail);
                }
                detail.clear();
            }
        }
        tong += stoll(details[1]);
    }
    file.close();
    cout << "Tong so tien thu duoc la " << tong << " vnd." << endl;
}