#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <queue>
#define NUB 15
#define NUB2 NUB * 2
#define SPACE(i) for (int j = 0; j < i ; j++,(cout << ' '))
#define NEWLINE(i) for (int j = 0; j < i ; j++,(cout << '\n'))
#define WIDTH 1
#define TOP 5
#define BOTTOM 3
#define VER(i) for (int j = 0 ; j < i ; j++,(cout << '|'))
#define HOR(i) for (int j = 0; j < i ; j++,(cout << '_'))
#define SP1 11
#define SP2 18
#define SP3 25
#define ESC 27
#define ENTER 13
#define BACKSPACE 8

using namespace std;

// Vị trí
void GoTo(SHORT x, SHORT y);
// Color
enum class ccolor;
void setColor(ccolor, ccolor);
// Size Console
void SetWindowSize(SHORT w, SHORT h);


// Di chuyển con trỏ tới vị trí  X, Y
void GoTo(SHORT x, SHORT y) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hand, pos);
}
// Set màu sắc cho chữ và nền
enum class ccolor {
	BLACK,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_AQUA,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	BRIGHT_WHITE,
};
void setColor(ccolor highlight, ccolor text) {
	auto hig_color = (int)highlight; // tự động nhận kiểu dữ liệu
	auto text_color = (int)text;
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	auto code = hig_color * 16 + text_color;
	SetConsoleTextAttribute(hand, code);
}


// Hang Hoa
class HangHoa {
	string  maHang = "";
	string	tenHang = "";
	string	noiSanXuat = "";
	string	mauSac = "";
	int giaBan = 0;
	string ngayNhapKho = "";
	int soLuong = 0;
public:

	friend istream& operator >> (istream& in, HangHoa&);
	friend ostream& operator << (ostream& out, const HangHoa&);
	friend ifstream& operator >> (ifstream& in, HangHoa&);
	friend ofstream& operator << (ofstream& out, HangHoa&);

	string getMaHang();
	int getSoLuong();
	string getTenHang();
	void update(int so);
	void setMaHang(const string&);
	string getNoiSanXuat();
	string getMauSac();
	string getNgayNhapKho();
	int getGiaBan();
	int getSoLuongHangHoa();
};
// DON HANG
class DonHang {
	static int STT;
	int _iMa = 1;
	int _iGia = 0;
	string _strTenKhachHang;
	string _strDiaChi;
	string _strSoDienThoai;
	string _strNgayDat;
public:
	vector<string> Code_Ma_HangHoa;
	vector<int> so_Luong_Hang;
	friend istream& operator >> (istream& in, DonHang&);

	int getMa();
	int getGia();
	string getTenKhachHang();
	string getDiaChi();
	string getSoDienThoai();
	string getNgayDat();
};

// Account
class Account {
	string TaiKhoan;
	string MatKhau;
public:
	friend ifstream& operator  >> (ifstream&, Account&);

	void setTaiKhoan();
	string getTaiKhoan() const;

	void setMatKhau(string);
	string getMatKhau() const;

	bool operator  == (const Account&)const;
};

// Program
class Program {

	// lựa chọn của người dùng
	char _cKey = 0;
	int stt = 1;
	// mảng các account, đơn hàng, hàng hóa
	vector <Account> Admin;
	vector<HangHoa> Items;
	queue<DonHang> Orders;
public:
	// lấy admin và hàng từ txt
	void getAdmin();
	void getItems();
	//---------------------------

	void run();
	void menu();

	// menu
	void display();
	void timKiem();
	void datHang();
	void quanLy();

	// Quản lý
	void menuQuanLy();
	void getOrders();
	void quanLyItems();

	// Quản lý hàng hóa
	void addItem();
	void deleteItem();
	void updateItem();

	// UpdateItem
	void updateItem(const string&, int);
	bool foundItem(const string&);

	void ghiFile(DonHang&, const string&, bool);
	void uploadFie(const string&);

	// Hàm support
	bool orderSuccess(DonHang&);
	int log();

	// Kiểm tra số sản phẩm truyền vô có lớn hơn số sản phẩm tối đa của sản phẩm có mã là ... 
	bool checkQuantity(const string&, int);

};


// CHẠY CHƯƠNG TRÌNH	
//---------------------------------------------------
int main() {
	Program program;
	program.getAdmin();
	program.getItems();
	program.run();
	return 0;
}
//----------------------------------------------------
// Hàng hóa
istream& operator >> (istream& in, HangHoa& hang)
{
	SPACE(NUB2); cout << "Ten mat hang: ";
	getline(in, hang.tenHang);
	SPACE(NUB2); cout << "Noi san xuat: ";
	getline(in, hang.noiSanXuat);
	SPACE(NUB2); cout << "Mau sac: ";
	getline(in, hang.mauSac);
	SPACE(NUB2); cout << "Gia ca: ";
	in >> hang.giaBan;
	SPACE(NUB2); cout << "Ngay nhap kho: ";
	in.ignore();
	getline(cin, hang.ngayNhapKho);
	SPACE(NUB2); cout << "So luong: ";
	in >> hang.soLuong;
	return in;
}
ostream& operator << (ostream& out, const HangHoa& hang) {

	SPACE(NUB - WIDTH); VER(WIDTH);
	out << setw(SP1) << hang.maHang; VER(WIDTH);
	out << setw(SP3) << hang.tenHang; VER(WIDTH);
	out << setw(SP2) << hang.noiSanXuat; VER(WIDTH);
	out << setw(SP1) << hang.mauSac; VER(WIDTH);
	out << setw(SP1) << hang.giaBan; VER(WIDTH);
	out << setw(SP2) << hang.ngayNhapKho; VER(WIDTH);
	out << setw(SP1) << hang.soLuong; VER(WIDTH);

	NEWLINE(1);
	SPACE(NUB - WIDTH);
	VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP3); VER(WIDTH); HOR(SP2); VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP2); VER(WIDTH); HOR(SP1); VER(WIDTH);
	NEWLINE(1);
	return out;
}

ifstream& operator >> (ifstream& in, HangHoa& hang) {
	string strtemp = "";
	getline(in, strtemp);

	size_t i = 0;
	for (; strtemp[i] != '~'; i++)
		hang.maHang += strtemp[i];
	i++;

	for (; strtemp[i] != '~'; ++i)
		hang.tenHang += strtemp[i];
	++i;

	for (; strtemp[i] != '~'; i++)
		hang.noiSanXuat += strtemp[i];
	++i;

	for (; strtemp[i] != '~'; i++)
		hang.mauSac += strtemp[i];
	++i;

	string Price = "";
	for (; strtemp[i] != '~'; i++)
		Price += strtemp[i];
	++i;

	hang.giaBan = stoi(Price);

	for (; strtemp[i] != '~'; i++)
		hang.ngayNhapKho += strtemp[i];
	++i;

	string number = "";
	for (; i < strtemp.size(); i++)
		number += strtemp[i];
	hang.soLuong = stoi(number);
	return in;
}
ofstream& operator << (ofstream& out, HangHoa& hang) {
	out << hang.getMaHang() << '~' << hang.getTenHang() << '~' << hang.getNoiSanXuat() << '~' << hang.getMauSac() << '~' << hang.getGiaBan() << '~' << hang.getNgayNhapKho() << '~' << hang.getSoLuongHangHoa();
	return out;
}

string HangHoa::getMaHang() {
	return maHang;
}
string HangHoa::getTenHang() {
	return tenHang;
}
string HangHoa::getNoiSanXuat() {
	return noiSanXuat;
}
string HangHoa::getMauSac() {
	return mauSac;
}
int HangHoa::getGiaBan() {
	return giaBan;
}
string HangHoa::getNgayNhapKho() {
	return ngayNhapKho;
}
int HangHoa::getSoLuong() {
	return soLuong;
}
void HangHoa::setMaHang(const string& ma) {
	maHang = ma;
}
void HangHoa::update(int so) {
	soLuong += so;
}
int HangHoa::getSoLuongHangHoa() {
	return soLuong;
}

// ĐẶT HÀNG
int DonHang::STT = 0;
istream& operator >> (istream& in, DonHang& don) {
	SPACE(NUB2);
	cout << "Ten khach hang: ";
	getline(in, don._strTenKhachHang);
	SPACE(NUB2);
	cout << "Dia chi khach hang: ";
	getline(in, don._strDiaChi);
	SPACE(NUB2);
	cout << "So dien thoai: ";
	in >> don._strSoDienThoai;
	SPACE(NUB2);
	cout << "Ngay dat hang: ";
	in >> don._strNgayDat;
	SPACE(NUB2);
	cout << "Nhap so san pham can mua: ";
	int _iNum;
	cin >> _iNum;
	NEWLINE(2);
	SPACE(NUB); cout << "***Nhap ma tung san pham***\n\n";

	string strCode;
	{
		int i = 0;
		int iProduct;
		while (i < _iNum) {
			std::cin.ignore(256, '\n');

			SPACE(NUB + NUB); cout << "Ma san pham thu " << i + 1 << ": ";
			in >> strCode;
			don.Code_Ma_HangHoa.push_back(strCode);
			SPACE(NUB * 2); cout << "So san pham dat mua: ";
			in >> iProduct;
			don.so_Luong_Hang.push_back(iProduct);
			i++;
		}
	}
	don._iMa = DonHang::STT;
	std::cin.ignore(256, '\n');
	return in;
}

int DonHang::getMa() {
	return _iMa;
}
int DonHang::getGia() {
	return _iGia;
}
string DonHang::getTenKhachHang() {
	return _strTenKhachHang;
}
string DonHang::getDiaChi() {
	return _strDiaChi;
}
string DonHang::getSoDienThoai() {
	return _strSoDienThoai;
}
string DonHang::getNgayDat() {
	return _strNgayDat;
}

// Tài khoản
ifstream& operator >> (ifstream& in, Account& acc) {
	in >> acc.TaiKhoan >> acc.MatKhau;
	return in;
}
void Account::setMatKhau(string mk) {
	MatKhau = mk;
}
string Account::getMatKhau()const {
	return MatKhau;
}
void Account::setTaiKhoan() {
	cin >> TaiKhoan;
}
string Account::getTaiKhoan() const {
	return TaiKhoan;
}
bool Account::operator == (const Account& acc) const {
	return this->TaiKhoan == acc.TaiKhoan && this->MatKhau == acc.MatKhau;
}

// Chương trình
void Program::getAdmin() {
	Account acc;
	ifstream inf;
	inf.open("Admin.txt", ios::in);
	while (!inf.eof()) {
		inf >> acc;
		Admin.push_back(acc);
	}
	inf.close();
}
void Program::getItems() {
	ifstream inf;
	inf.open("HangHoa.txt", ios::in);
	while (!inf.eof()) {
		HangHoa hang;
		inf >> hang;
		Items.push_back(hang);
	}
	inf.close();
}
// Đặt hàng thành công
bool Program::orderSuccess(DonHang& don) {
	for (size_t i = 0; i < don.Code_Ma_HangHoa.size(); i++) {
		if (!foundItem(don.Code_Ma_HangHoa[i]))
			return false;
		else
			if (don.so_Luong_Hang[i] <= 0 && checkQuantity(don.Code_Ma_HangHoa[i], don.so_Luong_Hang[i]))
				return false;
	}
	return true;
}
// Tìm thấy hàng
bool Program::foundItem(const string& ma) {
	for (size_t i = 0; i < Items.size(); i++) {
		if (ma == Items[i].getMaHang())
			return true;
	}
	return false;
}
// Kiểm tra số lượng đặt nhỏ hơn số lượng hàng đang có
bool Program::checkQuantity(const string& ma, int n) {
	for (size_t i = 0; i < Items.size(); i++)
		if (ma == Items[i].getMaHang())
			return Items[i].getSoLuong() <= n;
	return false;
}
// cập nhật số lượng hàng
void Program::updateItem(const string& ma, int product) {
	for (size_t i = 0; i < Items.size(); i++) {
		if (ma == Items[i].getMaHang())
			Items[i].update(product);
		return;
	}
}

// Man hinh chinh 
void Program::run() {
	menu();
}
void Program::menu() {
	system("cls");

	setColor(ccolor::BLACK, ccolor::LIGHT_AQUA);
	NEWLINE(TOP);
	SPACE(NUB2);	cout << "*************************************************\n";
	SPACE(NUB2);	cout << "***";
	setColor(ccolor::BLACK, ccolor::LIGHT_GREEN);
	cout << "                   Menu                    ";
	setColor(ccolor::BLACK, ccolor::LIGHT_AQUA);
	cout << "***\n";
	SPACE(NUB2); cout << "*************************************************\n";
	setColor(ccolor::BLACK, ccolor::BRIGHT_WHITE);
	SPACE(NUB2);	cout << "1. Hien thi thong tin hang hoa.\n";
	SPACE(NUB2);	cout << "2. Tim kiem thong tin hang hoa.\n";
	SPACE(NUB2);	cout << "3. Dat hang.\n";
	SPACE(NUB2);	cout << "4. Quan ly.\n\n";

	NEWLINE(BOTTOM);
	setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
	SPACE(NUB2);  cout << "An \"ESC\" de thoat.\n";

	setColor(ccolor::BLACK, ccolor::WHITE);
	while (_cKey = _getch()) {
		switch (_cKey) {
		case '1':
			display();
			exit(0);
		case'2':
			timKiem();
			exit(0);
		case '3':
			datHang();
			exit(0);
		case '4':
			quanLy();
			exit(0);
		case ESC:
			exit(0);
		default:
			setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
			SPACE(NUB2); cout << "Khong hop le! Vui long nhap lai.\n";
			Sleep(2000);
			menu();
			exit(0);
		}
	}

}

// Chức năng 1: Hiển thị thông tin hàng hóa
void Program::display() {
	setColor(ccolor::BLACK, ccolor::BRIGHT_WHITE);
	system("cls");
	cout << left;
	SPACE(NUB - WIDTH);
	HOR(WIDTH + SP1 + WIDTH + SP3 + WIDTH + SP2 + WIDTH + SP1 + WIDTH + SP1 + WIDTH + SP2 + WIDTH + SP1 + WIDTH);
	NEWLINE(1);
	SPACE(NUB - WIDTH);
	VER(WIDTH);
	setColor(ccolor::BLACK, ccolor::BRIGHT_WHITE);
	cout << setw(SP1) << "Ma hang"; VER(WIDTH);
	cout << setw(SP3) << "Ten hang";        VER(WIDTH);
	cout << setw(SP2) << "Noi san xuat";    VER(WIDTH);
	cout << setw(SP1) << "Mau sac";         VER(WIDTH);
	cout << setw(SP1) << "Gia ban";         VER(WIDTH);
	cout << setw(SP2) << "Ngay nhap kho";   VER(WIDTH);
	cout << setw(SP1) << "So luong";        VER(WIDTH);
	NEWLINE(1);
	SPACE(NUB - WIDTH);
	VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP3); VER(WIDTH); HOR(SP2); VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP2); VER(WIDTH); HOR(SP1); VER(WIDTH);
	NEWLINE(1);

	cout << left;
	for (size_t i = 0; i < Items.size(); i++)
		cout << Items[i];

	NEWLINE(3);
	setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
	SPACE(NUB2); cout << "Nhan \"ESC\" de thoat hoac \"p\" de quay lai.\n";
	while (_cKey = _getch()) {
		if (_cKey == ESC) {
			exit(0);
		}
		else if (_cKey == 'p') {
			menu();
		}
	}
}
// Chức năng 2: Tìm kiếm thông tin hàng hóa
void Program::timKiem() {
	system("cls");

	NEWLINE(TOP);
	string strNameProduct = "";
	setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
	SPACE(NUB); cout << "Nhap ten san pham can tim ";
	setColor(ccolor::BLACK, ccolor::BRIGHT_WHITE);
	getline(cin, strNameProduct);
	NEWLINE(BOTTOM);

	cout << left;
	SPACE(NUB - WIDTH);
	int check = 0;
	for (size_t i = 0; i < Items.size(); i++) {
		if (strNameProduct == Items[i].getTenHang()) {
			check++;
		}
	}
	if (check != 0) {
		setColor(ccolor::BLACK, ccolor::WHITE);
		HOR(WIDTH + SP1 + WIDTH + SP3 + WIDTH + SP2 + WIDTH + SP1 + WIDTH + SP1 + WIDTH + SP2 + WIDTH + SP1 + WIDTH);
		NEWLINE(1);
		SPACE(NUB - WIDTH);                     VER(WIDTH);
		cout << setw(SP1) << "Ma hang";         VER(WIDTH);
		cout << setw(SP3) << "Ten hang";        VER(WIDTH);
		cout << setw(SP2) << "Noi san xuat";    VER(WIDTH);
		cout << setw(SP1) << "Mau sac";         VER(WIDTH);
		cout << setw(SP1) << "Gia ban";         VER(WIDTH);
		cout << setw(SP2) << "Ngay nhap kho";   VER(WIDTH);
		cout << setw(SP1) << "So luong";        VER(WIDTH);
		NEWLINE(1);
		SPACE(NUB - WIDTH);
		VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP3); VER(WIDTH); HOR(SP2); VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP2); VER(WIDTH); HOR(SP1); VER(WIDTH);
		NEWLINE(1);

		for (size_t i = 0; i < Items.size(); i++)
			if (Items[i].getTenHang() == strNameProduct)
				cout << Items[i];
		NEWLINE(3);
	}
	else {
		setColor(ccolor::BLACK, ccolor::BRIGHT_WHITE);
		cout << "Khong tim thay\n";
		NEWLINE(1);
	}
	setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
	SPACE(NUB); cout << "Nhan \"ESC\" de thoat hoac \"ENTER\" de tiep tuc tim kiem hoac \"p\" de quay lai.\n";

	while (_cKey = _getch()) {
		if (_cKey == ESC)
			exit(0);
		else if (_cKey == 'p')
			menu();
		else if (_cKey == ENTER)
			timKiem();
		exit(0);
	}
}
// Chức năng 3: Đặt hàng
void Program::datHang() {
	system("cls");
	NEWLINE(TOP);

	DonHang don;
	cin >> don;

	NEWLINE(3);

	if (orderSuccess(don)) {
		NEWLINE(5);
		setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
		SPACE(NUB2); cout << "Don hang dang duoc xu ly...";
		Orders.push(don);
	}
	else {
		setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
		SPACE(NUB2); cout << "Don hang THAT BAI!!!";
	}

	NEWLINE(3);
	setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
	SPACE(NUB2);
	cout << "Nhan \"ESC\" de thoat hoac \"ENTER\" de tiep tuc dat hang hoac \"p\" de quay lai .\n";

	while (_cKey = _getch()) {
		if (_cKey == ESC)
			exit(0);
		else if (_cKey == 'p')
			menu();
		else if (_cKey == ENTER)
			datHang();
	}
}
void Program::getOrders() {
	system("cls");

	for (size_t i = 0; i < Orders.size(); i++) {
		if (orderSuccess(Orders.front())) {
			ghiFile(Orders.front(), "DonHang.txt", true);
			for (size_t j = 1; j < Orders.front().Code_Ma_HangHoa.size(); j++)
				updateItem(Orders.front().Code_Ma_HangHoa[j], -Orders.front().so_Luong_Hang[j]);
		}
		else
			ghiFile(Orders.front(), "DonHang.txt", false);
		stt++;
		Orders.pop();
	}

	NEWLINE(TOP);
	setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
	SPACE(NUB2); cout << "Da xu ly. Con lai " << Orders.size() << " don hang can xu li.\n";
	NEWLINE(BOTTOM);
	SPACE(NUB2); cout << "An \"ESC\" de thoat hoac \"p\" quay lai man hoac \"ENTER\" de tiep tuc.\n";
	while (_cKey = _getch()) {
		if (_cKey == ESC)
			exit(0);
		else if (_cKey == 'p')
			menuQuanLy();
		else if (_cKey == ENTER)
			getOrders();
	}
}
void Program::ghiFile(DonHang& don, const string& path, bool state) {
	ofstream of;
	of.open("DonHang.txt", ios::out);
	setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
	of << "======DON HANG " << (state ? "THANH CONG" : "THAT BAI") << " ======\n";
	of << "Ma don: " << stt << endl;
	of << "Ten khach hang: " << don.getTenKhachHang() << endl;
	of << "Dia chi: " << don.getDiaChi() << endl;
	of << "Dien thoai: " << don.getSoDienThoai() << endl;
	of << "Ngay dat: " << don.getNgayDat() << endl;
	of << "***Cac san pham dat mua la***" << endl;
	for (size_t i = 0; i < don.Code_Ma_HangHoa.size(); i++)
		of << "   Ma hang hoa " << don.Code_Ma_HangHoa[i] << " voi " << don.so_Luong_Hang[i] << " so luong.\n";
	of << "\n=====================================================" << endl;
	of.close();
}
void Program::uploadFie(const string& path) {
	ofstream of;
	of.open(path, ios::out);
	if (of) {
		for (size_t i = 0; i < Items.size(); i++) {
			of << Items[i];
			if (i != Items.size() - 1)
				of << "\n";
		}
	}
	of.close();
}
// Chức năng 4: Quản lý
void Program::quanLy() {
	system("cls");
	NEWLINE(TOP);
	setColor(ccolor::BLACK, ccolor::LIGHT_AQUA);
	SPACE(NUB2); cout << "*************************************************\n";
	SPACE(NUB2); cout << "***";
	setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
	cout << "             DANG NHAP HE THONG            ";
	setColor(ccolor::BLACK, ccolor::LIGHT_AQUA);
	cout << "***\n";
	SPACE(NUB2); cout << "*************************************************\n";
	NEWLINE(BOTTOM);
	setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
	SPACE(NUB2); cout << "User      : \n";
	SPACE(NUB2); cout << "Password  : \n";
	setColor(ccolor::BLACK, ccolor::WHITE);
	int login = log();
	SPACE(NUB2); cout << "Nhan \"ESC\" de thoat hoac an \"p\" de quay lai man hinh hoac an \"ENTER\" de tiep tuc.\n";
	while (_cKey = _getch()) {
		if (_cKey == ESC)
			exit(0);
		else if (_cKey == 'p')
			menu();
		else if (_cKey == ENTER)
			if (login == 2)
				menuQuanLy();
			else if (login == 1)
				quanLy();
			else
				exit(0);
	}
}
int Program::log() {
	Account acc;
	GoTo(NUB2 + 15, TOP + BOTTOM + 3);
	acc.setTaiKhoan();
	GoTo(NUB2 + 15, TOP + BOTTOM + 3 + 1);
	acc.setMatKhau("");

	while (true) {
		_cKey = _getch();
		if (_cKey == BACKSPACE) {
			string new_Pass = acc.getMatKhau();
			if (new_Pass != "") {
				new_Pass.pop_back();
				cout << "\b \b";
			}
			acc.setMatKhau(new_Pass);
		}
		else if (isspace(_cKey)) {
			break;
		}
		else {
			acc.setMatKhau(acc.getMatKhau() + _cKey);
			cout << '*';
		}
	}

	setColor(ccolor::BLACK, ccolor::YELLOW);
	NEWLINE(3);

	static int so_lan_nhap = 3;
	bool success = false;
	for (size_t i = 0; i < Admin.size(); i++) {
		if (Admin[i] == acc) {
			success = true;
			break;
		}
	}
	if (success && so_lan_nhap) {
		setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
		SPACE(NUB2); cout << "Dang nhap thanh cong.";
		Sleep(1000);
		menuQuanLy();
		NEWLINE(6);
		return 2;
	}
	else if (success && so_lan_nhap == 0) {
		setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
		SPACE(NUB2); cout << "Dang nhap thanh cong.";
		Sleep(1000);
		menuQuanLy();
		NEWLINE(6);
		return 2;
	}
	else if (!success) {
		(so_lan_nhap > 0) ? so_lan_nhap-- : so_lan_nhap;
		setColor(ccolor::BLACK, ccolor::RED);
		SPACE(NUB2); cout << "Dang nhap khong thang cong.\n";
		SPACE(NUB2); cout << "So lan nhap lai: " << so_lan_nhap;
		NEWLINE(6);
		setColor(ccolor::BLACK, ccolor::WHITE);
		if (!success && so_lan_nhap == 0) {
			setColor(ccolor::BLACK, ccolor::RED);
			SPACE(NUB2); cout << "Nhap sai so lan cho phep roi *_*.\n";
			SPACE(NUB2); cout << "BYE!!!";
			Sleep(2000);
			exit(0);
		}
		return 1;
	}
	return 0;
}

// quan ly
void Program::menuQuanLy() {
	system("cls");
	NEWLINE(TOP);
	setColor(ccolor::BLACK, ccolor::LIGHT_AQUA);
	SPACE(NUB2); cout << "*************************************************\n";
	SPACE(NUB2); cout << "***";
	setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
	cout << "                Menu Quan Ly               ";
	setColor(ccolor::BLACK, ccolor::LIGHT_AQUA);
	cout << "***\n";
	SPACE(NUB2); cout << "*************************************************\n";
	setColor(ccolor::BLACK, ccolor::BRIGHT_WHITE);
	NEWLINE(BOTTOM);
	SPACE(NUB2); cout << "1. Xu ly don hang.\n";
	SPACE(NUB2); cout << "2. Quan ly hang hoa.\n";
	NEWLINE(BOTTOM);
	setColor(ccolor::BLACK, ccolor::LIGHT_YELLOW);
	SPACE(NUB2); cout << "Nhan \"ESC\" de thoat hoac \"p\" de quay lai man hinh chinh.\n";

	while (_cKey = _getch()) {
		switch (_cKey) {
		case'1':
			getOrders();
			exit(0);
		case'2':
			quanLyItems();
			exit(0);
		case'p':
			menu();
			exit(0);
		case ESC:
			exit(0);
		default:
			setColor(ccolor::BLACK, ccolor::LIGHT_RED);
			SPACE(NUB2); cout << "Du lieu khong hop le!";
			Sleep(2000);
			menuQuanLy();
			exit(0);
		}
	}

}
void Program::quanLyItems() {
	system("cls");
	NEWLINE(TOP);
	setColor(ccolor::BLACK, ccolor::LIGHT_AQUA);
	SPACE(NUB2); cout << "*************************************************\n";
	SPACE(NUB2); cout << "***";
	setColor(ccolor::BLACK, ccolor::LIGHT_GREEN);
	cout << "              Quan Ly Hang Hoa            ";
	setColor(ccolor::BLACK, ccolor::LIGHT_AQUA);
	cout << "***\n";
	SPACE(NUB2); cout << "*************************************************\n";
	setColor(ccolor::BLACK, ccolor::BRIGHT_WHITE);
	NEWLINE(BOTTOM);
	SPACE(NUB2); cout << "1. Them hang moi,\n";
	SPACE(NUB2); cout << "2. Xoa hang.\n";
	SPACE(NUB2); cout << "3. Cap nhat so luong hang.\n";
	NEWLINE(BOTTOM);
	SPACE(NUB2); cout << "An \"ESC\" de thoat hoac \"p\" de quay lai.\n";
	while (_cKey = _getch()) {
		switch (_cKey) {
		case'1':
			addItem();
			exit(0);
		case'2':
			deleteItem();
			exit(0);
		case '3':
			updateItem();
			exit(0);
		case 'p':
			menuQuanLy();
			exit(0);
		case ESC:
			exit(0);
		default:
			setColor(ccolor::BLACK, ccolor::LIGHT_RED);
			SPACE(NUB2); cout << "Du lieu khong hop le!";
			Sleep(2000);
			quanLyItems();
			exit(0);
		}
	}
}
// cac chuc nang cua quan ly hang hoa
	// chuc nang 1: them hang
void Program::addItem() {
	system("cls");
	NEWLINE(TOP);

	HangHoa hang;
	string strCode;

	SPACE(NUB2); cout << "Ma hang ";
	cin >> strCode;
	cin.ignore(225, '\n');
	if (foundItem(strCode)) {
		NEWLINE(BOTTOM);
		SPACE(NUB2);
		cout << "Ma hang da ton tai.\n";
	}
	else {
		cin >> hang;
		hang.setMaHang(strCode);
		Items.push_back(hang);
		NEWLINE(3);
		setColor(ccolor::BLACK, ccolor::GREEN);
		SPACE(NUB2);  cout << "Them thanh cong";
	}

	uploadFie("HangHoa.txt");
	NEWLINE(BOTTOM);
	SPACE(NUB); cout << "Nhan \"ESC\" de thoat hoac \"p\" de quay lai hoac \"ENTER\" de tiep tuc.";
	while (_cKey = _getch()) {
		if (_cKey == ESC)
			exit(0);
		else if (_cKey == 'p')
			quanLyItems();
		else if (_cKey == ENTER)
			addItem();
	}
}
// chuc nang 2: xoa hang
void Program::deleteItem() {
	system("cls");
	NEWLINE(TOP);
	SPACE(NUB2); cout << "Ma hang: ";
	string strCode;
	cin >> strCode;
	bool success = false;
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i].getMaHang() == strCode) {
			Items.erase(Items.begin() + i);
			success = true;
		}
	}
	NEWLINE(BOTTOM);
	if (success) {
		SPACE(NUB2); cout << "!!!Da xoa!!!";
		uploadFie("HangHoa.txt");
		NEWLINE(BOTTOM);
	}
	else {
		cout << "Khong ton tai.";
	}

	SPACE(NUB2); cout << "An \"ESC\" de thoat hoac \"p\" de quay lai hoac \"ENTER\" de tiep tuc.\n";
	while (_cKey = _getch()) {
		if (_cKey == ESC)
			exit(0);
		else if (_cKey == 'p')
			quanLyItems();
		else if (_cKey == ENTER)
			deleteItem();
	}
}
// Chuc nang 3: cap nhat
void Program::updateItem() {
	system("cls");
	NEWLINE(TOP);
	SPACE(NUB2);
	cout << "Ma hang muon cap nhat ";
	string strCode;
	cin >> strCode;
	int i_Product = 0;
	SPACE(NUB2); cout << "1. Tang\n";
	SPACE(NUB2); cout << "2. Giam\n";
	bool flag = false;
	while (_cKey = _getch()) {
		if (_cKey == '1' || _cKey == '2') {
			SPACE(NUB2);
			flag = _cKey == '1';
			cout << ((flag) ? "Tang them: " : "Giam xuong: ");
			break;
		}
	}
	cin >> i_Product;
	bool success = false;
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i].getMaHang() == strCode) {
			success = true;
			flag ? Items[i].update(i_Product) : Items[i].update(-i_Product);
		}
	}
	uploadFie("HangHoa.txt");
	NEWLINE(BOTTOM);
	if (success) {
		SPACE(NUB2);
		cout << "!!!!THANH CONG!!!!";
	}
	NEWLINE(BOTTOM);
	SPACE(NUB);
	cout << "Nhan \"ESC\" de thoat hoac \"p\" de quay lai.";
	while (_cKey = _getch()) {
		if (_cKey == ESC)
			exit(0);
		if (_cKey == 'p')
			quanLyItems();
	}
}
