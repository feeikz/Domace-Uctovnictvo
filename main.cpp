#include "main.h"

/**
 * @brief Program na spravovanie financii domacnosti.
 * @file main.cpp
 * @author Frederik Zajac
 * @mainpage LOGIN ZAJ0098 - Domaci ucetnitvi
 */


/** @class InputDate
 *  @brief Trieda obsahujuca parametre datumu
 *  @param InputDate.day           parameter dna
 *  @param InputDate.month         parameter mesiaca
 *  @param InputDate.rok           parameter roku
 */
class InputDate {
public:
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

/** @class Invoice
 *  @brief Trieda obsahujuca parametre vstupneho suboru, ktory moze uz existovat, alebo je mozne ho vytvorit
 *  @param Invoice.ID           Identifikacne cislo urcene pre kazdy zaznam v subore
 *  @param Invoice.type         Druh zaznamu v subore (Prijem/Vydaj)
 *  @param Invoice.category     Kategoria zaznamu v subore
 *  @param Invoice.amount       Ciastka zaznamu
 *  @param Invoice.date         Datum zaznamu vychadzajuci z parametrou triedy InputDate

 */
class Invoice{
public:
    unsigned int ID;
    string type;
    string category;
    double amount;
    InputDate date;
};

/**
 * @brief Funkcia ktora ziskava vstup od uzivatela
 * @param input - vstup od uzivatela
 * @return - vracia retazec "Prijem" alebo "Vydaj"
 */
string EnterType(){
    char input;
	cout<<"Zadajte typ zaznamu (P)rijem alebo (V)ydaj:\t";

	cin>>input;
	cin.clear();
	cin.ignore(10000,'\n');

	input=toupper(input);


	while((input!='P'&&input!='V')||(cin.fail())){
		cout<<"Zadali ste zly vstup. Opakujte vyber v tvare (P/V)\t";
		cin>>input;
		cin.clear();
        cin.ignore(10000, '\n');

		input = toupper(input);
	}

	if(input=='P')
		return "Prijem";
	else
		return "Vydaj";
}

/**
 * @brief Funkcia ktora ziskava vstup od uzivatela
 * @param InvoiceCategory - staticky alokovane pole
 * @param input - vstup od uzivatela
 * @return - vracia vybranu kategoriu
 */

string EnterCategory(){
	string InvoiceCategory[]={"vyplata","inkaso","strava","oblecenie","cestovanie","ostatne"};

	cout<<"        *Kategorie*          "<<endl;
	cout<<"------------------------------"<<endl;

	for (int i=0;i<6;i++){
			cout<<i+1<< ") "<<InvoiceCategory[i]<<endl;
    }

	cout<<"Vyberte si kategoriu vasho zaznamu (1 - 6):"<<endl;

	unsigned int input;
	cin>>input;
	cin.clear();
    cin.ignore(10000,'\n');

	while(cin.fail()||input<1||input>6){
		cout<<"Nespravna odpoved. Zadajte cislo kategorie (1 - 6):"<<endl;
		cin>>input;
		cin.clear();
        cin.ignore(10000,'\n');
	}
	return InvoiceCategory[input-1];
}
/**
 * @brief Funkcia ktora ziskava vstup od uzivatela
 * @param input - vstup od uzivatela
 * @return - vracia zadanu sumu
 */
double EnterAmount(){
    double input;

	cout<<"Zadejte castku v EUR, ktoru chcete vlozit :\t";
	cin>>input;
	while(cin.fail()||input<= 0){
		cout<<"Zadali ste nespravnu ciastku. Zadajte znovu (v EUR):\t";
		cin>>input;
	}
	return input;
}

/**
 * @brief Funkcia ktora ziskava vstup od uzivatela
 * @param input - vstup od uzivatela
 * @return - vracia zadanu sumu
 */
string EnterDate(){
    bool switcher=true;
	string input;
	cout<<"Zadajte datum zaznamu (DD.MM.RRRR):\t";

	while(switcher){
		cin>>input;
        cin.clear();
        cin.ignore(10000,'\n');

		while(input.length()!=10||(cin.fail())){
			cout<<"Zadali ste datum v nespravnom formate. Zadajte prosim znovu (DD.MM.RRRR):\t";
			cin>>input;
			cin.clear();
            cin.ignore(10000,'\n');
		}

		if((atoi((input.substr(6,4)).c_str()))<1900||(atoi((input.substr(6,4)).c_str()))>2100||cin.fail()){
			cout<<"Rok ste zadali mimo povoleny rozsah (1900 - 2100). Zadajte prosim znovu (DD.MM.RRRR):\t";
        }
        else if((atoi((input.substr(0,2)).c_str()))==0){
			cout<<"Den ste zadali mimo povoleny rozsah. Zadajte prosim znovu (DD.MM.RRRR):\t";
        }
		else{
			switch (atoi((input.substr(3,2)).c_str())){
			case 1: case 3: case 5: case 7: case 8: case 10:
			case 12:{
				if(atoi((input.substr(0,2)).c_str())>31)
					cout<<"Tento mesiac ma maximalne 31 dni. Zadajte znovu prosim (DD.MM.RRRR):\t";
				else switcher=false;
			}break;
			case 4: case 6: case 9: case 11:{
				if (atoi((input.substr(0,2)).c_str())>30)
					cout<<"Tento mesiac ma maximalne 30 dni. Zadajte znovu prosim (DD.MM.RRRR):\t";
				else switcher=false;
			}break;
				case 2:{
				if(atoi((input.substr(0,2)).c_str())==29){
					if(atoi((input.substr(7,4)).c_str())%4!=0)
							cout<<"Tento rok nieje prestupny. Zadajte znovu prosim (DD.MM.RRRR):\t";
						else switcher=false;
				}
				else if(atoi((input.substr(0,2)).c_str())>28)
					cout<<"Tento mesiac ma maximalne 28 alebo 29 dni. Zadajte znovu prosim (DD.MM.RRRR):\t";
				else switcher=false;
			}break;
			default:
				cout<<"Zadali ste mesiac mimo rozsah. Zadajte znovu prosim (DD.MM.RRRR):\t";
			}
		}
	}
	return input;
}

/**
 * @brief Funkcia vytvara zaznam do suboru
 * @param type - premmena do ktorej sa zapise navratova hodnota z funkcie EnterType()
 * @param category - premmena do ktorej sa zapise navratova hodnota z funkcie  EnterCategory()
 * @param value - premmena do ktorej sa zapise navratova hodnota z funkcie  EnterAmount()
 * @param date - premmena do ktorej sa zapise navratova hodnota z funkcie  EnterDate()
 */
void Add(const bool switcher, string File,int contentCount, Invoice add[])
{
	unsigned int ID=add[contentCount - 1].ID + 1;
	string type=EnterType();
	string category=EnterCategory();
	double value=EnterAmount();
	string date=EnterDate();

	ofstream out(File.c_str());
	for(int i= 0;i<contentCount;i++)
	{
		out<<add[i].ID <<";"<<add[i].type<<";"<< add[i].category<<";"<< add[i].amount << ";";
		if (add[i].date.day<10){
			out<<"0";
		}

		out<<add[i].date.day <<".";
		if (add[i].date.month<10){
			out<<"0";
		}

		out<<add[i].date.month<<"."<<add[i].date.year;
		out<<endl;
	}
	out <<ID<<";"<<type<<";"<<category<<";"<<value<<";"<<date;
	out.close();
}


/**
 * @brief Funkcia na otvaranie alebo vytvaranie vstupnych suborov.
 */
bool open_csv_file(string &Folder,string &File,bool noFile){
    if(!noFile){
       cout<<"Zadajte nazov csv suboru:\t";
       cin>>File;
       cin.clear();
       cin.ignore(10000,'\n');
    }

    ifstream invoiceFile((Folder+File+".csv").c_str());

    if(!(invoiceFile.is_open())){
        cout<<"Zadali ste zly nazov suboru."<<endl;
        cout<<"Chcete vytvorit subor? Zadajte (A)no alebo (N)ie.\t";

        char choice;
        cin>>choice;
        cin.clear();
        cin.ignore(10000,'\n');
        char upperchoice=toupper(choice);

        while ((upperchoice!='A'&&upperchoice!='N')||(cin.fail())){
			cout<<"*ERROR* Zopakujte pokus.\t";
			cin>>choice;
            cin.clear();
            cin.ignore(10000,'\n');
			upperchoice=toupper(choice);
		}
        if(upperchoice=='N'){
            return 0;
		}
        else{
			string invoiceFile=(Folder+File+".csv");
			cout<<"Vytvorte zaznam (Prijem/Vydaj)"<<endl;
			Invoice *NewTally=new Invoice[1];
			Add(true,invoiceFile,0,NewTally);
		}
    }
    else {
        cout<<"Subor otvoreny."<<endl;
        invoiceFile.close();
        return true;
    }
}

/**
 * @brief Funkcia ktora vracia riadky zaznamov zo vstupneho suboru.
 * @param counter - pocet riadkov/zaznamov suboru
 * @param line - pomocna premenna na citanie riadku
 * @return - vracia pocet riadkov/zaznamov suboru
 */
unsigned int LinesCounter(ifstream &File){
    int counter=0;
    string line;

    while(getline(File, line)){
        if((count(line.begin(),line.end(),';'))==4)
            counter++;
    }
    File.clear();
	File.seekg(0);

    return counter;
}

/**
 * @brief Funkcia ktora uklada data zo suboru do databazy
 * @param countLines - pocet riadkov/zaznamov v databaze
 * @param line - pomocna premenna na citanie riadku
 * @param ID,day,month,year,type,category,value - atributy databazy
 */
bool AddToDatabase(ifstream &File,Invoice invoiceList[])
{
    int countLines = 0;
	string line;

	while (getline(File, line)){
		int ID;
		int day;
		int month;
		int year;

		string type;
		string invoiceCategory;
		double value;

		if((count(line.begin(),line.end(),';'))==4){
			ID=atoi((line.substr(0, line.find(";"))).c_str());
			line.erase(0,line.find(";")+1);

			type=line.substr(0, line.find(";"));
			line.erase(0,line.find(";")+1);

			invoiceCategory=line.substr(0, line.find(";"));
			line.erase(0,line.find(";")+1);

			value=atoi((line.substr(0, line.find(";"))).c_str());
			line.erase(0,line.find(";")+1);

			day=atoi((line.substr(0, line.find("."))).c_str());
			line.erase(0,line.find(".")+1);

			month=atoi((line.substr(0,line.find("."))).c_str());
			line.erase(0, line.find(".")+1);

			year = atoi(line.c_str());
			line.erase();
		}

		if(type!="Vydaj"&&type!="Prijem"){
			cout <<"Nespravny typ zaznamu Prijmu/Vydaju v ID: "<<ID<<endl;
			return false;
		}

		bool RightCategory=false;
		string InvoiceCategoryName[]={"vyplata","inkaso","strava","oblecenie","cestovanie","ostatne"};

		for (int i=0;i<6;i++){
			if (invoiceCategory==InvoiceCategoryName[i]){RightCategory=true;}
		}

		if(!RightCategory){
			cout<<"Nespravny typ kategorie v ID: "<<ID<<endl;
			cout<<"Koniec programu:"<<endl;

			return false;
		}

		if(value<=0){
			cout<<"Nespravna ciastka v ID: "<<ID<<endl;
			return false;
		}

		if(year>2100||year<2018){
			cout<<"Zadany rok je mimo rozsah (2018 - 2100) v ID: "<<ID<<" Zadany rok: "<<year<<endl;
			return false;
		}

		bool date = false;

		switch (month){
		case 1: case 3: case 5: case 7: case 8: case 10:
		case 12:{
			if (day>31)date=true;
		}break;
		case 4: case 6: case 9: case 11:{
			if(day>30)date=true;
		}break;
		case 2:{
			if (day==29){
				if(year%100==0){if(year%400!=0)date=true;}
				else if (year%4!=0)date = true;
			}
			else if(day>28)date=true;
		}break;
		default:
			date=true;
		}
		if(date||day==0){
			cout<<"Datum zaznamu neexistuje v ID: "<<ID<<endl;
			return false;
		}
		invoiceList[countLines].ID=ID;
		invoiceList[countLines].type=type;
		invoiceList[countLines].category=invoiceCategory;
		invoiceList[countLines].amount=value;
		invoiceList[countLines].date.day=day;
		invoiceList[countLines].date.month=month;
		invoiceList[countLines].date.year=year;
		countLines++;
	}
	return true;
}

/**
 * @brief Funkcia obsahujuca hlavne MENU
 * @param choice - vstup od uzivatela
 * @return - vracia vstup od uzivatela
 */

int MENU(int contentCount,const string File){
 	cout<<"-------------------------------------------------------------------------------"<<endl;
	cout<<endl;

	cout<<"|MENU| (Vyberte jednu z moznosti 1-4):"<<endl;
	cout<<"..............................................................................."<<endl;
	cout<<"      1. Vypis informacii"<<endl;
	cout<<"      2. Editovat"<<endl;
	cout<<"      3. Zmenit vstupny subor"<<endl;
	cout<<"      4. Ukoncit program"<<endl;
	cout<<"..............................................................................."<<endl;

	int choice;
	cin>>choice;
	cin.clear();
    cin.ignore(10000,'\n');

	while(choice<1||choice>4||cin.fail()){
        if(choice==2&&File=="faktura_backup"){
            cout<<"Zalozny subor sa z bezpecnostnych dovodov needituje. Opakujte prosím: \t";
        }else cout<<"Nespravna odpoved. Opakujte prosim :\t";

        cin>>choice;
        cin.clear();
        cin.ignore(10000,'\n');
	}
	return choice;
}

/**
 * @brief Funkcia vypisuje data do konzole.
 * @param ID,day,month,year,type,category,value - atributy databazy
 */
void showData(Invoice invoiceList[],int contentCount)
{

	cout<<endl<<"-------------------------------------------------------------------------------"<<endl;
	printf("%3s %8s %20s %20s %12s", "ID", "TYP", "KATEGORIA", "CIASTKA (EUR)", "DATUM");
	cout<<endl << "-------------------------------------------------------------------------------"<<endl;

	for(int i=0;i<contentCount;i++)
	{
		unsigned int ID=invoiceList[i].ID;
		string type=invoiceList[i].type;
		string invoiceCategory=invoiceList[i].category;
		double value=invoiceList[i].amount;
		int day=invoiceList[i].date.day;
		int month=invoiceList[i].date.month;
		int year=invoiceList[i].date.year;

        printf("%3u %10s %18s %15.2f  ", ID, type.c_str(), invoiceCategory.c_str(), value);
        if(day<10){cout<<"       0"<<day;}
        else {cout<<"       "<<day;}
		cout<<".";

		if(month<10)
			cout<<"0";
		cout<<month<<"."<<year<< endl;
	}
}

/**
 * @brief Funkcia odstrani zaznam podla uzivatelovho vstupu a nasledne vypise vsetky existujuce zaznamy
 * @param input - vstup od uzivatela
 */
void removeData(Invoice invoiceList[],unsigned int contentCount,string File){
    showData(invoiceList,contentCount);

    cout<<endl;
    cout<<"Zadajte ID zaznamu, ktory chcete vymazat.\t"<<endl;
    unsigned int ID;

    bool tmp=false;
    while(!tmp){
        unsigned int input;
        cin>>input;
        cin.clear();
        cin.ignore(10000,'\n');

        if(!cin.fail()){
            for(unsigned int i=0;i<contentCount;i++){
                if(input==invoiceList[i].ID){
                    ID=i;
                    tmp=true;
                    break;
                }
            }
        }
        if(!tmp){
            cout<<"Zadane ID sa nenachadza v databaze. Zadajte znovu.\t";
        }
    }

    ofstream editFile(File.c_str());
    for(unsigned int i=0;i<contentCount;i++){
        if(i!=ID){
            editFile<<invoiceList[i].ID<<";"<<invoiceList[i].type<<";"<<invoiceList[i].category<<";"<<invoiceList[i].amount<<";";

            if(invoiceList[i].date.day<10){editFile<<"0";}
            editFile<<invoiceList[i].date.day<<".";
            if(invoiceList[i].date.month<10){editFile<<"0";}
            editFile<<invoiceList[i].date.month<<"."<<invoiceList[i].date.year;

            if(i+1!=contentCount){
                editFile<<endl;
            }
        }
    }
    editFile.close();
}

/**
 * @brief Funkcia ktora "rozsiruje" zakladne menu. Umoznuje pridat alebo odstranit zaznam.
 * @param choice - vstup od uzivatela
 */
void subMenu(Invoice invoiceList[],int contentCount,string File){
    bool switcher=true;
    while(switcher){
        cout << "-----------------------------------------------------" << endl;
		cout << "|MENU| (Vyberte jednu z moznosti 1 - 3):" << endl;
		cout << "      1: Pridat zaznam" << endl;
		cout << "      2: Odstranit zaznam" << endl;
		cout << "      3: Spat do hlavneho menu" << endl;
		cout << "-----------------------------------------------------" << endl;

		unsigned int choice;
		cin>>choice;
		cin.clear();
        cin.ignore(10000,'\n');

        while(choice>3||choice<1||cin.fail()){
            cout<<"ERROR.Zadajte znovu prosim."<<endl;
            cin>>choice;
            cin.clear();
            cin.ignore(1000,'\n');
        }

        switch(choice){
            case 1:{
                Add(false,File,contentCount,invoiceList);
                switcher=false;
            }break;
            case 2:{
                removeData(invoiceList,contentCount,File);
                cout<<"Zaznam bol vymazany"<<endl;
                switcher=false;
            }break;
            case 3:{
                switcher=false;
            }break;
        }
    }
}

/**
 * @brief Funkcia hlada najmensi a najvacsi rok zo suboru
 */
void FindYears(Invoice invoiceList[],int contentCount,int &Min,int &Max){

    for(int i=0;i<contentCount;i++){
        if(i==0){
            Min=invoiceList[i].date.year;
            Max=invoiceList[i].date.year;
            continue;
        }
        if(Min>invoiceList[i].date.year){
            Min=invoiceList[i].date.year;
        }
        if(Max<invoiceList[i].date.year){
            Max=invoiceList[i].date.year;
        }
    }
}

/**
 * @brief Funkcia vracia suhrn zaznamov za jednotlivy mesiac.
 * @param num - pocet zaznamov za mesiac
 * @param return - vracia pocet zaznamov
 */
int countNotes(Invoice invoiceList[],int sumary,int month,int year){
    int num=0;
    for(int i=0;i<sumary;i++){
        if(invoiceList[i].date.year==year&&invoiceList[i].date.month==month){
            num++;
        }
    }
    return num;
}

/**
 * @brief Funkcia ktora vyplni struktur Month vo funkcii HTML() zo ziskanych hodnot z funkcie monthSummary().
 */
void Fill(Invoice invoiceList[],int contentCount,int month,int year,Invoice currentMonth[],int lengthMonth){
    int j=0;
    for(int i=0;i<contentCount;i++){
        if(invoiceList[i].date.month==month&&invoiceList[i].date.year==year){
            currentMonth[j]=invoiceList[i];
            j++;
        }
    }
}

/**
 * @brief Funkcia zoraduje zaznamy v mesiaci podla uvedenej ciastky od najvacsieho.
 */
void sortMonth(Invoice currentMonth[],int lengthMonth){
    for(int i=0;i<lengthMonth;i++){
        bool switcher=false;
        for(int j=0;j<lengthMonth-i;j++){
            if(currentMonth[j].amount<currentMonth[j+1].amount){
                Invoice tmp=currentMonth[j];
                currentMonth[j]=currentMonth[j+1];
                currentMonth[j+1]=tmp;
                switcher=true;
            }
            if(!switcher){
            break;
            }
        }
    }
}


/**
 * @brief Funkcia vytvarajuca html subor
 * @param input - vstup od uzivatela
 * @param category - staticke pole kategorii
 */
void HTML(Invoice invoiceList[],unsigned int counter)
{
    string folder="../vystupnidata/";
    string name;
    cout<<"Zadajte nazov suboru: ";
    cin>>name;

    ofstream HTMLfile((folder+name+".html").c_str());
    cout<<endl;

    HTMLfile<<"<!DOCTYPE html>\n<head>\n<title>"<<name<<"</title>\n<link rel=\"stylesheet\"type=\"text/css\" href=\"styles.css\">\n</head>\n";
	HTMLfile<<"<body><h1>Suhrn financii za jednotlive mesiace</h1>";

	int minYear=0;
	int maxYear=0;

	string category[]={"Vyplata","Inkaso","Strava","Oblecenie","Cestovanie","Ostatne"};


	FindYears(invoiceList,counter,minYear,maxYear);
	for (int i=minYear;i<=maxYear;i++){
		for (int j=1;j<=12;j++){
			int monthSum = countNotes(invoiceList,counter,j,i);
			if (monthSum == 0)continue;

			Invoice Month[monthSum];
			Fill(invoiceList,counter,j,i,Month,monthSum);

			sortMonth(Month,monthSum);
			bool switcherB=true;
			double incomes=0;
			double expenses=0;
			double allCategories[6];
			for (int k=0;k<monthSum;k++)
			{
				if (switcherB)
				{
					switcherB=false;
					HTMLfile<<"\n<h2>";
					switch (j){
                      case 1: HTMLfile<<"Januar";
                            break;
                        case 2: HTMLfile<<"Februar";
                            break;
                        case 3: HTMLfile<<"Marec";
                            break;
                        case 4: HTMLfile<<"April";
                            break;
                        case 5: HTMLfile<<"Maj";
                            break;
                        case 6: HTMLfile<<"Jun";
                            break;
                        case 7: HTMLfile<<"Jul";
                            break;
                        case 8: HTMLfile<<"August";
                            break;
                        case 9: HTMLfile<<"September";
                            break;
                        case 10: HTMLfile<<"Oktober";
                            break;
                        case 11: HTMLfile<<"November";
                            break;
                        case 12: HTMLfile<<"December";
                            break;
                        }
                        HTMLfile<<" "<<i<<"</h2>";
                        HTMLfile<<"\n<table>\n\t<th>ID</th>\n\t<th>Typ</th>\n\t<th>Kategoria</th>\n\t<th>Ciastka (v EUR)</th>\n\t<th>Datum</th>\n</tr>";
				}
                if(Month[k].category=="Vyplata"){allCategories[0]+=Month[k].amount;}
                else if(Month[k].category=="Inkaso"){allCategories[1]+=Month[k].amount;}
                else if(Month[k].category=="Strava"){allCategories[2]+=Month[k].amount;}
                else if(Month[k].category=="Oblecenie"){allCategories[3]+=Month[k].amount;}
                else if(Month[k].category=="Cestovanie"){allCategories[4]+=Month[k].amount;}
                else {allCategories[5]+=Month[k].amount;}

                HTMLfile<<"\n<tr>";
                HTMLfile<<"\n\t<td>"<<Month[k].ID<<"</td>";
                HTMLfile<<"\n\t<td>"<<Month[k].type<<"</td>";
                HTMLfile<<"\n\t<td>"<<Month[k].category<<"</td>";
                if(Month[k].type=="Prijem"){HTMLfile<<"\n\t<td>"<<"+";}
                else{HTMLfile<<"\n\t<td>"<<"-";}
                HTMLfile<<fixed<<setprecision(2)<<Month[k].amount<<"</td>";
                HTMLfile<<"\n\t<td>"<<Month[k].date.day<<"."<<Month[k].date.month<<"."<<Month[k].date.year<<"</td>";
                if(Month[k].type=="Prijem"){incomes+=Month[k].amount;}
                if(Month[k].type=="Vydaj"){expenses+=Month[k].amount;}
                HTMLfile<<"\n\t</tr>";
			}
            HTMLfile<<"\n</table>";
            HTMLfile<<"\n<table>\n\t<th>Prijem/Vydaj</th>\n\t<th>Ciastka (v EUR)</th>\n</tr>";
            HTMLfile<<"\n<tr>";
            HTMLfile<<"\n\t<td>"<<"Prijmy"<<"</td>"<<"\n\t<td>"<<"+"<<incomes<<"</td>"<<"\n</tr>";
            HTMLfile<<"\n\t<td>"<<"Vydaje"<<"</td>"<<"\n\t<td>"<<"-"<<expenses<<"</td>"<<"\n</tr>";
            HTMLfile<<"\n\t<td><b>"<<"Celkovy stav"<<"</b></td>"<<"\n\t<td><b>";

            if((incomes-expenses)>0){HTMLfile<<"+";}

            HTMLfile<<(incomes-expenses)<<"</b></td>"<<"\n</tr>";
            HTMLfile<<"\n</table>";
		}
	}
	HTMLfile<<"\n</body>\n</html>";
	HTMLfile.close();
}

/**
 * @brief Hlavna funkcia, ktora riadi program
 * @param fileNO - premenna, ktora urcuje, ci je otvoreny vstupny subor
 * @param loadFile - premenna, ktora urcuje nacitanie vstupu
 * @param menu - premenna, ktora urcuje nacitanie menu
 * @param counter - pocet zaznamov v subore
 */
int main()
{
    string File;
    string Folder="../vstupnidata/";
    cout<<"Vytajte v programe na spravu domaceho uctovnictva."<<endl<<endl;


    bool fileNO=false; //fileNotOpened
    bool loadFile; //needLoadFile
    bool menu; //showMenu

   while(loadFile){
        loadFile=false;
        if(!open_csv_file(Folder,File,fileNO)){
            cout<<"Nebol nacitany ziadny subor"<<endl;
            cout<<"Koniec programu"<<endl;
            return 0;
        }

        fileNO=false;
        ifstream inFile((Folder+File+".csv").c_str());
        int counter=LinesCounter(inFile);

        if(counter==0){
            cout<<"Subor je prazdny"<<endl;
            cout<<"Koniec programu"<<endl;

            inFile.close();
            return 0;
        }

        Invoice *invoiceList=new Invoice[counter];
        if(!AddToDatabase(inFile,invoiceList)){
            cout<<"Subor nebol otvoreny."<<endl;
            cout<<"Koniec programu"<<endl;
            delete[] invoiceList;
            inFile.close();
            return 0;
        }
        inFile.close();

        menu=true;
        while(menu){
            int userChoice=MENU(counter,File);
            switch(userChoice){
                case 1:{
                    showData(invoiceList,counter);

                    cout<<"Chcete vytvorit HTML subor vypisu? (A/N)   ";
                    char userChoice;
                    cin>>userChoice;
                    cin.clear();
                    cin.ignore(10000,'\n');
                    userChoice=toupper(userChoice);

                    while((userChoice!='A'&&userChoice!='N')||(cin.fail())){
                        cout<<"Nespravna odpoved. Zadajte (A)no alebo (N)ie.  ";
                        cin>>userChoice;
                        cin.clear();
                        cin.ignore(10000,'\n');
                        userChoice=toupper(userChoice);
                    }

                    if(userChoice=='A'){
                        HTML(invoiceList,counter);
                        cout<<"Vypisujem do HTML"<<endl;
                    }
                }break;
                case 2:{
                    string editFile=(Folder+File+".csv").c_str();
                    subMenu(invoiceList,counter,editFile);

                    fileNO=true;
                    loadFile=true;
                    menu=false;
                }break;
                case 3:{
                    menu=false;
                    loadFile=true;
                    delete[]invoiceList;
                    open_csv_file(File,Folder,fileNO);
                }break;
                case 4:{
                    menu=false;
                    delete[]invoiceList;
                    cout<<"Ukoncujem program"<<endl;
                }break;
            }
        }
    }


return 0;
}



