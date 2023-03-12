#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <unistd.h>
using namespace std;

int crewNumber = 681, actorNumber = 54, numberOfExtras = 132, numberOfPeople = 735, everybody = 867;
string soup[29],mainDish[29],dessert[29];
string supa[29], felPrincipal[29],desert[29];

//TEMPLATE-URI
template <class T>
void write(T x)
{
    cout <<"COSTUL TOTAL.csv\n";
}

template<>
void write(char x)
{
    cout <<"MENIU IN ENGLEZA.csv\n";
}

template<>
void write(int x)
{
    cout <<"MENIU IN ROMANA.csv\n";
}

template<>
void write(double x)
{
    cout <<"PEOPLE.csv\n";
}

//creare fisier cu cast&crew + extras
void read_record()
{
	fstream fin, cinn, fout;

	// Open an existing file
	fin.open("castcrew.csv", ios::in);
    cinn.open("extras.csv", ios::in);
    fout.open("people.csv",ios::out);


	vector<string> row;
	string line, word, temp;
    int count = 0;
    //735 de actori si crew
	while (count != 735) {

		row.clear();
        
		getline(fin, line);

		// used for breaking words
		stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (std::getline(s, word, ',')) {

			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}
        count ++;
		fout << row[0] << ',' <<row[1]<<"\n";
		
	}
    //procedam la fel si pentru figuranti/extras
    count = 0;

    //132 de figuranti
    while (count != 132) {

		row.clear();
        
		getline(cinn, line);

		// used for breaking words
		stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (std::getline(s, word, ',')) {

			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}
        count ++;
        fout << row[0] << ',' <<row[1]<<"\n";
		
	}

	fin.close();
    cinn.close();
    fout.close();
}

//CLASA PERSOANA
class Persoana
{
public:
char tipDieta[10], job[30];
int camera;

//constructor default
Persoana(){
    strcpy(tipDieta,"normal");
    strcpy(job,"crew");
    camera = 0;
    
}
~Persoana(){};
void asignareCrew()
{
  int  nrandom;
  char food[3][15]={"normal","vegetarian","pescetarian"};
  camera = 2;
  strcpy(job,"crew");
  nrandom = (rand() %3) + 1;
  strcpy(tipDieta, food[nrandom]);
}
};

//CLASA ACTOR CARE INCLUDE SI FIGURANTI
class Actori: public Persoana
{
    private:
    int figurant;
    public:
    char personaj[10];
    
    //constructor default
    Actori()
    {
        strcpy(personaj,"default");
        figurant = -1;
        strcpy(tipDieta,"normal");
        strcpy(job,"crew");
        camera = 0;

    }
    ~Actori(){};

    void setFigurant(int fig)
    {
        this -> figurant = fig;
    }

    int getFigurant()
    {
        return figurant;
    }
    friend void costTotal(Persoana member[813], Actori actor[54], int zile,fstream &fout);
    
    //FIGURANT
    void asignare(int fig)
    {
    int i, nrandom;
    char food[3][15]={"normal","vegetarian","pescetarian"};
    char role[5][15] = {"Vampir","Werewolf","Sirena","Psychic","Human"};

    camera = 3;
    strcpy(job , "extras");
    nrandom = (rand() %3) + 1;
    strcpy(tipDieta, food[nrandom]); 
    figurant = 1;  
    }

    //ACTOR
    void asignare()
    {
    int i, nrandom;
    char food[3][15]={"normal","vegetarian","pescetarian"};
    char role[5][15] = {"Vampir","Werewolf","Sirena","Psychic","Human"};

    camera = 2;
    strcpy(job , "extras");

    nrandom = (rand() %3) + 1;
    strcpy(tipDieta, food[nrandom]); 

    figurant = 0;  
    nrandom = (rand() % 5) + 1;
    strcpy(personaj,role[nrandom]);
    }

};

//CALCULARE COST TOTAL
void costTotal(Persoana member[813], Actori actor[54], int zile,fstream &fout)
{
 int i;
 int transport, cazare, machiaj, apa, mancare;
 double pretTransport, pretCazare, pretMachiaj=0, pretLichide, pretMancare, pretTotal;
 int nr_autocare, suc, cafea, reducere;
 double dollar;
 dollar = 4.62;
 
 //TRANSPORT
 nr_autocare = ceil(numberOfPeople/50);
 if(numberOfPeople % 50 != 0)nr_autocare ++;
 pretTransport = 5680 * nr_autocare *2; //dus intors
 fout <<std::fixed<<std::setprecision(2) << pretTransport/dollar <<',';
 
 //LICHIDE
 suc = ceil(0.8 * everybody);
 apa = everybody;
 cafea = ceil(0.5 * everybody);
 pretLichide = suc* 4 + 30* cafea + everybody* 3; //pret pentru o zi
 pretLichide *=zile;

 //CASTEL
 pretCazare = 10000;
 reducere  = 2*floor(zile/10) * pretCazare/10; 
 pretCazare = pretCazare*zile - reducere; 
 fout <<std::fixed<<std::setprecision(2) << pretCazare/dollar <<',';
 
 //ACOMODARE
 pretCazare = 0;
 zile--;
 pretCazare += ceil(crewNumber/2) * 350 * zile;
 pretCazare += ceil(actorNumber/2)* 350 * zile;
 pretCazare += ceil(numberOfExtras/3) * 420 * zile;
 zile++;
 fout <<std::fixed<<std::setprecision(2)<<pretCazare/dollar <<',';

 //MACHIAJ SI MANCARE ACTORI + FIGURANTI
 for(i = 1; i <= actorNumber+numberOfExtras; i++)
 {
    if(strcmp(actor[i].personaj,"Vampir") == 0) pretMachiaj += 230*zile;
    else if(strcmp(actor[i].personaj,"Werewolf") == 0) pretMachiaj +=555*zile;
    else if(strcmp(actor[i].personaj,"Sirena") == 0) pretMachiaj +=345*zile;
    else if(strcmp(actor[i].personaj,"Psychic") == 0) pretMachiaj +=157*zile;
    else if(strcmp(actor[i].personaj,"Human") == 0) pretMachiaj +=55*zile;

    if(strcmp(actor[i].tipDieta,"normal") == 0) pretMancare +=40*zile;
    if(strcmp(actor[i].tipDieta,"vegetarian") == 0) pretMancare +=33*zile;
    if(strcmp(actor[i].tipDieta,"pescetarian") == 0) pretMancare +=46*zile;
 }
 
 //MANCARE CREW 
  for(i = 1; i <= crewNumber; i++)
 {
    if(strcmp(member[i].tipDieta,"normal") == 0) pretMancare += 40*zile;
    if(strcmp(member[i].tipDieta,"vegetarian") == 0) pretMancare += 33*zile;
    if(strcmp(member[i].tipDieta,"pescetarian") == 0) pretMancare += 46*zile;

 }
 pretTotal = pretTransport + pretMancare + pretMachiaj + pretCazare + pretLichide;
 fout <<std::fixed<<std::setprecision(2)<<(pretMancare + pretLichide)/dollar<<','<<pretMachiaj/dollar<<','<<pretTotal/dollar<<'\n';
 
 

}

//CREARE MENIU MANCARE 3 ZILE
void createMenu()
{
    /*supa,main,dessert
    0-normal;  10-vegetarian; 20-pescetarian
    */

    fstream fin,fout,bin,bout;
    int i,nrandom;
    fin.open("meals.csv", ios::in);
    fout.open("meniu in engleza.csv", ios::out);

    bin.open("feluri.csv", ios::in);
    bout.open("meniu in romana.csv", ios::out);

    //.........................................start creare vector meals
	vector<string> row;
	string line, word, temp;
    int count = 0;

	while (count <= 29) {
    //am creat un fisier cu mai multe posibilitati de feluri de mancare. Fiecare fel il voi stoca in vector pe categorii: supa,main,desert;
		row.clear();
		getline(fin, line);
		stringstream s(line);

		while (std::getline(s, word, ',')) 
			row.push_back(word);
		
        soup[count] = row[0];
        mainDish[count] = row[1];
        dessert[count] = row[2];
        count++;
	}

    count = 0;

    while(count <= 29)
    {
        //la fel procedez si pentru meniul in romana
        row.clear();
        getline(bin,line);
        stringstream s(line);
        while (std::getline(s, word, ',')) 
			row.push_back(word);
		
        supa[count] = row[0];
        felPrincipal[count] = row[1];
        desert[count] = row[2];

        count ++;
    }
	fin.close();
    bin.close();
    //..........................................finish creare vector meals

    //GENERARE MENIU RANDOM 
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 9); // define the range
    std::uniform_int_distribution<> b(10, 19); // define the range
    std::uniform_int_distribution<> c(20, 29); // define the range
     
        //creare meniu normal
        fout <<"Normal:\n";
        bout <<"Normal:\n";
        for(int j = 1; j<=3; j++)
        {
        //aleg un numar random si avand in vedere ca vectorii contin aceeasi informatie doar ca in limbi diferite, atunci numarul ales random este acelasi pentru ambii vectori
        nrandom = distr(gen);
        fout << soup[nrandom]<<',';
        bout << supa[nrandom] <<',';

        nrandom = distr(gen);
        fout << mainDish[nrandom]<<',';
        bout << felPrincipal[nrandom] <<',';
        
        nrandom = distr(gen);
        fout << dessert[nrandom]<<'\n';
        bout << desert[nrandom]<<'\n';
        }

        //creare meniu vegetarian
        fout <<"Vegetarian:\n";
        bout <<"Vegetarian:\n";
        
        for(int j = 1; j<=3; j++)
        {
        nrandom = b(gen);
        fout << soup[nrandom]<<',';
        bout << supa[nrandom] <<',';
        nrandom = b(gen);
        fout << mainDish[nrandom]<<',';
        bout << felPrincipal[nrandom] <<',';
        nrandom = b(gen);
        fout << dessert[nrandom]<<'\n';
        bout << desert[nrandom]<<'\n';
        }
        //creare meniu pescetarian
        fout <<"Pescetarian:\n";
        bout <<"Pescetarian:\n";
        for(int j = 1; j<=3; j++)
        {
        nrandom = c(gen);
        fout << soup[nrandom]<<',';
        bout << supa[nrandom] <<',';
        nrandom = c(gen);
        fout << mainDish[nrandom]<<',';
        bout << felPrincipal[nrandom] <<',';
        nrandom = c(gen);
        fout << dessert[nrandom]<<'\n';
        bout << desert[nrandom]<<'\n';
        }
        
    fout.close();
    bout.close();
    
    //.................................................FINISH GENERARE
}


int main()
{
 int i,zile[4]={30,45,60,100},j;
 read_record();
 Persoana member[685]; //crew si figuranti
 Actori actor[186];

 //folosesc metode
 for(i = 0; i <= crewNumber; i++)
    member[i].asignareCrew();
    
 for(i = 0; i<=actorNumber; i++)
    actor[i].asignare();
 
 for(i = actorNumber; i<=actorNumber + numberOfExtras; i++)
    actor[i].asignare(1);
 
 fstream fout;
 fout.open("Costul total.csv",ios::out);
 
 fout << "Transport,Castel,Acomodare,Mancare si apa, Machiaj,Total\n";
 for(j = 0;j<=3; j++)
 {
     fout << zile[j] <<"ZILE:\n";
     costTotal(member, actor,zile[j], fout);
 }
 fout.close();
 createMenu();
 int x;
    char y;
    double z;
    //parte de template-uri ca sa afli ce nume au fisierele in care am pus informatia ceruta
 cout << "Fisierele au fost create.\n";
 try{
    
    cout <<"Daca doresti sa afli numele fisierului csv pentru meniul in romana, introdu un numar intreg:";
    cin >> x;
    if(!int(x)) throw "Nu ai introdus corect";
    write(x);
    
    cout <<"Daca doresti sa afli numele fisierului csv pentru meniul in engleza, scrie 'e': ";
    fflush(stdin);
    cin >> y;
    if(y != 'e') throw "Nu ai introdus corect";
    write(y);
 
    cout <<"Daca doresti sa afli numele fisierului csv pentru informatiile cu oamenii, scrie 1.12: ";
    fflush(stdin);
    cin >> z;
    if(z != 1.12) throw "Nu ai introdus corect";
    write(z);
 }
 catch (const char* msg)
 {cout << msg << endl;}

 return 0;


}