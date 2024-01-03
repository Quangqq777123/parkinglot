#include"Create_Folder.h"
#include"core.h"
const string Foldername = "Parkinglots_Data";
const string history = "Logs";
const string ID = "ID_Car";
const string list = "List";
const string Save_ID = "Save";
string temp;
void prestart() {
    createDirectory("Parkinglots_Data");
    Add_File(Foldername, history);
    Add_File(Foldername, ID);
    Add_File(Foldername, list);
    Add_File(Foldername, Save_ID);
  
}
int main() {
    system("color 70");
    srand(time(0));
batdau:
    cout << "Ban co muon bat dau chuong trinh quan ly khong? (Y/N)" << endl;
    char Start; cin >> Start;
    if(Start=='Y'||Start=='y'){
        prestart();
        system("cls");
    }
    else if (Start == 'N' || Start == 'n') {
        cout << "hen gap lai"<<endl;
        return 0;
    }
    else {
        system("cls");
        cout << "nhap sai, nhap lai"<<endl;
        goto batdau;
    }
    while (true) {
        Auto_Car_out(Foldername, ID, history, Save_ID);
       system("cls");
        int choice=0;
        cout << " Chuong Trinh Quan Ly Bai Xe"<<endl;
        cout <<" - Option 1: Tao moi 1 bai xe"<<endl;
        cout <<" - Option 2: Cho xe vao bai xe"<<endl;
        cout <<" - Option 3: Cho xe ra "<<endl;
        cout <<" - Option 4: Gia lap 1 xe vao bai xe"<<endl;
        cout <<" - Option 5: tim xe trong bai"<<endl;
        cout <<" - Option 6: Lich su lam viec" << endl;
        cout <<" - Option 7: Trang thai bai do xe" << endl;
        cout << " - Option 8: Danh sach xe da ra khoi bai" << endl;
        cout << " - Option 9: Exit" << endl;
        cout << endl;
        cout << "Moi nhap lua chon: "; cin >> choice;
        system("cls");
        switch (choice) {
        case 1: {
            Add_Parking_Lot(Foldername, history, list);
            system("pause");
            break;
        }
        case 2: {
            string name= Get_Parking_lot_Name(Foldername,list);
            system("pause");
            Car_in(Foldername, name, ID, history);
            break;
        }
        case 4: {
            string name = Get_Parking_lot_Name(Foldername, list);
            system("pause");
            Car_in_simulator(Foldername, name, ID, history);
            break;
        }
        case 3: {
            Car_out(Foldername, ID, history, Save_ID, temp, false);
            system("pause");
            break;
        }
        case 5: {
            Find_ID(Foldername, ID);
            system("pause");
            break;
        }
        case 6: {
            LOG(Foldername, history);
            system("pause");
            break;
        }
        case 7: {
            string name = Get_Parking_lot_Name(Foldername, list);
            system("pause");
            Parkinglot_data(Foldername, name);
            system("pause");
            break;
        }
        case 8: {
            Save_Data(Foldername, Save_ID);
            system("pause");
            break;
        }
        case 9: return 0;
        default: {
            cout << "Nhap sai, moi nhap lai" << endl; system("pause");
        }
        }
    }
    return 0;
}