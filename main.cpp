
// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
// Here we will create a new Structure of Data designed for Employees
struct Employees {
    string date;
    string name;
    string ssn;
    double hours,pay,overtime,doublepay,gross,deductions,net;
};

// The first thing we need for our program is a function that ask the user the name of the file that he or she wants to open
// and how many employees he or she wants in the roster.
// We will call this function "File".

void File (string &file, int &size){
    int repeat;
    do {
        cout << " Please, enter the name of the file you want to open."
                "\n This file must include the extension of his data type. "
                "\n For example: (Nomina.dat) ";
        cin >> file;
        ifstream data(file);
        if (data.is_open()) {
            cout << "\n Good, we were able to open the file.";
            repeat =0;
            cout << "\n Now, how many employees do you want to procees?: ";
            cin >> size;
        }
        else {
            cout << "\n ups, cant find the file \n" << file;
            repeat = 1;
        }
    }while (repeat == 1);
}
// Next thing we should do is to ask the user for the name of the file the program is going to create
// This function is going to be called "Nomina_Name" because well... that's what it does.
void Nomina_Name(ofstream &nomina,string &Nomina){
    cout << "\n We need the name of the file that you want to create: ";
    cin >> Nomina;
    nomina.open(Nomina);
}
// Now we have both the name of the file that we will retrieve the data from and the name of the file we will create.

// We should proceed to read the data of the file, lets create a function called read that does this.
void Read(ifstream &data,Employees &E1){
    data >> E1.date >> E1.name >> E1.ssn >> E1.hours >> E1.pay;
}
// Before the calculations and displaying the info we need the layout of the paper.
// The following function named "Layout" is going to create it.

void Layout (ofstream &nomina, string &nominaname){
    // Layout del Papel
    // Layout del papel y de la consola

    nomina << right << setw(100) << "Nomina de la Empresa\n\n";
    cout << right << setw(100) << "Nomina de la Empresa\n\n";
    nomina << left << setw(18) << "Fecha";
    cout << left << setw(18) << "Fecha";
    nomina << left << setw(18) << "Nombre";
    cout << left << setw(18) << "Nombre";
    nomina << left << setw(18) << "SSN";
    cout << left << setw(18) << "SSN";
    nomina << left << setw(18) << "Horas/semana";
    cout << left << setw(18) << "Horas/semana";
    nomina << left << setw(18) << "Salario/hora";
    cout << left << setw(18) << "Salario/hora";
    nomina << left << setw(18) << "Horas Extra";
    cout << left << setw(18) << "Horas Extra";
    nomina << left << setw(18) << "Total Bruto";
    cout << left << setw(18) << "Total Bruto";
    nomina << left << setw(18) << "deducciones";
    cout << left << setw(18) << "deducciones";
    nomina << left << setw(18) << "Neto" << endl;
    cout << left << setw(18) << "Neto" << endl;
    for (int i = 0; i <= 160; i++){
        nomina << left << setw (0) << "=";
        cout << left << setw (0) << "=";
    }
    nomina << left << endl;
    cout << left << endl;
}
// Now we have everything we need, lets begin calculating things for the rooster
// Lets do a function that calculates overtime
void Overtime (Employees &E){
    if (E.hours > 40) {
        E.overtime = E.hours - 40;
        E.hours = E.hours - E.overtime;
    }
    else{
        E.overtime = 0;
    }
}
// Now that we have the overtime lets calculate the pay
// The following function calculates the pay based on the overtime
void Overtime_Pay(Employees &E){
    E.doublepay = E.overtime * (E.pay*2);
}
// lets calculate the gross pay
void Gross (Employees &E){
    double holder;
    holder = E.hours * E.pay;
    E.gross = holder + E.doublepay;
}
// This Function calculates the deductions of the employees
void Deductions (Employees &E){
    E.deductions = (E.gross * 0.18);
}
// This Function calculates the net payment of the employees
void Net (Employees &E){
    E.net = E.gross - E.deductions;
}
// This Function is an accumulator for the total of the roster
void Total (Employees E, double &total){
    total = total + E.gross;
}
// Now we have everything the only thing we need to do is to create a function that displays the information
// This function will be called " Display".
void Display(ofstream &file,Employees E1){
    file << left << setw(18) << E1.date;
    cout << left << setw(18) << E1.date;
    file << left << setw(18) << E1.name;
    cout << left << setw(18) << E1.name;
    file << left << setw(18) << E1.ssn;
    cout << left << setw(18) << E1.ssn;
    file << left << setw(18) << E1.hours + E1.overtime;
    cout << left << setw(18) << E1.hours + E1.overtime;
    file << left << setw(18) << E1.pay;
    cout << left << setw(18) << E1.pay;
    file << left << setw(18) << E1.overtime;
    cout << left << setw(18) << E1.overtime;
    file << left << setw(18) << E1.gross;
    cout << left << setw(18) << E1.gross;
    file << left << setw(18) << E1.deductions;
    cout << left << setw(18) << E1.deductions;
    file << left << setw(18) << E1.net << endl;
    cout << left << setw(18) << E1.net << endl;
}
// Here we create a function that returns the index of the specific employee you are looking for.
int filter (Employees E1[], int size){
    char reply = 'y';
    string name;
    int i = 0;
    bool found = false;
    int f_index = -1;

    cout << " Do you want to filter by name? (Y or N) ";
    cin >> reply;
    if (reply == 'y'|| reply == 'Y'){
        cout << " wich name do you want to search for? ";
        cin >> name;
        while (i < size && !found){
            if (name == E1[i].name){
                f_index = i;
                found = true;
            }
            i++;
        }
        return f_index;
    }
    else{
        return -1;
    }
}
// Here we create a function that sort the arrays by the order of the names
void Ssort (Employees E1[], int size){
    int minInd;
    Employees min;
    for(int start = 0; start < (size-1); start++){
        min.name = E1[start].name;
        minInd = start;
        for(int i = start+1; i<size; i++){
            if(E1[i].name<min.name){
                min.name = E1[i].name;
                minInd = i;
                swap(E1[minInd],E1[start]);
            }
        }
    }
}
// This function just displays and write in a file the total of the roster.
void Total_N (ofstream &file,double total){
    cout << "\nEl total de la nomina es = "<< total << endl;
    file << "\nEl total de la nomina es = "<< total << endl;
}
// This function displays a menu on the screen for the user to decide what to do next.
void Menu (char &selection){
    cout << "\n What do you want to do?";
    cout << "\n A. Select another file";
    cout << "\n B. Filter by name";
    cout << "\n C. Sort by name";
    cout << "\n D. Exit";
    cout << "\n Please, enter the character of yore choice: ";
    cin >> selection;
}
// This function ask the user if he or she wants to repeat the program
void Repeat (string &repeat){
    cout << "\n Do you want to input another file ( If so please enter yes) ";
    cin >> repeat;
}
// This is were the program starts
int main(){
    //Here we are declaring the variables that our program is going to use
    string file,Nomina;
    Employees* E1 = nullptr;
    int i = 0, size,find;
    char Selection;
    string repeat;
    double total =0;
    // This is the body of the whole program.
    do {
        File(file,size);
        E1 = new Employees [size];
        ofstream nominaf;
        Nomina_Name(nominaf,Nomina);
        Layout(nominaf, Nomina);
        ifstream data(file);
        while ( i < size && !data.eof()) {
            Read(dynamic_cast<ifstream &>(data), E1[i]);
            Overtime(E1[i]);
            Overtime_Pay(E1[i]);
            Gross(E1[i]);
            Deductions(E1[i]);
            Net(E1[i]);
            Total(E1[i], total);
            Display(nominaf, E1[i]);
            i++;
        }
        Total_N(nominaf, total);
        // Here we call the Menu function and execute the correct functions based on the user selection
        Menu(Selection);
        if ( Selection == 'a' || Selection == 'A'){
            Repeat(repeat);
        }
        else if (Selection == 'b'|| Selection == 'B'){
            find = filter(E1,size);
            if (find == -1){
                cout << "\n The name you're looking for isn't in this file\n ";
                system("pause");
            }
            else {
                Layout(nominaf, Nomina);
                Display(nominaf, E1[find]);
                Total_N(nominaf,total);
                Repeat(repeat);
            }
        }
        else if ( Selection == 'c'|| Selection == 'C'){
            Ssort(E1,i);
            Layout(nominaf, Nomina);
            int t = 0;
            while ( t < i){
            Display(nominaf, E1[t]);
            t++;}
            Total_N(nominaf,total);
            Repeat(repeat);
        }
        else if(Selection == 'd'|| Selection == 'D') {
            return 0;
        }
        // here we restore some values so that when we re-run the program it wont cause any trouble.
        nominaf.close();
        i = 0;
        total = 0;
        delete E1;
        E1 = nullptr;
    } while (repeat == "yes");

    return 0;
}